#include "model.h"

int main() {
  cube test;
  test.turn('r');
  test.turn('u');
  test.printCube();
  test.turn('r', 1);
  test.turn('u', 1);
  test.printCube();  
}
