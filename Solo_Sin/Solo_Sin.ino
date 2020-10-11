float Funcion_0;
float Funcion_1;

//Tiempo..................................................INICIALIZACION
float Tiempo = 0.0;
float Variable_t = 0.0;
float Ancho = 10;

void setup() {
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
// Interrupcion
ISR(TIMER2_COMPA_vect) {
  Tiempo = Tiempo + 0.05;
}

void loop() {
  Variable_t = Tiempo;
  Variable_t = Variable_t / 100.0;
  Variable_t = Variable_t*Ancho;
  Funcion_0 = 0.5 + (0.5  * sin(Variable_t));
  Funcion_1 = 0.5 + (0.5  * cos(Variable_t + 45.0));
  Serial.print(Funcion_0);
  Serial.print(",");
  Serial.println(Funcion_1);
  delay(10);
}
