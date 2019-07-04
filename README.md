# PIC16F84A + NEOPIXEL + CCS Compiler

Programacion del microcontrolador (uC) mas popular de Microchip, el PIC16F84A para controlar el encendido de una tira NEOPIXEL, 
la variante del uC es PIC16F84A-20, el cual puede funcionar con un crystal de hasta 20MHz.

## Introduccion

El proyecto es una pequeña lampara con 5 leds NEOPIXEL, un boton para cambiar el color (modos de funcionamiento). 
Los NEOPIXELS estan dentro de una media capsula que difumina el color de los leds. 
Los NEOPIXELS usados a pesar de que son RGB, el orden realmente de cada NEOPIXEL es GRB, tener cuidado de como se envia estos 
valores a cada NEOPIXEL.

    Nota: Para cada NEOPIXEL se usan 3 bytes, un byte por cada color G, R, B.

Para mas información sobre los Neopixel referirse a la Uberguide de Adafruit:

https://cdn-learn.adafruit.com/downloads/pdf/adafruit-neopixel-uberguide.pdf

"NeoPixel" es la marca de Adafruit para píxeles y tiras de color RGB con direcciones individuales basadas en los controladores 
LED WS2812, WS2811 y SK6812, utilizando un protocolo de control de un solo cable. Para conocer el protocolo que manejan los 
NEOPIXEL:

https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf

Requerimientos

El lenguaje usado es C proporcionado por el compilador CCS Compiler.

    * CCS Compiler v5.081, (testeado también con v4.13).

Diseño del esquema.

    * Proteus ISIS v8.

Fuente de Alimetacion.

    * Modulo LM2596 DC-DC Step-Down. Voltaje de entrada 12VDC con salida a 5VDC.

* Un Protoboard.

## Esquema

Se utilizan un boton (btn) PULL-DOWN para cambiar el color en los leds. El pin RX es usado para la recepcion de datos, por 
ejemplo, se puede setear un color a traves del puerto rs-232 de una PC hacia el PIC16F84A.

![esquema](PIC16_Neopixels.png?raw=true "esquema")

### Caracteristicas del PIC16F84A
![datasheet](pic16f84a.png?raw=true "esquema")
## Funcionamiento
Basicamente hay dos modos de operacion, el primero es realizado por el boton, el cual solo cambia de forma uniforme el color
de los NEOPIXEL, muestra los colores individuales del arcoiris y por ultimo un efecto RGB multicolor.
Se habilito la recepcion de datos seriales RX (rs-232) por software, en el pin B0 (INT_EXT) para la recepcion de datos para
setear algun color no definido por el evento del boton.
El envio y recepcion de estos datos sigue el patron:
    
    1 byte(R) -> 1 byte (G) -> 1 byte (B)
Para setear el color naranja, enviar en formato hexadecimal o su correspondiente caracter ascii:
    
    ff8000+0D -> 0D = CR(Carrier Return) 
El CR es para indicar dentro del firmware del PIC16F84A que debe procesar el color. Por lo que se espera recibir 4 bytes por 
el puerto serie. Esto es ideal para agregar un modulo bluetooth y con una app, controlar el color desde un smartphone.

    Nota: Debido a la limitada RAM (68 bytes) del PIC16F84A no es posible controlar muchos leds.

## Codigo

La parte esensial del proyecto es la libreria Neopixel.c, la cual se encarga de enviar los valores RGB a la tira de NEOPIXELS. 
Los colores estan repartidos en tres arrays NeoGreen[NeoPixel], NeoRed[NeoPixel] y NeoBlue[NeoPixel], setear un color a un 
NEOPIXEL significa separar el valor del color RGB, en R, G y B, y asignar cada uno en la misma posicion en esos tres 
arrays, la longitud de cada array es igual a la cantidad de NEOPIXELS usados, el cual se define como:

    #define NUM_PIXELS 5

La funcion:

    void NeoDraw (void)

se encarga de recorrer y leer cada valor para cada color en esos arrays. La funcion:

    void NeoBit (int1 Bit)

esta funcion es llamada dentro de NeoDraw(), se encarga de generar el "protocolo" poniendo un pin del PIC en estado alto o bajo
de acuerdo al protocolo del chip WS2812B, en este caso se escribe al puerto de forma directa, pin_A3 es el pin de datos usados 
para la tira de NEOPIXELS.

    #bit RA3=0x5.3   //neopin

Asi en lugar de usar las funciones:

    output_high(PIN_A3);
    output_low(PIN_A3);

las cuales consumen "más" tiempo en ejecutarse a nivel asm que escribir directamente al pin del puerto A. Asi es posible
usar un PIC16 o PIC12 con un crystal de 20MHz y lograr trabajar con leds NEOPIXEL como con Arduino.
