int xAxis, yAxis;

void setup() {
  Serial.begin(38400);
}

void loop() {
  xAxis = analogRead(A0);
  yAxis = analogRead(A1);
  Serial.write(xAxis/4); 
  Serial.write(yAxis/4);
  delay(20);
}