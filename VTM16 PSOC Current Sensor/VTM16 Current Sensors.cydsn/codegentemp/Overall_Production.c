/*******************************************************************************
* File Name: Overall_Production.c  
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
#include "Overall_Production.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Overall_Production__PORT == 15 && ((Overall_Production__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Overall_Production_Write
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
void Overall_Production_Write(uint8 value) 
{
    uint8 staticBits = (Overall_Production_DR & (uint8)(~Overall_Production_MASK));
    Overall_Production_DR = staticBits | ((uint8)(value << Overall_Production_SHIFT) & Overall_Production_MASK);
}


/*******************************************************************************
* Function Name: Overall_Production_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Overall_Production_DM_STRONG     Strong Drive 
*  Overall_Production_DM_OD_HI      Open Drain, Drives High 
*  Overall_Production_DM_OD_LO      Open Drain, Drives Low 
*  Overall_Production_DM_RES_UP     Resistive Pull Up 
*  Overall_Production_DM_RES_DWN    Resistive Pull Down 
*  Overall_Production_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Overall_Production_DM_DIG_HIZ    High Impedance Digital 
*  Overall_Production_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Overall_Production_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Overall_Production_0, mode);
}


/*******************************************************************************
* Function Name: Overall_Production_Read
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
*  Macro Overall_Production_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Overall_Production_Read(void) 
{
    return (Overall_Production_PS & Overall_Production_MASK) >> Overall_Production_SHIFT;
}


/*******************************************************************************
* Function Name: Overall_Production_ReadDataReg
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
uint8 Overall_Production_ReadDataReg(void) 
{
    return (Overall_Production_DR & Overall_Production_MASK) >> Overall_Production_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Overall_Production_INTSTAT) 

    /*******************************************************************************
    * Function Name: Overall_Production_ClearInterrupt
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
    uint8 Overall_Production_ClearInterrupt(void) 
    {
        return (Overall_Production_INTSTAT & Overall_Production_MASK) >> Overall_Production_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
