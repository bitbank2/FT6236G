//
// FT62x6 capacitive touch library
// written by Larry Bank
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

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#endif
#include <BitBang_I2C.h>

#ifndef __FT6236G__
#define __FT6236G__

#define FT_SUCCESS 0
#define FT_ERROR -1

#define TOUCH_REG_STATUS 0x02
#define TOUCH_REG_XH 0x03
#define TOUCH_REG_XL 0x04
#define TOUCH_REG_YH 0x05
#define TOUCH_REG_YL 0x06
#define TOUCH_REG_WEIGHT 0x07
#define TOUCH_REG_AREA 0x08
// register offset to info for the second touch point
#define PT2_OFFSET 6
typedef struct _fttouchinfo
{
  int count;
  uint16_t x[2], y[2];
  uint8_t pressure[2], area[2];
} TOUCHINFO;

class FT6236G
{
public:
    FT6236G() {_iAddr = 0x38;}
    ~FT6236G() {}

    int init(int iSDA, int iSCL, bool iBitBang, uint32_t u32Speed);
    int getSamples(TOUCHINFO *pTI);
    
private:
    int _iAddr;
    BBI2C _bbi2c;
}; // class FT6236G

#endif // __FT6236G__
