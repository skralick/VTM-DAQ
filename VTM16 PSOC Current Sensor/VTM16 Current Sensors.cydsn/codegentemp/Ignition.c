/*******************************************************************************
* File Name: Ignition.c  
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
#include "Ignition.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Ignition__PORT == 15 && ((Ignition__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Ignition_Write
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
void Ignition_Write(uint8 value) 
{
    uint8 staticBits = (Ignition_DR & (uint8)(~Ignition_MASK));
    Ignition_DR = staticBits | ((uint8)(value << Ignition_SHIFT) & Ignition_MASK);
}


/*******************************************************************************
* Function Name: Ignition_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Ignition_DM_STRONG     Strong Drive 
*  Ignition_DM_OD_HI      Open Drain, Drives High 
*  Ignition_DM_OD_LO      Open Drain, Drives Low 
*  Ignition_DM_RES_UP     Resistive Pull Up 
*  Ignition_DM_RES_DWN    Resistive Pull Down 
*  Ignition_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Ignition_DM_DIG_HIZ    High Impedance Digital 
*  Ignition_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Ignition_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Ignition_0, mode);
}


/*******************************************************************************
* Function Name: Ignition_Read
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
*  Macro Ignition_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Ignition_Read(void) 
{
    return (Ignition_PS & Ignition_MASK) >> Ignition_SHIFT;
}


/*******************************************************************************
* Function Name: Ignition_ReadDataReg
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
uint8 Ignition_ReadDataReg(void) 
{
    return (Ignition_DR & Ignition_MASK) >> Ignition_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Ignition_INTSTAT) 

    /*******************************************************************************
    * Function Name: Ignition_ClearInterrupt
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
    uint8 Ignition_ClearInterrupt(void) 
    {
        return (Ignition_INTSTAT & Ignition_MASK) >> Ignition_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
