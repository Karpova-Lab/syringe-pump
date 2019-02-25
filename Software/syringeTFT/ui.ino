void arrowUI(void (*fxn)(uint16_t), uint16_t buttonPos){
    if (! (buttons & 1<<buttonPos)) {
        enableMotor();
        showMenu(ST77XX_BLACK,ST77XX_BLACK,ST77XX_BLACK);
        (*fxn)(ST77XX_WHITE);
        uint16_t count = 0;
        while(!(buttons & 1<<buttonPos)){
            stepper.run();
            switch (buttonPos){
            case UP:
                if(digitalRead(limit_push) && digitalRead(limit_pull)){
                    moveDirection(softDirection);
                }
                else{
                    limitReached();
                    buttons = ss.readButtons();
                }
                break;
            case DOWN:
                if (digitalRead(limit_push) && digitalRead(limit_pull)){
                    moveDirection(!softDirection);
                }
                else{
                    limitReached();
                    buttons = ss.readButtons();
                }
                break;
            case LEFT: 
                retract();
                buttons = ss.readButtons();
                break;
            case RIGHT:
                delay(1000);
                ongoingPosition = 0;
                buttons = ss.readButtons();
                break;
            case CENTER:
                uint32_t holdStarted = millis();
                while( ((millis()-holdStarted) < 2750) & (!(buttons & 1<<buttonPos)) ){
                    buttons = ss.readButtons();
                }
                if( !(buttons & 1<<buttonPos) ){
                    softDirection = !softDirection;
                    EEPROM.update(DIRECTION_ADDRESS, softDirection);
                    successfulFlip(ST77XX_WHITE);
                }
                break;
            }
            if (count++ == 300){
                count = 0;
                buttons = ss.readButtons();
            }
        }
    if (softDirection){
        ongoingPosition += long(stepper.currentPosition());
    }
    else{
        ongoingPosition -= long(stepper.currentPosition());
    }        
    stopImmediately();    
    (*fxn)(ST77XX_BLACK);
    showMenu(ST77XX_WHITE,ST77XX_WHITE,ST77XX_GREEN);
  }
}

void buttonUI(void (*fxn)(uint16_t), uint8_t buttonPos, uint16_t aboutColor, uint16_t helpColor ){
    if (! (buttons & 1<<buttonPos)) {
        showMenu(aboutColor,helpColor,ST77XX_BLACK);
        (*fxn)(ST77XX_WHITE);
        while(!(buttons & 1<<buttonPos)){
            buttons = ss.readButtons();
        }
        (*fxn)(ST77XX_BLACK);
        showMenu(ST77XX_WHITE,ST77XX_WHITE,ST77XX_GREEN);
    }
}

void ttlUI(void (*fxn)(uint16_t), uint8_t ttlPin){
    if(digitalRead(ttlPin)==HIGH){
    enableMotor();
    showMenu(ST77XX_BLACK,ST77XX_BLACK,ST77XX_BLACK);
    (*fxn)(ST77XX_WHITE);
    while(digitalRead(ttlPin)==HIGH){
      stepper.run();
      if(digitalRead(limit_push) && digitalRead(limit_pull)){
          moveDirection(softDirection);
      }
      else{
          limitReached();
      }
    }
    if (softDirection){
        ongoingPosition += long(stepper.currentPosition());
    }
    else{
        ongoingPosition -= long(stepper.currentPosition());
    }  
    stopImmediately();    
    (*fxn)(ST77XX_BLACK);
    showMenu(ST77XX_WHITE,ST77XX_WHITE,ST77XX_GREEN);
  }

}

void showMenu(uint16_t aboutColor, uint16_t helpColor, uint16_t dispenseColor ){
    about(aboutColor);  
    help(helpColor);
    showDispensed(dispenseColor);
}

void firmware(uint16_t color){
    tft.setRotation(3);
    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(0,12);
    tft.print("\n\nFirmware Version: ");tft.println(VERSION);
    tft.println(DATE);
    tft.println("Syringe Volume: 60 mL");
}

void about(uint16_t color){
    tft.setRotation(3);
    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(130,12);
    tft.println("About");
}

void help(uint16_t color){
    tft.setRotation(3);
    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(135,60);
    tft.println("Help");
}

void rightArrow(uint16_t color){
    tft.setRotation(3);

    uint16_t leftSideX = 67; 
    uint16_t centerY = 40;
    uint16_t arrowWidth = 10;
    uint16_t arrowHeight = 5;
    tft.fillTriangle(leftSideX, centerY-arrowHeight, leftSideX, centerY+arrowHeight, leftSideX+arrowWidth, centerY, color);

    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(leftSideX + arrowWidth + 3, centerY - 3);

    tft.print("Reset Volume");
}

void leftArrow(uint16_t color){
    tft.setRotation(3);
    uint16_t rightSide = 53; 
    uint16_t centerY = 40;
    uint16_t arrowWidth = 10;
    uint16_t arrowHeight = 5;
    tft.fillTriangle(rightSide, centerY-arrowHeight, rightSide, centerY+arrowHeight, rightSide-arrowWidth, centerY, color);

    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(0, centerY - 3);

    tft.print("Retract");
}

void upArrrow(uint16_t color){
    tft.setRotation(3);

    uint16_t centerX = 60; 
    uint16_t bottomSide = 33;
    uint16_t arrowWidth = 5;
    uint16_t arrowHeight = 10;
    tft.fillTriangle(centerX - arrowWidth, bottomSide, centerX, bottomSide - arrowHeight, centerX + arrowWidth,bottomSide, color);

    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(centerX - 20, bottomSide - 18);

    tft.print("Infuse");
}

void downArrow(uint16_t color){
    tft.setRotation(3);
    uint16_t centerX = 60; 
    uint16_t bottomSide = 47;
    uint16_t arrowWidth = 5;
    uint16_t arrowHeight = 10;
    tft.fillTriangle(centerX - arrowWidth, bottomSide, centerX, bottomSide + arrowHeight, centerX + arrowWidth,bottomSide, color);

    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(centerX -33, bottomSide + 11);

    tft.print("Withdrawal");
}

void showButtonMap(uint16_t color){
    rightArrow(color);
    leftArrow(color);
    upArrrow(color);
    downArrow(color);
}     

void retracting(uint16_t color){
    tft.setRotation(3);
    uint16_t rightSide = 22; 
    uint16_t centerY = 40;
    uint16_t arrowWidth = 20;
    uint16_t arrowHeight = 10;
    tft.fillTriangle(rightSide, centerY-arrowHeight, rightSide, centerY+arrowHeight, rightSide-arrowWidth, centerY, color);

    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(30 , 30);
    tft.print("Retract");
}

void resetting(uint16_t color){
    tft.setRotation(3);
    uint16_t leftSideX = 2; 
    uint16_t centerY = 40;
    uint16_t arrowWidth = 20;
    uint16_t arrowHeight = 10;
    tft.fillTriangle(leftSideX, centerY-arrowHeight, leftSideX, centerY+arrowHeight, leftSideX+arrowWidth, centerY, color);

    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(40 , 17);
    tft.print("Reset");
    tft.setCursor(30 , 43);
    tft.print("Volume");
}

void pushing(uint16_t color){
    tft.setRotation(3);
    uint16_t centerX = 12; 
    uint16_t bottomSide = 50;
    uint16_t arrowWidth = 10;
    uint16_t arrowHeight = 20;
    tft.fillTriangle(centerX - arrowWidth, bottomSide, centerX, bottomSide - arrowHeight, centerX + arrowWidth,bottomSide, color);

    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(30 , 30);
    tft.print("Infuse");
}

void pulling(uint16_t color){
    uint16_t centerX = 12; 
    uint16_t topSide = 30;
    uint16_t arrowWidth = 10;
    uint16_t arrowHeight = 20;
    tft.fillTriangle(centerX - arrowWidth, topSide, centerX, topSide + arrowHeight, centerX + arrowWidth,topSide, color);

    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.setCursor(30 , 30);
    tft.print("Withdrawal");

}

void flipDirection(uint16_t color){

    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.setCursor(0 , 0);
    tft.print("Continue\nHolding\nto flip\ndirection");
}

void successfulFlip(uint16_t color){
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.setCursor(0 , 0);
    tft.print("Direction\nflipped!");
    delay(1250);
    tft.fillScreen(ST77XX_BLACK);
}

void showDispensed(uint16_t color){
    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(0,21);
    tft.print(long(ongoingPosition*resolution));  
    tft.setCursor(tft.getCursorX(),28);
    tft.setTextSize(2);
    tft.println(F(" uL\ndispensed"));
}

void limitMessage(uint16_t color){
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(40 , 17);
    tft.print("Limit\n");
    tft.setCursor(20 ,tft.getCursorY());
    tft.print("Reached");
}