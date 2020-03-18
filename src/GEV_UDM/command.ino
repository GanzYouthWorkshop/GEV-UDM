//***************************************************************************************
//Configurations
//***************************************************************************************

//***************************************************************************************
//Includes
//***************************************************************************************

//***************************************************************************************
//Global variables
//***************************************************************************************

/*typedef struct t_command_result
{
  int result_code.
  bool is_output,
  int result,
} CommandResult;*/

#define COMMAND_NONE 0
#define COMMAND_PING 1
#define COMMAND_READ_FIRMWARE_VER 2

#define COMMAND_READ_REGISTER 10
#define COMMAND_WRITE_REGISTER 11

#define COMMAND_LIGHT_TURN 101
#define COMMAND_LIGHT_SET_PWM 100

//***************************************************************************************
//Setup
//***************************************************************************************
/*CommandResult handleCommand(int command, int argument1, int argument2)
{
  
  CommandResult result = { 1, false, 0 };
  
  switch(command)
  {
    case COMMAND_NONE: 
      break;
      
    case COMMAND_PING:
      result.is_output = true;
      result.result = argument1;
      break;
      
    case COMMAND_READ_FIRMWARE_VER:
      result.result = FIRMWARE_VERSION;
      break;

    case COMMAND_READ_REGISTER:
      

    case COMMAND_WRITE_REGISTER:
      if(argument1 < 0 || argument 1 >= (5 * 1024))
      {
        result.result_code = 0;
        break;
      }
      else
      {
        byte* databank;
        if (argument1 < 1024
        {
          result.result = databank_special[argument1];
        }
        else
        {
          result.result = databank_general[argument1 - 1024];
        }

        result.result = argument1;
      }
          
    default:
      result.result_code = 0;
      break;
  }

  return result;
}*/

/*CommandResult readRegister(int reg)
{
  if(reg < 0 || reg 1 >= (5 * 1024))
  {
    result.result_code = 0;
    break;
  }
  else
  {
    if (argument1 < 1024
    {
      result.result = databank_special[reg];
    }
    else
    {
      result.result = databank_general[reg - 1024];
    }
  }
}*/

