/*
1.- Test motors i leds
2.- Test sensors
3.- Calibra
4.- Compara_lectures
5.- Envia posicio
6.- Interrupcio temps
7.- Kp
8.- Kd
*/


#include <EEPROM.h> // Per desar les dades de calibracio

// Leer la tension de la bateria
#define VBAT A6

// Configuracion de los motores y sus encoders
#define DIRA 5 // Direcc motor derecha
#define PWMA 11 // PWM motor derecha
#define DIRB 4 // Direcc motor izquierda
#define PWMB 3 // PWM motor izquierda
// PWM estan en los pines 11 y 3, controlados por el timer2. 
//Cambiamos la frecuencia de ese timer de 500Hz a 4kHz para mayor control


// Pulsadores y leds
#define PUSH 0
#define Led1 6 // rojo
#define Led2 10 // verde //placa verda: 2 / placa blanca: 10
#define Led3 13 //nano

// Colores de los leds
#define red 0
#define green 1
#define nano 2

// Sensores de linea
#define SD1 A0
#define SD0 A1
#define SE0 A2
#define SE1 A3

//variables pd
int Kp=20;
int Kd=20;
long errort=0;
long errorp=0;
long errord=0;
volatile int tiempo_pd=0;//!!!!!!!!!
int velocidad=100;

// sensores línea
int S_max[4]={0,0,0,0};
int S_min[4]={1000,1000,1000,1000};
int S_[4]={500,500,500,500};

// posicionamiento
volatile int tiempo=0;
volatile int posicion=0;
volatile int posicion_ant=0;



void setup() {
  //Entradas
pinMode(PUSH,INPUT_PULLUP);

// Salidas
pinMode(Led1,OUTPUT);
pinMode(Led2,OUTPUT);
pinMode(Led3,OUTPUT);
pinMode(DIRA,OUTPUT);
pinMode(DIRB,OUTPUT);
pinMode(PWMA,OUTPUT);
pinMode(PWMB,OUTPUT);

sequencia_inici();
//Comunicaciones
//Serial.begin(9600); // Comentar si no se utiliza

}

void loop() {
  //while (1)
 //   test_motores(); // probamos motores
    //test_sensores(); //probamos lecturas crudas sensores
  if (!digitalRead(PUSH)) // iniciamos con el pulsador apretado
    calibra();
  else // si no hay nada, cargamos los datos de la ultima calibracion
    carga_datos();
  //Serial.begin(9600);
  tiempo=0;
  while(digitalRead(PUSH));
  configura_timers();
while(1)
{
  //compara_lectures(); //comprovem com afecta la calibració a les lectures dels sensors.
  //envia_posicion();
  //delay(10);
  //if (tiempo>5000)
  //  led_on(red);
}
}

void configura_timers(void)
{
  cli(); // deshabilitamos interrupciones
  //motores a 4 KHz
  TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
// TIMER SETUP- the timer interrupt allows preceise timed measurements of the reed switch
  //for mor info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1

  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0;
  // set timer count for 1khz increments
  OCR1A = 1999;// = (16*10^6) / (1000*8) - 1
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);   
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//habilitamos interrupciones
}

void sequencia_inici(void)
{
  for (int j=0;j<3;j++)
  {
led_on(red);
led_off(green);
led_off(nano);
delay(100);
led_off(red);
led_on(green);
led_off(nano);
delay(100);
led_off(red);
led_off(green);
led_on(nano);
delay(100);
led_off(red);
led_off(green);
led_off(nano);

  }
  
}
void pd(void){

 // Error proporcional
 calcula_posicion();
 errorp=posicion;
 errorp=Kp*errorp/10;
 
  // Error diferencial
  if (posicion==posicion_ant)
  {
    tiempo_pd++;
    if (tiempo_pd>500)
        tiempo_pd=500;
     errord=errord*(tiempo-1)/tiempo;
  }
  else
  {
    errord=Kd*(posicion-posicion_ant);
    tiempo_pd=1;
  }
  
  // Error total
  errort=errord + errorp;
  //Serial.println(errort);
  
    if (errort>0){
      errort=min(errort,velocidad);
      motores (velocidad-errort, velocidad);
      }
    else{
      errort=max(errort,-velocidad);
      motores(velocidad, velocidad + errort);
    }
  
}

void envia_posicion(void)
{
  calcula_posicion();
  Serial.println(posicion);
  delay(100);
}

void calibra(void){
  led_on(green);
 while(!digitalRead(PUSH));
  delay(300);
for (int j=0;j<5;j++)
{
  S_max[j]=0;
  S_min[j]=1000;
}
  led_off(green);
  led_on(red);
 for (int temps_calib=0;temps_calib<3000;temps_calib++)
 {
    max_mins();
    delay(1);
 }
    
 for (int j=0;j<4;j++){
          EEPROMWriteInt(2*j+100, S_max[j]-10);
          delay(5);
          EEPROMWriteInt(2*j+108, S_min[j]+10);
          delay(5);
      }
      led_off(red);
}

void max_mins(void)
{
  S_[0]=analogRead(SD1);
  S_[1]=analogRead(SD0);
  S_[2]=analogRead(SE0);
  S_[3]=analogRead(SE1);  
  for (char k=0;k<4;k++){
    if (S_[k]>S_max[k])
        S_max[k]=S_[k];
    if (S_[k]<S_min[k])
        S_min[k]=S_[k];
  }
}

void carga_datos(void){
 Serial.begin(9600); // Comentar si no se utiliza
 delay(500);
      for (int j=0;j<4;j++){
          S_max[j]=EEPROMReadInt(2*j+100);
          delay(10);
          S_min[j]=EEPROMReadInt(2*j+108);
          delay(10);                          
      }
 Serial.print("SD1: ");
 Serial.print(S_max[0]);
 Serial.print(" ");
 delay(20);
 Serial.println(S_min[0]);
  Serial.print("SD0: ");
 Serial.print(S_max[1]);
 Serial.print(" ");
  delay(20);
 Serial.println(S_min[1]);
 Serial.print("SE1: ");
 Serial.print(S_max[2]);
 Serial.print(" ");
  delay(20);
 Serial.println(S_min[2]);
  Serial.print("SE0: ");
 Serial.print(S_max[3]);
 Serial.print(" ");
 Serial.println(S_min[3]);
}


void calcula_posicion(){

  posicion_ant=posicion;
 //llegim
  S_[0]=analogRead(SD1);
  S_[1]=analogRead(SD0);
  S_[2]=analogRead(SE0);
  S_[3]=analogRead(SE1); 
 
//transformem 
      for (int j=0;j<4;j++){
        if (S_[j]<S_min[j])
            S_[j]=0;
        else
          {
            if (S_[j]>S_max[j])
              S_[j]=100;
            else
              S_[j]=map(S_[j],S_min[j],S_max[j],0,100);
          }
      }
 
  int suma_lecturas=S_[0]+S_[1]+S_[2]+S_[3];
  if (suma_lecturas > 80)
  {
    S_[0]=S_[0]*50;
    S_[1]=S_[1]*25;
    S_[1]=S_[1]+S_[0];
    S_[2]=S_[2]*25;
    S_[3]=S_[3]*50;
    S_[3]=S_[2]+S_[3];
    posicion=S_[1] - S_[3];
    posicion=posicion/suma_lecturas;
  }
  else
  {
    if (posicion_ant>0)
        posicion=50;
    else
        posicion=-50;
  }
 
}

void test_motores(void)
  {
    motores(100,100);
    delay(1000);
    motores(0,0);
    delay(200);
    motores(-100,-100);
    delay(1000);
    motores(0,0);
    delay(200);   
    
  }

void test_sensores(void)
{
    //Serial.begin(115200);
  while (1)
  {
    Serial.print(analogRead(SE1));
    Serial.print(" ");
    Serial.print(analogRead(SE0));
    Serial.print(" ");
    Serial.print(analogRead(SD0));
    Serial.print(" ");
    Serial.println(analogRead(SD1));
    delay(250);
  }
}

void compara_lectures(void)
{
   //llegim
  S_[0]=analogRead(SD1);
  S_[1]=analogRead(SD0);
  S_[2]=analogRead(SE0);
  S_[3]=analogRead(SE1); 
 Serial.print(S_[0]);
 Serial.print(" ");
 Serial.print(S_[1]);
 Serial.print(" ");
 Serial.print(S_[2]);
 Serial.print(" ");
 Serial.println(S_[3]);
 //transformem 
      for (int j=0;j<4;j++){
        if (S_[j]<S_min[j])
            S_[j]=0;
        else
          {
            if (S_[j]>S_max[j])
              S_[j]=100;
            else
              S_[j]=map(S_[j],S_min[j],S_max[j],0,100);
          }
      }
 Serial.print(S_[0]);
 Serial.print(" ");
 Serial.print(S_[1]);
 Serial.print(" ");
 Serial.print(S_[2]);
 Serial.print(" ");
 Serial.println(S_[3]);
 //Serial.println();
}

void led_on(char nled)
{
    switch (nled) {
  case 0:    // rojo
    digitalWrite(Led1,HIGH);
    break;
  case 1:    // verde
    digitalWrite(Led2,HIGH);
    break;
  case 2:    // amarillo
    digitalWrite(Led3,HIGH);
    break;
    }
}

void led_off(char nled)
{
    switch (nled) {
  case 0:    // rojo
    digitalWrite(Led1,LOW);
    break;
  case 1:    // verde
    digitalWrite(Led2,LOW);
    break;
  case 2:    // amarillo
    digitalWrite(Led3,LOW);
    break;
    }
}



void motores(int motor_d,int motor_i)
{
if (motor_d>0)
  digitalWrite(DIRA,LOW);
else
  digitalWrite(DIRA,HIGH);

if (motor_i>0)
  digitalWrite(DIRB,LOW);
else
  digitalWrite(DIRB,HIGH);

motor_d=char(min(255,abs(motor_d)));
motor_i=char(min(255,abs(motor_i)));

analogWrite(PWMA,motor_d);
analogWrite(PWMB,motor_i);

}


ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  tiempo++;
  pd();
}


//This function will write a 2 byte integer to the eeprom at the specified address and address + 1
void EEPROMWriteInt(int p_address, int p_value)
     {
     byte lowByte = ((p_value >> 0) & 0xFF);
     byte highByte = ((p_value >> 8) & 0xFF);

     EEPROM.write(p_address, lowByte);
     EEPROM.write(p_address + 1, highByte);
     }

//This function will read a 2 byte integer from the eeprom at the specified address and address + 1
unsigned int EEPROMReadInt(int p_address)
     {
     byte lowByte = EEPROM.read(p_address);
     byte highByte = EEPROM.read(p_address + 1);

     return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
     }
