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

#define _HAL_DISP_MOP_C_

#include "drv_disp_os.h"
#include "hal_disp_common.h"
#include "disp_debug.h"
#include "hal_disp_util.h"
#include "hal_disp_reg.h"
#include "hal_disp_chip.h"
#include "hal_disp_st.h"
#include "hal_disp_mop.h"
#include "hal_disp.h"


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------
#define HAL_DISP_MOP_MIU_BUS 4
#define HAL_DISP_MOP_DBLBF_WRITE_MD 0
#define HAL_DISP_MOP_FORCE_WRITE_MD 1

#define HAL_DISP_MOP_WRITE_MD HAL_DISP_MOP_DBLBF_WRITE_MD

//-------------------------------------------------------------------------------------------------
//  structure
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
//  Variable
//-------------------------------------------------------------------------------------------------

//SW shadow
//bk 0x1406
//u16 u16Mopg01SwShadowVal[E_HAL_DISP_LAYER_MOPG01_SHADOW_NUM];
//u32 u16Mopg01SwShadowReg[E_HAL_DISP_LAYER_MOPG01_SHADOW_NUM];

//bk 0x1407
//u16 u16Mopg02SwShadowVal[E_HAL_DISP_LAYER_MOPG02_SHADOW_NUM];
//u32 u16Mopg02SwShadowReg[E_HAL_DISP_LAYER_MOPG02_SHADOW_NUM];

//bk 0x1408
//u16 u16MopsSwShadowVal[E_HAL_DISP_LAYER_MOPS_SHADOW_NUM];
//u32 u16MopsSwShadowReg[E_HAL_DISP_LAYER_MOPS_SHADOW_NUM];

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

/*u32 _HalDispMopgGwinRegBkMap(HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId)
{
    u32 u32RegBk;

    if(eMopId==E_HAL_DISP_MOPID_00)
    {
        switch(eMopgId)
        {
            case E_HAL_DISP_MOPG_ID_00:
            case E_HAL_DISP_MOPG_ID_01:
            case E_HAL_DISP_MOPG_ID_02:
            case E_HAL_DISP_MOPG_ID_03:
            case E_HAL_DISP_MOPG_ID_04:
            case E_HAL_DISP_MOPG_ID_05:
            case E_HAL_DISP_MOPG_ID_06:
            case E_HAL_DISP_MOPG_ID_07:
                u32RegBk = REG_DISP_MOPG_BK01_BASE;
                break;
            case E_HAL_DISP_MOPG_ID_08:
            case E_HAL_DISP_MOPG_ID_09:
            case E_HAL_DISP_MOPG_ID_10:
            case E_HAL_DISP_MOPG_ID_11:
            case E_HAL_DISP_MOPG_ID_12:
            case E_HAL_DISP_MOPG_ID_13:
            case E_HAL_DISP_MOPG_ID_14:
            case E_HAL_DISP_MOPG_ID_15:
                u32RegBk = REG_DISP_MOPG_BK02_BASE;
                break;
            default:
                DISP_ERR("[HALMOP]%s %d, Mopg ID %d not support\n", __FUNCTION__, __LINE__,eMopgId);
                u32RegBk = REG_DISP_MOPG_BK01_BASE;
                break;
        }
    }
    else if(eMopId==E_HAL_DISP_MOPID_01)
    {
        switch(eMopgId)
        {
            case E_HAL_DISP_MOPG_ID_00:
            case E_HAL_DISP_MOPG_ID_01:
            case E_HAL_DISP_MOPG_ID_02:
            case E_HAL_DISP_MOPG_ID_03:
            case E_HAL_DISP_MOPG_ID_04:
            case E_HAL_DISP_MOPG_ID_05:
            case E_HAL_DISP_MOPG_ID_06:
            case E_HAL_DISP_MOPG_ID_07:
                u32RegBk = REG_DISP_MOPG_BK11_BASE;
                break;
            case E_HAL_DISP_MOPG_ID_08:
            case E_HAL_DISP_MOPG_ID_09:
            case E_HAL_DISP_MOPG_ID_10:
            case E_HAL_DISP_MOPG_ID_11:
            case E_HAL_DISP_MOPG_ID_12:
            case E_HAL_DISP_MOPG_ID_13:
            case E_HAL_DISP_MOPG_ID_14:
            case E_HAL_DISP_MOPG_ID_15:
                u32RegBk = REG_DISP_MOPG_BK12_BASE;
                break;
            default:
                DISP_ERR("[HALMOP]%s %d, Mopg ID %d not support\n", __FUNCTION__, __LINE__,eMopgId);
                u32RegBk = REG_DISP_MOPG_BK01_BASE;
                break;
        }
    }
    else
    {
        DISP_ERR("[HALMOP]%s %d, Mop ID %d not support\n", __FUNCTION__, __LINE__,eMopId);
    }

    return u32RegBk;
}

u32 _HalDispMopgGwinRegShiftMap(HalDispMopgGwinId_e eMopgId)
{
    u32 u32GeinRegShift;

    switch(eMopgId)
    {
        case E_HAL_DISP_MOPG_ID_00:
        case E_HAL_DISP_MOPG_ID_08:
            u32GeinRegShift = 0x00;
            break;
        case E_HAL_DISP_MOPG_ID_01:
        case E_HAL_DISP_MOPG_ID_09:
            u32GeinRegShift = 0x20;
            break;
        case E_HAL_DISP_MOPG_ID_02:
        case E_HAL_DISP_MOPG_ID_10:
            u32GeinRegShift = 0x40;
            break;
        case E_HAL_DISP_MOPG_ID_03:
        case E_HAL_DISP_MOPG_ID_11:
            u32GeinRegShift = 0x60;
            break;
        case E_HAL_DISP_MOPG_ID_04:
        case E_HAL_DISP_MOPG_ID_12:
            u32GeinRegShift = 0x80;
            break;
        case E_HAL_DISP_MOPG_ID_05:
        case E_HAL_DISP_MOPG_ID_13:
            u32GeinRegShift = 0xA0;
            break;
        case E_HAL_DISP_MOPG_ID_06:
        case E_HAL_DISP_MOPG_ID_14:
            u32GeinRegShift = 0xC0;
            break;
        case E_HAL_DISP_MOPG_ID_07:
        case E_HAL_DISP_MOPG_ID_15:
            u32GeinRegShift = 0xE0;
            break;
        default:
            DISP_ERR("[HALMOP]%s %d, Mopg ID %d not support\n", __FUNCTION__, __LINE__,eMopgId);
            u32GeinRegShift = 0x00;
            break;
    }
    return u32GeinRegShift;
}

void _HalDispMopRotDbBfWrWithoutCmdq(void *pCtx, HalDispMopId_e eMopId, HalDispMopRotId_e eMopRotId)
{
    u16 u16RegVal;
    u32 Mop_Reg_Base = 0;
    void *pCmdqCtx = NULL;

    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_01_L:
                                                     REG_DISP_MOP_ROT_BK0_01_L;

    u16RegVal = (eMopRotId == E_HAL_DISP_MOPROT_ROT0_ID) ? DISP_BIT2:
                (eMopRotId == E_HAL_DISP_MOPROT_ROT1_ID) ? DISP_BIT3:
                                                           DISP_BIT2;

    if(pCmdqCtx)
    {
        if(HAL_DISP_MOP_WRITE_MD == HAL_DISP_MOP_DBLBF_WRITE_MD)
        {
            HalDispUtilityW2BYTEMSKDirect(Mop_Reg_Base, u16RegVal, u16RegVal, pCmdqCtx);
            HalDispUtilityW2BYTEMSKDirect(Mop_Reg_Base, 0, u16RegVal, pCmdqCtx);
        }
    }
}


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
///MOPG
void HalDispMopgSwReset(HalDispMopId_e eMopId, void *pCmdq)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    Mopg_Gwin_Reg_BK = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPG_BK10_BASE:
                                                         REG_DISP_MOPG_BK00_BASE;
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK10_BASE) ? REG_DISP_MOPG_BK10_00_L:
                                                                         REG_DISP_MOPG_BK00_00_L;
    HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_Base, 0x0001, 0x0001, pCmdq);
    HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_Base, 0x0000, 0x0001, pCmdq);
}

void HalDispMopgSetAutoStretchWinSizeEn(void *pCtx, HalDispMopId_e eMopId, bool bEnAuto)//0: use reg_gw_hsize/vsize; 1: use display size
{
    void *pCmdqCtx = NULL;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mopg_Gwin_Reg_BK = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPG_BK10_BASE:
                                                         REG_DISP_MOPG_BK00_BASE;
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK10_BASE) ? REG_DISP_MOPG_BK10_01_L:
                                                                         REG_DISP_MOPG_BK00_01_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base, bEnAuto ? (DISP_BIT11|DISP_BIT10) : 0, (DISP_BIT11|DISP_BIT10), pCmdqCtx);//bit11:auto blanking. 0:use reg h15; 1:use display blanking;bit10:auto stretch window
    }
}

void HalDispMopgSetStretchWinSize(void *pCtx, HalDispMopId_e eMopId, u16 u16Width, u16 u16Height)
{
    void *pCmdqCtx = NULL;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Base_gwh = 0;
    u32 Mopg_Gwin_Reg_Base_gwv = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mopg_Gwin_Reg_BK = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPG_BK10_BASE:
                                                         REG_DISP_MOPG_BK00_BASE;
    Mopg_Gwin_Reg_Base_gwh = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK10_BASE) ? REG_DISP_MOPG_BK10_07_L:
                                                                             REG_DISP_MOPG_BK00_07_L;
    Mopg_Gwin_Reg_Base_gwv = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK10_BASE) ? REG_DISP_MOPG_BK10_08_L:
                                                                             REG_DISP_MOPG_BK00_08_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base_gwh, u16Width, 0x1FFF, pCmdqCtx);//reg_gw_hsize
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base_gwv, u16Height, 0x1FFF, pCmdqCtx);//reg_gw_vsize
    }
}

void HalDispMopgSetHextSize(void *pCtx, HalDispMopId_e eMopId, u16 u16Hext)
{
    void *pCmdqCtx = NULL;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mopg_Gwin_Reg_BK = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPG_BK10_BASE:
                                                         REG_DISP_MOPG_BK00_BASE;
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK10_BASE) ? REG_DISP_MOPG_BK10_15_L:
                                                                         REG_DISP_MOPG_BK00_15_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base, u16Hext, 0x1FFF, pCmdqCtx);//reg_gw_hsize
    }
}

void HalDispMopgSetPipeDelay(void *pCtx, HalDispMopId_e eMopId, u8 u8PipeDelay)
{
    void *pCmdqCtx = NULL;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mopg_Gwin_Reg_BK = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPG_BK10_BASE:
                                                         REG_DISP_MOPG_BK00_BASE;
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK10_BASE) ? REG_DISP_MOPG_BK10_03_L:
                                                                         REG_DISP_MOPG_BK00_03_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base, u8PipeDelay, 0x001F, pCmdqCtx);//reg_pipe_delay
    }
}

void HalDispMopgInit(void *pCtx)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    HalDispMopId_e eMopId;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    for(eMopId = E_HAL_DISP_MOPID_00; eMopId < E_HAL_DISP_MOP_NUM; eMopId++)
    {
        Mopg_Gwin_Reg_BK = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPG_BK10_BASE:
                                                             REG_DISP_MOPG_BK00_BASE;

        HalDispMopgSwReset(eMopId, pCmdqCtx);
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x01)*2, DISP_BIT8, DISP_BIT8, pCmdqCtx);//clk_miu. 0:use free run; 1:use gated clock
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x01)*2, DISP_BIT9, DISP_BIT9, pCmdqCtx);//clk_gop. 0:use free run; 1:use gated clock
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x01)*2, DISP_BIT10, DISP_BIT10, pCmdqCtx);//auto stretch win. 0:use reg h8; 1:use display blanking
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x01)*2, DISP_BIT11, DISP_BIT11, pCmdqCtx);//auto blanking. 0:use reg h15; 1:use display blanking
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x03)*2, 0x0A, 0x001F, pCmdqCtx);//set pipe delay (default=0xA)
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x04)*2, 0xF8, 0x00FF, pCmdqCtx);//h04 [7:0]ymd_thd
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x05)*2, 0xD0, 0x00FF, pCmdqCtx);//h05 [7:0]cdma_thd; default=0xf8, use 0xd0 for patch
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x06)*2, 0xF0, 0x00FF, pCmdqCtx);//h06 Luma DMA priority [7]yhp_en [6:0] yhp_thd
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x0B)*2, 0xF0, 0x00FF, pCmdqCtx);//h0b Chroma DMA priority [7]yhp_en [6:0] yhp_thd
        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x15)*2, 0x80, 0x1FFF, pCmdqCtx);//h15 [12:0]gw_hext

        HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x40)*2, 0x0689, 0x07FF, pCmdqCtx);//h40 set 4tap

        if(HAL_DISP_MOP_WRITE_MD == HAL_DISP_MOP_FORCE_WRITE_MD)
        {
            HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x7F)*2, DISP_BIT9, DISP_BIT9, pCmdqCtx);//set force write or not
        }
        else
        {
            HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x7F)*2, DISP_BIT8, DISP_BIT8, pCmdqCtx);
            HalDispUtilityW2BYTEMSKDirect(Mopg_Gwin_Reg_BK + (0x7F)*2, DISP_BIT8, 0, pCmdqCtx);
        }
    }
}

void HalDispMopgGwinEn(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, bool bEn)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_00_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_00_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_00_L:
                                                                         REG_DISP_MOPG_BK01_00_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, bEn ? DISP_BIT0 : 0, DISP_BIT0, pCmdqCtx);//reg_pipe_delay
    }
}

void HalDispMopgSetYAddr(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    u32 Mopg_Gwin_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_02_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_02_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_02_L:
                                                                         REG_DISP_MOPG_BK01_02_L;
    Mopg_Gwin_Reg_Base2 = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_03_L:
                          (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_03_L:
                          (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_03_L:
                                                                          REG_DISP_MOPG_BK01_03_L;
    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base2 + Mopg_Gwin_Reg_Shift, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopgSetAddr16Offset(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, u8 u8Offset)
{
    u32 u32RegVal;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    //u32 u32RegForSwShd = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_01_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_01_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_01_L:
                                                                         REG_DISP_MOPG_BK01_01_L;
    u32RegVal = (u8Offset<<9);

    //u32RegForSwShd = _HalDispMopgGwinRegSwShadowMap(eMopgId);

    //_HalMopSwShadowHandler(Mopg_Gwin_Reg_BK, u32RegForSwShd, (u32RegVal & 0x1E00), 0x1E00);

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, (u32RegVal & 0x1E00), 0x1E00, pCmdqCtx);
    }
}

void HalDispMopgSetCAddr(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    u32 Mopg_Gwin_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_04_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_04_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_04_L:
                                                                         REG_DISP_MOPG_BK01_04_L;
    Mopg_Gwin_Reg_Base2 = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_05_L:
                          (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_05_L:
                          (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_05_L:
                                                                          REG_DISP_MOPG_BK01_05_L;
    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base2 + Mopg_Gwin_Reg_Shift, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopgSetGwinParam(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, u16 u16Hst, u16 u16Vst, u16 u16Width, u16 u16Height)
{
    u16 u16Hend;
    u16 u16Vend;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Hst_Base = 0;
    u32 Mopg_Gwin_Reg_Hend_Base = 0;
    u32 Mopg_Gwin_Reg_Vst_Base = 0;
    u32 Mopg_Gwin_Reg_Vend_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Hst_Base  = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_06_L:
                              (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_06_L:
                              (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_06_L:
                                                                              REG_DISP_MOPG_BK01_06_L;
    Mopg_Gwin_Reg_Hend_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_07_L:
                              (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_07_L:
                              (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_07_L:
                                                                              REG_DISP_MOPG_BK01_07_L;
    Mopg_Gwin_Reg_Vst_Base  = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_08_L:
                              (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_08_L:
                              (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_08_L:
                                                                              REG_DISP_MOPG_BK01_08_L;
    Mopg_Gwin_Reg_Vend_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_09_L:
                              (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_09_L:
                              (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_09_L:
                                                                              REG_DISP_MOPG_BK01_09_L;
    u16Hend = u16Hst + u16Width -1;
    u16Vend = u16Vst + u16Height -1;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Hst_Base  + Mopg_Gwin_Reg_Shift, u16Hst,  0x1FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Hend_Base + Mopg_Gwin_Reg_Shift, u16Hend, 0x1FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Vst_Base  + Mopg_Gwin_Reg_Shift, u16Vst,  0x1FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Vend_Base + Mopg_Gwin_Reg_Shift, u16Vend, 0x1FFF, pCmdqCtx);
    }
}

void HalDispMopgSetPitch(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, u16 u16Pitch)
{
    u16 u16RegVal;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_0A_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_0A_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_0A_L:
                                                                         REG_DISP_MOPG_BK01_0A_L;
    u16RegVal = u16Pitch >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, u16RegVal, 0x1FFF, pCmdqCtx);
    }
}

void HalDispMopgSetSourceParam(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, u16 u16SrcWidth, u16 u16SrcHeight)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_SrcWidth_Base = 0;
    u32 Mopg_Gwin_Reg_SrcHeight_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_SrcWidth_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_0B_L:
                                  (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_0B_L:
                                  (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_0B_L:
                                                                                  REG_DISP_MOPG_BK01_0B_L;
    Mopg_Gwin_Reg_SrcHeight_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_0C_L:
                                   (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_0C_L:
                                   (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_0C_L:
                                                                                   REG_DISP_MOPG_BK01_0C_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_SrcWidth_Base  + Mopg_Gwin_Reg_Shift, (u16SrcWidth-1),  0x1FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_SrcHeight_Base + Mopg_Gwin_Reg_Shift, (u16SrcHeight-1), 0x1FFF, pCmdqCtx);
    }
}

void HalDispMopgSetHScaleFac(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, u16 u16HRatio)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_0D_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_0D_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_0D_L:
                                                                         REG_DISP_MOPG_BK01_0D_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, u16HRatio,  0x1FFF, pCmdqCtx);
    }
}

void HalDispMopgSetVScaleFac(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, u16 u16VRatio)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_0E_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_0E_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_0E_L:
                                                                         REG_DISP_MOPG_BK01_0E_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, u16VRatio,  0x1FFF, pCmdqCtx);
    }
}

void HalDispMopgSetLineBufStr(void *pCtx, HalDispMopId_e eMopId, HalDispMopgGwinId_e eMopgId, u16 u16GwinHstr, u8 u8WinPri)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    u16 u16RegVal = 0;
    //u32 u32RegForSwShd = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopId, eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK02_BASE) ? REG_DISP_MOPG_BK02_01_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK11_BASE) ? REG_DISP_MOPG_BK11_01_L:
                         (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK12_BASE) ? REG_DISP_MOPG_BK12_01_L:
                                                                         REG_DISP_MOPG_BK01_01_L;

    //u32RegForSwShd = _HalDispMopgGwinRegSwShadowMap(eMopgId);
    if(u8WinPri==0)
    {
        u16RegVal=0;
    }
    else
    {
        u16RegVal = ((u16GwinHstr>>3) + 2*u8WinPri) & 0xFF;//lb_str = gwin_hstr/8 + 2*gwin_priority; gwin_priority is the order of the position of display(from left on) 0~15
    }

    //_HalMopSwShadowHandler(Mopg_Gwin_Reg_BK, u32RegForSwShd, u16RegVal, 0x00FF);
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, u16RegVal,  0x00FF, pCmdqCtx);
    }
}
*/

///MOPS
void _HalDispMopSetDbBfWr(bool bEn, void *pCmdqCtx)
{
    HalDispUtilityW2BYTEMSKDirect(REG_DISP_MOPS_BK0_01_L, bEn, 0x1, pCmdqCtx);
    HalDispUtilityW2BYTEMSKDirect(REG_DISP_MOPS_HVSP_60_L, bEn ? DISP_BIT7 : 0, DISP_BIT7, pCmdqCtx);
}

void HalDispMopsSwReset(HalDispMopId_e eMopId, void *pCmdq)
{
    //u32 Mops_Gwin_Reg_BK = 0;
    u32 Mops_Gwin_Reg_Base = 0;
    //Mops_Gwin_Reg_BK = REG_DISP_MOPS_BK0_BASE;
    Mops_Gwin_Reg_Base = REG_DISP_MOPS_BK0_00_L;
    HalDispUtilityW2BYTEMSKDirect(Mops_Gwin_Reg_Base, 0x0001, 0x0001, pCmdq);
    HalDispUtilityW2BYTEMSKDirect(Mops_Gwin_Reg_Base, 0x0000, 0x0001, pCmdq);
}

void HalDispMopsSetColorFmt(void *pCtx, HalDispMopId_e eMopId, HalDispPixelFormat_e eFmt)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Reg_Base = 0;
    u32 Mops_Reg_Base2 = 0;
    u16 u16Val_02 = 0;
    u16 u16Val_03 = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Reg_Base = REG_DISP_MOPS_BK0_02_L;
    Mops_Reg_Base2 = REG_DISP_MOPS_BK0_03_L;

    switch(eFmt)
    {
        case E_HAL_DISP_PIXEL_FRAME_YUV422_YUYV:
            u16Val_02 = 0x0E80;
            u16Val_03 = 0;
            break;
        case E_HAL_DISP_PIXEL_FRAME_ARGB8888:
            u16Val_02 = 0x0C00;
            u16Val_03 = 0xA100;
            break;
        case E_HAL_DISP_PIXEL_FRAME_YUV_MST_420:
        case E_HAL_DISP_PIXEL_FRAME_YUV_SEMIPLANAR_420:
        default: //set yuv420
            u16Val_02 = 0x0204;
            u16Val_03 = 0;
            break;
    }

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Reg_Base, u16Val_02, 0xFFFF, pCmdqCtx);//reg_gw_hsize
        HalDispUtilityW2BYTEMSK(Mops_Reg_Base2, u16Val_03, 0xFFFF, pCmdqCtx);//reg_gw_hsize
    }
}

void HalDispMopsSetAutoStretchWinSizeEn(void *pCtx, HalDispMopId_e eMopId, bool bEnAuto)//0: use reg_gw_hsize/vsize; 1: use display size
{
    /*void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_BK0_01_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, bEnAuto ? (DISP_BIT11|DISP_BIT10) : 0, (DISP_BIT11|DISP_BIT10), pCmdqCtx);//bit11:auto blanking. 0:use reg h15; 1:use display blanking;bit10:auto stretch window
    }*/

}

void HalDispMopsSetStretchWinSize(void *pCtx, HalDispMopId_e eMopId, u16 u16Width, u16 u16Height)
{
/*    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Width_Reg_Base = 0;
    u32 Mops_Gwin_Height_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Width_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_07_L:
                                                                 REG_DISP_MOPS_BK0_07_L;

    Mops_Gwin_Height_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_08_L:
                                                                  REG_DISP_MOPS_BK0_08_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Width_Reg_Base, u16Width, 0x1FFF, pCmdqCtx);//reg_gw_hsize
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Height_Reg_Base, u16Height, 0x1FFF, pCmdqCtx);//reg_gw_vsize
    }*/
}

void HalDispMopsSetHextSize(void *pCtx, HalDispMopId_e eMopId, u16 u16Hext)
{
/*    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Width_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Width_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_15_L:
                                                                 REG_DISP_MOPS_BK0_15_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Width_Reg_Base, u16Hext, 0x1FFF, pCmdqCtx);//reg_gw_hsize
    }*/
}

void HalDispMopsSetPipeDelay(void *pCtx, HalDispMopId_e eMopId, u8 u8PipeDelay)
{
/*    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_03_L:
                                                           REG_DISP_MOPS_BK0_03_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, u8PipeDelay, 0x001F, pCmdqCtx);//reg_pipe_delay
    }*/
}

void HalDispMopsInit(void *pCtx)
{
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    //set default YUV420
    //HalDispUtilityW2BYTEMSKDirect(REG_DISP_MOPS_BK0_02_L, 0x0204, 0xFFFF, pCmdqCtx);
    HalDispUtilityW2BYTEMSKDirect(REG_DISP_MOPS_BK0_03_L, 0, 0xFFFF, pCmdqCtx);
    //req len/thd
    HalDispUtilityW2BYTEMSKDirect(REG_DISP_MOPS_BK0_21_L, 0x2220, 0xFFFF, pCmdqCtx);
    HalDispUtilityW2BYTEMSKDirect(REG_DISP_MOPS_BK0_22_L, 0x2220, 0xFFFF, pCmdqCtx);
    HalDispUtilityW2BYTEMSKDirect(REG_DISP_MOPS_BK0_23_L, 0x3E3E, 0xFFFF, pCmdqCtx);
    HalDispUtilityW2BYTEMSKDirect(REG_DISP_MOPS_BK0_24_L, 0x007C, 0x00FF, pCmdqCtx);

    if(HAL_DISP_MOP_WRITE_MD == HAL_DISP_MOP_DBLBF_WRITE_MD)
    {
        _HalDispMopSetDbBfWr(TRUE, pCmdqCtx);
    }
    else
    {
        _HalDispMopSetDbBfWr(FALSE, pCmdqCtx);
    }
}

void HalDispMopsGwinEn(void *pCtx, HalDispMopId_e eMopId, bool bEn)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_BK0_01_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, bEn ? DISP_BIT15 : 0, DISP_BIT15, pCmdqCtx);
    }
}

void HalDispMopsSetYAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    u32 Mops_Gwin_Reg_Base2 = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_BK0_08_L;
    Mops_Gwin_Reg_Base2 = REG_DISP_MOPS_BK0_09_L;
    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopsSetAddr16Offset(void *pCtx, HalDispMopId_e eMopId, u8 u8Offset)
{
/*    u32 u32RegVal;
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_BK0_21_L;

    u32RegVal = (u8Offset<<9);
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, (u32RegVal & 0x1E00), 0x1E00, pCmdqCtx);
    }*/
}

void HalDispMopsSetCAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    u32 Mops_Gwin_Reg_Base2 = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_BK0_10_L;
    Mops_Gwin_Reg_Base2 = REG_DISP_MOPS_BK0_11_L;
    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopsSetGwinParam(void *pCtx, HalDispMopId_e eMopId, u16 u16Hst, u16 u16Vst, u16 u16Width, u16 u16Height)
{
    u16 u16Hend;
    u16 u16Vend;
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Hst_Base = 0;
    u32 Mops_Gwin_Reg_Hend_Base = 0;
    u32 Mops_Gwin_Reg_Vst_Base = 0;
    u32 Mops_Gwin_Reg_Vend_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Hst_Base = REG_DISP_TOP_OP2_0_1D_L;
    Mops_Gwin_Reg_Hend_Base = REG_DISP_TOP_OP2_0_1E_L;
    Mops_Gwin_Reg_Vst_Base = REG_DISP_TOP_OP2_0_1F_L;
    Mops_Gwin_Reg_Vend_Base = REG_DISP_TOP_OP2_0_20_L;
    u16Hend = u16Hst + u16Width -1;
    u16Vend = u16Vst + u16Height -1;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Hst_Base, HalDispUtilityR2BYTEDirect(REG_DISP_TOP_OP2_0_17_L)+u16Hst,  0x1FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Hend_Base, HalDispUtilityR2BYTEDirect(REG_DISP_TOP_OP2_0_17_L)+u16Hend, 0x1FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Vst_Base, HalDispUtilityR2BYTEDirect(REG_DISP_TOP_OP2_0_19_L)+u16Vst,  0x1FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Vend_Base, HalDispUtilityR2BYTEDirect(REG_DISP_TOP_OP2_0_19_L)+u16Vend, 0x1FFF, pCmdqCtx);
    }
}

void HalDispMopsSetHvspIn(void *pCtx, HalDispMopId_e eMopId, u16 u16Width, u16 u16Height)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Width_Base = 0;
    u32 Mops_Gwin_Reg_Height_Base = 0;

    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Width_Base = REG_DISP_MOPS_HVSP_20_L;
    Mops_Gwin_Reg_Height_Base = REG_DISP_MOPS_HVSP_21_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Width_Base, u16Width,  0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Height_Base, u16Height, 0xFFFF, pCmdqCtx);
    }
}
void HalDispMopsSetHvspOut(void *pCtx, HalDispMopId_e eMopId, u16 u16Width, u16 u16Height)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Width_Base = 0;
    u32 Mops_Gwin_Reg_Height_Base = 0;

    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Width_Base = REG_DISP_MOPS_HVSP_22_L;
    Mops_Gwin_Reg_Height_Base = REG_DISP_MOPS_HVSP_23_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Width_Base, u16Width,  0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Height_Base, u16Height, 0xFFFF, pCmdqCtx);
    }
}


void HalDispMopsSetPitch(void *pCtx, HalDispMopId_e eMopId, u16 u16Pitch)
{
    u16 u16RegVal;
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Y_Base = 0;
    u32 Mops_Gwin_Reg_C_Base = 0;
    u32 Mops_Gwin_Reg_En_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Y_Base = REG_DISP_MOPS_BK0_30_L;
    Mops_Gwin_Reg_C_Base = REG_DISP_MOPS_BK0_31_L;
    Mops_Gwin_Reg_En_Base = REG_DISP_MOPS_BK0_32_L;
    u16RegVal = u16Pitch;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_En_Base, 0x0001 , 0x0001, pCmdqCtx);//lineoffset en
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Y_Base, u16RegVal, 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_C_Base, u16RegVal, 0xFFFF, pCmdqCtx);
    }
}

void HalDispMopsSetSourceParam(void *pCtx, HalDispMopId_e eMopId, u16 u16SrcWidth, u16 u16SrcHeight)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Width_Base = 0;
    u32 Mops_Gwin_Reg_Height_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Width_Base = REG_DISP_MOPS_BK0_04_L;
    Mops_Gwin_Reg_Height_Base = REG_DISP_MOPS_BK0_05_L;

    if(pCmdqCtx)
    {
        if(u16SrcWidth%16)
        {
            DISP_ERR("[HALMOP]%s %d, Src_Width=%d not support, should be 16 align\n", __FUNCTION__, __LINE__,u16SrcWidth);
        }
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Width_Base, (u16SrcWidth),  0x1FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Height_Base, (u16SrcHeight), 0x1FFF, pCmdqCtx);
    }
}

void HalDispMopsSetHScaleFac(void *pCtx, HalDispMopId_e eMopId, u32 u16HRatio)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    u32 Mops_Gwin_Reg_Base2 = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_HVSP_07_L;
    Mops_Gwin_Reg_Base2 = REG_DISP_MOPS_HVSP_08_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, (u16HRatio & 0xFFFF),  0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base2, (u16HRatio >> 16),  0x00FF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base2, 0x0100,  0x0100, pCmdqCtx);//scaling enable
    }
}

void HalDispMopsSetVScaleFac(void *pCtx, HalDispMopId_e eMopId, u32 u16VRatio)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    u32 Mops_Gwin_Reg_Base2 = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_HVSP_09_L;
    Mops_Gwin_Reg_Base2 = REG_DISP_MOPS_HVSP_0A_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, (u16VRatio & 0xFFFF),  0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base2, (u16VRatio >> 16),  0x00FF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base2, 0x0100,  0x0100, pCmdqCtx);//scaling enable
    }
}

void HalDispMopsHwCropEn(void *pCtx, HalDispMopId_e eMopId, bool bEn)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_HVSP_60_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, bEn ? DISP_BIT0 : 0, DISP_BIT0, pCmdqCtx);
    }
}
void HalDispMopsHwCropInSize(void *pCtx, HalDispMopId_e eMopId, u16 u16Width, u16 u16Height)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    u32 Mops_Gwin_Reg_Base2 = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_HVSP_61_L;
    Mops_Gwin_Reg_Base2 = REG_DISP_MOPS_HVSP_62_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, u16Width, 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base2, u16Height, 0xFFFF, pCmdqCtx);
    }
}

void HalDispMopsHwCropHst(void *pCtx, HalDispMopId_e eMopId, u16 u16Val)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_HVSP_63_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, u16Val, 0xFFFF, pCmdqCtx);
    }
}

void HalDispMopsHwCropHsize(void *pCtx, HalDispMopId_e eMopId, u16 u16Val)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_HVSP_64_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, u16Val, 0xFFFF, pCmdqCtx);
    }
}

void HalDispMopsHwCropVst(void *pCtx, HalDispMopId_e eMopId, u16 u16Val)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_HVSP_65_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, u16Val, 0xFFFF, pCmdqCtx);
    }
}

void HalDispMopsHwCropVsize(void *pCtx, HalDispMopId_e eMopId, u16 u16Val)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = REG_DISP_MOPS_HVSP_66_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, u16Val, 0xFFFF, pCmdqCtx);
    }
}

/*void HalDispMopsSetRingEn(void *pCtx, HalDispMopId_e eMopId, bool bEn)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_54_L:
                                                           REG_DISP_MOPS_BK0_54_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, bEn ? DISP_BIT15 : 0, DISP_BIT15, pCmdqCtx);
    }
}

void HalDispMopsSetRingSrc(void *pCtx, HalDispMopId_e eMopId, bool bImi)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_54_L:
                                                           REG_DISP_MOPS_BK0_54_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, bImi ? DISP_BIT14 : 0, DISP_BIT14, pCmdqCtx);
    }
}

void HalDispMopsSetRingBuffHeight(void *pCtx, HalDispMopId_e eMopId, u16 u16RingBufHeight)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_54_L:
                                                           REG_DISP_MOPS_BK0_54_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, u16RingBufHeight, 0x1FFF, pCmdqCtx);
    }
}

void HalDispMopsSetBuffStartLine(void *pCtx, HalDispMopId_e eMopId, u16 u16RingBufStartLine)
{
    void *pCmdqCtx = NULL;
    u32 Mops_Gwin_Reg_Base = 0;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    Mops_Gwin_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_55_L:
                                                           REG_DISP_MOPS_BK0_55_L;

    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mops_Gwin_Reg_Base, u16RingBufStartLine, 0x1FFF, pCmdqCtx);
    }
}
*/
// Set ClkRate
void HalDispMopSetClk(bool bEn, u32 u32ClkRate)
{
/*    u16 u16RegVal;

    u16RegVal = (u32ClkRate <= CLK_MHZ(288)) ? (0x02 << 2) :
                (u32ClkRate <= CLK_MHZ(320)) ? (0x00 << 2) :
                (u32ClkRate <= CLK_MHZ(384)) ? (0x01 << 2) :
                                               (0x03 << 2);


    u16RegVal |= bEn ? 0x0000 : 0x0001;

    W2BYTEMSK(REG_CLKGEN_54_L, u16RegVal, 0x000F);
*/}

// Get ClkRate
void HalDispMopGetClk(bool *pbEn, u32 *pu32ClkRate)
{
/*    u16 u16RegVal;

    u16RegVal = R2BYTE(REG_CLKGEN_54_L);

    *pbEn = u16RegVal & 0x0001 ? 0 : 1;

    *pu32ClkRate = ((u16RegVal & 0x0C) >> 2) == 0x00 ? CLK_MHZ(320) :
                   ((u16RegVal & 0x0C) >> 2) == 0x01 ? CLK_MHZ(384) :
                   ((u16RegVal & 0x0C) >> 2) == 0x02 ? CLK_MHZ(288) :
                                                       0;
*/}

///MOP common
void HalDispMopDbBfWr(void *pCtx, HalDispMopId_e eMopId)
{
/*    u32 Mop_Reg_Base = 0;
    void *pCmdqCtx = NULL;

    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = REG_DISP_MOPG_BK00_7F_L;
    if(pCmdqCtx)
    {
        if(HAL_DISP_MOP_WRITE_MD == HAL_DISP_MOP_DBLBF_WRITE_MD)
        {
            HalDispUtilityW2BYTEMSKDirectCmdq(pCmdqCtx, Mop_Reg_Base, DISP_BIT8, DISP_BIT8);
            HalDispUtilityW2BYTEMSKDirectCmdq(pCmdqCtx, Mop_Reg_Base, 0, DISP_BIT8);
        }
    }*/
}

//MOP rotate
/*void HalDispMopRotDbBfWr(void *pCtx, HalDispMopId_e eMopId, HalDispMopRotId_e eMopRotId)
{
    u16 u16RegVal;
    u32 Mop_Reg_Base = 0;
    void *pCmdqCtx = NULL;

    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_01_L:
                                                     REG_DISP_MOP_ROT_BK0_01_L;

    u16RegVal = (eMopRotId == E_HAL_DISP_MOPROT_ROT0_ID) ? DISP_BIT2:
                (eMopRotId == E_HAL_DISP_MOPROT_ROT1_ID) ? DISP_BIT3:
                                                           DISP_BIT2;

    if(pCmdqCtx)
    {
        if(HAL_DISP_MOP_WRITE_MD == HAL_DISP_MOP_DBLBF_WRITE_MD)
        {
            HalDispUtilityW2BYTEMSKDirectCmdq(pCmdqCtx, Mop_Reg_Base, u16RegVal, u16RegVal);
            HalDispUtilityW2BYTEMSKDirectCmdq(pCmdqCtx, Mop_Reg_Base, 0, u16RegVal);
        }
    }
}

void HalDispMopRot0DbfEn(HalDispMopId_e eMopId, bool bEn, void *pCmdq)
{
    u32 Mop_Reg_Base = 0;
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_01_L:
                                                     REG_DISP_MOP_ROT_BK0_01_L;
    HalDispUtilityW2BYTEMSKDirect(Mop_Reg_Base, bEn ? DISP_BIT0 : 0, DISP_BIT0, pCmdq);
}

void HalDispMopRot1DbfEn(HalDispMopId_e eMopId, bool bEn, void *pCmdq)
{
    u32 Mop_Reg_Base = 0;
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_01_L:
                                                     REG_DISP_MOP_ROT_BK0_01_L;
    HalDispUtilityW2BYTEMSKDirect(Mop_Reg_Base, bEn ? DISP_BIT1 : 0, DISP_BIT1, pCmdq);
}

void HalDispMopRot0En(void *pCtx, HalDispMopId_e eMopId, bool bEn)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    u32 Mop_ROT_TOP_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_0A_L:
                                                     REG_DISP_MOPS_BK0_0A_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_01_L:
                                                      REG_DISP_MOP_ROT_BK0_01_L;
    Mop_ROT_TOP_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_TOP_1_BASE:
                                                             REG_DISP_TOP_0_BASE;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, bEn ? DISP_BIT0 : 0, DISP_BIT0, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, bEn ? DISP_BIT14 : 0, DISP_BIT14, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_ROT_TOP_Reg_Base + (0x20)*2, bEn ? DISP_BIT14 : 0, DISP_BIT14, pCmdqCtx);
    }
}

void HalDispMopRot1En(void *pCtx, HalDispMopId_e eMopId, bool bEn)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    u32 Mop_ROT_TOP_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_51_L:
                                                     REG_DISP_MOPS_BK0_51_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_01_L:
                                                      REG_DISP_MOP_ROT_BK0_01_L;
    Mop_ROT_TOP_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_TOP_1_BASE:
                                                             REG_DISP_TOP_0_BASE;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, bEn ? DISP_BIT0 : 0, DISP_BIT0, pCmdqCtx);
        //_HalMopSwShadowHandler(REG_DISP_MOPS_BK0_BASE, E_HAL_DISP_LAYER_MOPS_51, bEn ? DISP_BIT0 : 0, DISP_BIT0);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, bEn ? DISP_BIT15 : 0, DISP_BIT15, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_ROT_TOP_Reg_Base + (0x20)*2, bEn ? DISP_BIT15 : 0, DISP_BIT15, pCmdqCtx);
    }
}

void HalDispMopRot0BlkNum(void *pCtx, HalDispMopId_e eMopId, u16 u16pitch)
{
    u32 Mop_Reg_BlkNum_Base = 0;
    u32 u32BlkNum = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_BlkNum_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_29_L:
                                                            REG_DISP_MOP_ROT_BK0_29_L;
    u32BlkNum = u16pitch/128;//block num need 128 align
    if(u16pitch%128)
    {
        u32BlkNum++;
    }
    if(pCmdqCtx)
    {
        //block num
        HalDispUtilityW2BYTEMSK(Mop_Reg_BlkNum_Base, u32BlkNum,  0x03FF, pCmdqCtx);
    }
}
void HalDispMopRot1BlkNum(void *pCtx, HalDispMopId_e eMopId, u16 u16pitch)
{
    u32 Mop_Reg_BlkNum_Base = 0;
    u32 u32BlkNum = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_BlkNum_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_49_L:
                                                            REG_DISP_MOP_ROT_BK0_49_L;
    u32BlkNum = u16pitch/128;//block num need 128 align
    if(u16pitch%128)
    {
        u32BlkNum++;
    }
    if(pCmdqCtx)
    {
        //block num
        HalDispUtilityW2BYTEMSK(Mop_Reg_BlkNum_Base, u32BlkNum,  0x03FF, pCmdqCtx);
    }
}

void HalDispMopRot0SourceWidth(void *pCtx, HalDispMopId_e eMopId, u16 u16inputWidth)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    //u32 Mop_Reg_BlkNum_Base = 0;
    //u32 u32BlkNum = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_10_L:
                                                     REG_DISP_MOP_ROT_BK0_10_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_20_L:
                                                      REG_DISP_MOP_ROT_BK0_20_L;

    if(pCmdqCtx)
    {
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, u16inputWidth,  0x07FF, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, (u16inputWidth>>1),  0x07FF, pCmdqCtx);
        //block num
        //HalDispUtilityW2BYTEMSK(Mop_Reg_BlkNum_Base, u32BlkNum,  0x03FF, pCmdqCtx);
    }
}

void HalDispMopRot0SourceHeight(void *pCtx, HalDispMopId_e eMopId, u16 u16inputHeight)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_11_L:
                                                     REG_DISP_MOP_ROT_BK0_11_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_21_L:
                                                      REG_DISP_MOP_ROT_BK0_21_L;
    if(pCmdqCtx)
    {
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, u16inputHeight, 0x07FF, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, (u16inputHeight>>1), 0x07FF, pCmdqCtx);
    }
}

void HalDispMopRot1SourceWidth(void *pCtx, HalDispMopId_e eMopId, u16 u16inputWidth)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    //u32 Mop_Reg_BlkNum_Base = 0;
    //u32 u32BlkNum = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_30_L:
                                                     REG_DISP_MOP_ROT_BK0_30_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_40_L:
                                                      REG_DISP_MOP_ROT_BK0_40_L;

    if(pCmdqCtx)
    {
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, u16inputWidth,  0x07FF, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, (u16inputWidth>>1),  0x07FF, pCmdqCtx);
        //block num
        //HalDispUtilityW2BYTEMSK(Mop_Reg_BlkNum_Base, u32BlkNum,  0x03FF, pCmdqCtx);
    }
}

void HalDispMopRot1SourceHeight(void *pCtx, HalDispMopId_e eMopId, u16 u16inputHeight)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_31_L:
                                                     REG_DISP_MOP_ROT_BK0_31_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_41_L:
                                                      REG_DISP_MOP_ROT_BK0_41_L;
    if(pCmdqCtx)
    {
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, u16inputHeight, 0x07FF, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, (u16inputHeight>>1), 0x07FF, pCmdqCtx);
    }
}

void HalDispMopRot0SetReadYAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_14_L:
                                                     REG_DISP_MOP_ROT_BK0_14_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_15_L:
                                                      REG_DISP_MOP_ROT_BK0_15_L;

    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot0SetReadCAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_24_L:
                                                     REG_DISP_MOP_ROT_BK0_24_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_25_L:
                                                      REG_DISP_MOP_ROT_BK0_25_L;

    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot1SetReadYAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_34_L:
                                                     REG_DISP_MOP_ROT_BK0_34_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_35_L:
                                                      REG_DISP_MOP_ROT_BK0_35_L;

    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot1SetReadCAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_44_L:
                                                     REG_DISP_MOP_ROT_BK0_44_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_45_L:
                                                      REG_DISP_MOP_ROT_BK0_45_L;

    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot0SetWriteYAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_17_L:
                                                     REG_DISP_MOP_ROT_BK0_17_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_18_L:
                                                      REG_DISP_MOP_ROT_BK0_18_L;

    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot0SetWriteCAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_27_L:
                                                     REG_DISP_MOP_ROT_BK0_27_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_28_L:
                                                      REG_DISP_MOP_ROT_BK0_28_L;

    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot1SetWriteYAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_37_L:
                                                     REG_DISP_MOP_ROT_BK0_37_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_38_L:
                                                      REG_DISP_MOP_ROT_BK0_38_L;

    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot1SetWriteCAddr(void *pCtx, HalDispMopId_e eMopId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_47_L:
                                                     REG_DISP_MOP_ROT_BK0_47_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_48_L:
                                                      REG_DISP_MOP_ROT_BK0_48_L;

    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u32RegVal & 0xFFFF), 0xFFFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u32RegVal>>16) & 0x0FFF), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot0SetRotateMode(void *pCtx, HalDispMopId_e eMopId, HalDispRotateMode_e eRotAng)
{
    u32 Mop_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_51_L:
                                                     REG_DISP_MOPS_BK0_51_L;
    if((eRotAng==E_HAL_DISP_ROTATE_90)||
       (eRotAng==E_HAL_DISP_ROTATE_270)||
       (eRotAng==E_HAL_DISP_ROTATE_NONE))
    {
        if(pCmdqCtx)
        {
            HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (eRotAng == E_HAL_DISP_ROTATE_270)? DISP_BIT1 : 0,  DISP_BIT1, pCmdqCtx);
        }
        //_HalMopSwShadowHandler(REG_DISP_MOPS_BK0_BASE, E_HAL_DISP_LAYER_MOPS_51, (eRotAng == E_HAL_DISP_ROTATE_270)? DISP_BIT1 : 0, DISP_BIT1);
    }
    else
    {
        DISP_ERR("[HALMOP]%s %d, Rotate ID %d not support\n", __FUNCTION__, __LINE__,eRotAng);
    }
}

void HalDispMopRot1SetRotateMode(void *pCtx, HalDispMopId_e eMopId, HalDispRotateMode_e eRotAng)
{
    u32 Mop_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOPS_BK1_51_L:
                                                     REG_DISP_MOPS_BK0_51_L;
    if((eRotAng==E_HAL_DISP_ROTATE_90)||
       (eRotAng==E_HAL_DISP_ROTATE_270)||
       (eRotAng==E_HAL_DISP_ROTATE_NONE))
    {
        if(pCmdqCtx)
        {
          HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (eRotAng == E_HAL_DISP_ROTATE_270)? DISP_BIT2 : 0,  DISP_BIT2, pCmdqCtx);
        }
        //_HalMopSwShadowHandler(REG_DISP_MOPS_BK0_BASE, E_HAL_DISP_LAYER_MOPS_51, (eRotAng == E_HAL_DISP_ROTATE_270)? DISP_BIT2 : 0, DISP_BIT2);
    }
    else
    {
        DISP_ERR("[HALMOP]%s %d, Rotate ID %d not support\n", __FUNCTION__, __LINE__,eRotAng);
    }
}

void HalDispMopRot0SetPixDummy(void *pCtx, HalDispMopId_e eMopId, u16 u16DummyPix)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_16_L:
                                                     REG_DISP_MOP_ROT_BK0_16_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_26_L:
                                                      REG_DISP_MOP_ROT_BK0_26_L;
    if(pCmdqCtx)
    {
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u16DummyPix<<12), 0xF000, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u16DummyPix/2)<<12), 0x7000, pCmdqCtx);
    }
}

void HalDispMopRot1SetPixDummy(void *pCtx, HalDispMopId_e eMopId, u16 u16DummyPix)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_36_L:
                                                     REG_DISP_MOP_ROT_BK0_36_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_46_L:
                                                      REG_DISP_MOP_ROT_BK0_46_L;
    if(pCmdqCtx)
    {
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u16DummyPix<<12), 0xF000, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, ((u16DummyPix/2)<<12), 0x7000, pCmdqCtx);
    }
}

void HalDispMopRot0SetRotateCropXEn(void *pCtx, HalDispMopId_e eMopId, bool bEn)
{
    u32 Mop_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_2A_L:
                                                     REG_DISP_MOP_ROT_BK0_2A_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (bEn<<15), 0x8000, pCmdqCtx);
    }
}
void HalDispMopRot0SetRotateCropYEn(void *pCtx, HalDispMopId_e eMopId, bool bEn)
{
    u32 Mop_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_2A_L:
                                                     REG_DISP_MOP_ROT_BK0_2A_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (bEn<<14), 0x4000, pCmdqCtx);
    }
}

void HalDispMopRot1SetRotateCropXEn(void *pCtx, HalDispMopId_e eMopId, bool bEn)
{
    u32 Mop_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_4A_L:
                                                     REG_DISP_MOP_ROT_BK0_4A_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (bEn<<15), 0x8000, pCmdqCtx);
    }
}
void HalDispMopRot1SetRotateCropYEn(void *pCtx, HalDispMopId_e eMopId, bool bEn)
{
    u32 Mop_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_4A_L:
                                                     REG_DISP_MOP_ROT_BK0_4A_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (bEn<<14), 0x4000, pCmdqCtx);
    }
}

void HalDispMopRot0SetRotateCropXClipNum(void *pCtx, HalDispMopId_e eMopId, u16 u16ClipNum, u16 u16ClipNumCmp)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_2A_L:
                                                     REG_DISP_MOP_ROT_BK0_2A_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_2B_L:
                                                      REG_DISP_MOP_ROT_BK0_2B_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u16ClipNum>>4), 0x0FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, (u16ClipNumCmp>>4), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot1SetRotateCropXClipNum(void *pCtx, HalDispMopId_e eMopId, u16 u16ClipNum, u16 u16ClipNumCmp)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_4A_L:
                                                     REG_DISP_MOP_ROT_BK0_4A_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_4B_L:
                                                      REG_DISP_MOP_ROT_BK0_4B_L;
    if(pCmdqCtx)
    {
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, (u16ClipNum>>4), 0x0FFF, pCmdqCtx);
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, (u16ClipNumCmp>>4), 0x0FFF, pCmdqCtx);
    }
}

void HalDispMopRot0SetRotateCropYClipNum(void *pCtx, HalDispMopId_e eMopId, u16 u16ClipNum, u16 u16ClipNumCmp)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    u32 Mop_Reg_Base3 = 0;
    u32 Mop_Reg_Base4 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_2C_L:
                                                     REG_DISP_MOP_ROT_BK0_2C_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_2D_L:
                                                      REG_DISP_MOP_ROT_BK0_2D_L;
    Mop_Reg_Base3 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_2E_L:
                                                      REG_DISP_MOP_ROT_BK0_2E_L;
    Mop_Reg_Base4 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_2F_L:
                                                      REG_DISP_MOP_ROT_BK0_2F_L;
    if(pCmdqCtx)
    {
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, u16ClipNum, 0xFFFF, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, (u16ClipNum/2), 0xFFFF, pCmdqCtx);
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base3, u16ClipNumCmp, 0xFFFF, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base4, (u16ClipNumCmp/2), 0xFFFF, pCmdqCtx);
    }
}

void HalDispMopRot1SetRotateCropYClipNum(void *pCtx, HalDispMopId_e eMopId, u16 u16ClipNum, u16 u16ClipNumCmp)
{
    u32 Mop_Reg_Base = 0;
    u32 Mop_Reg_Base2 = 0;
    u32 Mop_Reg_Base3 = 0;
    u32 Mop_Reg_Base4 = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);
    Mop_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_4C_L:
                                                     REG_DISP_MOP_ROT_BK0_4C_L;
    Mop_Reg_Base2 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_4D_L:
                                                      REG_DISP_MOP_ROT_BK0_4D_L;
    Mop_Reg_Base3 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_4E_L:
                                                      REG_DISP_MOP_ROT_BK0_4E_L;
    Mop_Reg_Base4 = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_4F_L:
                                                      REG_DISP_MOP_ROT_BK0_4F_L;
    if(pCmdqCtx)
    {
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base, u16ClipNum, 0xFFFF, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base2, (u16ClipNum/2), 0xFFFF, pCmdqCtx);
        //Y
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base3, u16ClipNumCmp, 0xFFFF, pCmdqCtx);
        //C
        HalDispUtilityW2BYTEMSK(Mop_Reg_Base4, (u16ClipNumCmp/2), 0xFFFF, pCmdqCtx);
    }
}


void HalDispMopRotInit(void *pCtx)
{
    HalDispMopId_e eMopId = 0;
    u32 Mop_Rot_Reg_Base = 0;
    void *pCmdqCtx = NULL;
    HalDispGetCmdqByCtx(pCtx, &pCmdqCtx);

    for(eMopId = E_HAL_DISP_MOPID_00; eMopId < E_HAL_DISP_MOP_NUM; eMopId++)
    {
        Mop_Rot_Reg_Base = (eMopId == E_HAL_DISP_MOPID_01) ? REG_DISP_MOP_ROT_BK1_BASE:
                                                             REG_DISP_MOP_ROT_BK0_BASE;
        //rot0 Y
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x12)*2, 0x0820, 0x3F3F, pCmdqCtx);//[13:8]reg_rot0_rdma_length_y=0x8; [5:0]reg_rot0_rdma_thd_y=0x20
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x13)*2, 0xA01F, 0xBFFF, pCmdqCtx);//[15]reg_rot0_rdma_hp_en_y=0x1; [13:8]reg_rot0_rdma_hp_thd_y=0x20; [7:0]reg_rot0_rdma_stop_y=0x1F
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x16)*2, 0x0800, 0x0F07, pCmdqCtx);//[11:8]reg_rot0_burst_wr_thd_y=0x8; [7:0]reg_rot0_pre_rdy_thd_y=0x1

        //rot0 C
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x22)*2, 0x0820, 0x3F3F, pCmdqCtx);//[13:8]reg_rot0_rdma_length_c=0x8; [5:0]reg_rot0_rdma_thd_c=0x20
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x23)*2, 0xA01F, 0xBFFF, pCmdqCtx);//[15]reg_rot0_rdma_hp_en_c=0x1; [13:8]reg_rot0_rdma_hp_thd_c=0x20; [7:0]reg_rot0_rdma_stop_c=0x1F
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x26)*2, 0x0800, 0x0F07, pCmdqCtx);//[11:8]reg_rot0_burst_wr_thd_c=0x8; [7:0]reg_rot0_pre_rdy_thd_c=0x1

        //rot1 Y
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x32)*2, 0x0820, 0x3F3F, pCmdqCtx);//[13:8]reg_rot1_rdma_length_y=0x8; [5:0]reg_rot1_rdma_thd_y=0x20
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x33)*2, 0xA01F, 0xBFFF, pCmdqCtx);//[15]reg_rot1_rdma_hp_en_y=0x1; [13:8]reg_rot1_rdma_hp_thd_y=0x20; [7:0]reg_rot1_rdma_stop_y=0x1F
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x36)*2, 0x0800, 0x0F07, pCmdqCtx);//[11:8]reg_rot1_burst_wr_thd_y=0x8; [7:0]reg_rot1_pre_rdy_thd_y=0x1

        //rot1 C
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x42)*2, 0x0820, 0x3F3F, pCmdqCtx);//[13:8]reg_rot1_rdma_length_c=0x8; [5:0]reg_rot1_rdma_thd_c=0x20
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x43)*2, 0xA01F, 0xBFFF, pCmdqCtx);//[15]reg_rot1_rdma_hp_en_c=0x1; [13:8]reg_rot1_rdma_hp_thd_c=0x20; [7:0]reg_rot1_rdma_stop_c=0x1F
        HalDispUtilityW2BYTEMSKDirect(Mop_Rot_Reg_Base + (0x46)*2, 0x0800, 0x0F07, pCmdqCtx);//[11:8]reg_rot1_burst_wr_thd_c=0x8; [7:0]reg_rot1_pre_rdy_thd_c=0x1

        //open double buffer write
        if(HAL_DISP_MOP_WRITE_MD == HAL_DISP_MOP_DBLBF_WRITE_MD)
        {
            HalDispMopRot0DbfEn(eMopId, TRUE, pCmdqCtx);
            _HalDispMopRotDbBfWrWithoutCmdq(pCtx, eMopId, E_HAL_DISP_MOPROT_ROT0_ID);
            HalDispMopRot1DbfEn(eMopId, TRUE, pCmdqCtx);
            _HalDispMopRotDbBfWrWithoutCmdq(pCtx, eMopId, E_HAL_DISP_MOPROT_ROT1_ID);
        }
        else
        {
            HalDispMopRot0DbfEn(eMopId, FALSE, pCmdqCtx);
            HalDispMopRot1DbfEn(eMopId, FALSE, pCmdqCtx);
        }
    }
}
*/
