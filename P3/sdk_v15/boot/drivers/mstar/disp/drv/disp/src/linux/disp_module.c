/*
* disp_module.c- Sigmastar
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

#define _DISP_MODULE_C_

#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#include "ms_msys.h"
#include "cam_sysfs.h"
#include "drv_disp_os.h"
#include "disp_sysfs.h"
#include "disp_debug.h"

#include "mhal_common.h"
#include "mhal_cmdq.h"
#include "mhal_disp_datatype.h"
#include "hal_disp_chip.h"
#include "hal_disp_st.h"
#include "hal_disp_util.h"
#include "hal_disp.h"
#include "drv_disp_ctx.h"
#include "drv_disp_irq.h"
#include "drv_disp_module.h"
#include "drv_disp_if.h"
//-------------------------------------------------------------------------------------------------
// Define & Macro
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Prototype
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Structure
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Variable
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
// internal function
//-------------------------------------------------------------------------------------------------


//==============================================================================
void _DrvDispGetIrqNum(struct platform_device *pDev, u8 u8Idx, u8 u8DevId)
{
    unsigned int DispIrqId = 0; //INT_IRQ_AU_SYSTEM;

    DispIrqId  = CamOfIrqToResource(pDev->dev.of_node, u8Idx, NULL);

    if (!DispIrqId)
    {
        DISP_ERR("[DISPMODULE] Can't Get SCL_IRQ, Idx=%d, DevId=%d\n", u8Idx,u8DevId);
    }
    else
    {
        DrvDispIrqSetIsrNum(u8DevId, DispIrqId);
    }
}


void _DrvDispModuleInit(void)
{
    int s32Ret;
    u8 i, u8IrqCnt;

    if(_tDispDevice.refCnt == 0)
    {
        _tDispDevice.refCnt++;


        s32Ret = alloc_chrdev_region(&_tDispDevice.tDevNumber, 0, 1, DRV_DISP_DEVICE_NAME);

        if(!_tDispClass)
        {
            _tDispClass = msys_get_sysfs_class();
            if(!_tDispClass)
            {
                _tDispClass = CamClassCreate(THIS_MODULE, DispClassName);
            }

        }
        else
        {
            cdev_init(&_tDispDevice.cdev, &_tDispDevice.fops);
            if (0 != (s32Ret= cdev_add(&_tDispDevice.cdev, _tDispDevice.tDevNumber, DRV_DISP_DEVICE_COUNT)))
            {
                DISP_ERR( "[DISP] Unable add a character device\n");
            }
        }

        if(_tDispDevice.devicenode == NULL && _tDispClass)
        {
            _tDispDevice.devicenode = CamDeviceCreate(_tDispClass, NULL, _tDispDevice.tDevNumber, NULL, DRV_DISP_DEVICE_NAME);
            DrvDispSysfsInit(_tDispDevice.devicenode);
        }

        if(stDrvDispPlatformDevice.dev.of_node == NULL)
        {
            stDrvDispPlatformDevice.dev.of_node = of_find_compatible_node(NULL, NULL, "sstar,disp");
        }
        if(stDrvDispPlatformDevice.dev.of_node == NULL)
        {
            DISP_ERR("[DISP INIT] Get Device mode Fail!!\n");
        }

        //Get IRQ
    }
    u8IrqCnt = DrvDispIrqGetIrqCount();
    for(i=0; i< u8IrqCnt; i++)
    {
        _DrvDispGetIrqNum(&stDrvDispPlatformDevice, i, i);
    }

    DrvDispOsSetDeviceNode(&stDrvDispPlatformDevice);

    DrvDispIfClkOn();
}


void _DrvDispModuleDeInit(void)
{
    if (_tDispDevice.refCnt)
    {
        _tDispDevice.refCnt--;
    }

    if (_tDispDevice.refCnt == 0)
    {
        if (_tDispDevice.cdev.count)
        {
            // Remove a cdev from the system
            cdev_del(&_tDispDevice.cdev);
         }

         //CamDeviceDestroy(m_pstDispClass, _tDispDevice.tDevNumber);
         unregister_chrdev_region(_tDispDevice.tDevNumber, 1);

         stDrvDispPlatformDevice.dev.of_node = NULL;
         _tDispClass = NULL;
     }

     DrvDispIfClkOff();
}

//-------------------------------------------------------------------------------------------------
// Module functions
//-------------------------------------------------------------------------------------------------

