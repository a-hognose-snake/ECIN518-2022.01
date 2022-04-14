# Informe Técnico - Semana 3
## Curso: Proyecto Integrador Plataformas TI

*Alumnos:*
* Joaquín Aravena O’Brien
* Josefina Figueroa Ubilla
* Cristian Galleguillos Araya

## Resumen

El trabajo realizado buscaba implementar un programa que pudiera mover dos motores con ruedas en conjunto con Arduino a través de un driver puente H L298N 2A. El programa debía ser capaz de hacer que las ruedas avanzaran o retrocedieran dependiendo de la tecla que se presionara: 

w -> avanzar

s -> retroceder

k -> parar
## 1. Introducción

El presente trabajo busca identificar y responder lo siguiente:

    1. ¿Qué es el driver puente H L298N 2A?
    2. ¿Cómo conectamos los motores con el driver y con Arduino?
    3. ¿Cómo logramos que Arduino mueva los motores?

### 1.1 Objetivo

**Objetivo General**

Entender como interactúa Arduino con los motores a través del driver L298N 2A.

### 1.2 Solución propuesta

Crear un programa capaz de hacer que Arduino controle los motores mediantes órdenes entregadas por consola.

## 2. Materiales y métodos

Para el desarrollo del presente trabajo, utilizamos:

- 1 Mouse
- 1 Teclado
- 1 Monitor
- 1 Arduino uno
- 1 Driver puente H L298N 2A
- 2 Motores.

### 2.1 Instalación
IDE:
- Arduino
[Descargar IDE de Arduino](https://www.arduino.cc/en/software)

### 2.2 Implementación
Se revisó levemente que era el driver puente H L298N 2A en conjunto con el profesor, explicando su funcionamiento y la finalidad de este. En este caso, el driver nos servirá para poder mover los motores. Para entender las partes del driver, se siguió una guía sobre como conectar un motor a Arduino con un driver.

![image](images/semana_3/driver.jpg)

Se realizaron las conexiones correspondientes entre el arduino y el driver siguiendo el esquema que está a continuación:

![image](images/semana_3/conexion_1.jpg)

Y el resultado obtenido fue el siguiente:

![image](images/semana_3/conexion_2.jpg)

Por último, se conectaron los motores al driver, los cables fueron soldados a los motores.

![image](images/semana_3/conexion_3.jpg)

Una vez que ya se tenía todo conectado correctamente, se tuvo que realizar el código en el IDE de Arduino, para mandarle instrucciones al Arduino. Primero definimos las variables correspondientes a las teclas que se utilizaran para hacer avanzar/retrocedes/parar a los motores, también declaramos las variables correspondientes a los pines del driver:
``` ino
#define KEY_W 119    // -> Corresponde a la tecla 'w'
#define KEY_S 115    // -> Corresponde a la tecla 's'
#define KEY_STOP 107 // -> Corresponde a la tecla 'k'

int IN1 = 6;
int IN2 = 7;
int IN3 = 5;
int IN4 = 4;
```
Luego, inicializamos los pines en la función setup, también inicializamos Serial, ya que nos servirá para detectar los input de las teclas:

```ino
void setup() 
{
    pinMode(IN4, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    Serial.begin (9600);
}
```
Ahora, creamos una función que evaluara si se presiona o no una tecla, si una tecla es presionada, se llamara a la función realizarMovimiento():

```ino
void evaluarKey() 
{
  if (Serial.available() > 0) { // -> Si Serial.available() > 0, significa que se ingreso un dato.
    incomingByte = Serial.read(); // -> Se está leyendo el numero de la tecla presionada.
    realizarMovimiento(int incomingByte);         
  }
}
```
Creamos la función realizarMovimiento(incomingByte) la cual recibe como parámetro el número de la tecla ingresada y en base a lo que se presione, le dirá a los pines que estén en HIGH o LOW:

```ino
void realizarMovimiento(int incomingByte) 
{
  switch(incomingByte) {
    case KEY_S: // -> REVERSA
      digitalWrite(IN4, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN1, LOW);
      break;  
    case KEY_W: // -> AVANZA
      digitalWrite(IN4, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN1, HIGH);
      break;
    case KEY_STOP: // -> STOP
      digitalWrite(IN4, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN1, LOW);
      break;
  }
}
```
Por último, llamamos la funcion evaluarKey() desde nuestro loop:
```ino
void loop()
{     
  evaluarKey();
}
```
## 3. Resultados obtenidos

El resultado obtenido fue el que se esperaba, ya que, logramos que las ruedas avanzaran, retrocedas o se detengan en base a lo que se presione.


## 4. Conclusiones



# Referecias
https://electronilab.co/tutoriales/tutorial-de-uso-driver-dual-l298n-para-motores-dc-y-paso-a-paso-con-arduino/
