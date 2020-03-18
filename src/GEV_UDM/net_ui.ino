

//***************************************************************************************
//Configurations
//***************************************************************************************

//***************************************************************************************
//Includes
//***************************************************************************************

//***************************************************************************************
//Global variables
//***************************************************************************************

//***************************************************************************************
//Methods
//***************************************************************************************
void handleNet(Client* cs)
{
  if (cs)
  {
    if(cs->connected())
    {
      Serial.write("Incoming eth...\n");
    }
    
    boolean currentLineIsBlank = true;
    while (cs->connected())
    {
      if (cs->available())
      {
        char c = cs->read();
        if (c == '\n' && currentLineIsBlank)
        {
          cs->println("HTTP/1.1 200 OK");
          cs->println("Content-Type: text/plain");
          cs->println("Connection: close");
          cs->println();        
          cs->println("Faszom az SPI buszba...");
          break;
        }
        if (c == '\n')
        {
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          currentLineIsBlank = false;
        }
      }
    }
    delay(10);
    cs->stop();
  }
}

