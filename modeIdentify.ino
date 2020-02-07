#include "strings.h"

#include "myChipsDatabase.h"

const char string_0[] PROGMEM = "String 0";

const char* const chips[] PROGMEM = {
  CHIP_x74245, 
  CHIP_74138,
  CHIP_x74173,
  CHIP_EMPTY
};

void identify() {
  // only include the chips you want to include in the scan - reduces the
  // program storage space n

  INFOLN(F("IDENTIFYING ... "));

  for (int i=0; i < sizeof(chips)/sizeof(const char* const); i++) {

    char chipBuf[1000+1];
    strncpy_P(chipBuf, (char*)pgm_read_dword(&(chips[i])), 1000);
  
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

        INFOLN(F("Testing"));

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
