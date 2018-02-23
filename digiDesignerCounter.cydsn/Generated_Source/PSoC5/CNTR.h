/*******************************************************************************
* File Name: CNTR.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CNTR_H) /* Pins CNTR_H */
#define CY_PINS_CNTR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CNTR_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CNTR__PORT == 15 && ((CNTR__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CNTR_Write(uint8 value);
void    CNTR_SetDriveMode(uint8 mode);
uint8   CNTR_ReadDataReg(void);
uint8   CNTR_Read(void);
void    CNTR_SetInterruptMode(uint16 position, uint16 mode);
uint8   CNTR_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CNTR_SetDriveMode() function.
     *  @{
     */
        #define CNTR_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CNTR_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CNTR_DM_RES_UP          PIN_DM_RES_UP
        #define CNTR_DM_RES_DWN         PIN_DM_RES_DWN
        #define CNTR_DM_OD_LO           PIN_DM_OD_LO
        #define CNTR_DM_OD_HI           PIN_DM_OD_HI
        #define CNTR_DM_STRONG          PIN_DM_STRONG
        #define CNTR_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CNTR_MASK               CNTR__MASK
#define CNTR_SHIFT              CNTR__SHIFT
#define CNTR_WIDTH              8u

/* Interrupt constants */
#if defined(CNTR__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CNTR_SetInterruptMode() function.
     *  @{
     */
        #define CNTR_INTR_NONE      (uint16)(0x0000u)
        #define CNTR_INTR_RISING    (uint16)(0x0001u)
        #define CNTR_INTR_FALLING   (uint16)(0x0002u)
        #define CNTR_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CNTR_INTR_MASK      (0x01u) 
#endif /* (CNTR__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CNTR_PS                     (* (reg8 *) CNTR__PS)
/* Data Register */
#define CNTR_DR                     (* (reg8 *) CNTR__DR)
/* Port Number */
#define CNTR_PRT_NUM                (* (reg8 *) CNTR__PRT) 
/* Connect to Analog Globals */                                                  
#define CNTR_AG                     (* (reg8 *) CNTR__AG)                       
/* Analog MUX bux enable */
#define CNTR_AMUX                   (* (reg8 *) CNTR__AMUX) 
/* Bidirectional Enable */                                                        
#define CNTR_BIE                    (* (reg8 *) CNTR__BIE)
/* Bit-mask for Aliased Register Access */
#define CNTR_BIT_MASK               (* (reg8 *) CNTR__BIT_MASK)
/* Bypass Enable */
#define CNTR_BYP                    (* (reg8 *) CNTR__BYP)
/* Port wide control signals */                                                   
#define CNTR_CTL                    (* (reg8 *) CNTR__CTL)
/* Drive Modes */
#define CNTR_DM0                    (* (reg8 *) CNTR__DM0) 
#define CNTR_DM1                    (* (reg8 *) CNTR__DM1)
#define CNTR_DM2                    (* (reg8 *) CNTR__DM2) 
/* Input Buffer Disable Override */
#define CNTR_INP_DIS                (* (reg8 *) CNTR__INP_DIS)
/* LCD Common or Segment Drive */
#define CNTR_LCD_COM_SEG            (* (reg8 *) CNTR__LCD_COM_SEG)
/* Enable Segment LCD */
#define CNTR_LCD_EN                 (* (reg8 *) CNTR__LCD_EN)
/* Slew Rate Control */
#define CNTR_SLW                    (* (reg8 *) CNTR__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CNTR_PRTDSI__CAPS_SEL       (* (reg8 *) CNTR__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CNTR_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CNTR__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CNTR_PRTDSI__OE_SEL0        (* (reg8 *) CNTR__PRTDSI__OE_SEL0) 
#define CNTR_PRTDSI__OE_SEL1        (* (reg8 *) CNTR__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CNTR_PRTDSI__OUT_SEL0       (* (reg8 *) CNTR__PRTDSI__OUT_SEL0) 
#define CNTR_PRTDSI__OUT_SEL1       (* (reg8 *) CNTR__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CNTR_PRTDSI__SYNC_OUT       (* (reg8 *) CNTR__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CNTR__SIO_CFG)
    #define CNTR_SIO_HYST_EN        (* (reg8 *) CNTR__SIO_HYST_EN)
    #define CNTR_SIO_REG_HIFREQ     (* (reg8 *) CNTR__SIO_REG_HIFREQ)
    #define CNTR_SIO_CFG            (* (reg8 *) CNTR__SIO_CFG)
    #define CNTR_SIO_DIFF           (* (reg8 *) CNTR__SIO_DIFF)
#endif /* (CNTR__SIO_CFG) */

/* Interrupt Registers */
#if defined(CNTR__INTSTAT)
    #define CNTR_INTSTAT            (* (reg8 *) CNTR__INTSTAT)
    #define CNTR_SNAP               (* (reg8 *) CNTR__SNAP)
    
	#define CNTR_0_INTTYPE_REG 		(* (reg8 *) CNTR__0__INTTYPE)
	#define CNTR_1_INTTYPE_REG 		(* (reg8 *) CNTR__1__INTTYPE)
	#define CNTR_2_INTTYPE_REG 		(* (reg8 *) CNTR__2__INTTYPE)
	#define CNTR_3_INTTYPE_REG 		(* (reg8 *) CNTR__3__INTTYPE)
	#define CNTR_4_INTTYPE_REG 		(* (reg8 *) CNTR__4__INTTYPE)
	#define CNTR_5_INTTYPE_REG 		(* (reg8 *) CNTR__5__INTTYPE)
	#define CNTR_6_INTTYPE_REG 		(* (reg8 *) CNTR__6__INTTYPE)
	#define CNTR_7_INTTYPE_REG 		(* (reg8 *) CNTR__7__INTTYPE)
#endif /* (CNTR__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CNTR_H */


/* [] END OF FILE */
