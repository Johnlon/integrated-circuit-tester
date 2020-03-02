
void setup() {
  Serial.begin(57600);

  mcp_setup();
  
  interactive();
  //identify(true);
 
  //decay(); 
  //emptySocket();
  //barLedTestPattern();

  reset();
  delay(1000000);
}
void loop() {}
