/*******************************************************************************
* File Name: CHG_DUTY.h  
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

#if !defined(CY_PINS_CHG_DUTY_H) /* Pins CHG_DUTY_H */
#define CY_PINS_CHG_DUTY_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CHG_DUTY_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CHG_DUTY__PORT == 15 && ((CHG_DUTY__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CHG_DUTY_Write(uint8 value);
void    CHG_DUTY_SetDriveMode(uint8 mode);
uint8   CHG_DUTY_ReadDataReg(void);
uint8   CHG_DUTY_Read(void);
void    CHG_DUTY_SetInterruptMode(uint16 position, uint16 mode);
uint8   CHG_DUTY_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CHG_DUTY_SetDriveMode() function.
     *  @{
     */
        #define CHG_DUTY_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CHG_DUTY_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CHG_DUTY_DM_RES_UP          PIN_DM_RES_UP
        #define CHG_DUTY_DM_RES_DWN         PIN_DM_RES_DWN
        #define CHG_DUTY_DM_OD_LO           PIN_DM_OD_LO
        #define CHG_DUTY_DM_OD_HI           PIN_DM_OD_HI
        #define CHG_DUTY_DM_STRONG          PIN_DM_STRONG
        #define CHG_DUTY_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CHG_DUTY_MASK               CHG_DUTY__MASK
#define CHG_DUTY_SHIFT              CHG_DUTY__SHIFT
#define CHG_DUTY_WIDTH              1u

/* Interrupt constants */
#if defined(CHG_DUTY__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CHG_DUTY_SetInterruptMode() function.
     *  @{
     */
        #define CHG_DUTY_INTR_NONE      (uint16)(0x0000u)
        #define CHG_DUTY_INTR_RISING    (uint16)(0x0001u)
        #define CHG_DUTY_INTR_FALLING   (uint16)(0x0002u)
        #define CHG_DUTY_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CHG_DUTY_INTR_MASK      (0x01u) 
#endif /* (CHG_DUTY__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CHG_DUTY_PS                     (* (reg8 *) CHG_DUTY__PS)
/* Data Register */
#define CHG_DUTY_DR                     (* (reg8 *) CHG_DUTY__DR)
/* Port Number */
#define CHG_DUTY_PRT_NUM                (* (reg8 *) CHG_DUTY__PRT) 
/* Connect to Analog Globals */                                                  
#define CHG_DUTY_AG                     (* (reg8 *) CHG_DUTY__AG)                       
/* Analog MUX bux enable */
#define CHG_DUTY_AMUX                   (* (reg8 *) CHG_DUTY__AMUX) 
/* Bidirectional Enable */                                                        
#define CHG_DUTY_BIE                    (* (reg8 *) CHG_DUTY__BIE)
/* Bit-mask for Aliased Register Access */
#define CHG_DUTY_BIT_MASK               (* (reg8 *) CHG_DUTY__BIT_MASK)
/* Bypass Enable */
#define CHG_DUTY_BYP                    (* (reg8 *) CHG_DUTY__BYP)
/* Port wide control signals */                                                   
#define CHG_DUTY_CTL                    (* (reg8 *) CHG_DUTY__CTL)
/* Drive Modes */
#define CHG_DUTY_DM0                    (* (reg8 *) CHG_DUTY__DM0) 
#define CHG_DUTY_DM1                    (* (reg8 *) CHG_DUTY__DM1)
#define CHG_DUTY_DM2                    (* (reg8 *) CHG_DUTY__DM2) 
/* Input Buffer Disable Override */
#define CHG_DUTY_INP_DIS                (* (reg8 *) CHG_DUTY__INP_DIS)
/* LCD Common or Segment Drive */
#define CHG_DUTY_LCD_COM_SEG            (* (reg8 *) CHG_DUTY__LCD_COM_SEG)
/* Enable Segment LCD */
#define CHG_DUTY_LCD_EN                 (* (reg8 *) CHG_DUTY__LCD_EN)
/* Slew Rate Control */
#define CHG_DUTY_SLW                    (* (reg8 *) CHG_DUTY__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CHG_DUTY_PRTDSI__CAPS_SEL       (* (reg8 *) CHG_DUTY__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CHG_DUTY_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CHG_DUTY__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CHG_DUTY_PRTDSI__OE_SEL0        (* (reg8 *) CHG_DUTY__PRTDSI__OE_SEL0) 
#define CHG_DUTY_PRTDSI__OE_SEL1        (* (reg8 *) CHG_DUTY__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CHG_DUTY_PRTDSI__OUT_SEL0       (* (reg8 *) CHG_DUTY__PRTDSI__OUT_SEL0) 
#define CHG_DUTY_PRTDSI__OUT_SEL1       (* (reg8 *) CHG_DUTY__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CHG_DUTY_PRTDSI__SYNC_OUT       (* (reg8 *) CHG_DUTY__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CHG_DUTY__SIO_CFG)
    #define CHG_DUTY_SIO_HYST_EN        (* (reg8 *) CHG_DUTY__SIO_HYST_EN)
    #define CHG_DUTY_SIO_REG_HIFREQ     (* (reg8 *) CHG_DUTY__SIO_REG_HIFREQ)
    #define CHG_DUTY_SIO_CFG            (* (reg8 *) CHG_DUTY__SIO_CFG)
    #define CHG_DUTY_SIO_DIFF           (* (reg8 *) CHG_DUTY__SIO_DIFF)
#endif /* (CHG_DUTY__SIO_CFG) */

/* Interrupt Registers */
#if defined(CHG_DUTY__INTSTAT)
    #define CHG_DUTY_INTSTAT            (* (reg8 *) CHG_DUTY__INTSTAT)
    #define CHG_DUTY_SNAP               (* (reg8 *) CHG_DUTY__SNAP)
    
	#define CHG_DUTY_0_INTTYPE_REG 		(* (reg8 *) CHG_DUTY__0__INTTYPE)
#endif /* (CHG_DUTY__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CHG_DUTY_H */


/* [] END OF FILE */
