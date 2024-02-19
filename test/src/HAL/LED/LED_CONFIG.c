#include "../../MCAL/GPIO/GPIO.h"
#include "LED.h"

const LED_CONFIG_t LEDs[LED_Number] =
{
		[LED_Alarm]= {
					 .PORT 		= GPIO_PORT_A_BASE_ADDRESS,
					 .PIN  		= GPIO_PIN_0,
					 .DIRECTION = LED_DIRECTION_REVERSE},

		[LED_Red]  = {
					 .PORT		= GPIO_PORT_A_BASE_ADDRESS,
					 .PIN		= GPIO_PIN_1,
					 .DIRECTION = LED_DIRECTION_FORWARD}
};


