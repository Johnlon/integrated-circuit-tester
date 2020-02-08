#include "tester_wires.h"

void usage() {
  INFOLN("perform test       >  t:testpattern[:description]");
  INFOLN("repeat last test   >  t");
  INFOLN("read all pins      >  ?");      
  INFOLN("repeat last action >  /");      
}

void interactive() {
  INFOLN("INTERACTIVE MODE:");
  usage();
  
  char op;
  char lastOp=0;
  const int MaxLen = 100;
  do {
    static char data[MaxLen +1] = "";
    readline(data, MaxLen );
 
    static char lastdata[MaxLen +1] = "";
    op = data[0];
    if (op == '/') {
      op = lastOp;
      strcpy(data, lastdata);
    } 
    
    lastOp = op;
    strcpy(lastdata, data);
    
    static char tokenise[MaxLen +1] = ""; // for tokenisation
    strcpy(tokenise, data);
    char *token = strtok(tokenise, ":");
    
    switch(op) {
      case 'h': {
        usage();
        break;
      }
      case 't': {
        static char prevTestcase[MaxLen+1] = "";
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
      
      case '?': {
        // TODO : use #ifdef here to use -2 only on the old hardware setting
        char buf[SOCKET_PINS-2+1];
        fill(buf, SOCKET_PINS-2+1,'?');
        test_ic(buf);
      }
      break;

    }
    
  } while (op != 'q');

  HALTLN(F("quit"));
}
