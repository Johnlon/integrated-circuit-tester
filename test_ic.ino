#include "tester_wires.h"
#include "io.h"

struct PinResult {
  boolean isOk;
  char result;
};


boolean test_ic(const __FlashStringHelper*  raw, const __FlashStringHelper* desc) {
  char buf1[100+1];
  char buf2[100+1];
  strncpy_P(buf1, (char*)raw, 100);
  strncpy_P(buf2, (char*)desc, 100);
  
  return test_ic(buf1, buf2);
}

boolean test_ic(const char*  raw, const char* name) {
  return test_ic(raw, name, true);
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
boolean test_ic(const char*  raw, const char* name, bool verbose) {
  if (strlen(raw) > SOCKET_PINS_VALID) {
    ERRORLN(F("too many pins in test pattern, max expected "), SOCKET_PINS_VALID, F(", but got "), strlen(raw))//, F(" in '"), raw, F("'"))
    return false;
  }

  char * scenario = strip(raw, '/');
  if (scenario == NULL) return false;

  scenario = fillUnusedPins(scenario);
  if (scenario == NULL) return false;

#ifdef USE_VI_PINS  
  // use with in original board - this tweak pushes the test case 
  // down the Zif by one position to avoid those pins
  scenario = patchScenario(scenario);
  if (scenario == NULL) return false;
#endif

  int pins = strlen(scenario);

  if (pins != SOCKET_PINS) {
      ERRORLN(scenario, F(" : test case length wrong, need "), SOCKET_PINS, F(", got "), pins);
      return false;
  }

  const char* sep = " : ";

  int clkPin = -1;

  // Setting Vcc, GND and output pins of the IC under test
  for (int i = 0; i < pins; i++) {
    struct Pins pinPair = toGPIOPin(i, pins);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;

    char code = scenario[i];
    
    switch (code) {
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
      case '?':
        xPinMode(gpioL, INPUT);
        xPinMode(gpioH, OUTPUT);
        break;

      case 'S':
        xPinMode(gpioL, INPUT);
        xPinMode(gpioH, INPUT);
        break;

      default:
        char location[SOCKET_PINS+1] = "";
        fill(location, SOCKET_PINS, ' ');
        location[i] = '^';
        
        ERRORLN(scenario, F(": Illegal code '"), code, F("' at pos "), (i+1));
        ERRORLN(location);
        return false;
    }
  }

  // toggle the clock high then low
  if (clkPin != -1) {
    //println("clocking");
    xDigitalWrite(clkPin, HIGH);
    xDigitalWrite(clkPin, LOW);
  }

  //  println("Looping");
  boolean pass = true;
  char result[SOCKET_PINS+1] = "";

  // Reading Outputs from the IC under test
  for (int i = 0; i < pins; i++) {
    Pins pinPair = toGPIOPin(i, pins);
    int gpioL = pinPair.gpioL;
    int gpioH = pinPair.gpioH;
    
    switch (scenario[i]) {
      case 'H': {
          PinResult r = expectPin('H', gpioH, gpioL);
          if (!r.isOk) pass = false;
          result[i] = r.result;
          break;
        }
      case 'L': {
          PinResult r = expectPin('L', gpioH, gpioL);
          if (!r.isOk) pass = false;
          result[i] = r.result;
          break;

        }
      case 'u':
      case 'Z': {
          PinResult r = expectPin('Z', gpioH, gpioL);
          if (!r.isOk) pass = false;
          result[i] = r.result;
          break;
        }

      case '?':
        result[i] = pinState(gpioH, gpioL);;
        break;

      case 'S':
        result[i] = xDigitalRead(gpioL)? '1': '0';
        break;

#ifdef USE_VI_PINS
      case '-':
        result[i] = '-';
        break;
#endif

      default:
        // pin is an input or a don't care so display as underscore
        result[i] = '_';
    }
  }

  if (verbose) {
    if (pass) {
      PASSLN(scenario, sep, name);
    } else {
      FAILLN(scenario, sep, name);
    }
    INFOLN(result);
  }
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

void testX(char x, const char* name) {
  // TODO : use #ifdef here to use -2 only on the old hardware setting
  char buf[SOCKET_PINS_VALID+ 1];

  fill(buf, sizeof(buf), x);
  test_ic(buf, name);
}

void reset() {
  //INFOLN(F("RESET"));

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

// strips the given char from the string
char* strip(const char * str, char remove) {
  static char stripped[SOCKET_PINS + 1];
  int len = strlen(str);
  
  int to = 0;
  for (int from = 0; from < len; from++) {
    if (str[from] != remove) {
      stripped[to++] = str[from];
    }

    if (to > SOCKET_PINS) {
      ERRORLN(str);
      ERRORLN(F("can't strip special chars - too long, max allowed is "), SOCKET_PINS);
      return NULL;
    }

  }
  stripped[to] = '\0';
  return stripped;
}

// hardware design error - A6/A7 dont work as outputs so shift the scenario down
// one set of pins. do not use the top row in the zip socket

#ifdef USE_VI_PINS  
char* patchScenario(const char* sin) {
  int len = strlen(sin);
  
  if (strlen(sin) != SOCKET_PINS_VALID) {
    ERRORLN(sin);
    ERRORLN(F("can't patch scenario - too long, length is "), len, F(" but only "), SOCKET_PINS_VALID, F(" allowed"));
    return NULL;
  }
 
  static char patchedScenario[SOCKET_PINS + 1];
  strcpy(patchedScenario, "-");
  strcat(patchedScenario, sin);
  strcat(patchedScenario, "-");
  return patchedScenario;
}
#endif  


char* fillUnusedPins(const char* test) {
  int len = strlen(test);

  int unusedPins = SOCKET_PINS_VALID -  len;

  static char filledUnusedPins[SOCKET_PINS + 1];
  filledUnusedPins[0] = 0;

  strcpy(filledUnusedPins, test);
  int leftLen = ((len+1) / 2);
  filledUnusedPins[leftLen] = '\0';

  fill(filledUnusedPins+leftLen, unusedPins+1, 'u');
  strcat(filledUnusedPins, test+leftLen);
  
  if (strlen(filledUnusedPins) != SOCKET_PINS_VALID) {
    HALTLN(F("SW ERROR WRONG LEN, expected "), SOCKET_PINS_VALID, F(" but got "), strlen(filledUnusedPins), F(" in '"), filledUnusedPins, F("'"))
  }

  return filledUnusedPins;
}
