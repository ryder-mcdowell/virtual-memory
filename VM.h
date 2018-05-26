#pragma once
#include <Arduino.h>
#include <Microchip_23LC1024.h>
#include <Streaming.h>

#define SRAM 5
#define HOLD 7

#define VERBOSE 0
#define TABLE_SIZE 16
#define PAGE_SIZE 32

class VM {
  public:
    VM();
    float getFaultRate();
    void resetFaultRate();
    byte& operator[] (const unsigned long index);
    int findPage(int page);
    int loadPage(int page, int offset);

  private:
    int page_table[TABLE_SIZE];
    byte physical_memory[TABLE_SIZE * PAGE_SIZE];
    int victim_index;
    float page_fault_rate;
    unsigned long reference_count;
    unsigned long page_fault_count;
    Microchip_23LC1024 sram;
};
