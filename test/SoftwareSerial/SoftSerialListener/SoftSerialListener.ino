#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(3, 2); // RX, TX

void setup() {
  Serial.begin(9600);
  Serial.println("Listening...");
  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available())
    Serial.write(mySerial.read());
}
