app:
ifeq ($(IMAGE_INSTALL_DIR),)
	@echo "directory of image is not defined"
	@exit 1
endif


	@cp -rfd $(APPLICATION_PATH)/zk_mini_nosensor/lib $(IMAGE_INSTALL_DIR)/customer
	@cp -rf $(APPLICATION_PATH)/zk_mini_nosensor/libsecurity $(IMAGE_INSTALL_DIR)/customer
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/lib/*
	@cp -rf $(APPLICATION_PATH)/zk_mini_nosensor/res $(IMAGE_INSTALL_DIR)/customer
	@cp -rf $(APPLICATION_PATH)/zk_mini_nosensor/etc/* $(IMAGE_INSTALL_DIR)/rootfs/etc/
	@chmod 755 $(IMAGE_INSTALL_DIR)/rootfs/etc/usb/usb_hotplug.sh
	@cat $(APPLICATION_PATH)/zk_mini_nosensor/demo.sh >> $(IMAGE_INSTALL_DIR)/customer/demo.sh
	@cp -rf $(APPLICATION_PATH)/zk_mini_nosensor/bin/zkgui $(IMAGE_INSTALL_DIR)/customer/zkgui
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/zkgui
	@echo "nameserver 202.96.128.86" >> $(IMAGE_INSTALL_DIR)/rootfs/etc/resolv.conf
	@echo "nameserver 8.8.8.8" >> $(IMAGE_INSTALL_DIR)/rootfs/etc/resolv.conf

