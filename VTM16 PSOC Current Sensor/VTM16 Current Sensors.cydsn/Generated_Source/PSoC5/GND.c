/*******************************************************************************
* File Name: GND.c  
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
#include "GND.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 GND__PORT == 15 && ((GND__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: GND_Write
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
void GND_Write(uint8 value) 
{
    uint8 staticBits = (GND_DR & (uint8)(~GND_MASK));
    GND_DR = staticBits | ((uint8)(value << GND_SHIFT) & GND_MASK);
}


/*******************************************************************************
* Function Name: GND_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  GND_DM_STRONG     Strong Drive 
*  GND_DM_OD_HI      Open Drain, Drives High 
*  GND_DM_OD_LO      Open Drain, Drives Low 
*  GND_DM_RES_UP     Resistive Pull Up 
*  GND_DM_RES_DWN    Resistive Pull Down 
*  GND_DM_RES_UPDWN  Resistive Pull Up/Down 
*  GND_DM_DIG_HIZ    High Impedance Digital 
*  GND_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void GND_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(GND_0, mode);
	CyPins_SetPinDriveMode(GND_1, mode);
	CyPins_SetPinDriveMode(GND_2, mode);
	CyPins_SetPinDriveMode(GND_3, mode);
	CyPins_SetPinDriveMode(GND_4, mode);
}


/*******************************************************************************
* Function Name: GND_Read
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
*  Macro GND_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 GND_Read(void) 
{
    return (GND_PS & GND_MASK) >> GND_SHIFT;
}


/*******************************************************************************
* Function Name: GND_ReadDataReg
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
uint8 GND_ReadDataReg(void) 
{
    return (GND_DR & GND_MASK) >> GND_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(GND_INTSTAT) 

    /*******************************************************************************
    * Function Name: GND_ClearInterrupt
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
    uint8 GND_ClearInterrupt(void) 
    {
        return (GND_INTSTAT & GND_MASK) >> GND_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
