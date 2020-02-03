#define CHIP_EMPTY chip("EMPTY", "Empty ZIF")  \
                    .scenario("ZZZZZZZZZZZ/ZZZZZZZZZZZ", "Empty")

#define CHIP_c74245 chip("74245", "Transceiver 8 bit") \
                  .scenario("XZZZZZZZZG/ZZZZZZZZ1V", "OE disabled")  \
                  .scenario("100000000G/LLLLLLLL0V", "A to B all low") \
                  .scenario("111111111G/HHHHHHHH0V", "A to B all high") \
                  .scenario("0LLLLLLLLG/000000000V", "B to A all low") \
                  .scenario("0HHHHHHHHG/111111110V", "B to A all high")

#define CHIP_c74242 chip("74242", "Transceiver Inverting 4 bit")  \
                  .scenario("1ZZZZZG/ZZZZZ0V", "OEA and OEB both disabled") \
                  .scenario("0ZZZZZG/ZZZZZ1V", "OEA and OEB both enabled") \
                  .scenario("0Z0000G/HHHHZ1V", "A to B all low") \
                  .scenario("0Z1111G/LLLLZ1V", "A to B all high") \
                  .scenario("1ZHHHHG/0000Z1V", "B to A all low") \
                  .scenario("1ZLLLLG/1111Z1V", "B to A all high")
