#include "VM.h"


void setup() {
  Serial.begin(115200);
  VM vm;

  int array_one[50000];
  int array_two[50000];

  int tmp = array_one[0] + array_two[0];
  

//  vm[2749] = 0xAB;
//  vm[963] = 0xCD;
//  vm[129775] = 0xEF;
//  vm[71066] = 0x01;

//  char *msg = "Hello from Virtual Memory!!!";
//  
//  for (int i = 0; i < strlen(msg); i++) {
//    vm[i*32] = msg[i];
//  }
//
//  for (int i = 0; i < strlen(msg); i++) {
//    Serial << (char) vm[i*32];
//  }
//  
//  Serial << endl;
}

void loop() {
  // put your main code here, to run repeatedly:
}
