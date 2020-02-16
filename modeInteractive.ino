#include "tester_wires.h"

void tUsage() {
  INFOLN(F("usage:"));
  INFOLN(F("  t:testpattern[:desc] - perform test using given pattern"));
}

void usage() {
  tUsage();
  INFOLN(F("  ? - test all pins - uses the pullup/down test"));
  INFOLN(F("  s - sample all pins - just sample the value of the pin"));
  INFOLN(F("  1 - set all pins to 1"));
  INFOLN(F("  0 - set all pins to 0"));
  INFOLN(F("  i - identify chip"));
  INFOLN(F("  / - repeat last action"));
  INFOLN(F("  l - led array test pattern"));
  INFOLN(F("  d - decay test for capacitance on pins - leave socket empty"));
}

void interactive() {
  const int INPUT_MAX_LEN = 100;
  
  INFOLN(F("INTERACTIVE MODE:"));
  usage();

  char op;
  char prevCommand[INPUT_MAX_LEN + 1] = "";

  do {
    char command[INPUT_MAX_LEN + 1] = "";
    readline(command, INPUT_MAX_LEN);

    op = command[0];

    // if this command is / then just repeat whatever the previous op was
    if (op == '/') {
      strcpy(command, prevCommand);
      op = command[0];
    }

    // keep a copy of this operation in case the next operation is a command to repeat this one
    strcpy(prevCommand, command);

    // start parsing the command - make a 
    char* token = strtok(command, ":");

    switch (op) {
      case 'h': {
        usage();
        break;
      }
      
      case 't': {
        char* testcase = strtok(NULL, ":");
        if (testcase == NULL) {
            ERRORLN(F("missing testcase"));
            tUsage();
            break;
        } 
        
        char* desc = strtok(NULL, ":");
        if (desc == NULL) desc = (char*)"";

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
