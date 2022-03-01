INC  += $(DB_BUILD_TOP)/../common/live555/UsageEnvironment/include
INC  += $(DB_BUILD_TOP)/../common/live555/groupsock/include
INC  += $(DB_BUILD_TOP)/../common/live555/liveMedia/include
INC  += $(DB_BUILD_TOP)/../common/live555/BasicUsageEnvironment/include
INC  += $(DB_BUILD_TOP)/../common/live555/mediaServer/include
INC  += $(DB_BUILD_TOP)/../common/iniparser
INC  += ./internal/cus3a

INC  += ./internal/qrcode/include
INC  += ./internal/rgn/include

ST_DEP := common venc vpe vif rgn live555 cus3a
LIBS += -L./internal/qrcode/lib
LIBS += -lpthread -lm
LIBS += -lmi_vif -lmi_vpe -lmi_divp -lmi_disp -lmi_panel -lmi_isp -lmi_iqserver -lmi_rgn -lcus3a
LIBS += -ldecoder

LIBS += -lmi_vif -lmi_vpe -lmi_venc -lmi_isp -lmi_iqserver -lcus3a -lispalgo -lmi_divp
ifneq ($(findstring $(CHIP),p3 i6e),)
LIBS +=-lfbc_decode
endif
ifneq ($(CHIP), p3)
INC += ./internal/ldc
LIBS +=-leptz
endif
#LIBS += -lZXing -lpthread
