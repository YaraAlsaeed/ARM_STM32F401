#ifndef _RCC_H
#define _RCC_H

#include "Std_types.h"

/*-------------------------------------------------------------*/
/*-------------------1st section: #defines---------------------*/
/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*---------------------Register Addresses----------------------*/
/*-------------------------------------------------------------*/


/*RCC Based Address*/
#define RCC_u32BASEADDRESS  0x40023800


typedef struct
{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 RCC_RESERVERD;
	volatile u32 RCC_RESERVED1;
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 RCC_RESERVED2;
	volatile u32 RCC_RESERVED3;
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 RCC_RESERVED4;
	volatile u32 RCC_RESERVED5;
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
}Rcc_tstrRegisterType;



/*Make the structure point at the base address of RCC*/
//#define RCC		((Rcc_tstrRegisterType* )(RCC_u32BASEADDRESS))
Rcc_tstrRegisterType *const RCC = (Rcc_tstrRegisterType *)RCC_u32BASEADDRESS;
/*
#define RCC_CR                  *((volatile u32*)0x40023800)
#define RCC_PLLCFGR             *((volatile u32*)0x40023804)
#define RCC_CFGR                *((volatile u32*)0x40023808)
#define RCC_CIR                 *((volatile u32*)0x4002380C)
#define RCC_AHB1RSTR            *((volatile u32*)0x40023810)
#define RCC_AHB2RSTR            *((volatile u32*)0x40023814)
#define RCC_APB1RSTR            *((volatile u32*)0x40023820)
#define RCC_APB2RSTR            *((volatile u32*)0x40023824)
#define RCC_AHB1ENR             *((volatile u32*)0x40023830)
#define RCC_AHB2ENR             *((volatile u32*)0x40023834)
#define RCC_APB1ENR             *((volatile u32*)0x40023840)
#define RCC_APB2ENR             *((volatile u32*)0x40023844)
#define RCC_AHB1LPENR           *((volatile u32*)0x40023850)
#define RCC_AHB2LPENR           *((volatile u32*)0x40023854)
#define RCC_APB1LPENR           *((volatile u32*)0x40023860)
#define RCC_APB2LPENR           *((volatile u32*)0x40023864)
#define RCC_BDCR                *((volatile u32*)0x40023870)
#define RCC_CSR                 *((volatile u32*)0x40023874)
#define RCC_SSCGR               *((volatile u32*)0x40023880)
#define RCC_PLLI2SCFGR          *((volatile u32*)0x40023884)
#define RCC_DCKCFGR             *((volatile u32*)0x4002388C)
*/

/*-------------------------------------------------------------*/
/*---------------------------Clocks----------------------------*/
/*-------------------------------------------------------------*/


#define RCC_HSI							0
#define RCC_HSE							1
#define RCC_PLL							2


/*-------------------------------------------------------------*/
/*----------------------------Buses----------------------------*/
/*-------------------------------------------------------------*/

#define AHB1            	            0
#define AHB2        	                1
#define APB1    	                    2
#define APB2	                        3

/*-------------------------------------------------------------*/
/*--------------------Peripherals of AHB1----------------------*/
/*-------------------------------------------------------------*/

#define GPIOA_RCC                       0
#define GPIOB_RCC                       1
#define GPIOC_RCC                       2
#define GPIOD_RCC                       3
#define GPIOE_RCC                       4
#define GPIOH_RCC                       7
#define CRC_RCC                         12
#define DMA1_RCC                        21
#define DMA2_RCC                        22


/*-------------------------------------------------------------*/
/*--------------------Peripherals of AHB2----------------------*/
/*-------------------------------------------------------------*/

#define OTGFS_RCC						 7



/*-------------------------------------------------------------*/
/*--------------------Peripherals of APB1----------------------*/
/*-------------------------------------------------------------*/

#define TIM2_RCC                        0
#define TIM3_RCC                        1
#define TIM4_RCC                        2
#define TIM5_RCC                        3
#define WWDG_RCC                        11
#define SPI2_RCC                        14
#define SPI3_RCC                        15
#define USART2_RCC                      17
#define I2C1_RCC                        21
#define I2C2_RCC                        22
#define I2C3_RCC                        23
#define PWR_RCC                         28

/*-------------------------------------------------------------*/
/*--------------------Peripherals of APB2----------------------*/
/*-------------------------------------------------------------*/

#define TIM1_RCC                        0
#define USART1_RCC                      4
#define USART6_RCC                      5
#define ADC1_RCC                        8
#define SDIO_RCC                        11
#define SPI1_RCC                        12
#define SPI4_RCC                        13
#define SYSCFG_RCC                      14
#define TIM9_RCC                        16
#define TIM10_RCC                       17
#define TIM11_RCC                       18




/*-------------------------------------------------------------*/
/*----------------------------Masks----------------------------*/
/*-------------------------------------------------------------*/

/*----------------------------Pin Masks------------------------*/
#define MASK_PIN_0                      0x00000001
#define MASK_PIN_1                      0x00000002
#define MASK_PIN_2                      0x00000004
#define MASK_PIN_3                      0x00000008

#define MASK_PIN_4                      0x00000010
#define MASK_PIN_5                      0x00000020
#define MASK_PIN_6                      0x00000040
#define MASK_PIN_7                      0x00000080

#define MASK_PIN_8                      0x00000100
#define MASK_PIN_9                      0x00000200
#define MASK_PIN_10                     0x00000400
#define MASK_PIN_11                     0x00000800

#define MASK_PIN_12                     0x00001000
#define MASK_PIN_13                     0x00002000
#define MASK_PIN_14                     0x00004000
#define MASK_PIN_15                     0x00008000

#define MASK_PIN_16                     0x00010000
#define MASK_PIN_17                     0x00020000
#define MASK_PIN_18                     0x00040000
#define MASK_PIN_19                     0x00080000

#define MASK_PIN_20                     0x00100000
#define MASK_PIN_21                     0x00200000
#define MASK_PIN_22                     0x00400000
#define MASK_PIN_23                     0x00800000

#define MASK_PIN_24                     0x01000000
#define MASK_PIN_25                     0x02000000
#define MASK_PIN_26                     0x04000000
#define MASK_PIN_27                     0x08000000

#define MASK_PIN_28                     0x10000000
#define MASK_PIN_29                     0x20000000
#define MASK_PIN_30                     0x40000000
#define MASK_PIN_31                     0x80000000

/*-------------------------------CR----------------------------*/
/*----------------------------Set Clock------------------------*/
#define MASK_GET_SYSCLK          		0x0000000C
#define MASK_SET_CR_HSI             	0x00000001
#define MASK_SET_CR_HSE             	0x00010000
#define MASK_SET_CR_PLL             	0x01000000

/*----------------------------Get Ready------------------------*/
#define MASK_GET_RDY_HSI         		0x00000002
#define MASK_GET_RDY_HSE         		0x00020000
#define MASK_GET_RDY_PLL         		0x02000000

/*----------------------------PLLCFGR---------------------------*/
/*----------------------------PLL Config-----------------------*/
#define MASK_SET_PPL_M           0x0000003F
#define MASK_SET_PPL_N           0x00007FC0
#define MASK_SET_PPL_P           0x00030000
#define MASK_SET_PPL_Q           0x0F000000
#define MASK_SET_PPL_SRC         0x00400000

#define  MASK_SW                 0x00000003
#define  MASK_GET_SWS            0x0000000C

#define MASK_SWS_HSI 			 0x00000000
#define MASK_SWS_HSE 			 0x00000004
#define MASK_SWS_PLL 			 0x00000008



#define SHIFT_PLL_M              0
#define SHIFT_PLL_N              6
#define SHIFT_PLL_P              16
#define SHIFT_PLL_Q              24
#define SHIFT_PLL_SRC            22


#define MASK_SET_PRE_AHB         0x000000F0
#define MASK_SET_PRE_APB1        0x00001C00
#define MASK_SET_PRE_APB2        0x0000E000

#define SHIFT_AHB                4
#define SHIFT_APB1               10
#define SHIFT_APB2               13

/* ---------------------- AHB Prescalers --------------------- */
#define AHB_NO_CLOCK_FACTOR                           0b0000
#define AHB_CLOCK_DIVIDED_BY_2                        0b1000
#define AHB_CLOCK_DIVIDED_BY_4                        0b1001
#define AHB_CLOCK_DIVIDED_BY_8                        0b1010
#define AHB_CLOCK_DIVIDED_BY_16                       0b1011
#define AHB_CLOCK_DIVIDED_BY_64                       0b1100
#define AHB_CLOCK_DIVIDED_BY_128                      0b1101
#define AHB_CLOCK_DIVIDED_BY_256                      0b1110
#define AHB_CLOCK_DIVIDED_BY_512                      0b1111


/* --------------------- APB1 Prescalers --------------------- */
#define APB1_NO_CLOCK_FACTOR                           0b000
#define APB1_CLOCK_DIVIDED_BY_2                        0b100
#define APB1_CLOCK_DIVIDED_BY_4                        0b101
#define APB1_CLOCK_DIVIDED_BY_8                        0b110
#define APB1_CLOCK_DIVIDED_BY_16                       0b111

/* --------------------- APB2 Prescaler ---------------------- */
#define APB2_NO_CLOCK_FACTOR                           0b000
#define APB2_CLOCK_DIVIDED_BY_2                        0b100
#define APB2_CLOCK_DIVIDED_BY_4                        0b101
#define APB2_CLOCK_DIVIDED_BY_8                        0b110
#define APB2_CLOCK_DIVIDED_BY_16                       0b111


/*-----------------------------CFGR----------------------------*/

typedef enum {
  RCC_enuOK,
  RCC_enuNotOK
}RCC_enuErrorStatus;


typedef enum{
  HSI,
  HSE
}RCC_enuPLLSRC;

typedef struct{
  RCC_enuPLLSRC   RCC_enuPLLSCR;
  u32             RCC_enuPLL_M;
  u32             RCC_enuPLL_N;
  u32             RCC_enuPLL_P;
  u32             RCC_enuPLL_Q;
}RCC_structCLKPLL;


typedef enum{
  OFF,
  ON
}RCC_enuClkStatus;

typedef enum{
  Not_Ready,
  Ready
}RCC_enuReadyStatus;

typedef enum {
  RCC_ClockStatus_enuHSI,
  RCC_ClockStatus_enuHSE,
  RCC_ClockStatus_enuPLL,
  RCC_ClockStatus_enuNotApplicable
}RCC_enuClockStatus;




/*---------------------------------------------------------------------------------*/
/*-----------------------RCC_enuSelectClk------------------------------------------*/
/*@description :  select the clock of the system-----------------------------------*/
/*@param       :  Copy_enuClk (RCC_CLK)   : RCC_HSI, RCC_HSE, RCC_PLL--------------*/
/*@return      :  error, choosing a wrong clock, or the clock isn't ready or on ,--*/
/*                 or failed to set the clock as a system clock -------------------*/
/*---------------------------------------------------------------------------------*/


RCC_enuErrorStatus  RCC_enuSelectClk             (u8 Copy_u8ClockSystem);

/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuControlClk ----------------------------------- */
/* @description : control the clock on/off -------------------------------------------- */
/* @param       :        Copy_enuClk (RCC_CLK)               : RCC_HSI, RCC_HSE, RCC_PLL*/
/*                       Copy_enuClkStatus (RCC_enuClkStatus): ON, OFF                  */
/* @return      :  error, choosing a wrong clock, or the clock isn't ready or on ,      */
/*                 or failed to set the clock as a system clock ----------------------- */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuControlClk(u8 Copy_u8ClockSystem,RCC_enuClkStatus Copy_enuClkStatus);

/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuConfigPLL ------------------------------------ */
/* @description : Configure the PLL configuration parameters -------------------------- */
/* @param       : RCC_enuPLLSCR : HSI, HSE.                                             */
/*                RCC_enuPLL_M : 2 : 63                                                 */
/*                RCC_enuPLL_N : 2 : 511                                                */
/*                RCC_enuPLL_P : 2,4,6,8                                                */
/*                RCC_enuPLL_Q : 2 : 15                                                 */
/* @return      :  error, choosing a wrong clock, or the clock isn't ready or on ,      */
/*                 or failed to set the clock as a system clock ----------------------- */
/* ------------------------------------------------------------------------------------ */
//RCC_enuErrorStatus  RCC_enuConfigPLL(RCC_structCLKPLL Copy_structPLLConfig);

RCC_enuErrorStatus  RCC_enuConfigurationPLL(RCC_enuPLLSRC Copy_enuPLLSRC, u32 Copy_enuPLL_M, u32 Copy_enuPLL_N, u32 Copy_enuPLL_P, u32 Copy_enuPLL_Q);



/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuControlPrescalerAHB -------------------------- */
/* @description : Configure the AHB prescaler ----------------------------------------- */
/* @param       : Copy_u32AHBPrescaler (u32)  : 0,2,4,8,16,64,128,256,512               */
/* @return      : error, you have a wrong choice                                        */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuControlPrescalerAHB(u32 Copy_u32AHBPrescaler);


/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuControlPrescalerAPB1 ------------------------- */
/* @description : Configure the APB1 prescaler ---------------------------------------- */
/* @param       : Copy_u32APB1Prescaler (u32)  : 0,2,4,8,16                             */
/* @return      : error, you have a wrong choice                                        */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuControlPrescalerAPB1(u32 Copy_u32APB1Prescaler);

/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuControlPrescalerAPB2 ------------------------- */
/* @description : Configure the APB2 prescaler ---------------------------------------- */
/* @param       : Copy_u32APB2Prescaler (u32)  : 0,2,4,8,16                             */
/* @return      : error, you have a wrong choice                                        */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuControlPrescalerAPB2(u32 Copy_u32APB2Prescaler);


/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuEnablePeripheral ----------------------------- */
/* @description : Enable the peripheral on the selected bridge ------------------------ */
/* @param       : Copy_u32PeripheralBus (u32)  : AHB1_BUS, AHB2_BUS, APB1_BUS, APB2_BUS */
/*              : Copy_u32Peripheral (u32)                                              */
/* @return      : error, you have a wrong choice of the bus                             */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuEnablePeripheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral);


/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuDisablePeripheral ---------------------------- */
/* @description : Disable the peripheral on the selected bridge ----------------------- */
/* @param       : Copy_u32PeripheralBus (u32)  : AHB1_BUS, AHB2_BUS, APB1_BUS, APB2_BUS */
/*              : Copy_u32Peripheral (u32)                                              */
/* @return      : error, you have a wrong choice of the bus                             */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuDisablePeripheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral);

#endif
