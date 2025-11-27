En el siguiente ejemplo, pretendo mostrarles como graficar en distintos tipos de pantallas, para poder generar barras de progreso o GAUGES circulares o semi circulares.

**1er EJEMPLO:**
**"Graficando Indicadores de progreso / Gauges con Display LCD y pantalla grafica Nokia5510"**

En este sencillo ejemplo, controlaremos el estado de dos salidas digitales dependiendo de la lectura de tres señales analógicas.
La idea básica, es poder configurar un margen inferior y un margen superior para indicarles a los Relay cuando activarse o no, dependiendo del valor del sensor.
En el programa, comento cada línea para que entiendan como fui generando las distintas gráficas 

<img width="846" height="593" alt="GAUGE_DisplayA" src="https://github.com/user-attachments/assets/749dbf12-b89a-4c34-b38c-9121b50ded77" />

(ver archivo ejemploGLCDyLCD.ino)

**Graficamos los gauges de progreso circulares en la pantalla grafica NOKIA5510**
Bien, para poder generar un indicador de progreso circular (GAUGE), necesitaremos aplicar trigonometria. En breves líneas, dejame explicarte como aplicar estas matemáticas

_**PRIMERO: Leemos el valor del sensor analógico**_

```(VSensor_graf1 = analogRead(A0))```

El valor leído VSensor_graf1 estará en el rango de 0 a 1023.
Este valor representa la medida analógica del sensor conectado al pin A0.

_**SEGUNDO: Mapeamos el valor del sensor a un ángulo de giro completo**_

```(angulo_graf1 = map(VSensor_graf1, 0, 1023, 0, 360))```

Aquí, utilizamos la función map() para convertir este valor del sensor (0-1023) a un rango de ángulos (0-360 grados).
Esto es porque queremos que el valor del sensor se corresponda con un ángulo de un círculo completo.

_**TERCERO: Convertimos el ángulo a radianes**_

```(angulorad_graf1 = angulo_graf1 * (M_PI / 180))```

El radian, es una unidad de medida de ángulos, definido por el cociente de la longitud del arco de un circulo entre el radio del mismo circulo.
Las funciones trigonométricas en el lenguaje C del IDE de Arduino, utilizan radianes en lugar de grados.
_La fórmula para convertir grados a radianes es:_

```radianes=grados*(PI/180)     //Recuerden que el valor de PI es de: 3,141592```

_**CUARTO: Calcular las coordenadas del puntero usando trigonometría**_
En este paso, utilizaremos las fórmulas trigonométricas para calcular las coordenadas (x, y) del puntero en el borde del círculo, dado un ángulo en radianes.

_**Fórmula del coseno y seno en trigonometría:**_

_En un círculo de radio 𝑟:
                                           La coordenada x se calcula como x=r×cos(θ)
                                           La coordenada y se calcula como y=r×sin(θ)
                               Donde:
                                           θ es el ángulo en radianes.
                                           r es el radio del círculo, que en tu caso es (radio_graf1)_

Después de haber convertido el ángulo a radianes (angulorad_graf1) utilizas estas fórmulas para calcular las coordenadas "x" e "y":

```x_graf1 = radio_graf1 * cos(angulorad_graf1);```
```y_graf1 = radio_graf1 * sin(angulorad_graf1);```

Con estas líneas del sketch, se calculan las posiciones "x" e "y" y del puntero en el círculo de radio (radio_graf1) basado en el ángulo (angulorad_graf1)

**Graficamos la barra de progreso en la pantalla grafica NOKIA5510**
Bien, este es el método mas sencillo que se me ocurrió para crear una barra de progreso vertical.
Lo primero que haremos, es crear un rectángulo sin fondo relleno con las puntas redondeadas ("drawRoundRect").
Luego, crearemos otro rectángulo con las puntas redondeadas, pero en este caso, implementaremos la función "fillRoundRect" para que tenga fondo relleno.
En esta sección, aprovecharemos las coordenadas para imprimir y haremos que el grafico con fondo se desplace en un eje vertical según el valor del puerto analógico mapeado para poder tener un eje Y entre dos puntos.
Tengan en cuenta que esto mismo, se podría hacer en un grafico horizontal cambiando los puntos de las coordenadas.

**Graficamos las barra de progreso en el Display LCD**
Este es el método que hace todo el trabajo en la barra de progreso.

```@parametro contador(A,B,C) = el número actual en el progreso del conteo```

```@parametro contadorTOTAL (A,B,C) = el número total a contar```

```@parametro ImprimirEnLinea (A,B,C) = la línea de la pantalla LCD en la que se va a imprimir```

Como vamos a usar una grafica de 16 caracteres, cada posición tiene 5 secciones, por lo tanto, necesitamos declarar el número 80.0 ya que serian 16 caracteres por 5 columnas del carácter creado en la CGRAM...

Si quisiera una grafica de 20 caracteres, tendría 20 x 5 = 100 columnas. Por lo tanto deberíamos cambiar en nuestra programación el 80.0 por 100.0
Esta constante debe estar en formato de numero flotante (X.0), de lo contrario, el programa lo interpretara como una integral (int) y no darán bien los cálculos.

_**Para entender un poco mejor, tenemos que:**_
El factor es el contadorTOTAL/dividido por el número de columnas de cada carácter (recuerden que cada carácter tiene 5 columnas).
El porcentaje es el recuento (contador A,B,C) dividido por el factor (por lo tanto, para 80 columnas, esto le dará un número entre 0 y 80) el número le proporciona la posición del carácter donde imprimir (por lo que para una pantalla de 16 x 2, estará entre 0 y 16; y una de 20x4, estará entre 0 y 20.
El resto le da el número de carácter de la pieza, por lo que devuelve un número entre 0 y 4

**2do EJEMPLO: "Graficando Gauges con Display OLED"**

<img width="844" height="592" alt="GAUGE_Display2" src="https://github.com/user-attachments/assets/06fb7e8f-b6b5-46b0-9f01-462aad6525ce" />

(ver archivo ejemploOLED.ino)

**theta** es un ángulo que va de 0 a Pi/2 o sea 0 a 180 (180 por que nuestro GAUGE es un semi circulo).
Cuando calculas:

  ```xrecta = radio*cos(theta)+xcentro;```
  ```yrecta = radio*sin(theta)+ycentro;```

Establecemos la coordenada del punto que se corresponde con theta entre 0 y 1023.

```cos(0) = 1```
```sen(0) = 0```

De modo que para 0° tendríamos las coordenadas:

```x = 1 + xcentro e y = 0 + ycentro```

Cuando el ángulo es 90° corresponde a 512 o sea la mitad entre 0 y 1023, seria:

```cos 90 = 0```
```sen 90 = 1```
```x = xcentro```
```y = 1 + ycentro```
