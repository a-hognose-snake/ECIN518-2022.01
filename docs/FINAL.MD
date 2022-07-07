# Informe Técnico - Entrega Final
## Curso: Proyecto Integrador Plataformas TI
*Alumnos:*
* Joaquín Aravena O’Brien
* Josefina Figueroa Ubilla
* Cristian Galleguillos Araya

## Resumen
![image](/images/final/MrRobot.jpeg)
El trabajo realizado buscaba implementar un robot que pudiera mover dos ruedas en conjunto a través de un driver puente H L298N 2A con un Arduino y una Raspberry pi conectados a través el protocolo i2c (maestro-esclavo). El programa ejecutado permite controlar el movimiento de ruedas (avanzar, retroceder y detenerse) mediante la detección de figuras, para cada figura detectada por la Raspberry se manda un byte de información con la acción que queremos que ejecute el arduino, los códigos y las acciones son las siguientes:

0x1 -> Avanzar (detecta una figura de 3 lados)

0x2 -> Retroceder (detecta una figura de 4 lados)

0x3 -> Detenerse (detecta una figura con > de 4 lados)

 Cabe mencionar que la figura a mostrar no puede estar a más de 30 cm del módulo de la cámara a causa de limitaciones de hardware y también de software, además el programa trabaja con umbralización esto quiere decir que lo configuramos para que detecte solamente figuras que sean de un color mayor al umbral (en nuestro caso solo detecta figuras blancas).
 ![image](/images/final/FigurasRojo.jpeg)


## 1. Introducción

El presente trabajo busca poder mover ruedas conectadas a un driver puente H L298N 2A con arduinos conectados gracias al protocolo i2c (maestro-esclavo), tomando en concideración las figuras detectadas por la Raspberry pi. 

### 1.1 Objetivo

**Objetivo General**

Entender la interacción que se genera entre una raspberry y Arduino utilizando el protocolo de comunicación I2C, implementando un mini robot capaz de utilizar la cámara (Open CV) para realizar diferentes acciones en base a lo que detecte, en este caso, el robot identificara figuras y moverá las ruedas.

### 1.2 Solución propuesta

Crear comunicación I2C entre la Raspberry Pi (Maestro) y Arduino (Esclavo). En la raspberry se implementará un script en python el cual utilizara OpenCV para tomar decisiones, aquellas decisiones serán enviadas hacia el esclavo (Arduino) para que haga funcionar los motores.

## 2. Materiales y métodos

Para el desarrollo del presente trabajo, utilizamos:

- 1 Raspberry Pi
- 1 Arduino uno
- 1 Driver puente H L298N 2A
- 2 Motores
- 1 Batería
- Cables jumper
- 1 Chasis
- Pernos
- Tuercas
- Golillas


### 2.1 Instalación
IDE:
- Arduino
[Descargar IDE de Arduino](https://www.arduino.cc/en/software)
- Thonny (Integrado en la Raspberry Pi)

### 2.2 Implementación

Lo primero que se realizó fue establecer la conexión I2C entre la Raspberry Pi (Maestro) y Arduino (Esclavo), para probar el funcionamiento de este, se realizó una prueba simple, la cual consistía en encender un par de leds en base a las teclas presionadas desde un Script que se estaba ejecutando en la Raspberry. Ya con el I2C probado, pasamos a trabajar netamente en la Raspberry. Ya que el objetivo era crear un robot el cual trabajara detectando figuras, tuvimos que utilizar OpenCV para el procesamiento de las imágenes que iba a recibir la cámara de nuestra Raspberry.

Al momento de crear un Script para esta tarea, surgieron diferentes problemas a la hora de realizar las pruebas de detección de objetos. El problema principal que encontramos fue que la cámara detectaba muchas figuras, esto debido a que el rango de detección era demasiado grande. Para disminuir la detección innecesaria, se trabajó bajo el modelo de detección propuesto por el profesor de la asignatura. Aquel, consistía en solo detectar figuras en dos áreas acotadas dentro del campo de visión y no en la imagen completa. La solución al problema anterior fue limitar el campo de visión para la detección sector izquierdo y derecho del campo de visión del módulo cámara. 

La solución anterior corrigió la mayoría de los problemas que teníamos y nos permitió salir del impedimento que no nos dejaba continuar con el proyecto. Luego de encontrar la solución a la detección innecesaria, definimos la máscara que utilizará OpenCV para limitar el campo de detección. También se importó smbus para el I2C y se definieron variables para ser utilizadas en ello.
```python
from smbus2 import SMBus
# i2c
ADDR = 0x8
bus = SMBus(1)
AVANZAR = 0x1
RETROCEDER = 0x2
DETENERSE = 0x3
```

```python
mask = np.zeros((480, 640), dtype=np.uint8)
mask[0:480,140:500] = 255
mask[0:100,0:640] = 255
mask[380:480,0:640] = 255
mask = cv.bitwise_not(mask)
```
Luego, añadimos la máscara a la imagen en grises proveniente desde la cámara y aplicamos un umbral para que OpenCV detecte figuras de color blanco.

```python
	#Todo esto esta dentro del while principal del programa
    ret, frame = capture.read()
    # Pasamos el video a escala de grises
    image_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    # Aplicamos una máscara para detectar las figuras solo en esa zona
    im_area = cv.bitwise_and(image_gray, image_gray, mask=mask)
	# Aplicamos un umbral para que detecte figuras blancas
    _, threshold = cv.threshold(im_area, 250, 255, cv.THRESH_BINARY)
```
Obtuvimos los contornos.

```python
	contours, _ = cv.findContours(threshold, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
```
Luego, tuvimos que evaluar cada contorno detectado. Para ello, recorremos los contornos.

```python
	for contour in contours:
```
Filtramos el área del contorno para que no se detectaran figuras de tamaño diminuto. Para ello, con que tengan un área mayor a 500 basta.

```python
        area = cv.contourArea(contour)
        if area > 500:
```
Calculamos approx. Approx nos sirve para saber que figura estará detectando la cámara.
```python
			epsilon = .02* cv.arcLength(contour, True)
            approx = cv.approxPolyDP(contour, epsilon, True)
```
Ahora, en base al largo de approx, se verifica que figura detecto, los casos son solo 3.

Caso 1 (Triángulo): En este caso, si el algoritmo detectaba un triángulo, se le enviaba a Arduino la señal correspondiente a Avanzar.
```python
            if len(approx) == 3:
                bus.write_byte(ADDR, AVANZAR)
```
Caso 2 (Cuadrado): En este caso, si el algoritmo detectaba un cuadrado, se le enviaba a Arduino la señal correspondiente a Retroceder.
```python
            elif len(approx) == 4:
                bus.write_byte(ADDR, RETROCEDER)
```
Caso 3 (Círculo): En este último caso, si el algoritmo detectaba un círculo, se le enviaba a Arduino la señal correspondiente a Detenerse.
```python
            elif len(approx) >=5:
                bus.write_byte(ADDR, DETENERSE)
```
Una vez implementado el algoritmo a utilizar, se armó el circuito y luego de probar su funcionamiento, se montaron las conexiones correspondientes entre el arduino y el driver en el chasis.

![image](/images/final/faltan/RuedasEnChasis.jpeg)
![image](/images/final/faltan/RuedasPorLado.jpeg)


Por último, se conectaron los motores al driver, los cables fueron soldados a los motores.
![image](/images/final/NoHaySoldadura.jpeg)
![image](/images/final/faltan/FuncionaConectadoAun.jpeg)
![image](/images/final/faltan/CablesSinControl.jpeg)

 

Código Fuente:

- [Maestro](/src/Maestro/testing.py)
- [Esclavo](/src/Esclavo/esclavo.ino)

## 3. Resultados obtenidos

![image](/images/final/MrRobotFinal.gif)


El resultado obtenido fue el que se esperaba, ya que, logramos que las ruedas del robot avanzaran, retrocedas o se detuvieran en base a lo detectado.