
char* fill(char* buf, int bufSize, char f) {
  if (bufSize > 0) {
    for (int i=0; i<bufSize; i++) {
      buf[i] = f;  
    }
    buf[bufSize-1] = '\0';
  }
  return buf;
}

char* pad(char* buf, int bufSize, char f) {
  int len = strlen(buf);
  int add = bufSize - len;
  char * r = fill((buf+len), add, f);
  
  return buf;
}

/*
- Fills the given buffer with a token if there was one and returns the number of chars read in the token.
- If no token was found then return 0
- If the token is longer than the buffer then fill the buffer with whatever fits and return the length of the complete token,
  in this case the rest of the token is ignored (read and thrown away), and the next call will start at the next token.

Note:
First arg is expected to be a direct 
F("string") which is of type __FlashStringHelper* or a
a value known to be a 'const char * const XXXX PROGMEM = "string"' in which case cast it to __FlashStringHelper* to call this.

PROGMEM is enough to ensure the string enters the EEPROM however the __FlashStringHelper identifies this param 
as having to be one of the above.
*/

int tokenise(const __FlashStringHelper * fsh, const char delimiter , char *buffer, size_t bufLength)
{
  char *s = (char *) fsh;
  static const char *str = NULL;

  if (s != NULL) {
    str = s;
  }

  if (str == NULL) {
  //  Serial.println("T:1");
    // Need a new string
    buffer[0] = '\0';
    return -1;
  }

  size_t buffIndex = 0;

  while (1) {
    char c = pgm_read_byte(str++);

    // Serial.print("R");
    // Serial.print(c);
    
    if (c == '\0') {
      str = NULL; // Reached end of string
      buffer[buffIndex] = '\0';
      return buffIndex;
    }

    if (c == delimiter) {
      buffer[buffIndex] = '\0';
      return buffIndex;
    }

    if (buffIndex < bufLength - 1) {
      buffer[buffIndex++] = c;
    }
  }
}
