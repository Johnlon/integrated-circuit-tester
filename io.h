#ifndef _IO_H_
#define _IO_H_

#define PASS   "PASS   : "
#define FAIL   "FAIL   : "
#define ERROR  "ERROR  : "
#define INFO   "INFO   : "
#define RESULT "RESULT : "
#define HALT   "HALT   : "

void print(const char * s1, const char * s2="", const char * s3="", const char * s4="", const char * s5="", const char * s6="", const char * s7="");
void println(const char * s1, const char * s2="", const char * s3="", const char * s4="", const char * s5="", const char * s6="", const char * s7="");
void halt(const char* m2, const char* m3, const char* m4, const char* m5);

#endif
