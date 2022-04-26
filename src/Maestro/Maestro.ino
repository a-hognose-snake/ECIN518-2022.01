#include "Wire.h"

byte cod;
int IN1 = 6;
int IN2 = 7;
int IN3 = 5; 
int IN4 = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode (IN4, OUTPUT);    // Input4 conectada al pin 4  -> if(4H and 3LW) -> REVERSA
  pinMode (IN3, OUTPUT);    // Input3 conectada al pin 5  -> if(2H and 1LW) -> AVANZA
  pinMode (IN1, OUTPUT);    // Input1 conectada al pin 6  -> if(2H and 1LW) -> REVERSA
  pinMode (IN2, OUTPUT);    // Input2 conectada al pin 7  -> if(1H and 2LW) -> AVANZA
  Wire.begin();
  Serial.begin(9600);
  delay(200);
}

void loop() {
  String msg = "";
  Wire.requestFrom(0x01, 1);
  while (Wire.available()){
      cod = Wire.read();
  }
  if(cod == 0) { // STOP
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW); 
  }
  else if  (cod == 1) { // AVANZAR
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, HIGH);
  }
  else if(cod == 2) { // RETROCEDER
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW);
  }
}
