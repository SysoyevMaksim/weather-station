#include <DHT.h>
#include <SoftwareSerial.h>

#define DHTPIN -1
DHT dht(DHTPIN, DHT22);

SoftwareSerial mySerial(5, 4);

void setup() {
  mySerial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) { 
    Serial.println("Ошибка считывания");
    return;
  }
  Serial.print("Влажность: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Температура: ");
  Serial.print(t);
  Serial.println(" *C "); 

}
