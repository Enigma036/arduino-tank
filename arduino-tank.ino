#include <Servo.h> 

// Declare the Servo pin 
int servoPin = 3; 

// Create a servo object 
Servo Servo1; 

void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
   Servo1.write(0); 
   Serial.begin(38400);
}

void loop(){ 
  /*if (Serial.available() > 0) {
    // read the incoming bytes:
    String str = Serial.readStringUntil('\n');
    */

    /*
    int commaIndex = str.indexOf(' ');
    String a = str.substring(0, commaIndex);
    String b = str.substring(commaIndex + 1);
    
    int incomingByte = b.toInt();
    if (incomingByte >= 0 && incomingByte <= 180 && a == "vez"){
      Servo1.write(incomingByte);
      Serial.println("Uhel:" + incomingByte);
    }
    */

  for(int i=0; i <= 180; i +=10){
    Servo1.write(i);
    delay(100);
  }

  for(int i=180; i >= 0; i -=10){
    Servo1.write(i);
    delay(100);
  }

  //}
}