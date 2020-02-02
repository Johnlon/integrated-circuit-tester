#ifndef TESTER_WIRES
#define TESTER_WIRES

// only for use working with my bad V1 PCB where A6/A7 doesn't work
#define USE_VI_PINS

struct Pins {
  int gpioL; // low resistance - used as gpio output to drive VCC/GNC and also logic inputs on the test IC, alternatively used a gpio input during probing for Z outputs
  int gpioH; // high resistance - used as a gpio output to apply a weak pull up or down to the test ic during high-Z tests; the rest of the the time set as a gpio input and ignored (no-op)
};

#endif