/*******************************************************************************
* File Name: CLR_STR_ISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_CLR_STR_ISR_H)
#define CY_ISR_CLR_STR_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CLR_STR_ISR_Start(void);
void CLR_STR_ISR_StartEx(cyisraddress address);
void CLR_STR_ISR_Stop(void);

CY_ISR_PROTO(CLR_STR_ISR_Interrupt);

void CLR_STR_ISR_SetVector(cyisraddress address);
cyisraddress CLR_STR_ISR_GetVector(void);

void CLR_STR_ISR_SetPriority(uint8 priority);
uint8 CLR_STR_ISR_GetPriority(void);

void CLR_STR_ISR_Enable(void);
uint8 CLR_STR_ISR_GetState(void);
void CLR_STR_ISR_Disable(void);

void CLR_STR_ISR_SetPending(void);
void CLR_STR_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CLR_STR_ISR ISR. */
#define CLR_STR_ISR_INTC_VECTOR            ((reg32 *) CLR_STR_ISR__INTC_VECT)

/* Address of the CLR_STR_ISR ISR priority. */
#define CLR_STR_ISR_INTC_PRIOR             ((reg8 *) CLR_STR_ISR__INTC_PRIOR_REG)

/* Priority of the CLR_STR_ISR interrupt. */
#define CLR_STR_ISR_INTC_PRIOR_NUMBER      CLR_STR_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CLR_STR_ISR interrupt. */
#define CLR_STR_ISR_INTC_SET_EN            ((reg32 *) CLR_STR_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CLR_STR_ISR interrupt. */
#define CLR_STR_ISR_INTC_CLR_EN            ((reg32 *) CLR_STR_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CLR_STR_ISR interrupt state to pending. */
#define CLR_STR_ISR_INTC_SET_PD            ((reg32 *) CLR_STR_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CLR_STR_ISR interrupt. */
#define CLR_STR_ISR_INTC_CLR_PD            ((reg32 *) CLR_STR_ISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_CLR_STR_ISR_H */


/* [] END OF FILE */
