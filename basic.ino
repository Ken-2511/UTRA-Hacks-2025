// definitions and constants
#include "NewPing.h"
#include <math.h>


#define TRIG_PIN 11
#define ECHO_PIN 10
#define MAX_DISTANCE 30


//color code:
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 3


//ENB is connected to left
const int IN1 = 4;  // Motor A direction control
const int IN2 = 5;  // Motor A direction control
const int ENA = 11; // Motor A speed control (PWM)
const int IN3 = 3; // Motor B direction control
const int IN4 = 2; // Motor B direction control
const int ENB = 10; // Motor B speed control (PWM)


// #define BLACK 0
// #define BLUE 1
// #define GREEN 2
// #define RED 3


// Define color sensor pins


#define S0 6
#define S1 7
#define S2 8
#define S3 9
#define sensorOut 13


#define RED 1
#define GREEN 2
#define BLUE 3
#define OTHER_COLOR 0




// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
int APW = 0;


bool done = false;
bool pastStart = false;


//setup:
void setup() {
 // Set all the motor control pins to output
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(ENA, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(ENB, OUTPUT);


 //code for setting up color sensors:
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  // Set Pulse Width scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);


 // put your setup code here, to run once:
 Serial.begin(9600);
}




//functions
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
double getSensorDistanceCm(){
 return sonar.ping_cm();
}
void moveForward(int speed){
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 analogWrite(ENA, speed);
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
 analogWrite(ENB, speed);
 delay(100);
 stopMotors();
}
void stopMotors() {
 // Stop both motors
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
 analogWrite(ENA, 0); // Stop Motor A
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, LOW);
 analogWrite(ENB, 0); // Stop Motor B
}
void turnRight(){
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 analogWrite(ENA, 255); // Full speed for Motor A
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
 analogWrite(ENB, 255); // Full speed for Motor B
 delay(2000); // Run for 2 seconds
}
void turnLeft(){
 // Rotate Motor A forward and Motor B backward
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 analogWrite(ENA, 255); // Full speed for Motor A
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
 analogWrite(ENB, 255); // Full speed for Motor B
 delay(2000); // Run for 2 seconds
}


// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}


// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}


// Function to read Blue Pulse Widths
int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}


// Function to read Blue Pulse Widths
int getTransparentPW() {
  // Set sensor to read Blue only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}


void normalize(double *act){
  double length = sqrt(act[0] * act[0] + act[1] * act[1] + act[2] * act[2] + act[3] * act[3]) + 1e-6;


    for(int i = 0; i < 4; i ++){
      act[i] = act[i] / length;
    }    
}


double dot_product(double * ref, double *act){
  normalize(ref);
  normalize(act);
  double result = 0;
  for(int i = 0; i < 4; i++){
    result = result + ref[i] * act[i];
  }
  // Serial.print("ref ");
  // for (int i = 0; i < 4; i++) {
  //   Serial.print(ref[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  // Serial.print("act ");
  // for (int i = 0; i < 4; i++) {
  //   Serial.print(act[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();


  // Serial.print("result ");
  // Serial.println(result);
  return result;
}


int getColor(double * act){
  int color = 0;
  double red[4] = {18, 60, 64, 12};
  double other[4] = {120, 134, 116, 42};
  double blue[4] = {34, 30, 24, 9};
  double green[4] = {26, 25, 34, 10};


  double distance[4];


  distance[0] = dot_product(red, act);
  distance[1] = dot_product(green, act);
  distance[2] = dot_product(blue, act);
  distance[3] = dot_product(other, act);
  double largest = distance[0];
  int index = 0;
  for(int i = 1; i < 4; i++){
    if(distance[i] > largest){
      largest = distance[i];
      index = i;
    }
  }


  // Serial.print("distances");
  // for (int i = 0; i < 4; i++) {
  //   Serial.print(distance[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();


  // Serial.print("largest: ");
  // Serial.print(largest);
  // Serial.print(" ");
  // Serial.print(index);
  // Serial.println();
     
  int colorcode[4] = {RED, GREEN, BLUE, OTHER_COLOR};
  return colorcode[index];
}
