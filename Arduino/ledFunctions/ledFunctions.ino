///////////////////////////////////////////////////////////////////////TRANSMISSION FUNCTIONS
void bitSend(bool out){
  if(out){
    PORTB |= B00001000;
    //Delay 0.8125 us
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB &= B11110111;
    //Delay 0.5625 us
     __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
  }
  else{
    PORTB |= B00001000;
    PORTB &= B11110111;
    //Delay 0.375 us
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB &= B11110111;
    // Delay 0.75 us
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    //
  }
}
void latch(){
  PORTB &= B11110111;
  delayMicroseconds(51);
}
void blastData(){
  noInterrupts();
  for(int i=0; i<GRB_SIZE; ++i){
    bitSend(GRB[i]);
  }
  latch();
  interrupts();
}
///////////////////////////////////////////////////////////////////ARRAY FUNCTIONS
void writeBit(bool val, int pos, int color, int pixel){
  GRB[24*pixel + color*8 + (7-pos) ] = val;
}
byte isolateBit(byte val, int pos){
  val &= 1 << pos;
  val>>pos;
  return val;
}
void writeByte(byte val, int color, int pixel){
  for(int i=0; i<8; ++i){
    byte insert = isolateBit(val,i);
    writeBit(insert,i,color,pixel);
  }
}
void writePixel(byte green, byte red, byte blue, int pixel){
  writeByte(green,0,pixel);
  writeByte(red,1,pixel);
  writeByte(blue,2,pixel);
}
////////////////////////////////////////////////////////////// COLOR PATTERNS
void setAllWhite(){
  for(int i=0; i<NUM_LED; ++i){
    writePixel(153,153,153,i);
  }
  blastData();
}
void setOff(){
  for(int i=0; i<NUM_LED; ++i){
    writePixel(0,0,0,i);
  }
  blastData();
}
void setPulseRed(){
int pulse = 6;
 for(int iter=0; iter<3; ++iter){
  for(int i=0; i<NUM_LED; ++i){
    writePixel(0,pulse,0,i);
  }
  blastData();
  pulse *= pulse;    
  }
}
void setPulseGreen(){
int pulse = 6;
 for(int iter=0; iter<3; ++iter){
  for(int i=0; i<NUM_LED; ++i){
    writePixel(pulse,0,0,i);
  }
  blastData();
  pulse *= pulse;    
  }
}
/////////////////////////////////////////////////////////////
