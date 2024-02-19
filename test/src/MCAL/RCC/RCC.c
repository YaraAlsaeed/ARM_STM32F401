#include "RCC.h"


/*---------------------------------------------------------------------------------*/
/*-----------------------RCC_enuSelectClk------------------------------------------*/
/*@description :  select the clock of the system-----------------------------------*/
/*@param       :  Copy_enuClk (RCC_CLK)   : RCC_HSI, RCC_HSE, RCC_PLL--------------*/
/*@return      :  error, choosing a wrong clock, or the clock isn't ready or on ,--*/
/*                 or failed to set the clock as a system clock -------------------*/
/*---------------------------------------------------------------------------------*/


RCC_enuErrorStatus   RCC_enuSelectClk(u8 Copy_u8ClockSystem)
{
	RCC_enuErrorStatus ErrorStatus;
	ErrorStatus = RCC_enuOK;
	u32 Loc_u32CFGR_Register;
	u32 Loc_u32TimeOut = 0;

	//check clock
	if (Copy_u8ClockSystem >= RCC_HSI && Copy_u8ClockSystem <= RCC_PLL)
	{
		switch(Copy_u8ClockSystem)
		{
		case RCC_HSI:
			//check if on
			if((RCC->RCC_CR & MASK_SET_CR_HSI)==MASK_SET_CR_HSI)
			{
				//check if ready
				if ((RCC->RCC_CR & MASK_GET_RDY_HSI)==MASK_GET_RDY_HSI)
				{
					//set SW
					Loc_u32CFGR_Register = RCC->RCC_CFGR;
					Loc_u32CFGR_Register &= ~MASK_SW;
					Loc_u32CFGR_Register |= RCC_HSI;
					RCC->RCC_CFGR = Loc_u32CFGR_Register;

					while( ((RCC->RCC_CFGR & MASK_GET_SWS) != MASK_SWS_HSI) && (Loc_u32TimeOut<100000))
					{
						Loc_u32TimeOut++;
					}
					if(Loc_u32TimeOut >= 100000)
					{
						//timeout
						ErrorStatus = RCC_enuNotOK;
					}
				}
				else
				{
					ErrorStatus = RCC_enuNotOK;
				}
			}
			else
			{
				ErrorStatus = RCC_enuNotOK;
			}
		break;

		case RCC_HSE:
			//check if on
			if((RCC->RCC_CR & MASK_SET_CR_HSE)==MASK_SET_CR_HSE)
						{
							//check if ready
							if ((RCC->RCC_CR & MASK_GET_RDY_HSE)==MASK_GET_RDY_HSE)
							{
								//set SW
								Loc_u32CFGR_Register = RCC->RCC_CFGR;
								Loc_u32CFGR_Register &= ~MASK_SW;
								Loc_u32CFGR_Register |= RCC_HSE;
								RCC->RCC_CFGR = Loc_u32CFGR_Register;

								while(((RCC->RCC_CFGR & MASK_GET_SWS) != MASK_SWS_HSE) && (Loc_u32TimeOut<100000))
								{
									Loc_u32TimeOut++;
								}

								if(Loc_u32TimeOut >= 100000)
								{
									//timeout
									ErrorStatus = RCC_enuNotOK;
								}
							}
							//not ready
							else
							{
								ErrorStatus = RCC_enuNotOK;
							}
						}
						//off
						else
						{
							ErrorStatus = RCC_enuNotOK;
						}
					break;

		case RCC_PLL:
			//check if on
						if((RCC->RCC_CR & MASK_SET_CR_PLL)==MASK_SET_CR_PLL)
									{
										//check if ready
										if ((RCC->RCC_CR & MASK_GET_RDY_PLL)==MASK_GET_RDY_PLL)
										{
											//set SW
											Loc_u32CFGR_Register = RCC->RCC_CFGR;
											Loc_u32CFGR_Register &= ~MASK_SW;
											Loc_u32CFGR_Register |= RCC_PLL;
											RCC->RCC_CFGR = Loc_u32CFGR_Register;

											while(((RCC->RCC_CFGR & MASK_GET_SWS) != MASK_SWS_PLL) && (Loc_u32TimeOut<100000))
											{
												Loc_u32TimeOut++;
											}


											if(Loc_u32TimeOut>=100000)
											{
												ErrorStatus=RCC_enuNotOK;
											}

										}
										//not ready
										else
										{
											ErrorStatus = RCC_enuNotOK;
										}
									}
						//off
									else
									{
										ErrorStatus = RCC_enuNotOK;
									}
								break;

		}
	}

	//wrong clock
	else
	{
		ErrorStatus=RCC_enuNotOK;
	}

	return ErrorStatus;

}



/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuControlClk ----------------------------------- */
/* @description : control the clock on/off -------------------------------------------- */
/* @param       :        Copy_enuClk (RCC_CLK)               : RCC_HSI, RCC_HSE, RCC_PLL*/
/*                       Copy_enuClkStatus (RCC_enuClkStatus): ON, OFF                  */
/* @return      :  error, choosing a wrong clock, or the clock isn't ready or on ,      */
/*                 or failed to set the clock as a system clock ----------------------- */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuControlClk(u8 Copy_u8ClockSystem,RCC_enuClkStatus Copy_enuClkStatus)
{
	u32 Loc_u32SystemClock;
	Loc_u32SystemClock = ((RCC->RCC_CFGR & MASK_GET_SWS)>>2);
	RCC_enuErrorStatus ErrorStatus;
	ErrorStatus = RCC_enuOK;
	u32 Loc_TimeOut;
	Loc_TimeOut = 0;

	//check if desired clock system is already set
	if(Loc_u32SystemClock == Copy_enuClkStatus)
	{
		ErrorStatus = RCC_enuNotOK;
	}

	//check if wrong clock chosen
	else if(!(Copy_u8ClockSystem>=RCC_HSI) && (Copy_u8ClockSystem <= RCC_PLL))
	{
		ErrorStatus = RCC_enuNotOK;
	}

	else
	{
		switch(Copy_u8ClockSystem)
		{
		//control HSI
		case RCC_HSI:
			//off
			if(Copy_enuClkStatus == OFF)
			{
				RCC->RCC_CR &= (~MASK_SET_CR_HSI);
			}
			//on
			else
			{
				RCC->RCC_CR |=MASK_SET_CR_HSI;

				//wait till ready
				while( ((RCC->RCC_CR & MASK_GET_RDY_HSI)== 0) & (Loc_TimeOut<100000))
				{
					Loc_TimeOut++;
				}

				if(Loc_TimeOut>=100000)
				{
					//timeout
					ErrorStatus = RCC_enuNotOK;
				}
			}
			break;

			//control HSE
		case RCC_HSE:
					//off
					if(Copy_enuClkStatus == OFF)
					{
						RCC->RCC_CR &= (~MASK_SET_CR_HSE);
					}
					//on
					else
					{
						RCC->RCC_CR |=MASK_SET_CR_HSE;

						//wait till ready
						while( ((RCC->RCC_CR & MASK_GET_RDY_HSE)== 0) & (Loc_TimeOut<100000))
						{
							Loc_TimeOut++;
						}

						if(Loc_TimeOut>=100000)
						{
							//timeout
							ErrorStatus = RCC_enuNotOK;
						}
					}
			break;
			//control PLL
				case RCC_PLL:
							//off
							if(Copy_enuClkStatus == OFF)
							{
								RCC->RCC_CR &= (~MASK_SET_CR_PLL);
							}
							//on
							else
							{
								RCC->RCC_CR |=MASK_SET_CR_PLL;

								//wait till ready
								while( ((RCC->RCC_CR & MASK_GET_RDY_PLL)== 0) & (Loc_TimeOut<100000))
								{
									Loc_TimeOut++;
								}

								if(Loc_TimeOut>=100000)
								{
									//timeout
									ErrorStatus = RCC_enuNotOK;
								}
							}
					break;

		};
	}


	return ErrorStatus;
}


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
//RCC_enuErrorStatus  RCC_enuConfigPLL(RCC_structCLKPLL Copy_structPLLConfig)


RCC_enuErrorStatus  RCC_enuConfigurationPLL(RCC_enuPLLSRC Copy_enuPLLSRC, u32 Copy_enuPLL_M, u32 Copy_enuPLL_N, u32 Copy_enuPLL_P, u32 Copy_enuPLL_Q)
{
	RCC_enuErrorStatus ErrorStatus;
		ErrorStatus = RCC_enuOK;
		RCC_enuPLLSRC Loc_enuPLLSRC = Copy_enuPLLSRC;
		u32 Loc_u32PLL_M = Copy_enuPLL_M;
		u32 Loc_u32PLL_N = Copy_enuPLL_N;
		u32 Loc_u32PLL_P = Copy_enuPLL_P;
		u32 Loc_u32PLL_Q = Copy_enuPLL_Q;
		u32 Loc_u32PLLCFGR;

		//checking errors of M, N, P, Q and clock source configuration
		/* M CONFIGURATION */
		  if(Loc_u32PLL_M == 0 || Loc_u32PLL_M == 1 || Loc_u32PLL_M > 63)
		  {
		    ErrorStatus = RCC_enuNotOK;
		  }

		  /* N CONFIGURATION */
		  else if(Loc_u32PLL_N == 0 || Loc_u32PLL_N == 1 || Loc_u32PLL_N == 433 || Loc_u32PLL_N >= 511)
		  {
			ErrorStatus = RCC_enuNotOK;
		  }

		  /* P CONFIGURATION */
		  else if((Loc_u32PLL_P != 2) && (Loc_u32PLL_P != 4) && (Loc_u32PLL_P != 6) && (Loc_u32PLL_P != 8))
		  {
			ErrorStatus = RCC_enuNotOK;
		  }

		  /* Q CONFIGURATION */
		  else if(Loc_u32PLL_Q == 0 || Loc_u32PLL_Q == 1 || Loc_u32PLL_Q > 15)
		  {
			ErrorStatus = RCC_enuNotOK;
		  }

		  /* CLOCK SOURCE */
		  else if(Loc_enuPLLSRC>HSE)
		  {
			ErrorStatus = RCC_enuNotOK;
		  }
		  else
		  {
			  //choose clock source
			  Loc_u32PLLCFGR = RCC->RCC_PLLCFGR;
			  Loc_u32PLLCFGR &= ~MASK_SET_PPL_SRC;
			  Loc_u32PLLCFGR |= (Loc_enuPLLSRC<<SHIFT_PLL_SRC);
			  RCC->RCC_PLLCFGR = Loc_u32PLLCFGR;



			  //M CONFIG
			  Loc_u32PLLCFGR = RCC->RCC_PLLCFGR;
			  Loc_u32PLLCFGR &= ~MASK_SET_PPL_M;
			  Loc_u32PLLCFGR |= (Loc_u32PLL_M<<SHIFT_PLL_M);
			  RCC->RCC_PLLCFGR = Loc_u32PLLCFGR;


			  //N CONFIG
 			  Loc_u32PLLCFGR = RCC->RCC_PLLCFGR;
 			  Loc_u32PLLCFGR &= ~MASK_SET_PPL_N;
 			  Loc_u32PLLCFGR |= (Loc_u32PLL_N<<SHIFT_PLL_N);
 			  RCC->RCC_PLLCFGR = Loc_u32PLLCFGR;

			  //P CONFIG
			  Loc_u32PLLCFGR = RCC->RCC_PLLCFGR;
			  Loc_u32PLLCFGR &= ~MASK_SET_PPL_P;
			  Loc_u32PLLCFGR |= (Loc_u32PLL_P<<SHIFT_PLL_P);
			  RCC->RCC_PLLCFGR = Loc_u32PLLCFGR;

			  //Q CONFIG
			  Loc_u32PLLCFGR = RCC->RCC_PLLCFGR;
 			  Loc_u32PLLCFGR &= ~MASK_SET_PPL_Q;
 			  Loc_u32PLLCFGR |= (Loc_u32PLL_Q<<SHIFT_PLL_Q);
 			  RCC->RCC_PLLCFGR = Loc_u32PLLCFGR;
		  }





		return ErrorStatus;
}


/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuControlPrescalerAHB -------------------------- */
/* @description : Configure the AHB prescaler ----------------------------------------- */
/* @param       : Copy_u32AHBPrescaler (u32)  : 0,2,4,8,16,64,128,256,512               */
/* @return      : error, you have a wrong choice                                        */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuControlPrescalerAHB(u32 Copy_u32AHBPrescaler)
{
	RCC_enuErrorStatus ErrorStatus;
	ErrorStatus = RCC_enuOK;
	u32 Loc_u32RCC_CFGR;

	switch(Copy_u32AHBPrescaler)
	{
		//no factor
		case AHB_NO_CLOCK_FACTOR:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_AHB;
			Loc_u32RCC_CFGR |= (AHB_NO_CLOCK_FACTOR<<SHIFT_AHB);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		// divided 2
		case AHB_CLOCK_DIVIDED_BY_2:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_AHB;
			Loc_u32RCC_CFGR |= (AHB_CLOCK_DIVIDED_BY_2<<SHIFT_AHB);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		// divided 4
		case AHB_CLOCK_DIVIDED_BY_4:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_AHB;
			Loc_u32RCC_CFGR |= (AHB_CLOCK_DIVIDED_BY_4<<SHIFT_AHB);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 8
		case AHB_CLOCK_DIVIDED_BY_8:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_AHB;
			Loc_u32RCC_CFGR |= (AHB_CLOCK_DIVIDED_BY_8<<SHIFT_AHB);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 16
		case AHB_CLOCK_DIVIDED_BY_16:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_AHB;
			Loc_u32RCC_CFGR |= (AHB_CLOCK_DIVIDED_BY_16<<SHIFT_AHB);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 64
		case AHB_CLOCK_DIVIDED_BY_64:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_AHB;
			Loc_u32RCC_CFGR |= (AHB_CLOCK_DIVIDED_BY_64<<SHIFT_AHB);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 128
		case AHB_CLOCK_DIVIDED_BY_128:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_AHB;
			Loc_u32RCC_CFGR |= (AHB_CLOCK_DIVIDED_BY_128<<SHIFT_AHB);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 256
		case AHB_CLOCK_DIVIDED_BY_256:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_AHB;
			Loc_u32RCC_CFGR |= (AHB_CLOCK_DIVIDED_BY_256<<SHIFT_AHB);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 512
		case AHB_CLOCK_DIVIDED_BY_512:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_AHB;
			Loc_u32RCC_CFGR |= (AHB_CLOCK_DIVIDED_BY_512<<SHIFT_AHB);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		default:
			ErrorStatus = RCC_enuNotOK;
			break;
	}


	return ErrorStatus;
}


/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuControlPrescalerAPB1 ------------------------- */
/* @description : Configure the APB1 prescaler ---------------------------------------- */
/* @param       : Copy_u32APB1Prescaler (u32)  : 0,2,4,8,16                             */
/* @return      : error, you have a wrong choice                                        */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuControlPrescalerAPB1(u32 Copy_u32APB1Prescaler)
{
	RCC_enuErrorStatus ErrorStatus;
	ErrorStatus = RCC_enuOK;
	u32 Loc_u32RCC_CFGR;

	switch(Copy_u32APB1Prescaler)
	{
		//no factor
		case APB1_NO_CLOCK_FACTOR:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB1;
			Loc_u32RCC_CFGR |= (APB1_NO_CLOCK_FACTOR<<SHIFT_APB1);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 2
		case APB1_CLOCK_DIVIDED_BY_2:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB1;
			Loc_u32RCC_CFGR |= (APB1_CLOCK_DIVIDED_BY_2<<SHIFT_APB1);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 4
		case APB1_CLOCK_DIVIDED_BY_4:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB1;
			Loc_u32RCC_CFGR |= (APB1_CLOCK_DIVIDED_BY_4<<SHIFT_APB1);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 8
		case APB1_CLOCK_DIVIDED_BY_8:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB1;
			Loc_u32RCC_CFGR |= (APB1_CLOCK_DIVIDED_BY_8<<SHIFT_APB1);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;

		//divided 16
		case APB1_CLOCK_DIVIDED_BY_16:
			Loc_u32RCC_CFGR = RCC->RCC_CFGR;
			Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB1;
			Loc_u32RCC_CFGR |= (APB1_CLOCK_DIVIDED_BY_16<<SHIFT_APB1);
			RCC->RCC_CFGR = Loc_u32RCC_CFGR;
			break;
	}

	return ErrorStatus;
}

/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuControlPrescalerAPB2 ------------------------- */
/* @description : Configure the APB2 prescaler ---------------------------------------- */
/* @param       : Copy_u32APB2Prescaler (u32)  : 0,2,4,8,16                             */
/* @return      : error, you have a wrong choice                                        */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuControlPrescalerAPB2(u32 Copy_u32APB2Prescaler)
{
	RCC_enuErrorStatus ErrorStatus;
		ErrorStatus = RCC_enuOK;
		u32 Loc_u32RCC_CFGR;

		switch(Copy_u32APB2Prescaler)
		{
			//no factor
			case APB2_NO_CLOCK_FACTOR:
				Loc_u32RCC_CFGR = RCC->RCC_CFGR;
				Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB2;
				Loc_u32RCC_CFGR |= (APB2_NO_CLOCK_FACTOR<<SHIFT_APB2);
				RCC->RCC_CFGR = Loc_u32RCC_CFGR;
				break;

			//divided 2
			case APB2_CLOCK_DIVIDED_BY_2:
				Loc_u32RCC_CFGR = RCC->RCC_CFGR;
				Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB2;
				Loc_u32RCC_CFGR |= (APB2_CLOCK_DIVIDED_BY_2<<SHIFT_APB2);
				RCC->RCC_CFGR = Loc_u32RCC_CFGR;
				break;

			//divided 4
			case APB2_CLOCK_DIVIDED_BY_4:
				Loc_u32RCC_CFGR = RCC->RCC_CFGR;
				Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB2;
				Loc_u32RCC_CFGR |= (APB2_CLOCK_DIVIDED_BY_4<<SHIFT_APB2);
				RCC->RCC_CFGR = Loc_u32RCC_CFGR;
				break;

			//divided 8
			case APB2_CLOCK_DIVIDED_BY_8:
				Loc_u32RCC_CFGR = RCC->RCC_CFGR;
				Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB2;
				Loc_u32RCC_CFGR |= (APB2_CLOCK_DIVIDED_BY_8<<SHIFT_APB2);
				RCC->RCC_CFGR = Loc_u32RCC_CFGR;
				break;

			//divided 16
			case APB2_CLOCK_DIVIDED_BY_16:
				Loc_u32RCC_CFGR = RCC->RCC_CFGR;
				Loc_u32RCC_CFGR &= ~MASK_SET_PRE_APB2;
				Loc_u32RCC_CFGR |= (APB2_CLOCK_DIVIDED_BY_16<<SHIFT_APB2);
				RCC->RCC_CFGR = Loc_u32RCC_CFGR;
				break;
		}

		return ErrorStatus;
}


/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuEnablePeripheral ----------------------------- */
/* @description : Enable the peripheral on the selected bridge ------------------------ */
/* @param       : Copy_u32PeripheralBus (u32)  : AHB1_BUS, AHB2_BUS, APB1_BUS, APB2_BUS */
/*              : Copy_u32Peripheral (u32)                                              */
/* @return      : error, you have a wrong choice of the bus                             */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuEnablePeripheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral)
{
	RCC_enuErrorStatus ErrorStatus;
	ErrorStatus = RCC_enuOK;

	switch(Copy_u32PeripheralBus)
	{
		//AHB1
		case AHB1:
			RCC->RCC_AHB1ENR |= (1<<Copy_u32Peripheral);
		break;
		//AHB2
		case AHB2:
			RCC->RCC_AHB2ENR |= (1<<Copy_u32Peripheral);
		break;
		//APB1
		case APB1:
			RCC->RCC_APB1ENR |= (1<<Copy_u32Peripheral);
		break;
		//APB2
		case APB2:
			RCC->RCC_APB2ENR |= (1<<Copy_u32Peripheral);
		break;

		default:
			ErrorStatus = RCC_enuNotOK;
		break;
	}

	return ErrorStatus;
}


/* ------------------------------------------------------------------------------------ */
/* ------------------------------ RCC_enuDisablePeripheral ---------------------------- */
/* @description : Disable the peripheral on the selected bridge ----------------------- */
/* @param       : Copy_u32PeripheralBus (u32)  : AHB1_BUS, AHB2_BUS, APB1_BUS, APB2_BUS */
/*              : Copy_u32Peripheral (u32)                                              */
/* @return      : error, you have a wrong choice of the bus                             */
/* ------------------------------------------------------------------------------------ */
RCC_enuErrorStatus  RCC_enuDisablePeripheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral)
{
	RCC_enuErrorStatus ErrorStatus;
		ErrorStatus = RCC_enuOK;

		switch(Copy_u32PeripheralBus)
		{
			//AHB1
			case AHB1:
				RCC->RCC_AHB1ENR &= (~(1<<Copy_u32Peripheral));
			break;
			//AHB2
			case AHB2:
				RCC->RCC_AHB2ENR &= (~(1<<Copy_u32Peripheral));
			break;
			//APB1
			case APB1:
				RCC->RCC_APB1ENR &= (~(1<<Copy_u32Peripheral));
			break;
			//APB2
			case APB2:
				RCC->RCC_APB2ENR &= (~(1<<Copy_u32Peripheral));
			break;

			default:
				ErrorStatus = RCC_enuNotOK;
			break;
		}

		return ErrorStatus;
}
