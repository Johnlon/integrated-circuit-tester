#include "io.h"


/* truncates line if exceeds MAX_LEN */
char * readline() {
  const int MAX_LEN = 100;
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
  }
  
  // not reached
}
