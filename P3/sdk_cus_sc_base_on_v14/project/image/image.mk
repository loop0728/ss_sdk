FSIMAGE_LIST:=$(filter-out $(patsubst %_fs__,%,$(filter %_fs__, $(foreach n,$(IMAGE_LIST),$(n)_fs_$($(n)$(FSTYPE))_))),$(IMAGE_LIST))
TARGET_FSIMAGE:=$(foreach n,$(FSIMAGE_LIST),$(n)_$(FLASH_TYPE)_$($(n)$(FSTYPE))_fsimage)
TARGET_NOFSIMAGE:=$(foreach n,$(filter-out $(FSIMAGE_LIST), $(IMAGE_LIST)),$(n)_nofsimage)

BOOT_FSIMAGE_LIST:=$(filter-out $(patsubst %_fs__,%,$(filter %_fs__, $(foreach n,$(BOOT_IMAGE_LIST),$(n)_fs_$($(n)$(FSTYPE))_))),$(BOOT_IMAGE_LIST))
BOOT_TARGET_FSIMAGE:=$(foreach n,$(BOOT_FSIMAGE_LIST),$(n)_$(FLASH_TYPE)_$($(n)$(FSTYPE))_fsimage)
BOOT_TARGET_NOFSIMAGE:=$(foreach n,$(filter-out $(BOOT_FSIMAGE_LIST), $(BOOT_IMAGE_LIST)),$(n)_nofsimage)

LINUX_FSIMAGE_LIST:=$(filter-out $(patsubst %_fs__,%,$(filter %_fs__, $(foreach n,$(LINUX_IMAGE_LIST),$(n)_fs_$($(n)$(FSTYPE))_))),$(LINUX_IMAGE_LIST))
LINUX_TARGET_FSIMAGE:=$(foreach n,$(LINUX_FSIMAGE_LIST),$(n)_$(LINUX_FLASH_TYPE)_$($(n)$(FSTYPE))_fsimage)
LINUX_TARGET_NOFSIMAGE:=$(foreach n,$(filter-out $(LINUX_FSIMAGE_LIST), $(LINUX_IMAGE_LIST)),$(n)_nofsimage)

ifeq ($(FLASH_TYPE), nor)
	FLASH_INFO_SUFFIX = nri
else
ifeq ($(FLASH_TYPE), spinand)
	FLASH_INFO_SUFFIX = sni
endif
endif

ifeq ($(LINUX_FLASH_TYPE), emmc)
images: $(TARGET_FSIMAGE) $(TARGET_NOFSIMAGE) $(LINUX_TARGET_FSIMAGE) $(LINUX_TARGET_NOFSIMAGE)
else
images: $(TARGET_FSIMAGE) $(TARGET_NOFSIMAGE)
endif

%_$(LINUX_FLASH_TYPE)_ext4_fsimage:
	@echo [[$@]]
	mke2fs -d $($(patsubst %_$(LINUX_FLASH_TYPE)_ext4_fsimage,%,$@)$(RESOUCE)) -t ext4 $(IMAGEDIR)/$(patsubst %_$(LINUX_FLASH_TYPE)_ext4_fsimage,%,$@).ext4 $$(($($(patsubst %_$(LINUX_FLASH_TYPE)_ext4_fsimage,%,$@)$(PATSIZE))/1024/1024))M

#the system can't bootup while use mkquashfs_xz compress.
%_$(FLASH_TYPE)_squashfs_fsimage: ./build/mksquashfs_xz
	@echo [[$@]]
	./build/mksquashfs_xz $($(patsubst %_$(FLASH_TYPE)_squashfs_fsimage,%,$@)$(RESOUCE)) $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_squashfs_fsimage,%,$@).sqfs -comp xz -all-root

%_$(FLASH_TYPE)_jffs2_fsimage: ./build/mkfs.jffs2
	@echo [[$@]]
	./build/mkfs.jffs2  $($(patsubst %_$(FLASH_TYPE)_jffs2_fsimage,%,$@)$(PATSIZE)) --pad=$($(patsubst %_$(FLASH_TYPE)_jffs2_fsimage,%,$@)$(PATSIZE)) --eraseblock=0x10000 -d $($(patsubst %_$(FLASH_TYPE)_jffs2_fsimage,%,$@)$(RESOUCE)) -o $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_jffs2_fsimage,%,$@).jffs2

%_$(FLASH_TYPE)_lfs_fsimage: ./build/mklittlefs
	@echo [[$@]]
	$(PROJ_ROOT)/image/makefiletools/script/lfs_pack.py --part_size=$($(patsubst %_$(FLASH_TYPE)_lfs_fsimage,%,$@)$(PATSIZE)) $($(patsubst %_$(FLASH_TYPE)_lfs_fsimage,%,$@)$(RESOUCE)) $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_lfs_fsimage,%,$@).lfs

%_$(FLASH_TYPE)_fwfs_fsimage: ./build/mkfwfs
	@echo [[$@]]
	$(PROJ_ROOT)/image/makefiletools/script/fwfs_pack.py --flash_type=$(FLASH_TYPE) --part_size=$($(patsubst %_$(FLASH_TYPE)_fwfs_fsimage,%,$@)$(PATSIZE)) $($(patsubst %_$(FLASH_TYPE)_fwfs_fsimage,%,$@)$(RESOUCE)) $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_fwfs_fsimage,%,$@).fwfs

# ubifs default settings
#ifeq ($(UBI_MLC_TYPE), 0)
ERASE_BLOCK_SIZE0   :=0x20000
NAND_PAGE_SIZE0     :=0x800
UBI_LEB_SIZE0       :=126976
RESERVED_SIZE0      :=0
#else ifeq ($(UBI_MLC_TYPE), 1)
ERASE_BLOCK_SIZE1   :=0x40000
NAND_PAGE_SIZE1     :=0x1000
UBI_LEB_SIZE1       :=253952
RESERVED_SIZE1      :=4
#else ifeq ($(UBI_MLC_TYPE), 2)
ERASE_BLOCK_SIZE2   :=0x100000
NAND_PAGE_SIZE2     :=0x2000
UBI_LEB_SIZE2       :=1032192
RESERVED_SIZE2      :=0
#else
ERASE_BLOCK_SIZE    :=0x20000
NAND_PAGE_SIZE      :=0x800
UBI_LEB_SIZE        :=126976
RESERVED_SIZE       :=0
#endif

define makebin
if [ $(1) != "0" ]; then \
	dd if=/dev/zero bs=$(1) count=1 | tr '\000' '\377' > $(2)_tmp;	\
	dd if=$(3) of=$(2)_tmp bs=$(1) count=1 conv=notrunc seek=0;	\
	for Row in {1..$(4)};do	\
		dd if=$(2)_tmp of=$(2) bs=$(1) count=1 conv=notrunc oflag=append;	\
	done;	\
	rm -rf $(2)_tmp;	\
fi;
endef


define updatecis
loop=$$[$$(stat -c "%s" $(3))/512-1];	\
for i in `seq 0 $${loop}`;do \
	blk_pb0_off=$$[$${i}*512+0x2F];	\
	blk_pb1_off=$$[$${i}*512+0x30];	\
	printf "%x: %02x" $${blk_pb0_off} $(1) | xxd -r - $(3);		\
	printf "%x: %02x" $${blk_pb1_off} $(2) | xxd -r - $(3);		\
done;
endef

TARGET_BOOT_IMAGE:=$(foreach n,$(BOOT_IMAGE_LIST),$(n)_mkboot)

boot_images:
	$(MAKE) $(TARGET_BOOT_IMAGE)
	cat $(foreach n,$(TARGET_BOOT_IMAGE),$(IMAGEDIR)/$(n)) > $(IMAGEDIR)/boot.bin
	rm -rfv $(foreach n,$(TARGET_BOOT_IMAGE),$(IMAGEDIR)/$(n))

%_mkboot:
	@if [ $(shell printf "%d" $($(patsubst %_mkboot,%,$@)$(DATASIZE))) -lt $(shell printf "%d" $(call filesize, $($(patsubst %_mkboot,%,$@)$(RESOUCE)))) ] ; then \
		echo "ERROR !!!!! $(patsubst %_mkboot,%,$@) resource file size is little than data size in config file"; \
		exit 1;  \
	fi;
	dd if=/dev/zero bs=$(shell printf "%d" $($(patsubst %_mkboot,%,$@)$(DATASIZE))) count=1 | tr '\000' '\377' > $(IMAGEDIR)/$@;
	dd if=$($(patsubst %_mkboot,%,$@)$(RESOUCE)) of=$(IMAGEDIR)/$@ bs=$(shell printf "%d" $($(patsubst %_mkboot,%,$@)$(DATASIZE))) count=1 conv=notrunc seek=0;
	if [ "$($(patsubst %_mkboot,%,$@)$(COPIES))" != "" ]; then \
		for((Row=1;Row<$($(patsubst %_mkboot,%,$@)$(COPIES));Row++));do \
			dd if=$(IMAGEDIR)/$@ of=$(IMAGEDIR)/$@ bs=$(shell printf "%d" $($(patsubst %_mkboot,%,$@)$(DATASIZE))) count=1 conv=notrunc seek=$${Row}; \
		done; \
	fi;

cis_nofsimage:
	@echo [[$@]]
	cp -vf $(PROJ_ROOT)/board/$(CHIP)/boot/$(FLASH_TYPE)/partition/* $(IMAGEDIR)/boot/
	$(PROJ_ROOT)/image/makefiletools/bin/pnigenerator -c $(FLASH_BLK_CNT) -s $(FLASH_BLK_SIZE) -a "$(cis$(BOOTTAB0))" -b "$(cis$(BOOTTAB1))" -t "$(cis$(SYSTAB))" -o $(IMAGEDIR)/boot/partinfo.pni	\
			$(filter-out %=,$(strip $(foreach n, $(IMAGE_LIST), $(n)_bbm=$($(n)$(BBMCFG))))) > $(IMAGEDIR)/partition_layout.txt
	cat $(IMAGEDIR)/partition_layout.txt
	if [ "$(FLASH_TYPE)" = "spinand" ]; then	\
		$(call updatecis,$(BLK_PB0_OFFSET),$(BLK_PB1_OFFSET),$(IMAGEDIR)/boot/flash.$(FLASH_INFO_SUFFIX))	\
		$(call updatecis,$(BLK_PB0_OFFSET),$(BLK_PB1_OFFSET),$(IMAGEDIR)/boot/flash_list.$(FLASH_INFO_SUFFIX))	\
	fi;
	dd if=/dev/zero bs=$(shell printf "%d" $(cis$(PGSIZE))) count=2 | tr '\000' '\377' > $(cis$(RESOUCE))
	dd if=$(IMAGEDIR)/boot/flash.$(FLASH_INFO_SUFFIX) of=$(cis$(RESOUCE)) bs=$(shell printf "%d" $(cis$(PGSIZE))) count=1 conv=notrunc seek=0
	dd if=$(IMAGEDIR)/boot/partinfo.pni of=$(cis$(RESOUCE)) bs=$(shell printf "%d" $(cis$(PGSIZE))) count=1 conv=notrunc seek=1
	cat $(IMAGEDIR)/boot/flash_list.$(FLASH_INFO_SUFFIX) >> $(cis$(RESOUCE))

ipl_nofsimage ipl_cust_nofsimage uboot_nofsimage:
	@echo [[$@]]
	cp -vf $($(patsubst %_nofsimage,%,$@)$(RESOUCE)) $(IMAGEDIR)/boot/

iplx_uboot_nofsimage:
	@echo [[$@]]
	cat $(iplx$(RESOUCE)) $(uboot$(RESOUCE)) > $(IMAGEDIR)/boot/BOOT_PART.bin

key_cust_nofsimage:
	@echo [[$@]]

boot_nofsimage: $(BOOT_TARGET_NOFSIMAGE) $(BOOT_TARGET_FSIMAGE)
	@echo [[$@]]
	$(MAKE) boot_images

logo_nofsimage:
	@echo [[$@]]
	$(PROJ_ROOT)/image/makefiletools/bin/dispcfggen -c -o $(logo$(RESOUCE)) -p $(LOGO_ADDR) -s $(BOOTLOGO_BUFSIZE) -d $(DISP_OUT_NAME)
	$(PROJ_ROOT)/image/makefiletools/bin/logogen -a -i $(PROJ_ROOT)/board/ini/misc/$(BOOTLOGO_FILE) -o $(logo$(RESOUCE))
ifneq ($(UPGRADE_FILE),)
	$(PROJ_ROOT)/image/makefiletools/bin/logogen -a -i $(PROJ_ROOT)/board/ini/misc/$(UPGRADE_FILE) -o $(logo$(RESOUCE))
else
	$(PROJ_ROOT)/image/makefiletools/bin/logogen -a -i $(PROJ_ROOT)/board/ini/misc/upgrade.jpg -o $(logo$(RESOUCE))
endif

%_$(FLASH_TYPE)_ramfs_fsimage:
	@echo [[$@]]
ifeq ($(PRODUCT), cardv)
	cd $(PROJ_ROOT)/kbuild/$(KERNEL_VERSION);./scripts/gen_initramfs_list.sh -o $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_ramfs_fsimage,%,$@).xz -u 0 -g 0 $(OUTPUTDIR)/rootfs/
else
	cd $(PROJ_ROOT)/kbuild/$(KERNEL_VERSION);./scripts/gen_initramfs_list.sh -o $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_ramfs_fsimage,%,$@).gz -u 0 -g 0 $(OUTPUTDIR)/rootfs/
	mv $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_ramfs_fsimage,%,$@).gz $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_ramfs_fsimage,%,$@).ramfs
endif

%_$(FLASH_TYPE)_ramfs_nocompress_fsimage:
	@echo [[$@]]
	cd $(PROJ_ROOT)/kbuild/$(KERNEL_VERSION);./scripts/gen_initramfs_list.sh -o $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_ramfs_nocompress_fsimage,%,$@).gz -u 0 -g 0 $(OUTPUTDIR)/rootfs/;
	gzip -d -n -f $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_ramfs_nocompress_fsimage,%,$@);
	mv $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_ramfs_nocompress_fsimage,%,$@) $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_ramfs_nocompress_fsimage,%,$@).ramfs

kernel_nofsimage:
	@echo [[$@]]
	cp -rvf $($(patsubst %_nofsimage,%,$@)$(RESOUCE)) $(IMAGEDIR)/$(patsubst %_nofsimage,%,$@)

%_$(FLASH_TYPE)_gz_fsimage:
	@echo [[$@]]
	cd $(PROJ_ROOT)/kbuild/$(KERNEL_VERSION);./scripts/gen_initramfs_list.sh -o $(IMAGEDIR)/initramfs.gz -u 0 -g 0 $(OUTPUTDIR)/tmprd/;

ramdisk_nofsimage:
	@echo [[$@]]
	@ $(PROJ_ROOT)/kbuild/$(KERNEL_VERSION)/scripts/mkimage -A arm -O linux -C none -a 0 -e 0 -n "RAMDISK" -d $($(patsubst %_nofsimage,%,$@)$(RESOUCE)) $(IMAGEDIR)/$(patsubst %_nofsimage,%,$@)

rtos_nofsimage:
	@echo [[$@]]
	#@$(PREFIX)objcopy -O binary -R .bss -R .bss_sram $($(patsubst %_nofsimage,%,$@)$(RESOUCE)) $(IMAGEDIR)/$(patsubst %_nofsimage,%,$@)
	cp $($(patsubst %_nofsimage,%,$@)$(RESOUCE)) $(IMAGEDIR)/$(patsubst %_nofsimage,%,$@)
%_$(FLASH_TYPE)_ubifs_fsimage: ./build/mkfs.ubifs
	@echo [[$@]]
	./build/mkfs.ubifs -F -r $($(patsubst %_$(FLASH_TYPE)_ubifs_fsimage,%,$@)$(RESOUCE)) -o $(IMAGEDIR)/$(patsubst %_$(FLASH_TYPE)_ubifs_fsimage,%,$@).ubifs -m $(NAND_PAGE_SIZE$(UBI_MLC_TYPE)) -e $(UBI_LEB_SIZE$(UBI_MLC_TYPE)) -c `./build/calc_nand_mfs.sh $(patsubst %_$(FLASH_TYPE)_ubifs_fsimage,%,$@) $(NAND_PAGE_SIZE$(UBI_MLC_TYPE)) $(ERASE_BLOCK_SIZE$(UBI_MLC_TYPE)) $(RESERVED_SIZE$(UBI_MLC_TYPE)) $($(patsubst %_$(FLASH_TYPE)_ubifs_fsimage,%,$@)$(PATSIZE))`
