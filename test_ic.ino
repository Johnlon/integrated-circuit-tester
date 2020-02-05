#include "tester_wires.h"

struct PinResult {
  boolean isOk;
  char result;
};

/*
   param "scenario" is the test case input and output state definition.
   even a trivial ic will require a sequence of these cases to tests it
   effectively.

   "scenario" is a string containing a sequence of character codes, one for each
   pin of the test IC.

  See the README for a full list of input and result codes.

   returns true if test passes, false otherwise
*/
boolean test_ic(const char*  raw, const char* name) {
  // reset();

  //scenario.replace("/", "");
  char * scenario = strip(raw, '/');

#ifdef USE_VI_PINS  // but in original board - this tweak pushes the test case
  // down the Zif by on position
  scenario = patchScenario(scenario);

#endif

  scenario = fillUnusedPins(scenario);

  int pins = strlen(scenario);

  const char* sep = " : ";

  char testcase[strlen(scenario) + strlen(sep) + strlen(name) +1];
  strcpy(testcase, scenario);
  strcat(testcase, sep);
  strcat(testcase, name);

  int clkPin = -1;

  if (pins % 2 != 0) {
    Serial.println("ERR1");
    Serial.println(scenario);
    halt("Scenario must have even number of pins");
  }

  // Setting Vcc, GND and output pins of the IC under test
  for (int i = 0; i < pins; i++) {
    struct Pins pinPair = toGPIOPin(i, pins);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;

    switch (scenario[i]) {
#ifdef USE_VI_PINS
      case '-':
#endif
      case 'X':
        // dont care - set to weak pull so as not to leave floating
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
        xDigitalWrite(gpioL, LOW);  // low intially, will be toggled later
        xPinMode(gpioH, INPUT);
        break;

      // EXPECTATIONS OF THE OUTPUTS OF THE IC
      case 'L':
        xPinMode(gpioL, INPUT);

        // will be weakly pulled in the opposite direction to expected.
        // if its still the expected value the it is a solid pass and not and
        // not a random floating value
        xPinMode(gpioH, OUTPUT);
        xDigitalWrite(gpioH, HIGH);
        break;
      case 'H':
        xPinMode(gpioL, INPUT);

        // will be weakly pulled in the opposite direction to expected.
        // if its still the expected value the it is a solid pass and not and
        // not a random floating value
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

  // toggle the clock high then low
  if (clkPin != -1) {
    //Serial.println("clocking");
    xDigitalWrite(clkPin, HIGH);
    xDigitalWrite(clkPin, LOW);
  }

  //  Serial.println("Looping");
  boolean pass = true;
  boolean wasTest = false;
  boolean forcePrint = false;
  String result = "";

  // Reading Outputs from the IC under test
  for (int i = 0; i < pins; i++) {
    Pins pinPair = toGPIOPin(i, pins);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;

    switch (scenario[i]) {
      case 'H': {
          wasTest = true;
          PinResult r = expectPin('H', gpioH, gpioL);
          if (!r.isOk) pass = false;
          result += r.result;
          break;
        }
      case 'L': {
          wasTest = true;
          PinResult r = expectPin('L', gpioH, gpioL);
          if (!r.isOk) pass = false;
          result += r.result;
          break;

        }
      case 'u':
      case 'Z': {
          wasTest = true;
          PinResult r = expectPin('Z', gpioH, gpioL);
          if (!r.isOk) pass = false;
          result += r.result;
          break;
        }

      case '?':
        forcePrint = true;
        result = +xDigitalRead(gpioL) ? "1" : "0";
        break;

#ifdef USE_VI_PINS
      case '-':
        result += '-';
        break;
#endif

      default:
        // pin is an input or a don't care so display as underscore
        result += '_';
    }
  }

  if (pass) {
    Serial.print("PASS  : ");
  } else {
    Serial.print("FAIL  : ");
  }
  Serial.println(testcase);

  Serial.println("Result: " + result);

  return pass;
}


const struct PinResult expectPin(char mode, int gpioH, int gpioL) {
  char r = pinState(gpioH, gpioL);
  if ( r == mode) return {true, '.'};
  return {false, r};
}

boolean test_ic(const char* scenario) {
  test_ic(scenario, "");
}

/* read from serial io */
int kbRead() {
  // send data only when you receive data:
  while (Serial.available() == 0) {
  }

  return Serial.read();
}

void reset() {
  Serial.println("---");

  for (int i = 0; i < SOCKET_PINS; i++) {
    Pins pinPair = toGPIOPin(i, SOCKET_PINS);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;

    // force to a definitive value - ie low - removing any stray charge on pin
    xPinMode(gpioL, OUTPUT);
    xDigitalWrite(gpioL, LOW);

    xPinMode(gpioH, OUTPUT);
    xDigitalWrite(gpioH, LOW);

    // disconnect
    xPinMode(gpioL, INPUT);
    xPinMode(gpioH, INPUT);
  }
}

char* strip(const char * str, char remove) {
  static char stripped[SOCKET_PINS + 1];
  int len = strlen(str);

  int to = 0;
  for (int from = 0; from < len; from++) {
    if (str[from] != remove) {
      stripped[to++] = str[from];
    }
  }
  stripped[to] = '\0';
  return stripped;
}

// hardware design error - A6/A7 dont work as outputs so shift the scenario down
// one set of pins. do not use the top row in the zip socket

char* patchScenario(const char* sin) {
  static char patchedScenario[SOCKET_PINS + 1];
  if (strlen(sin) > (SOCKET_PINS - 2)) {
    error(sin);
    halt("can't patch scenario - too long");
  }

  sprintf(patchedScenario, "-%s-", sin);
  return patchedScenario;
}



char* fillUnusedPins(const char* test) {
  static char filledUnusedPins[SOCKET_PINS + 1];

//Serial.println("FILLING " + test);
  int len = strlen(test);

  int unusedPins = 2 * unusedSlots(len);

  char fill[unusedPins + 1];

  int i = 0;
  while (i < unusedPins) {
    fill[i++] = 'u';
  }
  fill[i] = '\0';

  char left[len + 1];
  strcpy(left, test);
  left[len / 2] = '\0';

  char right[len + 1];
  strcpy(right, test + (len / 2));
  right[len / 2] = '\0';

  // Serial.println("IN    "+ String(test));
  // Serial.println("LEFT  "+ String(left));
  // Serial.println("RIGHT "+ String(right));
  // Serial.println("FILL  "+ String(fill));

  filledUnusedPins[0] = '\0';
  strcpy(filledUnusedPins , left);
  strcat(filledUnusedPins , fill);
  strcat(filledUnusedPins , right);

  return filledUnusedPins;
}
