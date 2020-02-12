#ifndef __MYCHIPSDATABASE__
#define __MYCHIPSDATABASE__

static const char CHIP_EMPTY[] PROGMEM = ("EMPTY:Empty ZIF"  \
                    ":ZZZZZZZZZZ/ZZZZZZZZZZ:Empty");

static const char CHIP_x74245[] PROGMEM = ("74245:Transceiver 8 bit" \
                  ":XZZZZZZZZG/ZZZZZZZZ1V:OE disabled"  \
                  ":100000000G/LLLLLLLL0V:A to B all low" \
                  ":111111111G/HHHHHHHH0V:A to B all high" \
                  ":0LLLLLLLLG/000000000V:B to A all low" \
                  ":0HHHHHHHHG/111111110V:B to A all high");

static const char CHIP_x74242[] PROGMEM = ("74242:Transceiver Inverting 4 bit"  \
                  ":1ZZZZZG/ZZZZZ0V:OEA and OEB both disabled" \
                  ":0ZZZZZG/ZZZZZ1V:OEA and OEB both enabled" \
                  ":0Z0000G/HHHHZ1V:A to B all low" \
                  ":0Z1111G/LLLLZ1V:A to B all high" \
                  ":1ZHHHHG/0000Z1V:B to A all low" \
                  ":1ZLLLLG/1111Z1V:B to A all high");

static const char CHIP_x74173[] PROGMEM = ("74173:4-bit 3-state D flip-flop with reset, dual clock enables and dual output enables" \
                  ":10ZZZZCG/0000001V:OE1 disabled" \
                  ":01ZZZZCG/0000001V:OE2 disabled" \
                  ":11ZZZZCG/0000001V:OE1 & OE2 disabled" \
                  ":00LLLLCG/0000001V:Clock all 0 into reg" \
                  ":00LLLLCG/0011111V:E1 & E2 enabled but MR asserted so will not load (holds value)" \
                  ":00LLLLCG/1111110V:E1 & E2 disabled so will not load" \
                  ":00LLLLCG/0111110V:E2 disabled so will not load"  \
                  ":00LLLLCG/1011110V:E1 disabled so will not load" \
                  ":00HHHHCG/0011110V:Load D to Q" \
                  ":00HHHHCG/1011110V:E1 disabled so will not load");

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


#endif                 
