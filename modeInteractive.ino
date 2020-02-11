#include "tester_wires.h"

void usage() {
  INFOLN(F("perform test       >  t:testpattern[:description]"));
  INFOLN(F("repeat last test   >  t"));
  INFOLN(F("test all pins      >  ?"));      
  INFOLN(F("sample all pins    >  s"));      
  INFOLN(F("set all pins to 1  >  1"));      
  INFOLN(F("set all pins to 0  >  0"));
  INFOLN(F("identify chip      >  i"));      
  INFOLN(F("repeat last action >  /"));      
}

void interactive() {
  INFOLN("INTERACTIVE MODE:");
  
  usage();
      
  char op;
  char lastOp=0;
  const int MaxLen = 100;
  char prevTestcase[MaxLen+1] = "";
  char lastdata[MaxLen +1] = "";
        
  do {
    char data[MaxLen +1] = "";
    readline(data, MaxLen );
 
    op = data[0];
    if (op == '/') {
      op = lastOp;
      strcpy(data, lastdata);
    } 
    
    lastOp = op;
    strcpy(lastdata, data);
    
    char tokenise[MaxLen +1] = ""; // for tokenisation
    strcpy(tokenise, data);
    char *token = strtok(tokenise, ":");
    
    switch(op) {
      case 'h': {
        usage();
        break;
      }
      case 't': {
        char* testcase = strtok(NULL, ":");
        if (testcase == NULL) {
          if (prevTestcase[0]==0) {
            ERRORLN(F("missing testcase argument in '"), data, "'");
            break;
          } else
            testcase = prevTestcase;
        } else {
          strcpy(prevTestcase, testcase);
        }
        char* desc = strtok(NULL, ":");
        if (desc == NULL) desc=(char*)"";
        
        test_ic(testcase, desc);
      }
      break;
      
      case 'i': {
        identify(false, true  );
      }
      break;

      case '?': {
#ifdef USE_VI_PINS  
        // TODO : use #ifdef here to use -2 only on the old hardware setting
        char buf[SOCKET_PINS-2+1];
#else
        char buf[SOCKET_PINS+1];
#endif
        fill(buf, sizeof(buf), '?');
        test_ic(buf, "status of all pins");
      }
      break;

    case 's': {
#ifdef USE_VI_PINS  
        // TODO : use #ifdef here to use -2 only on the old hardware setting
        char buf[SOCKET_PINS-2+1];
#else
        char buf[SOCKET_PINS+1];
#endif
        fill(buf, sizeof(buf), 'S');
        test_ic(buf, "sample all pins");
      }
      break;

    case '1': {
#ifdef USE_VI_PINS  
        // TODO : use #ifdef here to use -2 only on the old hardware setting
        char buf[SOCKET_PINS-2+1];
#else
        char buf[SOCKET_PINS+1];
#endif
        fill(buf, sizeof(buf), '1');
        test_ic(buf, "all pins 1");
      }
      break;

    case '0': {
#ifdef USE_VI_PINS  
        // TODO : use #ifdef here to use -2 only on the old hardware setting
        char buf[SOCKET_PINS-2+1];
#else
        char buf[SOCKET_PINS+1];
#endif
        fill(buf, sizeof(buf), '0');
        test_ic(buf, "all pins 0");
      }
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
