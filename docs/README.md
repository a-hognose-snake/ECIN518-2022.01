# Informe Técnico - Semana 1
## Curso: Proyecto Integrador Plataformas TI

*Alumnos:*
* Joaquín Aravena O’Brien
* Josefina Figueroa Ubilla
* Cristian Galleguillos Araya

## Resumen 

El trabajo realizado buscaba investigar y entender el funcionamiento de una Raspberry Pi y integrar el módulo de cámara.

## 1. Introducción

El presente trabajo busca identificar y responder lo siguiente:

    1. Identificar los pines de la Raspberry Pi
    2. ¿Qué es la Raspberry Pi?
    3. ¿Cómo funciona la Raspberry Pi?
    4. ¿Cómo trabajar con una Raspberry Pi?
    5. Conecte la Raspberry, e indague su funcionamiento
    6. Describa el entorno de trabajo de la Raspberry Pi
    7. ¿Qué cámara tiene conectada la Raspberry Pi?
    8. Indague cómo hacer funcionar la cámara con la Raspberry
    9. Trace los siguientes pasos para continuar con el proyecto

### 1.1 Objetivo

**Objetivo General**

Entender el funcionamiento de una Raspberry Pi y su integración con el módulo de cámara.

### 1.2 Solución propuesta

Detectar visualmente las partes de las Raspberry Pi, investigar su funcionamiento, hacer funcionar y integrar el modulo de cámara.

## 2. Materiales y métodos

Para el desarrolo del presente trabajo, utilizamos:

- 1 Raspberry Pi
- 1 Modulo de Cámara
- 1 Mouse
- 1 Teclado
- 1 Monitor
- 1 Tarjeta Micro SD

### 2.1 Instalación
Sistema Operativo:
- Raspberry Pi OS

IDE:
- Visual Studio Code
- Thonny Python IDE

[Guía de Instalación para Módulo de Cámara ](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/4)

[Guía de Instalación Raspberry Pi OS ](https://www.youtube.com/watch?v=ntaXWS8Lk34)

### 2.2 Implementación
La Raspberry Pi es un computador de bajo costo y tamaño pequeño. Tiene un sistema operativo y soporta el uso de periféricos y módulos para poder interactuar con su ambiente. Funciona como un mini laboratorio de exploración computacional o simplemente ayuda a recrear proyectos a baja escala, dadas sus limitaciones en términos de poder computacional y almacenamiento.

Para familiarizarnos con le computador y el modulo, identificamos visualmente los puertos de la Raspberry Pi.

![image](/images/parts.png)

Al intentar prender el computador conectando la fuente de poder, nos encontramos con muchos errores en el monitor, por lo cual volvimos a instalar el sistema operativo utilizando la guía en “2.1 Instalación”.

![image](/images/raspi-config.jpeg)

![image](/images/camera-on.jpeg)

Al tener el sistema operativo funcionando sin errores, conectamos el módulo de la cámara utilizando la guía en “2.1 Instalación”.

![image](/images/code1.jpeg)

![image](/images/terminal.png)

Para probar el funcionamiento de la cámara, escribimos un script en Thonny Python IDE y lo ejecutamos desde la terminal.

## 3. Resultados obtenidos

![image](/images/foto1.jpeg)

Computador y modulo de cámara funcional, en conjunto con mayor entendimiento acerca del funcionamiento de la Raspberry Pi y fotos del procedimiento.

## 4. Conclusiones

Es necesario leer documentación previo a jugar con los módulos, ya que los pines de conexión son delicados.

Cabe mencionar que las imágenes salen con un color medio rosado, al parece es un problema común con las cámaras de Raspberry Pi y tendremos que investigar más al respecto para ver si es que se puede arreglar esa tonalidad o si esto no es de importancia dado el objetivo final del proyecto.


# Referecias

1. Timmons-Brown, M. (2019). Learn Robotics with Raspberry Pi: Build and Code Your Own Moving, Sensing, Thinking Robots. Ανακτήθηκε από https://books.google.cl/books?id=V1v6DwAAQBAJ
