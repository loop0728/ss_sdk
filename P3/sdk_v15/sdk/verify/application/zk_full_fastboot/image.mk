app:
ifeq ($(IMAGE_INSTALL_DIR),)
	@echo "directory of image is not defined"
	@exit 1
endif

	@rm -rf $(IMAGE_INSTALL_DIR)/rootfs/customer_app/lib
	@mkdir -p $(IMAGE_INSTALL_DIR)/rootfs/customer_app/lib

	@cp -rf $(APPLICATION_PATH)/zk_full_fastboot/RunFiles/bin/zkgui $(IMAGE_INSTALL_DIR)/rootfs/customer_app/zkgui
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/rootfs/customer_app/zkgui
	@cp -rfd $(APPLICATION_PATH)/zk_full_fastboot/RunFiles/lib/RunFirst/lib $(IMAGE_INSTALL_DIR)/rootfs/customer_app/
	@cp -rfd $(APPLICATION_PATH)/zk_full_fastboot/RunFiles/lib/RunFirst/libsecurity $(IMAGE_INSTALL_DIR)/rootfs/customer_app/
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/rootfs/customer_app/lib/*
	@cp -rfd $(APPLICATION_PATH)/zk_full_fastboot/RunFiles/lib/RunLater/lib $(IMAGE_INSTALL_DIR)/customer/lib
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/lib/*
	@cp -rf $(APPLICATION_PATH)/zk_full_fastboot/RunFiles/res/RunFirst/* $(IMAGE_INSTALL_DIR)/rootfs/customer_app/
	@cp -rf $(APPLICATION_PATH)/zk_full_fastboot/RunFiles/res/RunLater $(IMAGE_INSTALL_DIR)/customer/res
	@cp -rf $(APPLICATION_PATH)/zk_full_fastboot/RunFiles/etc/* $(IMAGE_INSTALL_DIR)/rootfs/etc/
	@chmod 755 $(IMAGE_INSTALL_DIR)/rootfs/etc/usb/usb_hotplug.sh
	@cat $(APPLICATION_PATH)/zk_full_fastboot/RunFiles/demo.sh >> $(IMAGE_INSTALL_DIR)/rootfs/etc/init.sh
	@cp  $(APPLICATION_PATH)/zk_full_fastboot/RunFiles/run_later.sh $(IMAGE_INSTALL_DIR)/customer/
	@chmod 777 $(IMAGE_INSTALL_DIR)/customer/run_later.sh
	@echo "nameserver 202.96.128.86" >> $(IMAGE_INSTALL_DIR)/rootfs/etc/resolv.conf
	@echo "nameserver 8.8.8.8" >> $(IMAGE_INSTALL_DIR)/rootfs/etc/resolv.conf


