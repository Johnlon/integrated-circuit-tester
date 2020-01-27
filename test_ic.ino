
#include <Adafruit_MCP23017.h>
#include "get_pin.h"

#ifdef USE_VI_PINS
#define PATCH '-'
#endif

#define IGNORE 'X'

Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;

void mcp_setup() {
  mcp1.begin(0);  //  address 0
  mcp2.begin(1);  // address 1
}

/* read from serial io */
int kbRead() {
  // send data only when you receive data:
  while (Serial.available() == 0) {
  }

  return Serial.read();
}

void reset() {
  Serial.println("\nresetting");

  for (int i = 0; i < NUM_PINS; i++) {
    Pins pinPair = toGPIOPin(i, NUM_PINS);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;

    xPinMode(gpioL, INPUT);
    xPinMode(gpioH, INPUT);
  }
}

void xPinMode(uint8_t p, uint8_t d) {
  // Serial.println("setting "+ String(p) + " as mode "+ String(d));

  if (p < 100) {
    // Serial.println("setting arduino "+ String(p) + " as mode "+ String(d));
    pinMode(p, d);
  } else if (p < 200) {
    // Serial.println("setting mcp1 "+ String(p-100) + " as mode "+ String(d));
    mcp1.pinMode(p - 100, d);
  } else if (p < 300) {
    // Serial.println("setting mcp2 "+ String(p-200) + " as mode "+ String(d));
    mcp2.pinMode(p - 200, d);
  } else
    halt("Error: pin number out of range: " + String(p));
}
void xDigitalWrite(uint8_t p, uint8_t d) {
  // Serial.println("writing " + String(d) + " to " + String(p));

  if (p < 100)
    digitalWrite(p, d);
  else if (p < 200)
    mcp1.digitalWrite(p - 100, d);
  else if (p < 300)
    mcp2.digitalWrite(p - 200, d);
  else
    halt("Error pin number of of range: " + String(p));
}
uint8_t xDigitalRead(uint8_t p) {
  if (p < 100) {
    return digitalRead(p);
  } else if (p < 200)
    return mcp1.digitalRead(p - 100);
  else if (p < 300)
    return mcp2.digitalRead(p - 200);
  else
    halt("Error pin number of of range: " + String(p));
}

// hardware design error - A6/A7 dont work as outputs so shift the scenario down
// one set of pins. do not use the top row in the zip socket
String patchScenario(String sin) {
  return PATCH + sin + PATCH;
}

/*
   param "scenario" is the test case input and output state definition.
   even a trivial ic will require a sequence of these cases to tests it
   effectively.

   "scenario" is a string containing a sequence of character codes, one for each
   pin of the test IC.

   The codes define the inputs and the expected outputs from the test subject.
   V=VCC of chip under test (set gpioL to high; set gpioH to high)
   G=GND of chip under test (set gpioL to low ; set gpioH to low)
   1=set input pin of chip under test to logic high
   0=set input pin of chip under test to logic low
   L=expect logic low output from chip under test
   H=expect logic high output from chip under test
   Z=expect high impedance output from chip under test
   X=dont care - gets set with a weak pull down
   /=ignored - use optionally as a left side right side separator for ease of
   reading or whatever else

   On output:
   .=pass for that pin
   -=one of the top two pins - theres a hardware fault on those so dont put the
   chip there
   _=the pin isn't an output so there's not test result
   H=a LOW was expected but HIGH was found
   L=a HIGH was expected but LOW was found
   h=a LOW was expected on the tristate test but HIGH was found
   l=a HIGH was expected on the tristate test but LOW was found

   

   returns true if test passes, false otherwise
*/
boolean test_ic(String scenario) {
  test_ic(scenario, "");
}
boolean test_ic(String scenario, String name) {
  Serial.println("Scenario : " + scenario + " " + name);

  scenario.replace("/", "");

#ifdef USE_VI_PINS  // but in original board - this tweak pushes the test case
                    // down the Zif by on position
  scenario = patchScenario(scenario);
#endif
  Serial.println("Testcase : " + scenario);

  int clkPin = -1;
  int pins = scenario.length();

  if (pins % 2 != 0) {
    halt("Scenario must have even number of pins : '" + scenario + "'");
  }

  // Setting Vcc, GND and output pins of the IC under test
  for (int i = 0; i < pins; i++) {
    Pins pinPair = toGPIOPin(i, pins);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;

    switch (scenario[i]) {
      case PATCH:   // dont care - set to weak pull up so as not to leave
                    // floating
      case IGNORE:  // dont care - set to weak pull up so as not to leave
                    // floating
        xPinMode(gpioL, INPUT);
        xPinMode(gpioH, OUTPUT);
        xDigitalWrite(gpioH, LOW);
        break;

      case 'V':
        xPinMode(gpioL, OUTPUT);
        xDigitalWrite(gpioL, HIGH);
        xPinMode(gpioH, INPUT);
        break;
      case 'G':
        xPinMode(gpioL, OUTPUT);
        xDigitalWrite(gpioL, LOW);
        xPinMode(gpioH, INPUT);
        break;

      // INPUTS TO IC
      case '1':
        xPinMode(gpioL,
                 OUTPUT);  // pull up in case IC pin is erroneously an input to
                           // avoid floating it and causing high current on HC
        xPinMode(gpioH, INPUT);  // the pullup won't affect the sense if the pin
                                 // is genuinely high or low
        break;
      case '0':
        xPinMode(gpioL,
                 OUTPUT);  // pull up in case IC pin is erroneously an input to
                           // avoid floating it and causing high current on HC
        xPinMode(gpioH, INPUT);  // the pullup won't affect the sense if the pin
                                 // is genuinely high or low
        break;

      // EXPECTATIONS OF THE OUTPUTS OF THE IC
      case 'L':
        xPinMode(gpioL,
                 INPUT_PULLUP);  // weakly pull up in case IC pin is erroneously
                                 // an input to avoid floating it and causing
                                 // high current on HC
        xPinMode(gpioL,
                 INPUT);  // we will set the gpio output to the opposite of the
                          // expected result - this allows us to distinguish a
                          // floating pin from a definite logic
        xPinMode(gpioH, INPUT);  // the pullup won't affect the sense if the pin
                                 // is genuinely high or low
        break;
      case 'H':
        xPinMode(gpioL,
                 INPUT_PULLUP);  // weakly pull up in case IC pin is erroneously
                                 // an input to avoid floating it and causing
                                 // high current on HC
        xPinMode(gpioL,
                 INPUT);  // we will set the gpio output to the opposite of the
                          // expected result - this allows us to distinguish a
                          // floating pin from a definite logic
        xPinMode(gpioH, INPUT);  // the pullup won't affect the sense if the pin
                                 // is genuinely high or low
        break;

      // FOR Z OUTPUT - there will be two tests one with gpioL as H and another
      // as L to see if this
      case 'Z':
        xPinMode(gpioL, INPUT);   // the pullup/down won't affect the sense if
                                  // the IC pin is genuinely high or low, but if
                                  // it's tristate then it will swing with gpioL
        xPinMode(gpioH, OUTPUT);  // we will pull this pin in both directions
        break;

      // FOR CLK INPUT
      case 'C':
        xPinMode(
            gpioL,
            INPUT_PULLUP);  // pull up in case IC pin is erroneously an input to
                            // avoid floating it and causing high current on HC
        xPinMode(gpioH, INPUT);  // the pullup won't affect the sense if the pin
                                 // is genuinely high or low but if it's
                                 // tristate then it will swing
        break;
    }
  }

  delay(5);

  // Serial.println("setting inputs of test chip");

  // setup the inputs to the IC under test
  for (int i = 0; i < pins; i++) {
    Pins pinPair = toGPIOPin(i, pins);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;

    switch (scenario[i]) {
      case IGNORE:  // ?? what is X - unused ?? ??
        xDigitalWrite(
            gpioH, LOW);  // set to low if not interesed / unused - don't float
        break;
      case '0':
        xDigitalWrite(gpioL, LOW);
        break;
      case '1':
        xDigitalWrite(gpioL, HIGH);
        break;
      case 'C':
        // set the clock pin to logic low initially
        clkPin = gpioL;
        xPinMode(gpioL, OUTPUT);
        xDigitalWrite(gpioL, LOW);
        break;
    }
  }

  // toggle the clock hign then low
  if (clkPin != -1) {
    Serial.println("\nclocking");

    // let clock pin of the IC float to logic high - not sure why we don't just
    // set this as a high output from the arduino? perhaps this is more
    // efficient as there is less current drain?
    xPinMode(clkPin, INPUT_PULLUP);
    delay(10);
    xPinMode(clkPin, OUTPUT);
    xDigitalWrite(clkPin, LOW);
  }

  delay(5);

  Serial.print("Response : ");

  boolean pass = true;

  // Reading Outputs from the IC under test
  for (int i = 0; i < pins; i++) {
    Pins pinPair = toGPIOPin(i, pins);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;
    //
    //    Serial.print("OUT ");
    //    Serial.println(gpioL);
    //    Serial.print("IN ");
    //    Serial.println(gpioH);

    switch (scenario[i]) {
      case 'H':
        // pull it low; if it still reads as H then its a solid H and not
        // floating
        xDigitalWrite(gpioL, LOW);
        if (!xDigitalRead(gpioH)) {
          pass = false;
          Serial.print('L');
        } else
          Serial.print('.');
        break;
      case 'L':
        // pull it high; if it still reads as L then its a solid L and not
        // floating
        xDigitalWrite(gpioL, HIGH);
        if (xDigitalRead(gpioH)) {
          pass = false;
          Serial.print('H');
        } else
          Serial.print('.');
        break;

      case 'Z':

        // pull it high; a Z should sense as H
        xDigitalWrite(gpioH, HIGH);
        if (!xDigitalRead(gpioL)) {
          pass = false;
          Serial.print('l');  // expected H but got L
        } else {
          // pull it low; a Z should sense as L
          xDigitalWrite(gpioH, LOW);
          if (xDigitalRead(gpioL)) {
            pass = false;
            Serial.print('h');  // expected L but got H
          } else {
            Serial.print('.');  // OK
          }
        }

        break;

#ifdef USE_VI_PINS
      case PATCH:
        Serial.print("-");
        break;
#endif

      default:
        // pin is an input or a don't care so display as underscore
        Serial.print("_");
    }
  }

  if (pass)
    Serial.println(" : good");
  else
    Serial.println(" : bad");
  // Serial.println("\nCase Result : "+String(result));
  return pass;
}
