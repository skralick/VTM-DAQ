/*******************************************************************************
* File Name: Ignition.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Ignition_H) /* Pins Ignition_H */
#define CY_PINS_Ignition_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ignition_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ignition__PORT == 15 && ((Ignition__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Ignition_Write(uint8 value) ;
void    Ignition_SetDriveMode(uint8 mode) ;
uint8   Ignition_ReadDataReg(void) ;
uint8   Ignition_Read(void) ;
uint8   Ignition_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Ignition_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Ignition_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Ignition_DM_RES_UP          PIN_DM_RES_UP
#define Ignition_DM_RES_DWN         PIN_DM_RES_DWN
#define Ignition_DM_OD_LO           PIN_DM_OD_LO
#define Ignition_DM_OD_HI           PIN_DM_OD_HI
#define Ignition_DM_STRONG          PIN_DM_STRONG
#define Ignition_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Ignition_MASK               Ignition__MASK
#define Ignition_SHIFT              Ignition__SHIFT
#define Ignition_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ignition_PS                     (* (reg8 *) Ignition__PS)
/* Data Register */
#define Ignition_DR                     (* (reg8 *) Ignition__DR)
/* Port Number */
#define Ignition_PRT_NUM                (* (reg8 *) Ignition__PRT) 
/* Connect to Analog Globals */                                                  
#define Ignition_AG                     (* (reg8 *) Ignition__AG)                       
/* Analog MUX bux enable */
#define Ignition_AMUX                   (* (reg8 *) Ignition__AMUX) 
/* Bidirectional Enable */                                                        
#define Ignition_BIE                    (* (reg8 *) Ignition__BIE)
/* Bit-mask for Aliased Register Access */
#define Ignition_BIT_MASK               (* (reg8 *) Ignition__BIT_MASK)
/* Bypass Enable */
#define Ignition_BYP                    (* (reg8 *) Ignition__BYP)
/* Port wide control signals */                                                   
#define Ignition_CTL                    (* (reg8 *) Ignition__CTL)
/* Drive Modes */
#define Ignition_DM0                    (* (reg8 *) Ignition__DM0) 
#define Ignition_DM1                    (* (reg8 *) Ignition__DM1)
#define Ignition_DM2                    (* (reg8 *) Ignition__DM2) 
/* Input Buffer Disable Override */
#define Ignition_INP_DIS                (* (reg8 *) Ignition__INP_DIS)
/* LCD Common or Segment Drive */
#define Ignition_LCD_COM_SEG            (* (reg8 *) Ignition__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ignition_LCD_EN                 (* (reg8 *) Ignition__LCD_EN)
/* Slew Rate Control */
#define Ignition_SLW                    (* (reg8 *) Ignition__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ignition_PRTDSI__CAPS_SEL       (* (reg8 *) Ignition__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ignition_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ignition__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ignition_PRTDSI__OE_SEL0        (* (reg8 *) Ignition__PRTDSI__OE_SEL0) 
#define Ignition_PRTDSI__OE_SEL1        (* (reg8 *) Ignition__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ignition_PRTDSI__OUT_SEL0       (* (reg8 *) Ignition__PRTDSI__OUT_SEL0) 
#define Ignition_PRTDSI__OUT_SEL1       (* (reg8 *) Ignition__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ignition_PRTDSI__SYNC_OUT       (* (reg8 *) Ignition__PRTDSI__SYNC_OUT) 


#if defined(Ignition__INTSTAT)  /* Interrupt Registers */

    #define Ignition_INTSTAT                (* (reg8 *) Ignition__INTSTAT)
    #define Ignition_SNAP                   (* (reg8 *) Ignition__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ignition_H */


/* [] END OF FILE */
