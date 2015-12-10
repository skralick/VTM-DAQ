/*******************************************************************************
* File Name: V_Supply.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "V_Supply.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 V_Supply__PORT == 15 && ((V_Supply__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: V_Supply_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void V_Supply_Write(uint8 value) 
{
    uint8 staticBits = (V_Supply_DR & (uint8)(~V_Supply_MASK));
    V_Supply_DR = staticBits | ((uint8)(value << V_Supply_SHIFT) & V_Supply_MASK);
}


/*******************************************************************************
* Function Name: V_Supply_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  V_Supply_DM_STRONG     Strong Drive 
*  V_Supply_DM_OD_HI      Open Drain, Drives High 
*  V_Supply_DM_OD_LO      Open Drain, Drives Low 
*  V_Supply_DM_RES_UP     Resistive Pull Up 
*  V_Supply_DM_RES_DWN    Resistive Pull Down 
*  V_Supply_DM_RES_UPDWN  Resistive Pull Up/Down 
*  V_Supply_DM_DIG_HIZ    High Impedance Digital 
*  V_Supply_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void V_Supply_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(V_Supply_0, mode);
	CyPins_SetPinDriveMode(V_Supply_1, mode);
	CyPins_SetPinDriveMode(V_Supply_2, mode);
	CyPins_SetPinDriveMode(V_Supply_3, mode);
	CyPins_SetPinDriveMode(V_Supply_4, mode);
	CyPins_SetPinDriveMode(V_Supply_5, mode);
}


/*******************************************************************************
* Function Name: V_Supply_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro V_Supply_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 V_Supply_Read(void) 
{
    return (V_Supply_PS & V_Supply_MASK) >> V_Supply_SHIFT;
}


/*******************************************************************************
* Function Name: V_Supply_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 V_Supply_ReadDataReg(void) 
{
    return (V_Supply_DR & V_Supply_MASK) >> V_Supply_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(V_Supply_INTSTAT) 

    /*******************************************************************************
    * Function Name: V_Supply_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 V_Supply_ClearInterrupt(void) 
    {
        return (V_Supply_INTSTAT & V_Supply_MASK) >> V_Supply_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
