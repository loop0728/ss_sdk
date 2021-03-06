/*
* rgn_ut_module.c- Sigmastar
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

#define _RGNUT_MODULE_C_

#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#include "ms_msys.h"
#include "cam_os_wrapper.h"
#include "cam_sysfs.h"
#include "mhal_common.h"

//-------------------------------------------------------------------------------------------------
// Define & Macro
//-------------------------------------------------------------------------------------------------
#define RGNUT_DEVICE_COUNT    1
#define RGNUT_DEVICE_NAME     "rgnut"
#define RGNUT_DEVICE_MAJOR    0x87
#define RGNUT_DEVICE_MINOR    0xFB

//-------------------------------------------------------------------------------------------------
// Prototype
//-------------------------------------------------------------------------------------------------
static int RgnUtModuleProbe(struct platform_device *pdev);
static int RgnUtModuleRemove(struct platform_device *pdev);
static int RgnUtModuleSuspend(struct platform_device *dev, pm_message_t state);
static int RgnUtModuleResume(struct platform_device *dev);

//-------------------------------------------------------------------------------------------------
// Structure
//-------------------------------------------------------------------------------------------------
typedef struct
{
    int s32Major;
    int s32Minor;
    int refCnt;
    struct cdev cdev;
    struct file_operations fops;
    struct device *devicenode;
}RgnUtModuleDevice_t;

//-------------------------------------------------------------------------------------------------
// Variable
//-------------------------------------------------------------------------------------------------
static RgnUtModuleDevice_t _tGopDevice =
{
    .s32Major = RGNUT_DEVICE_MAJOR,
    .s32Minor = RGNUT_DEVICE_MINOR,
    .refCnt = 0,
    .devicenode = NULL,
    .cdev =
    {
        .kobj = {.name= RGNUT_DEVICE_NAME, },
        .owner = THIS_MODULE,
    },
    /*
    .fops =
    {
        .open = RgnUtModuleOpen,
        .release = RgnUtModuleRelease,
        .unlocked_ioctl = RgnUtModuleIoctl,
        .poll = RgnUtModulePoll,
    },*/
};

static struct class * _tGopClass = NULL;


static const struct of_device_id _RgnUtMatchTable[] =
{
    { .compatible = "sstar,gop" },// for probe,need match dtsi.
    {}
};

static struct platform_driver stRgnUtPlatformDriver =
{
    .probe      = RgnUtModuleProbe,
    .remove     = RgnUtModuleRemove,
    .suspend    = RgnUtModuleSuspend,
    .resume     = RgnUtModuleResume,
    .driver =
    {
        .name   = RGNUT_DEVICE_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = of_match_ptr(_RgnUtMatchTable),
    },
};



u32 _gu32GopDbgLevel = 0;

//-------------------------------------------------------------------------------------------------
// internal function
//-------------------------------------------------------------------------------------------------
u32 RgnTestShow(char *buf);
void RgnTest(const char *buf, u32 n);
void RgnTestInit(void);
void RgnTestDeInit(void);

static ssize_t rgn_test_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return RgnTestShow(buf);
}
static ssize_t rgn_test_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
    RgnTest(buf,n);
    return n;
}
static DEVICE_ATTR(test,0644, rgn_test_show, rgn_test_store);

void RgnUtSysfsInit(struct device *device)
{
    CamDeviceCreateFile(device, &dev_attr_test);
}


//==============================================================================
static int RgnUtModuleSuspend(struct platform_device *dev, pm_message_t state)
{
    int ret = 0;
    return ret;
}

static int RgnUtModuleResume(struct platform_device *dev)
{
    int ret = 0;
    CamOsPrintf("[GOPMODULE] %s\n",__FUNCTION__);
    return ret;
}


void _RgnUtRemove(void)
{
    CamOsPrintf("[GOPMODULE] %s\n",__FUNCTION__);
}

void _RgnUtModuleInit(void)
{
    dev_t  dev;

    if(_tGopDevice.s32Major)
    {
        dev     = MKDEV(_tGopDevice.s32Major, _tGopDevice.s32Minor);
        if(!_tGopClass)
        {
            _tGopClass = msys_get_sysfs_class();
        }
        //ToDo
        if(_tGopDevice.devicenode==NULL)
        {      
            _tGopDevice.devicenode = CamDeviceCreate(_tGopClass, NULL, dev,NULL, RGNUT_DEVICE_NAME);
            RgnUtSysfsInit(_tGopDevice.devicenode);
            CamOsPrintf( "[GOPMODULE] register sysfs\n");
        }

    }
}



//-------------------------------------------------------------------------------------------------
// Module functions
//-------------------------------------------------------------------------------------------------
static int RgnUtModuleProbe(struct platform_device *pdev)
{
    //unsigned char ret;
    int s32Ret;
    dev_t  dev;
    //struct resource *res_irq;
    //struct device_node *np;
    CamOsPrintf("[GOPMODULE] %s:%d\n",__FUNCTION__,__LINE__);

    if(_tGopDevice.s32Major == 0)
    {
        s32Ret                  = alloc_chrdev_region(&dev, _tGopDevice.s32Minor, RGNUT_DEVICE_COUNT, RGNUT_DEVICE_NAME);
        _tGopDevice.s32Major  = MAJOR(dev);
    }

    _tGopClass = msys_get_sysfs_class();
    if(IS_ERR(_tGopClass))
    {
        CamOsPrintf("[GOPMODULE]Failed at class_create().Please exec [mknod] before operate the device/n");
    }
    else
    {
        //_tGopDevice.devicenode->dma_mask=&u64SclHvsp_DmaMask;
        //_tGopDevice.devicenode->coherent_dma_mask=u64SclHvsp_DmaMask;
    }
    //probe
    //create device
    _RgnUtModuleInit();
    RgnTestInit();
    return 0;
}
static int RgnUtModuleRemove(struct platform_device *pdev)
{
    CamOsPrintf("[GOPMODULE] %s\n",__FUNCTION__);
    RgnTestDeInit();
    _RgnUtRemove();
    //ToDo
    CamDeviceUnregister(_tGopDevice.devicenode);
    return 0;
}

int RgnUtModuleInit(void)
{
    int ret = 0;

    CamOsPrintf("[GOPMODULE] %s:%d\n",__FUNCTION__,__LINE__);


    ret = CamPlatformDriverRegister(&stRgnUtPlatformDriver);
    if (!ret)
    {
        CamOsPrintf("[GOPMODULE] platform_driver_register success\n");
    }
    else
    {
        CamOsPrintf( "[GOPMODULE] platform_driver_register failed\n");
        CamPlatformDriverUnregister(&stRgnUtPlatformDriver);
    }

    return ret;
}
void RgnUtModuleExit(void)
{
    CamPlatformDriverUnregister(&stRgnUtPlatformDriver);
}

module_init(RgnUtModuleInit);
module_exit(RgnUtModuleExit);

MODULE_AUTHOR("SIGMASTAR");
MODULE_DESCRIPTION("rgn ut");
