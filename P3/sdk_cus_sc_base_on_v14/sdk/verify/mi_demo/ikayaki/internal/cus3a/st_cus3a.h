#ifndef _ST_CUS3A_H_
#define _ST_CUS3A_H_

#ifdef __cplusplus
extern "C" {
#endif
/*
int ae_init(void* pdata, ISP_AE_INIT_PARAM *init_state);
void ae_release(void* pdata);
void ae_run(void* pdata, const ISP_AE_INFO *info, ISP_AE_RESULT *result);
int awb_init(void *pdata);
void awb_run(void* pdata, const ISP_AWB_INFO *info, ISP_AWB_RESULT *result);
void awb_release(void *pdata);
int af_init(void *pdata, ISP_AF_INIT_PARAM *param);
void af_release(void *pdata);
void af_run(void *pdata, const ISP_AF_INFO *af_info, ISP_AF_RESULT *result);
int af_ctrl(void *pdata, ISP_AF_CTRL_CMD cmd, void* param);
*/
void ST_EnableCustomize3A(void);
void ST_ReleaseCUS3A(void);

#ifdef __cplusplus
}
#endif

#endif
