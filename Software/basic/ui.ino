void arrowUI(void (*fxn_1)(uint16_t), uint8_t buttonPos){
    if (! (buttons & 1<<buttonPos)) {
        enableMotor();
        (*fxn_1)(ST77XX_WHITE);
        showMenu(ST77XX_BLACK,ST77XX_BLACK,ST77XX_BLACK);
        uint16_t count = 0;
        while(!(buttons & 1<<buttonPos)){
            stepper.run();
            switch (buttonPos){
            case LEFT:
                if(digitalRead(limit_push)){
                    if (stepper.distanceToGo() < 8000){
                        stepper.move(100000);
                    }
                }
                else{
                    limitReached();
                    buttons = ss.readButtons();
                }
                break;
            case RIGHT:
                if (digitalRead(limit_pull)){
                    if (stepper.distanceToGo() > -8000){
                        stepper.move(-100000);
                    }
                }
                else{
                    limitReached();
                    buttons = ss.readButtons();
                }
                break;
            case UP: 
                retract();
                buttons = ss.readButtons();
                break;
            case DOWN:
                delay(1000);
                ongoingPosition = 0;
                buttons = ss.readButtons();
                break;
            }
            if (count++ == 300){
                count = 0;
                buttons = ss.readButtons();
            }
        }    
    ongoingPosition += long(stepper.currentPosition());
    stopImmediately();    
    (*fxn_1)(ST77XX_BLACK);
    showMenu(ST77XX_WHITE,ST77XX_WHITE,ST77XX_GREEN);
  }
}

void buttonUI(void (*fxn_1)(uint16_t), uint8_t buttonPos, uint16_t aboutColor, uint16_t helpColor ){
    if (! (buttons & 1<<buttonPos)) {
        showMenu(aboutColor,helpColor,ST77XX_BLACK);
        (*fxn_1)(ST77XX_WHITE);
        while(!(buttons & 1<<buttonPos)){
            buttons = ss.readButtons();
        }
        (*fxn_1)(ST77XX_BLACK);
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
  tft.println("\n\nFirmware Version: 1");
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

    uint16_t leftSideX = 52; 
    uint16_t centerY = 40;
    uint16_t arrowWidth = 10;
    uint16_t arrowHeight = 5;
    tft.fillTriangle(leftSideX, centerY-arrowHeight, leftSideX, centerY+arrowHeight, leftSideX+arrowWidth, centerY, color);

    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(leftSideX + arrowWidth + 3, centerY - 3);

    tft.print("Pull");
}

void leftArrow(uint16_t color){
    tft.setRotation(3);
    uint16_t rightSide = 38; 
    uint16_t centerY = 40;
    uint16_t arrowWidth = 10;
    uint16_t arrowHeight = 5;
    tft.fillTriangle(rightSide, centerY-arrowHeight, rightSide, centerY+arrowHeight, rightSide-arrowWidth, centerY, color);

    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(rightSide - 35, centerY - 3);

    tft.print("Push");
}

void upArrrow(uint16_t color){
    tft.setRotation(3);

    uint16_t centerX = 45; 
    uint16_t bottomSide = 33;
    uint16_t arrowWidth = 5;
    uint16_t arrowHeight = 10;
    tft.fillTriangle(centerX - arrowWidth, bottomSide, centerX, bottomSide - arrowHeight, centerX + arrowWidth,bottomSide, color);

    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(centerX - 20, bottomSide - 18);

    tft.print("Retract");
}

void downArrow(uint16_t color){
    tft.setRotation(3);
    uint16_t centerX = 45; 
    uint16_t bottomSide = 47;
    uint16_t arrowWidth = 5;
    uint16_t arrowHeight = 10;
    tft.fillTriangle(centerX - arrowWidth, bottomSide, centerX, bottomSide + arrowHeight, centerX + arrowWidth,bottomSide, color);

    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(centerX -33, bottomSide + 11);

    tft.print("Reset Volume");
}

void showButtonMap(uint16_t color){
    rightArrow(color);
    leftArrow(color);
    upArrrow(color);
    downArrow(color);
}     

void pushing(uint16_t color){
    tft.setRotation(3);
    uint16_t rightSide = 10; 
    uint16_t centerY = 7;
    uint16_t arrowWidth = 10;
    uint16_t arrowHeight = 5;
    tft.fillTriangle(rightSide, centerY-arrowHeight, rightSide, centerY+arrowHeight, rightSide-arrowWidth, centerY, color);

    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.setCursor(15 , 0);
    tft.print("Push");
}

void pulling(uint16_t color){
    tft.setRotation(3);
    uint16_t leftSideX = 0; 
    uint16_t centerY = 7;
    uint16_t arrowWidth = 10;
    uint16_t arrowHeight = 5;
    tft.fillTriangle(leftSideX, centerY-arrowHeight, leftSideX, centerY+arrowHeight, leftSideX+arrowWidth, centerY, color);

    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.setCursor(15 , 0);
    tft.print("Pull");
}

void retracting(uint16_t color){
    tft.setRotation(3);
    uint16_t centerX = 5; 
    uint16_t bottomSide = 12;
    uint16_t arrowWidth = 5;
    uint16_t arrowHeight = 10;
    tft.fillTriangle(centerX - arrowWidth, bottomSide, centerX, bottomSide - arrowHeight, centerX + arrowWidth,bottomSide, color);

    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.setCursor(15 , 0);
    tft.print("Retract");
}

void resetting(uint16_t color){
    uint16_t centerX = 5; 
    uint16_t bottomSide = 2;
    uint16_t arrowWidth = 5;
    uint16_t arrowHeight = 10;
    tft.fillTriangle(centerX - arrowWidth, bottomSide, centerX, bottomSide + arrowHeight, centerX + arrowWidth,bottomSide, color);

    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.setCursor(15 , 0);
    tft.print("Reset Volume");
}

void showDispensed(uint16_t color){
    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.setCursor(0,35);
    tft.print(int(ongoingPosition*resolution));  
    tft.setCursor(tft.getCursorX(),42);
    tft.setTextSize(1);
    tft.println(F(" uL dispensed"));
}