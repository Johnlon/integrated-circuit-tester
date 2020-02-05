#ifndef _TEST_IC_
#define  _TEST_IC_

#include "tester_wires.h"

struct Scenario {
  const char* test;
  const char* name;
  Scenario* next;

  Scenario(const char* test,const char* tname)
      : next(NULL), test(test), name(tname) {}
};

struct Chip {
  const char* name;
  const char* description;

  Scenario* scenarios;

  Chip(const char* name, const char* desc)
      : name(name), description(desc), scenarios(NULL) {}

  Chip& scenario(const char* test) {
    return scenario(test, "");
  }

  Chip& scenario(const char* test, const char* tname) {
    Scenario* s = new Scenario(test, tname);

    // add to end of list
    Scenario* last = this->scenarios;
    if (NULL == last) {
      this->scenarios = s;
    } else {
      while (last->next != NULL) {
        last = last->next;
      }
      last->next = s;
    }

    return *this;
  }
};

Chip chip(const char* name, const char* desc) {
  return Chip(name,desc);
}

#endif
