import cv2 as cv
from smbus import SMBus
import numpy as np

# i2c
ADDR = 0x8
bus = SMBus(1)
AVANZAR = 0x1
RETROCEDER = 0x2
DETENERSE = 0x3

# Open CV
mask = np.zeros((480, 640), dtype=np.uint8)
mask[0:480,140:500] = 255
mask[0:100,0:640] = 255
mask[380:480,0:640] = 255
mask = cv.bitwise_not(mask)

capture = cv.VideoCapture(0)

while (capture.isOpened()):
    ret, frame = capture.read()
    # Pasamos el video a escala de grises
    image_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    # Aplicamos una máscara para detectar las figuras solo en esa zona
    im_area = cv.bitwise_and(image_gray, image_gray, mask=mask)
    # Aplicamos un umbral para que detecte figuras blancas
    _, threshold = cv.threshold(im_area, 250, 255, cv.THRESH_BINARY)
    
    contours, _ = cv.findContours(threshold, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    
    # Dibujamos el área donde se vizualizarán las figuras
    cv.rectangle(frame, (0, 100), (140, 380), (0, 255, 0), 1)
    cv.rectangle(frame, (500, 100), (639, 380), (0, 255, 0), 1)

    for contour in contours:
        area = cv.contourArea(contour)
        if area > 500:
            epsilon = .02* cv.arcLength(contour, True)
            approx = cv.approxPolyDP(contour, epsilon, True)
            cv.drawContours(frame, [approx], 0, (0, 0, 0), 5)
            x = approx.ravel()[0]
            y = approx.ravel()[1] - 5
            if len(approx) > 0 and len(approx) <= 6:
                #cv.putText(frame, "Avanzar", (x, y), cv.FONT_HERSHEY_COMPLEX, .5, (0, 0, 0))
                bus.write_byte(ADDR, AVANZAR)
            elif len(approx) > 6 and len(approx) <= 10:
                #cv.putText(frame, "Detenerse", (x, y), cv.FONT_HERSHEY_COMPLEX, .5, (0, 0, 0))
                bus.write_byte(ADDR, DETENERSE)
            elif len(approx) > 10:
                #cv.putText(frame, "Retroceder", (x, y), cv.FONT_HERSHEY_COMPLEX, .5, (0, 0, 0))
                bus.write_byte(ADDR, RETROCEDER)
    #cv.imshow('Capture', frame)
    #cv.imshow('Mask', mask)
    # Esc para salir
    key = cv.waitKey(70) & 0xFF
    if key == 27:
        bus.write_byte(ADDR, DETENERSE)
        break
capture.release()
cv.destroyAllWindows()