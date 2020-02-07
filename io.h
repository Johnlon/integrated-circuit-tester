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

#define PASS   F("PASS   : ")
#define FAIL   F("FAIL   : ")
#define ERROR  F("ERROR  : ")
#define INFO   F("INFO   : ")
#define RESULT F("RESULT : ")
#define HALT   F("HALT   : ")
#define MATCH  F("MATCH  : ")

//
//void INFOLN(const char * s1, const __FlashStringHelper* s2);
//void INFOLN(const char * s1, const char * s2="", const char * s3="", const char * s4="", const char * s5="");

//void errorln(const char * s1, const char * s2="", const char * s3="", const char * s4="", const char * s5="");
//void halt(const char* m1, const char* m2 = "", const char* m3 = "", const char* m4 = "", const char* m5 = "");

//void print(const __FlashStringHelper* s1, const char * s2="", const char * s3="", const char * s4="", const char * s5="", const char * s6="", const char * s7="");
//void println(const __FlashStringHelper* s1, const char * s2="", const char * s3="", const char * s4="", const char * s5="", const char * s6="", const char * s7="");

#define PRINT1(s1) \
  {Serial.print(s1);}
  
#define PRINT2(s1,s2) \
  {Serial.print(s1);\
  Serial.print(s2);}
  
#define PRINT3(s1,s2,s3) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3);}
  
#define PRINT4(s1,s2,s3,s4) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4);}
  
#define PRINT5(s1,s2,s3,s4,s5) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4); \
  Serial.print(s5);}

#define PRINT6(s1,s2,s3,s4,s5,s6) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4); \
  Serial.print(s5); \
  Serial.print(s6);}

#define PRINT7(s1,s2,s3,s4,s5,s6,s7) \
  {Serial.print(s1); \
  Serial.print(s2); \
  Serial.print(s3); \
  Serial.print(s4); \
  Serial.print(s5); \
  Serial.print(s6); \
  Serial.print(s7);}



// SEE https://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros
// The multiple macros that you would need anyway [as per: Crazy Eddie]
#define XXX_0(T)                      {Serial.print(T);} 
#define XXX_1(T,A)                    PRINT2(T,A) 
#define XXX_2(T,A,B)                  PRINT3(T,A,B)
#define XXX_3(T,A,B,C)                PRINT4(T,A,B,C)
#define XXX_4(T,A,B,C,D)              PRINT5(T,A,B,C,D)
#define XXX_5(T,A,B,C,D,E)            PRINT6(T,A,B,C,D,E)
#define XXX_6(T,A,B,C,D,E,F)          PRINT7(T,A,B,C,D,E,F)


// The interim macro that simply strips the excess and ends up with the required macro
#define XXX_X(x,A,B,C,D,E,FUNC, ...)  FUNC  

// The macro that the programmer uses 
#define XXX_GEN(CODE, ...)                XXX_X(,##__VA_ARGS__,\
                                          XXX_6(CODE, __VA_ARGS__, "\n"),\
                                          XXX_5(CODE, __VA_ARGS__, "\n"),\
                                          XXX_4(CODE, __VA_ARGS__, "\n"),\
                                          XXX_3(CODE, __VA_ARGS__, "\n"),\
                                          XXX_2(CODE, __VA_ARGS__, "\n"),\
                                          XXX_1(CODE, __VA_ARGS__, "\n")\
                                         ) 

#define ERRORLN(...)   XXX_GEN(ERROR, ##__VA_ARGS__)
#define INFOLN(...)   XXX_GEN(INFO, ##__VA_ARGS__)
#define HALTLN(...)   {XXX_GEN(INFO, ##__VA_ARGS__); while (1) delay(10000);}
#define MATCHLN(...)   {XXX_GEN(MATCH, ##__VA_ARGS__); while (1) delay(10000);}


#endif
