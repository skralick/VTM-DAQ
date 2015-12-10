/*******************************************************************************
* File Name: .h
* Version 2.0
*
* Description:
*  This file provides private constants and parameter values for the EZI2C
*  component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EZI2C_PVT_EZI2C_1_H)
#define CY_EZI2C_PVT_EZI2C_1_H

#include "EZI2C_1.h"


/***************************************
*     Vars with External Linkage
***************************************/

extern EZI2C_1_BACKUP_STRUCT  EZI2C_1_backup;

/* Status and state variables */
extern volatile uint8 EZI2C_1_curStatus;
extern volatile uint8 EZI2C_1_curState;

/* Primary slave address variables */
extern volatile uint8* EZI2C_1_dataPtrS1;
extern volatile uint16 EZI2C_1_bufSizeS1;
extern volatile uint16 EZI2C_1_wrProtectS1;
extern volatile uint8 EZI2C_1_rwOffsetS1;
extern volatile uint8 EZI2C_1_rwIndexS1;

/* Secondary slave address variables */
#if (EZI2C_1_ADDRESSES == EZI2C_1_TWO_ADDRESSES)
    extern volatile uint8  EZI2C_1_addrS1;
    extern volatile uint8  EZI2C_1_addrS2;
    extern volatile uint8* EZI2C_1_dataPtrS2;
    extern volatile uint16 EZI2C_1_bufSizeS2;
    extern volatile uint16 EZI2C_1_wrProtectS2;
    extern volatile uint8 EZI2C_1_rwOffsetS2;
    extern volatile uint8 EZI2C_1_rwIndexS2;
#endif  /* (EZI2C_1_ADDRESSES == EZI2C_1_TWO_ADDRESSES) */

#if (EZI2C_1_WAKEUP_ENABLED)
    extern volatile uint8 EZI2C_1_wakeupSource;
#endif /* (EZI2C_1_WAKEUP_ENABLED) */

#endif /* CY_EZI2C_PVT_EZI2C_1_H */


/* [] END OF FILE */
