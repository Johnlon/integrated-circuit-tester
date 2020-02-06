#include "test_ic.h"
#include "chipsDatabase.h"
#include "myChipsDatabase.h"
#include "io.h"

void setup() {
  Serial.begin(9600);
  mcp_setup();

  interactive();
  
  //emptySocket();
  //identify();
  //barLedTestPattern();

  reset();
  delay(1000000);
}

void usage() {
  println(INFO, "perform test       >  t:testpattern[:description]");
  println(INFO, "repeat last test   >  t");
  println(INFO, "read all pins      >  ?");      
  println(INFO, "repeat last action >  /");      
}

void interactive() {
  println(INFO, "INTERACTIVE MODE:");
  usage();
  
  char op;
  char lastOp=0;
  do {
    static char data[100+1] = "";
    readline(data, 100);
 
    static char lastdata[100+1] = "";
    op = data[0];
    if (op == '/') {
      op = lastOp;
      strcpy(data, lastdata);
    } 
    
    lastOp = op;
    strcpy(lastdata, data);
    
    static char tokenise[100+1] = ""; // for tokenisation
    strcpy(tokenise, data);
    char *token = strtok(tokenise, ":");
    
    switch(op) {
      case 'h': {
        usage();
        break;
      }
      case 't': {
        static char prevTestcase[100+1] = "";
        char* testcase = strtok(NULL, ":");
        if (testcase == NULL) {
          if (prevTestcase[0]==0) {
            println(ERROR, "missing testcase argument in '", data, "'");
            break;
          } else
            testcase = prevTestcase;
        } else {
          strcpy(prevTestcase, testcase);
        }
        char* desc = strtok(NULL, ":");
        if (desc == NULL) desc="";
        test_ic(testcase, desc);
      }
      break;
      
      case '?': {
        char buf[SOCKET_PINS-2+1];
        fill(buf, SOCKET_PINS-2+1,'?');
        test_ic(buf);
      }
      break;

    }
    
  
  } while (op != 'q');

  println(HALT, "quit");
}

void identify() {
  // only include the chips you want to include in the scan - reduces the
  // program storage space needed
  Chip chips[] = {
    //CHIP_EMPTY,
    //CHIP_c74245, 
    //CHIP_74138
    CHIP_x74173
   };

  
  // Work in progress - chip detection - test all scenarios
  println(INFO, "\n=======================");
  println(INFO, "IDENTIFYING ... ");

  for (const Chip& chip : chips) {
    reset();

    println(INFO, "\nTesting: ", chip.name, " : " , chip.description);

    const Scenario* testcase = chip.scenarios;
    bool allok = true;
    while (testcase != NULL) {

      bool ok = test_ic(testcase->test, testcase->name);
      if (!ok)
        allok = false;
      testcase = testcase->next;
    }

    if (allok)
      println(INFO, "matches ");
    else
      println(INFO, "not ");
    
    println(INFO, chip.name);
  }

  reset();
}

void emptySocket() {
  // 11 pin each side socket empty self test - 11 because orig hw has bug on top
  test_ic("ZZZZZZZZZZZ/ZZZZZZZZZZZ", "Empty socket self test");
}

void decay() {
  println(INFO, "Testcase :  1111111111111111111111");
  test_ic("1111111111111111111111");            // capacitance test
  test_ic("??????????????????????", "0 secs");  // capacitance test
  delay(1000);
  test_ic("??????????????????????", "1 sec");  // capacitance test
  delay(1000);
  test_ic("??????????????????????", "2 secs");  // capacitance test
  delay(4000);
  test_ic("??????????????????????", "6 secs");  // capacitance test
  delay(4000);
  test_ic("??????????????????????", "10 secs");  // capacitance test
  delay(5000);
  test_ic("??????????????????????", "15 secs");  // capacitance test
  delay(5000);
  test_ic("??????????????????????", "20 secs");  // capacitance test
  delay(5000);
  test_ic("??????????????????????", "25 secs");  // capacitance test
}

void barLedTestPattern() {
  int i = 10;
  while (i-- > 0) {
    
    int i = 5;
    int d1 = 200;
    while (i-- > 0) {
      test_ic("11111111111/00000000000", "on");
      delay(d1);
      test_ic("00000000000/00000000000", "of");
      delay(d1);
    }
    
    int j = 16;
    int d2 = 20;
    while (j-->0) {
      test_ic("10001000100/00000000000", "walk");
      delay(d2);
      test_ic("01000100010/00000000000", "walk");
      delay(d2);
      test_ic("00100010001/00000000000", "walk");
      delay(d2);
      test_ic("00010001000/00000000000", "walk");
      delay(d2);
    }
  }
}
void loop() {}
