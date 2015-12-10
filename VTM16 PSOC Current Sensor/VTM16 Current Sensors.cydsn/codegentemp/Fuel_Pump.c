/*******************************************************************************
* File Name: Fuel_Pump.c  
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
#include "Fuel_Pump.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Fuel_Pump__PORT == 15 && ((Fuel_Pump__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Fuel_Pump_Write
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
void Fuel_Pump_Write(uint8 value) 
{
    uint8 staticBits = (Fuel_Pump_DR & (uint8)(~Fuel_Pump_MASK));
    Fuel_Pump_DR = staticBits | ((uint8)(value << Fuel_Pump_SHIFT) & Fuel_Pump_MASK);
}


/*******************************************************************************
* Function Name: Fuel_Pump_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Fuel_Pump_DM_STRONG     Strong Drive 
*  Fuel_Pump_DM_OD_HI      Open Drain, Drives High 
*  Fuel_Pump_DM_OD_LO      Open Drain, Drives Low 
*  Fuel_Pump_DM_RES_UP     Resistive Pull Up 
*  Fuel_Pump_DM_RES_DWN    Resistive Pull Down 
*  Fuel_Pump_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Fuel_Pump_DM_DIG_HIZ    High Impedance Digital 
*  Fuel_Pump_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Fuel_Pump_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Fuel_Pump_0, mode);
}


/*******************************************************************************
* Function Name: Fuel_Pump_Read
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
*  Macro Fuel_Pump_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Fuel_Pump_Read(void) 
{
    return (Fuel_Pump_PS & Fuel_Pump_MASK) >> Fuel_Pump_SHIFT;
}


/*******************************************************************************
* Function Name: Fuel_Pump_ReadDataReg
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
uint8 Fuel_Pump_ReadDataReg(void) 
{
    return (Fuel_Pump_DR & Fuel_Pump_MASK) >> Fuel_Pump_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Fuel_Pump_INTSTAT) 

    /*******************************************************************************
    * Function Name: Fuel_Pump_ClearInterrupt
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
    uint8 Fuel_Pump_ClearInterrupt(void) 
    {
        return (Fuel_Pump_INTSTAT & Fuel_Pump_MASK) >> Fuel_Pump_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
