/*******************************************************************************
* File Name: CNTR.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CNTR_ALIASES_H) /* Pins CNTR_ALIASES_H */
#define CY_PINS_CNTR_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define CNTR_0			(CNTR__0__PC)
#define CNTR_0_INTR	((uint16)((uint16)0x0001u << CNTR__0__SHIFT))

#define CNTR_1			(CNTR__1__PC)
#define CNTR_1_INTR	((uint16)((uint16)0x0001u << CNTR__1__SHIFT))

#define CNTR_2			(CNTR__2__PC)
#define CNTR_2_INTR	((uint16)((uint16)0x0001u << CNTR__2__SHIFT))

#define CNTR_3			(CNTR__3__PC)
#define CNTR_3_INTR	((uint16)((uint16)0x0001u << CNTR__3__SHIFT))

#define CNTR_4			(CNTR__4__PC)
#define CNTR_4_INTR	((uint16)((uint16)0x0001u << CNTR__4__SHIFT))

#define CNTR_5			(CNTR__5__PC)
#define CNTR_5_INTR	((uint16)((uint16)0x0001u << CNTR__5__SHIFT))

#define CNTR_6			(CNTR__6__PC)
#define CNTR_6_INTR	((uint16)((uint16)0x0001u << CNTR__6__SHIFT))

#define CNTR_7			(CNTR__7__PC)
#define CNTR_7_INTR	((uint16)((uint16)0x0001u << CNTR__7__SHIFT))

#define CNTR_INTR_ALL	 ((uint16)(CNTR_0_INTR| CNTR_1_INTR| CNTR_2_INTR| CNTR_3_INTR| CNTR_4_INTR| CNTR_5_INTR| CNTR_6_INTR| CNTR_7_INTR))

#endif /* End Pins CNTR_ALIASES_H */


/* [] END OF FILE */
