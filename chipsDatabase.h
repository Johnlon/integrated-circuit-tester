#define CHIP_4000 F("4000:Dual 3-input NOR gate and inverter" \
	":00000HG1LH000V::" \
	":00000HG0HH000V::" \
	":00001LG0HL100V::" \
	":00010LG0HL010V::" \
	":00011LG0HL110V::" \
	":00100LG0HL001V::" \
	":00101LG0HL101V::" \
	":00110LG0HL011V::" \
	":00111LG0HL111V::" \
)
#define CHIP_4001 F("4001:Quad 2-input NOR gate" \
	":00HH00G00HH00V::" \
	":01LL01G01LL01V::" \
	":10LL10G10LL10V::" \
	":11LL11G11LL11V::" \
)
#define CHIP_4002 F("4002:Dual 4-input NOR gates" \
	":L00010G01100LV::" \
	":L00010G01000LV::" \
	":L00010G01111LV::" \
	":L00110G00011LV::" \
	":L11000G01111LV::" \
	":L01000G00100LV::" \
	":L11110G01111LV::" \
	":H00000G00000HV::" \
	":L10100G01010LV::" \
	":L01010G00101LV::" \
)
#define CHIP_4009 F("4009:Hex inverters with level shifted outputs" \
	":VH0H0H0G0H0HX0HV::" \
	":VL1L1L1G1L1LX1LV::" \
)
#define CHIP_4010 F("4010:Hex buffers with level shifted outputs" \
	":VH1H1H1G1H1HX1HV::" \
	":VL0L0L0G0L0LX0LV::" \
)
#define CHIP_40106 F("40106:Hex inverters with schmitt-trigger inputs" \
	":0H0H0HGH0H0H0V::" \
	":1L1L1LGL1L1L1V::" \
)
#define CHIP_4011 F("4011:Quad 2-input NAND gates" \
	":00HL11G11LH00V::" \
	":10HH10G10HH10V::" \
	":01HH01G01HH01V::" \
	":11LH00G00HL11V::" \
)
#define CHIP_4012 F("4012:Dual 4-input NAND gates" \
	":H0000XGX0000HV::" \
	":H1010XGX1010HV::" \
	":H0101XGX0101HV::" \
	":L1111XGX1111LV::" \
)
#define CHIP_4013 F("4013:Dual D flip-flop with set and reset" \
	":LHC100G001CHLV::" \
	":HLC001G100CLHV::" \
	":LHC000G000CHLV::" \
	":HLC010G010CLHV::" \
)
#define CHIP_4015 F("4015:Dual 4-bit serial-in parallel-out shift register with asynchronous reset" \
	":CLLLL10GCLLLL10V::" \
	":CLLLH01GCLLLH01V::" \
	":CLLHH01GCLLHH01V::" \
	":CLHHH01GCLHHH01V::" \
	":CHHHL00GCHHHL00V::" \
)
#define CHIP_4016 F("4016:Quad analog switches" \
	":0HH000G0HH000V::" \
	":1HH100G1HH100V::" \
	":0LL011G0LL011V::" \
	":1HH111G1HH111V::" \
)
#define CHIP_40161 F("40161:4-bit synchronous binary counter" \
	":0C10110G10XXXXXV::" \
	":0C10110G11LLLLLV::" \
	":1C10110G00HHLHLV::" \
	":1000001G11HHLHLV::" \
	":1C00001G11HHHLLV::" \
	":1C00001G11HHHHHV::" \
	":1C00001G11LLLLLV::" \
	":1C00001G11LLLHLV::" \
	":1100001G11LLHLLV::" \
	":1000001G11LLHLLV::" \
	":0000001G11LLLLLV::" \
	":1C00001G11XXXXXV::" \
)
#define CHIP_40162 F("40162:4-bit synchronous decade counter" \
	":0C11100G10XXXXXV::" \
	":1C11100G00LHHHLV::" \
	":1000001G11LHHHLV::" \
	":1C00001G11HLLLLV::" \
	":1C00001G11HLLHHV::" \
	":1C00001G11LLLLLV::" \
	":1C00001G11LLLHLV::" \
	":1C00001G11LLHLLV::" \
	":1100001G11LLHHLV::" \
	":0100001G11LLHHLV::" \
	":0000001G11LLHHLV::" \
	":0100001G11LLLLLV::" \
	":1C00001G11XXXXXV::" \
)
#define CHIP_4017 F("4017:4-bit asynchronous decade counter" \
	":LLHLLLLGLLLH0C1V::" \
	":LHLLLLLGLLLH0C0V::" \
	":LLLHLLLGLLLH0C0V::" \
	":LLLLLLHGLLLH0C0V::" \
	":LLLLLLLGLHLH0C0V::" \
	":HLLLLLLGLLLL0C0V::" \
	":LLLLHLLGLLLL0C0V::" \
	":LLLLLHLGLLLL0C0V::" \
	":LLLLLLLGHLLL0C0V::" \
	":LLLLLLLGLLHL0C0V::" \
	":LLHLLLLGLLLH0C0V::" \
	":LLHLLLLGLLLH1C0V::" \
)
#define CHIP_40174 F("40174:6-bit D flip-flop with reset" \
	":1H11H1HGCH1H11HV::" \
	":1L00L0LGCL0L00LV::" \
	":0L00L0LGCL0L00LV::" \
	":0L11L1LGCL1L11LV::" \
)
#define CHIP_40175 F("40175:Quad D-type flip-flop" \
	":1HL11LHGCHL11LHV::" \
	":1LH00HLGCLH00HLV::" \
	":0LH00HLGCLH00HLV::" \
	":0LH11HLGCLH11HLV::" \
)
#define CHIP_4018 F("4018:5-stage Johnson counter with preset inputs" \
	":100HHH0G10H1HC1V::" \
	":100HLH0G10H1HC0V::" \
	":100LLH0G10H1HC0V::" \
	":100LLL0G10H1HC0V::" \
	":100LLL0G10L1HC0V::" \
	":000LLL0G10L1LC0V::" \
	":000HHH0G11L1LC0V::" \
	":000HHH0G00H0LC0V::" \
	":100HHH0G00H0HC0V::" \
	":100HLH0G00H0HC0V::" \
)
#define CHIP_4019 F("4019:8-to-4 line noninverting data selector/multiplexer with OR function" \
	":1111111G1HHHH11V::" \
	":1111111G0HHHH11V::" \
	":1111111G0LLLL01V::" \
	":0000000G1LLLH11V::" \
	":1010101G1HHHL00V::" \
	":1010101G0HHHH10V::" \
)
#define CHIP_40192 F("40192:4-bit synchronous decade up/down counter" \
	":1XX11XXG011HH11V::" \
	":1HH11HLG010HH01V::" \
	":0HH10HLG001HH00V::" \
	":0LL11LHG001HH00V::" \
	":0LL10LHG001HH00V::" \
	":0LH11LHG001HH00V::" \
	":0LH10LHG001LH00V::" \
	":0LL11LLG001HH00V::" \
	":0LL10LLG001HH00V::" \
	":0LH11LLG001HH00V::" \
	":0LH01LLG001HH00V::" \
	":0LL11LLG001HH00V::" \
	":0LL01LLG001HL00V::" \
	":0LH11HLG001HH00V::" \
)
#define CHIP_40193 F("40193:4-bit synchronous binary up/down counter" \
	":0XX11XXG111HH11V::" \
	":0LH11HHG110HH01V::" \
	":0LH10HHG001HH00V::" \
	":0HL11HHG001HH00V::" \
	":0HL10HHG001HH00V::" \
	":0HH11HHG001HH00V::" \
	":0HH10HHG001LH00V::" \
	":0LL11LLG001HH00V::" \
	":0LL10LLG001HH00V::" \
	":0LH11LLG001HH00V::" \
	":0LH01LLG001HH00V::" \
	":0LL11LLG001HH00V::" \
	":0LL01LLG001HL00V::" \
	":0HH11HHG001HH00V::" \
)
#define CHIP_4020 F("4020:14-bit asynchronous binary counter with reset" \
	":LLLLLLLGL01LLLLV::" \
	":LLLLLLLGL00LLLLV::" \
	":LLLLLLLGLC0LLLLV::" \
	":LLLLLLLGHC0LLLLV::" \
	":LLLLLLLGHC0LLLLV::" \
	":LLLLLLLGLC0LLLLV::" \
	":LLLLLLLGLC0LLLLV::" \
	":LLLLLLLGHC0LLLLV::" \
	":LLLLLLLGLC0LLLLV::" \
	":LLLLLLLGLC0LLLLV::" \
	":LLLLLLLGHC0LLLLV::" \
	":LLLLLLLGHC0LLLLV::" \
	":LLLLLLLGLC0LLLLV::" \
	":LLLLLLLGLC0LLLLV::" \
	":LLLLLLLGHC0LLLLV::" \
	":LLLLLLLGHC0LLLLV::" \
	":LLLLLLLGLC0LLLLV::" \
	":LLLLLLHGLC0LLLLV::" \
	":LLLLLLHGHC0LLLLV::" \
	":LLLLLLHGHC0LLLLV::" \
	":LLLLLLHGLC0LLLLV::" \
	":LLLLLLHGLC0LLLLV::" \
	":LLLLLLHGHC0LLLLV::" \
	":LLLLLLHGHC0LLLLV::" \
	":LLLLLLHGLC0LLLLV::" \
	":LLLLLLHGLC0LLLLV::" \
)
#define CHIP_4022 F("4022:3-bit asynchronous binary counter" \
	":LHLLLXLGXLLH0C1V::" \
	":HLLLLXLGXLLH0C0V::" \
	":LLHLLXLGXLLH0C0V::" \
	":LLLLLXHGXLLH0C0V::" \
	":LLLLLXLGXLHL0C0V::" \
	":LLLHLXLGXLLL0C0V::" \
	":LLLLHXLGXLLL0C0V::" \
	":LLLLLXLGXHLL0C0V::" \
	":LHLLLXLGXLLH0C0V::" \
	":LHLLLXLGXLLH1C0V::" \
)
#define CHIP_4023 F("4023:Triple 3-input NAND gates" \
	":00000HG0HH000V::" \
	":00100HG1HH100V::" \
	":10010HG0HH010V::" \
	":10110HG1HH110V::" \
	":01001HG0HH001V::" \
	":01101HG1HH101V::" \
	":11011HG0HH011V::" \
	":11111LG1LL111V::" \
)
#define CHIP_4024 F("4024:7-bit asynchronous binary counter with reset" \
	":C1XXXXGXXXXXXV::" \
	":C0LLLLGXLXLHXV::" \
	":C0LLLLGXLXHLXV::" \
	":C0LLLLGXLXHHXV::" \
	":C0LLLLGXHXLLXV::" \
	":C0LLLLGXHXLHXV::" \
	":C0LLLLGXHXHLXV::" \
	":C0LLLLGXHXHHXV::" \
	":C0LLLHGXLXLLXV::" \
	":C0LLLHGXLXLHXV::" \
	":C0LLLHGXLXHLXV::" \
	":C0LLLHGXLXHHXV::" \
	":C0LLLHGXHXLLXV::" \
	":C1LLLLGXLXLLXV::" \
)
#define CHIP_4025 F("4025:Triple 3-input NOR gates" \
	":00000HG0HH000V::" \
	":00100LG1LL100V::" \
	":10010LG0LL010V::" \
	":10110LG1LL110V::" \
	":01001LG0LL001V::" \
	":01101LG1LL101V::" \
	":11011LG0LL011V::" \
	":11111LG1LL111V::" \
)
#define CHIP_4027 F("4027:Dual J-K flip-flops with set and reset" \
	":HLC0001G1000CLHV::" \
	":LHC1000G0001CHLV::" \
	":HLC0010G0100CLHV::" \
	":HLC0000G0000CLHV::" \
	":LHC0100G0010CHLV::" \
)
#define CHIP_4028 F("4028:1-of-10 noninverting decoder/demultiplexer" \
	":LLHLLLLGL0000LLV::" \
	":LLLLLLLGL1000HLV::" \
	":LLHLLLLGL0000LLV::" \
	":LLLLLLLGL1001LHV::" \
	":HLLLLLLGL0010LLV::" \
	":LLLLLHLGL1010LLV::" \
	":LLLLLLHGL0011LLV::" \
	":LLLHLLLGL1011LLV::" \
	":LLLLLLLGH0100LLV::" \
	":LLLLHLLGL1100LLV::" \
)
#define CHIP_4029 F("4029:4-bit synchronous binary/decade up/down counter with preset and ripple carry output" \
	":1L000LHG01L00LCV::" \
	":0L000HHG01L00LCV::" \
	":0L000LHG01H00LCV::" \
	":0L000HHG01H00LCV::" \
	":0L000LHG01L00HCV::" \
	":0L000HHG01L00HCV::" \
	":0L000LHG01H00HCV::" \
	":0L000HHG01H00HCV::" \
	":0H000LHG01L00LCV::" \
	":0H000HLG00L00LCV::" \
	":0H000LHG00L00LCV::" \
	":0L000HHG00H00HCV::" \
	":0L000LHG00H00HCV::" \
	":0L000HHG00L00HCV::" \
	":0L000LHG00L00HCV::" \
	":0L000HHG00H00LCV::" \
	":0L000LHG00H00LCV::" \
	":0L000HHG00L00LCV::" \
	":0L001LHG00L00LCV::" \
	":0L000LLG00L00LCV::" \
	":0H000HHG00L00LCV::" \
	":CL000LHG01H11HCV::" \
)
#define CHIP_4030 F("4030:Quad 2-input XOR gate" \
	":10HH10G10HH10V::" \
	":01HH01G01HH01V::" \
	":00LL00G00LL00V::" \
	":11LL11G11LL11V::" \
)
#define CHIP_4031 F("4031:64-bit serial-in serial-out shift register with multiplexed inputs" \
	":0CXXXHLGX0XXXX1V::" \
	":0CXXXLHGX0XXXX0V::" \
	":1CXXXHLGX1XXXX0V::" \
	":0CXXXLHGX1XXXX0V::" \
)
#define CHIP_4040 F("4040:12-bit asynchronous binary counter with reset" \
	":XXXXXXXGXC1XXXXV::" \
	":LLLLLLLGHC0LLLLV::" \
	":LLLLLLHGLC0LLLLV::" \
	":LLLLLLHGHC0LLLLV::" \
	":LLLLLHLGLC0LLLLV::" \
	":LLLLLHLGHC0LLLLV::" \
	":LLLLLHHGLC0LLLLV::" \
	":LLLLLHHGHC0LLLLV::" \
	":LLLLHLLGLC0LLLLV::" \
	":LLLLHLLGHC0LLLLV::" \
	":LLLLHLHGLC0LLLLV::" \
	":LLLLHLHGHC0LLLLV::" \
	":LLLLHHLGLC0LLLLV::" \
	":LLLLHHLGHC0LLLLV::" \
	":LLLLHHHGLC0LLLLV::" \
)
#define CHIP_4041 F("4041:Quad buffers with complementary outputs" \
	":HL1HL1GHL1HL1V::" \
	":LH0LH0GLH0LH0V::" \
)
#define CHIP_4042 F("4042:4-bit transparent latch with selectable latch enable polarity and complementary outputs" \
	":HHL1001GLHHL11LV::" \
	":HHL1101GLHHL11LV::" \
	":LLH0110GHLLH00HV::" \
)
#define CHIP_4043 F("4043:Quad 3-state S-R latches with overriding set" \
	":LL10101GLL10001V::" \
	":HH01110GHH01010V::" \
	":HH00100GHH00000V::" \
	":HH11111GHH11111V::" \
)
#define CHIP_4044 F("4044:Quad 3-state S-R latches with overriding reset" \
	":HX01110GHH01H10V::" \
	":HX11111GHH11H11V::" \
	":LX10101GLL10L01V::" \
)
#define CHIP_4048 F("4048:3-state 8-input multifunction gate." \
	":H100000G0000000V::" \
	":L110100G0010100V::" \
	":H110100G1010100V::" \
	":L100000G1000000V::" \
)
#define CHIP_4049 F("4049:Hex inverters with high-to-low level shifter inputs" \
	":VL1H0L1G0H1L11L1::" \
	":VH0L1H0G1L0H01L1::" \
)
#define CHIP_4051 F("4051:8-channel analog multiplexer/demultiplexer" \
	":11L1100G0001011V::" \
	":11L1100G0011101V::" \
	":11L1100G0101110V::" \
	":11L1100G0110111V::" \
	":01L1100G1001111V::" \
	":11L1000G1011111V::" \
	":10L1100G1101111V::" \
	":11L0100G1111111V::" \
	":00H0000G0000100V::" \
	":00H0000G0010010V::" \
	":00H0000G0100001V::" \
	":00H0000G0111100V::" \
	":10H0000G1000000V::" \
	":00H0100G1010000V::" \
	":01H0000G1100000V::" \
	":00H1000G1110000V::" \
	":11H1110G0001011V::" \
)
#define CHIP_4053 F("4053:Triple 2-to-1 line analog multiplexer/demultiplexer" \
	":010X100G00010XXV::" \
	":010H100G00010HHV::" \
	":011H000G10010HHV::" \
	":100H100G01010HHV::" \
	":010H100G00101HHV::" \
)
#define CHIP_4066 F("4066:Quad analog switches" \
	":0HH000G0HH000V::" \
	":1HH100G1HH100V::" \
	":0LL011G0LL011V::" \
	":1HH111G1HH111V::" \
)
#define CHIP_4068 F("4068:8-input AND/NAND gate with complementary outputs" \
	":011110G01111LV::" \
	":010100G01010HV::" \
	":001010G00101HV::" \
	":000110G00011HV::" \
	":011000G01100HV::" \
	":000000G01111HV::" \
	":000000G00000HV::" \
	":011110G01110HV::" \
	":011010G01111HV::" \
	":001110G00111HV::" \
)
#define CHIP_4069 F("4069:Hex inverters" \
	":0H0H0HGH0H0H0V::" \
	":1L1L1LGL1L1L1V::" \
)
#define CHIP_4070 F("4070:Quad 2-input XOR gates" \
	":00LL00G00LL00V::" \
	":10HH10G10HH10V::" \
	":01HH01G01HH01V::" \
	":11LL11G11LL11V::" \
)
#define CHIP_4071 F("4071:Quad 2-input OR gates" \
	":00LH11G11HL00V::" \
	":10HH10G10HH10V::" \
	":01HH01G01HH01V::" \
	":11HL00G00LH11V::" \
)
#define CHIP_4072 F("4072:Dual 4-input OR gates" \
	":L00000G00000LV::" \
	":H10000G01000HV::" \
	":H01000G00100HV::" \
	":H11000G01100HV::" \
	":H00100G00010HV::" \
	":H10100G01010HV::" \
	":H01100G00110HV::" \
	":H11100G01110HV::" \
	":H00010G00001HV::" \
	":H10010G01001HV::" \
	":H11110G01111HV::" \
)
#define CHIP_4073 F("4073:Triple 3-input AND gates" \
	":00000LG0LL000V::" \
	":00100LG1LL100V::" \
	":10010LG0LL010V::" \
	":10110LG1LL110V::" \
	":11001LG0LL001V::" \
	":01101LG1LL101V::" \
	":11001LG0LL011V::" \
	":11111HG1HH111V::" \
)
#define CHIP_4075 F("4075:Triple 3-input OR gates" \
	":00000LG0LL000V::" \
	":00110HG1HH100V::" \
	":10010HG0HH010V::" \
	":10110HG1HH110V::" \
	":11001HG0HH001V::" \
	":01101HG1HH101V::" \
	":11011HG0HH011V::" \
	":11111HG1HH100V::" \
)
#define CHIP_4076 F("4076:4-bit 3-state D flip-flop with reset" \
	":00HHHHCG0011110V::" \
	":00HLHLCG0001010V::" \
	":00LHLHCG0010100V::" \
)
#define CHIP_4077 F("4077:Quad 2-input XNOR gates" \
	":00HH00G00HH00V::" \
	":10LL10G10LL10V::" \
	":01LL01G01LL01V::" \
	":11HH11G11HH11V::" \
)
#define CHIP_4078 F("4078:8-input OR/NOR gate with complementary outputs" \
	":111110G01111LV::" \
	":010100G01010LV::" \
	":001010G00101LV::" \
	":000110G00011LV::" \
	":011000G01100LV::" \
	":000000G01111LV::" \
	":000000G00000HV::" \
	":111110G01110LV::" \
	":011010G01111LV::" \
	":001110G00111LV::" \
)
#define CHIP_4081 F("4081:Quad 2-input AND gates" \
	":00LH11G11HL00V::" \
	":10LL10G10LL10V::" \
	":01LL01G01LL01V::" \
	":11HL00G00LH11V::" \
)
#define CHIP_4082 F("4082:Dual 4-input AND gates" \
	":L00000G00000LV::" \
	":L10000G01000LV::" \
	":L01000G00100LV::" \
	":L11000G01100LV::" \
	":L00100G00010LV::" \
	":L10100G01010LV::" \
	":L01100G00110LV::" \
	":L11100G01110LV::" \
	":L00010G10111LV::" \
	":L10010G01001LV::" \
	":H11110G01111HV::" \
)
#define CHIP_4093 F("4093:Quad 2-input NAND gates with schmitt-trigger inputs" \
	":00HH00G00HH00V::" \
	":10HH10G10HH10V::" \
	":01HH01G01HH01V::" \
	":11LL11G11LL11V::" \
)
#define CHIP_4094 F("4094:8-bit 3-state serial-in parallel-out shift register with output latches" \
	":1X0XXXXGXXXXXX1V::" \
	":11CHXXXGXXXXXX1V::" \
	":10CLHXXGXXXXXX1V::" \
	":11CHLHXGXXXXXX1V::" \
	":10CLHLHGXXXXXX1V::" \
	":11CHLHLGXXXXXH1V::" \
	":10CLHLHGXXXXHL1V::" \
	":11CHLHLGXXXHLH1V::" \
	":10CLHLHGXXHLHL1V::" \
	":11CHLHLGLXLHLH1V::" \
	":10CLHLHGHXHLHL1V::" \
	":01CLHLHGLXHLHL1V::" \
	":110HLHLGLXLHLH1V::" \
	":100HHHHGLXHHHH0V::" \
)
#define CHIP_4098 F("4098:Dual monostable multivibrator, retriggerable, resettable" \
	":01000LHGHL00010V::" \
	":01101LHGHL10110V::" \
	":01111XXGXX11110V::" \
	":01111XXGXX11110V::" \
	":01111HLGLH11110V::" \
	":00111LHGHL11100V::" \
	":01101LHGHL10110V::" \
	":01111LHGHL11110V::" \
	":01110HLGLH01110V::" \
	":00110LHGHL01100V::" \
	":01111LHGHL11110V::" \
)
#define CHIP_4503 F("4503:2/4-bit 3-state noninverting buffer/line driver" \
	":10H1H0HGH1L0H10V::" \
	":11H0H1HGH0H1L00V::" \
	":00L1H0LGH1H1H01V::" \
	":01H0L1HGL0H0H11V::" \
)
#define CHIP_4510 F("4510:4-bit synchronous decade up/down counter" \
	":1L010HHG01L01HCV::" \
	":0L000LHG01H00HCV::" \
	":0L000HHG01H00HCV::" \
	":0L000LHG00H00HCV::" \
	":0L000HHG00L00HCV::" \
)
#define CHIP_4511 F("4511:BCD-7 Segment Latch Decoder Driver" \
	":0001000GHHHHHHHV::" \
	":0011001GLLHHLLLV::" \
	":0111001GLHHLHHHV::" \
	":0011000GHHHHHLHV::" \
	":0010000GLLLLLLLV::" \
)
#define CHIP_4512 F("4512:8-to-1 line 3-state data selector/multiplexer with AND inputs" \
	":0111111G10000L0V::" \
	":1000000G00000H0V::" \
	":1011111G10100L0V::" \
	":0100000G00100H0V::" \
	":1101111G10010L0V::" \
	":0010000G00010H0V::" \
	":1110111G10110L0V::" \
	":0001000G00110H0V::" \
	":1111011G10001L0V::" \
	":0000100G00001H0V::" \
	":1111101G10101L0V::" \
	":0000010G00100H1V::" \
	":1111110G10011L0V::" \
	":0000001G00011H0V::" \
	":1111111G00111L0V::" \
	":0000000G10111H0V::" \
	":0000000G11111L0V::" \
	":1111111G00111H1V::" \
)
#define CHIP_4518 F("4518:Dual 4-bit asynchronous decade counters" \
	":C1XXXX1GC1XXXX1V::" \
	":C0XXXX0GC0XXXX0V::" \
	":C1LLLL1GC1LLLL1V::" \
	":C0LLLL0GC0LLLL0V::" \
	":C1HLLL0GC1HLLL0V::" \
	":C0LHLL0GC0LHLL0V::" \
	":C1XXXX0GC1XXXX0V::" \
)
#define CHIP_4519 F("4519:4 - BIT AND/OR SELECTOR" \
	":0111111G0LLLL01V::" \
	":0011001G0HLHL11V::" \
	":0101100G1HHLH10V::" \
	":1010110G1LLLH11V::" \
	":1001001G1LLHL10V::" \
	":1110011G1HHHL10V::" \
)
#define CHIP_4520 F("4520:Dual binary counter" \
	":C1XXXX1GC1XXXX1V::" \
	":C1HLLL0GC1HLLL0V::" \
	":C1LHLL0GC1LHLL0V::" \
	":C1HHLL0GC1HHLL0V::" \
	":C1LLHL0GC1LLHL0V::" \
	":C1HLHL0GC1HLHL0V::" \
	":C1LHHL0GC1LHHL0V::" \
	":C1HHHL0GC1HHHL0V::" \
	":C1LLLH0GC1LLLH0V::" \
	":C1HLLH0GC1HLLH0V::" \
	":C1LHLH0GC1LHLH0V::" \
)
#define CHIP_4529 F("4529:dual 4-channel or single 8-channel analog data selector" \
	":1101000GHH01011V::" \
	":1101010GLL01011V::" \
	":1010111GHH10100V::" \
	":0010101GLL10101V::" \
)
#define CHIP_4532 F("4532:8-to-3 line noninverting priority encoder with cascade inputs" \
	":00000LLGL0000LLV::" \
	":00001LLGL0000LHV::" \
	":00011HHGH0000HLV::" \
	":00101HHGL0000HLV::" \
	":01001HLGH0000HLV::" \
	":10001HLGL0000HLV::" \
	":00001LHGH0001HLV::" \
	":00001LHGL0010HLV::" \
	":00001LLGH0100HLV::" \
	":00001LLGL1000HLV::" \
)
#define CHIP_4543 F("4543:BCD to 7-segment decoder/LCD driver with input latch" \
	":1001000GHHHHHHHV::" \
	":1000100GLHHLLLLV::" \
	":1110000GHLHHHHHV::" \
	":1011000GLLLLLLLV::" \
)
#define CHIP_4572 F("4572:CMOS Hex Inverter" \
	":H0H0H00GH0H0H00V::" \
	":H0H0L10GH0H0H10V::" \
	":L1L1L01GL1L1H01V::" \
	":L1L1L11GL1L1L11V::" \
)
#define CHIP_7400 F("7400:Quad 2-input NAND gates" \
	":00H00HGH00H00V::" \
	":10H10HGH10H10V::" \
	":01H01HGH01H01V::" \
	":11L11LGL11L11V::" \
)
#define CHIP_7401 F("7401:Quad 2-input open-collector NAND gates" \
	":H00H00G00H00HV::" \
	":H10H10G10H10HV::" \
	":H01H01G01H01HV::" \
	":L11L11G11L11LV::" \
)
#define CHIP_7402 F("7402:Quad 2-input NOR gates" \
	":H00H00G00H00HV::" \
	":L10L10G10L10LV::" \
	":L01L01G01L01LV::" \
	":L11L11G11L11LV::" \
)
#define CHIP_7403 F("7403:Quad 2-input open-collector NAND gates" \
	":00H00HGH00H00V::" \
	":10H10HGH10H10V::" \
	":01H01HGH01H01V::" \
	":11L11LGL11L11V::" \
)
#define CHIP_7404 F("7404:Hex inverters" \
	":0H0H0HGH0H0H0V::" \
	":1L1L1LGL1L1L1V::" \
)
#define CHIP_7405 F("7405:Hex open-collector inverters" \
	":0H0H0HGH0H0H0V::" \
	":1L1L1LGL1L1L1V::" \
)
#define CHIP_7406 F("7406:Hex open-collector high-voltage inverters" \
	":0H0H0HGH0H0H0V::" \
	":1L1L1LGL1L1L1V::" \
)
#define CHIP_7407 F("7407:Hex open-collector high-voltage buffers" \
	":1H1H1HGH1H1H1V::" \
	":0L0L0LGL0L0L0V::" \
)
#define CHIP_7408 F("7408:Quad 2-input AND gates" \
	":00L00LGL00L00V::" \
	":01L01LGL01L01V::" \
	":10L10LGL10L10V::" \
	":11H11HGH11H11V::" \
)
#define CHIP_7409 F("7409:Quad 2-input open-collector AND gates" \
	":11H11HGH11H11V::" \
	":10L10LGL10L10V::" \
	":01L01LGL01L01V::" \
	":00L00LGL00L00V::" \
)
#define CHIP_7410 F("7410:Triple 3-input NAND gates" \
	":00000HGH000H0V::" \
	":00100HGH100H1V::" \
	":10010HGH010H0V::" \
	":10110HGH110H1V::" \
	":01001HGH001H0V::" \
	":01101HGH101H1V::" \
	":11011HGH011H0V::" \
	":11111LGL111L1V::" \
)
#define CHIP_74107 F("74107:Dual negative-edge-triggered J-K flip-flops with reset" \
	":0HL0LHG0C00C0V::" \
	":1HL1LHG1C01C0V::" \
	":0HL0LHG0C10C1V::" \
	":1LH0HLG1C10C1V::" \
	":0HL1LHG0C11C1V::" \
	":1LH1HLG1C11C1V::" \
)
#define CHIP_74109 F("74109:Dual J-/K flip-flops with set and reset" \
	":000C1LHGHL1C000V::" \
	":011C1LHGHL1C110V::" \
	":100C0HLGLH0C001V::" \
	":111C0HLGLH1C111V::" \
	":100C1LHGHL1C001V::" \
	":110C1HLGLH1C011V::" \
	":101C1HLGLH1C101V::" \
	":111C1HLGLH1C111V::" \
)
#define CHIP_7411 F("7411:Triple 3-input AND gates" \
	":00000LGL000L0V::" \
	":00001LGL001L1V::" \
	":01010LGL010L0V::" \
	":10100LGL100L0V::" \
	":11110LGL110L0V::" \
	":01011LGL011L1V::" \
	":10101LGL101L1V::" \
	":11111HGH111H1V::" \
)
#define CHIP_74112 F("74112:Dual negative-edge-triggered J-K flip-flops with set and reset" \
	":C000HLLGH000C11V::" \
	":C110HLLGH011C11V::" \
	":C001LHHGL100C00V::" \
	":C111LHHGL100C00V::" \
	":C001LHHGL100C11V::" \
	":C011HLLGH110C11V::" \
	":C101LHHGL101C11V::" \
	":C111HLLGH111C11V::" \
)
#define CHIP_74113 F("74113:Dual negative-edge-triggered J-K flip-flop with set" \
	":C000HLGLH000CV::" \
	":C110HLGLH011CV::" \
	":C001HLGLH100CV::" \
	":C011HLGLH000CV::" \
	":C101LHGHL101CV::" \
	":C111HLGLH111CV::" \
)
#define CHIP_7412 F("7412:Triple 3-input open-collector NAND gates" \
	":00000HGH000H0V::" \
	":00100HGH100H1V::" \
	":10010HGH010H0V::" \
	":10110HGH110H1V::" \
	":01001HGH001H0V::" \
	":01101HGH101H1V::" \
	":11011HGH011H0V::" \
	":11111LGL111L1V::" \
)
#define CHIP_74123 F("74123:Dual retriggerable monostable multivibrators with overriding reset" \
	":000HLLHG000HLLHV::" \
	":110HLLHG110HLLHV::" \
	":010HLLHG010HLLHV::" \
	":111HLLHG111HLLHV::" \
	":000HLLHG000HLLHV::" \
	":101HLLHG101HLLHV::" \
)
#define CHIP_74125 F("74125:Quad 3-state noninverting buffer with active low enables" \
	":01H01HGH10H10V::" \
	":00L00LGL00L00V::" \
	":10H10HGH01H01V::" \
	":11H11HGH11H11V::" \
	":10H11HGH01H11V::" \
	":11H10HGH11H01V::" \
	":11H10HGH01H11V::" \
	":10H11HGH11H01V::" \
)
#define CHIP_74126 F("74126:Quad 3-state noninverting buffer with active high enables" \
	":11H11HGH11H11V::" \
	":10L10LGL01L01V::" \
	":00H00HGH00H00V::" \
	":01H01HGH10H10V::" \
)
#define CHIP_7413 F("7413:Dual 4-input NAND gates with schmitt-trigger inputs" \
	":00000HGH00000V::" \
	":10000HGH10000V::" \
	":01000HGH01000V::" \
	":11000HGH11000V::" \
	":00010HGH00010V::" \
	":10010HGH10010V::" \
	":01010HGH01010V::" \
	":11010HGH11010V::" \
	":11111LGL11111V::" \
)
#define CHIP_74132 F("74132:Quad 2-input NAND gates with schmitt-trigger inputs" \
	":00H00HGH00H00V::" \
	":10H10HGH10H10V::" \
	":01H01HGH01H01V::" \
	":11L11LGL11L11V::" \
)
#define CHIP_74133 F("74133:13-input NAND gate" \
	":0000000GH000000V::" \
	":1000000GH000000V::" \
	":1100000GH000000V::" \
	":0000000GH111000V::" \
	":1111000GH000000V::" \
	":1111100GH000000V::" \
	":0000000GH111111V::" \
	":1111111GH000000V::" \
	":1111111GH100000V::" \
	":1111111GH110000V::" \
	":1111111GH111000V::" \
	":1111111GH111100V::" \
	":1111111GH111110V::" \
	":1111111GL111111V::" \
)
#define CHIP_74136 F("74136:Quad 2-input open-collector XOR gates" \
	":00L00LGL00L00V::" \
	":10H10HGH10H10V::" \
	":01H01HGH01H01V::" \
	":11L11LGL11L11V::" \
)
#define CHIP_74137 F("74137:1-of-8 inverting decoder/demultiplexer with address latches" \
	":111111HGHHHHHHHV::" \
	":000010HGHHHHHHHV::" \
	":111110HGHHHHHHHV::" \
	":000000HGHHHHHHHV::" \
	":000001HGHHHHHHLV::" \
	":100001HGHHHHHLHV::" \
	":010001HGHHHHLHHV::" \
	":110001HGHHHLHHHV::" \
	":001001HGHHLHHHHV::" \
	":101001HGHLHHHHHV::" \
	":011001HGLHHHHHHV::" \
	":111001LGHHHHHHHV::" \
)
#define CHIP_74138 F("74138:1-of-8 inverting decoder/demultiplexer" \
	":111111HGHHHHHHHV::" \
	":000110HGHHHHHHHV::" \
	":111110HGHHHHHHHV::" \
	":000000HGHHHHHHHV::" \
	":000001HGHHHHHHLV::" \
	":100001HGHHHHHLHV::" \
	":010001HGHHHHLHHV::" \
	":110001HGHHHLHHHV::" \
	":001001HGHHLHHHHV::" \
	":101001HGHLHHHHHV::" \
	":011001HGLHHHHHHV::" \
	":111001LGHHHHHHHV::" \
)
#define CHIP_74139 F("74139:Dual 1-of-4 inverting decoder/demultiplexer" \
	":101HHHHGHHHH011V::" \
	":110HHHHGHHHH101V::" \
	":000LHHHGHHHL000V::" \
	":010HLHHGHHLH010V::" \
	":001HHLHGHLHH100V::" \
	":011HHHLGLHHH110V::" \
)
#define CHIP_7414 F("7414:Hex inverters with schmitt-trigger inputs" \
	":0H0H0HGH0H0H0V::" \
	":1L1L1LGL1L1L1V::" \
)
#define CHIP_74140 F("74140:Dual 4-input NAND gates/50R line drivers" \
	":00000HGH00000V::" \
	":10000HGH10000V::" \
	":01000HGH01000V::" \
	":11000HGH11000V::" \
	":00010HGH00010V::" \
	":10010HGH10010V::" \
	":01010HGH01010V::" \
	":11010HGH11010V::" \
	":11111LGL11111V::" \
)
#define CHIP_74147 F("74147:10-to-4 line inverting priority encoder" \
	":11111HHGH1111H0V::" \
	":11111HHGL0111L0V::" \
	":11110HHGH1111L0V::" \
	":11101LLGL1111H0V::" \
	":11011LLGH1111H0V::" \
	":10111LHGL1111H0V::" \
	":01111LHGH1111H0V::" \
	":11111HLGL1110H0V::" \
	":11111HLGH1101H0V::" \
	":11111HHGL1011H0V::" \
)
#define CHIP_74148 F("74148:10-to-4 line inverting priority encoder" \
	":01011HHGH0101HHV::" \
	":11110HHGH1111HLV::" \
	":10100LLGL0101LHV::" \
	":01010LLGH1010LHV::" \
	":10110LHGL0101LHV::" \
	":01110LHGH1010LHV::" \
	":11110HLGL1010LHV::" \
	":11110HLGH0101LHV::" \
	":11110HHGL1011LHV::" \
	":11110HHGH0111LHV::" \
)
#define CHIP_7415 F("7415:Triple 3-input open-collector AND gates" \
	":00000LGL000L0V::" \
	":00100LGL100L1V::" \
	":10010LGL010L0V::" \
	":10110LGL110L1V::" \
	":01001LGL001L0V::" \
	":01101LGL101L1V::" \
	":11011LGL011L0V::" \
	":11111HGH111H1V::" \
)
#define CHIP_74151 F("74151:8-to-1 line data selector/multiplexer with complementary outputs" \
	":0101LH1G1010101V::" \
	":1010LH1G0101010V::" \
	":1110LH0G0001111V::" \
	":0001HL0G0000000V::" \
	":1101LH0G0011111V::" \
	":0010HL0G0010000V::" \
	":1011LH0G0101111V::" \
	":0100HL0G0100000V::" \
	":0111LH0G0111111V::" \
	":1000HL0G0110000V::" \
	":1111LH0G1001110V::" \
	":0000HL0G1000001V::" \
	":1111LH0G1011101V::" \
	":0000HL0G1010010V::" \
	":1111LH0G1101011V::" \
	":0000HL0G1100100V::" \
	":1111LH0G1110111V::" \
	":0000HL0G1111000V::" \
)
#define CHIP_74153 F("74153:8-to-2 line noninverting data selector/multiplexer with separate enables" \
	":100101LGL101011V::" \
	":111010LGL010101V::" \
	":001010LGL101001V::" \
	":000101HGL010101V::" \
	":000101LGL101011V::" \
	":011010HGL010111V::" \
	":011010LGL101001V::" \
	":010101HGL010101V::" \
	":010101LGL101011V::" \
	":011010HGL010111V::" \
	":100101LGL010100V::" \
	":101010LGH101000V::" \
	":100101LGL101010V::" \
	":101010LGH010110V::" \
	":110101LGL100100V::" \
	":111010LGH011000V::" \
	":110101LGL101010V::" \
	":111010LGH010110V::" \
)
#define CHIP_74157 F("74157:8-to-4 line noninverting data selector/multiplexer" \
	":111H11HGH11H110V::" \
	":101L01LGL10L101V::" \
	":000L00LGL00L000V::" \
	":001L01LGL10L100V::" \
	":010H10HGH01H010V::" \
	":011H11HGH11H110V::" \
	":100L00LGL00L000V::" \
	":110L10LGL01L010V::" \
	":101H01HGH10H100V::" \
	":010L10LGL01L011V::" \
)
#define CHIP_74158 F("74158:4-of-8 inverting decoder/demultiplexer" \
	":010H10HGH10H101V::" \
	":101H01HGH01H011V::" \
	":000H00HGH00H000V::" \
	":001H01HGH10H100V::" \
	":010L10LGL01L010V::" \
	":011L11LGL11L110V::" \
	":100H00HGH00H000V::" \
	":110H10HGH01H010V::" \
	":101L01LGL10L100V::" \
	":111L11LGL11L110V::" \
)
#define CHIP_7416 F("7416:Hex open-collector high-voltage inverters" \
	":0H0H0HGH0H0H0V::" \
	":1L1L1LGL1L1L1V::" \
)
#define CHIP_74160 F("74160:4-bit synchronous decade counter" \
	":0C00000G00LLLLLV::" \
	":0C00001G11LLLLLV::" \
	":1C11101G01LHHHLV::" \
	":1C00001G11HLLLLV::" \
	":1C11101G11HLLHHV::" \
	":1C00001G11LLLLLV::" \
	":1C00001G11LLLHLV::" \
	":1C00001G11LLHLLV::" \
	":1C00001G11LLHHLV::" \
	":1C00001G11LHLLLV::" \
	":1C00001G11LHLHLV::" \
	":1100001G11LHHLLV::" \
	":1000001G11LHHLLV::" \
	":0000001G11LLLLLV::" \
)
#define CHIP_74161 F("74161:4-bit synchronous binary counter" \
	":0100000G00LLLLLV::" \
	":0100001G11LLLLLV::" \
	":1C00001G10LLLLLV::" \
	":1C00000G11LLLLLV::" \
	":1C00000G10LLLLLV::" \
	":1C00000G00LLLLLV::" \
	":1C00111G01HHLLLV::" \
	":1C00001G11HHLHLV::" \
	":1C00001G11HHHLLV::" \
	":1C00001G11HHHHHV::" \
	":1C00001G11LLLLLV::" \
	":1C00001G11LLLHLV::" \
	":1100001G11LLHLLV::" \
	":1000001G11LLHLLV::" \
	":0000001G11LLLLLV::" \
	":1C00001G11XXXXXV::" \
)
#define CHIP_74162 F("74162:4-bit synchronous decade counter" \
	":0100000G00XXXXXV::" \
	":0C00000G00LLLLLV::" \
	":0C00000G00LLLLLV::" \
	":0C10000G11LLLLLV::" \
	":1C00001G10LLLLLV::" \
	":1C00000G11LLLLLV::" \
	":0C00000G11LLLLLV::" \
	":1C11100G00LHHHLV::" \
	":1C00111G11HLLLLV::" \
	":1C00001G11HLLHHV::" \
	":1C00001G11LLLLLV::" \
	":1C00001G11LLLHLV::" \
	":1C00001G11LLHLLV::" \
	":1100001G11LLHHLV::" \
	":0100001G11LLHHLV::" \
	":0000001G11LLHHLV::" \
	":0100001G11LLLLLV::" \
	":1C00001G11XXXXXV::" \
)
#define CHIP_74163 F("74163:4-bit synchronous binary counter" \
	":0100000G00XXXXXV::" \
	":1000000G00XXXXXV::" \
	":0C00000G00LLLLLV::" \
	":0C10000G11LLLLLV::" \
	":1C00111G01HHLLLV::" \
	":1C00001G11HHLHLV::" \
	":1C00001G11HHHLLV::" \
	":1C00001G11HHHHHV::" \
	":1C00001G11LLLLLV::" \
	":1C00001G11LLLHLV::" \
	":1C00001G11LLHLLV::" \
	":1C00001G11LLHHLV::" \
	":1C00001G11LHLLLV::" \
	":1100001G11LHLHLV::" \
	":0100001G11LHLHLV::" \
	":0000001G11LHLHLV::" \
	":0100001G11LLLLLV::" \
)
#define CHIP_74164 F("74164:8-bit serial-in parallel-out shift register" \
	":00LLLLGC0LLLLV::" \
	":11LLLLGC0LLLLV::" \
	":00LLLLGC1LLLLV::" \
	":11HLLLGC1LLLLV::" \
	":11HHLLGC1LLLLV::" \
	":00LHHLGC1LLLLV::" \
	":01LLHHGC1LLLLV::" \
	":10LLLHGC1HLLLV::" \
)
#define CHIP_74165 F("74165:8-bit parallel-in serial-out shift register" \
	":0C0000HGL000000V::" \
	":0C0100HGL000000V::" \
	":1C0100HGL000000V::" \
	":1C0010HGL100000V::" \
	":1C0001LGH100000V::" \
	":1C0000HGL100000V::" \
)
#define CHIP_74166 F("74166:8-bit parallel-in serial-out shift register" \
	":000000CG0000L00V::" \
	":111110CG0111L11V::" \
	":000000CG1000L00V::" \
	":111110CG1111L11V::" \
	":000000CG1000L00V::" \
	":111110CG1111H10V::" \
	":100000CG1000H01V::" \
	":111110CG1111H11V::" \
	":000000CG1000H01V::" \
	":011110CG1111H11V::" \
	":100001CG1000H01V::" \
	":011111CG1111H10V::" \
)
#define CHIP_7417 F("7417:Hex open-collector high-voltage buffers" \
	":1H1H1HGH1H1H1V::" \
	":0L0L0LGL0L0L0V::" \
)
#define CHIP_74173 F("74173:4-bit 3-state D flip-flop with reset, dual clock enables and dual output enables" \
	":00LLLLCG0000001V::" \
	":00LLLLCG1111111V::" \
	":00LLLLCG0000000V::" \
	":00LLLLCG1111110V::" \
	":00LLLLCG1000000V::" \
	":00LLLLCG1111110V::" \
	":00LLLLCG0100000V::" \
	":00LLLLCG1111110V::" \
	":00LLLLCG0000000V::" \
)
#define CHIP_74174 F("74174:6-bit D flip-flop with reset" \
	":0L00L00GCL0L00LV::" \
	":0L11L10GCL1L11LV::" \
	":1L00L00GCL0L00LV::" \
	":1H11H11GCH1H11HV::" \
)
#define CHIP_74175 F("74175:4-bit D flip-flop with complementary outputs and reset" \
	":0LH00HLGCLH00HLV::" \
	":0LH11HLGCLH11HLV::" \
	":1HL11LHGCHL11LHV::" \
	":1LH00HLGCLH00HLV::" \
)
#define CHIP_7418 F("7418:Dual 4-input NAND gates with schmitt-trigger inputs" \
	":00000HGH00000V::" \
	":10000HGH10000V::" \
	":01000HGH01000V::" \
	":11000HGH11000V::" \
	":00010HGH00010V::" \
	":10010HGH10010V::" \
	":01010HGH01010V::" \
	":11010HGH11010V::" \
	":11111LGL11111V::" \
)
#define CHIP_74182 F("74182:Look-ahead carry generator" \
	":110011HGHHLH100V::" \
	":101010LGLHLL010V::" \
)
#define CHIP_74190 F("74190:4-bit synchronous decade up/down counter" \
	":0LL00LLG000LHC0V::" \
	":0LL10LLG001LHC0V::" \
	":0LH00LLG001LHC0V::" \
	":0HL00LLG001LHC0V::" \
	":0HH00LLG001LHC0V::" \
	":0LL00HLG001LHC0V::" \
	":0HH01LLG001LHC0V::" \
	":0HL01LLG001LHC0V::" \
	":0LH01LLG001LHC0V::" \
)
#define CHIP_74191 F("74191:4-bit synchronous binary up/down counter" \
	":0LL00LLG000LHC0V::" \
	":0LL10LLG001LHC0V::" \
	":0LH00LLG001LHC0V::" \
	":0HL00LLG001LHC0V::" \
	":0HH00LLG001LHC0V::" \
	":0LL00HLG001LHC0V::" \
	":0HH01LLG001LHC0V::" \
	":0HL01LLG001LHC0V::" \
	":0LH01LLG001LHC0V::" \
)
#define CHIP_74192 F("74192:4-bit synchronous decade up/down counter" \
	":0LL11LLG1011110V::" \
	":0LL11LLG1011100V::" \
	":0LL11LHG1001100V::" \
	":0LL11LHG1011100V::" \
	":0LL10LHG1011100V::" \
	":0LH11LHG1011100V::" \
	":0LH10LHG1010100V::" \
)
#define CHIP_74193 F("74193:4-bit synchronous binary up/down counter" \
	":1HH00HHG110XX01V::" \
	":1HLC1HHG111XX01V::" \
	":1LHC1HHG111XX01V::" \
	":1LLC1HHG111XX01V::" \
	":1HH1CLHG111XX01V::" \
	":1LL1CHHG111XX01V::" \
	":1LH1CHHG111XX01V::" \
	":1LLC1LLG111XX11V::" \
)
#define CHIP_74194 F("74194:4-bit bidirectional universal shift register with asynchronous reset" \
	":0000000G00CLLLLV::" \
	":0111111G11CLLLLV::" \
	":1000000G00CLLLLV::" \
	":1111111G11CLLLLV::" \
	":1011110G11CHHHHV::" \
	":1100001G11CLLLLV::" \
	":1111110G10CLLLHV::" \
	":1100001G10CLLHHV::" \
	":1100001G10CLHHHV::" \
	":1100001G10CHHHHV::" \
	":1000000G10CHHHLV::" \
	":1011111G10CHHLLV::" \
	":1000001G01CHHHLV::" \
	":1111111G01CHHHHV::" \
	":1000000G01CLHHHV::" \
	":1111110G01CLLHHV::" \
	":1000000G00CLLHHV::" \
	":1111111G00CLLHHV::" \
)
#define CHIP_74195 F("74195:4-bit universal shift register with J-/K inputs and asynchronous reset" \
	":0000000G0CHLLLLV::" \
	":1000000G0CHLLLLV::" \
	":1000000G1CHLLLLV::" \
	":1010000G1CHLLLLV::" \
	":1000000G1CHLLLLV::" \
	":1110000G1CHLLLHV::" \
	":1100000G1CHLLHLV::" \
)
#define CHIP_7420 F("7420:Dual 4-input NAND gates" \
	":00000HGH00000V::" \
	":10000HGH10000V::" \
	":01000HGH01000V::" \
	":11000HGH11000V::" \
	":00010HGH00010V::" \
	":10010HGH10010V::" \
	":01010HGH01010V::" \
	":11010HGH11010V::" \
	":11111LGL11111V::" \
)
#define CHIP_7421 F("7421:Dual 4-input AND gates" \
	":11X11HGH11X11V::" \
	":01X01LGL01X01V::" \
	":10X10LGL10X10V::" \
	":00X00LGL00X00V::" \
)
#define CHIP_7422 F("7422:Dual 4-input open-collector NAND gates" \
	":00000HGH00000V::" \
	":10000HGH10000V::" \
	":01000HGH01000V::" \
	":11000HGH11000V::" \
	":00010HGH00010V::" \
	":10010HGH10010V::" \
	":01010HGH01010V::" \
	":11010HGH11010V::" \
	":00001HGH00001V::" \
	":10001HGH10001V::" \
	":01001HGH01001V::" \
	":11001HGH11001V::" \
	":00011HGH00011V::" \
	":10011HGH10011V::" \
	":01011HGH01011V::" \
	":11011LGL11011V::" \
)
#define CHIP_74237 F("74237:1-of-8 noninverting decoder/demultiplexer with address latches" \
	":000010XGXXXXXXXV::" \
	":000110LGLLLLLLLV::" \
	":000001LGLLLLLLHV::" \
	":100001LGLLLLLHLV::" \
	":010001LGLLLLHLLV::" \
	":110001LGLLLHLLLV::" \
	":001001LGLLHLLLLV::" \
	":101001LGLHLLLLLV::" \
	":011001LGHLLLLLLV::" \
	":111001HGLLLLLLLV::" \
)
#define CHIP_74242 F("74242:4-bit 3-state inverting bus transceiver" \
	":10HHHHG000001V::" \
	":10LLLLG111101V::" \
	":000000GHHHH00V::" \
	":001111GLLLL00V::" \
)
#define CHIP_74243 F("74243:4-bit 3-state noninverting bus transceiver" \
	":10HHHHG111101V::" \
	":10LLLLG000001V::" \
	":001111GHHHH00V::" \
	":000000GLLLL00V::" \
)
#define CHIP_7425 F("7425:Dual 4-input NOR gates with enable input" \
	":10100LGL10100V::" \
	":01100LGL01100V::" \
	":11100LGL11100V::" \
	":00110LGL00110V::" \
	":10110LGL10110V::" \
	":01110LGL01110V::" \
	":11110LGL11110V::" \
	":00101LGL00101V::" \
	":10101LGL10101V::" \
	":01101LGL01101V::" \
	":11101LGL11101V::" \
	":00111LGL00111V::" \
	":10111LGL10111V::" \
	":01111LGL01111V::" \
	":11111LGL11111V::" \
	":00100HGH00100V::" \
)
#define CHIP_74251 F("74251:8-to-1 line 3-state data selector/multiplexer with complementary outputs" \
	":1010LH0G0001010V::" \
	":1010HL0G0010101V::" \
	":1010LH0G0100101V::" \
	":1010HL0G0110101V::" \
	":1010HL0G1000101V::" \
	":1010LH0G1010101V::" \
	":1010HL0G1100101V::" \
	":1010LH0G1110101V::" \
)
#define CHIP_74253 F("74253:8-to-2 line 3-state noninverting data selector/multiplexer" \
	":100000HGH000001V::" \
	":111111HGH111111V::" \
	":000000LGL000000V::" \
	":000001HGH100000V::" \
	":000000LGL000010V::" \
	":000010HGH010010V::" \
	":010000LGL000000V::" \
	":010100HGH001000V::" \
)
#define CHIP_74257 F("74257:8-to-4 line 3-state noninverting data selector/multiplexer" \
	":000H00HGH00H001V::" \
	":111H11HGH11H111V::" \
	":000L00LGL00L000V::" \
	":001L01LGL10L100V::" \
	":010H10HGH01H010V::" \
	":011H11HGH11H110V::" \
	":100L00LGL00L000V::" \
	":110L10LGL01L010V::" \
	":101H01HGH10H100V::" \
	":111H11HGH11H110V::" \
)
#define CHIP_74258 F("74258:8-to-4 line 3-state inverting data selector/multiplexer" \
	":000H00HGH00H001V::" \
	":111H11HGH11H111V::" \
	":000H00HGH00H000V::" \
	":001H01HGH10H100V::" \
	":010L10LGL01L010V::" \
	":011L11LGL11L110V::" \
	":100H00HGH00H000V::" \
	":110H10HGH01H010V::" \
	":101L01LGL10L100V::" \
	":111L11LGL11L110V::" \
)
#define CHIP_74259 F("74259:1-of-8 addressable latch with reset" \
	":100LLLLGLLLL010V::" \
	":010LLLLGLLLL110V::" \
	":001LLLLGLLLL110V::" \
	":000HLLLGLLLL100V::" \
	":100LHLLGLLLL100V::" \
	":010LLHLGLLLL100V::" \
	":110LLLHGLLLL100V::" \
	":001LLLLGHLLL100V::" \
)
#define CHIP_7426 F("7426:Quad 2-input open-collector high-voltage NAND gates" \
	":00H00HGH00H00V::" \
	":10H10HGH01H01V::" \
	":01H01HGH10H10V::" \
	":11L11LGL11L11V::" \
)
#define CHIP_74260 F("74260:Dual 5-input NOR gates" \
	":0000HHG000000V::" \
	":1010LLG101001V::" \
	":0101LLG010110V::" \
	":1101LLG110111V::" \
	":0010LLG001110V::" \
	":1111LLG111111V::" \
	":1000LLG100000V::" \
	":1110LLG011101V::" \
	":0110LLG111010V::" \
	":1011LLG110011V::" \
)
#define CHIP_74266 F("74266:Quad 2-input open-collector XNOR gates" \
	":00HH00G00HH00V::" \
	":10LL10G10LL10V::" \
	":01LL01G01LL01V::" \
	":11HH11G11HH11V::" \
)
#define CHIP_7427 F("7427:Triple 3-input NOR gates" \
	":00000HGH000H0V::" \
	":00100LGL100L1V::" \
	":10010LGL010L0V::" \
	":10110LGL110L1V::" \
	":01001LGL001L0V::" \
	":10101LGL101L1V::" \
	":11011LGL011L0V::" \
	":11111LGL111L1V::" \
)
#define CHIP_7428 F("7428:Quad 2-input NOR gates with buffered outputs" \
	":H00H00G00H00HV::" \
	":L10L10G10L10LV::" \
	":L01L01G01L01LV::" \
	":L11L11G11L11LV::" \
)
#define CHIP_74280 F("74280:9-bit odd/even parity generator/checker" \
	":1001LHG010101V::" \
	":0100HLG101010V::" \
	":1101LHG111111V::" \
	":0000HLG000000V::" \
	":1101LHG100001V::" \
	":0000LHG011111V::" \
	":1100LHG011001V::" \
	":0001HLG101100V::" \
)
#define CHIP_74283 F("74283:4-bit binary full adder with fast carry." \
	":L00L000G0L00L00V::" \
	":L00H001G0L00L00V::" \
	":H11H111G1H11H11V::" \
	":H01H010G0H01H10V::" \
	":H00L110G0H00L11V::" \
	":L11H001G1L11H00V::" \
)
#define CHIP_74292 F("74292:15-bit programmable frequency divider/digital timer" \
	":10X00XXG0000X00V::" \
	":10LC0LLG0010L00V::" \
	":10LC0LLG0010L00V::" \
	":10LC0LHG0010L00V::" \
	":10LC0LHG0010L00V::" \
	":10LC0LLG0010L00V::" \
)
#define CHIP_74293 F("74293:4-bit asynchronous binary counter with /2 and /8 sections and reset" \
	":000LL0GLL1111V::" \
	":000LL0GLL1100V::" \
	":000LL0GLH0100V::" \
	":000LL0GLH1100V::" \
	":000LH0GLH1000V::" \
	":000LH0GLH1100V::" \
	":000HL0GLH1000V::" \
	":000HL0GLH1100V::" \
	":000HH0GLH1000V::" \
	":000HH0GLH1100V::" \
	":000LL0GHH1000V::" \
	":000LL0GHH1100V::" \
)
#define CHIP_74294 F("74294:15-bit programmable frequency divider/digital timer" \
	":10XC0XXGXX0XX00V::" \
	":10LC0XLGXX1XX00V::" \
	":10LC0XLGXX1XX00V::" \
	":10LC0XHGXX1XX00V::" \
	":10LC0XHGXX1XX00V::" \
	":10LC0XLGXX1XX00V::" \
	":10LC0XLGXX1XX00V::" \
	":10LC0XHGXX1XX00V::" \
	":10LC0XHGXX1XX00V::" \
)
#define CHIP_74298 F("74298:8-to-4 line noninverting data selector/multiplexer with output registers" \
	":1010010G10CLHLHV::" \
	":1010010G11CHLHLV::" \
)
#define CHIP_7430 F("7430:8-input NAND gate" \
	":111111GL00110V::" \
	":011111GH00110V::" \
	":101111GH00110V::" \
	":110111GH00110V::" \
	":111011GH00110V::" \
	":111101GH00110V::" \
	":111110GH00110V::" \
	":111111GH00010V::" \
	":111111GH00100V::" \
	":100000GH00000V::" \
)
#define CHIP_7432 F("7432:Quad 2-input OR gates" \
	":00L00LGL00L00V::" \
	":01H01HGH10H10V::" \
	":10H10HGH01H01V::" \
	":11H11HGH11H11V::" \
)
#define CHIP_74365 F("74365:6-bit 3-state noninverting buffer/line driver" \
	":11H1H1HGH1H1H11V::" \
	":01H1H1HGH1H1H11V::" \
	":01H1H1HGH1H1H10V::" \
	":00L0L0LGL0L0L00V::" \
	":11H1H1HGH1H1H10V::" \
	":01H1H1HGH1H1H11V::" \
	":10H0H0HGH0H0H00V::" \
	":00H0H0HGH0H0H01V::" \
)
#define CHIP_74366 F("74366:6-bit 3-state inverting buffer/line driver" \
	":10H0H0HGH0H0H00V::" \
	":00H0H0HGH0H0H01V::" \
	":11H1H1HGH1H1H11V::" \
	":01H1H1HGH1H1H11V::" \
	":01L1L1LGL1L1L10V::" \
	":00H0H0HGH0H0H00V::" \
)
#define CHIP_74367 F("74367:2/4-bit 3-state noninverting buffer/line driver" \
	":11H1H1HGH1H1H11V::" \
	":00L0L0LGL0L0L00V::" \
	":01H1H1HGH1H1H10V::" \
	":00L0L1HGL0L0L00V::" \
	":01X0X0XGX1X0X00V::" \
)
#define CHIP_74368 F("74368:2/4-bit 3-state inverting buffer/line driver" \
	":11H1H1HGH1H1H11V::" \
	":10H0H0HGH0H0H00V::" \
	":00H0H0HGH0H0H00V::" \
	":01L1L1LGL1L1L10V::" \
)
#define CHIP_7437 F("7437:Quad 2-input NAND gates with buffered output" \
	":00H00HGH00H00V::" \
	":10H10HGH10H10V::" \
	":01H01HGH01H01V::" \
	":11L11LGL11L11V::" \
)
#define CHIP_74375 F("74375:Dual 2-bit transparent latches with complementary outputs" \
	":0HL1LH0G0HL1LH0V::" \
	":1LH1HL1G1LH1HL1V::" \
	":1LH0HL1G1LH0HL1V::" \
	":0LH0HL0G0LH0HL0V::" \
)
#define CHIP_7438 F("7438:Quad 2-input open-collector NAND gates with buffered output" \
	":00H00HGH00H00V::" \
	":10H10HGH10H10V::" \
	":01H01HGH01H01V::" \
	":11L11LGL11L11V::" \
)
#define CHIP_74386 F("74386:Quad 2-input XOR gates" \
	":00LL00G00LL00V::" \
	":10HH10G10HH10V::" \
	":01HH01G01HH01V::" \
	":11LL11G11LL11V::" \
)
#define CHIP_74390 F("74390:Dual 4-bit asynchronous decade counters with separate /2 and /5 sections and reset" \
	":01X0XXXGXXX0X10V::" \
	":00L0LLLGLLL0L00V::" \
	":C0H0LLLGLLL0H0CV::" \
	":C0L0HLLGLLH0L0CV::" \
	":C0H0HLLGLLH0H0CV::" \
	":C0L0LHLGLHL0L0CV::" \
	":C0H0LHLGLHL0H0CV::" \
	":C0L0HHLGLHH0L0CV::" \
	":C0H0HHLGLHH0H0CV::" \
	":C0L0LLHGHLL0L0CV::" \
	":C0H0LLHGHLL0H0CV::" \
	":C0L0LLLGLLL0L0CV::" \
)
#define CHIP_74393 F("74393:Dual 4-bit asynchronous binary counters with reset" \
	":00XXXXGXXXX00V::" \
	":00XXXXGXXXX00V::" \
	":00XXXXGXXXX00V::" \
	":11LLLLGLLLL11V::" \
	":10LLLLGLLLL01V::" \
	":00HLLLGLLLH00V::" \
	":10HLLLGLLLH01V::" \
	":00LHLLGLLHL00V::" \
	":10LHLLGLLHL01V::" \
	":00HHLLGLLHH00V::" \
	":10HHLLGLLHH01V::" \
	":00LLHLGLHLL00V::" \
	":10LLHLGLHLL01V::" \
	":00HLHLGLHLH00V::" \
	":10HLHLGLHLH01V::" \
)
#define CHIP_7440 F("7440:Dual 4-input NAND gates with buffered output" \
	":00000HGH00000V::" \
	":10000HGH10000V::" \
	":01000HGH01000V::" \
	":11000HGH11000V::" \
	":00010HGH00010V::" \
	":10010HGH10010V::" \
	":01010HGH01010V::" \
	":11010HGH11010V::" \
	":11111LGL11111V::" \
)
#define CHIP_7442 F("7442:1-of-10 inverting decoder/demultiplexer" \
	":LHHHHHHGHHH0000V::" \
	":HLHHHHHGHHH0001V::" \
	":HHLHHHHGHHH0010V::" \
	":HHHLHHHGHHH0011V::" \
	":HHHHLHHGHHH0100V::" \
	":HHHHHLHGHHH0101V::" \
	":HHHHHHLGHHH0110V::" \
	":HHHHHHHGLHH0111V::" \
	":HHHHHHHGHLH1000V::" \
	":HHHHHHHGHHL1001V::" \
)
#define CHIP_7446 F("7446:Open-collector BCD to 7-segment decoder/common-anode LED driver with ripple blank input and output" \
	":001H100GLLLLLHLV::" \
	":001H001GHHLLHHHV::" \
	":101H100GLLHLLLHV::" \
	":101H001GHLLLLLHV::" \
	":011H100GHHLLHLLV::" \
	":011H001GHLLHLLLV::" \
	":111H100GLLLHHLLV::" \
	":111H001GHHLLLHHV::" \
	":001H110GLLLLLLLV::" \
	":001H011GHHLLLLLV::" \
)
#define CHIP_7447 F("7447:Open-collector BCD to 7-segment decoder/common-anode LED driver with ripple blank input and output" \
	":001H100GLLLLLHLV::" \
	":001H001GHHLLHHHV::" \
	":101H100GLLHLLLHV::" \
	":101H001GHLLLLLHV::" \
	":011H100GHHLLHLLV::" \
	":011H001GHLLHLLLV::" \
	":111H100GLLLHHLLV::" \
	":111H001GHHLLLHHV::" \
	":001H110GLLLLLLLV::" \
	":001H011GHHLLLLLV::" \
)
#define CHIP_7450 F("7450:Dual 2−Wide 2−Input AND/OR Invert Gate" \
	":00000HGH00010V::" \
	":11111LGL11011V::" \
	":11010HGH10010V::" \
	":10011LGL00011V::" \
)
#define CHIP_7451 F("7451:2-wide 2-input and 2-wide 3-input AND-NOR gates" \
	":10000HGL11001V::" \
	":01000HGH01001V::" \
	":10100HGH10000V::" \
	":01100LGH00000V::" \
	":00010HGH10000V::" \
	":00001HGL11000V::" \
	":00011LGH01000V::" \
	":10110HGH00000V::" \
	":11001HGL00001V::" \
	":01111LGH00001V::" \
)
#define CHIP_7455 F("7455:2-wide 4-input AND-NOR gate" \
	":111100GL10000V::" \
	":000000GL11111V::" \
	":100000GH11011V::" \
	":010000GH10011V::" \
	":110000GH11101V::" \
	":001000GH10101V::" \
	":101000GH11001V::" \
	":011000GH10001V::" \
	":111000GH11110V::" \
	":000100GH10110V::" \
)
#define CHIP_7458 F("7458:2-wide 2-input and 2-wide 3-input AND-OR gates" \
	":11111HGH11111V::" \
	":11100HGH00011V::" \
	":00000LGL00000V::" \
)
#define CHIP_74589 F("74589:8-bit 3-state parallel-in serial-out shift register with input registers" \
	":1010101GX10C110V::" \
	":1010101GH100010V::" \
	":1010101GH100110V::" \
	":1010101GL1C0110V::" \
	":1010101GH1C0110V::" \
	":1010101GL1C0100V::" \
	":1010101GH1C0100V::" \
)
#define CHIP_74595 F("74595:8-bit 3-state serial-in parallel-out shift register with output registers" \
	":XXXXXXXGX00000XV::" \
	":LLLLLLLGL10000LV::" \
	":LLLLLLLGL1C001LV::" \
	":LLLLLLLGL1C001LV::" \
	":LLLLLLLGL1C001LV::" \
	":LLLLLLLGL1C001LV::" \
	":HHHLLLLGL10C01HV::" \
)
#define CHIP_74597 F("74597:8-bit parallel-in serial-out shift register with input registers" \
	":1010101GX00C110V::" \
	":1010101GL10C010V::" \
	":1010101GL10C010V::" \
	":1010101GH1C0110V::" \
	":1010101GL1C0110V::" \
)
#define CHIP_7460 F("7460:Dual 4−Input Expander" \
	":111111G1LHHL1V::" \
	":101010G1HLLH0V::" \
	":010101G0HLLH1V::" \
	":000000G0HLLH0V::" \
)
#define CHIP_7461 F("7461:Three expanders three entries" \
	":111111GHHH111V::" \
	":101010GLLL101V::" \
	":010101GLLL010V::" \
	":000000GLLL000V::" \
	":111000GLHL000V::" \
	":000111GHLL000V::" \
	":000000GLLH111V::" \
)
#define CHIP_7462 F("7462:Expanders 3-2-2-3-entries" \
	":11111LGH11111V::" \
	":00000HGL00000V::" \
	":11000LGH00000V::" \
	":00111LGH00000V::" \
	":00000LGH11100V::" \
	":00000LGH00011V::" \
	":10101HGL10101V::" \
	":01010HGL01010V::" \
)
#define CHIP_7465 F("7465:Porta AND-OR-NOT de 4-2-3-2 Entries open collector" \
	":000000GH00000V::" \
	":010101GH10101V::" \
	":101010GH01010V::" \
	":111111GL11111V::" \
	":011000GL00000V::" \
	":000111GL00000V::" \
	":000000GL11100V::" \
	":100000GL00011V::" \
)
#define CHIP_7474 F("7474:Dual D flip-flop with set and reset" \
	":00C1LHGHL1C00V::" \
	":10C0HLGLH0C01V::" \
	":10C1LHGHL1C01V::" \
	":11C1HLGLH1C11V::" \
)
#define CHIP_7485 F("7485:4-bit noninverting magnitude comparator with cascade inputs" \
	":0100HLLG0101011V::" \
	":1001LLHG1010100V::" \
	":1100HLLG1010101V::" \
	":0001LLHG0101010V::" \
	":1100HLLG1001001V::" \
	":0001LLHG0110110V::" \
	":1100HLLG0111001V::" \
	":0001LLHG1000110V::" \
	":1001HLLG0011001V::" \
	":0100LLHG1100110V::" \
	":1010LHLG0011001V::" \
	":0101LLLG1100110V::" \
)
#define CHIP_7486 F("7486:Quad 2-input XOR gates" \
	":00L00LGL00L00V::" \
	":01H01HGH01H01V::" \
	":10H10HGH10H10V::" \
	":11L11LGL11L11V::" \
)
