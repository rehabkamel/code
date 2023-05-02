#include <gForceAdapterC.h>
#include <AFMotor.h>
#include <SoftwareSerial.h>
#define gforceSerial Serial
SoftwareSerial bluetoothSerial(0,1);     //RX, TX
#define Timeout 1000                      //initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
char command;

#include <Arduino.h>
// Uses https://github.com/PaulStoffregen/TimerOne for sending on a regular interval
#include <TimerOne.h>

// ECHO pin, needs to be a pin that supports interrupts!
#define ULTRASONIC_PIN_INPUT      2
// TRIG pin, can be any output pin
#define ULTRASONIC_PIN_OUTPUT     9
// update interval, make sure to keep it above 20ms
#define ULTRASONIC_TIMER_US       50000 

// the time the pulse was sent
volatile long ultrasonic_echo_start = 0;
// the distance once it's been measured
volatile long ultrasonic_distance = 0;


void setup(){
  bluetoothSerial.begin(115200);  
  Serial.begin(115200);
  gforceSerial.begin(115200);

    // set the echo pin to receive interrupts, on an arduino uno only pin 2 and 3 can link to interrupts
    pinMode(ULTRASONIC_PIN_INPUT, INPUT_PULLUP);
    pinMode(ULTRASONIC_PIN_OUTPUT, OUTPUT);
  
    // set the update interval for sending the trigger
    Timer1.initialize(ULTRASONIC_TIMER_US);
    // link the trigger function to the timer
    Timer1.attachInterrupt(ultrasonicPulse);
    // link the echo function to the echo pin
    attachInterrupt(digitalPinToInterrupt(ULTRASONIC_PIN_INPUT), ultrasonicEcho, FALLING);
    
}

void loop() {
  struct GF_Data gForceData;
  struct GF_Euler Euler;
  GF_Ret ret = GFC_GetgForceData((&gForceData), Timeout);
  if(ultrasonic_distance >= 30){
  if (GF_RET_OK == ret) {
    GF_Gesture gesture;
    switch (gForceData.type){
    case GF_Data::QUATERNION:
      GFC_QuaternionToEuler(&(gForceData.value.quaternion), &Euler);
      break;
      case GF_Data::GESTURE:
      gesture = gForceData.value.gesture;
      if (gesture == GF_FIST ){
        forward();
      }
      else if (gesture == GF_SPREAD){
        back();
      }
      else if (gesture == GF_WAVEIN){
        forward_right();
      }
      else if (gesture == GF_WAVEOUT){
        forward_left();
      }
      else if (gesture == GF_PINCH){
        left();
      }
      else if (gesture == GF_SHOOT){      
        right();
      }
      else if (gesture == GF_RELEASE){
        Stop();
      }
      break;
      default:
      break;
    }
  }
  else {            //else rate
  Stop();
   }
  }
  
  else{         //else ultra
  Stop();
  delay(1000);
  back();
  delay(2000);
  Stop();
    }
}

void forward(){
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void back(){
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void left(){
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void right(){
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}
void forward_left(){
  motor1.setSpeed(125); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(125); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void forward_right(){
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(125); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(125); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void back_left(){
  motor1.setSpeed(125); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(125); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void back_right(){
 motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(125); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(125); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void Stop(){
  motor1.setSpeed(0);  //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0);  //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0);  //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0);  //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}
int SYS_GetChar(unsigned char *data){
  int ret = gforceSerial.read();
  if (ret == -1)
  return 0;
  *data = (unsigned char)ret;
  return 1;
}
unsigned long SYS_GetTick(void){
  return millis();
}


void ultrasonicPulse(){
    // Clears the trigger Pin
    digitalWrite(ULTRASONIC_PIN_OUTPUT, LOW);
    delayMicroseconds(2);
    // Sets the trigger on HIGH state for 10 micro seconds to send a series of pulses
    digitalWrite(ULTRASONIC_PIN_OUTPUT, HIGH);
    // blocks 10 microseconds from the interrupt, I think we'll live :)
    delayMicroseconds(10);
    // disable the sending again so we can wait for a response
    digitalWrite(ULTRASONIC_PIN_OUTPUT, LOW);
    // record the send time
    ultrasonic_echo_start = micros();
}


void ultrasonicEcho(){
    // don't do anything if no pulse has been sent
    if(ultrasonic_echo_start != 0){
        // calculate the distance by measuring how long it took to return the sound
        // The speed of sound is 343 m/s and we need half the time it took (since
        // the sound has to travel towards the object _AND_ back). So a single echo does
        // 1/(343/2) = 0.005831 seconds per meter
        ultrasonic_distance = (micros() - ultrasonic_echo_start) / 58;
        ultrasonic_echo_start = 0;
    }
}
