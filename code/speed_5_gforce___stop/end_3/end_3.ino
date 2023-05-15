  #include <Arduino.h>//إستدعاء المكتبة الخاصة بالاردوينو
  #include <TimerOne.h>//إستدعاء المكتبة الخاصة بالتايمر المساعد للالتراسونك 
  #include <gForceAdapterC.h>//إستدعاء المكتبة الخاصة بالحساس 
  #include <AFMotor.h>//إستدعاء المكتبة الخاصة  ب AF Shield
  #include <SoftwareSerial.h>//تنفيذ برنامج للإتصال التسلسلي لاستخدام منافذ تسلسليه اضافيه علي الاردوينو
  #define gforceSerial Serial //تعريف الأطراف الخاصة بالحساس 
  #define Timeout //وقت استقبال اشارة جديدة 1000                  //initial
 motors pin
  #define ULTRASONIC_PIN_INPUT      2 //بيعرف طرف echo الالتراسونك موصل علي الرجل 2
  #define ULTRASONIC_PIN_OUTPUT     9 //بيعرف طرف trig الالتراسونك موصل علي الرجل 9
  #define ULTRASONIC_TIMER_US       50000 
  SoftwareSerial bluetoothSerial(0,1);     //RX, TX
  AF_DCMotor motor1(1, MOTOR12_1KHZ); 
  AF_DCMotor motor2(2, MOTOR12_1KHZ);
  AF_DCMotor motor3(3, MOTOR34_1KHZ);
  AF_DCMotor motor4(4, MOTOR34_1KHZ);
  volatile long ultrasonic_echo_start = 0;
  volatile long ultrasonic_distance = 0;


void setup() دالة تحتوى علي الأوامر التي يتم تنفيذها في اول البرنامج ولمره واحده 
{   
//قوس فتح الداله
  bluetoothSerial.begin(115200);  // 
  Serial.begin(115200);
  gforceSerial.begin(115200);
  pinMode(ULTRASONIC_PIN_INPUT, INPUT_PULLUP);//يتم تعريف حاله الطرف ultrasonicpin input أنه طرف إدخال 
  pinMode(ULTRASONIC_PIN_OUTPUT, OUTPUT);//يتم تعريف حاله الطرف ultrasonicpinoutput انه طرف اخراج
  Timer1.initialize(ULTRASONIC_TIMER_US);//التايمر بيعد في طرف trig 
  Timer1.attachInterrupt(ultrasonicPulse);//التايمر بيستقبل من طرف echo 
  attachInterrupt(digitalPinToInterrupt(ULTRASONIC_PIN_INPUT), ultrasonicEcho, FALLING);
}

void loop()//داله تحتوى علي أوامر يتم تنفيذها أكثر من مرة
{
//قوس فتح الداله
struct GF_Data gForceData;
struct GF_Euler Euler;
GF_Ret ret = GFC_GetgForceData((&gForceData), Timeout);
  if(ultrasonic_distance >= 30)//داله شرطيه(اذا كانت المسافه المقاسه بالالتراسونك اكبر من أو تساوى) 30
{
فتح قوس الداله الشرطيه الأولي //
    if (GF_RET_OK == ret)//داله شرطيه() 
 { فتح قوس الداله الشرطيه الثانيه//
      GF_Gesture gesture;
      switch (gForceData.type){
      case GF_Data::QUATERNION:
      GFC_QuaternionToEuler(&(gForceData.value.quaternion), &Euler);
      break;
      case GF_Data::GESTURE:
      gesture = gForceData.value.gesture;
//الحركات الخاصة بالتحريك 
      if (gesture == GF_FIST ) // اذا  كانت الحركه المطبقه علي الحساس FIST 
سوف يتم تنفيذ ما بداخل  داله  forward 
{// ifقوس فتح دالة  
      forward();//داله الحركه الي الأمام 
      }//قوس غلق داله if
      else if (gesture == GF_SPREAD)//اذا كانت الحركه المطبقه علي الحساس SPREAD سوف يتم تنفيذ   دالة back ما بداخل  
{//فتح قوس داله else if 
      back();// دالة الحركة الي الخلف 
      }//قوس غلق else if
      else if (gesture == GF_WAVEIN)//إذا كانت الحركة المطبقه على الحساس WAVEINيتم تنفيذ ما بداخل داله forward right 
{//قوس فتح else if 
      forward_right();//دالة الحركة الي الأمام يمين 
      }//قوس غلق else if 
      else if (gesture == GF_WAVEOUT)//إذا كانت الحركة المطبقه على الحساس WAVEOUTيتم تنفيذ ما بداخل داله forward left
{//قوس فتح else if 
      forward_left();// دالة الحركة الي الأمام يسار 
      }//قوس غلق else if 
      else if (gesture == GF_PINCH)//إذا كانت الحركة المطبقه على الحساس PINCHيتم تنفيذ ما بداخل داله left 
{//قوس فتح else if 
      left();//دالة الحركة يسار 
      }//قوس غلق else if 
      else if (gesture == GF_SHOOT)//إذا كانت الحركة المطبقه على الحساس SHOOT يتم تنفيذ ما بداخل داله right 
{    //قوس فتحelse if  
      right();//دالة الحركة الي اليمين
      }//قوس غلق else if 
      else if (gesture == GF_RELEASE)//إذا كانت الحركة المطبقه على الحساس RELEASEيتم تنفيذ ما بداخل داله stop 
{    //قوس فتح else if 
      Stop();//دالة الوقوف 
      }قوس غلق else if 
      break;// يتم ايقاف الحلقه عند تحقق الشرط 
      default:// في حالة عدم تحقيق الشرط يتم تنفيذ ما بداخل default
      break; يتم تشغيل ما بداخل الحاله فقط وليس كل ما بعدها 
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
  digitalWrite(ULTRASONIC_PIN_OUTPUT, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_PIN_OUTPUT, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_PIN_OUTPUT, LOW);
  ultrasonic_echo_start = micros();
}

void ultrasonicEcho(){
  if(ultrasonic_echo_start != 0){
    ultrasonic_distance = (micros() - ultrasonic_echo_start) / 58;
    ultrasonic_echo_start = 0;
  }
}