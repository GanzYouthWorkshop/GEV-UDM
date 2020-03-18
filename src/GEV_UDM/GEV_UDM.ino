//***************************************************************************************
//Configurations
//***************************************************************************************
// Use the defines below to enable/disable certain functionalities
// Disabling a function will remove the functionality from compilation - this saves both program and operational memory

#define USE_LIGHT_CONTROLLER  //Defines the PWM constant current switching functionality - light_control.ino
#define USE_GPIO              //Defines the GPIO feature - not implemented yet
#define USE_WIFI              //Defines the Wifi AP and client feature - wifi_ui.ino
#define USE_ETHERNET          //Defines the Ethernet feature - ethernet_ui.ino
#define USE_WEB               //Defines the common web interface - web_ui.indo, net_ui.ino
#define USE_OLED              //Defines the OLED and physical button interface - phy_ui.ino
#define USE_TELNET            //Defines a telnet interface - not implemented yet
#define USE_SERIAL            //Defines a USB-RS232 command interface - main module

#define FIRMWARE_VERSION 10   //Version 0.1 - Format works as follow: 123456 is v12.34.56, 115 is v1.15

//***************************************************************************************
//Includes
//***************************************************************************************

//***************************************************************************************
//Global variables
//***************************************************************************************

volatile byte databank_special[1024];
volatile byte databank_general[4096];

//***************************************************************************************
//Setup
//***************************************************************************************
void setup()
{
  //Starting debug port at 115200 baud
  Serial.begin(115200);
  
  Serial.write("\n============================================\n");
  Serial.write("| Code based on GEV IoT Framework for ESP. |\n");
  Serial.write("| ---------------------------------------- |\n");
  Serial.write("| Copyright Ganz Youth Workshop 2019.      |\n");
  Serial.write("============================================\n\n");

  Serial.write("Debug port open. \n");

#ifdef USE_OLED
  initOLED();
  Serial.write("Display initialized.\n");
#endif
  
#ifdef USE_WIFI
  initWifi();
  Serial.write("Wifi started.\n");
#endif

#ifdef USE_ETHERNET
  initEthernet();
  Serial.write("Ethernet started.\n");
#endif

#ifdef USE_LIGHT_CONTROLLER
  //Setting up second core program
  initLightControl();
  Serial.write("Light control started.\n");
#endif
}

//***************************************************************************************
// Program of core 1 - communications and administration
//***************************************************************************************
void loop()
{
  //Handling Serial input - this is always on!
  handleSerial();

#ifdef USE_OLED
  //Handle physical buttons an OLED display
  handleOLED();
#endif

#ifdef USE_WIFI
  //Handling Wifi input
  handleWifi();
#endif

#ifdef USE_ETHERNET
  //Handling Ethernet input over SPI
  handleEthernet();
#endif

  delay(1);
}

void handleSerial()
{
  
}


