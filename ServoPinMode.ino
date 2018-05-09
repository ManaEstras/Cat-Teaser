#include <Servo.h> 
const int modePin = 2;

int leftPin  = 3;
int rightPin = 4;

int LeftRight = 9;
int UpDown1 = 8;
int UpDown2 = 10;

Servo servoUpDown1; //left
Servo servoUpDown2;//right 
Servo servoLeftRight; //rotate

int servoAngle = 0;
int leftTurn = 0;
int rightTurn = 0;
int modeauto = 0;

void setup()
{
  Serial.begin(9600);  
  servoUpDown1.attach(UpDown1);
  servoUpDown2.attach(UpDown2);
  servoLeftRight.attach(LeftRight);
  servoUpDown1.write(90);
  servoUpDown2.write(90);
  servoLeftRight.write(90);
  pinMode(modePin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
}
void loop()
{
 modeauto = digitalRead(modePin);
 leftTurn = digitalRead(leftPin);
 rightTurn  = digitalRead(rightPin);
 Serial.println(modeauto);
if (modeauto == 1) {
  AutoMode();
 } else{
  ManualMode();
   }
}
//
// AutoMode if Auto = 1;
void AutoMode()
{
ccwMid();
cwMid();
}
//turn left right if Auto = 0;
void ManualMode(){
  Turn();
}

void Turn() {  
  if (leftTurn == HIGH) {
     ccwTurn();   
  }
  if (rightTurn == HIGH) {
    cwTurn();
    }
}
void ccwMid(){
 for(servoAngle = 0; servoAngle < 90; servoAngle += 3)   
  {                                  
    servoLeftRight.write(servoAngle);
    delay(30);                     
  } 
 }
 void cwMid(){
 for(servoAngle = 90; servoAngle > 0; servoAngle-=3)  //clockwise 0 to 90
  {                                
    servoLeftRight.write(servoAngle);          
    delay(30);      
  }
}
void ccwTurn(){
 for(servoAngle < 90; servoAngle += 1)   
  {                                  
    servoLeftRight.write(servoAngle);
    servoLeftRight.write(servoAngle);
    delay(300);  
    servoLeftRight.write(servoAngle);
    servoLeftRight.write(servoAngle);
    delay(300);  
    servoLeftRight.write(servoAngle);
    servoLeftRight.write(servoAngle);
    delay(300);
    if (servoAngle = 90){break;}                     
  } 
 }
 void cwTurn(){
 for(servoAngle = 90; servoAngle > 0; servoAngle-=1)  //clockwise 0 to 90
  {                                
    servoLeftRight.write(servoAngle); 
    servoLeftRight.write(servoAngle); 
    delay(300);  
    servoLeftRight.write(servoAngle);  
    servoLeftRight.write(servoAngle);
    delay(300);  
    servoLeftRight.write(servoAngle);
    servoLeftRight.write(servoAngle);
    delay(300);      
    if (servoAngle = 0){break;} 
  }
 }


