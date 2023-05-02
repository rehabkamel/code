#include <AFMotor.h>
#include <SoftwareSerial.h>
#define S1Trig 9
#define S1Echo 10
SoftwareSerial bluetoothSerial(0, 1); // RX, TX
//initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
long duration; 
int distance;
char command;   
int state;          //Bluetooth cihazndan gelecek sinyalin deikeni
int vSpeed=255;     // Standart Hz, 0-255 aras bir deer alabilir

void setup() {
  interrupts ();
  pinMode(S1Trig, OUTPUT);      //Set the Trig pins as input pins     
  pinMode(S1Echo, INPUT);       //Set the Echo pins as input pins 
  bluetoothSerial.begin(9600);  //Set the baud rate to your Bluetooth module.
  attachInterrupt(0,ab1,FALLING);  //pin 9
}
 
void ab1() {
  digitalWrite(S1Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(S1Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S1Trig, LOW);
  duration= pulseIn(S1Echo, HIGH);          //Get the pulse
  distance=duration / 29 / 2;               //Convert time to the distance
  return duration;                          // Return the values from the sensor
  }
void loop(){
  if(bluetoothSerial.available() > 0){     
      state = bluetoothSerial.read();   
    }
    if (state == '0'){
      vSpeed=25;}
    else if (state == '1'){
      vSpeed=51;}
    else if (state == '2'){
      vSpeed=76;}
    else if (state == '3'){
      vSpeed=102;}
    else if (state == '4'){
      vSpeed=127;}
    else if (state == '5'){
      vSpeed=153;}
    else if (state == '6'){
      vSpeed=178;}
    else if (state == '7'){
      vSpeed=204;}
    else if (state == '8'){
      vSpeed=129;}
    else if (state == '9'){
      vSpeed=255;}
    else if (state == 'q'){
      vSpeed=255;}      
    if (state == 'F') {
  motor1.setSpeed(vSpeed); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(vSpeed); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(vSpeed); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(vSpeed); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
    }
    else if (state == 'B') {
  motor1.setSpeed(vSpeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(vSpeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(vSpeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(vSpeed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
    }
    else if (state == 'L') {
  motor1.setSpeed(vSpeed/2); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(vSpeed/2); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(vSpeed); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(vSpeed); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
    }
    else if (state == 'R') {
  motor1.setSpeed(vSpeed); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(vSpeed); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(vSpeed/2); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(vSpeed/2); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
    }
    else if (state == 'G') {
  motor1.setSpeed(vSpeed/2); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(vSpeed/2); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(vSpeed); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(vSpeed); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
    }
    else if (state == 'I') {
  motor1.setSpeed(vSpeed); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(vSpeed); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(vSpeed/2); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(vSpeed/2); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
    }
    else if (state == 'H') {
  motor1.setSpeed(vSpeed/2); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(vSpeed/2); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(vSpeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(vSpeed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
    }
    else if (state == 'J') {
  motor1.setSpeed(vSpeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(vSpeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(vSpeed/2); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(vSpeed/2); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise      
    }
    else if (state == 'S'){
  motor1.setSpeed(0);  //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0);  //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0);  //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0);  //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button      
    }   
      }