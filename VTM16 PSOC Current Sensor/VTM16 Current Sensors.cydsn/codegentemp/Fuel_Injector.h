/*******************************************************************************
* File Name: Fuel_Injector.h  
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

#if !defined(CY_PINS_Fuel_Injector_H) /* Pins Fuel_Injector_H */
#define CY_PINS_Fuel_Injector_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Fuel_Injector_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Fuel_Injector__PORT == 15 && ((Fuel_Injector__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Fuel_Injector_Write(uint8 value) ;
void    Fuel_Injector_SetDriveMode(uint8 mode) ;
uint8   Fuel_Injector_ReadDataReg(void) ;
uint8   Fuel_Injector_Read(void) ;
uint8   Fuel_Injector_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Fuel_Injector_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Fuel_Injector_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Fuel_Injector_DM_RES_UP          PIN_DM_RES_UP
#define Fuel_Injector_DM_RES_DWN         PIN_DM_RES_DWN
#define Fuel_Injector_DM_OD_LO           PIN_DM_OD_LO
#define Fuel_Injector_DM_OD_HI           PIN_DM_OD_HI
#define Fuel_Injector_DM_STRONG          PIN_DM_STRONG
#define Fuel_Injector_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Fuel_Injector_MASK               Fuel_Injector__MASK
#define Fuel_Injector_SHIFT              Fuel_Injector__SHIFT
#define Fuel_Injector_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Fuel_Injector_PS                     (* (reg8 *) Fuel_Injector__PS)
/* Data Register */
#define Fuel_Injector_DR                     (* (reg8 *) Fuel_Injector__DR)
/* Port Number */
#define Fuel_Injector_PRT_NUM                (* (reg8 *) Fuel_Injector__PRT) 
/* Connect to Analog Globals */                                                  
#define Fuel_Injector_AG                     (* (reg8 *) Fuel_Injector__AG)                       
/* Analog MUX bux enable */
#define Fuel_Injector_AMUX                   (* (reg8 *) Fuel_Injector__AMUX) 
/* Bidirectional Enable */                                                        
#define Fuel_Injector_BIE                    (* (reg8 *) Fuel_Injector__BIE)
/* Bit-mask for Aliased Register Access */
#define Fuel_Injector_BIT_MASK               (* (reg8 *) Fuel_Injector__BIT_MASK)
/* Bypass Enable */
#define Fuel_Injector_BYP                    (* (reg8 *) Fuel_Injector__BYP)
/* Port wide control signals */                                                   
#define Fuel_Injector_CTL                    (* (reg8 *) Fuel_Injector__CTL)
/* Drive Modes */
#define Fuel_Injector_DM0                    (* (reg8 *) Fuel_Injector__DM0) 
#define Fuel_Injector_DM1                    (* (reg8 *) Fuel_Injector__DM1)
#define Fuel_Injector_DM2                    (* (reg8 *) Fuel_Injector__DM2) 
/* Input Buffer Disable Override */
#define Fuel_Injector_INP_DIS                (* (reg8 *) Fuel_Injector__INP_DIS)
/* LCD Common or Segment Drive */
#define Fuel_Injector_LCD_COM_SEG            (* (reg8 *) Fuel_Injector__LCD_COM_SEG)
/* Enable Segment LCD */
#define Fuel_Injector_LCD_EN                 (* (reg8 *) Fuel_Injector__LCD_EN)
/* Slew Rate Control */
#define Fuel_Injector_SLW                    (* (reg8 *) Fuel_Injector__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Fuel_Injector_PRTDSI__CAPS_SEL       (* (reg8 *) Fuel_Injector__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Fuel_Injector_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Fuel_Injector__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Fuel_Injector_PRTDSI__OE_SEL0        (* (reg8 *) Fuel_Injector__PRTDSI__OE_SEL0) 
#define Fuel_Injector_PRTDSI__OE_SEL1        (* (reg8 *) Fuel_Injector__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Fuel_Injector_PRTDSI__OUT_SEL0       (* (reg8 *) Fuel_Injector__PRTDSI__OUT_SEL0) 
#define Fuel_Injector_PRTDSI__OUT_SEL1       (* (reg8 *) Fuel_Injector__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Fuel_Injector_PRTDSI__SYNC_OUT       (* (reg8 *) Fuel_Injector__PRTDSI__SYNC_OUT) 


#if defined(Fuel_Injector__INTSTAT)  /* Interrupt Registers */

    #define Fuel_Injector_INTSTAT                (* (reg8 *) Fuel_Injector__INTSTAT)
    #define Fuel_Injector_SNAP                   (* (reg8 *) Fuel_Injector__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Fuel_Injector_H */


/* [] END OF FILE */
