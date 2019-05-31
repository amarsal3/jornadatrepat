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
  while(digitalRead(push_fi)&&digitalRead(push_centre))
  {
    if(analogRead(SPD)>150)
      led_on(rojo);
    else
      led_off(rojo);
    if(analogRead(SPE)>150)
      led_on(verde);
    else
      led_off(verde);
  }
  //mirem a sota ara
  while(!(digitalRead(push_fi)&&digitalRead(push_centre)));
    delay(200);
  while(digitalRead(push_fi)&&digitalRead(push_centre))
  { 
    if (digitalRead(SLFD))
      led_off(rojo);
    else
      led_on(rojo);
    if (digitalRead(SLFE))
      led_off(verde);
    else
      led_on(verde);
    }
  while(!(digitalRead(push_fi)&&digitalRead(push_centre)));
    delay(200);
    led_on(nano);
  while(digitalRead(push_fi)&&digitalRead(push_centre))
  { 
    if (digitalRead(SLPD))
      led_off(rojo);
    else
      led_on(rojo);
    if (digitalRead(SLPE))
      led_off(verde);
    else
      led_on(verde);
    }
    led_off(nano); 
    while(!(digitalRead(push_fi)&&digitalRead(push_centre)));
    delay(200);
}


void atura(void)
{
        motor_dret.writeMicroseconds(1465);//blau:1466/ vermell:1455 / groc:1440 / verd: 1448 / blanc: 1465
        motor_esquerra.writeMicroseconds(1463);// blau:1456 / vermell: 1456 / groc:1452 / verd:1457 / Blanc:1463 
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
