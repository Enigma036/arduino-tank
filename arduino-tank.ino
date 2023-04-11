#include <Servo.h> 

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

  ServoVez.attach(servo_vez);  // Nastavení prvního serva
  ServoKanon.attach(kanon_vez); // Nastavení druhého serva

  pinMode(m1a, OUTPUT);  // Digital pin 10 set as output Pin
  pinMode(m1b, OUTPUT);  // Digital pin 11 set as output Pin
  pinMode(m2a, OUTPUT);  // Digital pin 12 set as output Pin
  pinMode(m2b, OUTPUT);  // Digital pin 13 set as output Pin

  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    value = Serial.readStringUntil('\n');
    Serial.println(value);
    
    Movement(value);

  
  }
}



void TurretMovement(String val){
    int commaIndex = val.indexOf(' ');
    String prvni = val.substring(0, commaIndex);
    String druhy = val.substring(commaIndex + 1);
    int int_value = druhy.toInt();

    if (int_value >= 0 && int_value <= 180 && prvni == "vez"){
      ServoVez.write(int_value);
      Serial.println("Uhel:" + int_value);
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