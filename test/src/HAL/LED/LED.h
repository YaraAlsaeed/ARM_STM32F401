#ifndef LED_H_
#define LED_H_

#include "Std_types.h"
#include "LED_CONFIG.h"

#define LED_DIRECTION_FORWARD		0
#define LED_DIRECTION_REVERSE		1
#define LED_STATE_ON				1
#define LED_STATE_OFF				0


typedef struct
{
	void *PORT;
	u32 PIN;
	u8 DIRECTION
}LED_CONFIG_t;


typedef enum
{
	LED_enuOK,
	LED_enuNOTOK
}LED_enuErrorStatus;


LED_enuErrorStatus LED_Init();

LED_enuErrorStatus LED_SetState(u32 Led, u8 State);

#endif
