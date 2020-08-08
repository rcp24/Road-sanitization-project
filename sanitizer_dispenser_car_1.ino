
#include <Servo.h>

Servo myservo1; //servo object to rotate sprayer
Servo myservo2; //another servo motor to press nob of spray

int pos = 0;    // variable to store the servo position

const int trigPin = 9;//trigger pin of sensor
const int echoPin = 8; //echo pin of sensor
const int signal =12; //signal pin of PIR sensor


long duration1, distance1,duration2, distance2;

void setup() {
   Serial.begin(9600);
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   pinMode(signal,INPUT); // PIR sensor to detect human motion
  pinMode(10,OUTPUT); //LED for ultrasonic sensor
  pinMode(6,OUTPUT); //input4 of motor driver 
   pinMode(5,OUTPUT); //input3 of motor driver
   pinMode(4,OUTPUT); //input1 of motor driver
   pinMode(3,OUTPUT); //input2 of motor driver
  myservo1.attach(7);// attaches the servo1 on pin 7 to the servo object
  myservo2.attach(2);// attaches the servo2 on pin 2 to the servo object
}

void loop() {
  cw(180);
  presser();
  acw(180);
  presser();
  sensor( trigPin,echoPin, duration1, distance1);
  sensor(signal,signal, duration2,distance2);
  
  //To avoid obstacles we are using HC-SR04 ultrasonic distance sensor 
  if(distance1<30){
    digitalWrite(10,HIGH);//LED pin of distance sensor
    delay(1000);    //led will glow for this much time
    right();
    forward();
     }
  
  if(distance2<20){
    digitalWrite(11,HIGH); //LED pin of PIR sensor
    delay(1000);
    cw(90);
    presser();
    acw(90);
  }       
    
  else{
    digitalWrite(10,LOW);  //LED will not glow
    digitalWrite(11,LOW);  //LED will not glow
    forward();
    backward();
  }
 
}
//forward 
void forward(){
  digitalWrite(6,HIGH);
    digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
    digitalWrite(3,LOW);
  delay(5000);
   
}
 //backward
void backward(){
 digitalWrite(6,LOW);
    digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
    digitalWrite(3,HIGH);
  delay(5000);
    
}
 //right
void right(){
      digitalWrite(6, HIGH); 
      digitalWrite(5, LOW); 
      digitalWrite(4, LOW); 
      digitalWrite(3, HIGH);
      delay(1200); 
}
//sprayer nob is being pressed
void presser()
{ 
     for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees // in steps of 1 degree
    myservo2.write(pos);              // tell servo2 to go to position in variable 'pos'
    delay(15);                       // waits 10ms for the servo to reach the position
      }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 10ms for the servo to reach the position
      }
}

//servo motor1 moving clockwise
void cw(int n){
   for (pos = 0; pos <= n; pos += 1) { // goes from 0 degrees to 180 degrees
     myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 10ms for the servo to reach the position
    }
}
 //servo motor1 moving anti-clockwise
void acw(int n){
  for (pos = n; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 10ms for the servo to reach the position
    }
}

//sensors working  
void sensor(int a,int b, float t,float s){
   
  digitalWrite(a, LOW);
  delayMicroseconds(2);
  digitalWrite(a, HIGH);
  delayMicroseconds(5);
  digitalWrite(a, LOW);  
  t= pulseIn(b, HIGH);//in microseconds
  Serial.println(t);
  s=t/100; 
}


