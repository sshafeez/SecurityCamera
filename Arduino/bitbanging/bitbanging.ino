//1 Nop is 62.5 ns, make sure to disable interrupts. Determined from 16 MHz, a nop is 62.4 ns for one cycle
//__asm__("nop\n\t"); Inline Assembly

#define NUM_LED 60
#define GRB_SIZE NUM_LED*3*8
bool GRB[GRB_SIZE];

#define PIRpin 4 //digital
#define LDRpin 0 //analog
#define LDRthresh 300 //in series with 10k reading voltage across the 10k
//LEDpin is 11

void setup() {
DDRB |= B00001000;
Serial.begin(9600);
pinMode(PIRpin,INPUT);
pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  while(true){
    setOff();
    delay(500);
    setAllWhite();
    delay(500);
  }
  digitalWrite(LED_BUILTIN,LOW);
  while (true){
    if (Serial.available()){break;}
  }
  char dump = Serial.read();
  digitalWrite(LED_BUILTIN,HIGH);
  while (true){ //Wait for motion
    if (digitalRead(PIRpin)) {break;}
  }
  digitalWrite(LED_BUILTIN,LOW);
  if (analogRead(LDRpin)<300) {setAllWhite();} //fill light
  Serial.println(5);
  while (true) { //wait for rpi to hear back from api
    if (Serial.available()) {break;}
  }
  char reply = Serial.read();
  if (reply=='p') {
    setPulseGreen();
    setOff();
  }
  else {
    setPulseRed();
    setOff();
  }
  delay(10000);

}

