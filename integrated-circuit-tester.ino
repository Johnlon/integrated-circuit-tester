#include "chip.h"

  // 74245 pin 1 dir 0=a2b, 1=b2a
  // left side is port A
  // pin 19 of 20 is /OE
Chip cEmpty = chip("EMPTY", "Empty ZIF")
                  .scenario("ZZZZZZZZZZZ/ZZZZZZZZZZZ", "Empty");

Chip c74245 = chip("74245", "Transceiver 8 bit")
                  .scenario("XZZZZZZZZG/ZZZZZZZZ1V", "OE disabled")
                  .scenario("100000000G/LLLLLLLL0V", "A to B all low")
                  .scenario("111111111G/HHHHHHHH0V", "A to B all high")
                  .scenario("0LLLLLLLLG/000000000V", "B to A all low")
                  .scenario("0HHHHHHHHG/111111110V", "B to A all high");

Chip c74242 = chip("74242", "Transceiver Inverting 4 bit")
                  .scenario("1ZZZZZG/ZZZZZ0V", "OEA and OEB both disabled")
                  .scenario("0ZZZZZG/ZZZZZ1V", "OEA and OEB both enabled")
                  .scenario("0Z0000G/HHHHZ1V", "A to B all low")
                  .scenario("0Z1111G/LLLLZ1V", "A to B all high")
                  .scenario("1ZHHHHG/0000Z1V", "B to A all low")
                  .scenario("1ZLLLLG/1111Z1V", "B to A all high");


// Chip cLedArray8 = chip("LED Array 8 ", "8 bar led array")
//                   .scenario("00000000/ZZZZZZZZ", "No power")
//                   .scenario("11111111/HHHHHHHH", "All powered")
//                   ;

// only include the chips you want to include in the scan - reduces the
// program storage space needed
Chip chips[] = {c74245, c74242, cEmpty};

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
      Serial.println("matches " + String(chip.name));
    else
      Serial.println("not " + String(chip.name));
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
