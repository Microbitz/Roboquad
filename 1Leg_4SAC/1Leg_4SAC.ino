#include "HCPCA9685.h"
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);

int pos0 = 0;
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int pos6 = 0;
int pos7 = 0;
unsigned int Pos1_map;
unsigned int Pos2_map;
unsigned int Pos3_map;
unsigned int Pos4_map;
float Funcion_0;
float Funcion_1;
//Comandos
bool Stand_by = false;
bool Rest = false;
bool Paso = false;
bool Adelante_0 = true;
bool Adelante_1 = false;
bool Run = false;
//Tiempo..................................................INICIALIZACION
float Tiempo = 0.0;
float Tiempo_0 = 0.0;
float Tiempo_1 = 0.0;
float Tiempo_3 = 0.0;
float Tiempo_3_t = 0.0;
float Vel_0 = 10.0;     //Velocidad_0
float Vel_1 = 10.0;     //Velocidad_1
float Ret0 = 0.0;
float Ret_t0 = 0.0;
float Ret1 = 0.0;
float Ret_t1 = 0.0;
float Retmax = 0.15;    // Meseta
float Peak_0 = 0.0;
float Peak_1 = 0.0;
bool Pulso_0 = 0;
bool Pulso_1 = 0;
bool OSR = 0;
bool OSRR = 0;
float Out_0 = 0.0;
float Out_1 = 0.0;
int cont_pasos = 0;
int valor_0 = 0;

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
  Tiempo_3 = Tiempo_3 + 0.05;
  Tiempo_3_t = Tiempo_3 / 100;
  Tiempo_0 = Tiempo / Vel_0;
  Tiempo_1 = Tiempo / Vel_1;
  Funcion_0 = 0.5  + (0.5 * sin(Tiempo_0));
  Funcion_1 = 1 - Funcion_0;

  if (Funcion_0 >= 0.95) {
    if (Ret_t0 < Retmax) {
      Tiempo = Tiempo - 0.05;
      Funcion_0 = 1;
    }
    Ret0 = Ret0 + 0.05;
  }

  if (Funcion_0 <= 0.05) {
    if (Ret_t1 < Retmax) {
      Tiempo = Tiempo - 0.05;
      Funcion_0 = 0;
    }
    Ret1 = Ret1 + 0.05;
  }

  Ret_t0 = Ret0 / 100;
  Ret_t1 = Ret1 / 100;

  if (Funcion_0 >= 0.95 && OSR == 0) {
    Peak_0 = Peak_0 + 1.0;
    cont_pasos = cont_pasos + 1;
    OSR = 1;
    Ret1 = 0.0;
  }
  if (Funcion_0 <= 0.95 && OSR == 1) {
    Peak_0 = Peak_0 - 1.0;
    OSR = 0;
    Ret0 = 0.0;
  }

  if (Tiempo_3_t <= 0.250) {
    Pulso_0 = 0;
    Pulso_1 = 1;
  }

  if (Tiempo_3_t > 0.250) {
    Pulso_0 = 1;
    Pulso_1 = 0;
  }

  if (Tiempo_3_t > 0.500) {
    Tiempo_3 = 0;
    Pulso_0 = 0;
    Pulso_1 = 1;
  }

  if (Stand_by == false) {
    Out_0 = Funcion_0;
    Out_1 = Funcion_1;
  }

  if (Stand_by == true) {
    Out_0 = 0.0;
    Out_1 = 0.0;
  }

}

void loop()
{
  if ( Stand_by == true) {
    //Delanteras
    HCPCA9685.Servo(2, 230);
    HCPCA9685.Servo(3, 230);
    HCPCA9685.Servo(6, 230);
    HCPCA9685.Servo(7, 230);
    //Traseras:
    HCPCA9685.Servo(0, 330);
    HCPCA9685.Servo(1, 450);
    HCPCA9685.Servo(4, 130);
    HCPCA9685.Servo(5, 0);
  }

  if ( Rest == true) {
    //Delanteras
    HCPCA9685.Servo(2, 180);    //LADO A
    HCPCA9685.Servo(3, 140);    //LADO A
    HCPCA9685.Servo(6, 130);    //LADO B
    HCPCA9685.Servo(7, 230);   //LADO B
    //Traseras:
    HCPCA9685.Servo(0, 410);    //LADO A
    HCPCA9685.Servo(1, 450);    //LADO A
    HCPCA9685.Servo(4, 180);   //LADO B
    HCPCA9685.Servo(5, 80);   //LADO B

    delay(1200);

    //Delanteras
    HCPCA9685.Servo(2, 330);
    HCPCA9685.Servo(3, 280);
    HCPCA9685.Servo(6, 280);
    HCPCA9685.Servo(7, 320);
    //Traseras:
    HCPCA9685.Servo(0, 285);
    HCPCA9685.Servo(1, 410);
    HCPCA9685.Servo(4, 40);
    HCPCA9685.Servo(5, 0);

    delay(1200);

  }

  if ( Adelante_0 == true) {
    //Delanteras
    pos2 = 180 + (50 * Funcion_0);
    pos3 = 140 - (10 * Funcion_0);
    pos6 = 130 + (150 * Funcion_0);
    pos7 = 230 + (100 * Funcion_0);
    //Traseras:
    pos0 = 410 - (125 * Funcion_0);
    pos1 = 450 - (40 * Funcion_0);
    pos4 = 180 - (140 * Funcion_0);
    pos5 = 80 - (80 * Funcion_0);

    //Delanteras
    HCPCA9685.Servo(2, pos2);    //LADO A
    HCPCA9685.Servo(3, pos3);    //LADO A
    HCPCA9685.Servo(6, pos6);    //LADO B
    HCPCA9685.Servo(7, pos7);   //LADO B
    //Traseras:
    HCPCA9685.Servo(0, pos0);    //LADO A
    HCPCA9685.Servo(1, pos1);    //LADO A
    HCPCA9685.Servo(4, pos4);   //LADO B
    HCPCA9685.Servo(5, pos5);   //LADO B
    
  }

  Serial.print(valor_0);
  Serial.print(",");
  Serial.print(Out_0);
  Serial.print(",");
  Serial.print(Out_1);
  Serial.println();

}
