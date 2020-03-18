#ifdef USE_OLED

//***************************************************************************************
//Configurations
//***************************************************************************************
#define SSD1306_128_32
#define OLED_RESET 4

//***************************************************************************************
//Includes
//***************************************************************************************
#include "lib/Adafruit-GFX/Adafruit_GFX.h"
#include "lib/Adafruit_SSD1306/Adafruit_SSD1306.h"

#include "lib/QRCode/qrcode.h"

//***************************************************************************************
//Global variables
//***************************************************************************************
enum ScreenMenus
{
  overview = 0,
  showIp = 1,
  showMask = 2,
  showQR = 3,
};

Adafruit_SSD1306 display(OLED_RESET);
int currentMenuState = ScreenMenus::overview;

//***************************************************************************************
//Resources
//***************************************************************************************

const PROGMEM byte ICON_ETH[] = { 0x00, 0x00, 0x1f, 0xf8, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x1f, 0xf8, 0x11, 0x88, 0x11, 0x88, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x1f, 0xf8, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80 };
const PROGMEM byte ICON_LIGHT[] = { 0x00, 0x00, 0x03, 0xe0, 0x04, 0x10, 0x08, 0x08, 0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x11, 0xc4, 0x08, 0x88, 0x08, 0x88, 0x04, 0x90, 0x03, 0xe0, 0x02, 0x20, 0x02, 0x20, 0x01, 0xc0, 0x00, 0x00 };
const PROGMEM byte ICON_WIFI[] = { 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x1c, 0x38, 0x20, 0x04, 0x43, 0xc2, 0x0c, 0x30, 0x10, 0x08, 0x03, 0xc0, 0x04, 0x20, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const PROGMEM byte ICON_STATUS[] = { 0x00, 0x00, 0x03, 0xe0, 0x04, 0x10, 0x08, 0x08, 0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x11, 0xc4, 0x08, 0x88, 0x08, 0x88, 0x04, 0x90, 0x03, 0xe0, 0x02, 0x20, 0x02, 0x20, 0x01, 0xc0, 0x00, 0x00 };
const PROGMEM byte ICON_GEV[] = { 0x00, 0x00, 0x03, 0xe0, 0x04, 0x10, 0x08, 0x08, 0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x11, 0xc4, 0x08, 0x88, 0x08, 0x88, 0x04, 0x90, 0x03, 0xe0, 0x02, 0x20, 0x02, 0x20, 0x01, 0xc0, 0x00, 0x00 };

//***************************************************************************************
//Methods
//***************************************************************************************
void initOLED()
{
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(3);
  clear();
  
  currentMenuState = ScreenMenus::overview;
}

void handleOLED()
{
  handlePhyInput();

  switch(currentMenuState)
  {
    case ScreenMenus::overview: drawOverview(); break;
    case ScreenMenus::showIp: drawIP(); break;
    case ScreenMenus::showQR: drawQR(); break;  
  }
}

void handlePhyInput()
{
  if(digitalRead(12))
  {
    //Up button pressed

    if(currentMenuState == 0)
    {
      currentMenuState = 3;
    }
    else
    {
      currentMenuState--;
    }

    Serial.println(currentMenuState);
    delay(200);
  }

  if(digitalRead(13))
  {
    //Down button pressed

    if(currentMenuState == 999)
    {
      currentMenuState = 0;
    }
    else
    {
      currentMenuState++;
    }

    Serial.println(currentMenuState);
    delay(200);
  }
}

void clear()
{
  display.fillScreen(0);
  display.display();
}

void drawOverview()
{  
  display.fillScreen(0);

  display.drawBitmap(0, 9, ICON_LIGHT, 16, 16, 1);
  drawMenu(1);
  
  int y0 = 40;
  int dy = 0;
  for(int i = 0; i < 6; i++)
  {    
    dy = i * 13;
    
    display.drawChar(0, y0 + dy, '1' + i, 1, 0, 1);

    if(pwm_set[i] > 0)
    {
      display.fillCircle(12, y0 + dy + 4, 3, 1);
    }
    else
    {
      display.drawCircle(12, y0 + dy + 4, 3, 1);
    }
    
    /*display.drawLine(9, y0 + dy, 9, y0 + 7 + i * 13, 1);
    display.drawLine(18, y0 + dy, 18, y0 + 7 + i * 13, 1);
    
    display.drawLine(9, y0 + dy, 11, y0 + dy, 1);
    display.drawLine(16, y0 + dy, 18, y0 + dy, 1);
    display.drawLine(9, y0 + 7 + dy, 11, y0 + 7 + dy, 1);
    display.drawLine(16, y0 + 7 + dy, 18, y0 + 7 + dy, 1);

    //TODO
    display.fillRect(11, y0 + 2 + dy, 4, 4, 1);*/

    display.drawLine(20, y0 + dy, 20, y0 + 7 + dy, 1);
    display.drawLine(20, y0 + 7 + dy, 30, y0 + 7 + dy, 1);
    display.drawLine(30, y0 + dy, 30, y0 + 7 + dy, 1);

    int pow = pwm[i] / 32;
    display.fillRect(22, y0 + dy + 7 - pow, 7, pow, 1);  
  }
   
  display.display();
}

void drawIP()
{
  display.fillScreen(0);
  
  drawMenu(0);

  display.drawBitmap(0, 9, ICON_ETH, 16, 16, 1);

  display.setTextColor(1, 0);
  display.setTextSize(1);
  display.setTextWrap(true);

  uint8_t ip[4] = {192,168,10,6};
  uint8_t myMASK[4] = {255,255,255,0};

  for(int i = 0; i < 4; i++)
  {
    display.setCursor(0, 27 + i * 10);
    display.print(ip[i]);
    display.drawChar(18, 27 + i * 10, '.', 1, 0, 1);

    display.setCursor(0, 76 + i * 10);
    display.print(myMASK[i]);
    display.drawChar(18, 76 + i * 10, '.', 1, 0, 1);

  }

  display.drawLine(2, 70, 20, 70, 1);
  display.display();
}

void drawQR()
{
  display.fillScreen(0);

  display.drawBitmap(0, 9, ICON_WIFI, 16, 16, 1);
  drawMenu(2);

  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 3, 0, "http://192.168.100.100:8080/");

  for (uint8_t y = 0; y < qrcode.size; y++)
  {
    for (uint8_t x = 0; x < qrcode.size; x++)
    {
      display.drawPixel(x, y + 48, qrcode_getModule(&qrcode, x, y) ? 1 : 0);
    }
  }
  display.display();
}

void drawMenu(int current)
{
  display.drawLine(11, 4, 15, 0, 1);
  display.drawLine(16, 0, 20, 4, 1);
  display.drawLine(11, 123, 15, 127, 1);
  display.drawLine(16, 127, 20, 123, 1);
  
  for(int i = 0; i < 6; i++)
  {
    int x = 16 + (i % 3) * 6;
    int y = 9 + (i / 3) * 6;

    if(i == current)
    {    
      //display.fillRect(27, 40 + i * 6, 4, 4, 1);
      display.fillRect(x, y, 4, 4, 1);
    }
    else
    {
      //display.drawRect(27, 40 + i * 6, 4, 4, 1);
      display.drawRect(x, y, 4, 4, 1);
    }
  }   
}
#endif
