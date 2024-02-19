#include "Std_types.h"
#include "GPIO.h"

/*-----------------------------MODE SHIFTS----------------------*/
#define MODE_SHIFT			0
#define TYPE_SHIFT			8
#define PU_OR_PD_SHIFT		16


/*------------------------------------FACTOR SHIFT--------------*/
#define FACTOR_SHIFT		0x00000002


/*-----------------------------MASKS----------------------------*/

/*-------------------------CLEAR MODE BITS----------------------*/
#define GPIO_CLEAR_MODE_BITS		0x00000003
#define GPIO_CLEAR_TYPE_BITS		0x00000001
#define GPIO_CLEAR_PU_OR_PD_BITS	0x00000003
#define GPIO_CLEAR_SPEED_BITS		0x00000003

/*--------------------------GET MODE BITS-----------------------*/
#define GPIO_GET_MODE_BITS    		0x00000003
#define GPIO_GET_TYPE_BIT     		0x00000100
#define GPIO_GET_PUPD_BITS		    0x00030000


/*-------------------------------BSRR--------------------------*/
#define BSRR_OFFSET                 16
#define BSRR_BIT_VALUE              1

/*------------------------REGISTERS STRUCT---------------------*/
typedef struct
{
  volatile u32 GPIO_MODER;
  volatile u32 GPIO_OTYPER;
  volatile u32 GPIO_OSPEEDR;
  volatile u32 GPIO_PUPDR;
  volatile u32 GPIO_IDR;
  volatile u32 GPIO_ODR;
  volatile u32 GPIO_BSRR;
  volatile u32 GPIO_LCKR;
  volatile u32 GPIO_AFRL;
  volatile u32 GPIO_AFRH;
} GPIO_Port_t;

#define GPIO_A							((volatile GPIO_Port_t*)(GPIO_PORT_A_BASE_ADDRESS))
#define GPIO_B							((volatile GPIO_Port_t*)(GPIOB_PORT_B_BASE_ADDRESS))
#define GPIO_C							((volatile GPIO_Port_t*)(GPIOC_PORT_C_BASE_ADDRESS))



/*--------------------------------------------------------------*/
/*--------------------------GPIO_Init---------------------------*/
/*@brief: function to initialize the pin configurations---------*/
/*@param: PtrtoPinConfig----------------------------------------*/
/*@return:GPIO_enuErrorStatus-----------------------------------*/
/*@constraint: Clock must be enabled before initializing--------*/
/*--------------------------------------------------------------*/
GPIO_enuErrorStatus GPIO_Init(GPIO_Pin_t *PtrtoPinConfig)
{
	GPIO_enuErrorStatus ErrorStatus;
	ErrorStatus = GPIO_enuOK;

	if(PtrtoPinConfig == NULL)
	{
		ErrorStatus = GPIO_enuNotOK;
	}

	else if(PtrtoPinConfig->Mode > ALT_FUNC_OD_PD)
	{
		ErrorStatus = GPIO_enuNotOK;
	}

	else if(PtrtoPinConfig->Pin > GPIO_PIN_15)
	{
		ErrorStatus = GPIO_enuNotOK;
	}

	else if(PtrtoPinConfig->Port != GPIO_PORT_A_BASE_ADDRESS && PtrtoPinConfig->Port != GPIO_PORT_B_BASE_ADDRESS && PtrtoPinConfig->Port != GPIO_PORT_C_BASE_ADDRESS)
	{
		ErrorStatus = GPIO_enuNotOK;
	}

	else if(PtrtoPinConfig->Speed > GPIO_SPEED_VHIGH)
	{
		ErrorStatus = GPIO_enuNotOK;
	}

	else
	{
		//local variables for the gpio registers
		u32 Loc_MODER=0;
		u32 Loc_OTYPER=0;
		u32 Loc_OSPEEDR=0;
		u32 Loc_PUPDR=0;
		//local variables for the configurations
		u32 Loc_ModeValue=0x00000000;
		u32 Loc_TypeValue=0x00000000;
		u32 Loc_PUPDValue=0x00000000;

		//copy mode bits, type bit and PU/PD bits to local variables
		Loc_ModeValue = (PtrtoPinConfig->Mode & GPIO_GET_MODE_BITS)>>MODE_SHIFT;
		Loc_TypeValue = (PtrtoPinConfig->Mode & GPIO_GET_TYPE_BIT )>>TYPE_SHIFT;
		Loc_PUPDValue = (PtrtoPinConfig->Mode & GPIO_GET_PUPD_BITS)>>PU_OR_PD_SHIFT;


		//copy config from registers to the local variables
		Loc_MODER 	= ((GPIO_Port_t *)PtrtoPinConfig->Port)->GPIO_MODER;
		Loc_OTYPER 	= ((GPIO_Port_t *)PtrtoPinConfig->Port)->GPIO_OTYPER;
		Loc_OSPEEDR = ((GPIO_Port_t *)PtrtoPinConfig->Port)->GPIO_OSPEEDR;
		Loc_PUPDR 	= ((GPIO_Port_t *)PtrtoPinConfig->Port)->GPIO_PUPDR;


		//clear config bits
		Loc_MODER 	&= ~(GPIO_CLEAR_MODE_BITS<<(PtrtoPinConfig->Pin*FACTOR_SHIFT));
		Loc_OTYPER 	&= ~(GPIO_CLEAR_TYPE_BITS<<(PtrtoPinConfig->Pin*FACTOR_SHIFT));
		Loc_OSPEEDR &= ~(GPIO_CLEAR_SPEED_BITS<<(PtrtoPinConfig->Pin*FACTOR_SHIFT));
		Loc_PUPDR 	&= ~(GPIO_CLEAR_PU_OR_PD_BITS<<(PtrtoPinConfig->Pin*FACTOR_SHIFT));

		//assign the values
		Loc_MODER 	|= (Loc_ModeValue<<(PtrtoPinConfig->Pin*FACTOR_SHIFT));
		Loc_OTYPER 	|= (Loc_TypeValue<<(PtrtoPinConfig->Pin));
		Loc_OSPEEDR |= ((PtrtoPinConfig->Speed) <<(PtrtoPinConfig->Pin*FACTOR_SHIFT));
		Loc_PUPDR 	|= (Loc_PUPDValue<<(PtrtoPinConfig->Pin*FACTOR_SHIFT));

		//copy from local variables to registers
		((GPIO_Port_t *)PtrtoPinConfig->Port)->GPIO_MODER  		= Loc_MODER;
		((GPIO_Port_t *)PtrtoPinConfig->Port)->GPIO_OTYPER 		= Loc_OTYPER;
		((GPIO_Port_t *)PtrtoPinConfig->Port)->GPIO_OSPEEDR		= Loc_OSPEEDR;
		((GPIO_Port_t *)PtrtoPinConfig->Port)->GPIO_PUPDR		= Loc_PUPDValue;

		ErrorStatus = GPIO_enuOK;
	}


	return ErrorStatus;
}


/*--------------------------------------------------------------*/
/*-----------------------GPIO_SetPinValue-----------------------*/
/*@brief: function to set the pin values------------------------*/
/*@param: PtrtoGPIO_Port, GPIO_PinNumber, GPIO_PinStatus--------*/
/*@return:GPIO_enuErrorStatus-----------------------------------*/
/*@constraint: GPIO must be initialized before setting pins-----*/
/*--------------------------------------------------------------*/
GPIO_enuErrorStatus GPIO_SetPinValue(void *PtrtoGPIO_Port,u32 GPIO_PinNumber, u8 GPIO_PinStatus)
{
	GPIO_enuErrorStatus ErrorStatus;
	ErrorStatus = GPIO_enuOK;

	if(PtrtoGPIO_Port == NULL)
	{
		ErrorStatus = GPIO_enuNotOK;
	}

	else if(GPIO_PinNumber > GPIO_PIN_15)
	{
		ErrorStatus = GPIO_enuNotOK;
	}

	else if(GPIO_PinStatus > GPIO_STATE_SET)
	{
		ErrorStatus = GPIO_enuNotOK;
	}

	else
	{
		//set pin
		if(GPIO_PinStatus == GPIO_STATE_SET)
		{
			((GPIO_Port_t*)PtrtoGPIO_Port)->GPIO_BSRR |= BSRR_BIT_VALUE<<GPIO_PinNumber;
		}
		//reset pin (using offset)
		else
		{
			((GPIO_Port_t*)PtrtoGPIO_Port)->GPIO_BSRR |= (BSRR_BIT_VALUE<<(GPIO_PinNumber+BSRR_OFFSET));
		}

		ErrorStatus = GPIO_enuOK;
	}


	return ErrorStatus;
}

/*--------------------------------------------------------------*/
/*-----------------------GPIO_GetPinValue-----------------------*/
/*@brief: function to get the pin values------------------------*/
/*@param: PtrtoGPIO_Port, GPIO_PinNumber, PtrtoPinStatus--------*/
/*@return:GPIO_enuErrorStatus-----------------------------------*/
/*--------------------------------------------------------------*/
GPIO_enuErrorStatus GPIO_GetPinValue(void *PtrtoGPIO_Port,u32 GPIO_PinNumber, u8 *PtrtoPinStatus)
{
	GPIO_enuErrorStatus ErrorStatus;
		ErrorStatus = GPIO_enuOK;

		if(PtrtoGPIO_Port == NULL || PtrtoPinStatus == NULL)
		{
			ErrorStatus = GPIO_enuNotOK;
		}

		else if(GPIO_PinNumber > GPIO_PIN_15)
		{
			ErrorStatus = GPIO_enuNotOK;
		}

		else
		{
			*PtrtoPinStatus = (((GPIO_Port_t*)PtrtoGPIO_Port)->GPIO_IDR >> GPIO_PinNumber)&1;
			ErrorStatus = GPIO_enuOK;
		}

		return ErrorStatus;
}


