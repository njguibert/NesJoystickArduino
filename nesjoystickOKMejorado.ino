int latch = 2; // set the latch pin
int clock = 3; // set the clock pin
int datin = 4;// set the data in pin
byte controller_data = 0;
byte cruz_data=0;
byte btn_data=0;
int ledpin = 13;
boolean btup=false;
boolean btdw=false;
boolean btlf=false;
boolean btrg=false;
boolean btsel=false;
boolean btpau=false;
boolean bt1=false;
boolean bt2=false;

JoyState_t joySt;
/* SETUP */
void setup() {
Serial.begin(9600);
pinMode(latch,OUTPUT);
pinMode(clock,OUTPUT);
pinMode(datin,INPUT);
pinMode(ledpin, OUTPUT);

digitalWrite(latch,HIGH);
digitalWrite(clock,HIGH);
  // Set joystick initial state
  joySt.xAxis = 127;
  joySt.yAxis = 127;
  joySt.zAxis = 127;
  joySt.buttons = 0;

}

/* THIS READS DATA FROM THE CONTROLLER */
void controllerRead() {
controller_data = 0;
digitalWrite(latch,LOW);
digitalWrite(clock,LOW);

digitalWrite(latch,HIGH);
delayMicroseconds(2);
digitalWrite(latch,LOW);

controller_data = digitalRead(datin);

for (int i = 1; i <= 7; i ++) {
digitalWrite(clock,HIGH);
delayMicroseconds(2);
controller_data = controller_data << 1;
controller_data = controller_data + digitalRead(datin) ;
delayMicroseconds(4);
digitalWrite(clock,LOW);
}

}

void loop() {
controllerRead();

btn_data=controller_data & B11110000;
cruz_data=controller_data & B00001111;
Serial.println(cruz_data, BIN);
//Serial.println(controller_data, BIN);

// if (controller_data==B11101111){
  // Serial.println("Button has been Pressed");   
   //}  else {
   //Serial.println("Button not pressed");
   //}

//for REFERENCE:  
//UP = 11110111
//DOWN=11111011
//LEFT=11111101
//RIGHT=11111110
//SELECT=11011111
//START=11101111
//A=01111111
//B=10111111

//=======================UP==================================
if (cruz_data==B00000111 && !btup){
 joySt.yAxis = 0;
 digitalWrite(ledpin, HIGH);   
 btup=true;
 }
if (cruz_data==B00001111 && btup){
 digitalWrite(ledpin, LOW);   
 btup=false;
 joySt.yAxis = 127;
 }
//===========================================================
//=======================DOWN================================
if (cruz_data==B00001011 && !btdw){
 digitalWrite(ledpin, HIGH);   
 btdw=true;
 joySt.yAxis = 255; 
 }
if (cruz_data==B00001111 && btdw){
 digitalWrite(ledpin, LOW);   
 btdw=false;
 joySt.yAxis = 127; 
 }
//===========================================================
//=======================LEFT================================
if (cruz_data==B00001101 && !btlf){
 digitalWrite(ledpin, HIGH);   
 btlf=true;
 joySt.xAxis = 0;
 }
if (cruz_data==B00001111 && btlf){
 digitalWrite(ledpin, LOW);   
 btlf=false;
 joySt.xAxis = 127;
 }
//===========================================================
//=======================RIGHT===============================
if (cruz_data==B00001110 && !btrg){
 digitalWrite(ledpin, HIGH);   
 btrg=true;
 joySt.xAxis = 255;
 }
if (cruz_data==B00001111 && btrg){
 digitalWrite(ledpin, LOW);   
 btrg=false;
 joySt.xAxis = 127;
 }
//===========================================================
//=======================SELECT==============================
if (btn_data==B11010000 && !btsel){
 digitalWrite(ledpin, HIGH);   
 btsel=true;
 joySt.buttons = joySt.buttons | 8; 
 }
if (btn_data==B11110000 && btsel){
 digitalWrite(ledpin, LOW);   
 btsel=false;
   joySt.buttons = joySt.buttons & 247;
 }
//===========================================================
//=======================PAUSE===============================
if (btn_data==B11100000 && !btpau){
 digitalWrite(ledpin, HIGH);   
 btpau=true;
 joySt.buttons = joySt.buttons | 4;
 }
if (btn_data==B11110000 && btpau){
 digitalWrite(ledpin, LOW);   
 btpau=false;
  joySt.buttons = joySt.buttons & 251;
 }
//===========================================================
//=======================BOTON1==============================
if (btn_data==B01110000 && !bt1){
 digitalWrite(ledpin, HIGH);   
 bt1=true;
  joySt.buttons = joySt.buttons | 1;
 }
if (btn_data==B11110000 && bt1){
 digitalWrite(ledpin, LOW);   
 bt1=false;
 joySt.buttons = joySt.buttons & 254;
 }
//===========================================================
//=======================BOTON2==============================
if (btn_data==B10110000 && !bt2){
 digitalWrite(ledpin, HIGH);   
 bt2=true;
 joySt.buttons = joySt.buttons | 2;
 }
if (btn_data==B11110000 && bt2){
 digitalWrite(ledpin, LOW);   
 bt2=false;
 joySt.buttons = joySt.buttons & 253;
 }
//============================================================
Joystick.setState(&joySt);

delay(100);

}
