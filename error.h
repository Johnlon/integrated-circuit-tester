#ifndef ERROR_FN
#define ERROR_FN

void error(const String& msg) {
    Serial.print("ERROR: " + String(msg));
}
void errorln(const String& msg) {
    Serial.println("ERROR: " + String(msg));
}

void halt(const String& msg) {
    Serial.println("");
    errorln(msg);
    Serial.println("halted");
    while (1) {
      delay(1000000);
    }
}
#endif