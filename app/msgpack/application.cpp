#include <string>

#include "application.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

void setup() {
    Serial.begin(57600);
}

void loop() {
    delay(1000);
}
