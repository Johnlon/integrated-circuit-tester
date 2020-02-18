#ifndef _IO_H_
#define _IO_H_

/* NOTE These are macros not functions, so for example the followung will not compile 
 
    if (allok)
      INFOLN(F("matches "));
    else
      INFOLN(F("not "));

 Because the first ';' breaks the if/else.

 Either remove the trailing ';' from the macro 
 
   if (allok) 
      INFOLN(F("matches "))
   else 
      INFOLN(F("not "))
    
OR use a block like ...
 
    if (allok) {
      INFOLN(F("matches "));
    } else {
      INFOLN(F("not "));
    }

 Prefer the former so as not to fool oneself these are functions.

  */

#define S_PASS   F("PASS   : ")
#define S_FAIL   F("FAIL   : ")
#define S_ERROR  F("ERROR  : ")
#define S_INFO   F("INFO   : ")
#define S_RESULT F("RESULT : ")
#define S_HALT   F("HALT   : ")
#define S_MATCH  F("MATCH  : ")

#define PRINT1(s1) \
  {Serial.print(s1); Serial.flush();}
  
#define PRINT2(s1,s2) \
  {Serial.print(s1);\
  Serial.print(s2); Serial.flush();}
  
#define PRINT3(s1,s2,s3) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); Serial.flush();}
  
#define PRINT4(s1,s2,s3,s4) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4); Serial.flush();}
  
#define PRINT5(s1,s2,s3,s4,s5) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4); \
  Serial.print(s5); Serial.flush();}

#define PRINT6(s1,s2,s3,s4,s5,s6) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4); \
  Serial.print(s5); \
  Serial.print(s6); Serial.flush();}

#define PRINT7(s1,s2,s3,s4,s5,s6,s7) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4); \
  Serial.print(s5); \
  Serial.print(s6); \
  Serial.print(s7); Serial.flush();}

#define PRINT8(s1,s2,s3,s4,s5,s6,s7,s8) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4); \
  Serial.print(s5); \
  Serial.print(s6); \
  Serial.print(s7); \
  Serial.print(s8); Serial.flush();}

#define PRINT9(s1,s2,s3,s4,s5,s6,s7,s8,s9) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4); \
  Serial.print(s5); \
  Serial.print(s6); \
  Serial.print(s7); \
  Serial.print(s8); \
  Serial.print(s9); Serial.flush();}

// SEE https://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros
// The multiple macros that you would need anyway [as per: Crazy Eddie]
#define XXX_0(T)                      {Serial.print(T);} 
#define XXX_1(T,A)                    PRINT2(T,A) 
#define XXX_2(T,A,B)                  PRINT3(T,A,B)
#define XXX_3(T,A,B,C)                PRINT4(T,A,B,C)
#define XXX_4(T,A,B,C,D)              PRINT5(T,A,B,C,D)
#define XXX_5(T,A,B,C,D,E)            PRINT6(T,A,B,C,D,E)
#define XXX_6(T,A,B,C,D,E,F)          PRINT7(T,A,B,C,D,E,F)
#define XXX_7(T,A,B,C,D,E,F,G)        PRINT8(T,A,B,C,D,E,F,G)
#define XXX_8(T,A,B,C,D,E,F,G,H)      PRINT9(T,A,B,C,D,E,F,G,H)


// The interim macro that simply strips the excess and ends up with the required macro
#define XXX_X(x,A,B,C,D,E,F,G,FUNC, ...)  FUNC  

// The macro that the programmer uses 
#define XXX_GEN(CODE, ...)                XXX_X(,##__VA_ARGS__,\
                                          XXX_8(CODE, __VA_ARGS__, "\n"),\
                                          XXX_7(CODE, __VA_ARGS__, "\n"),\
                                          XXX_6(CODE, __VA_ARGS__, "\n"),\
                                          XXX_5(CODE, __VA_ARGS__, "\n"),\
                                          XXX_4(CODE, __VA_ARGS__, "\n"),\
                                          XXX_3(CODE, __VA_ARGS__, "\n"),\
                                          XXX_2(CODE, __VA_ARGS__, "\n"),\
                                          XXX_1(CODE, __VA_ARGS__, "\n")\
                                         ) 

#define ERRORLN(...)   XXX_GEN(S_ERROR, ##__VA_ARGS__)
#define INFOLN(...)  XXX_GEN(S_INFO, ##__VA_ARGS__)
#define HALTLN(...)   {XXX_GEN(S_INFO, ##__VA_ARGS__); while (1) delay(10000);}
#define MATCHLN(...)   {XXX_GEN(S_MATCH, ##__VA_ARGS__);}
#define FAILLN(...)  {XXX_GEN(S_FAIL, ##__VA_ARGS__);}
#define PASSLN(...)   {XXX_GEN(S_PASS, ##__VA_ARGS__);}
#define RESULTLN(...)   {XXX_GEN(S_RESULT, ##__VA_ARGS__);}

#endif
