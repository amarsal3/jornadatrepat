/*
Test de los motores:
cuando apretamos cualquier pulsador:
adelante
atras
giro derecha
giro izquierda
pivota en sentido horario
pivota en sentido antihorario

*/




#define SD A7
#define SLD A6
#define SIZ A3
#define SLIZ A2

#define PUSH1 A0
#define PUSH2 12

#define AIN2 2
#define AIN1 3
#define BIN1 4
#define PWMA 5
#define PWMB 6
#define BIN2 7

#define Led1 10
#define Led2 11
#define Led3 13

#define rojo 1
#define verde 0
#define nano 2


volatile int velocidad=100;

void setup() {
  //Entradas
pinMode(PUSH1,INPUT_PULLUP);
pinMode(PUSH2,INPUT_PULLUP);

pinMode(SIZ,INPUT);
pinMode(SLIZ,INPUT);


// Salidas
pinMode(Led1,OUTPUT);
pinMode(Led2,OUTPUT);
pinMode(Led3,OUTPUT);

pinMode(AIN1,OUTPUT);
pinMode(AIN2,OUTPUT);
pinMode(BIN1,OUTPUT);
pinMode(BIN2,OUTPUT);
pinMode(PWMA,OUTPUT);
pinMode(PWMB,OUTPUT);


}
void loop() {
  while(digitalRead(PUSH1)&&digitalRead(PUSH2));

 delay(500);

   adelante();
   led_on(rojo);
   delay(500);
   para();
   led_off(rojo);
   delay(200);
   atras();
   led_on(verde);
   delay(500);
   para();
   led_off(verde);
   delay(200);
   giro_derecha();
   delay(500);
   para();
   delay(200);
   giro_izquierda();
   delay(500);
   para();
   delay(200);
   pivota_h();
   led_on(nano);
   delay(500);
      para();
   delay(200);
   pivota_ah();
   delay(500);
      para();
      led_off(nano);
   delay(200);

 
}

void led_on(char nled)
{
    switch (nled) {
  case 0:    // your hand is on the sensor
    digitalWrite(Led1,HIGH);
    break;
  case 1:    // your hand is close to the sensor
    digitalWrite(Led2,HIGH);
    break;
  case 2:    // your hand is a few inches from the sensor
    digitalWrite(Led3,HIGH);
    break;
    }
}

void led_off(char nled)
{
    switch (nled) {
  case 0:    // your hand is on the sensor
    digitalWrite(Led1,LOW);
    break;
  case 1:    // your hand is close to the sensor
    digitalWrite(Led2,LOW);
    break;
  case 2:    // your hand is a few inches from the sensor
    digitalWrite(Led3,LOW);
    break;
    }
}



void adelante(void)
{
 digitalWrite(AIN2,HIGH);
 digitalWrite(AIN1,LOW);
 analogWrite(PWMA,velocidad);
  digitalWrite(BIN1,HIGH);
 digitalWrite(BIN2,LOW);
 analogWrite(PWMB,velocidad);
}

void atras(void)
{
 digitalWrite(AIN1,HIGH);
 digitalWrite(AIN2,LOW);
 analogWrite(PWMA,velocidad);
 digitalWrite(BIN2,HIGH);
 digitalWrite(BIN1,LOW);
 analogWrite(PWMB,velocidad);
  
}
void giro_derecha(void)
{
   digitalWrite(AIN2,HIGH);
 digitalWrite(AIN1,LOW);
 analogWrite(PWMA,0);
  digitalWrite(BIN1,HIGH);
 digitalWrite(BIN2,LOW);
 analogWrite(PWMB,velocidad);
  
}

void giro_izquierda(void)
{
   digitalWrite(AIN2,HIGH);
 digitalWrite(AIN1,LOW);
 analogWrite(PWMA,velocidad);
  digitalWrite(BIN1,HIGH);
 digitalWrite(BIN2,LOW);
 analogWrite(PWMB,0);
}

void pivota_h(void)
{
  digitalWrite(AIN1,HIGH);
 digitalWrite(AIN2,LOW);
 analogWrite(PWMA,velocidad);
  digitalWrite(BIN1,HIGH);
 digitalWrite(BIN2,LOW);
 analogWrite(PWMB,velocidad); 
}

void pivota_ah()
{
  digitalWrite(AIN2,HIGH);
 digitalWrite(AIN1,LOW);
 analogWrite(PWMA,velocidad);
  digitalWrite(BIN2,HIGH);
 digitalWrite(BIN1,LOW);
 analogWrite(PWMB,velocidad); 
}

void para(void)
{
  digitalWrite(AIN1,HIGH);
 digitalWrite(AIN2,LOW);
 analogWrite(PWMA,0);
   digitalWrite(BIN1,HIGH);
 digitalWrite(BIN2,LOW);
 analogWrite(PWMB,0);
  
}
