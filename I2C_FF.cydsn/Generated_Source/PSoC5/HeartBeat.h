/*******************************************************************************
* File Name: HeartBeat.h  
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

#if !defined(CY_PINS_HeartBeat_H) /* Pins HeartBeat_H */
#define CY_PINS_HeartBeat_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HeartBeat_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HeartBeat__PORT == 15 && ((HeartBeat__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HeartBeat_Write(uint8 value);
void    HeartBeat_SetDriveMode(uint8 mode);
uint8   HeartBeat_ReadDataReg(void);
uint8   HeartBeat_Read(void);
void    HeartBeat_SetInterruptMode(uint16 position, uint16 mode);
uint8   HeartBeat_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HeartBeat_SetDriveMode() function.
     *  @{
     */
        #define HeartBeat_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HeartBeat_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HeartBeat_DM_RES_UP          PIN_DM_RES_UP
        #define HeartBeat_DM_RES_DWN         PIN_DM_RES_DWN
        #define HeartBeat_DM_OD_LO           PIN_DM_OD_LO
        #define HeartBeat_DM_OD_HI           PIN_DM_OD_HI
        #define HeartBeat_DM_STRONG          PIN_DM_STRONG
        #define HeartBeat_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HeartBeat_MASK               HeartBeat__MASK
#define HeartBeat_SHIFT              HeartBeat__SHIFT
#define HeartBeat_WIDTH              1u

/* Interrupt constants */
#if defined(HeartBeat__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HeartBeat_SetInterruptMode() function.
     *  @{
     */
        #define HeartBeat_INTR_NONE      (uint16)(0x0000u)
        #define HeartBeat_INTR_RISING    (uint16)(0x0001u)
        #define HeartBeat_INTR_FALLING   (uint16)(0x0002u)
        #define HeartBeat_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HeartBeat_INTR_MASK      (0x01u) 
#endif /* (HeartBeat__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HeartBeat_PS                     (* (reg8 *) HeartBeat__PS)
/* Data Register */
#define HeartBeat_DR                     (* (reg8 *) HeartBeat__DR)
/* Port Number */
#define HeartBeat_PRT_NUM                (* (reg8 *) HeartBeat__PRT) 
/* Connect to Analog Globals */                                                  
#define HeartBeat_AG                     (* (reg8 *) HeartBeat__AG)                       
/* Analog MUX bux enable */
#define HeartBeat_AMUX                   (* (reg8 *) HeartBeat__AMUX) 
/* Bidirectional Enable */                                                        
#define HeartBeat_BIE                    (* (reg8 *) HeartBeat__BIE)
/* Bit-mask for Aliased Register Access */
#define HeartBeat_BIT_MASK               (* (reg8 *) HeartBeat__BIT_MASK)
/* Bypass Enable */
#define HeartBeat_BYP                    (* (reg8 *) HeartBeat__BYP)
/* Port wide control signals */                                                   
#define HeartBeat_CTL                    (* (reg8 *) HeartBeat__CTL)
/* Drive Modes */
#define HeartBeat_DM0                    (* (reg8 *) HeartBeat__DM0) 
#define HeartBeat_DM1                    (* (reg8 *) HeartBeat__DM1)
#define HeartBeat_DM2                    (* (reg8 *) HeartBeat__DM2) 
/* Input Buffer Disable Override */
#define HeartBeat_INP_DIS                (* (reg8 *) HeartBeat__INP_DIS)
/* LCD Common or Segment Drive */
#define HeartBeat_LCD_COM_SEG            (* (reg8 *) HeartBeat__LCD_COM_SEG)
/* Enable Segment LCD */
#define HeartBeat_LCD_EN                 (* (reg8 *) HeartBeat__LCD_EN)
/* Slew Rate Control */
#define HeartBeat_SLW                    (* (reg8 *) HeartBeat__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HeartBeat_PRTDSI__CAPS_SEL       (* (reg8 *) HeartBeat__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HeartBeat_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HeartBeat__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HeartBeat_PRTDSI__OE_SEL0        (* (reg8 *) HeartBeat__PRTDSI__OE_SEL0) 
#define HeartBeat_PRTDSI__OE_SEL1        (* (reg8 *) HeartBeat__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HeartBeat_PRTDSI__OUT_SEL0       (* (reg8 *) HeartBeat__PRTDSI__OUT_SEL0) 
#define HeartBeat_PRTDSI__OUT_SEL1       (* (reg8 *) HeartBeat__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HeartBeat_PRTDSI__SYNC_OUT       (* (reg8 *) HeartBeat__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HeartBeat__SIO_CFG)
    #define HeartBeat_SIO_HYST_EN        (* (reg8 *) HeartBeat__SIO_HYST_EN)
    #define HeartBeat_SIO_REG_HIFREQ     (* (reg8 *) HeartBeat__SIO_REG_HIFREQ)
    #define HeartBeat_SIO_CFG            (* (reg8 *) HeartBeat__SIO_CFG)
    #define HeartBeat_SIO_DIFF           (* (reg8 *) HeartBeat__SIO_DIFF)
#endif /* (HeartBeat__SIO_CFG) */

/* Interrupt Registers */
#if defined(HeartBeat__INTSTAT)
    #define HeartBeat_INTSTAT            (* (reg8 *) HeartBeat__INTSTAT)
    #define HeartBeat_SNAP               (* (reg8 *) HeartBeat__SNAP)
    
	#define HeartBeat_0_INTTYPE_REG 		(* (reg8 *) HeartBeat__0__INTTYPE)
#endif /* (HeartBeat__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HeartBeat_H */


/* [] END OF FILE */
