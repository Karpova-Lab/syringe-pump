
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
  if (softDirection){
      ongoingPosition += long(stepper.currentPosition());
  }
  else{
      ongoingPosition -= long(stepper.currentPosition());
  }   
  stepper.setCurrentPosition(0);
  Serial1.write("Limit Reached\n");
  limitMessage(ST77XX_RED);
  delay(1000);
  limitMessage(ST77XX_BLACK);
}

void retract(){
  // digitalWrite(refillStatus,HIGH);
  while(1){
    stepper.run();
    if (digitalRead(limit_push) && digitalRead(limit_pull)){
      moveDirection(!softDirection);
    }
    else{
      // digitalWrite(refillStatus,LOW);
      stepper.setCurrentPosition(0);// stop the motor
      if (softDirection){
          stepper.move(250); //bounce off the limit switch
      }
      else{
          stepper.move(-250); //bounce off the limit switch
      }
      while(stepper.isRunning()){
        stepper.run();
      }
      ongoingPosition = 0;
      stepper.setCurrentPosition(0);
      limitReached();
      break;
    }
  }
}

void moveDirection(uint8_t oneWay){
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

void dispenseVolume(int volume){
  enableMotor();
  if (!softDirection){
    volume *= -1;
  }
  stepper.move(volume/resolution);

  while (stepper.isRunning()){
    if (digitalRead(limit_push) && digitalRead(limit_pull)){
      stepper.run();
    }
    else{
      limitReached();
    }
  }
}