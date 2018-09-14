#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h> // Hardware-specific library https://github.com/adafruit/Adafruit-ST7735-Library
#include "Adafruit_miniTFTWing.h"

Adafruit_miniTFTWing ss;
#define TFT_RST    -1    // we use the seesaw for resetting to save a pin
#define TFT_CS   5
#define TFT_DC   6

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
int triangleHeight = 15;
int triangle_offsetFromBottom = 5;
uint32_t buttons;

void setup()   {
  Serial.begin(115200);

  // while (!Serial) {
  //   delay(10);  // Wait until serial console is opened
  // }

  if (!ss.begin()) {
    Serial.println("seesaw couldn't be found!");
    while(1);
  }

  Serial.print("seesaw started!\tVersion: ");
  Serial.println(ss.getVersion(), HEX);

  ss.tftReset();   // reset the display
  ss.setBacklight(TFTWING_BACKLIGHT_ON);  // turn off the backlight

  tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display
  Serial.println("TFT initialized");

  tft.setRotation(3);

  tft.fillScreen(ST77XX_RED);
  delay(25);
  tft.fillScreen(ST77XX_GREEN);
  delay(25);
  tft.fillScreen(ST77XX_BLUE);
  delay(25);
  tft.fillScreen(ST77XX_BLACK);

  showMenu(ST77XX_WHITE,ST77XX_WHITE);


}

void loop() {
  delay(10);
  buttons = ss.readButtons();
  Serial.println(buttons, BIN);

  if (!(buttons & 1<<10)) {
    while(!(buttons & 1<<10)){
      firmware(ST77XX_WHITE);
      showMenu(ST77XX_GREEN,ST77XX_BLACK);
      buttons = ss.readButtons();
    }
    firmware(ST77XX_BLACK);
    showMenu(ST77XX_WHITE,ST77XX_WHITE);
  }

  if (!(buttons & 1<<9)) {
    while(!(buttons & 1<<9)){
      rightArrow(ST77XX_WHITE);
      leftArrow(ST77XX_WHITE);
      upArrrow(ST77XX_WHITE);
      downArrow(ST77XX_WHITE);
      showMenu(ST77XX_BLACK,ST77XX_GREEN);
      buttons = ss.readButtons();
    }
    rightArrow(ST77XX_BLACK);
    leftArrow(ST77XX_BLACK);
    upArrrow(ST77XX_BLACK);
    downArrow(ST77XX_BLACK);
    showMenu(ST77XX_WHITE,ST77XX_WHITE);
  }

  updateUI(pushing,3); //left
  updateUI(pulling,7); //right
  updateUI(retracting,2); //up
  updateUI(resetting,4); //down
}

