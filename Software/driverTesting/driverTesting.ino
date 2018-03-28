#include <StepControl.h> //https://github.com/luni64/TeensyStep

//Stepper Motor variables
#define EN  12
#define PIN2 11
#define PIN3 10
#define PIN4 9
#define PIN5 8
#define PIN6 7

#define stp 6
#define dir 5


const uint8_t motorSteps = 200; //steps per revolution
uint32_t baseSpeed = 16000; //45 mm/s assuming ball is 9.5mm in diameter
float relSpeed = 1.0;
Stepper motor(stp, dir);     // STEP pin: 2, DIR pin: 3
StepControl<> controller;    // Use default settings 
int numSteps;
bool enabled  = true;

// enum stepResolution {FULL=0, HALF=2, QTR=1, EIGHTH=3};  //Microstep Resolution Truth Table is on pg.3 of A3957 datasheet.
enum motorDirection {PULL,PUSH};
int alternate = 0;
bool continuousOn = false;
bool direction = PUSH;
float moveSteps = 6400.0;
float valsFromParse[2];


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  // setupDRV();
  // setupAllegro();
  setupTMC();
  delay(500);
  Serial.println("\nSerial Connected");
  Serial.println("\'e\' enable/disable motor");
  Serial.println("\'t\' to turn motor");
  Serial.println("\'s\' to change speed");
  Serial.println("\'a\' to change acceleration");
  Serial.println("\'i\' to continuously turn motor");
  Serial.println("\'i\' again to stop motor");

}

void loop() {
  if (Serial.available()){
    char cmd = Serial.read();
    uint32_t myTime;
    switch (cmd){
      case 't': //change number revolutions
        if(parseSerialCmd()){
          moveSteps = valsFromParse[0];
        }
        myTime = millis();
        turnMotor(1);
        Serial.print("myTime:");
        Serial.println(millis()-myTime);
        break;
      case 'r': //change number revolutions
        if(parseSerialCmd()){
          moveSteps = valsFromParse[0];
        }
        myTime = millis();
        turnMotor(-1);
        Serial.print("myTime:");
        Serial.println(millis()-myTime);

        break;
      case 'a':
        if (parseSerialCmd()){
          changeAccel(valsFromParse[0]);
        }
        break;
      case 'i':
        continuousOn = ! continuousOn;
        if (continuousOn){
          rotateContinuously();
        }
        else{
          Serial.println("stopped");
          controller.stop();
        }
        break;
      case 's':
        if(parseSerialCmd()){
          changeSpeed(valsFromParse[0]);
        }
        break;
      case 'e':
        toggleEnable();
      break;
    }
  }
}

void toggleEnable(){
  if (enabled){
    digitalWrite(EN,HIGH);
    enabled = false;
  }
  else{
    digitalWrite(EN,LOW);
    enabled = true;
  }
  Serial.print("Enabled = "); Serial.println(enabled);
}

void rotateContinuously(){
  if (parseSerialCmd()){
    relSpeed = valsFromParse[0];            
  }
  controller.rotateAsync(motor,relSpeed);
  Serial.print("spinning continuously @ ");
  Serial.print(int(relSpeed*100));
  Serial.print("% speed with ");
  Serial.print("...");
}

void turnMotor(int8_t direction){  
  Serial.print("spinning ");
  Serial.print(moveSteps);
  Serial.print(" steps (");
  Serial.print(moveSteps/numSteps*360.0);
  Serial.print(" degrees) @ ");
  Serial.print("...");
  
  motor.setTargetRel(int(direction*moveSteps));  // Set target position to 1000 steps from current position

  controller.move(motor);         // Do the move
  while(controller.isRunning()){  // wait until the movement is finished
    delay(10);                     
  }
  Serial.println("done");
}


uint8_t parseSerialCmd(){
  char msgData[30] = "";
  Serial.readBytesUntil('\n',msgData,30);
  char* msgPointer;
  msgPointer = strtok(msgData," ");
  uint8_t i = 0;
  while (msgPointer!=NULL){
    valsFromParse[i] = atof(msgPointer);
    msgPointer = strtok(NULL," ");
    i++;
  }
  return i;
}


void changeAccel(int newAccel){
  Serial.print("\tNew Accel: "); Serial.println(newAccel);
  motor.setAcceleration(newAccel);    // stp/s^2
}
void changeSpeed(int newSpeed){
  Serial.print("\tNew Max Speed: "); Serial.println(newSpeed);
  motor.setMaxSpeed(newSpeed);
}

void setupDRV(void){
    //Motor setup
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  pinMode(PIN4, OUTPUT);
  pinMode(PIN5, OUTPUT);
  pinMode(PIN6, OUTPUT);

  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, HIGH);
  digitalWrite(PIN4, HIGH);
  digitalWrite(PIN5, HIGH);
  digitalWrite(PIN6, HIGH);

  numSteps = 32*motorSteps;
  moveSteps = 10*numSteps;
  motor.setMaxSpeed(30000);
  motor.setAcceleration(90000);    // stp/s^2  
}

void setupAllegro(void){
    //Motor setup
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  pinMode(PIN4, OUTPUT);
  pinMode(PIN5, OUTPUT);
  pinMode(PIN6, OUTPUT);

  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, HIGH);
  digitalWrite(PIN4, HIGH);
  digitalWrite(PIN5, HIGH);
  digitalWrite(PIN6, HIGH);

  numSteps = 16*motorSteps;
  moveSteps = 10*numSteps;

  motor.setMaxSpeed(15000);
  motor.setAcceleration(90000);    // stp/s^2  
}

void setupTMC(void){
  pinMode(PIN5, OUTPUT);//CFG0
  digitalWrite(PIN5, LOW);//CFG0

  pinDisable(PIN2); //CFG1
  pinDisable(PIN3); //CFG2

  pinMode(PIN4, OUTPUT); //CFG3
  digitalWrite(PIN4, HIGH); //CFG3

  pinMode(EN, OUTPUT); //CFG6
  digitalWrite(EN, LOW); //CFG6


  numSteps = 16*motorSteps;
  moveSteps = numSteps;
  motor.setMaxSpeed(5000);
  motor.setAcceleration(5000);    // stp/s^2  


}

void pinDisable(const uint8_t pin) { //https://forum.pjrc.com/threads/34800-Are-Teensy3-2-Pins-High-Low-and-Tri-State
  volatile uint32_t *config;  
  if (pin >= CORE_NUM_TOTAL_PINS) return;
  config = portConfigRegister(pin);
  *config = 0;
}