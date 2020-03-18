#ifdef USE_LIGHT_CONTROLLER

//***************************************************************************************
//Configurations
//***************************************************************************************

//Configuring the Light controller channels
#define MAX_LIGHT_CHANNELS 6

//***************************************************************************************
//Global variables
//***************************************************************************************
volatile byte pwm_set[MAX_LIGHT_CHANNELS] = {255, 50, 10, 255, 0, 0};
volatile byte pwm[MAX_LIGHT_CHANNELS] = {255, 65, 10, 255, 129, 0};
byte pwmPin [MAX_LIGHT_CHANNELS] = {25, 26, 36, 36, 36, 36};

TaskHandle_t RealTimeThread;

//***************************************************************************************
//Methods
//***************************************************************************************
void initLightControl()
{
  xTaskCreatePinnedToCore(realtime, "Realtime", 10000, NULL, 0, &RealTimeThread, 0);
}

void realtime(void* parameter)
{
  for(int i = 0; i < MAX_LIGHT_CHANNELS; i++)
  {
    pinMode(pwmPin[i], OUTPUT);
  }
  
  while(true)
  {
    for(int step = 0; step < 255; step++)
    {  
      for(int i = 0; i < MAX_LIGHT_CHANNELS; i++)
      {
        if(step == 0)
        {
          digitalWrite(pwmPin[i], 0);
        }
        if(pwm[i] > step)
        {
          digitalWrite(pwmPin[i], 1);
        }
      }
      delayMicroseconds(10);
    }
  }
}

#endif
