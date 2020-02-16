#include "strings.h"
#include "chipsDatabase.h"
#include "myChipsDatabase.h"
#include "tester_wires.h"

const char* const chips[] PROGMEM = {
  CHIP_x74245, 
  CHIP_74138,
  CHIP_x74173,
  CHIP_EMPTY,
  CHIP_7400,
 CHIP_7401,
 CHIP_7402,
 CHIP_7403,
 CHIP_7404,
 CHIP_7405,
 CHIP_7406,
 CHIP_7407,
 CHIP_7408,
 CHIP_7409,
 CHIP_7410,
 CHIP_74107,
 CHIP_74109,
 CHIP_7411,
 CHIP_74112,
 CHIP_74113,
 CHIP_7412,
 CHIP_74123,
 CHIP_74125,
 CHIP_74126,
 CHIP_7413,
 CHIP_74132,
 CHIP_74133,
 CHIP_74136,
 CHIP_74137,
 CHIP_74138,
 CHIP_74139,
 CHIP_7414,
 CHIP_74140,
 CHIP_74147,
 CHIP_74148,
 CHIP_7415,
 CHIP_74151,
 CHIP_74153,
 CHIP_74157,
 CHIP_74158,
 CHIP_7416,
 CHIP_74160,
 CHIP_74161,
 CHIP_74162,
 CHIP_74163,
 CHIP_74164,
 CHIP_74165,
 CHIP_74166,
 CHIP_7417,
 CHIP_74173,
 CHIP_74174,
 CHIP_74175,
 CHIP_7418,
 CHIP_74182,
 CHIP_74190,
 CHIP_74191,
 CHIP_74192,
 CHIP_74193,
 CHIP_74194,
 CHIP_74195,
 CHIP_7420,
 CHIP_7421,
 CHIP_7422,
 CHIP_74237,
 CHIP_74242,
 CHIP_74243,
 CHIP_7425,
 CHIP_74251,
 CHIP_74253,
 CHIP_74257,
 CHIP_74258,
 CHIP_74259,
 CHIP_7426,
 CHIP_74260,
 CHIP_74266,
 CHIP_7427,
 CHIP_7428,
 CHIP_74280,
 CHIP_74283,
 CHIP_74292,
 CHIP_74293,
 CHIP_74294,
 CHIP_74298,
 CHIP_7430,
 CHIP_7432,
 CHIP_74365,
 CHIP_74366,
 CHIP_74367,
 CHIP_74368,
 CHIP_7437,
 CHIP_74375,
 CHIP_7438,
 CHIP_74386,
 CHIP_74390,
 CHIP_74393,
 CHIP_7440,
 CHIP_7442,
 CHIP_7446,
 CHIP_7447,
 CHIP_7450,
 CHIP_7451,
 CHIP_7455,
 CHIP_7458,
 CHIP_74589,
 CHIP_74595,
 CHIP_74597,
 CHIP_7460,
 CHIP_7461,
 CHIP_7462,
 CHIP_7465,
 CHIP_7474,
 CHIP_7485,
 CHIP_7486,
};


void identify(boolean verbose, boolean skipOnFirstFail, boolean stopOnFirstMatch) {
  // only include the chips you want to include in the scan - reduces the
  // program storage space n

  int matches = 0;
  int count = sizeof(chips)/sizeof(const char* const);

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
              INFOLN(F("no more test cases, "), c, F(" executed"));
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
