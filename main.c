/*
   Copyright 2012 Dynastream Innovations, Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "types.h"
#include "antinterface.h"
#include "antdefines.h"
#include "timer.h"
#include "system.h"
#include "config.h"
#include "ioboard.h"

volatile USHORT usLowPowerMode;                 // low power mode control

//----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////
// main
//
// main function  
//
// Configures device simulator
//
// \return: This function does not return. 
////////////////////////////////////////////////////////////////////////////
void main()
{
   System_DisableWatchdog();                    // Disable the watchdog
   __disable_interrupt();
   
   System_Init();                               // Setup the clock 
   Timer_Init();                                // Setup the timer
   
   Timer_DelayTime(50000);                      // delay for 500ms to allow DCO to settle

#if defined (USE_EXTERNAL_32KHZ)
   EXT_CLOCK_32KHZ_SEL |= EXT_CLOCK_32KHZ_BIT;  // Select ACLK out on P2.0
   EXT_CLOCK_32KHZ_DIR |= EXT_CLOCK_32KHZ_BIT;  // Set as output
#endif

   __enable_interrupt();                        // Enable global interrupts
   
   
   IOBOARD_LED0_SEL &= ~IOBOARD_LED0_BIT;   // Set as output
   IOBOARD_LED0_DIR |= IOBOARD_LED0_BIT;    // Set as output
   IOBOARD_LED0_OUT |= IOBOARD_LED0_BIT;    // Port select HI for SYNC serial

   while(1)
   {
       __delay_cycles(500000);
       IOBOARD_LED0_OUT ^= IOBOARD_LED0_BIT;
   }
   
   ANTInterface_Init();                         // Initialize ANT to serial interface

   main_bsbctx();                               // Run bike speed and bike cadence TX main thread - does not return.

} 
