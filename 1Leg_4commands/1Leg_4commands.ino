#include "HCPCA9685.h"
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int pos6 = 0;
int pos7 = 0;
int pos8 = 0;
unsigned int Pos1_map;
unsigned int Pos2_map;
unsigned int Pos3_map;
unsigned int Pos4_map;
float Funcion_0;
float Funcion_1;
//Comandos
bool Stand_by = true;
bool Rest = false;
bool Adelante = false;
bool Run = false;
//Tiempo..................................................INICIALIZACION
float Tiempo = 0.0;
float Tiempo_0 = 0.0;
float Tiempo_1 = 0.0;
float Vel_0 = 20.0;
float Vel_1 = 20.0;

void setup()
{
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  Serial.begin(9600);

  // TIMER 2 for interrupt frequency 20 Hz:
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 12499;
  TCCR2B |= (1 << WGM21);
  TCCR2B |= (0 << CS22) | (1 << CS21) | (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);

}

ISR(TIMER2_COMPA_vect) {
  Tiempo = Tiempo + 0.05;
  Tiempo_0 = Tiempo / Vel_0;
  Tiempo_1 = Tiempo / Vel_1;
  if (Tiempo == 100.0) {
    Tiempo = 0.0;
  }
}

void loop()
{
  if ( Stand_by == true) {
    pos8 = 230;
    //Delanteras
    HCPCA9685.Servo(0, 230);    //230
    HCPCA9685.Servo(1, 400);    //400
    HCPCA9685.Servo(4, 230);    //230
    HCPCA9685.Servo(5, 400);    //400
    //Traseras
    HCPCA9685.Servo(2, 230);    //230
    HCPCA9685.Servo(3, 230);    //230
    HCPCA9685.Servo(6, 230);    //230
    HCPCA9685.Servo(7, 230);    //230
  }

  if ( Rest == true) {
    //Delanteras
    HCPCA9685.Servo(0, 80);     //80
    HCPCA9685.Servo(1, 350);    //35
    HCPCA9685.Servo(4, 380);    //380
    HCPCA9685.Servo(5, 450);    //450
    //Traseras
    HCPCA9685.Servo(2, 110);    //230
    HCPCA9685.Servo(3, 280);    //230
    HCPCA9685.Servo(6, 350);    //230
    HCPCA9685.Servo(7, 180);    //230
  }

  if ( Adelante == true) {
    Funcion_0 = 0.5 + (0.5 * sin(Tiempo_0));
    Funcion_1 = 0.5 + (0.5 * cos(Tiempo_0 + 45));
    //Delanteras
    pos1 = 230 + (90 * Funcion_0);
    pos2 = 450 - (100 * Funcion_0);
    pos3 = 310 - (90 * Funcion_1);
    pos4 = 350 + (100 * Funcion_1);
    //Traseras
    pos5 = 280 - (90 * Funcion_0);
    pos6 = 230 + (220 * Funcion_0);
    pos7 = 190 + (90 * Funcion_1);
    pos8 = 230 - (220 * Funcion_1);

    //Delanteras
    HCPCA9685.Servo(0, pos1);
    HCPCA9685.Servo(1, pos2);
    HCPCA9685.Servo(4, pos3);
    HCPCA9685.Servo(5, pos4);
    //Traseras
    HCPCA9685.Servo(2, pos5);
    HCPCA9685.Servo(3, pos6);
    HCPCA9685.Servo(6, pos7);
    HCPCA9685.Servo(7, pos8);

    delay(20);
  }

  if ( Run == true) {
    Funcion_0 = 0.5 + (0.5 * sin(Tiempo_0));
    Funcion_1 = 0.5 + (0.5 * cos(Tiempo_0 + 45));
    //Delanteras
    pos1 = 230 - (150 * Funcion_0);
    pos2 = 350 + (100 * Funcion_0);
    pos3 = 230 + (150 * Funcion_0);
    pos4 = 450 - (100 * Funcion_0);
    //Traseras
    pos5 = 280 - (90 * Funcion_1);
    pos6 = 230 + (220 * Funcion_1);
    pos7 = 190 + (90 * Funcion_1);
    pos8 = 230 - (220 * Funcion_1);
    
    //Delanteras
    HCPCA9685.Servo(0, pos1);
    HCPCA9685.Servo(1, pos2);
    HCPCA9685.Servo(4, pos3);
    HCPCA9685.Servo(5, pos4);
    //Traseras
    HCPCA9685.Servo(2, pos5);
    HCPCA9685.Servo(3, pos6);
    HCPCA9685.Servo(6, pos7);
    HCPCA9685.Servo(7, pos8);

    delay(20);
  }

  Serial.print(Funcion_0);
  Serial.print(",");
  Serial.println(Funcion_1);
}
