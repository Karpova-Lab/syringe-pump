/*
Syringe pump
By: Andy Lustig
Date: 2018-08-22
https://karpova-lab.github.io/syringe-pump/index.html
*/

#define VERSION 8

#define TEN_ML 0.379 // microliters per 1/16th microstep for 10mL syringe
#define SIXTY_ML 1.327 // microliters per 1/16th microstep for 60mL syringe

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD130632.h>
#include <AccelStepper.h> //http://www.airspayce.com/mikem/arduino/AccelStepper/

//Display Variables
Adafruit_SSD1306 display = Adafruit_SSD1306();
#define pushMSG F("A: Push")
#define pullMSG F("B: Pull")
#define retractMSG F("C: Retracting")
#define resetMSG F("C: Reset Dispensed")

// TMC2208 Stepper Driver 
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

//ttl pins
const byte ttlPush = A5; //ttl output 1 (A: RJ45 pin 3).
const byte ttlRetract = A3; //ttl output 2 (C: RJ45 pin 2).
const byte refillStatus = A4; //ttl input 1 (B: RJ45 pin 1). 

long dispenseVolume = 200; //microliters 
long ongoingPosition = 0;

const float resolution =  SIXTY_ML;
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
  stepper.setMaxSpeed(3500);
  stepper.setAcceleration(5000);
  pinMode( enablePin, OUTPUT ); 
  enableMotor();
  //ttl setup
  pinMode(ttlPush,INPUT);
  pinMode(ttlRetract,INPUT);
  pinMode(refillStatus,OUTPUT);
  digitalWrite(refillStatus,LOW);


  display.print(F("Firmware Version:"));
  display.print(VERSION);
  display_then_clearBuff();
  delay(1500);
  mainMenu();
}

void loop() {

  //Check for commands
  checkButton(TOP);
  checkButton(MIDDLE);
  checkButton(BOTTOM);
  if (digitalRead(ttlPush)){
    holdAction(TOP);
    mainMenu();
  }
  if (digitalRead(ttlRetract)){
    holdAction(MIDDLE);
    mainMenu();
  }

  //run motor if a step is scheduled to be executed, otherwise do nothing.
  stepper.run();

  //stop motor if a limit switch is reached
  if(stepper.isRunning() && !digitalRead(limit_push)){
    limitReached();
    mainMenu();
  }
  if(stepper.isRunning() && !digitalRead(limit_pull)){
    limitReached();
    mainMenu();
  }

  //disable motor if no more steps are scheduled  
  if (!stepper.isRunning() && motorEnabled){
    disableMotor();
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
  while(!digitalRead(btnPins[action]) | digitalRead(ttlPush) | digitalRead(ttlRetract)){
    stepper.run();
    switch (action){
      case TOP: //Push
        if(digitalRead(limit_push)){
          if (stepper.distanceToGo() < 8000){
            stepper.move(100000);
          }
        }
        else{
          limitReached();
        }
        break;
      case MIDDLE: //Pull
        if (digitalRead(limit_pull)){
          if (stepper.distanceToGo() > -8000){
            stepper.move(-100000);
          }
        }
        else{
          limitReached();
        }
        break;
      case BOTTOM:
        retract();
        break;
    }
  }
  ongoingPosition += long(stepper.currentPosition());
  stopImmediately();
}

void clickAction(byte action){
  enableMotor();
  showChoice(action);
  switch (action){
    case TOP: //Push
      stepper.move(long(dispenseVolume/resolution));
      ongoingPosition += long(dispenseVolume/resolution);
      break;
    case MIDDLE: //Pull
      stepper.move(-long(dispenseVolume/resolution));
      ongoingPosition += -long(dispenseVolume/resolution);
      break;
    case BOTTOM: //Reset dispensed volume to 0 uL dispensed
      ongoingPosition = 0;
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
      display.print(resetMSG);
      break;
    case 3: //fast push
      display.println(pushMSG);
      break;
    case 4: //fast pull
      display.println();
      display.println(pullMSG);
      break;
    case 5: //fast pull
      display.println();
      display.println();
      display.print(retractMSG);
      break;
  }
  display_then_clearBuff();
}

void mainMenu(){ //takes about 16ms to refresh the menu
  // display.print(F("   Reward = "));
  // display.print(dispenseVolume);  
  display.print(F(" Dispensed = "));
  display.print(int(ongoingPosition*resolution));  
  display.println(F(" uL"));
  display.println(pushMSG);
  display.println(pullMSG);
  display.print(resetMSG);
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

void retract(){
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
      stepper.setCurrentPosition(0);// stop the motor
      display.print(F("Limit Reached"));
      display_then_clearBuff();
      stepper.move(250); //bounce off the limit switch
      while(stepper.isRunning()){
        stepper.run();
      }
      delay(1000);
      stepper.setCurrentPosition(0);
      ongoingPosition = 0;//reset dispensed volume to 0
      break;
    }
  }
}

void stopImmediately(){
    stepper.setCurrentPosition(0);
}

void slowStop(){
  stepper.stop();
  while(stepper.isRunning()){
    stepper.run();
  }
}


// if (digitalRead(ttlPush)){
//   long ttlSignalClock = millis();
//   while (digitalRead(ttlPush)){
//     //wait for signal to go back low
//   }
//   ttlSignalClock = millis()-ttlSignalClock;
//   if (ttlSignalClock>20){ //update dispenseVolume
//     updateRewardVolume(ttlSignalClock);
//   }
//   else{//dispense
//     clickAction(TOP);
//   }    
//   mainMenu();
// }

// void updateRewardVolume(long rewardLength){
//   int multiple = 10;
//   dispenseVolume = rewardLength  + multiple/2;
//   dispenseVolume -= dispenseVolume % multiple;
//   dispenseVolume *= 1/10.0; //microliters to dispense
// }