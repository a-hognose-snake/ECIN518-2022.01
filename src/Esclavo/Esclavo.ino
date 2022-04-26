#include "Wire.h"
byte entra = 0;
byte CODE;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  
  // Codigo esclavo
  Wire.begin(0x01);
  Wire.onReceive(solicitud);
  Wire.onRequest(peticion);
}

void loop() {
  int valor = analogRead(A0);
  if (valor == 0) CODE = 0;
  else if (valor > 0 && valor <= 500) CODE = 1;
  else CODE = 2;
}

void solicitud(int re) {
  while (Wire.available()) {
    entra = Wire.read();
    }
    //Serial.println(entrada);
}

void peticion () {
  Wire.write(CODE);
}
