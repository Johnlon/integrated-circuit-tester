#include "error.h"

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

#define MCP1(X) 100+X
#define MCP2(X) 200+X


/* pin out depends on your test circuit and how you've wired it together.
  this scheme defines a mapping between the pins of the chip under test and a pair of GPIO pins of the arduino.
  Gconfigures the pair of GPIO pins that will interact with pin 1 of the IC under test.

  toGPIOPin() returns the GPIO pin that maps to the given IC pin.

  MCP23017 max io current is 25ma so the gpioL resistance could be as low as 200 ohm assuming the high / low output differential is 5v.
  MCP23017 datasheet says High out is Vdd-0.7 (ie 4.3)
  MCP23017 datasheet says Low out is 0.6v
  So the diff is 3.7v.
  So the most we can supply to Vcc of the test chip is 3.7v  
  What low value resistor to use? 3.7v/25ma = 148ohm


  Device Class Vcc levels
  =======================
  
  HC logic chips data sheets say VCC may be as low as 2v typially
  HCT data sheets quote 4.5 as lowest Vcc but this is the min in order to maintail TTL compatibility. In reality HCT will run fine at lower Vcc.

  http://www.ti.com/lit/an/sdya009c/sdya009c.pdf - Texas Instruments - Designing With Logic
  2.2 Behavior With Low Supply Voltages
  "TTL devices attain stability with a supply voltage of about 3.5 V, and are fully functional at a typical voltage of 4 V"

  */

struct Pins {
  int gpioL; // low resistance - used as gpio output to drive VCC/GNC and also logic inputs on the test IC, alternatively used a gpio input during probing for Z outputs
  int gpioH; // high resistance - used as a gpio output to apply a weak pull up or down to the test ic during high-Z tests; the rest of the the time set as a gpio input and ignored (no-op)
};

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

// only for testing with my bad PCB where A6/A7 doesn't work
#define USE_VI_PINS

#ifndef USE_VI_PINS
// use corrected pinout
#define GPIO_PINS GPIO_PINS_V2
#else
// use original pinout with A6/A7 usage at top of socket
#define GPIO_PINS GPIO_PINS_V1 
#endif

int NUM_PINS = (sizeof(GPIO_PINS) / sizeof(Pins));

#define SOCKET_PINS 24 // bottom 4 pins of 28 holes are not connected

// map from IC pin to arduino PINS
Pins toGPIOPin(int icPin, int pinCount) {
  if (NUM_PINS != SOCKET_PINS) {
    halt("\nsocket has " + String(SOCKET_PINS) + " pins but cfg has "+ String(NUM_PINS));
  }

  if (icPin < 0 || icPin >= NUM_PINS) {
    halt("\nNo test pin configured for IC pin "  + String(icPin));
  }

  int leftSideTestPins = pinCount / 2;
  int socketPin = icPin;
  
  if (icPin < leftSideTestPins)
    socketPin = icPin;
  else 
    socketPin = icPin + (2 * ((SOCKET_PINS/2)-leftSideTestPins));

  return GPIO_PINS[socketPin];
}
