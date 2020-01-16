void UI(void (*fxn)(uint16_t), uint16_t buttonPos){
    if (! (buttons & 1<<buttonPos)) {
        stepper.enableOutputs();
        tft.fillScreen(ST77XX_BLACK);
        (*fxn)(ST77XX_WHITE);
        uint8_t count = 0;
        if (buttonPos==B_BTN){
            setFast(); 
        }
        else{
            setSlow();
        }
        while(!(buttons & 1<<buttonPos)){
            stepper.run();
            switch (buttonPos){
            case UP:
                if(digitalRead(limit_push)){
                    moveDirection(INFUSE);
                }
                else{
                    limitReached(INFUSE);
                    buttons = ss.readButtons();
                }
                break;
            case DOWN:
                if (digitalRead(limit_pull)){
                    moveDirection(RETRACT);
                }
                else{
                    limitReached(RETRACT);
                    buttons = ss.readButtons();
                }
                break;
            case B_BTN: 
                retract();
                buttons = ss.readButtons();
                break;
            case A_BTN:
                delay(1000);
                ongoingPosition = 0;
                buttons = ss.readButtons();
                break;
            case CENTER:
                uint32_t holdStarted = millis();
                while( ((millis()-holdStarted) < 900) & (!(buttons & 1<<buttonPos)) ){
                    buttons = ss.readButtons();
                }
                tft.print("...");
                if( !(buttons & 1<<buttonPos) ){
                    setFast();
                    bool hit_pull = determine_direction();
                    tft.fillScreen(ST77XX_BLACK);
                    tft.setTextColor(ST77XX_WHITE);
                    tft.setTextSize(2);
                    tft.setCursor(80,11);
                    tft.print("Infuse");
                    tft.setCursor(70,62);
                    tft.print("Retract"); 
                    bool selected = false;
                    while(!selected){
                        buttons = ss.readButtons();
                        if(! (buttons & 1<<A_BTN)){
                            selected = true;
                            if (hit_pull){
                                pull_is_21  = !pull_is_21;
                                limit_pull = limit_pins[pull_is_21];
                                limit_push = limit_pins[!pull_is_21];
                                EEPROM.update(LIMIT_PIN_ASSIGNMENT_ADDRESS, pull_is_21);
                            }
                            // was pushed
                        }
                        else if (! (buttons & 1<<B_BTN)){
                            selected = true;
                            softDirection = !softDirection;
                            EEPROM.update(DIRECTION_ADDRESS, softDirection);
                            stepper.setPinsInverted(softDirection, false, true);
                            if (!hit_pull){
                                pull_is_21  = !pull_is_21;
                                limit_pull = limit_pins[pull_is_21];
                                limit_push = limit_pins[!pull_is_21];
                                EEPROM.update(LIMIT_PIN_ASSIGNMENT_ADDRESS, pull_is_21);
                            }
                            // retracted
                        }
                    }
                    delay(1000);
                }
                break;
            }
            if (count++ == 254){
                count = 0;
                buttons = ss.readButtons();
            }
        }
    ongoingPosition += long(stepper.currentPosition());
    stepper.setCurrentPosition(0);    
    showMenu();
  }
}

void serialUI(){
  if (Serial1.available()){
    char msg = Serial1.read();
    if (msg=='I' | msg == 'C' | msg == 'R' | msg == 'Z'){
        tft.fillScreen(ST77XX_BLACK);
        if (msg=='I'){ 
            uint32_t volume = parseData();
            dispenseVolume(volume);
        }
        else if (msg=='C'){
            connectedMessage();
        }
        else if (msg == 'R'){
            stepper.enableOutputs();
            retracting(ST77XX_WHITE);
            retract();
        }
        else if (msg == 'Z'){
            resetting(ST77XX_WHITE);
            delay(1000);
            ongoingPosition = 0;
        }
        ongoingPosition += long(stepper.currentPosition());
        stepper.setCurrentPosition(0);
        showMenu();
    }    
  }
}

void showMenu(){
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    tft.setCursor(129,11);
    tft.print("Reset");
    tft.setCursor(123,62);
    tft.print("Refill"); 
    showDispensed(ST77XX_GREEN);
}

void retracting(uint16_t color){
    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(30 , 30);
    tft.print("Refill");
}

void resetting(uint16_t color){
    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(40 , 17);
    tft.print("Reset");
    tft.setCursor(30 , 43);
    tft.print("Volume");
}

void pushing(uint16_t color){
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(30, 30);
    tft.print("Infuse");
}

void pulling(uint16_t color){
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(20, 30);
    tft.print("Retract");
}

void flipDirection(uint16_t color){
    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.setCursor(30,30);
    tft.print("Homing");
}

void successfulFlip(uint16_t color){
    tft.fillScreen(ST77XX_WHITE);
    delay(900);
}

void showDispensed(uint16_t color){
    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(0,30);
    tft.print(ongoingPosition*resolution/1000);  
    tft.setCursor(tft.getCursorX(),37);
    tft.setTextSize(2);
    tft.print(" mL");
}

void limitMessage(uint16_t color){
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(color);
    tft.setTextSize(3);
    tft.setCursor(40, 30);
    tft.print("Limit");
}

void connectedMessage(){
    tft.fillScreen(ST77XX_BLACK);;
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.setCursor(0 , 0);
    tft.print("pyControl");
    delay(1500);
    ongoingPosition = 0;
    tft.fillScreen(ST77XX_BLACK);
    showMenu();
}

void setFast(){
    stepper.setAcceleration(850); 
    for(byte i=0; i<10;i++){
        driver.mres(5); 
        delay(5);
    }
}

void setSlow(){
    stepper.setAcceleration(5000); 
    for(byte i=0; i<10;i++){
        driver.mres(4); 
        delay(5);
    }
}