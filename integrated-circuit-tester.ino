
struct Scenario {
  const char* test;
  const char* name;
  Scenario* next;

  Scenario(const char* test, const char* tname)
      : next(NULL), test(test), name(tname) {}
};

struct Chip {
  const char* name;
  const char* description;

  Scenario* scenarios;
  Chip* next;

  Chip(const char* name, const char* desc)
      : name(name), description(desc), scenarios(NULL), next(NULL) {}

  Chip& scenario(const char* test, const char* tname) {
    Scenario* s = new Scenario(test, tname);
    if (this->scenarios != NULL) {
      s->next = this->scenarios;
    }
    this->scenarios = s;
    return *this;
  }
};

Chip chips[] = {};

void setup() {
  Serial.begin(9600);
  Serial.println("Testing ...");


  // 74244 dir 0=a2b, 1=b2a
  // left side is port A
  // pin 19 of 20 is /OE
  Chip c74244("74244", "Transceiver 8 bit");
  c74244.scenario("XZZZZZZZZG/ZZZZZZZZ1V", "OE disabled")
      .scenario("100000000G/LLLLLLLL0V", "A to B all low")
      .scenario("111111111G/HHHHHHHH0V", "A to B all high")
      .scenario("0LLLLLLLLG/000000000V", "B to A all low")
      .scenario("0HHHHHHHHG/111111110V", "B to A all high");

  Chip c74242("74242", "Transceiver Inverting 4 bit");
  c74242.scenario("XZZZZZG/ZZZZZ1V", "OE disabled")
      .scenario("10HHHHG000001V", "A to B all low")
      .scenario("10LLLLG111101V", "A to B all high")
      .scenario("000000GHHHH00V", "B to A all low")
      .scenario("001111GLLLL00V", "B to A all high");

// only include the chips you want to include in the scan - reduces the program storage space needed
  Chip chips[] = {c74244, c74242};
  mcp_setup();

  // socket empty self test
  // test_ic("ZZZZZZZZZZ/ZZZZZZZZZZ", "Empty socket self test");


  // test_ic("XZZZZZZZZG/ZZZZZZZZ1V");  // 74245 - OE disabled
  // test_ic("100000000G/LLLLLLLL0V");  // 74245 - A to B all low
  // test_ic("111111111G/HHHHHHHH0V");  // 74245 - A to B all high
  // test_ic("0LLLLLLLLG/000000000V");  // 74245 - B to A all low
  // test_ic("0HHHHHHHHG/111111110V");  // 74245 - B to A all high

  // Work in progress - chip detection - test all scenarios
  Serial.println("\n=======================");
  Serial.println("IDENTIFYING ... ");

  for (const Chip& chip : chips) {
    Serial.println("\nTesting: " + String(chip.name) + " : " +
                   String(chip.description));

    const Scenario* testcase = chip.scenarios;
    bool allok = true;
    while (testcase != NULL) {
      bool ok = test_ic(testcase->test, testcase->name);
      if (!ok)
        allok = false;

      testcase = testcase->next;
    }

    if (allok) {
      Serial.println("! match for " + String(chip.name));
    }
  }

  delay(1000000);
  // reset();
}

void loop() {}
