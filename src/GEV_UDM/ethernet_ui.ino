#ifdef USE_ETHERNET

//***************************************************************************************
//Configurations
//***************************************************************************************
#define WEB_PORT 80

//***************************************************************************************
//Includes
//***************************************************************************************
#include <SPI.h>
#include "lib/ethernet/EthernetServer.h"

//***************************************************************************************
//Global variables
//***************************************************************************************
EthernetServer server(WEB_PORT);

uint8_t mac[6] = {0x45,0xB0,0xB0,0xA0,0x34,0x65};
IPAddress ip(192, 168, 10, 6);

//***************************************************************************************
//Methods
//***************************************************************************************
void initEthernet()
{
  Ethernet.init(5);
  Ethernet.begin(mac, ip);

  /*if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true)
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF)
  {
    Serial.println("Ethernet cable is not connected.");
  }*/

  server.begin();
  
  Serial.print("Ethernet address: ");
  Serial.println(Ethernet.localIP());
}

void handleEthernet()
{
  EthernetClient client = server.available();
  if (client)
  {
    handleNet(&client);    
  }
}

#endif
