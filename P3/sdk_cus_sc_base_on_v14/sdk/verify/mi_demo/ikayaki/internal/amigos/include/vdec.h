#ifndef __VDEC_H__
#define __VDEC_H__

#include "mi_common_datatype.h"
#include "sys.h"


typedef struct stVdecInfo_s
{
    int picWidth;
    int picHeight;
    int decodeType;
    int dpBufMode;
    int refFrameNum;
    unsigned int bitstreamSize;
}stVdecInfo_t;

typedef struct stDecOutInfo_s
{
    int intPortId;
    int intDecOutWidth;
    int intDecOutHeight;
}stDecOutInfo_t;

class Vdec: public Sys
{
public:
    Vdec();
    virtual ~Vdec();

private:
    virtual void Init();
    virtual void Deinit();
    stVdecInfo_t stVdecInfo;
    std::map<std::string, int> mapInputChnId;
};
#endif

