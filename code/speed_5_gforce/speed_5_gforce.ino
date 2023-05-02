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
int SYS_GetChar(unsigned char *data){
  int ret = gforceSerial.read();
  if (ret == -1)
  return 0;
  *data = (unsigned char)ret;
  return 1;
}
/* returns System time */
unsigned long SYS_GetTick(void){
  return millis();
}
void setup(){
  bluetoothSerial.begin(115200);  //Set the baud rate to your Bluetooth module.
  Serial.begin(115200);
  gforceSerial.begin(115200);
}
void loop() {
  struct GF_Data gForceData;
  struct GF_Euler Euler;
  GF_Ret ret = GFC_GetgForceData((&gForceData), Timeout);

  if (GF_RET_OK == ret)
  {
    GF_Gesture gesture;

    switch (gForceData.type)
    {
    case GF_Data::QUATERNION:
      GFC_QuaternionToEuler(&(gForceData.value.quaternion), &Euler);
      break;

    case GF_Data::GESTURE:
      gesture = gForceData.value.gesture;
      Serial.print("gesture: ");
      Serial.println(gesture);

      if (gesture == GF_FIST){
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
  else {
    Serial.print("GFC_GetgForceData() returned: ");
    Serial.println(ret);
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