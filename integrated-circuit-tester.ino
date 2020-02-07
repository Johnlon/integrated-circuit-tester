#include "test_ic.h"
#include "chipsDatabase.h"
#include "myChipsDatabase.h"
#include "io.h"
#include "strings.h"

void setup() {
  Serial.begin(9600);
  mcp_setup();
  
  //interactive();
  decay();
  
  //emptySocket();
  //identify();
  //barLedTestPattern();

  reset();
  delay(1000000);
}
void loop() {}
