#include <Servo.h> 
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 8); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Piny
int servo_vez = 6; // Servo věž
int kanon_vez = 7; // Nonón věž

int tx_audio = 8; // TX Audio
int rx_audio = 10; // RX Audio

int front_led = 11; // Přední ledky
int back_led = 12; // Zadní ledky
// Konec pinů

// Konec označení motorů
int m1a = 3;
int m1b = 2;
int m2a = 4;
int m2b = 5;
// Začátek označení motorů

Servo ServoVez; // Natsavení prvního serva - Vež
Servo ServoKanon; // Natsavení druhého serva - Kanón

String value;


void setup() 
{  
  mySoftwareSerial.begin(9600);

  ServoVez.attach(servo_vez);  // Nastavení prvního serva
  ServoKanon.attach(kanon_vez); // Nastavení druhého serva

  pinMode(m1a, OUTPUT);  // Digital pin 10 set as output Pin
  pinMode(m1b, OUTPUT);  // Digital pin 11 set as output Pin
  pinMode(m2a, OUTPUT);  // Digital pin 12 set as output Pin
  pinMode(m2b, OUTPUT);  // Digital pin 13 set as output Pin
  Serial.begin(38400);

  pinMode(front_led, OUTPUT);
  pinMode(back_led, OUTPUT);

  if (!myDFPlayer.begin(mySoftwareSerial, false)) {  //Use softwareSerial to communicate with mp3.
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
      while(true){
        delay(0); // Code to compatible with ESP8266 watch dog.
      }
  }
  Serial.println(F("DFPlayer Mini je online."));
  myDFPlayer.volume(20); 
  ServoKanon.write(40);

}

void loop()
{
  if (Serial.available() > 0)
  {
    value = Serial.readStringUntil('\n');
    Serial.println(value);
    
    Movement(value);
    TurretMovement(value);  
    CanonMovement(value);
    MusicPlayer(value);
    Diods(value);
  
  }
}

void MusicPlayer(String val){  

  static unsigned long timer = millis();

  int commaIndex = val.indexOf(' ');
  String prvni = val.substring(0, commaIndex);
  String druhy = val.substring(commaIndex + 1);
  int int_value = druhy.toInt();

  if (int_value == 1 && prvni == "mp"){
    Serial.print("Hraji první song");
    myDFPlayer.play(1);
    delay(100);
  }

  else if(int_value == 2 && prvni == "mp"){
    myDFPlayer.play(2);
  }

  else if(int_value == 3 && prvni == "mp"){
    myDFPlayer.play(3);
  }

  else if(val == "mp s"){
    myDFPlayer.stop();
  }
    
}

void TurretMovement(String val){
    int commaIndex = val.indexOf(' ');
    String prvni = val.substring(0, commaIndex);
    String druhy = val.substring(commaIndex + 1);
    int int_value = druhy.toInt();

    if (int_value >= 0 && int_value <= 180 && prvni == "tur"){
      ServoVez.write(int_value);
    }
}

void Diods(String val){
    if (val == "lf"){
      if(digitalRead(front_led)){
        digitalWrite(front_led, LOW);
      }
      else{
        digitalWrite(front_led, HIGH);
      }
    }
    else if (val == "lb"){
      if(digitalRead(back_led)){
        digitalWrite(back_led, LOW);
      }
      else{
        digitalWrite(back_led, HIGH);
      }
    }
}

void CanonMovement(String val){
    int commaIndex = val.indexOf(' ');
    String prvni = val.substring(0, commaIndex);
    String druhy = val.substring(commaIndex + 1);
    int int_value = druhy.toInt();

    if (int_value >= 30 && int_value <= 90 && prvni == "bar"){
      ServoKanon.write(int_value);
    }
}

void Movement(String val){
  if( val == "fw") // Forward
    {
      Serial.print("JEDU DOPŘEDU");
      digitalWrite(m1a, HIGH);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, HIGH);
      digitalWrite(m2b, LOW);  
    }

  else if(val == "bw") // Backward
    {
      Serial.print("JEDU DOZADU");
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, HIGH);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, HIGH); 
    }
  
  else if(val == "lw") //Left
    {
      Serial.print("JEDU DOLEVA");
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, HIGH);
      digitalWrite(m2a, HIGH);
      digitalWrite(m2b, LOW);
    }

  else if(val == "rw") //Right
    {
      Serial.print("JEDU DOPRAVA");
      digitalWrite(m1a, HIGH);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, HIGH); 
    }
    
  else if(val == "s") //Stop
    {
      Serial.print("ZASTAVUJI");
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, LOW); 
    }
}
