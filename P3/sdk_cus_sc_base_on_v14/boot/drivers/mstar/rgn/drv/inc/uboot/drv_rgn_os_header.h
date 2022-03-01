/* SigmaStar trade secret */
/* Copyright (c) [2019~2020] SigmaStar Technology.
All rights reserved.

Unless otherwise stipulated in writing, any and all information contained
herein regardless in any format shall remain the sole proprietary of
SigmaStar and be kept in strict confidence
(SigmaStar Confidential Information) by the recipient.
Any unauthorized act including without limitation unauthorized disclosure,
copying, use, reproduction, sale, distribution, modification, disassembling,
reverse engineering and compiling of the contents of SigmaStar Confidential
Information is unlawful and strictly prohibited. SigmaStar hereby reserves the
rights to any and all damages, losses, costs and expenses resulting therefrom.
*/

#ifndef __DRV_RGN_OS_HEADER_H__
#define __DRV_RGN_OS_HEADER_H__

#include <common.h>
#include <command.h>
#include <config.h>
#include <malloc.h>
#include <stdlib.h>


//=============================================================================
//  Defines & Macro
//=============================================================================
#ifndef NULL
#define NULL 0
#endif

typedef unsigned char       u8;
typedef signed   char       s8;
typedef unsigned short      u16;
typedef signed   short      s16;
typedef unsigned int        u32;
typedef signed   int        s32;
typedef unsigned long long  u64;
typedef signed   long long  s64;

#define CamOsMemAlloc       malloc
#define CamOsMemRelease     free
#define CamOsPanic(x)


//=============================================================================
//  Structure & Emu
//=============================================================================

#define RGN_CMDQ_ONESHOTINIT(x)
#define RGN_CMDQ_ONESHOTDEINIT(x)
#define RGN_CMDQ_ONESHOTLOCK(x)
#define RGN_CMDQ_ONESHOTUNLOCK(x)

typedef struct
{
    char used;
}DrvRgnOsSemConfig_t;

#endif
