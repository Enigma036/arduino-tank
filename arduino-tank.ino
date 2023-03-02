#include <Servo.h> //zahrnutí knihovny pro ovládání servo motoru
Servo myservo; //každý motor má svou instanci třídy Servo
Servo myservoVez;
int pos = 30; //proměnná obsahující pozici motoru (úhel natočení)
int t = 1;
int tlacitko = 0;
int position = 0;
byte brightness; // INT for received serial data
void setup() {
  Serial.begin(38400); // Serial communication begin to read data
  myservo.attach(7); //tento motor je připojen na pin D9
  myservoVez.attach(5);
  myservo.write(90);
  myservoVez.write(pos); // Max - 90; Min - 30 
  pinMode(3, OUTPUT);
}
void loop()
{
  if (Serial.available() > 0) {
    // read byte of received data:
    brightness = Serial.read();
    if(brightness == 48){
      if(pos > 35){
        pos = pos - 60;
      }
    }
    else if(brightness == 51){
      if(tlacitko == 0){
        digitalWrite(3, HIGH);
        tlacitko = 1;
      }
      else{
        digitalWrite(3, LOW);
        tlacitko = 0;        
      }
    }
    else if(brightness == 10){
      ;
    }
    else{
      if(pos < 85){
        pos = pos + 60;
      }
    }
    myservoVez.write(pos);
    Serial.println(brightness);
  }
}


