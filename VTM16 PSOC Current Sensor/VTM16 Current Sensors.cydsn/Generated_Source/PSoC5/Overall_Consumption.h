/*******************************************************************************
* File Name: Overall_Consumption.h  
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

#if !defined(CY_PINS_Overall_Consumption_H) /* Pins Overall_Consumption_H */
#define CY_PINS_Overall_Consumption_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Overall_Consumption_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Overall_Consumption__PORT == 15 && ((Overall_Consumption__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Overall_Consumption_Write(uint8 value) ;
void    Overall_Consumption_SetDriveMode(uint8 mode) ;
uint8   Overall_Consumption_ReadDataReg(void) ;
uint8   Overall_Consumption_Read(void) ;
uint8   Overall_Consumption_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Overall_Consumption_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Overall_Consumption_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Overall_Consumption_DM_RES_UP          PIN_DM_RES_UP
#define Overall_Consumption_DM_RES_DWN         PIN_DM_RES_DWN
#define Overall_Consumption_DM_OD_LO           PIN_DM_OD_LO
#define Overall_Consumption_DM_OD_HI           PIN_DM_OD_HI
#define Overall_Consumption_DM_STRONG          PIN_DM_STRONG
#define Overall_Consumption_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Overall_Consumption_MASK               Overall_Consumption__MASK
#define Overall_Consumption_SHIFT              Overall_Consumption__SHIFT
#define Overall_Consumption_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Overall_Consumption_PS                     (* (reg8 *) Overall_Consumption__PS)
/* Data Register */
#define Overall_Consumption_DR                     (* (reg8 *) Overall_Consumption__DR)
/* Port Number */
#define Overall_Consumption_PRT_NUM                (* (reg8 *) Overall_Consumption__PRT) 
/* Connect to Analog Globals */                                                  
#define Overall_Consumption_AG                     (* (reg8 *) Overall_Consumption__AG)                       
/* Analog MUX bux enable */
#define Overall_Consumption_AMUX                   (* (reg8 *) Overall_Consumption__AMUX) 
/* Bidirectional Enable */                                                        
#define Overall_Consumption_BIE                    (* (reg8 *) Overall_Consumption__BIE)
/* Bit-mask for Aliased Register Access */
#define Overall_Consumption_BIT_MASK               (* (reg8 *) Overall_Consumption__BIT_MASK)
/* Bypass Enable */
#define Overall_Consumption_BYP                    (* (reg8 *) Overall_Consumption__BYP)
/* Port wide control signals */                                                   
#define Overall_Consumption_CTL                    (* (reg8 *) Overall_Consumption__CTL)
/* Drive Modes */
#define Overall_Consumption_DM0                    (* (reg8 *) Overall_Consumption__DM0) 
#define Overall_Consumption_DM1                    (* (reg8 *) Overall_Consumption__DM1)
#define Overall_Consumption_DM2                    (* (reg8 *) Overall_Consumption__DM2) 
/* Input Buffer Disable Override */
#define Overall_Consumption_INP_DIS                (* (reg8 *) Overall_Consumption__INP_DIS)
/* LCD Common or Segment Drive */
#define Overall_Consumption_LCD_COM_SEG            (* (reg8 *) Overall_Consumption__LCD_COM_SEG)
/* Enable Segment LCD */
#define Overall_Consumption_LCD_EN                 (* (reg8 *) Overall_Consumption__LCD_EN)
/* Slew Rate Control */
#define Overall_Consumption_SLW                    (* (reg8 *) Overall_Consumption__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Overall_Consumption_PRTDSI__CAPS_SEL       (* (reg8 *) Overall_Consumption__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Overall_Consumption_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Overall_Consumption__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Overall_Consumption_PRTDSI__OE_SEL0        (* (reg8 *) Overall_Consumption__PRTDSI__OE_SEL0) 
#define Overall_Consumption_PRTDSI__OE_SEL1        (* (reg8 *) Overall_Consumption__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Overall_Consumption_PRTDSI__OUT_SEL0       (* (reg8 *) Overall_Consumption__PRTDSI__OUT_SEL0) 
#define Overall_Consumption_PRTDSI__OUT_SEL1       (* (reg8 *) Overall_Consumption__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Overall_Consumption_PRTDSI__SYNC_OUT       (* (reg8 *) Overall_Consumption__PRTDSI__SYNC_OUT) 


#if defined(Overall_Consumption__INTSTAT)  /* Interrupt Registers */

    #define Overall_Consumption_INTSTAT                (* (reg8 *) Overall_Consumption__INTSTAT)
    #define Overall_Consumption_SNAP                   (* (reg8 *) Overall_Consumption__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Overall_Consumption_H */


/* [] END OF FILE */
