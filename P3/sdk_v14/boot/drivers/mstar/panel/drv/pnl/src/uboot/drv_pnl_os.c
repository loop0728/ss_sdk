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

#define _DRV_PNL_OS_C_
#include <common.h>
#include <command.h>
#include <config.h>
#include <malloc.h>
#include <stdlib.h>
#include "../drivers/mstar/gpio/drvGPIO.h"
#include "../drivers/mstar/pwm/mdrv_pwm.h"

void * DrvPnlOsMemAlloc(u32 u32Size)
{
    return malloc(u32Size);
}

void DrvPnlOsMemRelease(void *pPtr)
{
    free(pPtr);
}

void DrvPnlOsMsSleep(u32 u32Msec)
{
    mdelay(u32Msec);
}

void DrvPnlOsUsSleep(u32 u32Usec)
{
    udelay(u32Usec);
}

void DrvPnlOsMsDelay(u32 u32Msec)
{
    mdelay(u32Msec);
}

void DrvPnlOsUsDelay(u32 u32Usec)
{
    udelay(u32Usec);
}

bool DrvPnlOsPadMuxActive(void)
{
    return 0;
}


bool DrvPnlOsSetDeviceNode(void *pPlatFormDev)
{
    return 0;
}

bool DrvPnlOsSetClkOn(void *pClkRate, u32 u32ClkRateSize)
{
    return 0;
}

bool DrvPnlOsSetClkOff(void)
{
    return 0;
}

bool DrvPnlOsGpioRequestOutput(u8 u8GpioNum)
{
    MDrv_GPIO_Pad_Set(u8GpioNum);
    //mdrv_gpio_set_output(u8GpioNum);

    return TRUE;
}

bool DrvPnlOsGpioRequestInput(u8 u8GpioNum)
{
    MDrv_GPIO_Pad_Set(u8GpioNum);
    //mdrv_gpio_set_input(u8GpioNum);

    return TRUE;
}

bool DrvPnlOsSetGpioValue(u8 u8GpioNum, u8 u8Val)
{
    if(u8Val)
        mdrv_gpio_set_high(u8GpioNum);
    else
        mdrv_gpio_set_low(u8GpioNum);

    return TRUE;
}

bool DrvPnlOsGetGpioValue(u8 u8GpioNum)
{
    return TRUE;
}

bool DrvPnlOsSetPWM(u8 u8PwmNum, u32 u32Period, u32 u32Duty)
{
#if CONFIG_SSTAR_PWM
    //DrvPWMInit(u8PwmNum);
    CamPwmConfig(u8PwmNum, u32Duty, u32Period);
    CamPwmEnable(u8PwmNum);
#endif
    return TRUE;
}

