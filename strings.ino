
char * itoa(int i) {
  static char buf[16+1];
  return itoa(i, buf, 10);
}

char * ctoa(char c) {
  static char buf[2] = "";
  buf[0] = c;
  buf[1] = 0;
  return buf;
}

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
