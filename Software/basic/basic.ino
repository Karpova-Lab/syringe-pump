#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h> // Hardware-specific library https://github.com/adafruit/Adafruit-ST7735-Library
#include "Adafruit_miniTFTWing.h"
#include <AccelStepper.h> //http://www.airspayce.com/mikem/arduino/AccelStepper/

#define DATE "Updated: 10/02/2018\n"

#define BPOD  //only uses 1 TTL output
#define TEN_ML 0.379 // microliters per 1/16th microstep for 10mL syringe
#define SIXTY_ML 1.327 // microliters per 1/16th microstep for 60mL syringe

//Display
Adafruit_miniTFTWing ss;
#define TFT_RST    -1    // we use the seesaw for resetting to save a pin
#define TFT_CS   5
#define TFT_DC   6
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
int triangleHeight = 15;
int triangle_offsetFromBottom = 5;
uint32_t buttons;

// TMC2208 Stepper Driver 
// http://learn.watterott.com/silentstepstick/pinconfig/
AccelStepper stepper(AccelStepper::DRIVER, 11, 10); //(stp,dir)
const byte enablePin = A0;
bool motorEnabled;

// limit switches
const byte limit_pull = 12;
const byte limit_push = A1;

//TTL pins
const byte ttlPush = A5; //TTL output 1 (A: RJ45 pin 3).
const byte ttlRetract = A3; //TTL output 2 (C: RJ45 pin 2).
const byte refillStatus = A4; //TTL input 1 (B: RJ45 pin 1). 

// //Indicator LED
// const byte indicatorLED = 13;

long ongoingPosition = 0;
enum buttonLocation {LEFT=3,RIGHT=7,UP=2,DOWN=4,CENTER=11};
const float resolution =  SIXTY_ML;
bool softDirection = 0;

void setup()   {
  Serial.begin(115200);

  //limit switch setup
  pinMode(limit_pull,INPUT_PULLUP);
  pinMode(limit_push,INPUT_PULLUP);  

  //Motor setup
  stepper.setMaxSpeed(3500);
  stepper.setAcceleration(5000);
  pinMode(enablePin,OUTPUT); 
  enableMotor();

  //TTL setup
  pinMode(ttlPush,INPUT);
  pinMode(ttlRetract,INPUT);
  pinMode(refillStatus,OUTPUT);
  digitalWrite(refillStatus,LOW);
  
  // //LED setup
  // pinMode(indicatorLED,OUTPUT);

  //Display Setup
  if (!ss.begin()) {
    Serial.println("seesaw couldn't be found!");
    while(1);
  }
  Serial.print("seesaw started!\tVersion: ");
  Serial.println(ss.getVersion(), HEX);

  ss.tftReset();   // reset the display
  ss.setBacklight(TFTWING_BACKLIGHT_ON);
  tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display
  Serial.println("TFT initialized");

  tft.fillScreen(ST77XX_RED);
  delay(15);
  tft.fillScreen(ST77XX_GREEN);
  delay(15);
  tft.fillScreen(ST77XX_BLUE);
  delay(15);
  tft.fillScreen(ST77XX_BLACK);

  showMenu(ST77XX_WHITE,ST77XX_WHITE,ST77XX_GREEN);
}

void loop() {
  buttons = ss.readButtons();
  // Serial.println(buttons, BIN);

  buttonUI(firmware,10,ST77XX_YELLOW,ST77XX_BLACK); //about
  buttonUI(showButtonMap,9,ST77XX_BLACK,ST77XX_YELLOW); //help


  arrowUI(pushing,LEFT); //left
  arrowUI(pulling,RIGHT); //right
  arrowUI(retracting,UP); //up
  arrowUI(resetting,DOWN); //down
  arrowUI(flipDirection,CENTER); //center


  //run motor if a step is scheduled to be executed, otherwise do nothing.
  stepper.run();

  //disable motor if no more steps are scheduled  
  if (!stepper.isRunning() && motorEnabled){
    disableMotor();
  }
}