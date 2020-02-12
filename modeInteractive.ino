#include "tester_wires.h"

void usage() {
  // const __FlashStringHelper * GAP  = F(" - ");
  INFOLN(F("t:testpattern[:desc] - perform test using given pattern"));
  INFOLN(F("t - repeat last test"));
  INFOLN(F("? - test all pins"));
  INFOLN(F("s - sample all pins"));
  INFOLN(F("1 - set all pins to 1"));
  INFOLN(F("0 - set all pins to 0"));
  INFOLN(F("i - identify chip"));
  INFOLN(F("/ - repeat last action"));
  INFOLN(F("l - led array test pattern"));
}

void testX(char x, const char* name) {
#ifdef USE_VI_PINS
  // TODO : use #ifdef here to use -2 only on the old hardware setting
  char buf[SOCKET_PINS - 2 + 1];
#else
  char buf[SOCKET_PINS + 1];
#endif
  fill(buf, sizeof(buf), x);
  test_ic(buf, name);
}

void interactive() {
  INFOLN(F("INTERACTIVE MODE:"));
  usage();

  char op;
  char lastOp = 0;
  const int MaxLen = 100;
  char prevTestcase[MaxLen + 1] = "";
  char lastdata[MaxLen + 1] = "";

  do {
    char data[MaxLen + 1] = "";
    readline(data, MaxLen);

    op = data[0];
    if (op == '/') {
      op = lastOp;
      strcpy(data, lastdata);
    }

    lastOp = op;
    strcpy(lastdata, data);

    char tokenise[MaxLen + 1] = "";  // for tokenisation
    strcpy(tokenise, data);
    char* token = strtok(tokenise, ":");

    switch (op) {
      case 'h': {
        usage();
        break;
      }
      case 't': {
        char* testcase = strtok(NULL, ":");
        if (testcase == NULL) {
          if (prevTestcase[0] == 0) {
            ERRORLN(F("missing testcase argument in '"), data, "'");
            break;
          } else
            testcase = prevTestcase;
        } else {
          strcpy(prevTestcase, testcase);
        }
        char* desc = strtok(NULL, ":");
        if (desc == NULL)
          desc = (char*)"";

        test_ic(testcase, desc);
      } break;

      case 'i':
        identify(false, true, false);
        break;

      case 'l':
        barLedTestPattern();
        break;

      case 'd':
        decay();
        break;

      case '?':
        testX('?', "status of all pins");
        break;
        
      case 's':
        testX('S', "sample all pins");
        break;

      case '1':
        testX('1', "all pins 1");
        break;

      case '0':
        testX('0', "all pins 0");
        break;

      default: {
        ERRORLN("invalid command '", op, "'")
        usage();
        break;
      }
    }

  } while (op != 'q');

  HALTLN(F("quit"));
}
