// Include the Wire library for I2C
#include <Wire.h>

// LED on pin 13
const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 5; 
const int IN4 = 4;

void avanzar();
void retroceder();
void detenerse();

void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x8);
  Serial.begin(9600);
  
  // Call receiveEvent when data received                
  Wire.onReceive(receiveEvent);
  
  pinMode (IN4, OUTPUT);    // Input4 conectada al pin 4  -> if(4H and 3LW) -> REVERSA
  pinMode (IN3, OUTPUT);    // Input3 conectada al pin 5  -> if(2H and 1LW) -> AVANZA
  pinMode (IN1, OUTPUT);    // Input1 conectada al pin 6  -> if(2H and 1LW) -> REVERSA
  pinMode (IN2, OUTPUT);    // Input2 conectada al pin 7  -> if(1H and 2LW) -> AVANZA
}



// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    if (c == 1) avanzar();
    else if (c == 2) detenerse();
    else if (c == 3) retroceder();
  }
}

void avanzar() {
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, HIGH);
}

void retroceder() {
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1, LOW);
}


void detenerse() {
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, LOW);
}

void loop() {
  delay(100);
}
