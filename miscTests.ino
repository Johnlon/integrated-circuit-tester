#include "strings.h"

void check(int interval, int *elapsed) {
  char buf[16+1];
  itoa(*elapsed, buf, 10);

  test_ic("SSSSSSSSSSSSSSSSSSSSSS", buf);  // capacitance test
  delay(interval);
  *elapsed += interval;
}

void decay() {
  test_ic(F("1111111111111111111111"), F("Charge pins up"));            // capacitance test
  
  int elapsed = 0;
  int i = 25;
  while (i-- > 0) {
    check(1000, &elapsed);
  }
}

void testWithDelay(const __FlashStringHelper*  raw, const __FlashStringHelper* name, int delayMS) {
  test_ic(raw, name);
  delay(delayMS);
 }

void barLedTestPattern() {
  int o = 2;

  while (o-- > 0) {
    int i = 5;
    int d1 = 200;
  
    while (i-- > 0) {
      testWithDelay(F("11111111111/00000000000"), F("on"), d1);
      testWithDelay(F("00000000000/00000000000"), F("of"), d1);
    }

    int j = 16;
    int d2 = 20;
    
    while (j-->0) {
      testWithDelay(F("10001000100/00000000000"), F("walk"), d2);
      testWithDelay(F("01000100010/00000000000"), F("walk"), d2);
      testWithDelay(F("00100010001/00000000000"), F("walk"), d2);
      testWithDelay(F("00010001000/00000000000"), F("walk"), d2);
    }
  }
}
