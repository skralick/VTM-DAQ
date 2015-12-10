/*******************************************************************************
* File Name: Fuel_Pump.h  
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

#if !defined(CY_PINS_Fuel_Pump_H) /* Pins Fuel_Pump_H */
#define CY_PINS_Fuel_Pump_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Fuel_Pump_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Fuel_Pump__PORT == 15 && ((Fuel_Pump__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Fuel_Pump_Write(uint8 value) ;
void    Fuel_Pump_SetDriveMode(uint8 mode) ;
uint8   Fuel_Pump_ReadDataReg(void) ;
uint8   Fuel_Pump_Read(void) ;
uint8   Fuel_Pump_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Fuel_Pump_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Fuel_Pump_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Fuel_Pump_DM_RES_UP          PIN_DM_RES_UP
#define Fuel_Pump_DM_RES_DWN         PIN_DM_RES_DWN
#define Fuel_Pump_DM_OD_LO           PIN_DM_OD_LO
#define Fuel_Pump_DM_OD_HI           PIN_DM_OD_HI
#define Fuel_Pump_DM_STRONG          PIN_DM_STRONG
#define Fuel_Pump_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Fuel_Pump_MASK               Fuel_Pump__MASK
#define Fuel_Pump_SHIFT              Fuel_Pump__SHIFT
#define Fuel_Pump_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Fuel_Pump_PS                     (* (reg8 *) Fuel_Pump__PS)
/* Data Register */
#define Fuel_Pump_DR                     (* (reg8 *) Fuel_Pump__DR)
/* Port Number */
#define Fuel_Pump_PRT_NUM                (* (reg8 *) Fuel_Pump__PRT) 
/* Connect to Analog Globals */                                                  
#define Fuel_Pump_AG                     (* (reg8 *) Fuel_Pump__AG)                       
/* Analog MUX bux enable */
#define Fuel_Pump_AMUX                   (* (reg8 *) Fuel_Pump__AMUX) 
/* Bidirectional Enable */                                                        
#define Fuel_Pump_BIE                    (* (reg8 *) Fuel_Pump__BIE)
/* Bit-mask for Aliased Register Access */
#define Fuel_Pump_BIT_MASK               (* (reg8 *) Fuel_Pump__BIT_MASK)
/* Bypass Enable */
#define Fuel_Pump_BYP                    (* (reg8 *) Fuel_Pump__BYP)
/* Port wide control signals */                                                   
#define Fuel_Pump_CTL                    (* (reg8 *) Fuel_Pump__CTL)
/* Drive Modes */
#define Fuel_Pump_DM0                    (* (reg8 *) Fuel_Pump__DM0) 
#define Fuel_Pump_DM1                    (* (reg8 *) Fuel_Pump__DM1)
#define Fuel_Pump_DM2                    (* (reg8 *) Fuel_Pump__DM2) 
/* Input Buffer Disable Override */
#define Fuel_Pump_INP_DIS                (* (reg8 *) Fuel_Pump__INP_DIS)
/* LCD Common or Segment Drive */
#define Fuel_Pump_LCD_COM_SEG            (* (reg8 *) Fuel_Pump__LCD_COM_SEG)
/* Enable Segment LCD */
#define Fuel_Pump_LCD_EN                 (* (reg8 *) Fuel_Pump__LCD_EN)
/* Slew Rate Control */
#define Fuel_Pump_SLW                    (* (reg8 *) Fuel_Pump__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Fuel_Pump_PRTDSI__CAPS_SEL       (* (reg8 *) Fuel_Pump__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Fuel_Pump_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Fuel_Pump__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Fuel_Pump_PRTDSI__OE_SEL0        (* (reg8 *) Fuel_Pump__PRTDSI__OE_SEL0) 
#define Fuel_Pump_PRTDSI__OE_SEL1        (* (reg8 *) Fuel_Pump__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Fuel_Pump_PRTDSI__OUT_SEL0       (* (reg8 *) Fuel_Pump__PRTDSI__OUT_SEL0) 
#define Fuel_Pump_PRTDSI__OUT_SEL1       (* (reg8 *) Fuel_Pump__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Fuel_Pump_PRTDSI__SYNC_OUT       (* (reg8 *) Fuel_Pump__PRTDSI__SYNC_OUT) 


#if defined(Fuel_Pump__INTSTAT)  /* Interrupt Registers */

    #define Fuel_Pump_INTSTAT                (* (reg8 *) Fuel_Pump__INTSTAT)
    #define Fuel_Pump_SNAP                   (* (reg8 *) Fuel_Pump__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Fuel_Pump_H */


/* [] END OF FILE */
