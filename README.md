Integrated Circuit Tester
=========================

This software accompanies a hardware design for an integrated circuit tester.

Hardware design, pcb and Principal of Operation on EasyEda : https://easyeda.com/john.lonergan.sharing/integrated-circuit-tester


Motivation
------

There were various motivations for building this:
- To test a bunch of chips I bought from eBay and AliExpress
- To allow me to check my understanding of the functioning of certain chips. By writing a sequence of test scenarios and then checking that my understanding is correct.
- To learn something about Arduinos
- To learn about EasyEda
- To have some fun getting a PCB made up (not having to etch it myself like the old days) 
- Nostalgia - I built something with a similar function at university in 1984 but it was a much bigger physically and hooked up to a BBC PC.

Summary
------

This device is intended to test 74** series chips but will work equally well with 4000 series CMOS or other 5v chips that don't need much supply current.

This device can also be used to test drive an LED array or 7 segment display, with visual inspection to check the device's behaviour. Note that the LED must be able to tolerate the forward current resulting from the inline 150R resistors (approx 15mA). 

What I learned
====

EasyEda
-----

- Its fun
- It's time consuming
- The power and ground lines should be made wider 
- Tweak the default track separation and width so they are more robust and lower resistance 

Arduino
-----

- A6/A7 cannot be used as digital outouts, just digital inputs only
- The I2C pins SCL/SDA are open collector and need pull ups - see more below
- D13 is connected via a 1k resistor and an LED to ground so this can interfere with it's reliability as a digital input due to the pull down.

__Do I or don't I need pullup resistors on the I2C lines SDA/SCL?__ 
There is a lot of confusing info on this online, but I found an explanation of why some kind of pullup MUST be present ....
 
_"I2C bus drivers are "open drain", meaning that they can pull the corresponding signal line low, but cannot drive it high. Thus, there can be no bus contention where one device is trying to drive the line high while another tries to pull it low, eliminating the potential for damage to the drivers or excessive power dissipation in the system. Each signal line MUST HAVE a pull-up resistor on it, to restore the signal to high when no device is asserting it low."_
 
However, for a physically short bus and where the voltages on each end are the same then a design doesn't need separate external pullups on the I2C pins. This is because the Ardunio Wire library turns on the internal pull up resistors in it's twi_init() called by Wire.begin() function on SDA & SCL. Doing this puts a weak-pull up on the I2C pins even though they are acting as outputs. Further digging explains that its possible to have the digital input pull ups turned on despite the pins acting as in/out I2C pins because the digital IO circuitry is in parallel to the I2C IO circuitry. Convenient!

Principal of operation 
====

This circuit is designed to both to power a low power logic device and also exercise it's various states by applying a sequence of known inputs and verifying expected outputs.
The circuit is designed to verify regular H and L outputs but is also capable of verifying that a pin is in a high impedance "high-Z" state. 

Two GPIO pins are dedicatd to test each pin of the chip under test.
- a pin "GPIO-L" with a low resistance in-line 
- a pin "GPIO-H" with a high resistance in-line
Together these two GPIO pins make the a single in/out “test pin” that is attached to the pin of the chip under test.

![pin-config.png](pin-config.png)

**GPIO-L and GPIO-H operate as a pair in one of four modes:
**
- Driving an input: Where the test subject's pin is a expected to be an input to that device, then GPIO-L is set to H or L as appropriate to drive the IC's input logic level; GPIO-H is not relevant in this use case and it is configured as a high impedance state.
 
- Testing for 1/0 output: Where the test subject's pin is expected to be bi-state output, then GPIO-L is configured as an input and is used to sense the state of the test IC's output pin; GPIO-H is not relevant in this use case and it is configured as a high impedance state.
  
- Testing for high-Z output: Where the test subject's pin is expected to be in a high-impedance output state, a tristate outputs with output enabe disabled, then this high-Z state can be verified by using GPIO-L as a sense input and simultaneously using GPIP-H to apply a weak pull up then a pull down signal to the test subject's pin. If this pull-up & down is sensed by GPIO-L then the test pin must be in a high impedance state. If the pin had not been high-Z and had been asserting either H or L then this strong H/L signal would have swamped  the weak pull up/down of GPIP-H and GPIO-L could not have detected the pull affect of  GPIO-H.

- Power supply to chip being tested: Where the test subject’s pin is expected to be either GND or VCC, then GPIO-L is set to a L or  H output respectively; GPIO-H is not relevant in this use case and it is configured as a high impedance state.


Choice of resistor values
-------

__GPIO-L__

The resistor on GPIO-L is present solely to provide over-current protection. However, one of the modes of use for the trst pins is to drive VCC and GND of the test subject, so this resistor has to be low enough that it can source and sink sufficient current that the test chip will operate correctly.

However, the resistor can't be so small that it fails to provide short circuit protection to the GPIO pin.

So we want the resistor to be a low value but not too low.

In the end I went for 150R in the implementation because I figured all current paths would have at least two serial resistors meaning the path would typically be 2x150R=300R. This is probably unreliable logic because in some errant cases the shorted resistors might be in parallel, but I figure it's good enough. 

__GPIO-H__

GPIO-H is used solely in the high-Z detection case where it acts as a weak pull up/down and in all other tests GPIO-H is disabled and plays no part. 

The high value resistor on GPIO-H is chosen so that this pin can apply a mild pullup/pulldown to the chip under test during that Z output state testing.

__Implementation__

Low Res : 150R
- drives VCC, GND plus regular logic inputs
- senses H/L/Z outputs 

High Res : 10k
- drives pullup/down during high-Z tests

NB: The high level voltage on the Zif socket is approx 4.8v.

Software
========

The approach I chosen is to use the serial console of the Arduino IDE as the interface to the test circuit. 

You load the test program into the the Arduino IDE, edit the code trivally to select the test plan for the chip you are interested in and then send the program to the Arduino to run the tests.

Feedback on the test results is reported from the Arduino back to the serial console of the IDE. Make sure the baud rate in the console matches the program.

I used the Arduino Nano and this doesn't support a file system so I can't include an onboard file with the test cases. Instead, I compile these into the Arduino program (sketch).

Other databases
===============

The format of the test cases is backward compatible with https://github.com/akshaybaweja/Smart-IC-Tester, however this implementation also supports  tri-state detection capability.



VSCode Setup
============

If you want to use VSCode instead of the Arduino IDE ...

https://cuneyt.aliustaoglu.biz/en/enabling-arduino-intellisense-with-visual-studio-code/

ALSO https://github.com/microsoft/vscode-arduino/issues/891

VSCODE formatting that I used :     _"C_Cpp.clang_format_fallbackStyle": "{ BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 0, AllowShortBlocksOnASingleLine: true}"_
