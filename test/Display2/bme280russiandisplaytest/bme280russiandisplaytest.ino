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

double t = 36.6;
double pr;
double hm;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  t = bme.readTemperature();
  hm = bme.readHumidity();
  pr = bme.readPressure() / 100.0F;
  
  tft.setTextColor(fg, bg);
  tft.loadFont(Calibri);
  
  tft.fillScreen(bg);
  tft.setCursor(0,0);

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

  delay(2000);
}
