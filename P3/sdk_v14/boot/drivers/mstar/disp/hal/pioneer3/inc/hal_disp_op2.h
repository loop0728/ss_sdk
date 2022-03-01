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

#ifndef _HAL_DISP_OP2_H_
#define _HAL_DISP_OP2_H_

//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  structure & Enum
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Prototype
//-------------------------------------------------------------------------------------------------

#ifdef _HAL_DISP_OP2_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE void HalDispSetSwReste(u8 u8Val, void *pCtx);
INTERFACE void HalDispSetFpllEn(u8 u8Val, void *pCtx);
INTERFACE void HalDispSetDacMux(u8 u8Val, void *pCtx);
INTERFACE void HalDispSetMaceSrc(bool bExtVideo, void *pCtx);
INTERFACE void HalDispSetPatGenMd(u8 u8Val, void *pCtx);
INTERFACE void HalDispSetTgenHtt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenVtt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenHsyncSt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenHsyncEnd(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenVsyncSt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenVsyncEnd(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenHfdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenHfdeEnd(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenVfdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenVfdeEnd(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenHdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenHdeEnd(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenVdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenVdeEnd(u16 u16Val, void *pCtx);;
INTERFACE void HalDispSetTgenDacHsyncSt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenDacHsyncEnd(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenDacHdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenDacHdeEnd(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenDacVdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetTgenDacVdeEnd(u16 u16Val, void *pCtx);
INTERFACE u16  HalDispGetTgenHtt(void *pCtx);
INTERFACE u16  HalDispGetTgenVtt(void *pCtx);
INTERFACE u16  HalDispGetTgenHsyncSt(void *pCtx);
INTERFACE u16  HalDispGetTgenHsyncEnd(void *pCtx);
INTERFACE u16  HalDispGetTgenHfdeSt(void *pCtx);
INTERFACE u16  HalDispGetTgenHfdeEnd(void *pCtx);
INTERFACE u16  HalDispGetTgenHdeSt(void *pCtx);
INTERFACE u16  HalDispGetTgenHdeEnd(void *pCtx);
INTERFACE u32  HalDispGetSynthSet(void *pCtx);
INTERFACE void HalDispSetFrameColor(u8 u8R, u8 u8G, u8 u8B, void *pCtx);
INTERFACE void HalDispSetFrameColorForce(u8 u8Val, void *pCtx);
INTERFACE void HalDispSetDispWinColor(u8 u8R, u8 u8G, u8 u8B, void *pCtx);
INTERFACE void HalDispSetDispWinColorForce(u8 u8Val, void *pCtx);
INTERFACE void HalDispSetDacTrimming(u16 u16R, u16 u16G, u16 u16B, void *pCtx);
INTERFACE void HalDispSetDacAffReset(u8 u8Val, void *pCtx);
INTERFACE void HalDispSetVgaHpdInit(void *pCtx);
INTERFACE void HalDispSetHdmitxSsc(u16 u16Step, u16 u16Span, void *pCtx);
INTERFACE void HalDispGetDacTriming(u16 *pu16R, u16 *pu16G, u16 *pu16B, void *pCtx);

// LCD
INTERFACE void HalDispSetLcdAffReset(u8 u8Val, void *pCtx);
INTERFACE void HalDispSetLcdFpllDly(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetLcdFpllRefSel(u16 u16Val, void *pCtx);

INTERFACE void HalDispSetHdmi2OdClkRate(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetDacSrcMux(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetHdmiSrcMux(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetLcdSrcMux(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetBt656SrcMux(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetDsiSrcMux(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetCmdqIntMask(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetMaceSrcSel(u16 u16Val, void *pCtx);
INTERFACE void HalDispSetMopWinMerge(u16 u16Val, void *pCtx);

INTERFACE void HalDispSetCmdqMux(u8 u8Val, void *pCtx);
//MCU lcd used
INTERFACE void HalDispSetClkDsiGateEn(u8 u8Val, void *pCtx);
INTERFACE void HalDispMcuLcdRefresh(u8 u8Val, void *pCtx);
INTERFACE void HalDispMcuLcdRest(u8 u8Val, void *pCtx);
INTERFACE void HalDispMcuLcdCmdqInit(void);

//Gop Blend
INTERFACE void HalDispSetGopBlend(u8 u8Val, void *pCtx);

#undef INTERFACE
#endif
