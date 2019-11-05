void bounce(int bounceDistance){
  stepper.setCurrentPosition(0);
  stepper.move(bounceDistance); //bounce off the limit switch
  while(stepper.isRunning()){
    stepper.run();
  }
  stepper.setCurrentPosition(0);
}

void limitReached(boolean infusing){
  if (infusing){
      ongoingPosition += long(stepper.currentPosition());
      bounce(-250);
  }
  else{
      ongoingPosition -= long(stepper.currentPosition());
      bounce(250);
  }   
  Serial1.write("Limit");
  limitMessage(ST77XX_RED);
  delay(1000);
  limitMessage(ST77XX_BLACK);
}

void retract(){
  while(1){
    stepper.run();
    if (digitalRead(limit_push) && digitalRead(limit_pull)){
      moveDirection(RETRACT);
    }
    else{
      stepper.setCurrentPosition(0);// stop the motor
      bounce(250);
      ongoingPosition = 0;
      break;
    }
  }
}

void moveDirection(bool infusing){
  if (infusing){
    if (stepper.distanceToGo() < 8000){
      stepper.move(10000);
    }
  }
  else{
    if (stepper.distanceToGo() > -8000){
        stepper.move(-10000);
    }
  }
}

void dispenseVolume(long volume){
  stepper.enableOutputs();
  stepper.move(volume/resolution);

  while (stepper.isRunning()){
    if (digitalRead(limit_push) && digitalRead(limit_pull)){
      stepper.run();
    }
    else{
      if (volume>=0){
        limitReached(INFUSE);
      }
      else{
        limitReached(RETRACT);
      }
    }
  }
}