#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
MCUFRIEND_kbv tft;
uint16_t ox = 0, oy = 0;
int ave = 0, avec = 0; 
double avet = 0;
////////////////////////////////////////////////////////////////
void aveg(void)
{ int z = 0;
  Serial.println(ave);
  Serial.println(avec);
  avet = ave / (double)avec;
  Serial.println(avet);
  avet = avet * 21;
  for (int i = 0; i < 24; i++) {
    for (uint16_t a = 0; a < 3; a++) {
      tft.drawLine(avet + a, z, avet + a, z + 10, 0x0FFA);
    } // thick
    for (uint16_t a = 0; a < 2; a++) {
      tft.drawLine(avet - a, z, avet - a, z + 10, 0x0FFA);
    } delay(100); z = z + 20;
  }
}
void dchart_10x10(uint16_t nx, uint16_t ny) {
  ave += nx;
  avec++;
  nx = nx * 21;
  ny = ny * 32;
  tft.drawCircle(nx, ny, 7, 0xFC60);
  tft.drawCircle(nx, ny, 6, 0xFC60);
  tft.fillCircle(nx, ny, 4, 0xFC60);
  delay (100);
  ox = nx;
  oy = ny;
}
void dotchart_10x10(uint16_t nx, uint16_t ny) {
  ave += nx;
  avec++;
  nx = nx * 21;
  ny = ny * 32;
  int plus = 0; float fplus = 0;
  int sign = 0;
  int y = 0, x = 0;
  y = oy;
  x = ox;
  float xmines, ymines;
  xmines = nx - ox;
  ymines = ny - oy;
  if (ox > nx)
  { xmines = ox - nx;
    sign = 1;
  }
  else
    sign = 0;
  for (uint16_t a = 0; a < 2; a++) {
    tft.drawLine(ox + a, oy, nx + a, ny, 0xFC00);
  } // thick
  for (uint16_t a = 0; a < 2; a++) {
    tft.drawLine(ox, oy + a, nx, ny + a, 0xFC00);
  }
  for (int a = 0; a < (ny - oy); a++)
  {
    fplus += xmines / ymines;
    plus = fplus;
    if (sign == 1)
      tft.drawFastHLine(0, y, x - plus, 0xA040);
    else
      tft.drawFastHLine(0, y, x + plus, 0xA040);
    y++;
    delay(5);
  }
  ox = nx;
  oy = ny;
}
////////////////////////////////////////////////////////////////////
void setup() {
  tft.reset();
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
}
void loop() {
  tft.invertDisplay(true);
  tft.fillScreen(0xffff);
  dotchart_10x10(3, 0);
  dotchart_10x10(2, 1);
  dotchart_10x10(4, 2);
  dotchart_10x10(4, 3);
  dotchart_10x10(5, 4);
  dotchart_10x10(3, 5);
  dotchart_10x10(6, 6);
  dotchart_10x10(7, 7);
  dotchart_10x10(9, 8);
  dotchart_10x10(8, 9);
  dotchart_10x10(10, 10);
  dchart_10x10(3, 0);
  dchart_10x10(2, 1);
  dchart_10x10(4, 2);
  dchart_10x10(4, 3);
  dchart_10x10(5, 4);
  dchart_10x10(3, 5);
  dchart_10x10(6, 6);
  dchart_10x10(7, 7);
  dchart_10x10(9, 8);
  dchart_10x10(8, 9);
  dchart_10x10(10, 10);
  tft.setRotation(1);
  tft.setTextSize(2);
  tft.setTextColor(0xF700);
  tft.setCursor(20, 20);
  tft.print("Average");
  int dl = 20;
  for (int i = 0; i < 6; i++) {
    for (uint16_t a = 0; a < 3; a++) {
      tft.drawLine(dl, 40 + a, dl + 10, 40 + a, 0x0FFA);
    }
    dl += 16;
  }
  tft.setRotation(0);
  aveg();
  while (1);
}
