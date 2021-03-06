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

#ifndef _HAL_PNL_H_
#define _HAL_PNL_H_

//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  structure & Enum
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Prototype
//-------------------------------------------------------------------------------------------------

#ifdef _HAL_PNL_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif


INTERFACE bool HalPnlGetLpllIdx(u32 u32Dclk, u16 *pu16Idx, bool bDsi);
INTERFACE u16  HalPnlGetLpllGain(u16 u16Idx, bool bDsi);
INTERFACE u16  HalPnlGetLpllDiv(u16 u16Idx, bool bDsi);
INTERFACE void HalPnlSetTTLPadMux(HalPnlOutputFormatBitMode_e enFmt, u16 u16Val);
INTERFACE void HalPnlSetSrgbPadMux(HalPnlOutputFormatBitMode_e enFmt, u16 u16Val);
INTERFACE void HalPnlSetBTPadMux(HalPnlLinkType_e eLinkType, u16 u16Val);
INTERFACE void HalPnlSetMipiDisPadMux(HalPnlMipiDsiLaneMode_e enLaneNum);
INTERFACE void HalPnlSetTtlPadCotnrol(u32 u32Ie, u32 u32Pe, u32 u32Ps, u32 u32Drv);
INTERFACE void HalPnlDumpLpllSetting(u16 u16Idx);
INTERFACE void HalPnlSetLpllSet(u32 u32LpllSet);
INTERFACE void HalPnlSetFrameColorEn(bool bEn, void *pCtx);
INTERFACE void HalPnlSetFrameColor(u16 u16R, u16 u16G, u16 u16B, void *pCtx);
INTERFACE void HalPnlSetVSyncSt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetVSyncEnd(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetVfdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetVfdeEnd(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetVdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetVdeEnd(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetVtt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetHSyncSt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetHSyncEnd(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetHfdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetHfdeEnd(u16 u16Va, void *pCtxl);
INTERFACE void HalPnlSetHdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetHdeEnd(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetHtt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetClkInv(bool bEn);
INTERFACE void HalPnlSetVsyncInv(bool bEn);
INTERFACE void HalPnlSetHsyncInv(bool bEn);
INTERFACE void HalPnlSetDeInv(bool bEn);
INTERFACE void HalPnlSetVsynRefMd(bool bEn);
INTERFACE void HalPnlW2BYTEMSK(u32 u32Reg, u16 u16Val, u16 u16Msk);
INTERFACE void HalPnlSetTgenExtHsEn(u8 u8Val, void *pCtx);
INTERFACE void HalPnlSetSwReste(u8 u8Val, void *pCtx);
INTERFACE void HalPnlSetFifoRest(u8 u8Val);
INTERFACE void HalPnlSetDacHsyncSt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetDacHsyncEnd(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetDacHdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetDacHdeEnd(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetDacVdeSt(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetDacVdeEnd(u16 u16Val, void *pCtx);
INTERFACE void HalPnlSetDitherEn(bool bEn, void *pCtx);
INTERFACE void HalPnlSetRgbMode(HalPnlOutputFormatBitMode_e enFmt, void *pCtx);
INTERFACE void HalPnlSetDispToDsiMd(u8 u8Val, void *pCtx);
INTERFACE void HalPnlSetLpllSkew(u16 u16Val);
INTERFACE void HalPnlSetRgbSwap(HalPnlRgbSwapType_e enChR, HalPnlRgbSwapType_e enChG, HalPnlRgbSwapType_e enChB, void *pCtx);
INTERFACE void HalPnlSetRgbMlSwap(u8 u8Val, void *pCtx);
INTERFACE void HalPnlSetSscEn(u8 u8Val);
INTERFACE void HalPnlSetSscSpan(u16 u16Val);
INTERFACE void HalPnlSetSscStep(u16 u16Val);
INTERFACE u32  HalPnlGetLpllSet(void);
INTERFACE u32  HalPnlGetRevision(void);

// LCD / LCD_MISC
INTERFACE void HalPnlSetLcdRgbVSyncWidth(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbVBp(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbVPorchTotal(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbVActive(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbHSyncWidth(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbHBp(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbHPorchTotal(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbHActive(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbFramePixelCnt(u32 u32Cnt);
INTERFACE void HalPnlSetLcdRgbDeltaMode(HalPnlRgbDeltaMode_e eOddLine, HalPnlRgbDeltaMode_e eEvenLine);
INTERFACE void HalPnlSetLcdRgbDtype(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbEn(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbVSyncPol(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbHSyncPol(u16 u16Val);
INTERFACE void HalPnlSetLcdMiscTgenSyncEn(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbVsyncPol(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbHsyncPol(u16 u16Val);
INTERFACE void HalPnlSetLcdRgbClkPol(u16 u16Val);
INTERFACE void HalPnlSetLcdDisp1Used(u16 u16Val);
INTERFACE void HalPnlSetLcdDisp1Type(u16 u16Val);
INTERFACE void HalPnlSetLcdBtEncMode(u16 u16Val);
INTERFACE void HalPnlSetLcdBtClip(u16 u16Val);
INTERFACE void HalPnlSetLcdBtEncModeEn(u16 u16Val);
INTERFACE void HalPnlSetLcdBt601En(u16 u16Val);
INTERFACE void HalPnlSetLcdAffReset(u8 u8Val);
INTERFACE u16 HalPnlGetLcdInit(void);

//MCU LCD (intel8080 or Motorola 8068)
INTERFACE void HalPnlSetMCUPadMux(HalPnlOutputFormatBitMode_e busWidth);
INTERFACE void HalPnlMCUSetBUS(HalPnlOutputFormatBitMode_e busWidth, HalPnlMcuDataBusCfg databus);
INTERFACE void HalPnlMCUCtl(void);
INTERFACE void HalPnlMCUSendCmd(void);
INTERFACE void HalPnlSetMCUIDXCmdNum( u8 u8TXNum);
INTERFACE void HalPnlSetMCUAutoConfigIDXCmd(u32 u32Val, u8 u8TXNum, bool bIdxCmd);
INTERFACE void HalPnlSetMCUType(HalPnlMcuType enMcuSys);
INTERFACE void HalPnlSetMCUPHA(bool bPHA);
INTERFACE void HalPnlSetMCUPOR(bool bPOR);
INTERFACE void HalPnlSetMCUIdxCmdTotalNum(u8 u8Num);
INTERFACE void HalPnlSetMCUCycleCnt(u16 u16RSLeadCs, u16 u16CSLeadRW, u16 u16RW_Cnt);

// Mipi Dsi
INTERFACE bool HalPnlGetTtlMipiDsiSupported(void);

INTERFACE void HalPnlInitMipiDsiDphy(void);
INTERFACE void HalPnlSetMipiDsiPadOutSel(HalPnlMipiDsiLaneMode_e enLaneMode);
INTERFACE void HalPnlResetMipiDsi(void);
INTERFACE void HalPnlEnableMipiDsiClk(void);
INTERFACE void HalPnlDisableMipiDsiClk(void);
INTERFACE void HalPnlSetMipiDsiLaneNum(HalPnlMipiDsiLaneMode_e enLaneMode);
INTERFACE void HalPnlSetMipiDsiCtrlMode(HalPnlMipiDsiCtrlMode_e enCtrlMode);
INTERFACE bool HalPnlGetMipiDsiClkHsMode(void);
INTERFACE void HalPnlSetMpiDsiClkHsMode(bool bEn);
INTERFACE bool HalPnlGetMipiDsiShortPacket(u8 u8ReadBackCount, u8 u8RegAddr);
INTERFACE bool HalPnlSetMipiDsiShortPacket(HalPnlMipiDsiPacketType_e enPacketType, u8 u8Count, u8 u8Cmd, u8 *pu8ParamList);
INTERFACE bool HalPnlSetMipiDsiLongPacket(HalPnlMipiDsiPacketType_e enPacketType, u8 u8Count, u8 u8Cmd, u8 *pu8ParamList);
INTERFACE bool HalPnlSetMipiDsiPhyTimConfig(HalPnlMipiDsiConfig_t *pstMipiDsiCfg);
INTERFACE bool HalPnlSetMipiDsiVideoTimingConfig(HalPnlMipiDsiConfig_t *pstMipiDsiCfg, HalPnlHwMipiDsiConfig_t *pstHwCfg);
INTERFACE void HalPnlGetMipiDsiReg(u32 u32Addr, u32 *pu32Val);
INTERFACE void HalPnlSetMipiDsiChPolarity(u8 *pu8ChPol);
INTERFACE void HalPnlSetMipiDsiChSel(HalPnlMipiDsiConfig_t *pstMipiDisCfg);

INTERFACE void HalPnlSetMipiDsiPatGen(void);

INTERFACE void HalPnlSetClkHdmi(bool bEn, u32 u32ClkRate);
INTERFACE void HalPnlGetClkHdmi(bool *pbEn, u32 *pu32ClkRate);
INTERFACE void HalPnlSetClkDac(bool bEn, u32 u32ClkRate);
INTERFACE void HalPnlGetClkDac(bool *pbEn, u32 *pu32ClkRate);
INTERFACE void HalPnlSetClkMipiDsiAbp(bool bEn, u32 u32ClkRate);
INTERFACE void HalPnlGetClkMipiDsiAbp(bool *pbEn, u32 *pu32ClkRate);
INTERFACE void HalPnlSetClkScPixel(bool bEn, u32 u32ClkRate);
INTERFACE void HalPnlGetClkScPixel(bool *pbEn, u32 *pu32ClkRate);
INTERFACE void HalPnlSetClkMipiDsi(bool bEn, u32 u32ClkRate);
INTERFACE void HalPnlGetClkMipiDsi(bool *pbEn, u32 *pu32ClkRate);

#undef INTERFACE
#endif
