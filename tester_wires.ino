#include <Adafruit_MCP23017.h>
#include "tester_wires.h"

Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;

void mcp_setup() {
  mcp1.begin(0);  //  address 0 = extender 1
  mcp2.begin(1);  // address 1 = extender 2
}

// bottom 4 pins of 28 holes are not connected
#define SOCKET_PINS 24

#define EXTENDER1_OFFSET 100
#define EXTENDER2_OFFSET 200

#define GPA0  0
#define GPA1  1
#define GPA2  2
#define GPA3  3
#define GPA4  4
#define GPA5  5
#define GPA6  6
#define GPA7  7
#define GPB0  8
#define GPB1  9
#define GPB2  10
#define GPB3  11
#define GPB4  12
#define GPB5  13
#define GPB6  14
#define GPB7  15

#define MCP1(X) (EXTENDER1_OFFSET+X)
#define MCP2(X) (EXTENDER2_OFFSET+X)

// This revision tries to use A6/A7 as outputs but thats not supported.
// Unfortunately, this we was the circuit I turned into PCBs so that's sad. 
// Luckily however, A6/A7 gpio pins were used only by the top row of the socket so as long as we avoid the
// top row we are still in business.
// This software automatically skips those two Zif pins so make sure to insert the test chip on position down,
// or solder a 24 pin Zip in a position one down from it's natural position.  
struct Pins GPIO_PINS_V1[] = {
  // top left
  {8, 9}, // DEAD - HW BUG
  {6, 7},
  {4, 5},
  {2, 3},
  
  {MCP2(GPB6), MCP2(GPB7)},
  {MCP2(GPB4), MCP2(GPB5)},
  {MCP2(GPB2), MCP2(GPB3)},
  {MCP2(GPB0), MCP2(GPB1)},
  
  {MCP2(GPA0), MCP2(GPA1)},
  {MCP2(GPA2), MCP2(GPA3)},
  {MCP2(GPA4), MCP2(GPA5)},
  {MCP2(GPA6), MCP2(GPA7)},
  // bottom left 
  
  // bottom right
  {MCP1(GPA6), MCP1(GPA7)},
  {MCP1(GPA4), MCP1(GPA5)},
  {MCP1(GPA2), MCP1(GPA3)},
  {MCP1(GPA0), MCP1(GPA1)},
  
  {MCP1(GPB6), MCP1(GPB7)},
  {MCP1(GPB4), MCP1(GPB5)},
  {MCP1(GPB2), MCP1(GPB3)},
  {MCP1(GPB0), MCP1(GPB1)},

  {10, 11},
  {A1, A0},
  {A3, A2},
  {A7, A6}  // DEAD - HW BUG COS CANT USE A6/A7 AS OUTPUT
  
  // top right  - ie Vcc on 74 series
 };

// Map of IC test pins to pin pairs on the arduino down left side of the chip under test (or the zif socket) and up the right side
// first pin is pin 1 at top left of chip.
// Warning This pin setup uses pin D13 as part of tp13 (12th row). However, there are multiple references that
// state that it is risky using D13 as an input due to voltages being skewed because D13 is connected to ground via a 1k resistor and LED.
// This usage is deliberately the 12th row of pins towards the bottom of the Zif so that if there's an issue then it doesn't
// impact the usage of the top 11 pairs of pins. 
// See schematic .. https://www.arduino.cc/en/uploads/Main/Arduino_Nano-Rev3.2-SCH.pdf
// Nano specific issue .. https://forum.arduino.cc/index.php?topic=493665.0
// and https://arduinodiy.wordpress.com/2012/04/28/solving-the-d13-problem-on-your-arduino/
Pins GPIO_PINS_v2[] = {
  // top left
  {6, 7},
  {4, 5},
  {2, 3},
  {MCP2(GPB6), MCP2(GPB7)},
  {MCP2(GPB4), MCP2(GPB5)},
  {MCP2(GPB2), MCP2(GPB3)},
  {MCP2(GPB0), MCP2(GPB1)},
  {MCP2(GPA0), MCP2(GPA1)},
  {MCP2(GPA2), MCP2(GPA3)},
  {MCP2(GPA4), MCP2(GPA5)},
  {MCP2(GPA6), MCP2(GPA7)},
  {8, 9},
  // bottom left 
  
  // bottom right
  {13, 12}, 
  {MCP1(GPA6), MCP1(GPA7)},
  {MCP1(GPA4), MCP1(GPA5)},
  {MCP1(GPA2), MCP1(GPA3)},
  {MCP1(GPA0), MCP1(GPA1)},
  {MCP1(GPB6), MCP1(GPB7)},
  {MCP1(GPB4), MCP1(GPB5)},
  {MCP1(GPB2), MCP1(GPB3)},
  {MCP1(GPB0), MCP1(GPB1)},
  {10, 11},
  {A1, A0},
  {A3, A2}
  // top right  - ie Vcc on 74 series
};

#ifndef USE_VI_PINS
// use corrected pinout
#define GPIO_PINS GPIO_PINS_V2
#else
// use original pinout with A6/A7 usage at top of socket
#define GPIO_PINS GPIO_PINS_V1 
#endif

int NUM_PINS() {
  return (sizeof(GPIO_PINS) / sizeof(Pins));
}

// map from test ic pin to GPIO PINS
// icPin is the pin number on chip being tested
// pinCount is the number of pins on the chip being tested 
struct Pins toGPIOPin(int icPin, int pinCount) {
  if (NUM_PINS() != SOCKET_PINS) {
    halt("\nsocket has " + String(SOCKET_PINS) + " pins but cfg has "+ String(NUM_PINS()));
  }

  if (icPin < 0 || icPin >= NUM_PINS()) {
    halt("\nNo test pin configured for IC pin "  + String(icPin));
  }

  // find out which Zif socket pin this is
  int leftSideTestPins = pinCount / 2;
  int socketPin = icPin;
  
  if (icPin < leftSideTestPins)
    socketPin = icPin;
  else {
    int pinsBelowChip = (SOCKET_PINS/2)-leftSideTestPins;
    socketPin = icPin + (2 * pinsBelowChip);
  }
  
  // lookup GPIO pins feeding that zif socket pin
  return GPIO_PINS[socketPin];
}

// given a chip with N pins then how man rows of Zif socket pins are empty
int unusedSlots(int chipPins) {
  int leftSideTestPins = chipPins / 2;
  int pinsBelowChip = (SOCKET_PINS/2)-leftSideTestPins;
  return pinsBelowChip;
}

/* Test a pin's state.
A simple call to digitalRead() isn't reliable because a disconnected (or test is input) pin might return random values due to floating.
Instead, we pull the pin it in a particular direction then checking to see if the pin followed the pull or not.
If the detected value is the opposite of the pull then this signals that the pin is asserting that definite value.
If the pin follws the pull in both directions then the pin cannot be asserting a definite level and must be a disconnected/a high-Z state/an input.

This functions assumes gpioH is already configured as an output and gpioL is already configured as an input
*/
char pinState(int gpioH, int gpioL) {
  
  xDigitalWrite(gpioH, HIGH);
  if (!xDigitalRead(gpioL)) {
    return 'L';
  } else {
    xDigitalWrite(gpioH, LOW);
    if (xDigitalRead(gpioL)) {
      return 'H';
    }
  }

  return 'Z';
}


void xPinMode(uint8_t p, uint8_t d) {
  int pin = -1;
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

  // Serial.println("xPinMode("+  device + " pin " + pin + ", " + String(d) +
  // ")");
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
