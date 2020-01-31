#include <Adafruit_MCP23017.h>

#ifdef USE_VI_PINS
#define PATCH '-'
#endif

Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;

void mcp_setup() {
  mcp1.begin(0);  //  address 0 = extender 1
  mcp2.begin(1);  // address 1 = extender 2
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

    // discharge/force to a definitive value - ie low
    xPinMode(gpioH, OUTPUT);
    xDigitalWrite(gpioH, LOW);
        
    // disconnect
    xPinMode(gpioL, INPUT);
    xPinMode(gpioH, INPUT);
  }
}

void xPinMode(uint8_t p, uint8_t d) {
  int pin=-1;
  String device = "";
  if (p < EXTENDER1_OFFSET) {
    pin = p;
    device = "arduino";
    pinMode(pin, d);
  } else if (p < EXTENDER2_OFFSET) {
    pin = p - EXTENDER1_OFFSET;
    device = "extender1";
    mcp1.pinMode(pin, d);
  } else {
    pin = p - EXTENDER2_OFFSET;
    device = "extender2";
    mcp2.pinMode(pin, d);
  } 

  //Serial.println("xPinMode("+  device + " pin " + pin + ", " + String(d) + ")");
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

String fillUnusedPins(const String& test) {
  int unused = 2*unusedSlots(test.length());

  String fill = "";
  
  while (unused -- > 0) { 
    fill += "u";
  }

  String left = test.substring(0, test.length()/2);
  String right = test.substring((test.length()/2), test.length());
  
  // Serial.println("IN    "+ test);
  // Serial.println("LEFT  "+ left);
  // Serial.println("RIGHT "+ right);
  // Serial.println("FILL  "+ fill);

  return left + fill + right;
}


/*
   param "scenario" is the test case input and output state definition.
   even a trivial ic will require a sequence of these cases to tests it
   effectively.

   "scenario" is a string containing a sequence of character codes, one for each
   pin of the test IC.

  See the README for a full list of input and result codes.

   returns true if test passes, false otherwise
*/
boolean test_ic(String scenario, String name) {
  //reset();

  scenario.replace("/", "");

#ifdef USE_VI_PINS  // but in original board - this tweak pushes the test case
                    // down the Zif by on position
  scenario = patchScenario(scenario);
#endif

  scenario = fillUnusedPins(scenario);

//  Serial.print("Testcase : " + scenario + "  : " + name);

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
      case PATCH:   
      case 'X':  
        // dont care - set to weak pull up so as not to leave floating
        xPinMode(gpioL, INPUT_PULLUP);
        xPinMode(gpioH, INPUT);
        //xDigitalWrite(gpioH, LOW);
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
        xPinMode(gpioL, OUTPUT);  
        xDigitalWrite(gpioL, HIGH);
        xPinMode(gpioH, INPUT);  
        break;
      case '0':
        xPinMode(gpioL, OUTPUT); 
        xDigitalWrite(gpioL, LOW);
        xPinMode(gpioH, INPUT); 
        break;
      
      // FOR CLK INPUT
      case 'C':
        clkPin = gpioL;
        xPinMode(gpioL, OUTPUT);
        xDigitalWrite(gpioL, LOW); // low intially, will be toggled later
        xPinMode(gpioH, INPUT);  
        break;
    
      // EXPECTATIONS OF THE OUTPUTS OF THE IC
      case 'L':
        // TODO Do a Z-like test and expect it to always return L - ie pull is ineffective
        // or is it enought to gently pull it the opposite direction? << temp solution 
        //  ztest is better and we could show a Z in the output
        xPinMode(gpioL, INPUT); 
        xPinMode(gpioH, OUTPUT);  
        xDigitalWrite(gpioH, HIGH);
        break;
      case 'H':
        // TODO: Do a Z-like test and expect it to always return L - ie pull is ineffective
        // or is it enought to gently pull it the opposite direction? << temp solution 
        //- ztest is better and we could show a Z in the output
        xPinMode(gpioL, INPUT);  
        xPinMode(gpioH, OUTPUT);  
        xDigitalWrite(gpioH, LOW);
        break;

      // FOR Z OUTPUT - there will be two tests, 
      // one with gpioL as H and another as L to see if this
      case 'u':
      case 'Z':
        xPinMode(gpioL, INPUT);   
        xPinMode(gpioH, OUTPUT);  
        break;

      case '?':
        // TODO: test for Z and we could show a Z in the output
        xPinMode(gpioL, INPUT);  
        xPinMode(gpioH, INPUT);  
        break;

    }
  }

  delay(5);

  // toggle the clock high then low
  if (clkPin != -1) {
    Serial.println("\nclocking");

    // let clock pin of the IC float to logic high - not sure why we don't just
    // set this as a high output from the arduino? perhaps this is more
    // efficient as there is less current drain?
    //xPinMode(clkPin, INPUT_PULLUP);
    xDigitalWrite(clkPin, HIGH);
    delay(10);
    //xPinMode(clkPin, OUTPUT);
    xDigitalWrite(clkPin, LOW);
  }

  delay(10);

  
//  Serial.println("Looping");
  boolean pass = true;
  boolean wasTest = false;
  boolean forcePrint = false;
// while(true) {
  String result = "";

  // Reading Outputs from the IC under test
  for (int i = 0; i < pins; i++) {
    Pins pinPair = toGPIOPin(i, pins);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;
  
    switch (scenario[i]) {
      case 'H':
        wasTest = true;
        // pull it low; if it still reads as H then its a solid H and not floating
        //xDigitalWrite(gpioL, LOW);
        if (!xDigitalRead(gpioL)) {
          pass = false;
          result += 'L';
        } else
          result += '.';
        break;
      case 'L':
        wasTest = true;
        // pull it high; if it still reads as L then its a solid L and not floating
        //xDigitalWrite(gpioL, HIGH);
        if (xDigitalRead(gpioL)) {
          pass = false;
          result += 'H';
        } else
          result += '.';
        break;

      case 'u':
      case 'Z':
        wasTest = true;
        //Serial.println("Z test  - read of pin " +String(gpioL) + " write "+String(gpioH));
        //Serial.println("WRITTEN HIGH");
        // pull it high; a Z should sense as H
        xDigitalWrite(gpioH, HIGH);
        //delay(2000);
        if (!xDigitalRead(gpioL)) {
          //Serial.println("err H");
          pass = false;
          result += 'l';  // expected H but got L
        } else {
          // pull it low; a Z should sense as L
          //Serial.println("WRITTEN LOW");
          xDigitalWrite(gpioH, LOW);
          //delay(2000);
          if (xDigitalRead(gpioL)) {
            //Serial.println("err L");
            pass = false;
            result += 'h';  // expected L but got H
          } else {
            result += '.';  // OK
            //Serial.println("ok");
          }
        }

        break;

      case '?':
        forcePrint = true;
        if (xDigitalRead(gpioL)) result += "1";
        else result += "0";
        break;

#ifdef USE_VI_PINS
      case PATCH:
        result += '-';
        break;
#endif

      default:
        // pin is an input or a don't care so display as underscore
        result += '_';
    }
  }

// Serial.println(">" + result);
// delay(1000);
// }

//  reset();

  if (pass) {
    if (wasTest)
      Serial.println(" : PASS");
    if (forcePrint) 
      Serial.println("Result   : " + result + " : " + name);
  } else {
    Serial.println(" : FAIL");
    Serial.println("Failure  : " + result);
  }

  return pass;
}

boolean test_ic(const String& scenario) {
  test_ic(scenario, "");
}


