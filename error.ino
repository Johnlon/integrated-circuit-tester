void error(String msg) {
    Serial.print("ERROR: " + msg);
}
void errorln(String msg) {
    Serial.println("ERROR: " + msg);
}

void halt(String msg) {
    Serial.println("halted");
    Serial.println(msg);
    while (1) {
        delay(1000);
        Serial.print(".");
    }
}
