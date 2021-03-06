/* Copyright (c) 2018-2019 Sigmastar Technology Corp.
 All rights reserved.

  Unless otherwise stipulated in writing, any and all information contained
 herein regardless in any format shall remain the sole proprietary of
 Sigmastar Technology Corp. and be kept in strict confidence
 (��Sigmastar Confidential Information��) by the recipient.
 Any unauthorized act including without limitation unauthorized disclosure,
 copying, use, reproduction, sale, distribution, modification, disassembling,
 reverse engineering and compiling of the contents of Sigmastar Confidential
 Information is unlawful and strictly prohibited. Sigmastar hereby reserves the
 rights to any and all damages, losses, costs and expenses resulting therefrom.
*/

#define SCA_TOOL_VERSION            "SN SCA V3.0.2 "

////////////////////////////////////////////////////////////////////////////////
// DRAM memory map
//
// Every Module Memory Mapping need 4 define,
// and check code in "msAPI_Memory_DumpMemoryMap"
// 1. XXX_AVAILABLE : For get avaialble memory start address
// 2. XXX_ADR       : Real Address with Alignment
// 3. XXX_GAP_CHK   : For Check Memory Gap, for avoid memory waste
// 4. XXX_LEN       : For the Memory size of this Module usage
////////////////////////////////////////////////////////////////////////////////
#define ENABLE_MIU_1                0
#define ENABLE_MIU_2                0
#define MIU_DRAM_LEN                0x0004000000
#define MIU_DRAM_LEN0               0x0004000000
#define MIU_DRAM_LEN1               0x0000000000
#define MIU_DRAM_LEN2               0x0000000000
#define MIU_INTERVAL                0x0040000000
#define CPU_ALIGN                   0x0000001000

////////////////////////////////////////////////////////////////////////////////
//MIU SETTING
////////////////////////////////////////////////////////////////////////////////
#define MIU0_GROUP_SELMIU                        0000:0000:0000:0000:0000:0000
#define MIU0_GROUP_PRIORITY                        1:0:2:3
#define MIU1_GROUP_SELMIU                        5016:0201:1280:80B8:0004:F61F
#define MIU1_GROUP_PRIORITY                        1:0:2:3
#define MIU2_GROUP_SELMIU                        0000:0000:0000:0000:0000:0000
#define MIU2_GROUP_PRIORITY                        0:0:0:0
////////////////////////////////////////////////////////////////////////////////
//MEMORY TYPE
////////////////////////////////////////////////////////////////////////////////
#define MIU0                        (0x0000)
#define MIU1                        (0x0001)
#define MIU2                        (0x0002)

#define TYPE_NONE                   (0x0000 << 2)

#define UNCACHE                     (0x0001 << 2)
#define REMAPPING_TO_USER_SPACE     (0x0002 << 2)
#define CACHE                       (0x0004 << 2)
#define NONCACHE_BUFFERABLE         (0x0008 << 2)


#define CMA                         (0x0010 << 2)
//MIU_0_START
/* E_LX_MEM   */
#define E_LX_MEM_LAYER                                         0
#define E_LX_MEM_AVAILABLE                                     0x0000000000
#define E_LX_MEM_ADR                                           0x0000000000  //Alignment 0x01000
#define E_LX_MEM_GAP_CHK                                       0x0000000000
#define E_LX_MEM_LEN                                           0x0003F20000
#define E_LX_MEM_MEMORY_TYPE                                   (MIU0 | TYPE_NONE | UNCACHE | TYPE_NONE)
#define E_LX_MEM_CMA_HID                                       0

/* E_MMAP_ID_DUMMY2   */
#define E_MMAP_ID_DUMMY2_LAYER                                 0
#define E_MMAP_ID_DUMMY2_AVAILABLE                             0x0003F20000
#define E_MMAP_ID_DUMMY2_ADR                                   0x0003F20000  //Alignment 0
#define E_MMAP_ID_DUMMY2_GAP_CHK                               0x0000000000
#define E_MMAP_ID_DUMMY2_LEN                                   0x00000E0000
#define E_MMAP_ID_DUMMY2_MEMORY_TYPE                           (MIU0 | TYPE_NONE | UNCACHE | TYPE_NONE)
#define E_MMAP_ID_DUMMY2_CMA_HID                               0

/* E_MMAP_ID_GE_VQ   */
#define E_MMAP_ID_GE_VQ_LAYER                                  1
#define E_MMAP_ID_GE_VQ_AVAILABLE                              0x0003F20000
#define E_MMAP_ID_GE_VQ_ADR                                    0x0003F20000  //Alignment 0x01000
#define E_MMAP_ID_GE_VQ_GAP_CHK                                0x0000000000
#define E_MMAP_ID_GE_VQ_LEN                                    0x0000020000
#define E_MMAP_ID_GE_VQ_MEMORY_TYPE                            (MIU0 | TYPE_NONE | UNCACHE | TYPE_NONE)
#define E_MMAP_ID_GE_VQ_CMA_HID                                0

/* E_MMAP_ID_AI   */
#define E_MMAP_ID_AI_LAYER                                     1
#define E_MMAP_ID_AI_AVAILABLE                                 0x0003F40000
#define E_MMAP_ID_AI_ADR                                       0x0003F40000  //Alignment 0x01000
#define E_MMAP_ID_AI_GAP_CHK                                   0x0000000000
#define E_MMAP_ID_AI_LEN                                       0x0000020000
#define E_MMAP_ID_AI_MEMORY_TYPE                               (MIU0 | TYPE_NONE | UNCACHE | TYPE_NONE)
#define E_MMAP_ID_AI_CMA_HID                                   0

/* E_MMAP_ID_AO   */
#define E_MMAP_ID_AO_LAYER                                     1
#define E_MMAP_ID_AO_AVAILABLE                                 0x0003F60000
#define E_MMAP_ID_AO_ADR                                       0x0003F60000  //Alignment 0x01000
#define E_MMAP_ID_AO_GAP_CHK                                   0x0000000000
#define E_MMAP_ID_AO_LEN                                       0x0000020000
#define E_MMAP_ID_AO_MEMORY_TYPE                               (MIU0 | TYPE_NONE | UNCACHE | TYPE_NONE)
#define E_MMAP_ID_AO_CMA_HID                                   0

/* E_MMAP_ID_AO_TMP   */
#define E_MMAP_ID_AO_TMP_LAYER                                 1
#define E_MMAP_ID_AO_TMP_AVAILABLE                             0x0003F80000
#define E_MMAP_ID_AO_TMP_ADR                                   0x0003F80000  //Alignment 0x01000
#define E_MMAP_ID_AO_TMP_GAP_CHK                               0x0000000000
#define E_MMAP_ID_AO_TMP_LEN                                   0x0000020000
#define E_MMAP_ID_AO_TMP_MEMORY_TYPE                           (MIU0 | TYPE_NONE | UNCACHE | TYPE_NONE)
#define E_MMAP_ID_AO_TMP_CMA_HID                               0

/* E_MMAP_ID_RESERVE   */
#define E_MMAP_ID_RESERVE_LAYER                                1
#define E_MMAP_ID_RESERVE_AVAILABLE                            0x0003FA0000
#define E_MMAP_ID_RESERVE_ADR                                  0x0003FA0000  //Alignment 0x01000
#define E_MMAP_ID_RESERVE_GAP_CHK                              0x0000000000
#define E_MMAP_ID_RESERVE_LEN                                  0x0000060000
#define E_MMAP_ID_RESERVE_MEMORY_TYPE                          (MIU0 | TYPE_NONE | UNCACHE | TYPE_NONE)
#define E_MMAP_ID_RESERVE_CMA_HID                              0

//MIU_1_START

#define MIU0_END_ADR                                           0x0004000000
#define MMAP_COUNT                                             0x0000000007

#define TEST_4K_ALIGN                   1

/* CHK_VALUE = 25253481 */