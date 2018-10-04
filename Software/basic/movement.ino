
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
  digitalWrite(enablePin,LOW);
  motorEnabled = true;
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

void retract(){
  digitalWrite(refillStatus,HIGH);
  Serial.println("retract loop");
  while(1){
    stepper.run();
    if (digitalRead(limit_pull)){
      moveDirection(!softDirection);
    }
    else{
      digitalWrite(refillStatus,LOW);
      stepper.setCurrentPosition(0);// stop the motor
      limitMessage(ST77XX_RED);
      if (softDirection){
          stepper.move(250); //bounce off the limit switch
      }
      else{
          stepper.move(-250); //bounce off the limit switch
      }
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

void moveDirection(bool oneWay){
  if (oneWay){
    if (stepper.distanceToGo() < 8000){
      stepper.move(100000);
    }
  }
  else{
    if (stepper.distanceToGo() > -8000){
        stepper.move(-10000);
    }
  }
}