//MD,ME
#include <Servo.h> // Servos i bandera


#define MD 3
#define ME 4

#define SLFD 5
#define SLFE 6
#define SLPD A4
#define SLPE A5

#define push_fi A0
#define push_centre A1

#define pin_led_vermell 11
#define pin_led_verd 10
#define pin_nano 13

#define SPD A2
#define SPE A3

#define rojo 0
#define verde 1
#define nano 2


Servo motor_dret;  // create servo object to control a servo
Servo motor_esquerra;


void setup() {
  //delay(1000);
// Initialize Serial port
  Serial.begin(9600);

  pinMode(pin_nano,OUTPUT);
  pinMode (push_fi,INPUT_PULLUP);
  pinMode (push_centre,INPUT_PULLUP);
  pinMode(pin_led_vermell,OUTPUT);
  pinMode(pin_led_verd,OUTPUT);

  //pinMode(SPD,INPUT);
  //pinMode(SPE,INPUT);
  
  pinMode(SLFD,INPUT);
  pinMode(SLFE,INPUT);
  pinMode(SLPD,INPUT);
  pinMode(SLPE,INPUT);
    
  motor_dret.attach(MD);  // attaches the servo on pin 9 to the servo object
  motor_esquerra.attach(ME);
  atura();
  Serial.begin(9600);
}

void loop() {
  while(digitalRead(push_centre)&&digitalRead(push_fi));
 endavant();
 delay(1000);
 atura();
 delay(500);
 gira_dreta();
 delay(1000);
 atura();
 delay(500);
 gira_esquerra();
 delay(1000);
 atura();
 delay(500);
 pivota_h();
 delay(1000);
 atura();
 delay(500);
 pivota_ah();
 delay(1000);
 atura();
 delay(500);
 enrera();
 delay(1000);
 atura();
 delay(500);
}



void atura(void)
{
        motor_dret.writeMicroseconds(1465);//blau:1466/ vermell:1455 / groc:1440 / verd: 1448 / blanc: 1465
        motor_esquerra.writeMicroseconds(1463);// blau:1456 / vermell: 1456 / groc:1452 / verd:1457 / Blanc:1463 
}

void endavant(void)
{
  motor_dret.write(0);
  motor_esquerra.write(180);
}

void gira_dreta(void)
{
  motor_dret.write(90);
  motor_esquerra.write(180);
}

void gira_esquerra(void)
{
  motor_dret.write(0);
  motor_esquerra.write(90);
}

void pivota_h(void)
{
  motor_dret.write(180);
  motor_esquerra.write(180);
}

void pivota_ah(void)
{
  motor_dret.write(0);
  motor_esquerra.write(0);
}

void enrera(void)
{
  motor_dret.write(180);
  motor_esquerra.write(0);
}


void led_on(char nled)
{
    switch (nled) {
  case 0:    // your hand is on the sensor
    digitalWrite(pin_led_verd,HIGH);
    break;
  case 1:    // your hand is close to the sensor
    digitalWrite(pin_led_vermell,HIGH);
    break;
  case 2:    // your hand is a few inches from the sensor
    digitalWrite(pin_nano,HIGH);
    break;
    }
}


void led_off(char nled)
{
    switch (nled) {
  case 0:    // your hand is on the sensor
    digitalWrite(pin_led_verd,LOW);
    break;
  case 1:    // your hand is close to the sensor
    digitalWrite(pin_led_vermell,LOW);
    break;
  case 2:    // your hand is a few inches from the sensor
    digitalWrite(pin_nano,LOW);
    break;
    }
}

void nano_on(void)
{
  digitalWrite(pin_nano,HIGH);
}


void nano_off(void)
{
  digitalWrite(pin_nano, LOW);
}

void red_on(void)
{
  digitalWrite(pin_led_vermell,HIGH);
}


void red_off(void)
{
  digitalWrite(pin_led_vermell, LOW);
}

void green_on (void)
{
        digitalWrite(pin_led_verd,HIGH);
}


void green_off (void)
{
        digitalWrite(pin_led_verd,LOW);
}
