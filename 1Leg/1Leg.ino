#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
float Funcion_0;
float Funcion_1;

//Tiempo..................................................INICIALIZACION
float Tiempo = 0.0;
float Tiempo_0 = 0.0;
float Tiempo_1 = 0.0;
float Vel_0 = 15.0;
float Vel_1 = 28.0;

void setup() {
  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
  myservo4.attach(6);
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

void loop() {

  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  Funcion_0 = 0.5 + (0.5 * sin(Tiempo_0));
  pos1 = 60 + (40 * Funcion_0);
  pos2 = 90 - (40 * Funcion_0);
  pos3 = 60 - (40 * Funcion_0);
  pos4 = 60 + (40 * Funcion_0);
  Serial.print(pos1);
  Serial.print(",");
  Serial.print(pos2);
  Serial.print(",");
  Serial.print(pos3);
  Serial.print(",");
  Serial.println(pos4);
  delay(10);
}
