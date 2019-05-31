/*
Programa simple de test de sensores de distancia.
Es necesario apretar un pulsador para iniciar el progama, luego hay un bip de un segundo.
Se chequean primero los sensores de distancia:
Si un sensor detecta presencia, se enciende el led correspondiente.
Si se aprietan los dos pulsadores al mismo tiempo, se pasa a comprobar los sensores de linea.
Si un sensor detecta blanco, se enciende el led correspondiente.
Es necesario apretar los dos pulsadores al mismo tiempo para volver a los sensores de distancia.
Los sensors de linea leen valores analogicos y por tanto se recomienda ajustar los limites marcados en el programa.
*/


#define SD A4
#define SLD A5
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


void setup() {
  //Entradas
pinMode(PUSH1,INPUT_PULLUP);
pinMode(PUSH2,INPUT_PULLUP);

pinMode(SIZ,INPUT);
pinMode(SLIZ,INPUT);
pinMode(SD,INPUT);
pinMode(SLD,INPUT);

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

Serial.begin(9600);
}

void loop() {

///Analizamos primero los sensores de distancia
    led_off(nano);
    while(digitalRead(PUSH1)&&digitalRead(PUSH2))
    {

      if (digitalRead(SIZ)) // no detectamos ningun sensor
        led_off(verde);
      else
        led_on(verde);  
      if (digitalRead(SD)) // solo izquierda
        led_off(rojo);
      else
        led_on(rojo);
    }
    //Canvi a sota
    led_on(nano);
    while(!(digitalRead(PUSH1)&&digitalRead(PUSH2)));
    delay(200);
    //Mirem a sota davant
    while(digitalRead(PUSH1)&&digitalRead(PUSH2))
    {
      if (digitalRead(SLIZ)) // no detectamos ningun sensor
        led_off(verde);
      else
        led_on(verde);  
      if (digitalRead(SLD)) // solo izquierda
        led_off(rojo);
      else
        led_on(rojo);
    }
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
