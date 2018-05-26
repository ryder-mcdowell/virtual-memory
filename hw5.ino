#include "VM.h"


void setup() {
  Serial.begin(115200);
  VM vm;

  //vector summation
  unsigned long sum = 0;

  for (unsigned long i = 0; i < 100000; i++) {
    if (i < 50000) {
      vm[i] = (byte) 8;
    } else {
      vm[i] = (byte) 2;
    }
  }

  for (unsigned long i = 0; i < 50000; i++) {
    sum += (vm[i] + vm[i + 50000]);
  }

  Serial << "Sum = " << sum << endl << "Page Fault Rate = " << vm.getFaultRate() << endl;
  vm.resetFaultRate();


  //page thrashing
  char *msg = "This is page thrashing. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque tincidunt arcu eu blandit aliquam. Nunc sed tellus eu nunc vehicula viverra. Donec dictum, metus quis tempus venenatis, mauris elit condimentum felis, sit amet ullamcorper ipsum sapien quis libero. Donec sit amet viverra ipsum. Aenean egestas tortor ut urna pulvinar fermentum. Nam erat ipsum, rhoncus eu est ac, commodo laoreet odio. Quisque dui leo, gravida vitae magna at, auctor dictum dui. Cras hendrerit accumsan pretium. Nam ac velit ac elit ullamcorper mollis nec vel dolor.";

  for (int i = 0; i < strlen(msg); i++) {
    vm[i*PAGE_SIZE] = msg[i];
  }

  for (int i = 0; i < strlen(msg); i++) {
    Serial << (char) vm[i*PAGE_SIZE];
  }

  Serial << endl << "Page Fault Rate = " << vm.getFaultRate() << endl;
  vm.resetFaultRate();
}

void loop() {
  // put your main code here, to run repeatedly:
}
