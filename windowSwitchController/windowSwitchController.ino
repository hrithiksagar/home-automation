/* windows switch for an automated window
* one relays toggles power on/off the other relay changes wire 
* basically it switches power on/of and from one wire to another making the windows actuators move up/down
* the window switch is controlled by bluetooth for testing, it will be improved to be connected by virtual wire switch
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 5); // RX, TX
const int powerRelay = 7;
const int switcherRelay = 8;
const int timeToMove = 21000;
byte state = LOW;

void setup() 
{
  mySerial.begin(9600);
  mySerial.setTimeout(70);    
  Serial.begin(9600);
  pinMode(powerRelay, OUTPUT);
  pinMode(switcherRelay, OUTPUT);
  digitalWrite(powerRelay, HIGH);
  digitalWrite(switcherRelay, HIGH);
}

void loop() 
{
  if (mySerial.available() > 0) {
    int received = mySerial.read() - 48;
    Serial.println(received);    
    if (received >= 0 && received <= 4) {
        Serial.println("Mooving");
        moveWindow(received);
    }  
  }  
  delay(2);  
}

void moveWindow(int received)
{
    if (received == 0) {
         state = HIGH;
         Serial.println("Mooving up");
    } else if (received == 1) {
         state = 1;
         Serial.println("Mooving down");
         state = LOW;
    } else if (received == 3) {
         Serial.println("Switching");
         if (state == LOW) {
             state = HIGH;             
         } else {
             state = LOW;           
         }    
    }
   digitalWrite(switcherRelay, state);    
   digitalWrite(powerRelay, LOW);
   delay(timeToMove);
   digitalWrite(powerRelay, HIGH);    
}
