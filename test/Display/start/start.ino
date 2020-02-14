#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;
String integer, real, temperature="36.6", humidity="78%";

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#include <FreeDefaultFonts.h>

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410

void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    if (ID == 0xD3) ID = 0x9481;
    tft.begin(ID);
    tft.setRotation(1);
}

void temperature_out()
{
   for(int i = 0; i < temperature.length() - 2; i++)
    {
       integer += temperature[i];
    }
    real += s[temperature.length()-1];
    showmsgXY(0, 50, 1, &FreeSevenSegNumFont, integer);
    showmsgXY(integer.length()*28+7, 42, 1, NULL, ".");
    showmsgXY(integer.length()*28+14, 50, 1, &FreeSevenSegNumFont, real);
    integer = "";
    real = "";
}

void loop(void)
{
    tft.fillScreen(BLACK);
    temperature_out();
    showmsgXY(0, 1000, 1, &FreeSevenSegNumFont, integer);
    delay(10000);
}

void showmsgXY(int x, int y, int sz, const GFXfont *f, String msg)
{
    int16_t x1, y1;
    uint16_t wid, ht;
    //tft.drawFastHLine(0, y, tft.width(), WHITE);
    tft.setFont(f);
    tft.setCursor(x, y);
    tft.setTextColor(GREEN);
    tft.setTextSize(sz);
    tft.print(msg);
}
