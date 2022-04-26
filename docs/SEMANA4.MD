# Informe Técnico - Semana 4
## Curso: Proyecto Integrador Plataformas TI

*Alumnos:*
* Joaquín Aravena O’Brien
* Josefina Figueroa Ubilla
* Cristian Galleguillos Araya

## Resumen

El trabajo realizado buscaba implementar un programa que pudiera mover dos ruedas en conjunto a través de un driver puente H L298N 2A con arduinos conectados gracias al protocolo i2c (maestro-esclavo). El script ejecutado permite parar el movimiento de ruedas, avanzar y retroceder. Las lecturas del potenciometro funcionan de tal forma que: 

0 -> para

1 -> avanza

2 -> retrocede

## 1. Introducción

El presente trabajo busca poder mover ruedas conectadas a un driver puente H L298N 2A con arduinos conectados gracias al protocolo i2c (maestro-esclavo), tomando en concideración las lecturas de potenciometro como dirrección de movimiento. 

### 1.1 Objetivo

**Objetivo General**

Entender como interactúan arduinos con las ruedas conectadas a un driver puente H L298N 2A y darles dirrecciones con un potenciometro.

### 1.2 Solución propuesta

Crear un programa capaz de hacer que los Arduinos controlen los motores mediantes comunicación i2c y a lectura de un pontenciometro.

## 2. Materiales y métodos

Para el desarrollo del presente trabajo, utilizamos:

- 2 Arduino uno
- 1 Driver puente H L298N 2A
- 2 Motores
- 1 Potenciómetro
- Cables jumper

### 2.1 Instalación
IDE:
- Arduino
[Descargar IDE de Arduino](https://www.arduino.cc/en/software)

### 2.2 Implementación
Se revisó levemente que era el driver puente H L298N 2A en conjunto con el profesor, explicando su funcionamiento y la finalidad de este. En este caso, el driver nos servirá para poder mover los motores. Para entender las partes del driver, se siguió una guía sobre como conectar un motor a Arduino con un driver.

![image](/images/semana_3/driver.jpg)

Se realizaron las conexiones correspondientes entre el arduino y el driver siguiendo el esquema que está a continuación:

![image](/images/semana_3/conexion_1.jpg)

Por último, se conectaron los motores al driver, los cables fueron soldados a los motores.

Una vez que ya se tenía todo conectado correctamente, se tuvo que realizar el código en el IDE de los arduinos para el maestro y el esclavo correspondientemente y tambien se hizo el circuito para la correcta lectura del potenciometro y así mandarle instrucciones a las ruedas. 

![image](/images/maestro-esclavo.jpeg)

Código Fuente:

- [Maestro](/src/Maestro/Maestro.ino)
- [Esclavo](/src/Esclavo/Esclavo.ino)

## 3. Resultados obtenidos

![Alt Text](/images/semana4.gif)

El resultado obtenido fue el que se esperaba, ya que, logramos que las ruedas avanzaran, retrocedas o se detengan en base a lo que se lea desde el potenciómetro.
