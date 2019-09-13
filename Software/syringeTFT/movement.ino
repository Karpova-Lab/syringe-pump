void stopImmediately(){
    stepper.setCurrentPosition(0);
}

void enableMotor(){
  PORTF &= ~(1<<7);
  motorEnabled = true;
}

void disableMotor(){
  PORTF |= (1<<7);
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
  Serial1.write("Limit");
  limitMessage(ST77XX_RED);
  delay(1000);
  limitMessage(ST77XX_BLACK);
}

void retract(){
  while(1){
    stepper.run();
    if (digitalRead(limit_push) && digitalRead(limit_pull)){
      moveDirection(!softDirection);
    }
    else{
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

void dispenseVolume(long volume){
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