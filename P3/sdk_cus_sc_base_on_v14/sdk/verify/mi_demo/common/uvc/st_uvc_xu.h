#ifndef _ST_UVC_XU_H_
#define _ST_UVC_XU_H_

#include <stdint.h>
#include "st_uvc_xu_datatype.h"

#define EU_ISP_CMD_OK			0x00
#define EU_ISP_CMD_NOT_SUPPORT	0x80

typedef struct _VC_CMD_CFG
{
	unsigned long bCmdCap;
	unsigned char bInfoCap;
	unsigned short bCmdLen;
	unsigned char bInfoLen;
	/*If cmd > 4, the following data is a pointer*/
	unsigned long  dwResVal;
	unsigned long  dwDefVal;
	unsigned long  dwMinVal;
	unsigned long  dwMaxVal;
	unsigned long  dwCurVal;
} VC_CMD_CFG;

void usb_vc_cmd_cfg(uint8_t req, VC_CMD_CFG *cfg, unsigned long cur_val, struct uvc_request_data *resp);

// process PU, CT, XU job.
int8_t usb_vc_eu1_cs_out(uint8_t entity_id, uint8_t cs, uint32_t len, struct uvc_request_data *data);
int8_t usb_vc_eu1_cs(uint8_t cs, uint8_t req, struct uvc_request_data *resp);

int8_t usb_vc_eu2_cs_out(uint8_t entity_id, uint8_t cs, uint32_t len, struct uvc_request_data *data);
int8_t usb_vc_eu2_cs(uint8_t cs, uint8_t req, struct uvc_request_data *resp);

typedef struct _DataExchangeParam
{
	unsigned short id;			//command ID
	unsigned long data_len;		//transfer lens
	unsigned long cur_offset;	//current read/write offset
	char *ptr;					//data buffer
} DataExchangeParam;
#endif // _ST_UVC_XU_H_
