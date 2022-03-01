/*
 *#############################################################################
 * SigmaStar trade secret
 * Copyright (c) 2006-2011 SigmaStar Technology Corp.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * SigmaStar Technology Corp. and be kept in strict confidence
 * (SigmaStar Confidential Information) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of SigmaStar Confidential
 * Information is unlawful and strictly prohibited. SigmaStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */


#include <common.h>
#include <command.h>
#include <environment.h>
#include <malloc.h>
#include "asm/arch/mach/ms_types.h"
#include "asm/arch/mach/platform.h"
#include "asm/arch/mach/io.h"

#include <../drivers/mstar/aesdma/drvAESDMA.h>
#include <rtk.h>
#include <ipl.h>
#include <../drivers/mstar/flash_util/inc/flash_util.h>


extern void halt(void);
extern void Dump_data(void*    addr, int size);

#define SIG_SIZE            256
#define ENV_ROOTFS_SIZE     "rootfs_size"

int do_test_sig2(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    u32 img_addr, img_sz, key_addr, key_len, sig_addr, sig_len;


    if (argc < 6)
	{
		return CMD_RET_USAGE;
	}

    img_addr = (u32)simple_strtoul(argv[1], NULL, 16);
    img_sz = (u32)simple_strtoul(argv[2], NULL, 16);
    key_addr = (u32)simple_strtoul(argv[3], NULL, 16);
    key_len = (u32)simple_strtoul(argv[4], NULL, 16);
    sig_addr = (u32)simple_strtoul(argv[5], NULL, 16);
    sig_len = (u32)simple_strtoul(argv[6], NULL, 16);

    if(runAuthenticate2(img_addr, img_sz, key_addr, key_len, sig_addr, sig_len))
        printf("runAuthenticate2 passed!\n");
    else
        printf("runAuthenticate2 failed!\n");

    return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	test_sig, CONFIG_SYS_MAXARGS, 1,	do_test_sig2,
	"Test runAuthenticate2\n",
	"test_sig img_addr img_sz key_addr key_len sig_addr sig_len(bytes)\n"
);

static u32 calc_checksum(void *buf, U32 size)
{
    U32 i;
    U32 sum = 0;

    for (i = 0; size > i; i += 4)
        sum += *(volatile U32*)(buf + i);
    return sum;
}

#ifdef CONFIG_MS_ISP_FLASH

#include <spi_flash.h>

static u8 _flash_get_keyN(const char *parts, u32 u32_keyN, u32 u32_size)
{
    struct spi_flash *flash;

    u8 u8_ret;

    size_t offset;
    size_t limit;
    size_t rsize;

    offset = 0;
    limit = 0;

    if (NULL == (flash = spi_flash_probe(0, 0, 0, 0)))
    {
        return 0;
    }

    do
    {
        u8_ret = 1;

        flash_get_parts(flash, parts, &offset, &limit);

        rsize = 32;

        if (spi_flash_read(flash, offset, rsize, (void*)u32_keyN))
        {
            break;
        }

        rsize = *((u16*)(u32_keyN + 8));
        rsize = (rsize + 0xf) &~0xf;
        offset += (rsize - SIG_SIZE);
        if (spi_flash_read(flash, offset, u32_size, (void*)u32_keyN))
        {
            break;
        }

        u8_ret = 0;

    } while (0);

    free(flash);

    return u8_ret;
}
#endif

#ifdef CONFIG_MS_SPINAND

#include <nand.h>

static u8 _flash_get_keyN(const char *parts, u32 u32_keyN, u32 u32_size)
{
    nand_info_t *nand;

    size_t offset;
    size_t limit;
    size_t rsize;

    nand = &nand_info[nand_curr_device];

    offset = 0;
    limit = 0;

    do
    {
        flash_get_parts(nand, parts, &offset, &limit);

        rsize = 32;

        if (nand_read_skip_bad(nand, offset, &rsize, NULL, limit, (u_char*)u32_keyN))
        {
            break;
        }

        limit += offset;
        rsize = *((u16*)(u32_keyN + 8));
        rsize = (rsize + 0xf) &~0xf;
        offset += (rsize - SIG_SIZE);
        printf("%s: rsize = 0x%x\r\n", __func__, rsize);

        while (offset < limit)
        {
            if (nand_block_isbad(nand, offset & ~(nand->erasesize - 1)))
            {
			    printf("Skipping bad block 0x%x\n", offset & ~(nand->erasesize - 1));
                offset += nand->erasesize;
                continue;
            }

            if (!nand_read(nand, offset, &u32_size, (u_char*)u32_keyN))
            {
                printf("load key to 0x%x\r\n", u32_keyN);
                break;
            }

        }

        return 0;
    } while (0);

    return 1;
}
#endif

int do_sig_auth(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    u8 u8_key_type;
    const char *parts;
    u32 image = 0;
    u32 data = 0;
    u32 image_size = 0;
    u32 KeyN = 0;
    u32 KeyAES = 0;

    if (argc < 4)
	{
		return CMD_RET_USAGE;
	}

    if (strncmp(argv[1], "key", strlen("key")))
    {
        return CMD_RET_USAGE;
    }

    u8_key_type = (u8)simple_strtoul(argv[2], NULL, 16);

    if (0 == u8_key_type && argc < 4)
    {
        return CMD_RET_USAGE;
    }

    do
    {
        if (0 == u8_key_type)
        {
            printf("[U-Boot] OTP Key\n\r");
            KeyN = (u32)simple_strtoul(argv[3], NULL, 16);
            image = (u32)simple_strtoul(argv[4], NULL, 16);
        }
        else
        {
            if ((u32)NULL == (KeyN = (u32)malloc(SIG_SIZE)))
            {
                return 0;
            }

            parts = "IPL_CUST";

            if (2 == u8_key_type)
            {
                parts = "IPL";
            }

            if (_flash_get_keyN(parts, KeyN, SIG_SIZE))
            {
                break;
            }
            //Dump_data((void*)KeyN, SIG_SIZE);
            image = (u32)simple_strtoul(argv[3], NULL, 16);

            printf("[U-Boot] CUST Key(%s)\r\n", parts);
        }

        if (RTK_MAKER == image_get_rtk_maker(image))
        {
        #if defined(CONFIG_INFINITY6E)
            image_size = image_get_rtk_size(image) - image_get_rtk_header_size();
            data = image + image_get_rtk_header_size();
        #else
                image_size = image_get_rtk_size(image);
        #endif
        }
        else if (image_check_magic((const image_header_t*) image))
        {
            image_size = image_get_data_size((const image_header_t*)image);
            data = image_get_data((const image_header_t*)image);
        }
        else if (getenv(ENV_ROOTFS_SIZE))
        {
            image_size = getenv_ulong(ENV_ROOTFS_SIZE, 16, 0) - SIG_SIZE;
            data = image;
        }

        if (0 == image_size)
        {
            break;
        }

        printf("[U-Boot] Image size = %d bytes\n\r", image_size);

        if (5 <= argc && (!strncmp(argv[4], "--aes", strlen("--aes")) || !strncmp(argv[5], "--aes", strlen("--aes"))))
        {
            image_size = (image_size + 0x0000000f) & ~0x0000000f; //align 16 for aes
        }

        if (runAuthenticate(data, image_size, (U32*)KeyN))
        {
            printf("[U-Boot] Authenticate pass!\n\r");
        }
        else
        {
            printf("[U-Boot] Authenticate failed!\n\r");
            halt();
        }

        if (5 <= argc && (!strncmp(argv[4], "--aes", strlen("--aes")) || !strncmp(argv[5], "--aes", strlen("--aes"))))
        {
            runDecrypt(data, image_size, (U16*)KeyAES);

            if (image_check_magic((const image_header_t*) image))
            {
                if (!image_check_dcrc((const image_header_t *) image))
                {
                    printf("[U-Boot] CRC32 check error!\n\r");
                    halt();
                }
            }
            else if (RTK_MAKER == image_get_rtk_maker(image))
            {
                if (image_get_rtk_checksum (image) != calc_checksum((void*)data, (image_size)))
                {
                    printf("[U-Boot] RTK Checksum error!\n\r");
                    halt();
                }
            }
            else if (image_get_ipl_checksum(image) != calc_checksum((void*)data, (image_size - 16)))
            {
                printf("[U-Boot] Checksum error!\n\r");
                halt();
            }
            printf("[U-Boot] Checksum ok!\n\r");
        }

        if (0 != u8_key_type && 0 != KeyN)
        {
            free((void*)KeyN);
        }

        return CMD_RET_SUCCESS;
    } while (0);

    return CMD_RET_FAILURE;
}

U_BOOT_CMD(
	sigauth, CONFIG_SYS_MAXARGS, 1,	do_sig_auth,
	"Only verify digital signature and aes",
	"Usage: sigauth key [key type] [key Load Address] [image address] [--aes]\n\r"
	"if [key type] is zero, it means using otp key, appending [key Load Address] is necessary.\n\r"
	"if [key type] is 1, it means using ipl_cust key.\n\r"
	"if [key type] is 2, it means using ipl key.\n\r"
	"command with [--aes] means using AES decryption, but don't use AES decrption without [--aes].\n\r"
);

