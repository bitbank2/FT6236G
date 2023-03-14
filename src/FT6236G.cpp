//
// FT62x6 capactive touch library
// Written by Larry Bank
//
// Copyright 2023 BitBank Software, Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//    http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//===========================================================================
#include "FT6236G.h"
//
// Initialize the library
// It only needs to initialize the I2C interface; the chip is ready
//
int FT6236G::init(int iSDA, int iSCL, bool bBitBang, uint32_t u32Speed)
{
    memset(&_bbi2c, 0, sizeof(_bbi2c));
    _bbi2c.bWire = !bBitBang; // use bit bang?
    _bbi2c.iSDA = iSDA;
    _bbi2c.iSCL = iSCL;
    #ifndef ARDUINO
    _bbi2c.iBus = 1; // default I2C bus on RPI is 1
    #endif
    I2CInit(&_bbi2c, u32Speed);
    return FT_SUCCESS;
} /* init() */

//
// Read the touch points
// returns 0 (none), or 1-2
//
int FT6236G::getSamples(TOUCHINFO *pTI)
{
uint8_t ucTemp[16];
int i, rc;
    
    if (!pTI)
       return FT_ERROR;

    rc = I2CReadRegister(&_bbi2c, _iAddr, TOUCH_REG_STATUS, ucTemp, 1); // read touch status
    if (rc == 0) { // something went wrong
        return FT_ERROR;
    }
    pTI->count = 0;
    i = ucTemp[0]; // number of touch points available
    if (i >= 1) { // get data
        rc = I2CReadRegister(&_bbi2c, _iAddr, TOUCH_REG_XH, ucTemp, 6*i); // read X+Y position(s)
        if ((ucTemp[0] & 0x40) == 0 && (ucTemp[2] & 0xf0) != 0xf0) { // finger is down
            pTI->x[0] = ((ucTemp[0] & 0xf) << 8) | ucTemp[1];
            pTI->y[0] = ((ucTemp[2] & 0xf) << 8) | ucTemp[3];
            // get touch pressure and area
            pTI->pressure[0] = ucTemp[4];
            pTI->area[0] = ucTemp[5];
            pTI->count++;
        }
        if (i > 1) { // get second point
            if ((ucTemp[6] & 0x40) == 0 && (ucTemp[8] & 0xf0) != 0xf0) { // finger is down
                pTI->x[1] = ((ucTemp[6] & 0xf) << 8) | ucTemp[7];
                pTI->y[1] = ((ucTemp[8] & 0xf) << 8) | ucTemp[9];
                // get touch pressure and area
                pTI->pressure[1] = ucTemp[10];
                pTI->area[1] = ucTemp[11];
                pTI->count++;
            }
        }
    } // if touch points available
    return FT_SUCCESS;
} /* getSamples() */

