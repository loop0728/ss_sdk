app:
ifeq ($(IMAGE_INSTALL_DIR),)
	@echo "directory of image is not defined"
	@exit 1
endif
	@cp -rfd $(APPLICATION_PATH)/barcode/prog_p3_fb $(IMAGE_INSTALL_DIR)/customer
	@cp -rfd $(APPLICATION_PATH)/barcode/prog_p3_gpio $(IMAGE_INSTALL_DIR)/customer
	@cp -rfd $(APPLICATION_PATH)/barcode/prog_barcode $(IMAGE_INSTALL_DIR)/customer
	@cp -rfd $(APPLICATION_PATH)/barcode/lib $(IMAGE_INSTALL_DIR)/customer
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/prog_p3_fb
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/prog_p3_gpio
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/prog_barcode
	@cat $(APPLICATION_PATH)/barcode/demo.sh >> $(IMAGE_INSTALL_DIR)/customer/demo.sh
