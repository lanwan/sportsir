/*
This software is subject to the license described in the License.txt file
included with this software distribution. You may not use this file except in compliance
with this license.

Copyright (c) Dynastream Innovations Inc. 2013
All rights reserved.
*/

#ifndef __BS_TX__
#define __BS_TX__

#include "config.h"
#include "types.h"
#include "antinterface.h"
#include "antplus.h"

// ANT Channel Settings

// Global Page Settings
#define BSTX_MFG_ID                          ((UCHAR) 2)        // Manufacturer ID
#define BSTX_SERIAL_NUMBER                   ((UCHAR) 0x21FE)   // Serial Number
#define BSTX_HW_VERSION                      ((UCHAR) 5)        // HW Version
#define BSTX_SW_VERSION                      ((UCHAR) 0)        // SW Version
#define BSTX_MODEL_NUMBER                    ((UCHAR) 2)        // Model Number

// Publc Functions
void 
BSTX_Init();

BOOL                                                           // TRUE is commands queued succesfully 
BSTX_Open(
   UCHAR ucAntChannel_,                                        // ANT Channel number
   USHORT usDeviceNumber_,                                     // ANT Channel device number
   UCHAR ucTransType_);                                        // ANT Channel transmission type
   
BOOL                                                           // TRUE if command queued succesfully  
BSTX_Close();

BOOL                                                           // TRUE if commands queued to transmit (don't sleep transmit thread)
BSTX_ChannelEvent(
   UCHAR* pucEventBuffer_,                                     // Pointer to buffer containing response from ANT
   ANTPLUS_EVENT_RETURN* pstEventStruct_);                     // Pointer to event structure set by this function
   
void 
BSTX_PulseEvent(                                               // Returns TRUE
   USHORT usTime1024,
   UCHAR ucAlarmNumber_);                                         // Time of pulse event in (1/1024)s

#endif
