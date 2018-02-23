/*******************************************************************************
* File Name: CHG_DUTY_ISR.h
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
#if !defined(CY_ISR_CHG_DUTY_ISR_H)
#define CY_ISR_CHG_DUTY_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CHG_DUTY_ISR_Start(void);
void CHG_DUTY_ISR_StartEx(cyisraddress address);
void CHG_DUTY_ISR_Stop(void);

CY_ISR_PROTO(CHG_DUTY_ISR_Interrupt);

void CHG_DUTY_ISR_SetVector(cyisraddress address);
cyisraddress CHG_DUTY_ISR_GetVector(void);

void CHG_DUTY_ISR_SetPriority(uint8 priority);
uint8 CHG_DUTY_ISR_GetPriority(void);

void CHG_DUTY_ISR_Enable(void);
uint8 CHG_DUTY_ISR_GetState(void);
void CHG_DUTY_ISR_Disable(void);

void CHG_DUTY_ISR_SetPending(void);
void CHG_DUTY_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CHG_DUTY_ISR ISR. */
#define CHG_DUTY_ISR_INTC_VECTOR            ((reg32 *) CHG_DUTY_ISR__INTC_VECT)

/* Address of the CHG_DUTY_ISR ISR priority. */
#define CHG_DUTY_ISR_INTC_PRIOR             ((reg8 *) CHG_DUTY_ISR__INTC_PRIOR_REG)

/* Priority of the CHG_DUTY_ISR interrupt. */
#define CHG_DUTY_ISR_INTC_PRIOR_NUMBER      CHG_DUTY_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CHG_DUTY_ISR interrupt. */
#define CHG_DUTY_ISR_INTC_SET_EN            ((reg32 *) CHG_DUTY_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CHG_DUTY_ISR interrupt. */
#define CHG_DUTY_ISR_INTC_CLR_EN            ((reg32 *) CHG_DUTY_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CHG_DUTY_ISR interrupt state to pending. */
#define CHG_DUTY_ISR_INTC_SET_PD            ((reg32 *) CHG_DUTY_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CHG_DUTY_ISR interrupt. */
#define CHG_DUTY_ISR_INTC_CLR_PD            ((reg32 *) CHG_DUTY_ISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_CHG_DUTY_ISR_H */


/* [] END OF FILE */
