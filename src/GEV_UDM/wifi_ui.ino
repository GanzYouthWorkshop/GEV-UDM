#ifdef USE_WIFI

//***************************************************************************************
//Configurations
//***************************************************************************************
#define WIFI_PORT 8080
#define CONNECT_ATTEMPTS 10

//***************************************************************************************
//Includes
//***************************************************************************************
#include <WiFi.h>

//***************************************************************************************
//Global variables
//***************************************************************************************
char ssid[]     = "yourssid";
char password[] = "yourpasswd";

WiFiServer wifi_server(WIFI_PORT);

//***************************************************************************************
//Methods
//***************************************************************************************
void initWifi()
{
  if(try_to_connect(ssid, password, CONNECT_ATTEMPTS))
  { 
    //Able to connect to saved AP
    Serial.println(WiFi.localIP()); 
  }
  else
  {
    //Creating our own AP
    start_softap("TEST", "TEST");
  }

}

void handleWifi()
{
  WiFiClient client = wifi_server.available();
  handleNet(&client);
}

bool try_to_connect(char* ssid, char* pass, int connect_attempts)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  for(int i = 0; i < connect_attempts; i++)
  {
    if(WiFi.status() == WL_CONNECTED)
    {
      return true;
    }

    delay(500);   
  }
  
  return false;
}

bool start_softap(char* ssid, char* pass)
{
  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, pass);
}

#endif
