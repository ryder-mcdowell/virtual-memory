#include "VM.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Begin\n");
  VM vm;

  vm[100] = 200;
  vm[200] = 400;
  vm[300] = 600;
  vm[400] = 800;
  vm[500] = 1000;
  Serial.println(vm[100]);
  vm[600] = 1200;

//  vm[7978] = 100;
//  Serial.println("------------------------------------------");
//  vm[127937] = 100;
//  Serial.println("------------------------------------------");
//  vm[39847] = vm[7978] + vm[127937];
//  Serial.println("------------------------------------------");
//  
//  Serial.print(vm[7978]);Serial.print(" + ");Serial.print(vm[127937]);Serial.print(" = ");Serial.println(vm[39847]);
}

void loop() {
  // put your main code here, to run repeatedly:
}
