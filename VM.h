#pragma once
#include <Arduino.h>
#include <Microchip_23LC1024.h>

#define SRAM  5
#define HOLD  7

#define VERBOSE 0
#define TABLE_SIZE 4
#define PAGE_SIZE 32

class VM {
  public:
    VM();
    int getFaultRate();
    void resetFaultRate();
    byte& operator[] (const unsigned long index);
    int findPage(unsigned long page);
    int loadPage(unsigned long page);

  private:
    int page_table[TABLE_SIZE];
    byte physical_memory[TABLE_SIZE * PAGE_SIZE];
    int victim_index;
    float page_fault_rate;
    int references_count;
    int page_faults_count;
    Microchip_23LC1024 sram;
};
