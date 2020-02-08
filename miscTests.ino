#include "strings.h"

void emptySocket() {
  // 11 pin each side socket empty self test - 11 because orig hw has bug on top
  test_ic(F("ZZZZZZZZZZZ/ZZZZZZZZZZZ"), F("Empty socket self test"));
}

void decay() {
#define DECAY_TEST F("SSSSSSSSSSSSSSSSSSSSSS")
  test_ic(F("1111111111111111111111"), F("Charge pins up"));            // capacitance test
  test_ic(DECAY_TEST, F("0 secs"));  // capacitance test
  delay(1000);
  test_ic(DECAY_TEST, F("1 sec"));  // capacitance test
  delay(1000);
  test_ic(DECAY_TEST, F("2 secs"));  // capacitance test
  delay(4000);
  test_ic(DECAY_TEST, F("6 secs"));  // capacitance test
  delay(4000);
  test_ic(DECAY_TEST, F("10 secs"));  // capacitance test
  delay(5000);
  test_ic(DECAY_TEST, F("15 secs"));  // capacitance test
  delay(5000);
  test_ic(DECAY_TEST, F("20 secs"));  // capacitance test
  delay(5000);
  test_ic(DECAY_TEST, F("25 secs"));  // capacitance test
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
