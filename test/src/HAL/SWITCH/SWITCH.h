#ifndef SW_H_
#define SW_H_

#include "Std_types.h"
#include "SWITCH_CONFIG.h"
#include "../../MCAL/GPIO/GPIO.h"

#define Switch_PULL_UP 					INPUT_PU
#define Switch_PULL_DOWN 				INPUT_PD


#define Switch_STATE_PRESSED 			0x00000001
#define Switch_STATE_NOT_PRESSED 		0x00000000

#define Switch_CONNECTION_MODE_INTPU	0x00000001
#define Switch_CONNECTION_MODE_INTPD	0x00000000

#define Switch_4Bits_OFFSET 			0x00000004

typedef enum {
  Switch_enuOK,
  Switch_enuNotOK
}Switch_enuErrorStatus;


typedef enum
{
	Switch_Released,
	Switch_Pressed
}Switch_Status_t;

typedef struct
{
    void *port;
	u32 PIN;
	u32 MODE;
	u32 CONNECTION_MODE;
}SWITCH_CONFIGURATIONS;

Switch_enuErrorStatus Switch_Init();

Switch_enuErrorStatus Switch_GetState(u8 Switch, u32 *Switch_State);


#endif
