#include <Servo.h>
int prevColour;
int currentColour;
int ringsCrossed;
bool done;
Servo myservo;
int pos = 0;  // variable to store the servo position

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  prevColour = -1;
  currentColour = -1;
  ringsCrossed = 0;
  done = false;
  myservo.attach(12);
  closeClaw();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!done){
    if (ringsCrossed >= 5){
      // place flag here
      done = true;
      // stop everything
    }
    moveForward(150);
    int colour = getColour();
    if (colour != currentColour){
      if (colour == prevColour){ // Jerry coded this so if it sucks ykw
  	for (pos = 0; pos <= 180; pos += 1)
  	{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);


  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 255);


  delay(1000);
  	}
      } else {
        prevColour = currentColour;
        currentColour = colour;
        ringsCrossed+=1;
      }
    } else {
      stopMotors()
    }
  }
  // call function to place flag here
  openClaw();
}
void closeClaw(){
  for (pos = 0; pos <= 110; pos += 1)
  {
    myservo.write(pos);
    delay(50);
  }
}
void openClaw(){
  for (pos = 110; 0 >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);
    delay(50);
  }
}
