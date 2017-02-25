/*
Syringe pump
By: Andy Lustig
Date: 2017-02-25
http://andybuilds.com/projects/Syringe%20Pump/syringe/
*/

#define VERSION 1

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD130632.h>
//for SD card
#include <SPI.h>
#include <SD.h>
File root;

//Display Variables
Adafruit_SSD1306 display(9);
const byte reedSwitch = 17;
const byte btnPins[3] = {0,1,16};
bool refresh = false;
#define pushMSG F("A: Push")
#define pullMSG F("B: Pull")
#define retractMSG F("C: Retract")

//Stepper Motor variables
#define stp 3
#define dir 2
#define MS1 4
#define MS2 5
#define EN  6
#define FULL    0  //Microstep Resolution Truth Table is on pg.3 of A3957 datasheet.
#define HALF    2
#define QTR     1
#define EIGHTH  3
#define TOP     0
#define MIDDLE  1
#define BOTTOM  2
#define PUSH 1
#define PULL 0
const float minResolution = 0.002655; //minimum resolution in mL
float volumePushed = 0;
const unsigned int syringeVolume = 22599; // # of microsteps in 60 mL syringe (60.0e^-3)/2.655e^-6)

//SD card
#define chipSelect 7
char readBuffer[100];

//mbed pins
const byte mbedPush = 14; //mbed output 1 (A)
const byte mbedRetract = 15; //mbed output 2 (C)
const byte refillStatus = 10; //mbed input 1 (B)

//Syringe varibales
#define click_push 2
#define click_pull 3
unsigned int volume[4] = {38,38,188,188};

void limitReached(bool isPushing=false);
void printDirectory(File directory, int numTabs);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(btnPins[TOP],INPUT_PULLUP);
  pinMode(btnPins[MIDDLE], INPUT_PULLUP);
  pinMode(btnPins[BOTTOM], INPUT_PULLUP);
  pinMode(reedSwitch,INPUT_PULLUP);
  delay(300); //feather oled display charge pump needs time to stablize. see: https://forums.adafruit.com/viewtopic.php?f=57&t=100042&start=15
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // Clear the buffer.
  display.clearDisplay();
  display_then_clearBuff();

  //Motor setup
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);

  pinMode(mbedPush,INPUT);
  pinMode(mbedRetract,INPUT);
  pinMode(refillStatus,OUTPUT);
  digitalWrite(refillStatus,LOW);
  rstStepperPins(); //Set step, direction, microstep and enable pins to default states

  //  //SD setup
  //  if (!SD.begin(chipSelect)) {
  //    display.println(F("No SD Card"));
  //  }
  //  else{
  //    display.println(F("SD Iniitialized!"));
  //    root = SD.open("/");
  //    printDirectory(root, 0);
  //    // getContents();
  //  }
  //  display_then_clearBuff();
  //  delay(5000);
  display.print(F("Firmware Version:"));
  display.print(VERSION);
  display_then_clearBuff();
  delay(2000);
  mainMenu();
}

void loop() {
  checkButton(TOP);
  checkButton(MIDDLE);
  checkButton(BOTTOM);
  if (digitalRead(mbedPush)){
    turnMotor(EIGHTH,PUSH);
    rstStepperPins();
    mainMenu();
  }
  if (digitalRead(mbedRetract)){
   clickAction(BOTTOM);
   mainMenu();
  }
}

void printDirectory(File directory, int numTabs) {
  while (true) {
    File entry =  directory.openNextFile();
    if (! entry) {
      // no more files
      display.println("no files?");
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      display.print('\t');
    }
    display.print(entry.name());
    if (entry.isDirectory()) {
      display.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      display.print("\t\t");
      display.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void getContents(){
  File dataFile = SD.open("config.txt", FILE_READ);
  if (dataFile) {
    //read in char data
    byte count = 0;
    while (dataFile.available()) {
      readBuffer[count] = dataFile.read();
      count++;
    }
    dataFile.close();
    //parse buffer
    String contents = "";
    byte parameter = 0;
    for (byte i = 0; i<count; i++){
      if (isDigit(readBuffer[i])) {
        contents += (char)readBuffer[i];
      }
      else if (readBuffer[i]==59){
        volume[parameter] = contents.toInt();
        parameter++;
        contents = "";
      }
    }
    display.println(F("\nValues read:"));
    display.print(volume[0]);
    for (byte i = 1; i <4; i++){
      display.print(", ");
      display.print(volume[i]);
    }
  }
  else{
    display.println(F("Error: no config.txt"));
  }
}

void display_then_clearBuff(){
    display.setTextColor(1,0);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.display();
    display.clearDisplay();
}

void checkButton(byte button){
  unsigned int holdTime = 0;
  unsigned int holdThresh = 350;
  if (!digitalRead(btnPins[button])){     // button has been pressed
    while(!digitalRead(btnPins[button])){
      delay(1);
      holdTime++;
      if (holdTime>=holdThresh){  //Button is being held down
        holdAction(button);
        mainMenu();
      }
    }
    if (holdTime<holdThresh){ //Button was only clicked
      clickAction(button);
      mainMenu();
    }
    rstStepperPins();
  }
  else{ //button wasn't pressed
  }
}

void holdAction(byte action){
  showChoice(action+3);
  while(!digitalRead(btnPins[action])){
    switch (action){
      case TOP: //Push
        if(volumePushed<syringeVolume){
          volumePushed += turnMotor(QTR,5,PUSH);
        }
        else{
          limitReached(1);
        }
        break;
      case MIDDLE: //Pull
        if (digitalRead(reedSwitch)){
          volumePushed += turnMotor(QTR,5,PULL);
        }
        else{
          limitReached();
        }
        break;
    }
  }
  rstStepperPins();
}

void clickAction(byte action){
  showChoice(action);
  switch (action){
    case TOP: //Push
      if(volumePushed<syringeVolume){
        volumePushed += turnMotor(EIGHTH,volume[click_push],PUSH);
        rstStepperPins();
        delay(150);
      }
      else{
        limitReached(1);
      }
      break;
    case MIDDLE: //Pull
      if (digitalRead(reedSwitch)){
        volumePushed += turnMotor(EIGHTH,volume[click_pull],PULL);
        rstStepperPins();
        delay(150);
      }
      else{
        limitReached();
      }
      break;
    case BOTTOM: //Retract
      digitalWrite(refillStatus,HIGH);
      while(1){
        if (!digitalRead(reedSwitch)){
          digitalWrite(refillStatus,LOW);
          rstStepperPins();
          limitReached();
          break;
        }
        else{
          volumePushed += turnMotor(QTR,10,PULL);
        }
      }
      break;
  }
}

void showChoice(byte choice){
  display.println();
  switch (choice){
    case 0: //step push
      display.println(pushMSG);
      break;
    case 1: //step pull
      display.println();
      display.println(pullMSG);
      break;
    case 2: //full retract
      display.println();
      display.println();
      display.print(retractMSG);
      break;
    case 3: //fast push
      display.println(pushMSG);
      break;
    case 4: //fast pull
      display.println();
      display.println(pullMSG);
      break;
  }
  display_then_clearBuff();
}

void mainMenu(){ //takes about 16ms to refresh the menu
  display.print("  --");
  display.print(volumePushed*minResolution);
  display.println(F(" mL pushed--"));
  display.println(pushMSG);
  display.println(pullMSG);
  display.print(retractMSG);
  display_then_clearBuff();
}

float turnMotor(byte resolution, int steps,bool myDIR){
  digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
  digitalWrite(dir, myDIR); //Pull direction pin low to move "forward"
  digitalWrite(MS1, resolution >> 1); //set resolution
  digitalWrite(MS2, resolution & 1);
  for(int x= 1; x<steps; x++){
    digitalWrite(stp,HIGH);
    delay(1);
    digitalWrite(stp,LOW);
    delay(1);
  }
  byte multiplier;
  switch (resolution){
    case EIGHTH:
      multiplier = 1;
      break;
    case QTR:
      multiplier = 2;
      break;
    case HALF:
      multiplier = 4;
      break;
    case FULL:
      multiplier = 8;
      break;
  }
  if (myDIR){
    return steps*multiplier;
  }
  else{
    return steps*multiplier*-1;
  }
}

void turnMotor(byte resolution,bool myDIR){
  digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
  digitalWrite(dir, myDIR); //Pull direction pin low to move "forward"
  digitalWrite(MS1, resolution >> 1); //set resolution
  digitalWrite(MS2, resolution & 1);
  while(digitalRead(mbedPush) && volumePushed<syringeVolume){ //at EIGHTH resolution we get 0.00265 mL / 2ms. for 100 microliter reward, turn on for 76ms
    digitalWrite(stp,HIGH);
    delay(1);
    digitalWrite(stp,LOW);
    delay(1);
    volumePushed++;
  }
}

//Reset Stepper Driver pins to default states
void rstStepperPins(){
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}

void limitReached(bool isPushing=false){
  if(!isPushing){
    volumePushed = 0;
  }
  display.print(F("Limit Reached"));
  display_then_clearBuff();
  delay(1000);
}
