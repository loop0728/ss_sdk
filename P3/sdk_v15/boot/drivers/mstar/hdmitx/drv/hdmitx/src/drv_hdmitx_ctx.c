/*
* drv_hdmitx_ctx.c- Sigmastar
*
* Copyright (c) [2019~2020] SigmaStar Technology.
*
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License version 2 for more details.
*
*/

#define _DRV_HDMITX_CTX_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include "mhal_common.h"
#include "drv_hdmitx_os.h"
#include "hdmitx_debug.h"
#include "hal_hdmitx_chip.h"
#include "hal_hdmitx_st.h"
#include "drv_hdmitx_ctx.h"
//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  structure
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Variable
//-------------------------------------------------------------------------------------------------
DrvHdmitxCtxConfig_t gstHdmitxCtxTbl[HAL_HDMITX_CTX_INST_MAX];
bool gbHdmitxCtxInit = FALSE;

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
bool DrvHdmitxCtxInit(void)
{
    u16 i;
    bool bRet = 1;

    if(gbHdmitxCtxInit)
    {
        return 1;
    }

    gbHdmitxCtxInit = 1;

    for(i=0; i<HAL_HDMITX_CTX_INST_MAX; i++)
    {
        gstHdmitxCtxTbl[i].bUsed = 0;
        gstHdmitxCtxTbl[i].s32CtxId= -1;

        gstHdmitxCtxTbl[i].pstHalCtx = DrvHdmitxOsMemAlloc(sizeof(DrvHdmitxCtxHalContain_t));

        if(gstHdmitxCtxTbl[i].pstHalCtx == NULL)
        {
            bRet = 0;
            HDMITX_ERR("[HdmitxCTX] %s %d, Allocate Mhal Ctx Fail\n", __FUNCTION__, __LINE__);
            break;
        }
        memset(gstHdmitxCtxTbl[i].pstHalCtx, 0, sizeof(DrvHdmitxCtxHalContain_t));
    }

    return bRet;
}


bool DrvHdmitxCtxDeInit(void)
{
    u16 i;

    if(gbHdmitxCtxInit == 0)
    {
        HDMITX_ERR("%s %d, Hdmitx Ctx not Inited\n", __FUNCTION__, __LINE__);
        return 0;
    }

    for(i=0; i<HAL_HDMITX_CTX_INST_MAX; i++)
    {
        gstHdmitxCtxTbl[i].bUsed = 0;
        gstHdmitxCtxTbl[i].s32CtxId= -1;
        DrvHdmitxOsMemRelease(gstHdmitxCtxTbl[i].pstHalCtx);
        gstHdmitxCtxTbl[i].pstHalCtx = NULL;
    }
    gbHdmitxCtxInit = 0;

    return 1;

}

bool DrvHdmitxCtxIsAllFree(void)
{
    u16 i;
    bool bFree = 1;

    for(i=0; i<HAL_HDMITX_CTX_INST_MAX; i++)
    {
        if(gstHdmitxCtxTbl[i].bUsed)
        {
            bFree = 0;
            break;
        }
    }
    return bFree;
}

bool DrvHdmitxCtxAllocate(DrvHdmitxCtxAllocConfig_t *pAllocCfg, DrvHdmitxCtxConfig_t **pCtx)
{
    u16 i = 0;
    bool bRet = 1;

    if(pAllocCfg == NULL)
    {
        HDMITX_ERR("[HdmitxCTX] %40s %d, CtxConfig is Empty\n", __FUNCTION__, __LINE__);
        *pCtx = NULL;
        bRet = 0;
    }
    else
    {
        *pCtx = NULL;
        for(i=0; i<HAL_HDMITX_CTX_INST_MAX; i++)
        {
            if(gstHdmitxCtxTbl[i].bUsed == 0)
            {
                gstHdmitxCtxTbl[i].bUsed = 1;
                gstHdmitxCtxTbl[i].s32CtxId = pAllocCfg->s32CtxId;
                *pCtx = &gstHdmitxCtxTbl[i];
                break;
            }
        }
    }

    if(*pCtx == NULL)
    {
        bRet = 0;
        HDMITX_ERR("%s %d, Alloc Ctx Fail\n", __FUNCTION__, __LINE__);
    }
    else
    {
        bRet = 1;
        HDMITX_MSG(HDMITX_DBG_LEVEL_CTX, "%s %d, Ctx Id:%d\n",
            __FUNCTION__, __LINE__, i);
    }

    return bRet;
}

bool DrvHdmitxCtxGet(DrvHdmitxCtxAllocConfig_t *pAllocCfg, DrvHdmitxCtxConfig_t **pCtx)
{
    u16 i = 0;
    bool bRet = 1;

    if(pAllocCfg == NULL)
    {
        HDMITX_ERR("[HdmitxCTX] %40s %d, CtxConfig is Empty\n", __FUNCTION__, __LINE__);
        *pCtx = NULL;
        bRet = 0;
    }
    else
    {
        *pCtx = NULL;
        for(i=0; i<HAL_HDMITX_CTX_INST_MAX; i++)
        {
            if(gstHdmitxCtxTbl[i].bUsed == 1 && gstHdmitxCtxTbl[i].s32CtxId == pAllocCfg->s32CtxId )
            {
                *pCtx = &gstHdmitxCtxTbl[i];
                break;
            }
        }
    }

    if(*pCtx == NULL)
    {
        bRet = 0;
        HDMITX_ERR("%s %d, Get Ctx is NULL\n", __FUNCTION__, __LINE__);
    }
    else
    {
        bRet = 1;
        HDMITX_MSG(HDMITX_DBG_LEVEL_CTX, "%s %d, Ctx Id:%d\n",
            __FUNCTION__, __LINE__, i);
    }

    return bRet;
}


bool DrvHdmitxCtxFree(DrvHdmitxCtxConfig_t *pCtx)
{
    bool bRet = 1;

    if(pCtx == NULL)
    {
        bRet = 0;
        HDMITX_ERR("[HdmitxCTX] %40s %d, CtxConfig is Empty\n", __FUNCTION__, __LINE__);
    }
    else
    {
        pCtx->bUsed = 0;
        pCtx->s32CtxId = -1;
        memset(pCtx->pstHalCtx, 0, sizeof(DrvHdmitxCtxHalContain_t));
    }
    return bRet;
}


