#include "Std_types.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "SWITCH.h"

extern const SWITCH_CONFIGURATIONS arrOfSwitches[Switches_Number];

Switch_enuErrorStatus Switch_Init()
{
	Switch_enuErrorStatus ErrorStatus;
	ErrorStatus = Switch_enuOK;
	GPIO_Pin_t Switch;
	u8 i;

	for(u8 i=0; i<Switches_Number; i++)
	{
		Switch.Port = arrOfSwitches[i].port;
		Switch.Pin	= arrOfSwitches[i].PIN;
		Switch.Mode = arrOfSwitches[i].MODE;
		GPIO_Init(&Switch);
	}
	return ErrorStatus;
}


Switch_enuErrorStatus Switch_GetState(u8 Switch, u32 *Switch_State)
{
	Switch_enuErrorStatus ErrorStatus;
	ErrorStatus = Switch_enuOK;
	u8 Temp;

	if(Switch_State == NULL)
	{
		ErrorStatus = Switch_enuNotOK;
	}
	else
	{
		ErrorStatus = GPIO_GetPinValue(arrOfSwitches[Switch].port, arrOfSwitches[Switch].PIN, &Temp);
		*Switch_State = Temp^(arrOfSwitches[Switch].CONNECTION_MODE);
	}

	return ErrorStatus;
}
