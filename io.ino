#include "io.h"

void print(const char * s1, const char * s2, const char * s3, const char * s4, const char * s5, const char * s6, const char * s7) {
  Serial.print(s1);
  Serial.print(s2); 
  Serial.print(s3); 
  Serial.print(s4); 
  Serial.print(s5); 
  Serial.print(s6); 
  Serial.print(s7); 
}

void println(const char * s1, const char * s2, const char * s3, const char * s4, const char * s5, const char * s6, const char * s7) {
  print(s1,s2, s3, s4, s5, s6, s7);
  Serial.println(""); 
}

void halt(const char* m1, const char* m2, const char* m3, const char* m4, const char* m5) {
    println(HALT, m1, m2, m3, m4, m5);
    while (1) {
        delay(100000);
    }
}

/* truncates line if exceeds MAX_LEN */
char * readline() {
  static const int MAX_LEN = 100;
  static char buffer[MAX_LEN+1] = "";
  return readline(buffer, MAX_LEN);
}

/* truncates line if exceeds maxLen */
char * readline(char* buffer, int maxLen) {

  static boolean lastWasCr = false; // used to allow skipping empty lines
  
  buffer[0] = '\0';
  
  while (1) {
    while (Serial.available() > 0) { 
      int c = Serial.read();
      if (c == '\n' || c == '\r') {
        if (lastWasCr) break; // read again    
        lastWasCr = true;
        return buffer;
      } 
      
      lastWasCr = false;
      int l = strlen(buffer);
      if (l < maxLen) {
        buffer[l] = c;
        buffer[l+1] = '\0';
      }
    }
    delay(10);
  }
  
  // not reached
}
