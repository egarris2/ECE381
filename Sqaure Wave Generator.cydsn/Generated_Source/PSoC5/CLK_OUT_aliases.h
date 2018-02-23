/*******************************************************************************
* File Name: CLK_OUT.h  
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

#if !defined(CY_PINS_CLK_OUT_ALIASES_H) /* Pins CLK_OUT_ALIASES_H */
#define CY_PINS_CLK_OUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define CLK_OUT_0			(CLK_OUT__0__PC)
#define CLK_OUT_0_INTR	((uint16)((uint16)0x0001u << CLK_OUT__0__SHIFT))

#define CLK_OUT_INTR_ALL	 ((uint16)(CLK_OUT_0_INTR))

#endif /* End Pins CLK_OUT_ALIASES_H */


/* [] END OF FILE */
