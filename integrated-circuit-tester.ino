#include "chip.h"

void setup() {
  Serial.begin(9600);
  mcp_setup();
  
  // 74245 pin 1 dir 0=a2b, 1=b2a
  // left side is port A
  // pin 19 of 20 is /OE
  Chip c74245("74245", "Transceiver 8 bit");
  c74245.scenario("XZZZZZZZZG/ZZZZZZZZ1V", "OE disabled")
      .scenario("100000000G/LLLLLLLL0V", "A to B all low")
      .scenario("111111111G/HHHHHHHH0V", "A to B all high")
      .scenario("0LLLLLLLLG/000000000V", "B to A all low")
      .scenario("0HHHHHHHHG/111111110V", "B to A all high");

  Chip c74242("74242", "Transceiver Inverting 4 bit");
  c74242.scenario("1ZZZZZG/ZZZZZ0V", "OEA and OEB both disabled")
      .scenario("0ZZZZZG/ZZZZZ1V", "OEA and OEB both enabled")
      .scenario("0Z0000G/HHHHZ1V", "A to B all low")
      .scenario("0Z1111G/LLLLZ1V", "A to B all high")
      .scenario("1ZHHHHG/0000Z1V", "B to A all low")
      .scenario("1ZLLLLG/1111Z1V", "B to A all high");

  // only include the chips you want to include in the scan - reduces the
  // program storage space needed
  const Chip* chips[] = {&c74245, &c74242, NULL};

  Serial.println("Testing ...");

  // 11 pin each side socket empty self test - 11 because orig hw has bug on top
  // row
  // test_ic("ZZZZZZZZZZZ/ZZZZZZZZZZZ", "Empty socket self test");

//   // test_ic("XZZZZZZZZG/ZZZZZZZZ1V");  // 74245 - OE disabled
//     reset();
//     test_ic("100000000G/LLLLLLLL0V");  // 74245 - A to B all low
//     test_ic("100000000G/LLLLLLLL0V");  // 74245 - A to B all low
//     reset();
//  //   test_ic("111111111G/HHHHHHHH0V");  // 74245 - A to B all high
//     test_ic("100000000G/HHHHHHHH0V");  // 74245 - A to B all high
//     reset();
//  //   test_ic("111111111G/HHHHHHHH0V");  // 74245 - A to B all high
//     test_ic("100100000G/HHHHHHHH0V");  // 74245 - A to B all high
//     reset();
//     test_ic("??????????/??????????");  // 74245 - A to B all high
//   //  test_ic("0LLLLLLLLG/000000000V");  // 74245 - B to A all low
//   //  test_ic("0HHHHHHHHG/111111110V");  // 74245 - B to A all high

  identify(chips);

  reset();
  delay(1000000);
}

void identify(const Chip* chips[]) {
  // Work in progress - chip detection - test all scenarios
  Serial.println("\n=======================");
  Serial.println("IDENTIFYING ... ");

  int idx = 0;
  while (chips[idx] != NULL) {
    reset();

    const Chip& chip = *chips[idx++];

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
void loop() {}
