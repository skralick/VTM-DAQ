/*******************************************************************************
* File Name: Overall_Consumption.c  
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
#include "Overall_Consumption.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Overall_Consumption__PORT == 15 && ((Overall_Consumption__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Overall_Consumption_Write
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
void Overall_Consumption_Write(uint8 value) 
{
    uint8 staticBits = (Overall_Consumption_DR & (uint8)(~Overall_Consumption_MASK));
    Overall_Consumption_DR = staticBits | ((uint8)(value << Overall_Consumption_SHIFT) & Overall_Consumption_MASK);
}


/*******************************************************************************
* Function Name: Overall_Consumption_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Overall_Consumption_DM_STRONG     Strong Drive 
*  Overall_Consumption_DM_OD_HI      Open Drain, Drives High 
*  Overall_Consumption_DM_OD_LO      Open Drain, Drives Low 
*  Overall_Consumption_DM_RES_UP     Resistive Pull Up 
*  Overall_Consumption_DM_RES_DWN    Resistive Pull Down 
*  Overall_Consumption_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Overall_Consumption_DM_DIG_HIZ    High Impedance Digital 
*  Overall_Consumption_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Overall_Consumption_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Overall_Consumption_0, mode);
}


/*******************************************************************************
* Function Name: Overall_Consumption_Read
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
*  Macro Overall_Consumption_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Overall_Consumption_Read(void) 
{
    return (Overall_Consumption_PS & Overall_Consumption_MASK) >> Overall_Consumption_SHIFT;
}


/*******************************************************************************
* Function Name: Overall_Consumption_ReadDataReg
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
uint8 Overall_Consumption_ReadDataReg(void) 
{
    return (Overall_Consumption_DR & Overall_Consumption_MASK) >> Overall_Consumption_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Overall_Consumption_INTSTAT) 

    /*******************************************************************************
    * Function Name: Overall_Consumption_ClearInterrupt
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
    uint8 Overall_Consumption_ClearInterrupt(void) 
    {
        return (Overall_Consumption_INTSTAT & Overall_Consumption_MASK) >> Overall_Consumption_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
