#include "strings.h"
#include "myChipsDatabase.h"
#include "tester_wires.h"

void identify(boolean verbose, boolean skipOnFirstFail, boolean stopOnFirstMatch) {
  // only include the chips you want to include in the scan - reduces the
  // program storage space n

  int matches = 0;
  int count = sizeof(chips)/sizeof(const char* const);

  INFOLN(F("IDENTIFYING (db size "), count, F(")... "));

  for (int i=0; i < count; i++) {

    if (verbose) {
      INFOLN(F("--------------------------------------------------------------"));
    }
  
    // two levels of indirection - firsly the array is PROGMEM so we have to grab the address of the array element from progmem.
    // - secondly inside tokenise() we have to walk the PROGMEM string that that address points at
    FSH chipDef= (FSH)pgm_read_word_near(&chips[i]);

    // read fields
    char name[6];
    int sz = tokenise(chipDef, ':', name, sizeof(name));
    if (sz == -1) {
        ERRORLN(F("missing chip name"));
        break;
    }
    pad(name, sizeof(name), 32);
    
    char desc[100];
    sz = tokenise(NULL, ':', desc, sizeof(desc));
    if (sz == -1) {
        ERRORLN(F("missing chip description"), " for ", name);
        break;
    }
    
    INFOLN(name, " : ", desc)
   
    bool allok = true;
    int c = 0;
    reset();
   
    while (true) {
        char test[2*SOCKET_PINS]; // space for a stupid number of separators
        sz = tokenise(NULL, ':', test, sizeof(test));
        if (sz == -1) {
            if (verbose) {
              INFOLN(F("no more test cases, "), itoa(c), F(" executed"));
            }
            break;
        }

        char testdesc[100];
        sz = tokenise(NULL, ':', testdesc, sizeof(testdesc));
        if (sz == -1) {
            ERRORLN(F("missing test case description"));
            break;
        } 

        bool ok = test_ic(test, testdesc, verbose);
        if (!ok) {
          allok = false;
          if (skipOnFirstFail) break;
        }
        c++;
    }

    if (allok) {
      MATCHLN(F("matches: "), name)
      matches ++;
      if (stopOnFirstMatch) return;
    } else {
      if (verbose) {
        INFOLN(F("no match: "), name)
      }
    }
  }

  INFOLN(F("found "), matches, F(" matches")); 

  reset();
}
