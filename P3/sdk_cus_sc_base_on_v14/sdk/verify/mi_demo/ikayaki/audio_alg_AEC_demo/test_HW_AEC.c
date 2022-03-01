#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>
#include <pthread.h>
#include <signal.h>


#include "AudioAecProcess.h"

#include "mi_sys.h"
#include "mi_aio_datatype.h"
#include "mi_common_datatype.h"
#include "mi_ai.h"
#include "mi_ao.h"

typedef enum
{
    E_SOUND_MODE_MONO = 0, /* mono */
    E_SOUND_MODE_STEREO = 1, /* stereo */
} SoundMode_e;


typedef enum
{
    E_SAMPLE_RATE_8000 = 8000, /* 8kHz sampling rate */
    E_SAMPLE_RATE_16000 = 16000, /* 16kHz sampling rate */
    E_SAMPLE_RATE_32000 = 32000, /* 32kHz sampling rate */
    E_SAMPLE_RATE_48000 = 48000, /* 48kHz sampling rate */
} SampleRate_e;

typedef enum
  {
      E_AENC_TYPE_G711A = 0,
      E_AENC_TYPE_G711U,
      E_AENC_TYPE_G726_16,
      E_AENC_TYPE_G726_24,
      E_AENC_TYPE_G726_32,
      E_AENC_TYPE_G726_40,
      PCM,
  } AencType_e;

typedef struct WAVE_FORMAT
{
    signed short wFormatTag;
    signed short wChannels;
    unsigned int dwSamplesPerSec;
    unsigned int dwAvgBytesPerSec;
    signed short wBlockAlign;
    signed short wBitsPerSample;
} WaveFormat_t;

typedef struct WAVEFILEHEADER
{
    char chRIFF[4];
    unsigned int  dwRIFFLen;
    char chWAVE[4];
    char chFMT[4];
    unsigned int  dwFMTLen;
    WaveFormat_t wave;
    char chDATA[4];
    unsigned int  dwDATALen;
} WaveFileHeader_t;


typedef enum
{
	E_AI_SOUND_MODE_MONO = 0,
	E_AI_SOUND_MODE_STEREO,
	E_AI_SOUND_MODE_QUEUE,
} AiSoundMode_e;

typedef struct AiOutFilenName_s
{
    MI_AUDIO_DEV AiDevId;
    MI_AUDIO_Attr_t stAiAttr;
} AiOutFileName_t;

typedef struct AiChnPriv_s
{
    MI_AUDIO_DEV AiDevId;
    MI_AI_CHN AiChn;
    MI_S32 s32Fd;
    MI_U32 u32TotalSize;
    MI_U32 u32ChnCnt;
    pthread_t tid;
} AiChnPriv_t;



#define ExecFunc(func, _ret_) \
do{	\
	MI_S32 s32TmpRet;	\
    printf("%d Start test: %s\n", __LINE__, #func);\
    s32TmpRet = func;	\
    if (s32TmpRet != _ret_)\
    {\
        printf("AUDIO_TEST [%d] %s exec function failed, result:0x%x\n",__LINE__, #func, s32TmpRet);\
        return 1;\
    }\
    else\
    {\
        printf("AUDIO_TEST [%d] %s  exec function pass\n", __LINE__, #func);\
    }\
    printf("%d End test: %s\n", __LINE__, #func);	\
}while(0);


#define AI_DEV_AMIC     (0)
#define AI_DEV_DMIC     (1)
#define AI_DEV_I2S_RX   (2)
#define AI_DEV_LINE_IN  (3)
#if (defined(CONFIG_SIGMASTAR_CHIP_P3))
#define AI_DEV_AMIC_2     (4)
#endif



/*0:Fixed input file  1:User input file*/
#define IN_PARAMETER 0

#define MI_AUDIO_SAMPLE_PER_FRAME (1024)
#define USER_BUF_DEPTH      (4)
#define TOTAL_BUF_DEPTH		(8)


static MI_S32   AoReadFd = -1;
static MI_AUDIO_DEV AoDevId = 0;
static MI_AO_CHN AoChn = 0;
static MI_S32 s32NeedSize = 0;
static pthread_t Aotid;
static pthread_t Aitid;


static MI_AUDIO_DEV AiDevId = 0;
static MI_S8*   ps8AiOutputPath = NULL;
static SoundMode_e eAiWavSoundMode = E_SOUND_MODE_MONO;
static AencType_e eAiWavAencType = PCM;
static MI_U32   u32AiChnCnt = 0;
static MI_S32   s32AiVolume = 8;

static MI_AUDIO_SampleRate_e eAoInSampleRate = E_MI_AUDIO_SAMPLE_RATE_INVALID;
static MI_S32	 s32AoVolume = -5;
static MI_BOOL  bAiExit = FALSE;
static MI_BOOL  bAoExit = FALSE;

static MI_S32   AiChnFd[MI_AUDIO_MAX_CHN_NUM] = {[0 ... MI_AUDIO_MAX_CHN_NUM-1] = -1};

static MI_AUDIO_SampleRate_e eAiSampleRate = E_MI_AUDIO_SAMPLE_RATE_INVALID;
static MI_AUDIO_SampleRate_e eAiWavSampleRate = E_MI_AUDIO_SAMPLE_RATE_INVALID;
static AiSoundMode_e eAiSoundMode = E_AI_SOUND_MODE_MONO;
static WaveFileHeader_t stWavHeaderInput;

float AVERAGE_RUN(int a)
{
    static unsigned int num = 0;
    static float avg = 0;
    if(0 == num)
        avg = 0;
    num++;
    avg = avg + ((float)a - avg) / ((float)num);
    return avg;
}

unsigned int _OsCounterGetMs(void)
{
    struct  timeval t1;
    gettimeofday(&t1, NULL);
    unsigned int T = ((1000000 * t1.tv_sec)+ t1.tv_usec) / 1000;
    return T;
}

void signalHandler(int signo)
{
    switch (signo){
        case SIGALRM:
        case SIGINT:
            printf("Catch signal!!!\n");
            bAiExit = TRUE;
            bAoExit = TRUE;
            break;
   }
   return;
}

void setTimer(MI_U32 u32RunTime)
{
    struct itimerval new_value, old_value;
    if (0 != u32RunTime)
    {
        new_value.it_value.tv_sec = u32RunTime;
        new_value.it_value.tv_usec = 0;
        new_value.it_interval.tv_sec = 0;
        new_value.it_interval.tv_usec = 0;
        setitimer(ITIMER_REAL, &new_value, &old_value);
    }
    return;
}

void initParam(MI_U32 u32RunTime)
{
	eAoInSampleRate = E_MI_AUDIO_SAMPLE_RATE_INVALID; //播放的音频文件采样率，根据实际播放的音频文件动态决定
	s32AoVolume = -5;
	bAiExit = FALSE;
	bAoExit = FALSE;

	eAiSoundMode = E_AI_SOUND_MODE_MONO;
	eAiWavSoundMode = E_SOUND_MODE_MONO;

	u32AiChnCnt = 2; //两个channel，一个用于Mic，一个用于硬件消回音
	s32AiVolume = 8; //Mi Audio In增益
	eAiSoundMode = E_AI_SOUND_MODE_MONO;
	eAiSampleRate = E_MI_AUDIO_SAMPLE_RATE_8000; //Mic采样率，可设为8K或16K
    eAiWavSampleRate = eAiSampleRate; //Wav文件的audio采样率，需要等于Mi Audio采样率
    eAiWavAencType = PCM;

	ps8AiOutputPath = malloc(64);
	if(ps8AiOutputPath != NULL)
	{
		memset(ps8AiOutputPath, 0, 64);
		sprintf((char *)ps8AiOutputPath, "./");  //定义AEC后的音频路径
	}

    signal(SIGALRM, signalHandler);
    signal(SIGINT, signalHandler);

    setTimer(u32RunTime);
    return;
}

void deInitParam()
{
	if(ps8AiOutputPath != NULL)
	{
		free(ps8AiOutputPath);
		ps8AiOutputPath = NULL;
	}
}

int addWaveHeader(WaveFileHeader_t* tWavHead, AencType_e eAencType, SoundMode_e eSoundMode, SampleRate_e eSampleRate, int raw_len)
{
    tWavHead->chRIFF[0] = 'R';
    tWavHead->chRIFF[1] = 'I';
    tWavHead->chRIFF[2] = 'F';
    tWavHead->chRIFF[3] = 'F';

    tWavHead->chWAVE[0] = 'W';
    tWavHead->chWAVE[1] = 'A';
    tWavHead->chWAVE[2] = 'V';
    tWavHead->chWAVE[3] = 'E';

    tWavHead->chFMT[0] = 'f';
    tWavHead->chFMT[1] = 'm';
    tWavHead->chFMT[2] = 't';
    tWavHead->chFMT[3] = 0x20;
    tWavHead->dwFMTLen = 0x10;

    if (eAencType == PCM)
    {
        if(eSoundMode == E_SOUND_MODE_MONO)
            tWavHead->wave.wChannels = 0x01;
        else
            tWavHead->wave.wChannels = 0x02;

        tWavHead->wave.wFormatTag = 0x1;
        tWavHead->wave.wBitsPerSample = 16; //16bit
        tWavHead->wave.dwSamplesPerSec = eSampleRate;
        tWavHead->wave.dwAvgBytesPerSec = (tWavHead->wave.wBitsPerSample  * tWavHead->wave.dwSamplesPerSec * tWavHead->wave.wChannels) / 8;
        tWavHead->wave.wBlockAlign = 1024;
    }

    tWavHead->chDATA[0] = 'd';
    tWavHead->chDATA[1] = 'a';
    tWavHead->chDATA[2] = 't';
    tWavHead->chDATA[3] = 'a';
    tWavHead->dwDATALen = raw_len;
    tWavHead->dwRIFFLen = raw_len + sizeof(WaveFileHeader_t) - 8;

    return 0;
}

MI_S32 createOutputFileName(AiOutFileName_t *pstAiOutFileName, MI_U32 u32ChnIdx, MI_S8* ps8OutputPath, MI_S8* ps8OutputFileName)
{
    char as8Tmp[512] = {0};

    memset(as8Tmp, 0, sizeof(as8Tmp));
    if ('/' == ps8OutputPath[strlen((char *)ps8OutputPath) - 1])
    {
        sprintf(as8Tmp, "%s", ps8OutputPath);
    }
    else
    {
        sprintf(as8Tmp, "%s/", ps8OutputPath);
    }
    strcat((char *)ps8OutputFileName, as8Tmp);

    //set Chn num
    memset(as8Tmp, 0, sizeof(as8Tmp));
    sprintf(as8Tmp, "Chn%d_", u32ChnIdx);
    strcat((char *)ps8OutputFileName, as8Tmp);

    memset(as8Tmp, 0, sizeof(as8Tmp));
    if (AI_DEV_AMIC == pstAiOutFileName->AiDevId)
    {
        sprintf(as8Tmp, "Amic_");
    }
    else if (AI_DEV_DMIC == pstAiOutFileName->AiDevId)
    {
        sprintf(as8Tmp, "Dmic_");
    }
    else if (AI_DEV_I2S_RX == pstAiOutFileName->AiDevId)
    {
        sprintf(as8Tmp, "I2SRx_" );
    }
    else if (AI_DEV_LINE_IN == pstAiOutFileName->AiDevId)
    {
        sprintf(as8Tmp, "LineIn_" );
    }
#if (defined(CONFIG_SIGMASTAR_CHIP_I6E) \
	|| defined(CONFIG_SIGMASTAR_CHIP_I6B0))
    else if (AI_DEV_I2S_RX_AND_SRC == pstAiOutFileName->AiDevId)
    {
        sprintf(as8Tmp, "I2SRx+Src_" );
    }
#elif (defined(CONFIG_SIGMASTAR_CHIP_I2M))
    else if (AI_DEV_AMIC_AND_I2S_RX == pstAiOutFileName->AiDevId)
    {
        sprintf(as8Tmp, "Amic+I2SRx_" );
    }
    else if (AI_DEV_DMIC_AND_I2S_RX == pstAiOutFileName->AiDevId)
    {
        sprintf(as8Tmp, "Dmic+I2SRx_" );
    }
#elif (defined(CONFIG_SIGMASTAR_CHIP_M6))
    else if (AI_DEV_AMIC_2_3 == pstAiOutFileName->AiDevId)
    {
        sprintf(as8Tmp, "Amic2_3_" );
    }
#elif (defined(CONFIG_SIGMASTAR_CHIP_P3))
    else if (AI_DEV_AMIC_2 == pstAiOutFileName->AiDevId)
    {
        sprintf(as8Tmp, "Amic2_" );
    }
#endif

    strcat((char *)ps8OutputFileName, as8Tmp);

    //set OutpuFile SampleRate
    memset(as8Tmp, 0, sizeof(as8Tmp));
    sprintf(as8Tmp, "%dK", pstAiOutFileName->stAiAttr.eSamplerate / 1000);
    strcat((char *)ps8OutputFileName, as8Tmp);

    //set OutpuFile BitWidth
    memset(as8Tmp, 0, sizeof(as8Tmp));
    sprintf(as8Tmp, "_%dbit", 16);
    strcat((char *)ps8OutputFileName, as8Tmp);

    //set OutpuFile Channel Mode
    memset(as8Tmp, 0, sizeof(as8Tmp));
    if (E_MI_AUDIO_SOUND_MODE_MONO == pstAiOutFileName->stAiAttr.eSoundmode)
    {
        sprintf(as8Tmp, "_MONO");
    }
    else if (E_MI_AUDIO_SOUND_MODE_STEREO == pstAiOutFileName->stAiAttr.eSoundmode)
    {
        sprintf(as8Tmp, "_STEREO");
    }
    else if (E_MI_AUDIO_SOUND_MODE_QUEUE == pstAiOutFileName->stAiAttr.eSoundmode)
    {
        sprintf(as8Tmp, "_QUEUE");
    }

    strcat((char *)ps8OutputFileName, as8Tmp);
    memset(as8Tmp, 0, sizeof(as8Tmp));
    sprintf(as8Tmp, ".wav");
    strcat((char *)ps8OutputFileName, as8Tmp);
    return 0;
}


void* aoSendFrame(void* data)
{
    MI_S32 s32Ret = MI_SUCCESS;
    MI_AUDIO_Frame_t stAoSendFrame;
	MI_U8 u8TempBuf[MI_AUDIO_SAMPLE_PER_FRAME * 4];

    while (FALSE == bAoExit)
    {
        s32Ret = read(AoReadFd, &u8TempBuf, s32NeedSize);
        if (s32Ret != s32NeedSize)
        {
            lseek(AoReadFd, sizeof(WaveFileHeader_t), SEEK_SET);
            s32Ret = read(AoReadFd, &u8TempBuf, s32NeedSize);
            if (s32Ret < 0)
            {
                printf("Input file does not has enough data!!!\n");
                break;
            }
        }
        memset(&stAoSendFrame, 0x0, sizeof(MI_AUDIO_Frame_t));
        stAoSendFrame.u32Len[0] = s32Ret;
        stAoSendFrame.apVirAddr[0] = u8TempBuf;
        stAoSendFrame.apVirAddr[1] = NULL;

        do{
            s32Ret = MI_AO_SendFrame(AoDevId, AoChn, &stAoSendFrame, -1);
        }while(s32Ret == MI_AO_ERR_NOBUF);

        if (s32Ret != MI_SUCCESS)
        {
            printf("[Warning]: MI_AO_SendFrame fail, error is 0x%x: \n", s32Ret);
        }
    }
	
    close(AoReadFd);
	
    return NULL;
}

MI_S32 initAo(void)
{
    MI_S32 s32Ret = MI_SUCCESS;
    MI_AUDIO_Attr_t stAoSetAttr, stAoGetAttr;
    MI_S32 s32AoGetVolume;
    MI_U32 u32PhyChnNum;
#if 0
    MI_AO_ChnParam_t stAoChnParam;
#endif

    AoReadFd = open((const char *)"./farend.wav", O_RDONLY, 0666);
    if (AoReadFd <= 0)
    {
        printf("Open audio out file farend.wav failed\n");
        printf("error:%s", strerror(errno));
        return -1;
    }

    s32Ret = read(AoReadFd, &stWavHeaderInput, sizeof(WaveFileHeader_t));
    if (s32Ret < 0)
    {
        printf("Read wav header failed!!!\n");
        return -1;
    }

    memset(&stAoSetAttr, 0x0, sizeof(MI_AUDIO_Attr_t));
    stAoSetAttr.eBitwidth = E_MI_AUDIO_BIT_WIDTH_16;
    stAoSetAttr.eWorkmode = E_MI_AUDIO_MODE_I2S_SLAVE;
    stAoSetAttr.WorkModeSetting.stI2sConfig.bSyncClock = FALSE;
    stAoSetAttr.WorkModeSetting.stI2sConfig.eFmt = E_MI_AUDIO_I2S_FMT_I2S_MSB;
    stAoSetAttr.WorkModeSetting.stI2sConfig.eMclk = E_MI_AUDIO_I2S_MCLK_0;
    stAoSetAttr.WorkModeSetting.stI2sConfig.u32TdmSlots = 4;
	stAoSetAttr.WorkModeSetting.stI2sConfig.eI2sBitWidth = E_MI_AUDIO_BIT_WIDTH_16;
    stAoSetAttr.u32PtNumPerFrm = MI_AUDIO_SAMPLE_PER_FRAME;

    if (stWavHeaderInput.wave.wChannels == 2)
    {
        stAoSetAttr.eSoundmode = E_MI_AUDIO_SOUND_MODE_STEREO;
    }
    else if(stWavHeaderInput.wave.wChannels == 1)
    {
        stAoSetAttr.eSoundmode = E_MI_AUDIO_SOUND_MODE_MONO;
    }

    stAoSetAttr.u32ChnCnt = 1;

    stAoSetAttr.eSamplerate = (MI_AUDIO_SampleRate_e)stWavHeaderInput.wave.dwSamplesPerSec;
    eAoInSampleRate = (MI_AUDIO_SampleRate_e)stWavHeaderInput.wave.dwSamplesPerSec;

    ExecFunc(MI_AO_SetPubAttr(AoDevId, &stAoSetAttr), MI_SUCCESS);
    ExecFunc(MI_AO_GetPubAttr(AoDevId, &stAoGetAttr), MI_SUCCESS);

    ExecFunc(MI_AO_Enable(AoDevId), MI_SUCCESS);
    ExecFunc(MI_AO_EnableChn(AoDevId, AoChn), MI_SUCCESS);

    ExecFunc(MI_AO_SetVolume(AoDevId, 0, s32AoVolume, E_MI_AO_GAIN_FADING_OFF), MI_SUCCESS);
    ExecFunc(MI_AO_GetVolume(AoDevId, 0, &s32AoGetVolume), MI_SUCCESS);

    switch (eAiSoundMode)
    {
        case E_MI_AUDIO_SOUND_MODE_MONO:
            u32PhyChnNum = 1;
            break;

        case E_MI_AUDIO_SOUND_MODE_STEREO:
            u32PhyChnNum = 2;
            break;

        default:
            break;
    }
    s32NeedSize = MI_AUDIO_SAMPLE_PER_FRAME * 2 * u32PhyChnNum * stAoSetAttr.u32ChnCnt;
    s32NeedSize = s32NeedSize / (stAoSetAttr.u32ChnCnt * 2 * u32PhyChnNum) * (stAoSetAttr.u32ChnCnt * 2 * u32PhyChnNum);
    pthread_create(&Aotid, NULL, aoSendFrame, NULL);
    printf("create ao thread.\n");
	return 0;

	return s32Ret;
}


MI_S32 AecInit(AEC_HANDLE * pHandle, char * workingBuffer)
{
    MI_S32 ret;
	unsigned int workingBufferSize;

    AudioAecInit aec_init;
    AudioAecConfig aec_config;
    
    /*********************User change section start*******************/
    unsigned int supMode_band[6] = {20,40,60,80,100,120};
    unsigned int supMode[7] = {4,4,4,4,4,4,4};
    aec_init.point_number = 128; //AEC算法每次处理的采样点个数
    aec_init.nearend_channel = 1;
    aec_init.farend_channel = 1;
    aec_init.sample_rate = IAA_AEC_SAMPLE_RATE_16000;
    aec_config.delay_sample = 0;
    aec_config.comfort_noise_enable = IAA_AEC_FALSE;
    /*********************User change section end*******************/
    memcpy(&(aec_config.suppression_mode_freq[0]), supMode_band, sizeof(supMode_band));
    memcpy(&(aec_config.suppression_mode_intensity[0]), supMode, sizeof(supMode));

    //(1)IaaAec_GetBufferSize
    workingBufferSize = IaaAec_GetBufferSize();
    workingBuffer = (char*)malloc(workingBufferSize);
    if(NULL == workingBuffer)
    {
        printf("workingBuffer malloc failed !\n");
        return -1;
    }
    printf("workingBuffer malloc success !\n");
    //(2)IaaAec_Init
    *pHandle = IaaAec_Init(workingBuffer, &aec_init);
    if (NULL == *pHandle)
    {
        printf("AEC init failed !\r\n");
        return -1;
    }
    printf("AEC init success !\r\n");
    //(3)IaaAec_Config
    ret = IaaAec_Config(*pHandle, &aec_config);
    if(ret)
    {
        printf("IaaAec_Config failed !\n");
        return -1;
    }
    printf("IaaAec_Config succeed !\n");

	return ret;
}
void* aiGetIaccAecBuf(void* data)
{
    AiChnPriv_t* priv = (AiChnPriv_t*)data;

    int ret;
	float avg;
	int counter = 0;
    unsigned int T0, T1;
	char *workingBuffer = NULL;
    char in_output[2048] = {0};
    char input_far[2048] = {0};

    MI_S32 s32Ret;
	MI_S64 before_us, after_us;
    struct timeval tv_before, tv_after;
		
	AEC_HANDLE handle;
	WaveFileHeader_t stWavHead;
    MI_AUDIO_Frame_t stAiChFrame[2];
    MI_AUDIO_AecFrame_t stAecFrame[2];

	s32Ret = AecInit(&handle, workingBuffer);
	if(s32Ret != 0)
	{
        printf("AEC init failed !\r\n");
        return NULL;
	}

	memset(&stAiChFrame, 0, sizeof(MI_AUDIO_Frame_t));
    memset(&stAecFrame, 0, sizeof(MI_AUDIO_AecFrame_t));
    while(FALSE == bAiExit)
    {
        s32Ret = MI_AI_GetFrame(priv[0].AiDevId, priv[0].AiChn, &stAiChFrame[0], &stAecFrame[0], -1);
        if (MI_SUCCESS == s32Ret)
        {
            {
                gettimeofday(&tv_before, NULL);
                write(priv[0].s32Fd, stAiChFrame[0].apVirAddr[0], stAiChFrame[0].u32Len[0]); //功放数据写入文件
				memcpy(input_far, stAiChFrame[0].apVirAddr[0], stAiChFrame[0].u32Len[0]); //拷贝一份用于回音消除
                gettimeofday(&tv_after, NULL);
                before_us = tv_before.tv_sec * 1000000 + tv_before.tv_usec;
                after_us = tv_after.tv_sec * 1000000 + tv_after.tv_usec;
                if (after_us - before_us > 10 * 1000)
                {
                    printf("Chn:%d, cost time:%lldus = %lldms.\n", priv[0].AiChn, after_us - before_us, (after_us - before_us) / 1000);
                }
                priv[0].u32TotalSize += stAiChFrame[0].u32Len[0];
            }
            MI_AI_ReleaseFrame(priv[0].AiDevId, priv[0].AiChn,  &stAiChFrame[0],  NULL);
        }
        else
        {
            printf("Dev%dChn%d get frame failed!!!error:0x%x\n", priv[0].AiDevId, priv[0].AiChn, s32Ret);
        }
		
		s32Ret = MI_AI_GetFrame(priv[1].AiDevId, priv[1].AiChn, &stAiChFrame[1], &stAecFrame[1], -1);
		if (MI_SUCCESS == s32Ret)
		{
			{
				gettimeofday(&tv_before, NULL);
				memcpy(in_output, stAiChFrame[1].apVirAddr[0], stAiChFrame[1].u32Len[0]); //拷贝一份Mic录到到数据，用于回音消除
				gettimeofday(&tv_after, NULL);
				before_us = tv_before.tv_sec * 1000000 + tv_before.tv_usec;
				after_us = tv_after.tv_sec * 1000000 + tv_after.tv_usec;
				if (after_us - before_us > 10 * 1000)
				{
					printf("Chn:%d, cost time:%lldus = %lldms.\n", priv[1].AiChn, after_us - before_us, (after_us - before_us) / 1000);
				}
				priv[1].u32TotalSize += stAiChFrame[1].u32Len[0];
			}
			MI_AI_ReleaseFrame(priv[1].AiDevId, priv[1].AiChn,	&stAiChFrame[1],  NULL);
		}
		else
		{
			printf("Dev%dChn%d get frame failed!!!error:0x%x\n", priv[1].AiDevId, priv[1].AiChn, s32Ret);
		}


	    counter++;
	    T0  = (long)_OsCounterGetMs();
	    //(4)IaaAec_Run
	    ret = IaaAec_Run(handle, (short *)in_output, (short *)input_far);

	    T1  = (long)_OsCounterGetMs();
	    avg = AVERAGE_RUN(T1 - T0);
	    if(0 == counter % 100)
	    {
	        printf("counter = %d\n", counter);
	        //printf("current time = %f\n", (float)counter * aec_init.point_number / aec_init.sample_rate);
	        printf("process time = %lu(ms)\t", (long)(T1 - T0));
	        printf("AVG is %.2f ms\n", avg);
	    }
		
	    if(ret < 0)
	    {
	        printf("IaaAec_Run failed !\n");
	        break;
	    }
        write(priv[1].s32Fd, in_output, stAiChFrame[1].u32Len[0]); //将回音消除后到数据写入到文件，用于确认是否有消除干净

    }
    memset(&stWavHead, 0, sizeof(WaveFileHeader_t));
    addWaveHeader(&stWavHead, eAiWavAencType, eAiWavSoundMode, eAiWavSampleRate, priv[0].u32TotalSize);
    lseek(priv[0].s32Fd, 0, SEEK_SET);
    write(priv[0].s32Fd, &stWavHead, sizeof(WaveFileHeader_t));

    memset(&stWavHead, 0, sizeof(WaveFileHeader_t));
    addWaveHeader(&stWavHead, eAiWavAencType, eAiWavSoundMode, eAiWavSampleRate, priv[1].u32TotalSize);
    lseek(priv[1].s32Fd, 0, SEEK_SET);
    write(priv[1].s32Fd, &stWavHead, sizeof(WaveFileHeader_t));
    
    close(priv[0].s32Fd);
	close(priv[1].s32Fd);
	IaaAec_Free(handle);
	free(workingBuffer);
    system("sync");
	

    return NULL;
}


MI_S32 initAi(void)
{
    MI_S32              s32Ret;
    MI_U32              u32ChnIdx;

    WaveFileHeader_t    stAiWavHead;
    MI_AUDIO_Attr_t     stAiSetAttr;
    MI_AUDIO_Attr_t     stAiGetAttr;
    AiOutFileName_t     stAiFileName;
    MI_S8               s8OutputFileName[512];
    MI_SYS_ChnPort_t    stAiChnOutputPort0[MI_AUDIO_MAX_CHN_NUM];	
	AiChnPriv_t 		stAiChnPriv[MI_AUDIO_MAX_CHN_NUM];

    memset(&stAiSetAttr, 0x0, sizeof(MI_AUDIO_Attr_t));
    memset(&stAiGetAttr, 0x0, sizeof(MI_AUDIO_Attr_t));
    stAiSetAttr.eBitwidth = E_MI_AUDIO_BIT_WIDTH_16;
    stAiSetAttr.eSamplerate = eAiSampleRate; //Audio采样率设置，此处目前是设置16K采样
    stAiSetAttr.eSoundmode = eAiSoundMode; //目前设为单声道模式
    stAiSetAttr.eWorkmode = E_MI_AUDIO_MODE_I2S_MASTER;
    stAiSetAttr.u32ChnCnt = u32AiChnCnt; //两个channel，一个用于Mic，一个用于硬件消回音
    stAiSetAttr.u32PtNumPerFrm = 128; //(stAiSetAttr.eSamplerate / 125 = 128); //MI接口每次获取的音频采样点个数。这个参数需要与AEC算法一致，目前AEC算法支持每次128个采样点的处理
    stAiSetAttr.WorkModeSetting.stI2sConfig.bSyncClock = FALSE;
    stAiSetAttr.WorkModeSetting.stI2sConfig.eFmt = E_MI_AUDIO_I2S_FMT_I2S_MSB;
    stAiSetAttr.WorkModeSetting.stI2sConfig.eMclk = E_MI_AUDIO_I2S_MCLK_0;
    stAiSetAttr.WorkModeSetting.stI2sConfig.u32TdmSlots = 4;
	stAiSetAttr.WorkModeSetting.stI2sConfig.eI2sBitWidth = E_MI_AUDIO_BIT_WIDTH_16;

	eAiWavSoundMode = E_SOUND_MODE_MONO;

    memset(&stAiFileName, 0x0, sizeof(AiOutFileName_t));
    stAiFileName.AiDevId = AiDevId;
    memcpy(&stAiFileName.stAiAttr, &stAiSetAttr, sizeof(MI_AUDIO_Attr_t));

    memset(&stAiWavHead, 0x0, sizeof(WaveFileHeader_t));
    for (u32ChnIdx = 0; u32ChnIdx < 2; u32ChnIdx++)
    {
        memset(s8OutputFileName, 0x0, sizeof(s8OutputFileName));
        createOutputFileName(&stAiFileName, u32ChnIdx, ps8AiOutputPath, s8OutputFileName);
        printf("OutputName:%s\n", s8OutputFileName);
        AiChnFd[u32ChnIdx] = open((const char *)s8OutputFileName, O_RDWR | O_CREAT, 0777);
        if (AiChnFd[u32ChnIdx] < 0)
        {
            printf("Open output file path:%s fail \n", s8OutputFileName);
            printf("error:%s", strerror(errno));
            return -1;
        }

        s32Ret = write(AiChnFd[u32ChnIdx], &stAiWavHead, sizeof(WaveFileHeader_t));
        if (s32Ret < 0)
        {
            printf("write wav head failed\n");
            return -1;
        }
    }

    ExecFunc(MI_AI_SetPubAttr(AiDevId, &stAiSetAttr), MI_SUCCESS);
    ExecFunc(MI_AI_GetPubAttr(AiDevId, &stAiGetAttr), MI_SUCCESS);
    ExecFunc(MI_AI_Enable(AiDevId), MI_SUCCESS);

	printf("fun:%s - Line:%d \n", __FUNCTION__, __LINE__);
    for (u32ChnIdx = 0; u32ChnIdx < u32AiChnCnt; u32ChnIdx++)
    {
        ExecFunc(MI_AI_SetVqeVolume(AiDevId, u32ChnIdx, s32AiVolume), MI_SUCCESS);
    }
	
    memset(&stAiChnPriv, 0x0, sizeof(stAiChnPriv));
    memset(&stAiChnOutputPort0, 0x0, sizeof(stAiChnOutputPort0));

    //Channel 0 用于硬件消回音
    stAiChnPriv[0].AiChn = 0;
    stAiChnPriv[0].AiDevId = AiDevId;
    stAiChnPriv[0].s32Fd = AiChnFd[0];
    stAiChnPriv[0].u32ChnCnt = 1;
    stAiChnPriv[0].u32TotalSize = 0;

    stAiChnOutputPort0[0].eModId = E_MI_MODULE_ID_AI;
    stAiChnOutputPort0[0].u32DevId = AiDevId;
    stAiChnOutputPort0[0].u32ChnId = 0;
    stAiChnOutputPort0[0].u32PortId = 0;
    ExecFunc(MI_SYS_SetChnOutputPortDepth(&stAiChnOutputPort0[0], USER_BUF_DEPTH, TOTAL_BUF_DEPTH), MI_SUCCESS);
    ExecFunc(MI_AI_EnableChn(AiDevId, 0), MI_SUCCESS);

    //Channel 1 用于Mic拾音
    stAiChnPriv[1].AiChn = 1;
    stAiChnPriv[1].AiDevId = AiDevId;
    stAiChnPriv[1].s32Fd = AiChnFd[1];
    stAiChnPriv[1].u32ChnCnt = 1;
    stAiChnPriv[1].u32TotalSize = 0;
    stAiChnOutputPort0[1].eModId = E_MI_MODULE_ID_AI;
    stAiChnOutputPort0[1].u32DevId = AiDevId;
    stAiChnOutputPort0[1].u32ChnId = 1;
    stAiChnOutputPort0[1].u32PortId = 0;
    ExecFunc(MI_SYS_SetChnOutputPortDepth(&stAiChnOutputPort0[1], USER_BUF_DEPTH, TOTAL_BUF_DEPTH), MI_SUCCESS);
    ExecFunc(MI_AI_EnableChn(AiDevId, 1), MI_SUCCESS);

    pthread_create(&Aitid, NULL, aiGetIaccAecBuf, stAiChnPriv);

    printf("create ai thread.\n");
    return 0;

	return s32Ret;
}


MI_S32 deinitAi(void)
{
    MI_U32 u32ChnIdx;

    for (u32ChnIdx = 0; u32ChnIdx < u32AiChnCnt; u32ChnIdx++)
    {
        ExecFunc(MI_AI_DisableChn(AiDevId, u32ChnIdx), MI_SUCCESS);
    }
    ExecFunc(MI_AI_Disable(AiDevId), MI_SUCCESS);
    return 0;
}

MI_S32 deinitAo(void)
{
    ExecFunc(MI_AO_DisableChn(AoDevId, AoChn), MI_SUCCESS);
    ExecFunc(MI_AO_Disable(AoDevId), MI_SUCCESS);

    return 0;
}


int main(int argc, char *argv[])
{
	initParam(10); //Time, Unit:S
	
	MI_SYS_Init();
	
	//init audio out
	initAo();
	initAi();

	// join ai
	pthread_join(Aitid, NULL);
	printf("join Ai thread done.\n");

	// join ao
	pthread_join(Aotid, NULL);
	printf("join Ao thread done.\n");
		
	// disable ai / ao
	deinitAi();
	deinitAo();

	MI_SYS_Exit();

    return 0;
}
