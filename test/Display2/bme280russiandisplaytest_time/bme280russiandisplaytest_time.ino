#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "Calibri.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <TFT_eSPI.h>      // Hardware-specific library

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

Adafruit_BME280 bme; 
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

double t;
double pr;
double hm;

const char *ssid     = "SOLOX2";
const char *password = "kalinovskogo784";

const long utcOffsetInSeconds = 3600;

String daysOfTheWeek[7] = {"Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Субота"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Used for messages and the C array generator

  tft.begin();
  tft.setRotation(0);  // portrait

  unsigned status;

  fg = TFT_WHITE;
  bg = TFT_BLACK;
  Wire.begin(21, 22); 
  Wire.setClock(100000); 
  status = bme.begin(0x76);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();
  t = bme.readTemperature();
  hm = bme.readHumidity();
  pr = bme.readPressure() / 100.0F;
  
  tft.setTextColor(fg, bg);
  tft.loadFont(Calibri);
  
  tft.fillScreen(bg);
  tft.setCursor(0,0);

  tft.print(daysOfTheWeek[timeClient.getDay()]);
  tft.print(", ");
  tft.print(timeClient.getHours()+2);
  tft.print(":");
  tft.print(timeClient.getMinutes());
  tft.print(":");
  tft.println(timeClient.getSeconds());

  tft.println("Температура:");
  tft.print(t);
  tft.println("°C");
  tft.println("Влажность:");
  tft.print(hm);
  tft.println("%");
  tft.println("Давление:");
  tft.print(pr);
  tft.println("hPa");
  
  tft.unloadFont();

  delay(1000);;
}
