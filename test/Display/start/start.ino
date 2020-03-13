#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;
String integer, real, temperature="36.6", humidity="78", hours = "17", minutes="30";

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

void temperature_out(int x, int y)
{
   for(int i = 0; i < temperature.length() - 2; i++)
    {
       integer += temperature[i];
    }
    real += temperature[temperature.length()-1];
    showmsgXY(x, y, 1, &FreeSevenSegNumFont, integer);
    showmsgXY(integer.length()*28+7 + x, y - 8, 1, NULL, ".");
    showmsgXY(integer.length()*28+14 + x, y, 1, &FreeSevenSegNumFont, real);
    tft.setCursor((integer.length()+2)*28 + x, y - 48);
    tft.setFont(NULL);
    tft.setTextSize(3);
    tft.print("o");
    showmsgXY((integer.length()+2)*28 + 19 + x, y - 3, 3, &FreeSerif12pt7b, "C");
    integer = "";
    real = "";
}   
    
void humidity_out (int x, int y)
{   
    showmsgXY(x, y, 1, &FreeSevenSegNumFont, humidity);
    showmsgXY(humidity.length()*28 + 19 + x, y, 3, &FreeSerif12pt7b, "%");
}

void real_time_out (int x, int y)
{
    showmsgXY(x, y, 1, &FreeSevenSegNumFont, hours);
    showmsgXY(hours.length()*28 + 2 + x, y - 56, 9, NULL, ":");
    showmsgXY(hours.length()*28 + 2 + x + 34, y, 1, &FreeSevenSegNumFont, minutes);
}

void start_display()
{
    real_time_out(150, 55);
    temperature_out(0, 110);
    humidity_out(0, 165);
}

void loop(void)
{
    tft.fillScreen(BLACK);
    //temperature_out(0, 50);
    //humidity_out (0, 50);
    //real_time_out(0, 50);
    start_display();
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
