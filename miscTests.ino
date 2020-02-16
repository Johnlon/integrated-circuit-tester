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

void barLedTestPattern() {
  int i = 10;
  while (i-- > 0) {
    
    int i = 5;
    int d1 = 200;
    while (i-- > 0) {
      test_ic(F("11111111111/00000000000"), F("on"));
      delay(d1);
      test_ic(F("00000000000/00000000000"), F("of"));
      delay(d1);
    }
    
    int j = 16;
    int d2 = 20;
    while (j-->0) {
      test_ic(F("10001000100/00000000000"), F("walk"));
      delay(d2);
      test_ic(F("01000100010/00000000000"), F("walk"));
      delay(d2);
      test_ic(F("00100010001/00000000000"), F("walk"));
      delay(d2);
      test_ic(F("00010001000/00000000000"), F("walk"));
      delay(d2);
    }
  }
}
