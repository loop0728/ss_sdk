include $(PROJ_ROOT)/configs/current.configs

IMAGE_INSTALL_DIR:=$(OUTPUTDIR)

.PHONY: rootfs

LIB_DIR_PATH:=$(PROJ_ROOT)/release/$(PRODUCT)/$(CHIP)/common/$(TOOLCHAIN)/$(TOOLCHAIN_VERSION)
RAMDISK_DIR?=$(OUTPUTDIR)/tmprd
RAMDISK_IMG?=$(ramdisk$(RESOUCE))

KBUILD_ROOT:=$(PROJ_ROOT)/kbuild/$(KERNEL_VERSION)
ifeq ($(LINUX_FLASH_TYPE), emmc)
KBUILD_CUST:=$(KBUILD_ROOT)/customize/emmc
else
KBUILD_CUST:=$(KBUILD_ROOT)/customize
endif
KERN_MODS_PATH:=$(KBUILD_ROOT)/modules
LIB_DIR_PATH:=$(PROJ_ROOT)/release/$(PRODUCT)/$(CHIP)/common/$(TOOLCHAIN)/$(TOOLCHAIN_VERSION)

LFS_MOUNT_BLK := $(foreach m, $(filter %_lfs, $(foreach block, $(USR_MOUNT_BLOCKS), $(block)_$($(block)$(FSTYPE)))), $(patsubst %_lfs, %, $(m)))
FWFS_MOUNT_BLK := $(foreach m, $(filter %_fwfs, $(foreach block, $(USR_MOUNT_BLOCKS), $(block)_$($(block)$(FSTYPE)))), $(patsubst %_fwfs, %, $(m)))
MOUNT_BLK := $(filter-out $(LFS_MOUNT_BLK), $(USR_MOUNT_BLOCKS))
MOUNT_BLK := $(filter-out $(FWFS_MOUNT_BLK), $(MOUNT_BLK))

ifeq ($(TOOLCHAIN), uclibc)
LIBC=$(strip $(patsubst %.tar.gz, %, $(word 1, $(notdir $(wildcard $(LIB_DIR_PATH)/package/libuclibc-*.tar.gz)))))
else
LIBC=$(strip $(patsubst %.tar.gz, %, $(word 1, $(notdir $(wildcard $(LIB_DIR_PATH)/package/libc-*.tar.gz)))))
endif

rootfs:
	cd rootfs; tar xf rootfs.tar.gz -C $(OUTPUTDIR)
	tar xf busybox/$(BUSYBOX).tar.gz -C $(OUTPUTDIR)/rootfs
	tar xf $(LIB_DIR_PATH)/package/$(LIBC).tar.gz -C $(OUTPUTDIR)/rootfs/lib
	mkdir -p $(miservice$(RESOUCE))/lib
	cat $(LIB_DIR_PATH)/mi_libs/dynamic/.libs_depend | sed 's#\(.*\)#$(LIB_DIR_PATH)/mi_libs/dynamic/lib\1.so#' | xargs -i cp -rvf {} $(miservice$(RESOUCE))/lib/
	cp $(LIB_DIR_PATH)/ex_libs/dynamic/* $(miservice$(RESOUCE))/lib/

	mkdir -p $(miservice$(RESOUCE))
	mkdir -p $(OUTPUTDIR)/customer
	cp -rf $(PROJ_ROOT)/board/ini/* $(OUTPUTDIR)/customer
	cp -rf $(PROJ_ROOT)/board/$(CHIP)/$(BOARD_NAME)/config/* $(miservice$(RESOUCE))
	cp -vf $(PROJ_ROOT)/board/$(CHIP)/mmap/$(MMAP) $(miservice$(RESOUCE))/mmap.ini
	cp -rvf $(LIB_DIR_PATH)/bin/config_tool/* $(miservice$(RESOUCE))
	
	#pq file
	#cp -rf $(PROJ_ROOT)/board/$(CHIP)/pqfile/PQ.bin $(OUTPUTDIR)/customer
	cp -rf $(PROJ_ROOT)/board/$(CHIP)/pqfile/PQ.bin $(OUTPUTDIR)/misc
	cp -rf $(PROJ_ROOT)/board/$(CHIP)/pqfile/PQConfig.ini $(miservice$(RESOUCE))
	
	
	cd $(miservice$(RESOUCE)); chmod +x config_tool; ln -sf config_tool dump_config; ln -sf config_tool load_config; ln -sf config_tool dump_mmap
	mkdir -p $(miservice$(RESOUCE))/iqfile/
	cp -rf $(PROJ_ROOT)/board/$(CHIP)/iqfile/isp_api.xml $(miservice$(RESOUCE))/iqfile/ -vf
	if [ "$(IQ0)" != "" ]; then \
		cp -rf $(PROJ_ROOT)/board/$(CHIP)/iqfile/$(IQ0) $(miservice$(RESOUCE))/iqfile/ -vf; \
		cd $(miservice$(RESOUCE))/iqfile; chmod +x $(shell echo $(IQ0) | awk -F'/' '{print $$NF}'); ln -sf $(shell echo $(IQ0) | awk -F'/' '{print $$NF}') iqfile0.bin; cd -; \
	fi;
	if [ "$(IQ1)" != "" ]; then \
		cp -rf $(PROJ_ROOT)/board/$(CHIP)/iqfile/$(IQ1) $(miservice$(RESOUCE))/iqfile/ -vf; \
		cd $(miservice$(RESOUCE))/iqfile; chmod +x $(shell echo $(IQ1) | awk -F'/' '{print $$NF}'); ln -sf $(shell echo $(IQ1) | awk -F'/' '{print $$NF}') iqfile1.bin; cd -; \
	fi;
	if [ "$(IQ2)" != "" ]; then \
		cp -rf $(PROJ_ROOT)/board/$(CHIP)/iqfile/$(IQ2) $(miservice$(RESOUCE))/iqfile/ -vf; \
		cd $(miservice$(RESOUCE))/iqfile; chmod +x $(shell echo $(IQ2) | awk -F'/' '{print $$NF}'); ln -sf $(shell echo $(IQ2) | awk -F'/' '{print $$NF}') iqfile2.bin; cd -; \
	fi;
	if [ "$(IQ3)" != "" ]; then \
		cp -rf $(PROJ_ROOT)/board/$(CHIP)/iqfile/$(IQ3) $(miservice$(RESOUCE))/iqfile/ -vf; \
		cd $(miservice$(RESOUCE))/iqfile; chmod +x $(shell echo $(IQ3) | awk -F'/' '{print $$NF}'); ln -sf $(shell echo $(IQ3) | awk -F'/' '{print $$NF}') iqfile3.bin; cd -; \
	fi;
	if [ "$(IQ_API0)" != "" ]; then \
		cp -rf $(PROJ_ROOT)/board/$(CHIP)/iqfile/$(IQ_API0) $(miservice$(RESOUCE))/iqfile/ -vf; \
		cd $(miservice$(RESOUCE))/iqfile; chmod +x $(shell echo $(IQ_API0) | awk -F'/' '{print $$NF}'); ln -sf $(shell echo $(IQ_API0) | awk -F'/' '{print $$NF}') iqapifile0.bin; cd -; \
	fi;
	if [ "$(IQ_API1)" != "" ]; then \
		cp -rf $(PROJ_ROOT)/board/$(CHIP)/iqfile/$(IQ_API1) $(miservice$(RESOUCE))/iqfile/ -vf; \
		cd $(miservice$(RESOUCE))/iqfile; chmod +x $(shell echo $(IQ_API1) | awk -F'/' '{print $$NF}'); ln -sf $(shell echo $(IQ_API1) | awk -F'/' '{print $$NF}') iqapifile1.bin; cd -; \
	fi;
	if [ -d $(PROJ_ROOT)/board/$(CHIP)/venc_fw ]; then \
		cp -rf $(PROJ_ROOT)/board/$(CHIP)/venc_fw $(miservice$(RESOUCE)); \
	fi;
	if [ -d $(PROJ_ROOT)/board/$(CHIP)/dla_file ]; then \
		mkdir $(miservice$(RESOUCE))/dla; \
		cp $(PROJ_ROOT)/board/$(CHIP)/dla_file/ipu_firmware.bin $(miservice$(RESOUCE))/dla; \
	fi;

	mkdir -p $(OUTPUTDIR)/rootfs/config
	cp -rf etc/* $(OUTPUTDIR)/rootfs/etc
	if [ "$(appconfigs$(RESOUCE))" != "" ]; then \
		mkdir -p  $(appconfigs$(RESOUCE)); \
		mkdir -p $(OUTPUTDIR)/rootfs/appconfigs;\
	fi;

	if [ "$(PHY_TEST)" = "yes" ]; then \
		mkdir $(miservice$(RESOUCE))/sata_phy ; \
		cp $(LIB_DIR_PATH)/bin/sata_phy/* $(miservice$(RESOUCE))/sata_phy ; \
	fi;

	if [ "$(verify_mixer)" = "enable" ] && [ "$(IS_DEMO_BOARD)" = "0" ]; then \
	if [ $(FLASH_TYPE) = "nor" ]; then \
		if [ "$(FLASH_SIZE)" != "8M" ]; then \
			cp -rf $(LIB_DIR_PATH)/bin/mixer/* $(OUTPUTDIR)/customer/ ; \
			echo export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:/customer >> ${OUTPUTDIR}/rootfs/etc/profile; \
			ln -sf ./mixer/font $(OUTPUTDIR)/customer/font ; \
			if [ -f "$(LIB_DIR_PATH)/bin/mi_demo/prog_rtsp" ]; then \
				cp -rf $(LIB_DIR_PATH)/bin/mi_demo/prog_rtsp $(OUTPUTDIR)/customer/; \
			fi;	\
		fi; \
	else \
		if [ -d "$(LIB_DIR_PATH)/bin/mixer" ]; then \
			cp -rf $(LIB_DIR_PATH)/bin/mixer/* $(OUTPUTDIR)/customer/ ; \
			ln -sf ./mixer/font $(OUTPUTDIR)/customer/font ; \
		fi;	\
		echo export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:/customer >> ${OUTPUTDIR}/rootfs/etc/profile; \
		if [ -d "$(LIB_DIR_PATH)/bin/mi_demo" ]; then \
			cp -rf $(LIB_DIR_PATH)/bin/mi_demo/ $(OUTPUTDIR)/customer/ ; \
		fi;	\
	fi;   \
        fi;

	if [ "$(DUAL_OS)" = "on" ]; then \
	       cp $(PROJ_ROOT)/board/$(CHIP)/rtos/PreloadSetting.txt $(OUTPUTDIR)/customer/ ; \
	       mkdir -p $(OUTPUTDIR)/misc ; \
	       cp $(PROJ_ROOT)/board/$(CHIP)/rtos/PreloadSetting.txt $(OUTPUTDIR)/misc ; \
	       cp -rf $(PROJ_ROOT)/board/$(CHIP)/iqfile/$(SENSOR_TYPE)/* $(OUTPUTDIR)/misc ; \
	       cp -f $(OUTPUTDIR)/misc/$(SENSOR_TYPE)_api.bin $(OUTPUTDIR)/misc/$(ISP_API_COLORNIGHT) ; \
	       cp -f $(OUTPUTDIR)/misc/$(SENSOR_TYPE)_api.bin $(OUTPUTDIR)/misc/$(ISP_API_DAY) ; \
	       cp -f $(OUTPUTDIR)/misc/$(SENSOR_TYPE)_api.bin $(OUTPUTDIR)/misc/$(ISP_API_NIGHT) ; \
	       rm -f $(OUTPUTDIR)/misc/$(SENSOR_TYPE)_api.bin ; \
	       mv $(OUTPUTDIR)/misc/$(SENSOR_TYPE)_iqfile.bin $(OUTPUTDIR)/misc/$(ISP_IQ) ; \
	       if [ "$(ISP_AWB)" != "" ]; then \
	       mv $(OUTPUTDIR)/misc/$(SENSOR_TYPE)_alsc_cali.data $(OUTPUTDIR)/misc/$(ISP_AWB) ; \
              fi;\
	       if [ "$(ISP_ALSC)" != "" ]; then \
	       mv $(OUTPUTDIR)/misc/$(SENSOR_TYPE)_awb_cali.data $(OUTPUTDIR)/misc/$(ISP_ALSC) ; \
              fi;\
	       if [ "$(DLA_FIRMWARE)" != "" ]; then \
	       cp -rf $(PROJ_ROOT)/board/$(CHIP)/dla_file/* $(OUTPUTDIR)/misc/ ; \
              fi;\
	       cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/PreloadSetting.txt $(OUTPUTDIR)/misc/ ; \
	       cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/ascii_8x16 $(OUTPUTDIR)/misc/ ; \
	       cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/hanzi_16x16 $(OUTPUTDIR)/misc/ ; \
	       cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/200X131.argb1555 $(OUTPUTDIR)/misc/ ; \
		   cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/200X133.bmp $(OUTPUTDIR)/misc/ ; \
	       if [ "$(CHIP)" = "i6e" ]; then \
	       cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/ldc_chn0_view0_table.bin $(OUTPUTDIR)/misc/ ; \
		   cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/new_AMTK_1R_cm_fhd_rtos_bin.cfg $(OUTPUTDIR)/misc/ ; \
		   cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/atan2_Q15.bin $(OUTPUTDIR)/misc/ ; \
		   cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/Cali_LDCpoly.bin $(OUTPUTDIR)/misc/ ; \
		   cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/sin_Q15.bin $(OUTPUTDIR)/misc/ ; \
		   cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/trdu0to180.bin $(OUTPUTDIR)/misc/ ; \
		   cp -rf $(PROJ_ROOT)/board/$(CHIP)/rtos/trdu180to220.bin $(OUTPUTDIR)/misc/ ; \
              fi;\
	fi;

	mkdir -p $(OUTPUTDIR)/rootfs/lib/modules/
	mkdir -p $(miservice$(RESOUCE))/modules/$(KERNEL_VERSION)

	touch ${OUTPUTDIR}/rootfs/etc/mdev.conf
	echo mice 0:0 0660 =input/ >> ${OUTPUTDIR}/rootfs/etc/mdev.conf
	echo mouse.* 0:0 0660 =input/ >> ${OUTPUTDIR}/rootfs/etc/mdev.conf
	echo event.* 0:0 0660 =input/ >> ${OUTPUTDIR}/rootfs/etc/mdev.conf
	echo pcm.* 0:0 0660 =snd/ >> ${OUTPUTDIR}/rootfs/etc/mdev.conf
	echo control.* 0:0 0660 =snd/ >> ${OUTPUTDIR}/rootfs/etc/mdev.conf
	echo timer 0:0 0660 =snd/ >> ${OUTPUTDIR}/rootfs/etc/mdev.conf
	echo '$$DEVNAME=bus/usb/([0-9]+)/([0-9]+) 0:0 0660 =bus/usb/%1/%2' >> ${OUTPUTDIR}/rootfs/etc/mdev.conf

	echo export PATH=\$$PATH:/config >> ${OUTPUTDIR}/rootfs/etc/profile
	echo export TERMINFO=/config/terminfo >> ${OUTPUTDIR}/rootfs/etc/profile
	echo export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:/config/lib >> ${OUTPUTDIR}/rootfs/etc/profile
	sed -i '/^mount.*/d' $(OUTPUTDIR)/rootfs/etc/profile
	echo mkdir -p /dev/pts >> ${OUTPUTDIR}/rootfs/etc/init.d/rcS
	echo mount -t sysfs none /sys >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
	echo mount -t tmpfs mdev /dev >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
	echo mount -t debugfs none /sys/kernel/debug/ >>  $(OUTPUTDIR)/rootfs/etc/init.d/rcS

	cp -rvf $(PROJ_ROOT)/tools/$(TOOLCHAIN)/$(TOOLCHAIN_VERSION)/fw_printenv/* $(OUTPUTDIR)/rootfs/etc/
	echo "$(ENV_CFG)" > $(OUTPUTDIR)/rootfs/etc/fw_env.config
	if [ "$(ENV_TYPE)" == "dualenv" ]; then \
		echo "$(ENV1_CFG)" >> $(OUTPUTDIR)/rootfs/etc/fw_env.config; \
	fi;
	cd $(OUTPUTDIR)/rootfs/etc/;ln -sf fw_printenv fw_setenv
	echo mkdir -p /var/lock >> ${OUTPUTDIR}/rootfs/etc/init.d/rcS

	if [ "$(FLASH_TYPE)"x = "nor"x  ]; then \
		echo mdev -s >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS ;\
	fi;
	if [ "$(LINUX_FLASH_TYPE)"x = "emmc"x  ]; then \
		   echo mdev -s >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS ;\
		   cp -f $(PROJ_ROOT)/tools/mkfs.ext4 $(OUTPUTDIR)/rootfs/sbin/ ;\
		   cp -f $(PROJ_ROOT)/tools/resize2fs $(OUTPUTDIR)/rootfs/sbin/ ;\
	fi;
	echo -e $(foreach block, $(MOUNT_BLK), "mount -t $($(block)$(FSTYPE)) $($(block)$(MOUNTPT)) $($(block)$(MOUNTTG))\n") >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
	if [ "$(LFS_MOUNT_BLK)" != "" ]; then \
		echo -e mdev -s >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS;	\
		if [ "$(TOOLCHAIN)" = "glibc" ] && [ "$(TOOLCHAIN_VERSION)" = "9.1.0" ]; then \
			tar -vxf $(PROJ_ROOT)/image/fuse/fuse-2.9.9-arm-linux-gnueabihf-glibc-9.1.0.tar.gz -C $(OUTPUTDIR)/rootfs/;	\
			tar -vxf $(PROJ_ROOT)/image/littlefs-fuse/littlefs-fuse-2.2.0-arm-linux-gnueabihf-glibc-9.1.0.tar.gz -C $(OUTPUTDIR)/rootfs/;	\
		fi;	\
		if [ "$(TOOLCHAIN)" = "glibc" ] && [ "$(TOOLCHAIN_VERSION)" = "8.2.1" ]; then \
			tar -vxf $(PROJ_ROOT)/image/fuse/fuse-2.9.9-arm-linux-gnueabihf-glibc-8.2.1.tar.gz -C $(OUTPUTDIR)/rootfs/;	\
			tar -vxf $(PROJ_ROOT)/image/littlefs-fuse/littlefs-fuse-2.2.0-arm-linux-gnueabihf-glibc-8.2.1.tar.gz -C $(OUTPUTDIR)/rootfs/;	\
		fi;	\
		mkdir -p $(OUTPUTDIR)/rootfs/misc;\
		$(foreach block, $(LFS_MOUNT_BLK), $(PROJ_ROOT)/image/makefiletools/script/lfs_mount.py --part_size=$($(block)$(PATSIZE)) --rcs_dir=$(OUTPUTDIR)/rootfs/etc/init.d/rcS $($(block)$(MOUNTPT)) $($(block)$(MOUNTTG));)\
	fi;

	if [ "$(FWFS_MOUNT_BLK)" != "" ]; then \
		echo -e mdev -s >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS;	\
		if [ "$(TOOLCHAIN)" = "glibc" ] && [ "$(TOOLCHAIN_VERSION)" = "9.1.0" ]; then \
			tar -vxf $(PROJ_ROOT)/image/fuse/fuse-2.9.9-arm-linux-gnueabihf-glibc-9.1.0.tar.gz -C $(OUTPUTDIR)/rootfs/;	\
			tar -vxf $(PROJ_ROOT)/image/firmwarefs-fuse/firmwarefs-fuse-2.2.0-arm-linux-gnueabihf-glibc-9.1.0.tar.gz -C $(OUTPUTDIR)/rootfs/;	\
		fi;	\
		if [ "$(TOOLCHAIN)" = "glibc" ] && [ "$(TOOLCHAIN_VERSION)" = "8.2.1" ]; then \
			tar -vxf $(PROJ_ROOT)/image/fuse/fuse-2.9.9-arm-linux-gnueabihf-glibc-8.2.1.tar.gz -C $(OUTPUTDIR)/rootfs/;	\
			tar -vxf $(PROJ_ROOT)/image/firmwarefs-fuse/firmwarefs-fuse-2.2.0-arm-linux-gnueabihf-glibc-8.2.1.tar.gz -C $(OUTPUTDIR)/rootfs/;	\
		fi;	\
		mkdir -p $(OUTPUTDIR)/rootfs/misc;\
		$(foreach block, $(FWFS_MOUNT_BLK), $(PROJ_ROOT)/image/makefiletools/script/fwfs_mount.py --flash_type=$(FLASH_TYPE) --part_size=$($(block)$(PATSIZE)) --rcs_dir=$(OUTPUTDIR)/rootfs/etc/init.d/rcS $($(block)$(MOUNTPT)) $($(block)$(MOUNTTG));)\
	fi;

	if [ "$(FLASH_TYPE)"x != "nor"x ]; then \
		-chmod 755 $(LIB_DIR_PATH)/bin/debug/*	;\
		cp -rf $(LIB_DIR_PATH)/bin/debug/* $(OUTPUTDIR)/customer/	;\
	else	\
		if [ -f "$(LIB_DIR_PATH)/bin/debug/i2c_read_write" ]; then \
			-chmod 755 $(LIB_DIR_PATH)/bin/debug/i2c_read_write  ;\
			cp -rf $(LIB_DIR_PATH)/bin/debug/i2c_read_write $(OUTPUTDIR)/customer/   ;\
		fi;	\
		if [ -f "$(LIB_DIR_PATH)/bin/debug/riu_r" ]; then \
			-chmod 755 $(LIB_DIR_PATH)/bin/debug/riu_r  ;\
			cp -rf $(LIB_DIR_PATH)/bin/debug/riu_r $(OUTPUTDIR)/customer/   ;\
		fi;	\
		if [ -f "$(LIB_DIR_PATH)/bin/debug/riu_w" ]; then \
			-chmod 755 $(LIB_DIR_PATH)/bin/debug/riu_w  ;\
			cp -rf $(LIB_DIR_PATH)/bin/debug/riu_w $(OUTPUTDIR)/customer/   ;\
		fi;	\
	fi;
	#add:  remove sshd in nor flash default
	if [[ "$(FLASH_TYPE)"x = "nor"x ]] && [[ -d "$(OUTPUTDIR)/customer/ssh" ]]; then \
		rm -rf $(OUTPUTDIR)/customer/ssh; \
	fi;
	#add emmc resizefs
	if [ "$(LINUX_FLASH_TYPE)"x = "emmc"x  ]; then \
		   echo "if [ ! -e /etc/init.d/resize.ext4.log ]; then" >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS; \
		   echo -e $(foreach part, $(EXT4_RESIZE_PAT_LIST), "    resize2fs $(part)\n") >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS; \
		   echo "    echo 'resize mmc blk' > /etc/init.d/resize.ext4.log" >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS; \
		   echo "fi;" >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS; \
	fi;
	#end add

	if [ -f "$(OUTPUTDIR)/customer/demo.sh" ]; then \
		rm  $(OUTPUTDIR)/customer/demo.sh; \
	fi;
	touch $(OUTPUTDIR)/customer/demo.sh
	chmod 755 $(OUTPUTDIR)/customer/demo.sh

	# change linux printk level to 4 
	echo 'echo 4 > /proc/sys/kernel/printk' >> $(OUTPUTDIR)/customer/demo.sh
	echo >> $(OUTPUTDIR)/customer/demo.sh

	# creat insmod ko scrpit
	if [ -f "$(KBUILD_CUST)/kernel_mod_list" ]; then \
		cat $(KBUILD_CUST)/kernel_mod_list | sed 's#\(.*\).ko#insmod /config/modules/$(KERNEL_VERSION)/\1.ko#' >> $(OUTPUTDIR)/customer/demo.sh; \
		cat $(KBUILD_CUST)/kernel_mod_list | sed 's#\(.*\).ko\(.*\)#$(KERN_MODS_PATH)/\1.ko#' | xargs -i cp -rvf {} $(miservice$(RESOUCE))/modules/$(KERNEL_VERSION); \
		echo "#kernel_mod_list" >> $(OUTPUTDIR)/customer/demo.sh; \
	fi;

	if [ "$(DUAL_OS)" != "on" ]; then \
		if [ -f "$(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/misc_mod_list" ]; then \
			cat $(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/misc_mod_list | sed 's#\(.*\).ko#insmod /config/modules/$(KERNEL_VERSION)/\1.ko#' >> $(OUTPUTDIR)/customer/demo.sh; \
			cat $(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/misc_mod_list | sed 's#\(.*\).ko\(.*\)#$(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/\1.ko#' | xargs -i cp -rvf {} $(miservice$(RESOUCE))/modules/$(KERNEL_VERSION); \
			echo "#misc_mod_list" >> $(OUTPUTDIR)/customer/demo.sh; \
		fi; \
		if [ -f "$(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/.mods_depend" ]; then \
			cat $(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/.mods_depend | sed '2,20s#\(.*\)#insmod /config/modules/$(KERNEL_VERSION)/\1.ko#' >> $(OUTPUTDIR)/customer/demo.sh; \
			cat $(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/.mods_depend | sed 's#\(.*\)#$(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/\1.ko#' | xargs -i cp -rvf {} $(miservice$(RESOUCE))/modules/$(KERNEL_VERSION); \
			echo "#mi module" >> $(OUTPUTDIR)/customer/demo.sh; \
		fi; \
		if [ -f "$(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/misc_mod_list_late" ]; then \
			cat $(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/misc_mod_list_late | sed 's#\(.*\).ko#insmod /config/modules/$(KERNEL_VERSION)/\1.ko#' >> $(OUTPUTDIR)/customer/demo.sh; \
			cat $(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/misc_mod_list_late | sed 's#\(.*\).ko\(.*\)#$(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/\1.ko#' | xargs -i cp -rvf {} $(miservice$(RESOUCE))/modules/$(KERNEL_VERSION); \
			echo "#misc_mod_list_late" >> $(OUTPUTDIR)/customer/demo.sh; \
		fi; \
	fi;

	if [ -f "$(KBUILD_CUST)/kernel_mod_list_late" ]; then \
		cat $(KBUILD_CUST)/kernel_mod_list_late | sed 's#\(.*\).ko#insmod /config/modules/$(KERNEL_VERSION)/\1.ko#' >> $(OUTPUTDIR)/customer/demo.sh; \
		cat $(KBUILD_CUST)/kernel_mod_list_late | sed 's#\(.*\).ko\(.*\)#$(KERN_MODS_PATH)/\1.ko#' | xargs -i cp -rvf {} $(miservice$(RESOUCE))/modules/$(KERNEL_VERSION); \
		echo "#kernel_mod_list_late" >> $(OUTPUTDIR)/customer/demo.sh; \
	fi;

	if [ "$(DUAL_OS)" != "on" ]; then \
		if [ "$(SENSOR_LIST)" != "" ]; then \
			cp -rvf $(foreach n,$(SENSOR_LIST),$(LIB_DIR_PATH)/modules/$(KERNEL_VERSION)/$(n)) $(miservice$(RESOUCE))/modules/$(KERNEL_VERSION); \
		fi; \
		if [ "$(SENSOR0)" != "" ]; then \
			echo insmod /config/modules/$(KERNEL_VERSION)/$(SENSOR0) $(SENSOR0_OPT) >> $(OUTPUTDIR)/customer/demo.sh; \
		fi; \
		if [ "$(SENSOR1)" != "" ]; then \
			echo insmod /config/modules/$(KERNEL_VERSION)/$(SENSOR1) $(SENSOR1_OPT) >> $(OUTPUTDIR)/customer/demo.sh; \
		fi; \
		if [ "$(SENSOR2)" != "" ]; then \
			echo insmod /config/modules/$(KERNEL_VERSION)/$(SENSOR2) $(SENSOR2_OPT) >> $(OUTPUTDIR)/customer/demo.sh; \
		fi;	\
		sed -i 's/mi_sys.ko/mi_sys.ko cmdQBufSize=768 logBufSize=256 /g' $(OUTPUTDIR)/customer/demo.sh; \
		sed -i '/mi_iqserver.ko/,+4d' $(OUTPUTDIR)/customer/demo.sh;\
		sed -i '/mi_isp.ko/,+4d' $(OUTPUTDIR)/customer/demo.sh;\
		sed -i 's/mi_common/insmod \/config\/modules\/$(KERNEL_VERSION)\/mi_common.ko/g' $(OUTPUTDIR)/customer/demo.sh; \
		sed -i '/#mi module/a	major=`cat /proc/devices | busybox awk "\\\\$$2==\\""mi_poll"\\" {print \\\\$$1}"`\nbusybox mknod \/dev\/mi_poll c $$major 0' $(OUTPUTDIR)/customer/demo.sh; \
	fi;

	if [ $(PHY_TEST) = "yes" ]; then \
		echo -e "\033[41;33;5m !!! Replace "mdrv-sata-host.ko" with "sata_bench_test.ko" !!!\033[0m" ; \
		sed '/mdrv-sata-host/d' $(OUTPUTDIR)/customer/demo.sh > $(OUTPUTDIR)/customer/demotemp.sh ; \
		echo insmod /config/sata_phy/sata_bench_test.ko >> $(OUTPUTDIR)/customer/demotemp.sh ; \
		cp $(OUTPUTDIR)/customer/demotemp.sh $(OUTPUTDIR)/customer/demo.sh ; \
		rm $(OUTPUTDIR)/customer/demotemp.sh ; \
	fi;

	echo current setting $(SIGMA_WIFI)
	if [ $(SIGMA_WIFI) != "no_wifi" ]; then	\
		mkdir -p  $(miservice$(RESOUCE))/wifi ; \
		if [ $(FLASH_TYPE) = "spinand" ]; then \
			cp -rf $(LIB_DIR_PATH)/wifi/libs/libdns  $(OUTPUTDIR)/customer -rfd ; \
			cp -rf $(LIB_DIR_PATH)/wifi/libs/ap/*   $(miservice$(RESOUCE))/wifi ; \
			cp -rf $(LIB_DIR_PATH)/wifi/bin/ap/*   $(miservice$(RESOUCE))/wifi ; \
		fi;	\
		find $(LIB_DIR_PATH)/wifi/bin/ -maxdepth 1 -type f -exec cp -P {}  $(miservice$(RESOUCE))/wifi \; ;\
		find $(LIB_DIR_PATH)/wifi/bin/ -maxdepth 1 -type l -exec cp -P {}  $(miservice$(RESOUCE))/wifi \; ;\
		find $(LIB_DIR_PATH)/wifi/libs/ -maxdepth 1 -type f -exec cp -P {}  $(miservice$(RESOUCE))/wifi \; ;\
		find $(LIB_DIR_PATH)/wifi/libs/ -maxdepth 1 -type l -exec cp -P {}  $(miservice$(RESOUCE))/wifi \; ;\
		cp -rf $(LIB_DIR_PATH)/wifi/modules/${SIGMA_WIFI}/*   $(miservice$(RESOUCE))/wifi ; \
		cp -rf $(LIB_DIR_PATH)/wifi/configs/*   $(miservice$(RESOUCE))/wifi ; \
		sed "s/sigma_wifi_ssw10xb/${SIGMA_WIFI}/g" $(miservice$(RESOUCE))/wifi/sigma_wifi_init.sh > $(miservice$(RESOUCE))/wifi/sigma_wifi_init.sh.out ;	\
		mv $(miservice$(RESOUCE))/wifi/sigma_wifi_init.sh.out $(miservice$(RESOUCE))/wifi/sigma_wifi_init.sh;	\
		chmod 777 $(miservice$(RESOUCE))/wifi/sigma_wifi_init.sh; \
		if [ "$(appconfigs$(RESOUCE))" != "" ]; then \
			if [ -f "$(miservice$(RESOUCE))/wifi/wpa_supplicant.conf" ]; then	\
				mv  $(miservice$(RESOUCE))/wifi/wpa_supplicant.conf $(appconfigs$(RESOUCE));	\
				cp $(OUTPUTDIR)/appconfigs/wpa_supplicant.conf $(appconfigs$(RESOUCE))/wpa_supplicant.conf_bak;	\
			fi;	\
		fi;	\
	fi;
	# Enable MIU protect on CMDQ buffer as default (While List: CPU)
	# [I5] The 1st 1MB of MIU is not for CMDQ buffer
#	echo 'echo set_miu_block3_status 0 0x70 0 0x100000 1 > /proc/mi_modules/mi_sys_mma/miu_protect' >> $(OUTPUTDIR)/customer/demo.sh

#	echo mount -t jffs2 /dev/mtdblock3 /config >> $(OUTPUTDIR)/rootfs/etc/profile
	ln -fs /config/modules/$(KERNEL_VERSION) $(OUTPUTDIR)/rootfs/lib/modules/
	find $(miservice$(RESOUCE))/modules/$(KERNEL_VERSION) -name "*.ko" | xargs $(STRIP) --strip-unneeded;
	find $(OUTPUTDIR)/rootfs/lib/ -name "*.so" | xargs $(STRIP)  --strip-unneeded;
	echo mkdir -p /dev/pts >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
	echo mount -t devpts devpts /dev/pts >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
#	echo "busybox telnetd&" >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
	echo "if [ -e /customer/demo.sh ]; then" >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
	echo "    /customer/demo.sh" >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
	echo "fi;" >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
	echo mdev -s >> $(OUTPUTDIR)/customer/demo.sh

	#add sshd, default password 1234
	if [[ "$(FLASH_TYPE)"x = "spinand"x ]]; then \
		if [[ $(TOOLCHAIN_VERSION) = "9.1.0" ]] || [[ $(TOOLCHAIN_VERSION) = "8.2.1" ]]; then \
			echo "root::0:0:Linux User,,,:/home/root:/bin/sh" > $(OUTPUTDIR)/rootfs/etc/passwd; \
			echo "sshd:x:74:74:Privilege-separated SSH:/var/empty/sshd:/sbin/nologin" >> $(OUTPUTDIR)/rootfs/etc/passwd; \
			echo "export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:/customer/ssh/lib" >> ${OUTPUTDIR}/rootfs/etc/init.d/rcS; \
			echo "mkdir /var/empty" >> ${OUTPUTDIR}/rootfs/etc/init.d/rcS; \
			echo "/customer/ssh/sbin/sshd -f /customer/ssh/etc/sshd_config" >> ${OUTPUTDIR}/rootfs/etc/init.d/rcS; \
			echo "export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:/customer/ssh/lib" >> ${OUTPUTDIR}/rootfs/etc/profile; \
		fi; \
	fi;
	echo "telnetd&" >> $(OUTPUTDIR)/rootfs/etc/init.d/rcS
	#end add

	mkdir -p $(OUTPUTDIR)/vendor
	mkdir -p $(OUTPUTDIR)/customer
	mkdir -p $(OUTPUTDIR)/rootfs/vendor
	mkdir -p $(OUTPUTDIR)/rootfs/customer
	mkdir -p $(OUTPUTDIR)/bootconfig
	mkdir -p $(OUTPUTDIR)/rootfs/bootconfig
	if [ "$(ramdisk$(RESOUCE))" != "" ]; then \
		rm -rf $(RAMDISK_DIR); \
		mkdir -p $(RAMDISK_DIR); \
		cd $(RAMDISK_DIR); cpio -i -F $(RAMDISK_IMG); \
		cp -R $(OUTPUTDIR)/tmprd/linuxrc $(OUTPUTDIR)/tmprd/init; \
		rm -rf $(OUTPUTDIR)/tmprd/usr/lib/modules/*; \
		cat $(PROJ_ROOT)/kbuild/$(KERNEL_VERSION)/$(CHIP)/configs/$(PRODUCT)/$(BOARD)/$(TOOLCHAIN)/$(TOOLCHAIN_VERSION)/$(FLASH_TYPE)/modules/ramdisk_rc1 | sed 's#\(.*\).ko\(.*\)#$(PROJ_ROOT)/kbuild/$(KERNEL_VERSION)/$(CHIP)/configs/$(PRODUCT)/$(BOARD)/$(TOOLCHAIN)/$(TOOLCHAIN_VERSION)/$(FLASH_TYPE)/modules/\1.ko#' | xargs -i cp -rvf {} $(OUTPUTDIR)/tmprd/usr/lib/modules; \
		cat $(PROJ_ROOT)/kbuild/$(KERNEL_VERSION)/$(CHIP)/configs/$(PRODUCT)/$(BOARD)/$(TOOLCHAIN)/$(TOOLCHAIN_VERSION)/$(FLASH_TYPE)/modules/ramdisk_rc2 | sed 's#\(.*\).ko\(.*\)#$(PROJ_ROOT)/kbuild/$(KERNEL_VERSION)/$(CHIP)/configs/$(PRODUCT)/$(BOARD)/$(TOOLCHAIN)/$(TOOLCHAIN_VERSION)/$(FLASH_TYPE)/modules/\1.ko#' | xargs -i cp -rvf {} $(OUTPUTDIR)/tmprd/usr/lib/modules; \
		$(PREFIX)strip --strip-unneeded $(OUTPUTDIR)/tmprd/usr/lib/modules/*; \
		cd $(RAMDISK_DIR); find | cpio -o -H newc -O $(RAMDISK_IMG); \
		echo "#!/bin/sh" > $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "echo Console done" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "mount -a" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		cat $(PROJ_ROOT)/kbuild/$(KERNEL_VERSION)/$(CHIP)/configs/$(PRODUCT)/$(BOARD)/$(TOOLCHAIN)/$(TOOLCHAIN_VERSION)/$(FLASH_TYPE)/modules/ramdisk_rc2 | sed 's#\(.*\).ko#insmod /usr/lib/modules/\1.ko#' >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "ubiattach /dev/ubi_ctrl -m $(UBI_AT_MTD)" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "mount -t ubifs ubi0:rootfs /usr" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "mount -t ubifs ubi0:miservice /config" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "mount -t ubifs ubi0:customer /customer" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
	        if [ "$(LFS_MOUNT_BLK)" != "" ]; then \
		    echo "mkdir -p /lfs" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		    echo -e mdev -s >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS;	\
		    echo -e $(foreach block, $(LFS_MOUNT_BLK), "/usr/bin/lfs --block_size=$($(block)$(BLKSIZE)) --block_cycles=500 --read_size=$($(block)$(PGSIZE)) --prog_size=$($(block)$(PGSIZE)) --cache_size=$($(block)$(BLKSIZE)) --block_count=$($(block)$(BLKCOUNT)) --lookahead_size=8 $($(block)$(MOUNTPT)) $($(block)$(MOUNTTG))\n") >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS;	\
	        fi; \
	        if [ "$(FWFS_MOUNT_BLK)" != "" ]; then \
		    echo "mkdir -p /fwfs" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		    echo -e mdev -s >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS;	\
		    $(foreach block, $(FWFS_MOUNT_BLK), $(PROJ_ROOT)/image/makefiletools/script/fwfs_mount.py --flash_type=$(FLASH_TYPE) --part_size=$($(block)$(PATSIZE)) --rcs_dir=$(OUTPUTDIR)/tmprd/etc/init.d/rcS $($(block)$(MOUNTPT)) $($(block)$(MOUNTTG));)\
	        fi; \
		echo "mkdir -p /dev/shm" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "mkdir -p /dev/pts" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "mount -t devpts for_telnetd /dev/pts" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "/usr/usr/sbin/telnetd -l /usr/bin/ash" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "mount --bind /usr/bin/sh /bin/sh" >> $(OUTPUTDIR)/tmprd/etc/init.d/rcS; \
		echo "#!/bin/sh" > $(OUTPUTDIR)/tmprd/etc/profile; \
		echo "export PATH=/usr/bin:/usr/sbin:/bin:/sbin:/usr/usr/bin:/usr/usr/sbin" >> $(OUTPUTDIR)/tmprd/etc/profile; \
		echo "export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:/config/lib" >> ${OUTPUTDIR}/tmprd/etc/profile; \
		echo "/usr/bin/busybox sh /customer/demo.sh" >> $(OUTPUTDIR)/tmprd/etc/profile; \
		echo export TERMINFO=/config/terminfo >> ${OUTPUTDIR}/tmprd/etc/profile; \
		cd $(PROJ_ROOT)/kbuild/$(KERNEL_VERSION); \
		./scripts/gen_initramfs_list.sh -o $(OUTPUTDIR)/initramfs.gz -u 0 -g 0 $(OUTPUTDIR)/tmprd/; \
	fi;
