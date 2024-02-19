#include "../../MCAL/GPIO/GPIO.h"
#include "LED.h"

extern const LED_CONFIG_t LEDs[LED_Number];

LED_enuErrorStatus LED_Init()
{
	LED_enuErrorStatus ErrorStatus;
	ErrorStatus = LED_enuOK;

	GPIO_Pin_t Led;
	u8 i;
	Led.Mode = OUTPUT_PP_FLOAT;
	Led.Speed= GPIO_SPEED_MED;

	for(i=0; i<LED_Number; i++)
	{
		Led.Pin=LEDs[i].PIN;
		Led.Port= LEDs[i].PORT;
		GPIO_Init(&Led);

	}

	return ErrorStatus;
}

LED_enuErrorStatus LED_SetState(u32 Led, u8 State)
{
	LED_enuErrorStatus ErrorStatus;
	ErrorStatus = LED_enuOK;

	GPIO_SetPinValue(LEDs[Led].PORT, LEDs[Led].PIN, LEDs[Led].DIRECTION ^ State);

	return ErrorStatus;
}
