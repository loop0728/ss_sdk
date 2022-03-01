app:
ifeq ($(IMAGE_INSTALL_DIR),)
	@echo "directory of image is not defined"
	@exit 1
endif
	@cp -rfd $(APPLICATION_PATH)/barcodeYuyan/prog_p3_fb $(IMAGE_INSTALL_DIR)/customer
	@cp -rfd $(APPLICATION_PATH)/barcodeYuyan/prog_p3_gpio $(IMAGE_INSTALL_DIR)/customer
	@cp -rfd $(APPLICATION_PATH)/barcodeYuyan/prog_barcodeYuyan $(IMAGE_INSTALL_DIR)/customer
	@cp -rfd $(APPLICATION_PATH)/barcodeYuyan/lib $(IMAGE_INSTALL_DIR)/customer
	@cp -rfd $(APPLICATION_PATH)/barcodeYuyan/font/* $(IMAGE_INSTALL_DIR)/customer
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/prog_p3_fb
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/prog_p3_gpio
	@$(STRIP) --strip-unneeded $(IMAGE_INSTALL_DIR)/customer/prog_barcodeYuyan
	@cat $(APPLICATION_PATH)/barcodeYuyan/demo.sh >> $(IMAGE_INSTALL_DIR)/customer/demo.sh
