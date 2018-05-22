#include "VM.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Begin\n");
  VM vm;

  vm[100] = '&';
  vm[200] = '!';
  vm[300] = '@';
  vm[400] = '#';
  vm[500] = '$';
  Serial.println((char) vm[100]);
  Serial.println((char) vm[200]);
  Serial.println((char) vm[300]);

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
