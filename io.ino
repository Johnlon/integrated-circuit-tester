#include "io.h"

/* truncates line if exceeds maxLen */
char * readlineI(char* buffer, int maxLen) {
  
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


/* truncates line if exceeds maxLen */
char * readline(char* buffer, int maxLen) {
  Serial.print(F("READY > "));
  
  char* ret = readlineI(buffer, maxLen);
  //Serial.println(ret);
  
  return ret;
}
