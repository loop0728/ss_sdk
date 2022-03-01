#pragma once
#pragma once
#ifndef SVTCLIENT_EXTERN_C
#ifdef __cplusplus
#define SVTCLIENT_EXTERN_C extern "C"
#else
#define SVTCLIENT_EXTERN_C
#endif
#endif

#define SVTCLIENT_API_EXPORTS

#ifndef SVTCLIENT_STDCALL
#if (defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64) && (defined _MSC_VER)
#define SVTCLIENT_STDCALL __stdcall
#else
#define SVTCLIENT_STDCALL
#endif
#endif

#define SVTCLIENT_IMPL SVTCLIENT_EXTERN_C
#define SVTCLIENT_API(rettype) SVTCLIENT_EXTERN_C SVTCLIENT_API_EXPORTS rettype SVTCLIENT_STDCALL



enum ImageFormats
{
	None = 0,
	Lum = 1,
	RGB = 2,
	BGR = 3,
	RGBX = 4,
	XRGB = 5,
	BGRX = 6,
	XBGR = 7,
};
#ifdef __cplusplus
extern "C" {
#endif
	namespace CodeDeCode {
		/**************************
		*liciencepath ��Ȩ�ļ�·��
		*��Ȩ�ļ�����sigmastar��ȡ
		****************************/
		SVTCLIENT_API(int) SDK_Init(const char* liciencepath);
		/*****************
		*���ܣ�ʵ�ֶ�ͼ��Ľ��빦��
		*���룺 dataͼ��buffer
		*���룺 widthͼ���
		*���룺 heightͼ��߶�
		*���룺 imgformatͼ���ʽ�ο�ImageFormats��ע��P3��i6eӲ����ARGB8888��Ӧ����BGRX
		*���룺 codeformat��ά��ָ����ʽ����QR_CODE����ָ����ѡ��Ϊ���и�ʽ   ����֧�ָ�ʽ{AZTEC,CODABAR,CODE_39,CODE_93,CODE_128,DATA_MATRIX,EAN_8,EAN_13,ITF,MAXICODE,PDF_417,QR_CODE,RSS_14,RSS_EXPANDED,UPC_AUPC_E}
		*���룺 faster��������룬���ǽ��뾫�Ȼ������½�
		*���룺 ispure�Ƿ��Ǵ����ģ�һ��Ϊfalse
		*���룺 norotate�Ƿ���ת��һ��ѡ��false
		*******************/
		SVTCLIENT_API(int) ImageDecode(const char* data, int width, int height, int imgformat,const char* codeformat, char* output, bool faster = false, bool ispure = false, bool norotate = false);
	}
#ifdef __cplusplus
}
#endif