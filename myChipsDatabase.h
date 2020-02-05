#define CHIP_EMPTY chip("EMPTY", "Empty ZIF")  \
                    .scenario("ZZZZZZZZZZ/ZZZZZZZZZZ", "Empty")

#define CHIP_x74245 chip("74245", "Transceiver 8 bit") \
                  .scenario("XZZZZZZZZG/ZZZZZZZZ1V", "OE disabled")  \
                  .scenario("100000000G/LLLLLLLL0V", "A to B all low") \
                  .scenario("111111111G/HHHHHHHH0V", "A to B all high") \
                  .scenario("0LLLLLLLLG/000000000V", "B to A all low") \
                  .scenario("0HHHHHHHHG/111111110V", "B to A all high")

#define CHIP_x74242 chip("74242", "Transceiver Inverting 4 bit")  \
                  .scenario("1ZZZZZG/ZZZZZ0V", "OEA and OEB both disabled") \
                  .scenario("0ZZZZZG/ZZZZZ1V", "OEA and OEB both enabled") \
                  .scenario("0Z0000G/HHHHZ1V", "A to B all low") \
                  .scenario("0Z1111G/LLLLZ1V", "A to B all high") \
                  .scenario("1ZHHHHG/0000Z1V", "B to A all low") \
                  .scenario("1ZLLLLG/1111Z1V", "B to A all high")

#define CHIP_x74173 chip("74173", "4-bit 3-state D flip-flop with reset, dual clock enables and dual output enables") \
                  .scenario("10ZZZZCG/0000001V", "OE1 disabled") \
                  .scenario("01ZZZZCG/0000001V", "OE2 disabled") \
                  .scenario("11ZZZZCG/0000001V", "OE1 & OE2 disabled") \
                  .scenario("00LLLLCG/0000001V", "Clock all 0 into reg") \
                  .scenario("00LLLLCG/0011111V", "E1 & E2 enabled but MR asserted so will not load (holds value)") \
                  .scenario("00LLLLCG/1111110V", "E1 & E2 disabled so will not load") \
                  .scenario("00LLLLCG/0111110V", "E2 disabled so will not load")  \
                  .scenario("00LLLLCG/1011110V", "E1 disabled so will not load") \
                  .scenario("00HHHHCG/0011110V", "Load D to Q") \
                  .scenario("00HHHHCG/1011110V", "E1 disabled so will not load") 

                 
