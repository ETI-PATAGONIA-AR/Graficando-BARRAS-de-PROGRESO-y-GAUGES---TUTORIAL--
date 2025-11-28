En el siguiente ejemplo, pretendo mostrarles como graficar en distintos tipos de pantallas, para poder generar barras de progreso o GAUGES circulares o semi circulares.

**1er EJEMPLO:**
**"Graficando Indicadores de progreso / Gauges con Display LCD y pantalla grafica Nokia5510"**

En este sencillo ejemplo, controlaremos el estado de dos salidas digitales dependiendo de la lectura de tres señales analógicas.
La idea básica, es poder configurar un margen inferior y un margen superior para indicarles a los Relay cuando activarse o no, dependiendo del valor del sensor.
En el programa, comento cada línea para que entiendan como fui generando las distintas gráficas 

<img width="846" height="593" alt="GAUGE_DisplayA" src="https://github.com/user-attachments/assets/749dbf12-b89a-4c34-b38c-9121b50ded77" />

_(pueden descargar el archivo ejemploGLCDyLCD.ino)_

```
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// Ejemplo para generar/visualizar y mostrar señales analogicas en graficas circulares, //
// barras de progreso y generacion de caracteres para almacenar en la CGRAM del LCD e   //
// implementarlas para graficar en un display LCD I2c y pantalla grafica NOKIA5510 I2c  //
//                   prof.martintorres@educ.ar - ETI Patagonia Argentina                //
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); //configuracion display LCD I2C en la direccion 0x27
#include <PCF8574_PCD8544.h>
PCF8574_PCD8544 display = PCF8574_PCD8544(0x20, 7, 6, 5, 4, 2); //configuracion display 5110 I2C en la direccion 0x20 O 0X22
#include <Adafruit_GFX.h>
byte CERO[]=
 {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
 };
byte UNO[]=
 {
  B11111,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111,
 };
byte DOS[]=
 {
  B11111,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11111,
 };
 byte TRES[]=
 {
  B11111,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11111,
 };
 byte CUATRO[]=
 {
  B11111,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11111,
 };
 byte CINCO[]=
 {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
 };
 byte varA[]=
 {
  B00000,
  B01110,
  B01010,
  B01010,
  B01010,
  B01110,
  B01010,
  B00000,
 };
  byte varB[]=
 {
  B00000,
  B01110,
  B01010,
  B01110,
  B01010,
  B01010,
  B01110,
  B00000,
 };
 
int analogInput1 = A0;
int analogInput2 = A1;
int analogInput3 = A2;
const int Relay1 = 12;
const int Relay2 = 13;
// Variables afectadas al primer grafico
 int Aux_graf1;
 int VSensor_graf1;
 int angulo_graf1;
 double x_graf1;
 double y_graf1;
 double x0_graf1;
 double y0_graf1;
 double angulorad_graf1;
 const int radio_graf1=15;
 int angulo_graf1;
 int i_graf1;
 int barraProgreso_graf1;
 int A;
// Variables afectadas al segundo grafico
 int Aux_graf2;
 int VSensor_graf2;
 int angulo_graf2;
 double x_graf2;
 double y_graf2;
 double x0_graf2;
 double y0_graf2;
 double angulorad_graf2;
 const int radio_graf2=15;
 int angulo_graf2;
 int i_graf2;
 int barraProgreso_graf2;
 int B;
// Variables afectadas al tercer grafico
 int VSensor_graf3;
 int DSensor_graf3;
 int ejeY_graf3;
 int ejeX_graf3;
 int Aux_graf3;
 int Aux_graf_3;
 int C;
 int barraProgreso_graf3;
// Variables afectadas al control de relay
int SetVarL;   //variable para guardar la seleccion de medida baja
int SetVarH;   //variable para guardar la seleccion de medida alta

void setup()
  {
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  digitalWrite(Relay1,LOW);
  digitalWrite(Relay2,LOW);
  display.begin();
  display.setContrast(60);
  display.clearDisplay();   //
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("--------------");
  display.setCursor(0, 7);
  display.println("Indicadores de");
  display.setCursor(0, 15);
  display.println(" progreso con ");
  display.setCursor(0, 25);
  display.println("Nokia 5510 I2c");
  display.setCursor(0, 35);
  display.println("ETI  Patagonia");
  display.setCursor(0, 44);
  display.println("--------------");
  display.display();
  lcd.init();
  lcd.createChar(0,CERO);
  lcd.createChar(1,UNO);
  lcd.createChar(2,DOS);
  lcd.createChar(3,TRES);
  lcd.createChar(4,CUATRO);
  lcd.createChar(5,CINCO);
  lcd.createChar(6,varA);
  lcd.createChar(7,varB);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("   Indicadores de   ");
  lcd.setCursor(0,1);
  lcd.print("    progreso con    ");
  lcd.setCursor(0,2);
  lcd.print("  Display LCD  I2c  ");
  lcd.setCursor(0,3);
  lcd.print("   ETI  Patagonia   ");
  delay(1500);
  display.clearDisplay();
  lcd.clear();
  }

void loop()
    {
        VSensor_graf1 = (analogRead(A0)) ;
        updateBarraPROGRESO1(barraProgreso_graf1, 100, 1);
        angulo_graf1 = map(VSensor_graf1,0,1023,0,255);
        Aux_graf1=  map(angulo_graf1,0,255,0,120);
        barraProgreso_graf1 = map(VSensor_graf1,0,1023,0,100);
  
        VSensor_graf2 = (analogRead(A1)) ;
        updateBarraPROGRESO2(barraProgreso_graf2, 100, 2);
        angulo_graf2 = map(VSensor_graf2,0,1023,0,255);
        Aux_graf2=  map(angulo_graf2,0,255,0,120);
        barraProgreso_graf2 = map(VSensor_graf2,0,1023,0,100);
  
        VSensor_graf3 = (analogRead(A2)) ;
        barraProgreso_graf3 = map(VSensor_graf3,0,1023,0,100);
        Aux_graf3 = map(VSensor_graf3,0,1023,0,255);
        ejeY_graf3=  map(Aux_graf3,0,255,33,0);
        VSensor_graf3 = (analogRead(A2)) ;
        Aux_graf3 = map(VSensor_graf3,0,1023,0,255);
        DSensor_graf3=map(Aux_graf3,0,255,0,120);
        SetVarH = Aux_graf1;
        SetVarL = Aux_graf2;
  
        lcd.setCursor(16, 1);
        lcd.write(6);
        lcd.setCursor(17, 1);
        lcd.print(barraProgreso_graf1);
        lcd.print("   ");
        lcd.setCursor(16, 2);
        lcd.write(7);
        lcd.setCursor(17, 2);
        lcd.print(barraProgreso_graf2);
        lcd.print("   ");
        lcd.setCursor(16, 3);
        lcd.print(12,"");//12
        lcd.setCursor(17, 3);
        lcd.print(barraProgreso_graf3);
        lcd.print("   ");
        updateBarraPROGRESO3(barraProgreso_graf3, 100, 3);
        delay(50);
  
        display.setCursor(0, 32);
        display.print("A:");
        display.print(SetVarH);
        display.setCursor(52,32);
        display.print("B:");
        display.print(SetVarL);
        display.setCursor(30,40);
        display.print(DSensor_graf3);
        
        if(DSensor_graf3 >= SetVarL && DSensor_graf3 < SetVarH)
            {
           lcd.setCursor(0, 0);
           lcd.print("*RELAY1=1**RELAY2=0*");
           display.setCursor(0,40);
           display.print("R1:1");
           display.setCursor(60,40);
           display.print("R2:0");
           digitalWrite(Relay1,HIGH);
           digitalWrite(Relay2,LOW);
           delay(10);
          }
          else
          {
           lcd.setCursor(0, 0);
           lcd.print("*RELAY1=0**RELAY2=1*");
           display.setCursor(60,40);
           display.print("R2:1");
           display.setCursor(0,40);
           display.print("R1:0");
           digitalWrite(Relay1,LOW);
           digitalWrite(Relay2,HIGH);
           delay(10);
          }
          display.display();
     graficas();
    }

void graficas()
     {
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//Graficamos el 1er circulo
    display.clearDisplay();
    const double rot_graf1=-M_PI/2;
    display.drawPixel(15,0,BLACK);
    display.drawCircle(15,15,radio_graf1,BLACK); //display.drawCircle(x,y,r,BLACK);
    for(i_graf1=0;i_graf1<12;i_graf1++)
       {
        angulo_graf1=360/12*i_graf1;
        angulorad_graf1=2*M_PI/12*i_graf1+rot_graf1;
        x_graf1=radio_graf1*cos(angulorad_graf1);
        y_graf1=radio_graf1*sin(angulorad_graf1);
        x0_graf1=(radio_graf1-3)*cos(angulorad_graf1);
        y0_graf1=(radio_graf1-3)*sin(angulorad_graf1);
        display.drawLine(15+x0_graf1,15+y0_graf1,15+x_graf1,15+y_graf1,BLACK);
       }
   angulorad_graf1=2*M_PI/120*Aux_graf1+rot_graf1; //
   x_graf1=(radio_graf1-2)*cos(angulorad_graf1);
   y_graf1=(radio_graf1-2)*sin(angulorad_graf1);
   x0_graf1=0;
   y0_graf1=0;
   display.drawLine(15+x0_graf1,15+y0_graf1,15+x_graf1,15+y_graf1,BLACK);
   //display.display();
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//Graficamos el 2do circulo
 
    const double rot_graf2=-M_PI/2;
    display.drawPixel(67,32,BLACK);
    display.drawCircle(67,15,radio_graf2,BLACK); //display.drawCircle(x,y,r,BLACK);
    for(i_graf2=0;i_graf2<12;i_graf2++)
       {
        angulo_graf2=360/12*i_graf2;
        angulorad_graf2=2*M_PI/12*i_graf2+rot_graf2;
        x_graf2=radio_graf2*cos(angulorad_graf2);
        y_graf2=radio_graf2*sin(angulorad_graf2);
        x0_graf2=(radio_graf2-3)*cos(angulorad_graf2);
        y0_graf2=(radio_graf2-3)*sin(angulorad_graf2);
        display.drawLine(67+x0_graf2,15+y0_graf2,67+x_graf2,15+y_graf2,BLACK);
       }
   angulorad_graf2=2*M_PI/120*Aux_graf2+rot_graf2; //
   x_graf2=(radio_graf1-2)*cos(angulorad_graf2);
   y_graf2=(radio_graf1-2)*sin(angulorad_graf2);
   x0_graf2=0;
   y0_graf2=0;
   display.drawLine(67+x0_graf2,15+y0_graf2,67+x_graf2,15+y_graf2,BLACK);
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//Graficamos la barra de progreso del medio
/*
Este es el método mas sencillo que se me ocurrio para crear una barra de progreso vertical.
Lo primero que haremos, es crear un rectangulo sin fondo relleno con las puntas redondeadas ("drawRoundRect").

Luego, crearemos otro rectángulo con las puntas redondeadas, pero en este caso, implementaremos la función "fillRoundRect" para que tenga fondo relleno.
En esta sección, aprovecharemos las coordenadas para imprimir y haremos que el grafico con fondo se desplace en un eje vertical según el valor del puerto analógico mapeado para poder tener un eje [B][SIZE=6]Y [/SIZE][/B]entre dos puntos. 
Tengan en cuenta que esto mismo, se podría hacer en un grafico horizontal

*/
//Graficamos el borde externo de la barra de progreso sin relleno
display.drawRoundRect (32,0,19,39,4,BLACK); //display.drawRoundRect (x,y,ancho,Linea de abajo,nivel redondeado,BLACK);
//Graficamos la barra de progreso con relleno que esta dentro de la otra grafica
int ejeY3;
display.fillRoundRect (34,ejeY_graf3,15,ejeY3=(35-ejeY_graf3),4,BLACK);    //display.fillRoundRect (34,2,15,35,4,BLACK);
//De la posicion 2 del ejeY hasta la posicion 35, tenemos nuestra barra
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void updateBarraPROGRESO1(unsigned long contadorA, unsigned long contadorTOTALA, int ImprimirEnLineaA)
{
  double factorA = contadorTOTALA / 80.0; 
  int porcentajeA = (contadorA + 1) / factorA;
  int numeroA = porcentajeA / 5;
  int restoA = porcentajeA % 5;
 
  if (numeroA > 0)
  {
    for (int A = 0; A < numeroA; A++)
    {
      lcd.setCursor(A, ImprimirEnLineaA);
      lcd.write(5);
    }
  }
  lcd.setCursor(numeroA, ImprimirEnLineaA);
  lcd.write(restoA);
  if (numeroA < 15)
  {
    for (int A = numeroA + 1; A <= 15; A++)
    {
      lcd.setCursor(A, ImprimirEnLineaA);
      lcd.write(0);
    }
  }
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void updateBarraPROGRESO2(unsigned long contadorB, unsigned long contadorTOTALB, int ImprimirEnLineaB)
{
  double factorB = contadorTOTALB / 80.0; 
  int porcentajeB = (contadorB + 1) / factorB;
  int numeroB = porcentajeB / 5;
  int restoB = porcentajeB % 5;
 
  if (numeroB > 0)
  {
    for (int B = 0; B < numeroB; B++)
    {
      lcd.setCursor(B, ImprimirEnLineaB);
      lcd.write(5);
    }
  }
  lcd.setCursor(numeroB, ImprimirEnLineaB);
  lcd.write(restoB);
  if (numeroB < 15)
  {
    for (int B = numeroB + 1; B <= 15; B++)
    {
      lcd.setCursor(B, ImprimirEnLineaB);
      lcd.write(0);
    }
  }
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void updateBarraPROGRESO3(unsigned long contadorC, unsigned long contadorTOTALC, int ImprimirEnLineaC)
{
  double factorC = contadorTOTALC / 80.0; 
  int porcentajeC = (contadorC + 1) / factorC;
  int numeroC = porcentajeC / 5;
  int restoC = porcentajeC % 5;
 
  if (numeroC > 0)
  {
    for (int C = 0; C < numeroC; C++)
    {
      lcd.setCursor(C, ImprimirEnLineaC);
      lcd.write(5);
    }
  }
  lcd.setCursor(numeroC, ImprimirEnLineaC);
  lcd.write(restoC);
  if (numeroC < 15)
  {
    for (int C = numeroC + 1; C <= 15; C++)
    {
      lcd.setCursor(C, ImprimirEnLineaC);
      lcd.write(0);
    }
  }
}
```

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

_(pueden descargar el archivo ejemploOLED.ino)_

```
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ejemplo de indicador de progreso analogico (GAUGE) con display OLED - ETI Patagonia - prof.martintorres@educ.ar //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128                // ancho display OLED
#define SCREEN_HEIGHT 64                // alto display OLED
#define REC_LENGTH 200                  //
// Declaramos la coneccion I2C del display OLED SSD1306 (SDA, SCL pines)
#define OLED_RESET     -1               // Reset pin #
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int SENSOR = A0;
int analogInput2 = A1;
int analogInput3 = A2;
const int Relay1 = 12;
const int Relay2 = 13;
int PWM_Out = 11;        // defino el pin a utilizar para el color AZUL
int PWM_VAR;
int PWM_POR;
int SetA;
int SetB;
int SetVarL;   //variable para guardar la seleccion de medida baja
int SetVarH;   //variable para guardar la seleccion de medida alta
int pos=1;                //posición en X del medidor, cambiando este valor lo corremos a la derecha o la izquierda siendo 0 lo mas a la izquierda posible
//Variables afectadas al grafico del GAUGE conformado por el medio circulo
float radio=40;           // radio del circulo, cambiándolo el medidor quedara mas grande o mas chico
float xcentro=radio;      //  X del centro del circulo que será el medidor
const float ycentro=63;   // Y del centro del circulo; como es un medio circulo la coordenada Y se quedara lo mas abajo posible ya que solo se vera el medio circulo de arriba
float radiochico=2;       //radio del circulito chico donde se apoya la aguja del medidor
// Variables afectadas a la aguja del GAUGE. Es un segmento donde un vértice es fijo (el centro del circulo del medidor) y el otro varia
float xrecta;             // X del otro extremo del segmento de recta el cual se calculara
float yrecta;             // Y del otro extremo del segmento de recta el cual se calculara
float theta;              // ángulo que se moverá la aguja del medidor según el valor de la entrada analogica
const float pi=3.1415927; // el numero pi para pasar ángulos de grados a radianes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
          {
           pinMode(Relay1,OUTPUT);
           pinMode(Relay2,OUTPUT);
           pinMode(PWM_Out,OUTPUT);
           digitalWrite(Relay1,LOW);
           digitalWrite(Relay2,LOW);
           digitalWrite(PWM_Out,LOW);
           display.begin(SSD1306_SWITCHCAPVCC,0x3C);
           display.clearDisplay();           // Borrar imagen en el OLED
           display.setTextSize(2);           // Tamaño del texto
           display.setTextColor(WHITE);      // Definir color del texto (WHITE-BLACK)
           display.setCursor(40,10);         // Definir posición
           display.println("ETI");           // Carga la información al buffer
           display.setCursor(10,30);   
           display.println("PATAGONIA");     // Carga la información al buffer
           display.setTextSize(1);           // Tamaño del texto
           display.setCursor(1,50);   
           display.println("Ejemplo GAUGE Display");     // Carga la información al buffer
           display.display(); // Actualiza display con datos en Buffer
           delay(1000); // Demora de 1 segundo.
           }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
    {
   display.clearDisplay();                                       // Borrar imagen en el OLED
   float a = analogRead(SENSOR);                       // lee la entrada analogica 0
   PWM_VAR = map(a,0,1023,0,240);
   PWM_POR = map(a,0,1023,0,100);
   SetA = (analogRead(A1)) ;
   SetVarH = map(SetA,0,1023,0,100);

   SetB = (analogRead(A2)) ;
   SetVarL = map(SetB,0,1023,0,100);

   display.setTextSize(1);                                      // Tamaño del texto
   display.setCursor(80,10);                                 // Definimos posición X e Y a imprimir
   display.println("SetA:");                                   // imprime la frase que esta entre comillas
   display.setTextSize(1);                                     // Tamaño del texto
   display.setCursor(108,10);                               // Definimos posición X e Y a imprimir
   display.println(SetVarH);                                 // imprime el valor de la entrada analogica
 
   display.setTextSize(1);                                    // Tamaño del texto
   display.setCursor(80,20);                               // Definimos posición X e Y a imprimir
   display.println("SetB:");                                 // imprime la frase que esta entre comillas
   display.setTextSize(1);                                   // Tamaño del texto
   display.setCursor(108,20);                            // Definimos posición X e Y a imprimir
   display.println(SetVarL);                               // imprime el valor de la entrada analógica

   theta=(a/2.84722-360)*pi/360;                   //el 2,84722 es para pasar valores de 0 a 1025
                                                                       // (lo que mide una entrada analógica) a grados
                                                                       // y el resto de la ecuación convierte en radianes
   display.drawCircle(xcentro+pos,ycentro,radio,SSD1306_WHITE);  //Dibuja un circulo cuyo centro esta en las coordenadas x e y y su radio es r (x,y,r), este es el medidor
   display.drawCircle(xcentro+pos,ycentro,radio-4,SSD1306_WHITE);//Dibuja un circulo cuyo centro esta en las coordenadas x e y y su radio es r (x,y,r), este es el medidor
   display.drawCircle(xcentro+pos,ycentro,radio-8,SSD1306_WHITE);//Dibuja un circulo cuyo centro esta en las coordenadas x e y y su radio es r (x,y,r), este es el medidor
   display.drawCircle(xcentro+pos,ycentro,radiochico,SSD1306_WHITE);//Dibuja el circulito donde se apoya la aguja del medidor

// Graficamos el segmento de la recta que seria la aguja del medidor, un extremo es fijo (el centro del circulo) el otro varia segun:
   xrecta=radio*cos(theta)+xcentro;
   yrecta=radio*sin(theta)+ycentro;
// Graficamos la línea indicadora
   display.drawLine(xcentro+pos,ycentro,xrecta+pos,yrecta,SSD1306_WHITE);         // dibuja una recta entre (X0,Y0) y (X1,Y1) seteando (X0,Y0,X1,Y1)
// Graficamos las marcas de graduación del medidor
   display.drawLine(xcentro-4*radio/5+pos,ycentro,xcentro-radio+pos,ycentro,SSD1306_WHITE);  // graduación 1
   display.drawLine(radio*cos(pi/4)+(xcentro-49+pos),radio*sin(pi/4)+(ycentro-49),radio*cos(pi/4)+(xcentro-56+pos),radio*sin(pi/4)+(ycentro-56),SSD1306_WHITE);  // graduación 2
   display.drawLine(xcentro+pos,ycentro-4*radio/5,xcentro+pos,ycentro-radio,SSD1306_WHITE);  // graduación 3
   display.drawLine(69,34,61,42, SSD1306_WHITE);                                             // graduación 4
   display.drawLine(xcentro+4*radio/5+pos,ycentro,xcentro+radio+pos,ycentro,SSD1306_WHITE);  // graduación 5

   display.setTextSize(1);            // Tamaño del texto
   display.setCursor(30,0);           // Definimos posición X e Y a imprimir
   display.println("ETI Patagonia");  // imprime la frase que esta entre comillas
   display.setCursor(0,10);           // Definimos posición X e Y a imprimir
   display.println("POTENCIA:");      // imprime la frase que esta entre comillas
   display.setTextSize(1);            // Tamaño del texto
   display.setCursor(54,10);          // Definimos posición X e Y a imprimir
   display.println(PWM_POR);          // imprime el valor de la entrada analógica

   if(PWM_POR >= SetVarL && PWM_POR < SetVarH)
          {
           display.setCursor(98,40);
           display.print("R1:1");
           display.setCursor(98,50);
           display.print("R2:0");
           digitalWrite(Relay1,HIGH);
           digitalWrite(Relay2,LOW);
           delay(10);
          }
          else
          {
           display.setCursor(98,40);
           display.print("R1:0");
           display.setCursor(98,50);
           display.print("R2:1");
           digitalWrite(Relay1,LOW);
           digitalWrite(Relay2,HIGH);
           delay(10);
          }
   display.display();
   analogWrite (PWM_Out,PWM_VAR); 
   delay(100);                                              // mide datos cada 100 milisegundos
  //display.clrScr();                                      //borra la pantalla para reiniciar el loop
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
```

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
