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