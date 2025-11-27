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