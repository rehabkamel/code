const int trigPin = 11;
const int echoPin = 10;
const int led = 13;

void setup() {
  Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode( led, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
  long duration, inches, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  long r = 3.4 * duration / 2;
  float distance = r / 100.00;
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  delay(100);
  if(distance<20){
  digitalWrite(led,HIGH);
 }
else{
  digitalWrite(led,LOW);
 }
 delay(300);
}