
void stopImmediately(){
    stepper.setCurrentPosition(0);
}

void slowStop(){
  stepper.stop();
  while(stepper.isRunning()){
    stepper.run();
  }
}

void enableMotor(){
  motorEnabled = true;
  digitalWrite(enablePin,LOW);
}

void disableMotor(){
  digitalWrite(enablePin,HIGH);  
  motorEnabled = false;
}

void limitReached(){
  stepper.setCurrentPosition(0);
  limitMessage(ST77XX_RED);
  delay(1000);
  limitMessage(ST77XX_BLACK);
}

void limitMessage(uint16_t color){
  tft.setTextColor(color);
  tft.setTextSize(2);
  tft.setCursor(0 , 35);
  tft.print("Limit Reached");
}


void retract(){
  digitalWrite(refillStatus,HIGH);
  Serial.println("retract loop");
  while(1){
    stepper.run();
    if (digitalRead(limit_pull)){
      if (stepper.distanceToGo() > -8000){
        stepper.move(-10000);
      }
    }
    else{
      digitalWrite(refillStatus,LOW);
      stepper.setCurrentPosition(0);// stop the motor
      limitMessage(ST77XX_RED);
      stepper.move(250); //bounce off the limit switch
      while(stepper.isRunning()){
        stepper.run();
      }
      delay(1000);
      limitMessage(ST77XX_BLACK);
      stepper.setCurrentPosition(0);
      ongoingPosition = 0;//reset dispensed volume to 0
      break;
    }
  }
}