#include "VM.h"

VM::VM():sram(SRAM,HOLD) {
  //initialize running counters
  references_count = 0;
  page_faults_count = 0;
  victim_index = 0;

  //initialize page table to be completely vacant
  for (int i = 0; i < TABLE_SIZE; i++) {
    page_table[i] = -1;
  }
}

int VM::getFaultRate() {

}

void VM::resetFaultRate() {

}

byte& VM::operator[] (const unsigned long index) {
  int page = floor(index / PAGE_SIZE);
  int offset = index % PAGE_SIZE;
  
  Serial.print("$ ");Serial.print("Request for address ");Serial.print(index);Serial.print(" | Page = ");Serial.print(page);Serial.print(" | Offset = ");Serial.println(offset);

  int page_index = findPage(page);
  if (page_index == -1) {
    Serial.print("$ ");Serial.print(page);Serial.println(" not found in Page Table (Page Fault)");
    //page fault
    page_index = loadPage(page);
    return physical_memory[page_index * PAGE_SIZE + offset];
  } else {
    Serial.print("$ ");Serial.print(page);Serial.println(" found in Page Table");
    //access page in physical memory @ page_location + offset
    return physical_memory[page_index * PAGE_SIZE + offset];
  }
  
}

int VM::findPage(unsigned long page) {
  int page_index = -1;
  Serial.println("$ Page Table: ");
  for (int i = 0; i < TABLE_SIZE; i++) {;
    Serial.print("          | ");Serial.print(page_table[i]);Serial.println(" |");
    if (page == page_table[i]) {
      page_index = i;
    }
  }
  return page_index;
}

int VM::loadPage(unsigned long page) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    //if vacant spot in page table
    if (page_table[i] == -1) {
      page_table[i] = page;    
      sram.read_page(page, &physical_memory[i * PAGE_SIZE]);  
      return i;
    }
  }
  Serial.print("$ ");Serial.print("Kicking out page ");Serial.println(victim_index);
  //if no vacant spots, kick one out
  sram.write_page(victim_index, &physical_memory[victim_index * PAGE_SIZE]);
  page_table[victim_index] = page;
  sram.read_page(page, &physical_memory[victim_index * PAGE_SIZE]);
  
  int victim_index_previous = victim_index;
  victim_index += 1;
  return (victim_index_previous);
}

