#include "strings.h"


const char XCHIP_x74173[] PROGMEM = "74173:4-bit 3-state D flip-flop with reset, dual clock enables and dual output enables" 
                  ":10ZZZZCG/0000001V:OE1 disabled" \
                  ":01ZZZZCG/0000001V:OE2 disabled" \
                  ":11ZZZZCG/0000001V:OE1 & OE2 disabled" \
                  ":00LLLLCG/0000001V:Clock all 0 into reg" \
                  ":00LLLLCG/0011111V:E1 & E2 enabled but MR asserted so will not load (holds value)" \
                  ":00LLLLCG/1111110V:E1 & E2 disabled so will not load" \
                  ":00LLLLCG/0111110V:E2 disabled so will not load"  \
                  ":00LLLLCG/1011110V:E1 disabled so will not load" \
                  ":00HHHHCG/0011110V:Load D to Q" \
                  ":00HHHHCG/1011110V:E1 disabled so will not load"; 

const char string_0[] PROGMEM = "String 0";

const char* const chips[] PROGMEM = {
  //CHIP_EMPTY,
  //CHIP_x74245, 
  //CHIP_74138,
  XCHIP_x74173
  //string_0
};

void identify() {
  // only include the chips you want to include in the scan - reduces the
  // program storage space n

  
  INFOLN(F("\n======================="));
  INFOLN(F("IDENTIFYING ... "));
  delay(1000);
  
  for (const char* const fchip : chips) {

    char chipBuf[1000+1];
    strncpy_P(chipBuf, (char*)pgm_read_dword(&(chips[0])), 1000);
  
    char *name = strtok(chipBuf, ":");
    if (name == NULL) {
        ERRORLN(F("missing chip name"));
        break;
    }

    char *desc = strtok(NULL, ":");
    if (desc == NULL) {
        ERRORLN(F("missing chip description"));
        break;
    }

    INFOLN(F("Testing: "), name, F(" : ") , desc);

    bool allok = true;
    int c = 0;
    reset();
   
    while (true) {

        char *test = strtok(NULL, ":");
        if (test == NULL) {
            INFOLN(F("no more test cases, "), itoa(c), F(" executed"));
            break;
        }

        char *testdesc = strtok(NULL, ":");
        if (testdesc == NULL) {
            ERRORLN(F("missing test case description"));
            break;
        } 

        bool ok = test_ic(test, testdesc);
        if (!ok)
            allok = false;
        c++;
    }

    if (allok) 
      INFOLN(F("matches "), name)
    else 
      INFOLN(F("not "), name)
  }

  reset();
}
