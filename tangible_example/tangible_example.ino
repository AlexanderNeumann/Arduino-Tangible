#include "Tangible.h"
Tangible tangible(0,1,600);

void setup() {
}

void loop() {
 tangible.update();
}

ISR(ANALOG_COMP_vect ) {
 tangible.checkTable();
}

