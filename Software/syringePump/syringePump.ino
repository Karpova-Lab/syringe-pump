/*
Syringe pump
By: Andy Lustig
Date: 2018-05-17
http://andybuilds.com/projects/Syringe%20Pump/syringe/
*/

#define VERSION 7
#define RESOLUTION 1.327 //1.327 microliters per 1/16th microstep

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD130632.h>
#include <AccelStepper.h> //http://www.airspayce.com/mikem/arduino/AccelStepper/

//Display Variables
Adafruit_SSD1306 display = Adafruit_SSD1306();
#define pushMSG F("A: Push")
#define pullMSG F("B: Pull")
#define retractMSG F("C: Full Retract")

// Stepper Driver
// http://learn.watterott.com/silentstepstick/pinconfig/
AccelStepper stepper(AccelStepper::DRIVER, 11, 10); //(stp,dir)
const byte enablePin = A0;
bool motorEnabled;

// limit switches
const byte limit_pull = 12;
const byte limit_push = A1;

// buttons
const byte btnPins[3] = {9,6,5};
enum buttonLocation {TOP,MIDDLE,BOTTOM};
int debounceTime = 200;

//mbed pins
const byte mbedPush = A5; //mbed output 1 (A) . FeatherM0:A5
const byte mbedRetract = A3; //mbed output 2 (C). FeatherM0:A3
const byte refillStatus = A4; //mbed input 1 (B). FeatherM0:A4

long dispenseVolume = 250; //microliters 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  Serial.println("Ready.");
  //OLED feather setup
  pinMode(btnPins[TOP],INPUT_PULLUP);
  pinMode(btnPins[MIDDLE], INPUT_PULLUP);
  pinMode(btnPins[BOTTOM], INPUT_PULLUP);
  pinMode(limit_pull,INPUT_PULLUP);
  pinMode(limit_push,INPUT_PULLUP);  

  delay(300); //feather oled display charge pump needs time to stablize. see: https://forums.adafruit.com/viewtopic.php?f=57&t=100042&start=15
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display_then_clearBuff();

  //Motor setup
  stepper.setMaxSpeed(5000);
  stepper.setAcceleration(1500);
  pinMode( enablePin, OUTPUT );  // now we're sourcing current, i.e. GND
  enableMotor();
  //mbed setup
  pinMode(mbedPush,INPUT);
  pinMode(mbedRetract,INPUT);
  pinMode(refillStatus,OUTPUT);
  digitalWrite(refillStatus,LOW);


  display.print(F("Firmware Version:"));
  display.print(VERSION);
  display_then_clearBuff();
  delay(1500);
  mainMenu();
}

void loop() {
  stepper.run();
  if(stepper.isRunning() && !digitalRead(limit_push)){
    limitReached();
    mainMenu();
  }
  if(stepper.isRunning() && !digitalRead(limit_pull)){
    limitReached();
    mainMenu();
  }
  checkButton(TOP);
  checkButton(MIDDLE);
  checkButton(BOTTOM);

  if (digitalRead(mbedPush)){
    long mbedSignalClock = millis();
    while (digitalRead(mbedPush)){
      //wait for signal to go back low
    }
    mbedSignalClock = millis()-mbedSignalClock;
    if (mbedSignalClock>20){ //update dispenseVolume
      updateRewardVolume(mbedSignalClock);
    }
    else{//dispense
      clickAction(TOP);
    }    
    mainMenu();
  }
  // if (digitalRead(mbedRetract)){
  //   while(digitalRead(mbedRetract)){
  //     delay(10);  //wait for signal to go back low;
  //   }
  //   // clickAction(BOTTOM);
  //   // mainMenu();
  // }
  if (!stepper.isRunning() && motorEnabled){
    disableMotor();
  }
}

void updateRewardVolume(long rewardLength){
  int multiple = 10;
  dispenseVolume = rewardLength  + multiple/2;
  dispenseVolume -= dispenseVolume % multiple;
  dispenseVolume *= 1/10.0; //microliters to dispense
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
    // enableMotor();
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
    delay(debounceTime);
  }
  else{ //button wasn't pressed
  }
}

void holdAction(byte action){
  enableMotor();
  showChoice(action+3);
  while(!digitalRead(btnPins[action])){
    stepper.run();
    switch (action){
      case TOP: //Push
        if(digitalRead(limit_push)){
          if (stepper.distanceToGo() < 800){
            stepper.move(1000);
          }
        }
        else{
          limitReached();
        }
        break;
      case MIDDLE: //Pull
        if (digitalRead(limit_pull)){
          if (stepper.distanceToGo() > -800){
            stepper.move(-1000);
          }
        }
        else{
          limitReached();;
        }
        break;
    }
  }
  stepper.setCurrentPosition(0);
}

void clickAction(byte action){
  enableMotor();
  showChoice(action);
  switch (action){
    case TOP: //Push
      stepper.move(long(dispenseVolume/RESOLUTION));break;
    case MIDDLE: //Pull
      stepper.move(-long(dispenseVolume/RESOLUTION));break;
    case BOTTOM: //Retract
      digitalWrite(refillStatus,HIGH);
      while(1){
        stepper.run();
        if (digitalRead(limit_pull)){
          if (stepper.distanceToGo() > -800){
            stepper.move(-1000);
          }
        }
        else{
          digitalWrite(refillStatus,LOW);
          stepper.setCurrentPosition(0);
          display.print(F("Limit Reached"));
          display_then_clearBuff();
          stepper.move(int(300/RESOLUTION)); //bounce off the limit switch
          while(stepper.isRunning()){
            stepper.run();
          }
          delay(1000);
          break;
        }
      }
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
  display.print(F("   Reward = "));
  display.print(dispenseVolume);  
  display.println(F(" uL"));
  display.println(pushMSG);
  display.println(pullMSG);
  display.print(retractMSG);
  display_then_clearBuff();
}


void limitReached(){
  stepper.setCurrentPosition(0);
  display.print(F("Limit Reached"));
  display_then_clearBuff();
  delay(1000);
}

void enableMotor(){
  motorEnabled = true;
  digitalWrite(enablePin,LOW);
}

void disableMotor(){
  digitalWrite(enablePin,HIGH);  
  motorEnabled = false;
}