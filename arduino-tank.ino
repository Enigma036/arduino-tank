#include <Servo.h> 

// Declare the Servo pin 
int servoPin = 3; 
int vole = 0;

// Create a servo object 
Servo Servo1; 

void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
   Servo1.write(90); 
   Serial.begin(9600);
}

void loop(){ 
  
  
  if (Serial.available() > 0) {
    // read the incoming bytes:
    String str = Serial.readString();

    if (str == "F"){
      vole += 10;
      Servo1.write(vole); 
    }
    else if (str == "G"){
      vole -= 10;
      Servo1.write(vole); 
    }
    
    }
  

}