//***************************************************************************************
//Configurations
//***************************************************************************************
#define GEVBUS_ADDRESS_HOST 0x00
#define GEVBUS_ADDRESS_BROADCAST 0x01
#define GEVBUS_REGISTER_COMMAND 0xFE
#define GEVBUS_REGISTER_COMMAND_ACK 0xFF


//***************************************************************************************
//Includes
//***************************************************************************************
#include <Wire.h>

//***************************************************************************************
//Global variables
//***************************************************************************************

//***************************************************************************************
//Methods
//***************************************************************************************
void GevbusInitHostMode()
{
  Wire.begin(GEVBUS_ADDRESS_HOST);
  Wire.onRequest(handleRequest);
}


void GevbusInitDeviceMode()
{
  Wire.begin(GEVBUS_ADDRESS_HOST);
}

void GevbusRequestAddress()
{
  Wire.requestFrom(GEVBUS_ADDRESS_HOST, 2);
  
}

void GevbusAnnounceAddress()
{
  
}

void GevbusReadRegister()
{
  
}

void GevbusWriteRegister()
{
  
}

void handleRequest()
{
  
}

