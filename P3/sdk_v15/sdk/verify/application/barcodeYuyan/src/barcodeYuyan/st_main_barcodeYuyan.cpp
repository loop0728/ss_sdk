/* Copyright (c) 2020-2021 Sigmastar Technology Corp.
 All rights reserved.

  Unless otherwise stipulated in writing, any and all information contained
 herein regardless in any format shall remain the sole proprietary of
 Sigmastar Technology Corp. and be kept in strict confidence
 (??Sigmastar Confidential Information??) by the recipient.
 Any unauthorized act including without limitation unauthorized disclosure,
 copying, use, reproduction, sale, distribution, modification, disassembling,
 reverse engineering and compiling of the contents of Sigmastar Confidential
 Information is unlawful and strictly prohibited. Sigmastar hereby reserves the
 rights to any and all damages, losses, costs and expenses resulting therefrom.
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/syscall.h>

//#include "ReadBarcode.h"
//#include "TextUtfEncoding.h"

//#include <iostream>
//#include <cstring>
//#include <string>
//#include <algorithm>
//#include <cctype>


#include "st_common.h"
#include "st_vif.h"
#include "st_vpe.h"
#include "st_venc.h"
#include "st_rgn.h"

#include "mi_disp.h"
#include "mi_divp.h"
#include "mi_panel.h"
#include "mi_sensor.h"
#include "mi_sensor_datatype.h"

#include "dot_matrix_font.h"

#include "st_cus3a.h"

#include "BasicUsageEnvironment.hh"
#include "liveMedia.hh"
#include "Live555RTSPServer.hh"

#include "decoder.h"
//using namespace ZXing;


#define USE_SNR_PAD_ID_1  (1)
#define BARCODE_IN_WIDTH    (1280)
#define BARCODE_IN_HIGH    (720)

#define ST_MAX_VENC_NUM (16)

typedef struct ST_VencAttr_s
{
    MI_U32     u32BindVpeChn;
    MI_U32     u32BindVpePort;
    MI_SYS_BindType_e  eBindType;
    MI_U32  u32BindParam;

    MI_VENC_CHN vencChn;
    MI_VENC_ModType_e eType;
    MI_U32    u32Width;
    MI_U32     u32Height;
    char szStreamName[128];
    MI_BOOL bUsed;
    MI_BOOL bStart;
}ST_VencAttr_t;

struct ST_Panel_Attr_T
{
    MI_U32              u32Width;
    MI_U32              u32Height;
    MI_SNR_PAD_ID_e     eSnrPad;
    MI_VIF_DEV          s32vifDev;
};

static ST_VencAttr_t gstVencattr[ST_MAX_VENC_NUM];

static struct ST_Panel_Attr_T g_stPanelAttr[]=
{

#if USE_SNR_PAD_ID_1
    {
            .u32Width = 1024,
            .u32Height = 600,
            .eSnrPad   = E_MI_SNR_PAD_ID_0,
            .s32vifDev = 0,
    },
#else
    {
        .u32Width = 1024,
        .u32Height = 600,
        .eSnrPad   = E_MI_SNR_PAD_ID_2,
        .s32vifDev = 1,
    },
#endif
};

#define SENSOR_RGB_FPS 30

#define DELAY_TIME()    //usleep(50000)
#define Key_DevName     "/dev/hidg0"

static int key_fd = -1;

static unsigned char gKeyNumValue[10] =
{
    0x62, /*0*/
    0x59, /*1*/
    0x5A, /*2*/
    0x5B, /*3*/
    0x5C, /*4*/
    0x5D, /*5*/
    0x5E, /*6*/
    0x5F, /*7*/
    0x60, /*8*/
    0x61, /*9*/
};

static bool Hid_Send_OneGBKEnglish(const unsigned char charactor)
{
    int offset = 0;
    static unsigned char charBase = 0x04; /* A or a */
    unsigned char keyType = 0;
    unsigned char report[8] = {0};

    if(charactor >= 'a' && charactor <= 'z')
    {
        keyType = 0;
        offset = charactor - 'a';
    }
    else if(charactor >= 'A' && charactor <= 'Z')
    {
        keyType = 0x02;
        offset = charactor - 'A';
    }
    else
    {
        printf("[fun:%s - Line:%d]unable to support charactor:0x%02x\n", __FUNCTION__, __LINE__, charactor);
    }

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset(report, 0, 8);
    report[0] = keyType;
    report[2] = charBase + offset;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset(report, 0, 8);
    report[0] = keyType;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    return true;
}

static bool Hid_Send_OneGBKChinese(const unsigned char valueH, const unsigned char valueL)
{
    int i;
    unsigned char buf[16] = {0};
    unsigned char report[8] = {0};
    unsigned short value = (valueH<<8) | valueL;

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset((unsigned char *)buf, 0, 16);
    sprintf((char *)buf, "%d", value);
    printf("value:%d  buf:%s\n", value, buf);

    for(i=0; i<16; i++)
    {
        if(buf[i] == 0) { break; }

        memset(report, 0, 8);
        report[0] = 0x04;
        report[2] = 0x00;
        write(key_fd, report, 8);
        DELAY_TIME();

        memset(report, 0, 8);
        report[0] = 0x04;
        report[2] = gKeyNumValue[buf[i]-'0'];
        write(key_fd, report, 8);
        DELAY_TIME();
    }

    //End of one gbk sending, it should send the following
    memset(report, 0, 8);
    report[0] = 0x04;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    return true;
}

static bool Hid_Send_Enter()
{
    unsigned char report[8] = {0};

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x28;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    return true;
}

static bool Hid_Send_Space()
{
    unsigned char report[8] = {0};

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x2C;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    return true;
}

/**************************
1. From ~ to ?
2. From ` to /
**************************/
static bool Hid_Send_Symbol(unsigned char symbol)
{
    unsigned char keyType;
    unsigned char keyValue;
    unsigned char report[8] = {0};

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset(report, 0, 8);
    switch(symbol)
    {
        /*From 1 to / */
        case '1':
            keyType = 0x00;
            keyValue = 0x1E;
        break;
        case '2':
            keyType = 0x00;
            keyValue = 0x1F;
        break;
        case '3':
            keyType = 0x00;
            keyValue = 0x20;
        break;
        case '4':
            keyType = 0x00;
            keyValue = 0x21;
        break;
        case '5':
            keyType = 0x00;
            keyValue = 0x22;
        break;
        case '6':
            keyType = 0x00;
            keyValue = 0x23;
        break;
        case '7':
            keyType = 0x00;
            keyValue = 0x24;
        break;
        case '8':
            keyType = 0x00;
            keyValue = 0x25;
        break;
        case '9':
            keyType = 0x00;
            keyValue = 0x26;
        break;
        case '0':
            keyType = 0x00;
            keyValue = 0x27;
        break;
        case '-':
            keyType = 0x00;
            keyValue = 0x2D;
        break;
        case '=':
            keyType = 0x00;
            keyValue = 0x2E;
        break;
        case '[':
            keyType = 0x02;
            keyValue = 0x2F;
        break;
        case ']':
            keyType = 0x00;
            keyValue = 0x30;
        break;
        case '\\':
            keyType = 0x00;
            keyValue = 0x31;
        break;
        case ';':
            keyType = 0x00;
            keyValue = 0x33;
        break;
        case '\'':
            keyType = 0x00;
            keyValue = 0x34;
        break;
        case '`':
            keyType = 0x00;
            keyValue = 0x35;
        break;
        case ',':
            keyType = 0x00;
            keyValue = 0x36;
        break;
        case '.':
            keyType = 0x00;
            keyValue = 0x37;
        break;
        case '/':
            keyType = 0x00;
            keyValue = 0x38;
        break;
        /*From ! to ?*/
        case '!':
            keyType = 0x02;
            keyValue = 0x1E;
        break;
        case '@':
            keyType = 0x02;
            keyValue = 0x1F;
        break;
        case '#':
            keyType = 0x02;
            keyValue = 0x20;
        break;
        case '$':
            keyType = 0x02;
            keyValue = 0x21;
        break;
        case '%':
            keyType = 0x02;
            keyValue = 0x22;
        break;
        case '^':
            keyType = 0x02;
            keyValue = 0x23;
        break;
        case '&':
            keyType = 0x02;
            keyValue = 0x24;
        break;
        case '*':
            keyType = 0x02;
            keyValue = 0x25;
        break;
        case '(':
            keyType = 0x02;
            keyValue = 0x26;
        break;
        case ')':
            keyType = 0x02;
            keyValue = 0x27;
        break;
        case '_':
            keyType = 0x02;
            keyValue = 0x2D;
        break;
        case '+':
            keyType = 0x02;
            keyValue = 0x2E;
        break;
        case '{':
            keyType = 0x02;
            keyValue = 0x2F;
        break;
        case '}':
            keyType = 0x02;
            keyValue = 0x30;
        break;
        case '|':
            keyType = 0x02;
            keyValue = 0x31;
        break;
        case ':':
            keyType = 0x02;
            keyValue = 0x33;
        break;
        case '"':
            keyType = 0x02;
            keyValue = 0x34;
        break;
        case '~':
            keyType = 0x02;
            keyValue = 0x35;
        break;
        case '<':
            keyType = 0x02;
            keyValue = 0x36;
        break;
        case '>':
            keyType = 0x02;
            keyValue = 0x37;
        break;
        case '?':
            keyType = 0x02;
            keyValue = 0x38;
        break;

        default:
            printf("[fun:%s - Line:%d]unable to support symbol:0x%x\n", __FUNCTION__, __LINE__, symbol);
        return false;
    }

    memset(report, 0, 8);
    report[0] = keyType;
    report[2] = keyValue;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset(report, 0, 8);
    report[0] = keyType;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    memset(report, 0, 8);
    report[0] = 0x00;
    report[2] = 0x00;
    write(key_fd, report, 8);
    DELAY_TIME();

    return true;
}

static bool Hidg_Dev_Init(char *key_path, char *mouse_path)
{
    key_fd = open(key_path, O_RDWR, 0666);
    if(key_fd < 0)
    {
        return false;
    }


    return true;
}

static void Hidg_Dev_DeInit(void)
{
    close(key_fd);
    key_fd = -1;
}


void ST_Flush(void)
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

MI_U32 ST_RGN_Init()
{
//	MI_U32 u32Width, u32Height;
//    MI_SYS_Rotate_e enRotateType = E_MI_SYS_ROTATE_NONE;
//    MI_RGN_ChnPortParam_t stRgnChnPortParam;
//    MI_RGN_ChnPort_t stRgnChnPort;
    MI_RGN_HANDLE hRgnHandle;
    ST_OSD_Attr_T stOsdAttr;

    //ST_DBG("enRgnMode:%d\n", g_stRgnOsd.enRgnMode);
    //printf("enRgnMode:%d\n", g_stRgnOsd.enRgnMode);

    hRgnHandle = 0;

    memset(&stOsdAttr, 0, sizeof(ST_OSD_Attr_T));

    stOsdAttr.stRect.u32X = 0;
    stOsdAttr.stRect.u32Y = 0;
    stOsdAttr.stRect.u16PicW = 1024;//stSizeBefore.u32Width;
    stOsdAttr.stRect.u16PicH = 480; //stSizeBefore.u32Height;
    stOsdAttr.ePixelFmt = E_MI_RGN_PIXEL_FORMAT_ARGB1555;

    stOsdAttr.stRgnChnPort.eModId = E_MI_RGN_MODID_VPE;
    stOsdAttr.stRgnChnPort.s32DevId = 0;
    stOsdAttr.stRgnChnPort.s32ChnId = 0;
    stOsdAttr.stRgnChnPort.s32OutputPortId = 0;
    ExecFunc(ST_OSD_Init(hRgnHandle, &stOsdAttr), MI_RGN_OK);

	return MI_SUCCESS;
}


MI_U32 ST_Vpe_Divp_Bind()
{
    MI_VPE_PortMode_t stVpeMode;
	MI_DIVP_ChnAttr_t stDivpChnAttr;
	MI_DIVP_OutputPortAttr_t stDivpPortAttr;
	MI_SYS_ChnPort_t stChnOutputPort;
	ST_Sys_BindInfo_T stBindInfo;
	ST_Panel_Attr_T *pstPanelAttr = g_stPanelAttr;
	memset(&stDivpChnAttr, 0, sizeof(MI_DIVP_ChnAttr_t));
	memset(&stVpeMode, 0, sizeof(MI_VPE_PortMode_t));
	memset(&stDivpPortAttr, 0, sizeof(MI_DIVP_OutputPortAttr_t));
	memset(&stBindInfo, 0, sizeof(ST_Sys_BindInfo_T));
	memset(&stChnOutputPort, 0, sizeof(MI_SYS_ChnPort_t));
	ExecFunc(MI_VPE_GetPortMode(0, 3, &stVpeMode), MI_VPE_OK);

	// init divp channel
	stDivpChnAttr.bHorMirror = FALSE;
    stDivpChnAttr.bVerMirror = FALSE;
    stDivpChnAttr.eDiType = E_MI_DIVP_DI_TYPE_OFF;
    stDivpChnAttr.eRotateType = E_MI_SYS_ROTATE_NONE;
    stDivpChnAttr.eTnrLevel = E_MI_DIVP_TNR_LEVEL_OFF;
    stDivpChnAttr.stCropRect.u16X = 0;
    stDivpChnAttr.stCropRect.u16Y = 0;
    stDivpChnAttr.u32MaxWidth = stVpeMode.u16Width;
    stDivpChnAttr.u32MaxHeight = stVpeMode.u16Height;
	
	//Create divp channel 0 for Yuyan decoder
    ExecFunc(MI_DIVP_CreateChn(0, &stDivpChnAttr), MI_SUCCESS);
    stDivpPortAttr.u32Width = BARCODE_IN_WIDTH; //stVpeMode.u16Width;
	stDivpPortAttr.u32Height = BARCODE_IN_HIGH; //stVpeMode.u16Height;
	stDivpPortAttr.eCompMode = E_MI_SYS_COMPRESS_MODE_NONE;
	stDivpPortAttr.ePixelFormat = E_MI_SYS_PIXEL_FRAME_YUV_SEMIPLANAR_420;
	ExecFunc(MI_DIVP_SetOutputPortAttr(0, &stDivpPortAttr), MI_SUCCESS);
	ExecFunc(MI_DIVP_StartChn(0), MI_SUCCESS);
	
	//Create divp channel 2 for disp
    ExecFunc(MI_DIVP_CreateChn(2, &stDivpChnAttr), MI_SUCCESS);
    stDivpPortAttr.u32Width = pstPanelAttr->u32Width; //stVpeMode.u16Width;
	stDivpPortAttr.u32Height = pstPanelAttr->u32Height; //stVpeMode.u16Height;
	stDivpPortAttr.eCompMode = E_MI_SYS_COMPRESS_MODE_NONE;
	stDivpPortAttr.ePixelFormat = E_MI_SYS_PIXEL_FRAME_YUV_SEMIPLANAR_420;
	ExecFunc(MI_DIVP_SetOutputPortAttr(2, &stDivpPortAttr), MI_SUCCESS);
	ExecFunc(MI_DIVP_StartChn(2), MI_SUCCESS);
	
	//Create divp channel 1 for venc
	stDivpChnAttr.stCropRect.u16X = 0;
	stDivpChnAttr.stCropRect.u16Y = 0;
	stDivpChnAttr.stCropRect.u16Width = 1280;
	stDivpChnAttr.stCropRect.u16Height = 720;
	stDivpChnAttr.u32MaxWidth = 1920;
	stDivpChnAttr.u32MaxHeight = 1080;
    ExecFunc(MI_DIVP_CreateChn(1, &stDivpChnAttr), MI_SUCCESS);
    stDivpPortAttr.u32Width = 1280; //stVpeMode.u16Width;
	stDivpPortAttr.u32Height = 720; //stVpeMode.u16Height;
	stDivpPortAttr.eCompMode = E_MI_SYS_COMPRESS_MODE_NONE;
	stDivpPortAttr.ePixelFormat = E_MI_SYS_PIXEL_FRAME_YUV_SEMIPLANAR_420;
	ExecFunc(MI_DIVP_SetOutputPortAttr(1, &stDivpPortAttr), MI_SUCCESS);
	ExecFunc(MI_DIVP_StartChn(1), MI_SUCCESS);
	
	//Bind vpe to divp channel 0 for zxing
	stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_VPE;
	stBindInfo.stSrcChnPort.u32DevId = 0;
	stBindInfo.stSrcChnPort.u32ChnId = 0;
	stBindInfo.stSrcChnPort.u32PortId = 0;
	stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_DIVP;
	stBindInfo.stDstChnPort.u32DevId = 0;
	stBindInfo.stDstChnPort.u32ChnId = 0;
	stBindInfo.stDstChnPort.u32PortId = 0;
	stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
	stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
	stBindInfo.eBindType = E_MI_SYS_BIND_TYPE_FRAME_BASE;
	ExecFunc(MI_SYS_SetChnOutputPortDepth(&stBindInfo.stDstChnPort, 2, 4), MI_SUCCESS);
	STCHECKRESULT(ST_Sys_Bind(&stBindInfo));

	//Bind vpe to divp channel 1 for venc
	stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_VPE;
	stBindInfo.stSrcChnPort.u32DevId = 0;
	stBindInfo.stSrcChnPort.u32ChnId = 0;
	stBindInfo.stSrcChnPort.u32PortId = 0;
	
	stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_DIVP;
	stBindInfo.stDstChnPort.u32DevId = 0;
	stBindInfo.stDstChnPort.u32ChnId = 1;
	stBindInfo.stDstChnPort.u32PortId = 0;
	stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
	stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
	stBindInfo.eBindType = E_MI_SYS_BIND_TYPE_FRAME_BASE;
	ExecFunc(MI_SYS_SetChnOutputPortDepth(&stBindInfo.stDstChnPort, 2, 4), MI_SUCCESS);
	STCHECKRESULT(ST_Sys_Bind(&stBindInfo));
	
	//Bind vpe to divp channel 2 for disp
	stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_VPE;
	stBindInfo.stSrcChnPort.u32DevId = 0;
	stBindInfo.stSrcChnPort.u32ChnId = 0;
	stBindInfo.stSrcChnPort.u32PortId = 0;
	
	stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_DIVP;
	stBindInfo.stDstChnPort.u32DevId = 0;
	stBindInfo.stDstChnPort.u32ChnId = 2;
	stBindInfo.stDstChnPort.u32PortId = 0;
	stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
	stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
	stBindInfo.eBindType = E_MI_SYS_BIND_TYPE_FRAME_BASE;
	ExecFunc(MI_SYS_SetChnOutputPortDepth(&stBindInfo.stDstChnPort, 2, 4), MI_SUCCESS);
	STCHECKRESULT(ST_Sys_Bind(&stBindInfo));
	
	return MI_SUCCESS;
}

MI_U32 ST_Vpe_Divp_UnBind()
{
	ST_Sys_BindInfo_T stBindInfo;

	memset(&stBindInfo, 0, sizeof(ST_Sys_BindInfo_T));
	stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_VPE;
	stBindInfo.stSrcChnPort.u32DevId = 0;
	stBindInfo.stSrcChnPort.u32ChnId = 0;
	stBindInfo.stSrcChnPort.u32PortId = 0;
	
	stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_DIVP;
	stBindInfo.stDstChnPort.u32DevId = 0;
	stBindInfo.stDstChnPort.u32ChnId = 0;
	stBindInfo.stDstChnPort.u32PortId = 0;
	stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
	stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
	STCHECKRESULT(ST_Sys_UnBind(&stBindInfo));
	
	stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_DIVP;
	stBindInfo.stDstChnPort.u32DevId = 0;
	stBindInfo.stDstChnPort.u32ChnId = 1;
	stBindInfo.stDstChnPort.u32PortId = 0;
	stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
	stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
	STCHECKRESULT(ST_Sys_UnBind(&stBindInfo));
	
	stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_DIVP;
	stBindInfo.stDstChnPort.u32DevId = 0;
	stBindInfo.stDstChnPort.u32ChnId = 2;
	stBindInfo.stDstChnPort.u32PortId = 0;
	stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
	stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
	STCHECKRESULT(ST_Sys_UnBind(&stBindInfo));

	//deinit divp channel
	ExecFunc(MI_SYS_SetChnOutputPortDepth(&stBindInfo.stDstChnPort, 0, 4), MI_SUCCESS);
	ExecFunc(MI_DIVP_StopChn(0), MI_SUCCESS);
    ExecFunc(MI_DIVP_DestroyChn(0), MI_SUCCESS);
	
	//deinit divp channel
	ExecFunc(MI_SYS_SetChnOutputPortDepth(&stBindInfo.stDstChnPort, 0, 4), MI_SUCCESS);
	ExecFunc(MI_DIVP_StopChn(1), MI_SUCCESS);
    ExecFunc(MI_DIVP_DestroyChn(1), MI_SUCCESS);

	//deinit divp channel
	ExecFunc(MI_SYS_SetChnOutputPortDepth(&stBindInfo.stDstChnPort, 0, 4), MI_SUCCESS);
	ExecFunc(MI_DIVP_StopChn(2), MI_SUCCESS);
    ExecFunc(MI_DIVP_DestroyChn(2), MI_SUCCESS);
	
	return MI_SUCCESS;
}

MI_U32 ST_PanelStart(void)
{
    ST_Panel_Attr_T *pstPanelAttr = g_stPanelAttr;

    MI_DISP_DEV DispDev = 0;
    MI_U32 u32DispWidth = pstPanelAttr->u32Width;
    MI_U32 u32DispHeight = pstPanelAttr->u32Height;
    
    MI_PANEL_IntfType_e eIntfType = E_MI_PNL_INTF_TTL;

    /************************************************
    Step1:  panel init
    *************************************************/
    STCHECKRESULT(MI_PANEL_Init(eIntfType));

    /************************************************
    Step2:  set disp pub 
    *************************************************/
    MI_DISP_PubAttr_t stPubAttr;
    memset(&stPubAttr, 0x0, sizeof(MI_DISP_PubAttr_t));
    
    stPubAttr.u32BgColor = YUYV_BLACK;
    stPubAttr.eIntfType = E_MI_DISP_INTF_TTL;
    stPubAttr.eIntfSync =  E_MI_DISP_OUTPUT_USER;
    STCHECKRESULT(MI_DISP_SetPubAttr(DispDev,  &stPubAttr));
    STCHECKRESULT(MI_DISP_Enable(DispDev));
    
    /************************************************
    Step3:  set layer
    *************************************************/
    MI_DISP_LAYER            DispLayer = 0;
    MI_SYS_PixelFormat_e     ePixFormat = E_MI_SYS_PIXEL_FRAME_YUV_SEMIPLANAR_420;  
    MI_DISP_VideoLayerAttr_t stLayerAttr;
    

    memset(&stLayerAttr, 0x0, sizeof(MI_DISP_VideoLayerAttr_t));

    stLayerAttr.stVidLayerDispWin.u16X = 0;
    stLayerAttr.stVidLayerDispWin.u16Y = 0;
    stLayerAttr.stVidLayerDispWin.u16Width = u32DispWidth;
    stLayerAttr.stVidLayerDispWin.u16Height = u32DispHeight;

    stLayerAttr.stVidLayerSize.u16Width = u32DispWidth;
    stLayerAttr.stVidLayerSize.u16Height = u32DispHeight;

    stLayerAttr.ePixFormat = ePixFormat;

    STCHECKRESULT(MI_DISP_BindVideoLayer(DispLayer,DispDev));
    STCHECKRESULT(MI_DISP_SetVideoLayerAttr(DispLayer, &stLayerAttr));
    STCHECKRESULT(MI_DISP_EnableVideoLayer(DispLayer));
    
    /************************************************
    Step4:  set inputport
    *************************************************/
    MI_U8 u8DispInport = 0;
    
    MI_DISP_InputPortAttr_t stInputPortAttr;
    MI_DISP_VidWinRect_t stWinRect;    
    
    //MI_PANEL_ParamConfig_t stPanelParam;
    
    //memset(&stPanelParam, 0x0, sizeof(MI_PANEL_ParamConfig_t));
    memset(&stWinRect, 0x0, sizeof(MI_DISP_VidWinRect_t));
    memset(&stInputPortAttr, 0x0, sizeof(MI_DISP_InputPortAttr_t));
    
    //MI_PANEL_GetPanelParam(&stPanelParam);
    
    stInputPortAttr.stDispWin.u16X = 0;
    stInputPortAttr.stDispWin.u16Y = 0;
    stInputPortAttr.stDispWin.u16Width =u32DispWidth;
    stInputPortAttr.stDispWin.u16Height = u32DispHeight;
    
    stInputPortAttr.u16SrcWidth =u32DispWidth;
    stInputPortAttr.u16SrcHeight = u32DispHeight;
    
    stWinRect.u16Width = u32DispWidth;
    stWinRect.u16Height = u32DispHeight;
        

    printf("%s:%d layer:%d port:%d srcwidth:%d srcheight:%d x:%d y:%d outwidth:%d outheight:%d\n",__FUNCTION__,__LINE__,
        DispLayer,u8DispInport,
        stInputPortAttr.u16SrcWidth,stInputPortAttr.u16SrcHeight,
        stInputPortAttr.stDispWin.u16X,stInputPortAttr.stDispWin.u16Y,
        stInputPortAttr.stDispWin.u16Width,stInputPortAttr.stDispWin.u16Height);
    
    STCHECKRESULT(MI_DISP_SetInputPortAttr(DispLayer, u8DispInport, &stInputPortAttr));
    STCHECKRESULT(MI_DISP_EnableInputPort(DispLayer, u8DispInport));
    STCHECKRESULT(MI_DISP_SetInputPortSyncMode(DispLayer, u8DispInport, E_MI_DISP_SYNC_MODE_FREE_RUN));

#if 1
	/************************************************
    Step5:  bind divp -> disp
    *************************************************/
    ST_Sys_BindInfo_T stBindInfo;
    memset(&stBindInfo, 0x0, sizeof(ST_Sys_BindInfo_T));
    stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_DIVP;
    stBindInfo.stSrcChnPort.u32DevId = 0;
    stBindInfo.stSrcChnPort.u32ChnId = 2;
    stBindInfo.stSrcChnPort.u32PortId = 0;
    stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_DISP;
    stBindInfo.stDstChnPort.u32DevId =  0;
    stBindInfo.stDstChnPort.u32ChnId = 0;
    stBindInfo.stDstChnPort.u32PortId = 0;
    stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
    stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
    stBindInfo.eBindType = E_MI_SYS_BIND_TYPE_FRAME_BASE;

    STCHECKRESULT(ST_Sys_Bind(&stBindInfo));
	
#else
    /************************************************
    Step5:  bind vpe->disp
    *************************************************/
    ST_Sys_BindInfo_T stBindInfo;
    memset(&stBindInfo, 0x0, sizeof(ST_Sys_BindInfo_T));
    stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_VPE;
    stBindInfo.stSrcChnPort.u32DevId = 0;
    stBindInfo.stSrcChnPort.u32ChnId = 0;
    stBindInfo.stSrcChnPort.u32PortId = 0;
    stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_DISP;
    stBindInfo.stDstChnPort.u32DevId =  0;
    stBindInfo.stDstChnPort.u32ChnId = 0;
    stBindInfo.stDstChnPort.u32PortId = 0;
    stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
    stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
    stBindInfo.eBindType = E_MI_SYS_BIND_TYPE_FRAME_BASE;

    STCHECKRESULT(ST_Sys_Bind(&stBindInfo));
#endif    

    return MI_SUCCESS;
}

MI_U32 ST_PanelStop(void)
{
    MI_U32 DispLayer = 0;
    MI_U32 DispInport = 0;
    MI_U32 DispDev = 0;

    ST_Sys_BindInfo_T stBindInfo;

    memset(&stBindInfo, 0x0, sizeof(ST_Sys_BindInfo_T));
    stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_DIVP;
    stBindInfo.stSrcChnPort.u32DevId = 0;
    stBindInfo.stSrcChnPort.u32ChnId = 2;
    stBindInfo.stSrcChnPort.u32PortId = 0;

    stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_DISP;
    stBindInfo.stDstChnPort.u32DevId = 0;
    stBindInfo.stDstChnPort.u32ChnId = 0;
    stBindInfo.stDstChnPort.u32PortId = 0;

    stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
    stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
    STCHECKRESULT(ST_Sys_UnBind(&stBindInfo));
    
    STCHECKRESULT(MI_DISP_DisableInputPort(DispLayer, DispInport));
    
    STCHECKRESULT(MI_DISP_DisableVideoLayer(DispLayer));
    STCHECKRESULT(MI_DISP_UnBindVideoLayer(DispLayer, DispDev));
    
    STCHECKRESULT(MI_DISP_Disable(DispLayer));
    STCHECKRESULT(MI_PANEL_DeInit());

    return 0;
}

MI_U32 ST_BaseModuleInit(void)
{
    ST_Panel_Attr_T *pstPanelAttr = g_stPanelAttr;
 
    MI_U32 u32CapWidth = 0, u32CapHeight = 0;
    MI_SYS_PixelFormat_e ePixFormat;
    ST_VPE_ChannelInfo_T stVpeChannelInfo;
    ST_Sys_BindInfo_T stBindInfo;
    MI_SNR_PADInfo_t  stPad0Info;
    MI_SNR_PlaneInfo_t stSnrPlane0Info;
    MI_U32 u32ResCount =0;
    MI_U8 u8ResIndex =0;
    MI_SNR_Res_t stRes;
    MI_U32 u32ChocieRes =0;
    
    MI_VIF_FrameRate_e eFrameRate = E_MI_VIF_FRAMERATE_FULL;
    MI_VIF_HDRType_e eVifHdrType = E_MI_VIF_HDR_TYPE_OFF;
    MI_VPE_HDRType_e eVpeHdrType = E_MI_VPE_HDR_TYPE_OFF;
    MI_VPE_3DNR_Level_e en3dNrLevel = E_MI_VPE_3DNR_LEVEL_OFF;
    MI_SYS_Rotate_e enRotation = E_MI_SYS_ROTATE_NONE;
    
    MI_SNR_PAD_ID_e eSnrPad = pstPanelAttr->eSnrPad;
    MI_VIF_DEV s32vifDev = pstPanelAttr->s32vifDev;
    MI_VIF_CHN s32vifChn = s32vifDev*4;

    memset(&stPad0Info, 0x0, sizeof(MI_SNR_PADInfo_t));
    memset(&stSnrPlane0Info, 0x0, sizeof(MI_SNR_PlaneInfo_t));
    memset(&stRes, 0x0, sizeof(MI_SNR_Res_t));

    /************************************************
    Step1:  init SYS
    *************************************************/
    STCHECKRESULT(ST_Sys_Init());

    if(eVifHdrType > 0)
        MI_SNR_SetPlaneMode(eSnrPad, TRUE);
    else
        MI_SNR_SetPlaneMode(eSnrPad, FALSE);

    MI_SNR_QueryResCount(eSnrPad, &u32ResCount);
    for(u8ResIndex=0; u8ResIndex < u32ResCount; u8ResIndex++)
    {
        MI_SNR_GetRes(eSnrPad, u8ResIndex, &stRes);
        printf("index %d, Crop(%d,%d,%d,%d), outputsize(%d,%d), maxfps %d, minfps %d, ResDesc %s\n",
        u8ResIndex,
        stRes.stCropRect.u16X, stRes.stCropRect.u16Y, stRes.stCropRect.u16Width,stRes.stCropRect.u16Height,
        stRes.stOutputSize.u16Width, stRes.stOutputSize.u16Height,
        stRes.u32MaxFps,stRes.u32MinFps,
        stRes.strResDesc);
    }
#if 0
    printf("choice which resolution use, cnt %d\n", u32ResCount);
    do
    {
        scanf("%d", &u32ChocieRes);
        ST_Flush();
        MI_SNR_QueryResCount(eSnrPad, &u32ResCount);
        if(u32ChocieRes >= u32ResCount)
        {
            printf("choice err res %d > =cnt %d\n", u32ChocieRes, u32ResCount);
        }
    }while(u32ChocieRes >= u32ResCount);
#endif
    u32ChocieRes = 0;
    printf("You select %d res\n", u32ChocieRes);

    MI_SNR_SetRes(eSnrPad,u32ChocieRes);
    MI_SNR_Enable(eSnrPad);

    MI_SNR_GetPadInfo(eSnrPad, &stPad0Info);
    MI_SNR_GetPlaneInfo(eSnrPad, 0, &stSnrPlane0Info);
	MI_SNR_SetFps(eSnrPad,SENSOR_RGB_FPS);

    //g_u32CapWidth = stSnrPlane0Info.stCapRect.u16Width;
    //g_u32CapHeight = stSnrPlane0Info.stCapRect.u16Height;
    u32CapWidth = stSnrPlane0Info.stCapRect.u16Width;
    u32CapHeight = stSnrPlane0Info.stCapRect.u16Height;
    eFrameRate = E_MI_VIF_FRAMERATE_FULL;
    ePixFormat = (MI_SYS_PixelFormat_e)RGB_BAYER_PIXEL(stSnrPlane0Info.ePixPrecision, stSnrPlane0Info.eBayerId);
	
	printf("========> Sensor output (width:%d - height:%d)\n", u32CapWidth, u32CapHeight);
    
    /************************************************
    Step2:  init VIF(for IPC, only one dev)
    *************************************************/
    MI_VIF_DevAttr_t stDevAttr;
    memset(&stDevAttr, 0x0, sizeof(MI_VIF_DevAttr_t));

    stDevAttr.eIntfMode = stPad0Info.eIntfMode;
    stDevAttr.eWorkMode = E_MI_VIF_WORK_MODE_RGB_FRAMEMODE;
    stDevAttr.eHDRType = eVifHdrType;
    if(stDevAttr.eIntfMode == E_MI_VIF_MODE_BT656)
        stDevAttr.eClkEdge = stPad0Info.unIntfAttr.stBt656Attr.eClkEdge;
    else
        stDevAttr.eClkEdge = E_MI_VIF_CLK_EDGE_DOUBLE;
    
    if(stDevAttr.eIntfMode == E_MI_VIF_MODE_MIPI)
        stDevAttr.eDataSeq =stPad0Info.unIntfAttr.stMipiAttr.eDataYUVOrder;
    else
        stDevAttr.eDataSeq = E_MI_VIF_INPUT_DATA_YUYV;

    if(stDevAttr.eIntfMode == E_MI_VIF_MODE_BT656)
        memcpy(&stDevAttr.stSyncAttr, &stPad0Info.unIntfAttr.stBt656Attr.stSyncAttr, sizeof(MI_VIF_SyncAttr_t));

    stDevAttr.eBitOrder = E_MI_VIF_BITORDER_NORMAL;

    ExecFunc(MI_VIF_SetDevAttr(s32vifDev, &stDevAttr), MI_SUCCESS);
    ExecFunc(MI_VIF_EnableDev(s32vifDev), MI_SUCCESS);
    //STCHECKRESULT(ST_Vif_EnableDev(s32vifDev, eVifHdrType, &stPad0Info));

    ST_VIF_PortInfo_T stVifPortInfoInfo;
    memset(&stVifPortInfoInfo, 0, sizeof(ST_VIF_PortInfo_T));
    stVifPortInfoInfo.u32RectX = 0;
    stVifPortInfoInfo.u32RectY = 0;
    stVifPortInfoInfo.u32RectWidth = u32CapWidth;
    stVifPortInfoInfo.u32RectHeight = u32CapHeight;
    stVifPortInfoInfo.u32DestWidth = u32CapWidth;
    stVifPortInfoInfo.u32DestHeight = u32CapHeight;
    stVifPortInfoInfo.eFrameRate = eFrameRate;
    stVifPortInfoInfo.ePixFormat = ePixFormat;
    STCHECKRESULT(ST_Vif_CreatePort(s32vifChn, 0, &stVifPortInfoInfo));
    STCHECKRESULT(ST_Vif_StartPort(0, s32vifChn, 0));
    
    if (enRotation != E_MI_SYS_ROTATE_NONE)
    {
        MI_BOOL bMirror = FALSE, bFlip = FALSE;

        switch(enRotation)
        {
        case E_MI_SYS_ROTATE_NONE:
            bMirror= FALSE;
            bFlip = FALSE;
            break;
        case E_MI_SYS_ROTATE_90:
            bMirror = FALSE;
            bFlip = TRUE;
            break;
        case E_MI_SYS_ROTATE_180:
            bMirror = TRUE;
            bFlip = TRUE;
            break;
        case E_MI_SYS_ROTATE_270:
            bMirror = TRUE;
            bFlip = FALSE;
            break;
        default:
            break;
        }

        MI_SNR_SetOrien(eSnrPad, bMirror, bFlip);
    }
    memset(&stVpeChannelInfo, 0, sizeof(ST_VPE_ChannelInfo_T));
	if(eSnrPad == E_MI_SNR_PAD_ID_0)
		stVpeChannelInfo.eBindSensorId = E_MI_VPE_SENSOR0;
	else if(eSnrPad == E_MI_SNR_PAD_ID_1)
		stVpeChannelInfo.eBindSensorId = E_MI_VPE_SENSOR1;
	else if(eSnrPad == E_MI_SNR_PAD_ID_2)
		stVpeChannelInfo.eBindSensorId = E_MI_VPE_SENSOR2;
	else if(eSnrPad == E_MI_SNR_PAD_ID_3)
		stVpeChannelInfo.eBindSensorId = E_MI_VPE_SENSOR3;
	else
		stVpeChannelInfo.eBindSensorId = E_MI_VPE_SENSOR_INVALID;
    stVpeChannelInfo.u16VpeMaxW = u32CapWidth;
    stVpeChannelInfo.u16VpeMaxH = u32CapHeight;
    stVpeChannelInfo.u32X = 0;
    stVpeChannelInfo.u32Y = 0;
    stVpeChannelInfo.u16VpeCropW = 0;
    stVpeChannelInfo.u16VpeCropH = 0;
    stVpeChannelInfo.eRunningMode = E_MI_VPE_RUN_CAM_MODE;//E_MI_VPE_RUN_REALTIME_MODE;
    stVpeChannelInfo.eFormat = ePixFormat;
    stVpeChannelInfo.e3DNRLevel = en3dNrLevel;
    stVpeChannelInfo.eHDRtype = eVpeHdrType;
    stVpeChannelInfo.bRotation = FALSE;
    STCHECKRESULT(ST_Vpe_CreateChannel(0, &stVpeChannelInfo));
    STCHECKRESULT(ST_Vpe_StartChannel(0));
    memset(&stBindInfo, 0x0, sizeof(ST_Sys_BindInfo_T));
    stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_VIF;
    stBindInfo.stSrcChnPort.u32DevId = s32vifDev;
    stBindInfo.stSrcChnPort.u32ChnId = s32vifChn;
    stBindInfo.stSrcChnPort.u32PortId = 0;
    stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_VPE;
    stBindInfo.stDstChnPort.u32DevId = 0;
    stBindInfo.stDstChnPort.u32ChnId = 0;
    stBindInfo.stDstChnPort.u32PortId = 0;
    stBindInfo.eBindType = E_MI_SYS_BIND_TYPE_FRAME_BASE;//E_MI_SYS_BIND_TYPE_REALTIME;
    stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
    stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
    STCHECKRESULT(ST_Sys_Bind(&stBindInfo));

    ST_VPE_PortInfo_T stVpePortInfo;
    memset(&stVpePortInfo, 0, sizeof(ST_VPE_PortInfo_T));
    stVpePortInfo.DepVpeChannel = 0;
    stVpePortInfo.u16OutputWidth = 1280;
    stVpePortInfo.u16OutputHeight = 720;
    stVpePortInfo.ePixelFormat = E_MI_SYS_PIXEL_FRAME_YUV_SEMIPLANAR_420;
    stVpePortInfo.eCompressMode = E_MI_SYS_COMPRESS_MODE_NONE;
    STCHECKRESULT(ST_Vpe_StartPort(0 , &stVpePortInfo)); //bind to disp for panenl & divp for barcode scanning
    
    return MI_SUCCESS;
}


MI_U32 ST_BaseModuleUnInit(void)
{
    ST_Sys_BindInfo_T stBindInfo;

 #if USE_SNR_PAD_ID_1
    MI_U32 u32VifDev = 0;
    MI_U32 u32VifChn = 0;
 #else
    MI_U32 u32VifDev = 1;
    MI_U32 u32VifChn = 4;
#endif
    memset(&stBindInfo, 0x0, sizeof(ST_Sys_BindInfo_T));
    stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_VIF;
    stBindInfo.stSrcChnPort.u32DevId = u32VifDev;
    stBindInfo.stSrcChnPort.u32ChnId = u32VifChn;
    stBindInfo.stSrcChnPort.u32PortId = 0;

    stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_VPE;
    stBindInfo.stDstChnPort.u32DevId = 0;
    stBindInfo.stDstChnPort.u32ChnId = 0;
    stBindInfo.stDstChnPort.u32PortId = 0;

    stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
    stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
    STCHECKRESULT(ST_Sys_UnBind(&stBindInfo));

    /************************************************
    Step1:  destory VPE
    *************************************************/
    STCHECKRESULT(ST_Vpe_StopChannel(0));
    STCHECKRESULT(ST_Vpe_DestroyChannel(0));

    /************************************************
    Step2:  destory VIF
    *************************************************/
    STCHECKRESULT(ST_Vif_StopPort(u32VifChn, 0));
    STCHECKRESULT(ST_Vif_DisableDev(u32VifDev));

    /************************************************
    Step3:  destory SYS
    *************************************************/
    STCHECKRESULT(ST_Sys_Exit());

    return MI_SUCCESS;
}

MI_S32 ST_VencStart(MI_U32 u32MaxVencWidth, MI_U32 u32MaxVencHeight, MI_U32 u32VencChn)
{
    MI_U32 u32VenBitRate = 0;
    MI_U32 u32Fps =0;
    ST_VencAttr_t *pStStreamAttr = &gstVencattr[u32VencChn];
    MI_SNR_PAD_ID_e eSnrPadId = E_MI_SNR_PAD_ID_0;
    MI_VENC_ChnAttr_t stChnAttr;
	ST_Sys_BindInfo_T stBindInfo;

	memset(pStStreamAttr, 0, sizeof(ST_VencAttr_t));
	pStStreamAttr->vencChn = 0;
	pStStreamAttr->eType = E_MI_VENC_MODTYPE_JPEGE;// E_MI_VENC_MODTYPE_H264E;
	pStStreamAttr->u32Width = 1280; 
	pStStreamAttr->u32Height = 720;

    MI_SNR_GetFps(eSnrPadId, &u32Fps);
    memset(&stChnAttr, 0, sizeof(MI_VENC_ChnAttr_t));

    u32VenBitRate = ((pStStreamAttr->u32Width * pStStreamAttr->u32Height + 500000)/1000000)*1024*1024;
    if(u32VenBitRate == 0)
	{
        u32VenBitRate = 2*1024*1024;
	}

    printf("chn %d, pichwidth %d, height %d, MaxWidth %d, MaxHeight %d bitrate %d, fps %d \n", u32VencChn,
        pStStreamAttr->u32Width, pStStreamAttr->u32Height, u32MaxVencWidth, u32MaxVencHeight, u32VenBitRate, u32Fps);
	system("sync");
	sleep(1);
    if(pStStreamAttr->eType == E_MI_VENC_MODTYPE_H264E)
    {
		stChnAttr.stVeAttr.eType = E_MI_VENC_MODTYPE_H264E;
        stChnAttr.stVeAttr.stAttrH264e.u32PicWidth = pStStreamAttr->u32Width;
        stChnAttr.stVeAttr.stAttrH264e.u32PicHeight = pStStreamAttr->u32Height;
        stChnAttr.stVeAttr.stAttrH264e.u32MaxPicWidth = u32MaxVencWidth;
		stChnAttr.stVeAttr.stAttrH264e.u32MaxPicHeight = u32MaxVencHeight;
        stChnAttr.stVeAttr.stAttrH264e.u32BFrameNum = 2;
        stChnAttr.stVeAttr.stAttrH264e.bByFrame = TRUE;
        

        stChnAttr.stRcAttr.eRcMode = E_MI_VENC_RC_MODE_H264CBR;
        stChnAttr.stRcAttr.stAttrH264Cbr.u32BitRate = u32VenBitRate;
        stChnAttr.stRcAttr.stAttrH264Cbr.u32FluctuateLevel = 0;
        stChnAttr.stRcAttr.stAttrH264Cbr.u32Gop = 30;
        stChnAttr.stRcAttr.stAttrH264Cbr.u32SrcFrmRateNum = u32Fps;
        stChnAttr.stRcAttr.stAttrH264Cbr.u32SrcFrmRateDen = 1;
        stChnAttr.stRcAttr.stAttrH264Cbr.u32StatTime = 0;
    }
	else if(pStStreamAttr->eType == E_MI_VENC_MODTYPE_JPEGE)
    {
        stChnAttr.stVeAttr.eType = E_MI_VENC_MODTYPE_JPEGE;
        stChnAttr.stVeAttr.stAttrJpeg.u32PicWidth = pStStreamAttr->u32Width;
        stChnAttr.stVeAttr.stAttrJpeg.u32PicHeight = pStStreamAttr->u32Height;
        stChnAttr.stVeAttr.stAttrJpeg.u32MaxPicWidth = u32MaxVencWidth;
        stChnAttr.stVeAttr.stAttrJpeg.u32MaxPicHeight = u32MaxVencHeight;

        stChnAttr.stRcAttr.eRcMode = E_MI_VENC_RC_MODE_MJPEGFIXQP;
        stChnAttr.stRcAttr.stAttrMjpegCbr.u32BitRate = 30;
        stChnAttr.stRcAttr.stAttrMjpegCbr.u32SrcFrmRateNum = u32Fps;
        stChnAttr.stRcAttr.stAttrMjpegCbr.u32SrcFrmRateDen = 1;
    }

    stChnAttr.stVeAttr.eType = pStStreamAttr->eType;
    STCHECKRESULT(ST_Venc_CreateChannel(u32VencChn, &stChnAttr));

    MI_VENC_InputSourceConfig_t stVencSourceCfg;
    stVencSourceCfg.eInputSrcBufferMode = E_MI_VENC_INPUT_MODE_NORMAL_FRMBASE;
    MI_VENC_SetInputSourceConfig(u32VencChn, &stVencSourceCfg);
    STCHECKRESULT(ST_Venc_StartChannel(u32VencChn));
	
	memset(&stBindInfo, 0x0, sizeof(ST_Sys_BindInfo_T));
	stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_DIVP;
	stBindInfo.stSrcChnPort.u32DevId = 0;
	stBindInfo.stSrcChnPort.u32ChnId = 1;
	stBindInfo.stSrcChnPort.u32PortId = 0;

	stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_VENC;
	stBindInfo.stDstChnPort.u32DevId = 1;
	stBindInfo.stDstChnPort.u32ChnId = u32VencChn;
	stBindInfo.stDstChnPort.u32PortId = 0;

	stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
	stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
	stBindInfo.eBindType = E_MI_SYS_BIND_TYPE_FRAME_BASE;
	stBindInfo.u32BindParam = 0;
	STCHECKRESULT(ST_Sys_Bind(&stBindInfo));

    pStStreamAttr->bStart = TRUE;

    return MI_SUCCESS;
}


MI_S32 ST_VencStop(MI_U32 u32VencChn)
{
	ST_Sys_BindInfo_T stBindInfo;
	
	memset(&stBindInfo, 0x0, sizeof(ST_Sys_BindInfo_T));
	stBindInfo.stSrcChnPort.eModId = E_MI_MODULE_ID_DIVP;
	stBindInfo.stSrcChnPort.u32DevId = 0;
	stBindInfo.stSrcChnPort.u32ChnId = 1;
	stBindInfo.stSrcChnPort.u32PortId = 0;

	stBindInfo.stDstChnPort.eModId = E_MI_MODULE_ID_VENC;
	stBindInfo.stDstChnPort.u32DevId = 0;
	stBindInfo.stDstChnPort.u32ChnId = u32VencChn;
	stBindInfo.stDstChnPort.u32PortId = 0;

	stBindInfo.u32SrcFrmrate = SENSOR_RGB_FPS;
	stBindInfo.u32DstFrmrate = SENSOR_RGB_FPS;
	STCHECKRESULT(ST_Sys_UnBind(&stBindInfo));

    STCHECKRESULT(ST_Venc_StopChannel(u32VencChn));
    STCHECKRESULT(ST_Venc_DestoryChannel(u32VencChn));

    return MI_SUCCESS;
}	

#define DLA_PERSON_COLOR    RGB2PIXEL1555(255, 0, 0)
#define DLA_ANIMAL_COLOR    RGB2PIXEL1555(0, 255, 0)
#define DLA_MOBILE_COLOR    RGB2PIXEL1555(0, 0, 255)
#define DLA_OTHERS_COLOR    RGB2PIXEL1555(0, 0, 0)

static volatile int drawonce = 0;
MI_S32  ST_Do_Barcode(const MI_SYS_BufInfo_t *stBufInfo,MI_SYS_BUF_HANDLE hBufHandle)
{
	MI_RGN_CanvasInfo_t *pstCanvasInfo = NULL;
	ST_Point_T stPoint;
	stPoint.u32X = 8; 
	stPoint.u32Y = 8;
//    ST_Rect_T stRect;
//	stRect.u32X = 0;
//	stRect.u32X = 0;
//	stRect.u16PicW = 32;
//	stRect.u16PicH = 32;
//	const char *pOsdChar = NULL;
	unsigned char osdChar[2048] = {0};
	static unsigned char osdCharCmp[2048] = {0};
	static unsigned char image_buffer[BARCODE_IN_WIDTH*BARCODE_IN_HIGH*4] = {0};
	unsigned int retLen = 0;

    if (stBufInfo->eBufType == E_MI_SYS_BUFDATA_RAW)
    {
        printf("BUFDATA TYEP: E_MI_SYS_BUFDATA_RAW\n");
    }
    else if (stBufInfo->eBufType == E_MI_SYS_BUFDATA_FRAME)
    {
        memcpy(image_buffer, stBufInfo->stFrameData.pVirAddr[0], 1280*720);
        Decoding_Image(image_buffer, 1280, 720);
        retLen = GetResultLength();
        //printf("retLen:%d, \n", retLen);
#if 1
        if(retLen > 0 && retLen < sizeof(osdChar))
        {
            memset(osdChar, 0, sizeof(osdChar));
            GetDecoderResult(osdChar);
            printf("retLen:%d, strLen:%d, DrawText:%s\n", retLen,strlen((const char*)osdChar), osdChar);
            for(int i=0; i<retLen && i<128; i++)
            {
                if(i%8 == 0) printf("\n");

                printf("%02x-", osdChar[i]);
            }

            printf("\n");

            if(memcmp(osdChar,osdCharCmp, strlen((const char*)osdChar)) == 0)
            {
                return MI_SUCCESS;
            }
            memcpy(osdCharCmp, osdChar, strlen((const char*)osdChar));

            for(int i=0; i<retLen; i++)
            {
                if(osdChar[i] < 0x81)
                {
                    if((osdChar[i]>='a' && osdChar[i]<='z') || (osdChar[i]>='A' && osdChar[i]<='Z'))
                    {
                        Hid_Send_OneGBKEnglish(osdChar[i]);
                    }
                    else
                    {
                        Hid_Send_Symbol(osdChar[i]);
                    }
                }
                else if(osdChar[i] >= 0x81 && osdChar[i] <= 0xFE)
                {
                    if(osdChar[i] >= 0xB0 && osdChar[i] <= 0xF7)
                    {
                        Hid_Send_OneGBKChinese(osdChar[i], osdChar[i+1]);
                    }
                    i++;
                }
                else
                {
                    printf("[Fun:%s - Line:%d] Unsupport the charactor:%x02x\n", osdChar[i]);
                }
            }
#if 1
            ST_OSD_GetCanvasInfo(0, &pstCanvasInfo);
            ST_OSD_Clear(0, NULL);
            ST_OSD_DrawText(0, stPoint, (char *)osdChar, DLA_PERSON_COLOR, DMF_Font_Size_32x32);
            ST_OSD_Update(0);
#endif
        }
#endif

    }

    return MI_SUCCESS;
}



static MI_BOOL gBarcode_Run = FALSE;
void *ST_Barcode_thread(void *argc)
{
    printf("detect thread start\n");
	sleep(2);
    fd_set read_fds;
    struct timeval tv;
    MI_S32 s32Ret = 0;
    MI_SYS_ChnPort_t stChnOutputPort;
	MI_SYS_BufInfo_t        stBufInfo;
	MI_SYS_BUF_HANDLE       stBufHandle;
	tv.tv_sec = 0;
    tv.tv_usec = 100 * 1000;
	//get fd
	MI_S32 s32DivpFd;
	
	stChnOutputPort.eModId      = E_MI_MODULE_ID_DIVP;
    stChnOutputPort.u32DevId    = 0;
    stChnOutputPort.u32ChnId    = 0;
    stChnOutputPort.u32PortId   = 0;
    s32Ret = MI_SYS_GetFd(&stChnOutputPort, &s32DivpFd);
	gBarcode_Run = TRUE;
    if (s32Ret < 0)
    {
        printf("divp ch0, get fd. err\n");
		gBarcode_Run = FALSE;
    }

    printf("====>[Line:%d] Start to get divp buf in thread\n", __LINE__);
    while(gBarcode_Run)
    {
        FD_ZERO(&read_fds);
        FD_SET(s32DivpFd, &read_fds);
        s32Ret = select(s32DivpFd + 1, &read_fds, NULL, NULL, &tv);
        if (s32Ret < 0)
        {
            printf("select failed\n");
        }
        else if (0 == s32Ret)
        {
            //printf("select timeout\n");
        }
        else
        {
	        if(FD_ISSET(s32DivpFd, &read_fds))
	        {

	            memset(&stBufInfo, 0x0, sizeof(MI_SYS_BufInfo_t));
				s32Ret = MI_SYS_ChnOutputPortGetBuf(&stChnOutputPort, &stBufInfo, &stBufHandle);
	            if (MI_SUCCESS != s32Ret)
	            {
	                printf("get divp buffer fail,ret:%x\n",s32Ret);
					continue;
	            }
				ST_Do_Barcode(&stBufInfo,stBufHandle);
				MI_SYS_ChnOutputPortPutBuf(stBufHandle);
	        }
        }
   }
   return NULL;
}



#define RTSP_LISTEN_PORT        554
static Live555RTSPServer *g_pRTSPServer = NULL;
void *ST_OpenStream(char const *szStreamName, void *arg)
{
    MI_S32 s32Ret = MI_SUCCESS;

    ST_VencAttr_t *pstVencAttr = &gstVencattr[0];

    if(pstVencAttr[0].eType != E_MI_VENC_MODTYPE_JPEGE)
    {
        s32Ret = MI_VENC_RequestIdr(pstVencAttr->vencChn, TRUE);

        ST_DBG("open stream \"%s\" success, chn:%d\n", szStreamName, pstVencAttr->vencChn);

        if(MI_SUCCESS != s32Ret)
        {
            ST_WARN("request IDR fail, error:%x\n", s32Ret);
        }
    }
    return pstVencAttr;
}

MI_U32 u32GetCnt=0, u32ReleaseCnt=0;
int ST_VideoReadStream(void *handle, unsigned char *ucpBuf, int BufLen, struct timeval *p_Timestamp, void *arg)
{
    MI_SYS_BufInfo_t stBufInfo;
    MI_S32 s32Ret = MI_SUCCESS;
    MI_S32 len = 0;
    MI_U32 u32DevId = 0;
    MI_VENC_Stream_t stStream;
    MI_VENC_Pack_t stPack;
    MI_VENC_ChnStat_t stStat;
    MI_VENC_CHN vencChn ;

    if(handle == NULL)
    {
        return -1;
    }

    ST_VencAttr_t *pstStreamInfo = (ST_VencAttr_t *)handle;

    vencChn = pstStreamInfo->vencChn;

    if(pstStreamInfo->bStart == FALSE)
        return 0;

    s32Ret = MI_VENC_GetChnDevid(vencChn, &u32DevId);

    if(MI_SUCCESS != s32Ret)
    {
        ST_INFO("MI_VENC_GetChnDevid %d error, %X\n", vencChn, s32Ret);
    }

    memset(&stBufInfo, 0x0, sizeof(MI_SYS_BufInfo_t));
    memset(&stStream, 0, sizeof(stStream));
    memset(&stPack, 0, sizeof(stPack));
    stStream.pstPack = &stPack;
    stStream.u32PackCount = 1;
    s32Ret = MI_VENC_Query(vencChn, &stStat);

    if(s32Ret != MI_SUCCESS || stStat.u32CurPacks == 0)
    {
        return 0;
    }

    s32Ret = MI_VENC_GetStream(vencChn, &stStream, 40);

    if(MI_SUCCESS == s32Ret)
    {
        u32GetCnt++;
        len = stStream.pstPack[0].u32Len;
        memcpy(ucpBuf, stStream.pstPack[0].pu8Addr, MIN(len, BufLen));

        s32Ret = MI_VENC_ReleaseStream(vencChn, &stStream);
        if(s32Ret != MI_SUCCESS)
        {
            ST_WARN("RELEASE venc buffer fail\n");
        }
        u32ReleaseCnt ++;
        return len;
    }

    return 0;
}

int ST_CloseStream(void *handle, void *arg)
{
    if(handle == NULL)
    {
        return -1;
    }

    ST_VencAttr_t *pstStreamInfo = (ST_VencAttr_t *)handle;

    ST_DBG("close \"%s\" success\n", pstStreamInfo->szStreamName);
    return 0;
}

MI_S32 ST_RtspServerStart(void)
{
    unsigned int rtspServerPortNum = RTSP_LISTEN_PORT;
    int iRet = 0;
    char *urlPrefix = NULL;
	char szStreamName[128];
    int i = 0;
    ServerMediaSession *mediaSession = NULL;
    ServerMediaSubsession *subSession = NULL;
    Live555RTSPServer *pRTSPServer = NULL;

    pRTSPServer = new Live555RTSPServer();

    if(pRTSPServer == NULL)
    {
        ST_ERR("malloc error\n");
        return -1;
    }

    iRet = pRTSPServer->SetRTSPServerPort(rtspServerPortNum);
	
	sprintf(szStreamName, "video%d", 0);

    while(iRet < 0)
    {
        rtspServerPortNum++;

        if(rtspServerPortNum > 65535)
        {
            ST_INFO("Failed to create RTSP server: %s\n", pRTSPServer->getResultMsg());
            delete pRTSPServer;
            pRTSPServer = NULL;
            return -2;
        }

        iRet = pRTSPServer->SetRTSPServerPort(rtspServerPortNum);
    }

    urlPrefix = pRTSPServer->rtspURLPrefix();

    for(i = 0; i < 1; i ++)
    {
        //if(pstStreamAttr[i].bUsed != TRUE)
            //continue;

        printf("=================URL===================\n");
        printf("%s%s\n", urlPrefix, szStreamName);
        printf("=================URL===================\n");

        pRTSPServer->createServerMediaSession(mediaSession,
                                              szStreamName,
                                              NULL, NULL);

            subSession = WW_JPEGVideoFileServerMediaSubsession::createNew(
                             *(pRTSPServer->GetUsageEnvironmentObj()),
                             szStreamName,
                             ST_OpenStream,
                             ST_VideoReadStream,
                             ST_CloseStream, 30);

        pRTSPServer->addSubsession(mediaSession, subSession);
        pRTSPServer->addServerMediaSession(mediaSession);
    }

    pRTSPServer->Start();

    g_pRTSPServer = pRTSPServer;

    return 0;
}

MI_S32 ST_RtspServerStop(void)
{
	g_pRTSPServer->Join();
	delete g_pRTSPServer;
	g_pRTSPServer = NULL;

    return 0;
}

int main(int argc, char **argv)
{
	void *status;
	MI_RGN_CanvasInfo_t *pstCanvasInfo = NULL;
	ST_Point_T stPoint;
	stPoint.u32X = 8;
	stPoint.u32Y = 8;
#if 0
    ST_Rect_T stRect;
    stRect.u32X = 0;
    stRect.u32Y = 0;
    stRect.u16PicW = 800;
    stRect.u16PicH = 480;
#endif

    pthread_t     g_detectThread;

    if(!Hidg_Dev_Init((char *)Key_DevName, (char *)Key_DevName))
    {
        printf("Hidg_Dev_Init err\n");
        return -1;
    }

    STCHECKRESULT(ST_BaseModuleInit());
    ST_Vpe_Divp_Bind();
    STCHECKRESULT(ST_PanelStart());
    ST_VencStart(1280, 720, 0);
    ST_RGN_Init();
    ST_RtspServerStart();
    Initial_Decoder();

    printf("======> StreamInit success\n");
    pthread_create(&g_detectThread, NULL, ST_Barcode_thread, NULL);
    pthread_setname_np(g_detectThread, "Detect_Task");
#if 0
    ST_OSD_GetCanvasInfo(0, &pstCanvasInfo);
    ST_OSD_Clear(0, NULL);
    ST_OSD_DrawText(0, stPoint, "animal", DLA_ANIMAL_COLOR, DMF_Font_Size_16x16);
    //ST_OSD_FillRect(0, stRect, DLA_PERSON_COLOR);
    ST_OSD_DrawText(0, stPoint, "animal", DLA_ANIMAL_COLOR, DMF_Font_Size_16x16);
    ST_OSD_Update(0);
#else
    ST_OSD_GetCanvasInfo(0, &pstCanvasInfo);
    ST_OSD_Clear(0, NULL);
    ST_OSD_DrawText(0, stPoint, "Welcome to use Sigmastar IC!", DLA_PERSON_COLOR, DMF_Font_Size_48x48);
    ST_OSD_Update(0);
#endif

    for(;;)
    {
        char cmd = 0xff;
        printf("input 'q' exit\n");
        scanf("%c", &cmd);
        ST_Flush();
        if('q' == cmd || 'Q' == cmd)
        {
        	gBarcode_Run = FALSE;
        	pthread_join(g_detectThread, &status);
            break;
        }
    }

    Hidg_Dev_DeInit();

    ST_RtspServerStop();
    ST_Vpe_Divp_UnBind();
    ST_VencStop(0);
    STCHECKRESULT(ST_PanelStop());
    STCHECKRESULT(ST_BaseModuleUnInit());

    return MI_SUCCESS;
}
