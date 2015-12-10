/*******************************************************************************
* File Name: Overall_Production.h  
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

#if !defined(CY_PINS_Overall_Production_H) /* Pins Overall_Production_H */
#define CY_PINS_Overall_Production_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Overall_Production_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Overall_Production__PORT == 15 && ((Overall_Production__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Overall_Production_Write(uint8 value) ;
void    Overall_Production_SetDriveMode(uint8 mode) ;
uint8   Overall_Production_ReadDataReg(void) ;
uint8   Overall_Production_Read(void) ;
uint8   Overall_Production_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Overall_Production_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Overall_Production_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Overall_Production_DM_RES_UP          PIN_DM_RES_UP
#define Overall_Production_DM_RES_DWN         PIN_DM_RES_DWN
#define Overall_Production_DM_OD_LO           PIN_DM_OD_LO
#define Overall_Production_DM_OD_HI           PIN_DM_OD_HI
#define Overall_Production_DM_STRONG          PIN_DM_STRONG
#define Overall_Production_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Overall_Production_MASK               Overall_Production__MASK
#define Overall_Production_SHIFT              Overall_Production__SHIFT
#define Overall_Production_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Overall_Production_PS                     (* (reg8 *) Overall_Production__PS)
/* Data Register */
#define Overall_Production_DR                     (* (reg8 *) Overall_Production__DR)
/* Port Number */
#define Overall_Production_PRT_NUM                (* (reg8 *) Overall_Production__PRT) 
/* Connect to Analog Globals */                                                  
#define Overall_Production_AG                     (* (reg8 *) Overall_Production__AG)                       
/* Analog MUX bux enable */
#define Overall_Production_AMUX                   (* (reg8 *) Overall_Production__AMUX) 
/* Bidirectional Enable */                                                        
#define Overall_Production_BIE                    (* (reg8 *) Overall_Production__BIE)
/* Bit-mask for Aliased Register Access */
#define Overall_Production_BIT_MASK               (* (reg8 *) Overall_Production__BIT_MASK)
/* Bypass Enable */
#define Overall_Production_BYP                    (* (reg8 *) Overall_Production__BYP)
/* Port wide control signals */                                                   
#define Overall_Production_CTL                    (* (reg8 *) Overall_Production__CTL)
/* Drive Modes */
#define Overall_Production_DM0                    (* (reg8 *) Overall_Production__DM0) 
#define Overall_Production_DM1                    (* (reg8 *) Overall_Production__DM1)
#define Overall_Production_DM2                    (* (reg8 *) Overall_Production__DM2) 
/* Input Buffer Disable Override */
#define Overall_Production_INP_DIS                (* (reg8 *) Overall_Production__INP_DIS)
/* LCD Common or Segment Drive */
#define Overall_Production_LCD_COM_SEG            (* (reg8 *) Overall_Production__LCD_COM_SEG)
/* Enable Segment LCD */
#define Overall_Production_LCD_EN                 (* (reg8 *) Overall_Production__LCD_EN)
/* Slew Rate Control */
#define Overall_Production_SLW                    (* (reg8 *) Overall_Production__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Overall_Production_PRTDSI__CAPS_SEL       (* (reg8 *) Overall_Production__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Overall_Production_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Overall_Production__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Overall_Production_PRTDSI__OE_SEL0        (* (reg8 *) Overall_Production__PRTDSI__OE_SEL0) 
#define Overall_Production_PRTDSI__OE_SEL1        (* (reg8 *) Overall_Production__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Overall_Production_PRTDSI__OUT_SEL0       (* (reg8 *) Overall_Production__PRTDSI__OUT_SEL0) 
#define Overall_Production_PRTDSI__OUT_SEL1       (* (reg8 *) Overall_Production__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Overall_Production_PRTDSI__SYNC_OUT       (* (reg8 *) Overall_Production__PRTDSI__SYNC_OUT) 


#if defined(Overall_Production__INTSTAT)  /* Interrupt Registers */

    #define Overall_Production_INTSTAT                (* (reg8 *) Overall_Production__INTSTAT)
    #define Overall_Production_SNAP                   (* (reg8 *) Overall_Production__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Overall_Production_H */


/* [] END OF FILE */
