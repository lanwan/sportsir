/*
This software is subject to the license described in the License.txt file
included with this software distribution. You may not use this file except in compliance
with this license.

Copyright (c) Dynastream Innovations Inc. 2013
All rights reserved.
*/

#ifndef __BC_TX__
#define __BC_TX__

#include "config.h"
#include "types.h"
#include "antinterface.h"
#include "antplus.h"

// Global Page Settings
#define BCTX_MFG_ID                          ((UCHAR) 3)        // Manufacturer ID
#define BCTX_SERIAL_NUMBER                   ((UCHAR) 0xBCDE)   // Serial Number
#define BCTX_HW_VERSION                      ((UCHAR) 4)        // HW Version
#define BCTX_SW_VERSION                      ((UCHAR) 3)        // SW Version
#define BCTX_MODEL_NUMBER                    ((UCHAR) 1)        // Model Number

// Publc Functions
void 
BCTX_Init();

BOOL                                                           // TRUE is commands queued succesfully 
BCTX_Open(
   UCHAR ucAntChannel_,                                        // ANT Channel number
   USHORT usDeviceNumber_,                                     // ANT Channel device number
   UCHAR ucTransType_);                                        // ANT Channel transmission type
   
BOOL                                                           // TRUE if command queued succesfully  
BCTX_Close();

BOOL                                                           // TRUE if commands queued to transmit (don't sleep transmit thread)
BCTX_ChannelEvent(
   UCHAR* pucEventBuffer_,                                     // Pointer to buffer containing response from ANT
   ANTPLUS_EVENT_RETURN* pstEventStruct_);                     // Pointer to event structure set by this function
   
void                                                           // Returns TRUE
BCTX_PulseEvent(                                               
   USHORT usTime1024,
   UCHAR ucAlarmNumber_);                                         // Time of pulse event in (1/1024)s

#endif
