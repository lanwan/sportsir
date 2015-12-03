/*
This software is subject to the license described in the License.txt file
included with this software distribution. You may not use this file except in compliance
with this license.

Copyright (c) Dynastream Innovations Inc. 2013
All rights reserved.
*/

#include "types.h"
#include "antinterface.h"
#include "antdefines.h"
#include "timer.h"
#include "printf.h"

#include "ioboard.h"
#include "bs_tx.h"
#include "bc_tx.h"


extern volatile USHORT usLowPowerMode;                          // low power mode control

#define BSTX_ANT_CHANNEL                     ((UCHAR) 0)        // Channels on a single ANT module must be different
#define BCTX_ANT_CHANNEL                     ((UCHAR) 1)        // Channels on a single ANT module must be different


// other defines
#define BSC_PRECISION                             ((ULONG)1000)


static const UCHAR aucNetworkKey[] = ANTPLUS_NETWORK_KEY;

static void ProcessANTBSTXEvents(ANTPLUS_EVENT_RETURN* pstEvent_);
static void ProcessANTBCTXEvents(ANTPLUS_EVENT_RETURN* pstEvent_);
static void ProcessAntEvents(UCHAR* pucEventBuffer_);

//----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////
// main
//
// main function  
//
// Configures device simulator and BSC TX channel.
//
// \return: This function does not return. 
////////////////////////////////////////////////////////////////////////////
void main_bsbctx()
{
   UCHAR* pucRxBuffer;
   ANTPLUS_EVENT_RETURN stBSCEventStruct;



   // Main loop
   // Set network key. Do not send other commands
   // until after a response is recieved to this one.
   ANT_NetworkKey(ANTPLUS_NETWORK_NUMBER, aucNetworkKey);

   // Main loop
   while(TRUE)
   {
      usLowPowerMode = 0;//LPM1_bits;                       // nitialize the low power mode -  move to processor specific file and generic function
      
      pucRxBuffer = ANTInterface_Transaction();                // Check if any data has been recieved from serial
      
      if(pucRxBuffer)
      {
         if(BSTX_ChannelEvent(pucRxBuffer, &stBSCEventStruct))
            usLowPowerMode = 0;

         ProcessANTBSTXEvents(&stBSCEventStruct);

         if(BCTX_ChannelEvent(pucRxBuffer, &stBSCEventStruct))
            usLowPowerMode = 0;

         ProcessANTBCTXEvents(&stBSCEventStruct);
         
         ProcessAntEvents(pucRxBuffer);
      }
      
      _BIS_SR(usLowPowerMode);                              // Go to sleep if we can  -  move to processor specific file and generic function
   } 
   
} 


////////////////////////////////////////////////////////////////////////////
// ProcessANTBSRXEvents
//
// BSC Reciever event processor  
//
// Processes events recieved from BSC module.
//
// \return: N/A 
///////////////////////////////////////////////////////////////////////////
void ProcessANTBSTXEvents(ANTPLUS_EVENT_RETURN* pstEvent_)
{

   switch(pstEvent_->eEvent)
   {

      case ANTPLUS_EVENT_TRANSMIT:
      {
         IOBOARD_LED0_OUT &= ~IOBOARD_LED0_BIT;                // Turn ON LED
         printf("BS Transmit.\n");
         IOBOARD_LED0_OUT |= IOBOARD_LED0_BIT;                 // Turn OFF LED
         break;
      } 
      case ANTPLUS_EVENT_NONE:
      default:
      {
         break;
      }
   }
}


////////////////////////////////////////////////////////////////////////////
// ProcessANTBCRXEvents
//
// BSC Reciever event processor  
//
// Processes events recieved from BSC module.
//
// \return: N/A 
///////////////////////////////////////////////////////////////////////////
void ProcessANTBCTXEvents(ANTPLUS_EVENT_RETURN* pstEvent_)
{

   switch(pstEvent_->eEvent)
   {

      case ANTPLUS_EVENT_TRANSMIT:
      {
         IOBOARD_LED0_OUT &= ~IOBOARD_LED0_BIT;                // Turn ON LED
         printf("BC Transmit.\n");
         IOBOARD_LED0_OUT |= IOBOARD_LED0_BIT;                 // Turn OFF LED
         break;
      } 
      case ANTPLUS_EVENT_NONE:
      default:
      {
         break;
      }
   }
}


////////////////////////////////////////////////////////////////////////////
// ProcessAntEvents
//
// Generic ANT Event handling  
//
// \return: N/A 
///////////////////////////////////////////////////////////////////////////
void ProcessAntEvents(UCHAR* pucEventBuffer_)
{
   
   if(pucEventBuffer_)
   {
      UCHAR ucANTEvent = pucEventBuffer_[BUFFER_INDEX_MESG_ID];   
      
      switch( ucANTEvent )
      {
         case MESG_RESPONSE_EVENT_ID:
         {
            switch(pucEventBuffer_[BUFFER_INDEX_RESPONSE_CODE])
            {
               case EVENT_RX_SEARCH_TIMEOUT:
               {
                  IOBOARD_LED0_OUT |= IOBOARD_LED0_BIT;         
                  break;
               }
               case EVENT_TX:
               {
                  break;
               }
               
               case RESPONSE_NO_ERROR:
               {   
                  if (pucEventBuffer_[3] == MESG_OPEN_CHANNEL_ID)
                  {
                     UCHAR ucChannel = pucEventBuffer_[BUFFER_INDEX_CHANNEL_NUM] & 0x1F;
                     
                     // Once the BS channel is opened, open the BC channel
                     if(ucChannel == BSTX_ANT_CHANNEL)
                     {
                        IOBOARD_LED0_OUT &= ~IOBOARD_LED0_BIT; 
                        printf("BS Open.\n");
                        BCTX_Open(BCTX_ANT_CHANNEL,49,5);                                                // proceed with next channel init after response has been received
                     }
                     else
                     {
                        IOBOARD_LED0_OUT &= ~IOBOARD_LED0_BIT; 
                        printf("BC Open.\n");
                     }
                  }
                  else if (pucEventBuffer_[3] == MESG_CLOSE_CHANNEL_ID)
                  {
                  
                  }
                  else if (pucEventBuffer_[3] == MESG_NETWORK_KEY_ID)
                  {
                     //Once we get a response to the set network key
                     //command, start opening the BS channel
                     BSTX_Open(BSTX_ANT_CHANNEL, 49, 5);
                  }
                  break;
               }
            }
         }
      }
   }      
}








