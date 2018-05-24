#include "VM.h"

VM::VM():sram(SRAM,HOLD) {
  //initialize running counters
  reference_count = 0;
  page_fault_count = 0;
  victim_index = 0;

  //initialize page table to be completely vacant
  for (int i = 0; i < TABLE_SIZE; i++) {
    page_table[i] = -1;
  }
}

int VM::getFaultRate() {
  return (page_fault_count / reference_count);
}

void VM::resetFaultRate() {
  page_fault_count = 0;
  reference_count = 0;
}

byte& VM::operator[] (const unsigned long index) {
  int page = floor(index / PAGE_SIZE);
  int offset = index % PAGE_SIZE;
  
  if (VERBOSE == 1) { Serial << "============================" << endl << "requesting virtual address: " << index << endl << "\tpage = " << page << ", offset = " << offset << endl; }
  reference_count += 1;

  int page_index = findPage(page);
  if (page_index == -1) {
    if (VERBOSE == 1) { Serial << "PAGE FAULT!" << endl; }
    //page fault
    page_fault_count += 1;
    page_index = loadPage(page, offset);
    return physical_memory[page_index * PAGE_SIZE + offset];
  } else {
    if (VERBOSE == 1) { Serial << "PAGE FOUND!" << endl << "\tpage table entry: " << page_index << endl << "\tphysical address: " << (page_index * PAGE_SIZE + offset) << endl; }
    //access page in physical memory @ page_location + offset
    return physical_memory[page_index * PAGE_SIZE + offset];
  }
  
}

int VM::findPage(unsigned long page) {
  int page_index = -1;
  /////////if (VERBOSE == 1) { Serial.println("$ Page Table: "); }
  for (int i = 0; i < TABLE_SIZE; i++) {;
    /////////if (VERBOSE == 1) { Serial.print("          | ");Serial.print(page_table[i]);Serial.println(" |"); }
    if (page == page_table[i]) {
      page_index = i;
    }
  }
  return page_index;
}

int VM::loadPage(unsigned long page, int offset) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    //if vacant spot in page table
    if (page_table[i] == -1) {
      if (VERBOSE == 1) { Serial << "\tempty slot in page table: " << i << endl << "\treading SRAM memory page: " << page << endl << "\tphysical address: " << (i * PAGE_SIZE + offset) << endl; }
      page_table[i] = page;    
      sram.read_page(page, &physical_memory[i * PAGE_SIZE]);  
      return i;
    }
  }
  if (VERBOSE == 1) { Serial << "\tNO SPACE in page table" << endl << "\tpage OUT: " << page_table[victim_index] << endl << "\tpage IN:  " << page << endl << "\tphysical address: " << (victim_index * PAGE_SIZE + offset) << endl; }
  //if no vacant spots, kick one out
  sram.write_page(page_table[victim_index], &physical_memory[victim_index * PAGE_SIZE]);
  page_table[victim_index] = page;
  sram.read_page(page, &physical_memory[victim_index * PAGE_SIZE]);
  
  int victim_index_previous = victim_index;
  victim_index += 1;
  if (victim_index == TABLE_SIZE) {
    victim_index = 0;
  }
  return (victim_index_previous);
}

