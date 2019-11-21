#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h> // Hardware-specific library https://github.com/adafruit/Adafruit-ST7735-Library
#include "Adafruit_miniTFTWing.h"
#include <TMC2208Stepper.h>
#include <AccelStepper.h> //http://www.airspayce.com/mikem/arduino/AccelStepper/
#include <EEPROM.h>

#define VERSION 9
#define DATE "Updated: 11/21/2019\n"
#define DIRECTION_ADDRESS 0
#define LIMIT_PIN_ASSIGNMENT_ADDRESS 1
#define TEN_ML 0.413 // microliters per 1/16th microstep for 10mL syringe
#define SIXTY_ML 1.4 // microliters per 1/16th microstep for 60mL syringe

//pinout: https://cdn-learn.adafruit.com/assets/assets/000/046/240/original/microcomputers_Adafruit_Feather_32u4_Basic_Proto_v2.3-1.png?1504884949

//---------------------------------------------TFT Display-----------------------------------------------
Adafruit_miniTFTWing ss;
#define TFT_RST    -1    // we use the seesaw for resetting to save a pin
#define TFT_CS   5
#define TFT_DC   6
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
uint16_t buttons;

//----------------------------------------TMC2208 Stepper Driver ---------------------------------------
// http://learn.watterott.com/silentstepstick/pinconfig/
const byte sw_rx = 9;
const byte sw_tx = 6;
#define R_SENSE 0.3
TMC2208Stepper driver = TMC2208Stepper(sw_rx, sw_tx); // Software serial
const byte step = 11;
const byte dir  = 10;
const byte enablePin = A0; //pin 36 PF7
AccelStepper stepper = AccelStepper(stepper.DRIVER, step, dir);
bool motorEnabled;
#define INFUSE 1
#define RETRACT 0

//-------------------------------------------Other Variables -----------------------------------
// limit switches
const byte limit_pins[2] = {12,21};
uint8_t limit_pull = limit_pins[0];
uint8_t limit_push = limit_pins[1];
uint8_t pull_is_21;

long ongoingPosition = 0;
enum buttonLocation {LEFT=3,RIGHT=7,UP=2,DOWN=4,CENTER=11,A_BTN=10,B_BTN=9};
const float resolution =  SIXTY_ML;
uint8_t softDirection = 0;
uint8_t  valsFromParse[5];

void setup()   {
  Serial1.begin(9600,SERIAL_8N1); //serial connection to pyControl

  //limit switch setup
  //A3 setup
  DDRF &= ~(1<<4); //set as input
  PORTF |= (1<<4); //enable pullup
  //D12 setup
  DDRD &= ~(1<<6); //set as input
  PORTD |= (1<<6); //enable pullup

  //--------------------------------------------------Motor setup-------------------------
  driver.beginSerial(115200);
  // Push at the start of setting up the driver resets the register to default
  driver.push();

  //set pins as outputs
  DDRF |= (1<<7); //enable pin
  DDRB |= (1<<7); //step pin
  DDRB |= (1<<6); // direction pin

  driver.rms_current(2000,1,R_SENSE);      // Set motor RMS current
  driver.mstep_reg_select(1);
  driver.mres(4);         // 0[256], 1[128], 2[64], 3[32], 4[16], 5[8], 6[4], 7[2], 8[0]. [microsteps]
  driver.toff(2);         // Enables driver in software

  stepper.setMaxSpeed(3500); // 100mm/s @ 80 steps/mm
  stepper.setAcceleration(5000); // 2000mm/s^2
  stepper.setEnablePin(enablePin);
  //get soft direction variable from non-volatile memmory
  EEPROM.get(DIRECTION_ADDRESS,softDirection);
  stepper.setPinsInverted(softDirection, false, true);

  //get limit switch pin assignments from non-volatile memmory
  EEPROM.get(LIMIT_PIN_ASSIGNMENT_ADDRESS,pull_is_21);
  if(pull_is_21>1){ // if eeprom hasn't ever been written to then it will be 255, so assign it to be 0
    pull_is_21 = 0;
    EEPROM.update(LIMIT_PIN_ASSIGNMENT_ADDRESS, pull_is_21);
  }
  limit_pull = limit_pins[pull_is_21];
  limit_push = limit_pins[!pull_is_21];
  //--------------------------------------------------Display Setup------------------
  if (!ss.begin()) {
    while(1);
  }
  ss.tftReset();   // reset the display
  ss.setBacklight(TFTWING_BACKLIGHT_ON);
  tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display

  // splash screen 
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  showMenu();
}

void loop() {
  buttons = ss.readButtons();

  //check for arrow pushes
  UI(retracting,B_BTN); //B_BTN
  UI(resetting,A_BTN); //A_BTN
  UI(pushing,UP); //up
  UI(pulling,DOWN); //down
  UI(flipDirection,CENTER); //center

  //check for serial messages
  serialUI();
  
  //disable motor if no more steps are scheduled  
  if (!stepper.isRunning()){
    stepper.disableOutputs();
  }
}

int parseData(){
  char msgData[15] = "";
  Serial1.readBytesUntil('\n',msgData,15);
  char* msgPointer;
  msgPointer = strtok(msgData,",");
  return atol(msgPointer);
}