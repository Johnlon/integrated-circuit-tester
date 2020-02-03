#include "test_ic.h"
#include "chipsDatabase.h"
#include "myChipsDatabase.h"

  // 74245 pin 1 dir 0=a2b, 1=b2a
  // left side is port A
  // pin 19 of 20 is /OE

// only include the chips you want to include in the scan - reduces the
// program storage space needed
Chip chips[] = {
  CHIP_EMPTY,
  CHIP_c74245, 
  CHIP_74138
 };
 
void setup() {
  Serial.begin(9600);
  mcp_setup();

  //emptySocket();
  identify();
  //barLedTestPattern();

  reset();
  delay(1000000);
}

void identify() {
  // Work in progress - chip detection - test all scenarios
  Serial.println("\n=======================");
  Serial.println("IDENTIFYING ... ");

  for (const Chip& chip : chips) {
    reset();

    Serial.println("\nTesting: " + String(chip.name) + " : " +
                   String(chip.description));

    const Scenario* testcase = chip.scenarios;
    bool allok = true;
    while (testcase != NULL) {
      // reset();

      bool ok = test_ic(testcase->test, testcase->name);
      if (!ok)
        allok = false;
      testcase = testcase->next;
    }

    if (allok)
      Serial.print("matches ");
    else
      Serial.print("not ");
    
    Serial.println(chip.name);
  }

  reset();
}

void emptySocket() {
  // 11 pin each side socket empty self test - 11 because orig hw has bug on top
  test_ic("ZZZZZZZZZZZ/ZZZZZZZZZZZ", "Empty socket self test");
}
void decay() {
  Serial.println("Testcase :  1111111111111111111111");
  test_ic("1111111111111111111111");            // capacitance test
  test_ic("??????????????????????", "0 secs");  // capacitance test
  delay(1000);
  test_ic("??????????????????????", "1 sec");  // capacitance test
  delay(1000);
  test_ic("??????????????????????", "2 secs");  // capacitance test
  delay(4000);
  test_ic("??????????????????????", "6 secs");  // capacitance test
  delay(4000);
  test_ic("??????????????????????", "10 secs");  // capacitance test
  delay(5000);
  test_ic("??????????????????????", "15 secs");  // capacitance test
  delay(5000);
  test_ic("??????????????????????", "20 secs");  // capacitance test
  delay(5000);
  test_ic("??????????????????????", "25 secs");  // capacitance test
}

void barLedTestPattern() {
  int i = 10;
  while (i-- > 0) {
    
    int i = 5;
    int d1 = 200;
    while (i-- > 0) {
      test_ic("11111111111/00000000000", "on");
      delay(d1);
      test_ic("00000000000/00000000000", "of");
      delay(d1);
    }
    
    int j = 16;
    int d2 = 20;
    while (j-->0) {
      test_ic("10001000100/00000000000", "walk");
      delay(d2);
      test_ic("01000100010/00000000000", "walk");
      delay(d2);
      test_ic("00100010001/00000000000", "walk");
      delay(d2);
      test_ic("00010001000/00000000000", "walk");
      delay(d2);
    }
  }
}
void loop() {}
