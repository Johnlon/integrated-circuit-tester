#ifndef TESTER_WIRES
#define TESTER_WIRES

// Only for use when working with my original V1 PCB where A6/A7 we connected to the first ZIF row - row 1 doesn't work in that case.
// Comment out otherwise
#define USE_VI_PINS

struct Pins {
  int gpioL; // low resistance - used as gpio output to drive VCC/GNC and also logic inputs on the test IC, alternatively used a gpio input during probing for Z outputs
  int gpioH; // high resistance - used as a gpio output to apply a weak pull up or down to the test ic during high-Z tests; the rest of the the time set as a gpio input and ignored (no-op)
};


// The PCB has 28 holes but the bottom 4 pins are not connected and are just drill holes.
#define SOCKET_PINS 24

#endif
