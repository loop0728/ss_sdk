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

#ifndef __RGN_DEBUG_H__
#define __RGN_DEBUG_H__

//=============================================================================
// Defines
//=============================================================================
//=============================================================================
// struct
//=============================================================================
#define  bool   unsigned char
extern bool gbrgndbglv;
#define DRV_RGN_DEBUG   (gbrgndbglv&DRVRGNDBGLV)
#define DRV_RGN_HLDEBUG   (gbrgndbglv&HLRGNDBGLV)

#define DRVRGNERR(fmt, arg...)    CamOsPrintf(KERN_WARNING fmt, ##arg)
#define DRVRGNDBG(fmt, arg...)    
#define DRVRGNHLDBG(fmt, arg...)   
#define DRVRGNDBGERR(fmt, arg...) 
#define HALRGNDBGLV 0x1
#define DRVRGNDBGLV 0x2
#define HLRGNDBGLV 0x4  //high level

#define HAL_RGN_DEBUG   (gbrgndbglv&HALRGNDBGLV)
#define HAL_HLRGN_DEBUG   (gbrgndbglv&HLRGNDBGLV)
#define HALRGNERR(fmt, arg...) CamOsPrintf(KERN_WARNING fmt, ##arg) //CamOsDebug(fmt, ##arg)

#define HALRGNDBG(fmt, arg...)
#define HALHLRGNDBG(fmt, arg...)
#define HALRGNDBGERR(fmt, arg...)

//=============================================================================

//=============================================================================
#define RGN_IO_OFFSET 0x00000000

#endif //
/** @} */ // end of hvsp_group
