const int motorA1  = 6;  // L298N'in IN3 Girii
  const int motorA2  = 7;  // L298N'in IN1 Girii
  const int motorB1  = 8; // L298N'in IN2 Girii
  const int motorB2  = 9;  // L298N'in IN4 Girii


  int i=0; //Dngler iin atanan rastgele bir deiken
  int j=0; //Dngler iin atanan rastgele bir deiken
  int state; //Bluetooth cihazndan gelecek sinyalin deikeni
  int vSpeed=255;     // Standart Hz, 0-255 aras bir deer alabilir

void setup() {
    // Pinlerimizi belirleyelim
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);  
    pinMode(5, OUTPUT); 
    pinMode(10, OUTPUT);  
    pinMode(2, OUTPUT);  
    pinMode(3, OUTPUT);  
    pinMode(4, OUTPUT);   
    // 9600 baud hznda bir seri port aalm
    Serial.begin(9600);
}
 
void loop() {
  digitalWrite(5,HIGH);
  digitalWrite(10,HIGH);
  
  /*Bluetooth balants koptuunda veya kesildiinde arabay durdur.
 (Aktif etmek iin alt satrn "//" larn kaldrn.)*/
//     if(digitalRead(BTState)==LOW) { state='S'; }

  //Gelen veriyi 'state' deikenine kaydet
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
  
  /* Uygulamadan ayarlanabilen 4 hz seviyesi.(Deerler 0-255 arasnda olmal)*/
    if (state == '0'){
      vSpeed=0;}
    else if (state == '1'){
      vSpeed=100;}
    else if (state == '2'){
      vSpeed=180;}
    else if (state == '3'){
      vSpeed=200;}
    else if (state == '4'){
      vSpeed=255;}
     
  /***********************leri****************************/
  //Gelen veri 'F' ise araba ileri gider.
    if (state == 'F') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        analogWrite(motorB1, vSpeed);      analogWrite(motorB2, 0); 
        digitalWrite(2,LOW); 
        digitalWrite(3,LOW); 
        digitalWrite(4,HIGH);
         
    }
  /**********************leri SA************************/
  //Gelen veri 'G' ise araba ileri sol(apraz) gider.
    else if (state == 'I') {
      analogWrite(motorA1,vSpeed ); analogWrite(motorA2, 0);  
        analogWrite(motorB1, 100);    analogWrite(motorB2, 0);
        digitalWrite(2,HIGH); 
        digitalWrite(4,LOW); 
    }
  /**********************leri SOL************************/
  //Gelen veri 'I' ise araba ileri sa(apraz) gider.
    else if (state == 'G') {
        analogWrite(motorA1, 100); analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);      analogWrite(motorB2, 0);
        digitalWrite(3,HIGH); 
        digitalWrite(4,LOW);  
    }
  /***********************Geri****************************/
  //Gelen veri 'B' ise araba geri gider.
    else if (state == 'B') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, vSpeed); 
    }
  /**********************Geri Sol************************/
  //Gelen veri 'H' ise araba geri sol(apraz) gider
    else if (state == 'H') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 100); 
        analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
    }
  /**********************Geri Sa************************/
  //Gelen veri 'J' ise araba geri sa(apraz) gider
    else if (state == 'J') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 100);
        digitalWrite(2,HIGH);  
        digitalWrite(4,LOW); 
    }
  /***************************Sol*****************************/
  //Gelen veri 'L' ise araba sola gider.
    else if (state == 'L') {
      analogWrite(motorA1, vSpeed);   analogWrite(motorA2, 150); 
        analogWrite(motorB1, 0); analogWrite(motorB2, 0); 
        digitalWrite(3,HIGH); 
        digitalWrite(4,LOW); 
    }
  /***************************Sa*****************************/
  //Gelen veri 'R' ise araba saa gider
    else if (state == 'R') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);   analogWrite(motorB2, 150);
        digitalWrite(2,HIGH); 
        digitalWrite(4,LOW);      
    }
  
  /************************Stop*****************************/
  //Gelen veri 'S' ise arabay durdur.
    else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
        digitalWrite(4,LOW); 
    }  
}
