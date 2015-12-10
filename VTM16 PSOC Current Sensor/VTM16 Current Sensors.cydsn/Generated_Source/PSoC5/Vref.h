/*******************************************************************************
* File Name: Vref.h  
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

#if !defined(CY_PINS_Vref_H) /* Pins Vref_H */
#define CY_PINS_Vref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vref_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vref__PORT == 15 && ((Vref__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Vref_Write(uint8 value) ;
void    Vref_SetDriveMode(uint8 mode) ;
uint8   Vref_ReadDataReg(void) ;
uint8   Vref_Read(void) ;
uint8   Vref_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Vref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Vref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Vref_DM_RES_UP          PIN_DM_RES_UP
#define Vref_DM_RES_DWN         PIN_DM_RES_DWN
#define Vref_DM_OD_LO           PIN_DM_OD_LO
#define Vref_DM_OD_HI           PIN_DM_OD_HI
#define Vref_DM_STRONG          PIN_DM_STRONG
#define Vref_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Vref_MASK               Vref__MASK
#define Vref_SHIFT              Vref__SHIFT
#define Vref_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vref_PS                     (* (reg8 *) Vref__PS)
/* Data Register */
#define Vref_DR                     (* (reg8 *) Vref__DR)
/* Port Number */
#define Vref_PRT_NUM                (* (reg8 *) Vref__PRT) 
/* Connect to Analog Globals */                                                  
#define Vref_AG                     (* (reg8 *) Vref__AG)                       
/* Analog MUX bux enable */
#define Vref_AMUX                   (* (reg8 *) Vref__AMUX) 
/* Bidirectional Enable */                                                        
#define Vref_BIE                    (* (reg8 *) Vref__BIE)
/* Bit-mask for Aliased Register Access */
#define Vref_BIT_MASK               (* (reg8 *) Vref__BIT_MASK)
/* Bypass Enable */
#define Vref_BYP                    (* (reg8 *) Vref__BYP)
/* Port wide control signals */                                                   
#define Vref_CTL                    (* (reg8 *) Vref__CTL)
/* Drive Modes */
#define Vref_DM0                    (* (reg8 *) Vref__DM0) 
#define Vref_DM1                    (* (reg8 *) Vref__DM1)
#define Vref_DM2                    (* (reg8 *) Vref__DM2) 
/* Input Buffer Disable Override */
#define Vref_INP_DIS                (* (reg8 *) Vref__INP_DIS)
/* LCD Common or Segment Drive */
#define Vref_LCD_COM_SEG            (* (reg8 *) Vref__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vref_LCD_EN                 (* (reg8 *) Vref__LCD_EN)
/* Slew Rate Control */
#define Vref_SLW                    (* (reg8 *) Vref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vref_PRTDSI__CAPS_SEL       (* (reg8 *) Vref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vref_PRTDSI__OE_SEL0        (* (reg8 *) Vref__PRTDSI__OE_SEL0) 
#define Vref_PRTDSI__OE_SEL1        (* (reg8 *) Vref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vref_PRTDSI__OUT_SEL0       (* (reg8 *) Vref__PRTDSI__OUT_SEL0) 
#define Vref_PRTDSI__OUT_SEL1       (* (reg8 *) Vref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vref_PRTDSI__SYNC_OUT       (* (reg8 *) Vref__PRTDSI__SYNC_OUT) 


#if defined(Vref__INTSTAT)  /* Interrupt Registers */

    #define Vref_INTSTAT                (* (reg8 *) Vref__INTSTAT)
    #define Vref_SNAP                   (* (reg8 *) Vref__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vref_H */


/* [] END OF FILE */
