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

#include "ioboard.h"
#include "config.h"

void IOBoard_Init()
{
   // Initialize the LED's 
   IOBOARD_LED0_SEL &= ~IOBOARD_LED0_BIT;   // Set as output
   IOBOARD_LED0_DIR |= IOBOARD_LED0_BIT;    // Set as output
   IOBOARD_LED0_OUT |= IOBOARD_LED0_BIT;    // Port select HI for SYNC serial
}