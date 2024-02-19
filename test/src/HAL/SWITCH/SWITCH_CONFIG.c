#include "../../MCAL/GPIO/GPIO.h"
#include "SWITCH.h"

const SWITCH_CONFIGURATIONS arrOfSwitches[Switches_Number] =
{
		[Switch1] = {
						.port = GPIO_PORT_B_BASE_ADDRESS,
						.PIN  = GPIO_PIN_0,
						.MODE = Switch_PULL_UP,
						.CONNECTION_MODE = Switch_CONNECTION_MODE_INTPU
		},

		[Switch2] = {
						.port = GPIO_PORT_B_BASE_ADDRESS,
						.PIN  = GPIO_PIN_1,
						.MODE = Switch_PULL_UP,
						.CONNECTION_MODE = Switch_CONNECTION_MODE_INTPU
		}
};
