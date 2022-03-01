app:
ifeq ($(IMAGE_INSTALL_DIR),)
	@echo "directory of image is not defined"
	@exit 1
endif

ifeq ($(IS_DEMO_BOARD), 1)
	@echo "echo 7 >/sys/class/gpio/export" >> $(IMAGE_INSTALL_DIR)/customer/demo.sh
	@echo "echo out >/sys/class/gpio/gpio7/direction" >> $(IMAGE_INSTALL_DIR)/customer/demo.sh
	@echo "echo 1 >/sys/class/gpio/gpio7/value" >> $(IMAGE_INSTALL_DIR)/customer/demo.sh
	@echo "echo 8 >/sys/class/gpio/export" >> $(IMAGE_INSTALL_DIR)/customer/demo.sh
	@echo "echo out >/sys/class/gpio/gpio8/direction" >> $(IMAGE_INSTALL_DIR)/customer/demo.sh
	@echo "echo 1 >/sys/class/gpio/gpio8/value" >> $(IMAGE_INSTALL_DIR)/customer/demo.sh
endif

	@cp -rf $(APPLICATION_PATH)/zk_bootup/RunFiles/bin/zkgui $(IMAGE_INSTALL_DIR)/customer/zkgui
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/zkgui
	@cp -rfd $(APPLICATION_PATH)/zk_bootup/RunFiles/lib $(IMAGE_INSTALL_DIR)/customer
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/lib/*
	@cp -rf $(APPLICATION_PATH)/zk_bootup/RunFiles/res $(IMAGE_INSTALL_DIR)/customer
	@cp -rf $(APPLICATION_PATH)/zk_bootup/RunFiles/etc/* $(IMAGE_INSTALL_DIR)/rootfs/etc/
	@chmod 755 $(IMAGE_INSTALL_DIR)/rootfs/etc/usb/usb_hotplug.sh
	@cat $(APPLICATION_PATH)/zk_bootup/RunFiles/demo.sh >> $(IMAGE_INSTALL_DIR)/customer/demo.sh

