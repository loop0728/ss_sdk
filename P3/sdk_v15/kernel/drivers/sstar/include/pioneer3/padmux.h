/*
* padmux.h- Sigmastar
*
* Copyright (c) [2019~2020] SigmaStar Technology.
*
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License version 2 for more details.
*
*/
#ifndef __PADMUX_H__
#define __PADMUX_H__

#define PINMUX_FOR_GPIO_MODE                    0x00

#define PINMUX_FOR_ALL_PAD_IN_1                 0x1
#define PINMUX_FOR_TEST_IN_MODE_1               0x2
#define PINMUX_FOR_TEST_IN_MODE_2               0x3
#define PINMUX_FOR_TEST_IN_MODE_3               0x4
#define PINMUX_FOR_TEST_OUT_MODE_1              0x5
#define PINMUX_FOR_TEST_OUT_MODE_2              0x6
#define PINMUX_FOR_TEST_OUT_MODE_3              0x7
#define PINMUX_FOR_I2C0_MODE_1                  0x8
#define PINMUX_FOR_I2C0_MODE_2                  0x9
#define PINMUX_FOR_I2C0_MODE_3                  0xa
#define PINMUX_FOR_I2C0_MODE_4                  0xb
#define PINMUX_FOR_I2C0_MODE_5                  0xc
#define PINMUX_FOR_I2C0_MODE_6                  0xd
#define PINMUX_FOR_I2C0_MODE_7                  0xe
#define PINMUX_FOR_I2C0_MODE_8                  0xf
#define PINMUX_FOR_I2C0_MODE_9                  0x10
#define PINMUX_FOR_I2C0_MODE_10                 0x11
#define PINMUX_FOR_I2C0_MODE_11                 0x12
#define PINMUX_FOR_I2C0_MODE_12                 0x13
#define PINMUX_FOR_I2C0_MODE_13                 0x14
#define PINMUX_FOR_I2C0_MODE_14                 0x15
#define PINMUX_FOR_I2C1_MODE_1                  0x16
#define PINMUX_FOR_I2C1_MODE_2                  0x17
#define PINMUX_FOR_I2C1_MODE_3                  0x18
#define PINMUX_FOR_I2C1_MODE_4                  0x19
#define PINMUX_FOR_I2C1_MODE_5                  0x1a
#define PINMUX_FOR_I2C1_MODE_6                  0x1b
#define PINMUX_FOR_I2C1_MODE_7                  0x1c
#define PINMUX_FOR_I2C1_MODE_8                  0x1d
#define PINMUX_FOR_I2C1_MODE_9                  0x1e
#define PINMUX_FOR_I2C1_MODE_10                 0x1f
#define PINMUX_FOR_I2C1_MODE_11                 0x20
#define PINMUX_FOR_SR0_MIPI_MODE_1              0x21
#define PINMUX_FOR_SR1_MIPI_MODE_1              0x22
#define PINMUX_FOR_SR1_MIPI_MODE_2              0x23
#define PINMUX_FOR_ISP_IR_MODE_1                0x24
#define PINMUX_FOR_ISP_IR_MODE_2                0x25
#define PINMUX_FOR_ISP_IR_MODE_3                0x26
#define PINMUX_FOR_SR0_CTRL_MODE_1              0x27
#define PINMUX_FOR_SR0_CTRL_MODE_2              0x28
#define PINMUX_FOR_SR0_MCLK_MODE_1              0x29
#define PINMUX_FOR_SR0_MCLK_MODE_2              0x2a
#define PINMUX_FOR_SR0_PDN_MODE_1               0x2b
#define PINMUX_FOR_SR0_RST_MODE_1               0x2c
#define PINMUX_FOR_SR0_RST_MODE_2               0x2d
#define PINMUX_FOR_SR1_CTRL_MODE_1              0x2e
#define PINMUX_FOR_SR1_CTRL_MODE_2              0x2f
#define PINMUX_FOR_SR1_MCLK_MODE_1              0x30
#define PINMUX_FOR_SR1_MCLK_MODE_2              0x31
#define PINMUX_FOR_SR1_PDN_MODE_1               0x32
#define PINMUX_FOR_SR1_PDN_MODE_2               0x33
#define PINMUX_FOR_SR1_RST_MODE_1               0x34
#define PINMUX_FOR_SR1_RST_MODE_2               0x35
#define PINMUX_FOR_SR0_BT601_MODE_1             0x36
#define PINMUX_FOR_SR0_BT601_MODE_2             0x37
#define PINMUX_FOR_SR0_BT601_MODE_3             0x38
#define PINMUX_FOR_SR0_BT656_MODE_1             0x39
#define PINMUX_FOR_SR0_BT656_MODE_2             0x3a
#define PINMUX_FOR_SR0_BT656_MODE_3             0x3b
#define PINMUX_FOR_SR0_BT656_MODE_4             0x3c
#define PINMUX_FOR_ETH0_MODE_1                  0x3d
#define PINMUX_FOR_ETH0_MODE_2                  0x3e
#define PINMUX_FOR_ETH0_MODE_3                  0x3f
#define PINMUX_FOR_ETH0_MODE_4                  0x40
#define PINMUX_FOR_ETH0_MODE_5                  0x41
#define PINMUX_FOR_ETH0_MODE_6                  0x42
#define PINMUX_FOR_ETH0_MODE_7                  0x43
#define PINMUX_FOR_ETH0_MODE_8                  0x44
#define PINMUX_FOR_ETH0_MODE_9                  0x45
#define PINMUX_FOR_ETH0_MODE_10                 0x46
#define PINMUX_FOR_ETH0_MODE_11                 0x47
#define PINMUX_FOR_ETH0_MODE_12                 0x48
#define PINMUX_FOR_TTL16_MODE_1                 0x49
#define PINMUX_FOR_TTL16_MODE_2                 0x4a
#define PINMUX_FOR_TTL16_MODE_3                 0x4b
#define PINMUX_FOR_TTL16_MODE_4                 0x4c
#define PINMUX_FOR_TTL18_MODE_1                 0x4d
#define PINMUX_FOR_TTL18_MODE_2                 0x4e
#define PINMUX_FOR_TTL18_MODE_3                 0x4f
#define PINMUX_FOR_TTL24_MODE_1                 0x50
#define PINMUX_FOR_TTL24_MODE_2                 0x51
#define PINMUX_FOR_TTL24_MODE_3                 0x52
#define PINMUX_FOR_TTL24_MODE_4                 0x53
#define PINMUX_FOR_TTL24_MODE_5                 0x54
#define PINMUX_FOR_RGB8_MODE_1                  0x55
#define PINMUX_FOR_RGB8_MODE_2                  0x56
#define PINMUX_FOR_RGB8_MODE_3                  0x57
#define PINMUX_FOR_BT656_OUT_MODE_1             0x58
#define PINMUX_FOR_BT656_OUT_MODE_2             0x59
#define PINMUX_FOR_BT656_OUT_MODE_3             0x5a
#define PINMUX_FOR_PSPI0_SR_MODE_1              0x5b
#define PINMUX_FOR_PSPI0_SR_MODE_2              0x5c
#define PINMUX_FOR_PSPI0_SR_MODE_3              0x5d
#define PINMUX_FOR_PSPI0_SR_MODE_4              0x5e
#define PINMUX_FOR_PSPI0_SR_MODE_5              0x5f
#define PINMUX_FOR_PSPI0_SR_MODE_6              0x60
#define PINMUX_FOR_PSPI0_G_MODE_1               0x61
#define PINMUX_FOR_PSPI0_G_MODE_2               0x62
#define PINMUX_FOR_SPI0_MODE_1                  0x63
#define PINMUX_FOR_SPI0_MODE_2                  0x64
#define PINMUX_FOR_SPI0_MODE_3                  0x65
#define PINMUX_FOR_SPI0_MODE_4                  0x66
#define PINMUX_FOR_SPI0_MODE_5                  0x67
#define PINMUX_FOR_PSPI1_PL_MODE_1              0x68
#define PINMUX_FOR_PSPI1_PL_MODE_2              0x69
#define PINMUX_FOR_PSPI1_PL_MODE_3              0x6a
#define PINMUX_FOR_PSPI1_PL_MODE_4              0x6b
#define PINMUX_FOR_PSPI1_PL_MODE_5              0x6c
#define PINMUX_FOR_PSPI1_PL_MODE_6              0x6d
#define PINMUX_FOR_PSPI1_PL_MODE_7              0x6e
#define PINMUX_FOR_PSPI1_PL_MODE_8              0x6f
#define PINMUX_FOR_PSPI1_PL_MODE_9              0x70
#define PINMUX_FOR_PSPI1_CS2_MODE_1             0x71
#define PINMUX_FOR_PSPI1_CS2_MODE_2             0x72
#define PINMUX_FOR_PSPI1_CS2_MODE_3             0x73
#define PINMUX_FOR_PSPI1_CS2_MODE_4             0x74
#define PINMUX_FOR_PSPI1_CS2_MODE_5             0x75
#define PINMUX_FOR_PSPI1_CS2_MODE_6             0x76
#define PINMUX_FOR_PSPI1_CS2_MODE_7             0x77
#define PINMUX_FOR_PSPI1_CS2_MODE_8             0x78
#define PINMUX_FOR_PSPI1_CS2_MODE_9             0x79
#define PINMUX_FOR_PSPI1_CS2_MODE_10            0x7a
#define PINMUX_FOR_PSPI1_TE_MODE_1              0x7b
#define PINMUX_FOR_PSPI1_TE_MODE_2              0x7c
#define PINMUX_FOR_PSPI1_TE_MODE_3              0x7d
#define PINMUX_FOR_PSPI1_TE_MODE_4              0x7e
#define PINMUX_FOR_PSPI1_TE_MODE_5              0x7f
#define PINMUX_FOR_PSPI1_TE_MODE_6              0x80
#define PINMUX_FOR_PSPI1_TE_MODE_7              0x81
#define PINMUX_FOR_PSPI1_TE_MODE_8              0x82
#define PINMUX_FOR_PSPI1_TE_MODE_9              0x83
#define PINMUX_FOR_PSPI1_TE_MODE_10             0x84
#define PINMUX_FOR_PSPI1_G_MODE_1               0x85
#define PINMUX_FOR_PSPI1_G_MODE_2               0x86
#define PINMUX_FOR_SPI1_MODE_1                  0x87
#define PINMUX_FOR_SPI1_MODE_2                  0x88
#define PINMUX_FOR_SPI1_MODE_3                  0x89
#define PINMUX_FOR_SPI1_MODE_4                  0x8a
#define PINMUX_FOR_SPI1_MODE_5                  0x8b
#define PINMUX_FOR_SPI1_MODE_6                  0x8c
#define PINMUX_FOR_SPI1_MODE_7                  0x8d
#define PINMUX_FOR_SPI1_MODE_8                  0x8e
#define PINMUX_FOR_SPI1_CS2_MODE_1              0x8f
#define PINMUX_FOR_SPI1_CS2_MODE_2              0x90
#define PINMUX_FOR_SPI1_CS2_MODE_3              0x91
#define PINMUX_FOR_SPI1_CS2_MODE_4              0x92
#define PINMUX_FOR_SPI1_CS2_MODE_5              0x93
#define PINMUX_FOR_SPI1_CS2_MODE_6              0x94
#define PINMUX_FOR_SDIO_MODE_1                  0x95
#define PINMUX_FOR_SDIO_MODE_2                  0x96
#define PINMUX_FOR_SD_CDZ_MODE_1                0x97
#define PINMUX_FOR_SD_CDZ_MODE_2                0x98
#define PINMUX_FOR_KEY_READ0_MODE_1             0x99
#define PINMUX_FOR_KEY_READ0_MODE_2             0x9a
#define PINMUX_FOR_KEY_READ0_MODE_3             0x9b
#define PINMUX_FOR_KEY_READ0_MODE_4             0x9c
#define PINMUX_FOR_KEY_READ0_MODE_5             0x9d
#define PINMUX_FOR_KEY_READ0_MODE_6             0x9e
#define PINMUX_FOR_KEY_READ0_MODE_7             0x9f
#define PINMUX_FOR_KEY_READ0_MODE_8             0xa0
#define PINMUX_FOR_KEY_READ0_MODE_9             0xa1
#define PINMUX_FOR_KEY_READ0_MODE_10            0xa2
#define PINMUX_FOR_KEY_READ0_MODE_11            0xa3
#define PINMUX_FOR_KEY_READ0_MODE_12            0xa4
#define PINMUX_FOR_KEY_READ0_MODE_13            0xa5
#define PINMUX_FOR_KEY_READ0_MODE_14            0xa6
#define PINMUX_FOR_KEY_READ1_MODE_1             0xa7
#define PINMUX_FOR_KEY_READ1_MODE_2             0xa8
#define PINMUX_FOR_KEY_READ1_MODE_3             0xa9
#define PINMUX_FOR_KEY_READ1_MODE_4             0xaa
#define PINMUX_FOR_KEY_READ1_MODE_5             0xab
#define PINMUX_FOR_KEY_READ1_MODE_6             0xac
#define PINMUX_FOR_KEY_READ1_MODE_7             0xad
#define PINMUX_FOR_KEY_READ1_MODE_8             0xae
#define PINMUX_FOR_KEY_READ1_MODE_9             0xaf
#define PINMUX_FOR_KEY_READ1_MODE_10            0xb0
#define PINMUX_FOR_KEY_READ1_MODE_11            0xb1
#define PINMUX_FOR_KEY_READ1_MODE_12            0xb2
#define PINMUX_FOR_KEY_READ1_MODE_13            0xb3
#define PINMUX_FOR_KEY_READ1_MODE_14            0xb4
#define PINMUX_FOR_KEY_READ2_MODE_1             0xb5
#define PINMUX_FOR_KEY_READ2_MODE_2             0xb6
#define PINMUX_FOR_KEY_READ2_MODE_3             0xb7
#define PINMUX_FOR_KEY_READ2_MODE_4             0xb8
#define PINMUX_FOR_KEY_READ2_MODE_5             0xb9
#define PINMUX_FOR_KEY_READ2_MODE_6             0xba
#define PINMUX_FOR_KEY_READ2_MODE_7             0xbb
#define PINMUX_FOR_KEY_READ2_MODE_8             0xbc
#define PINMUX_FOR_KEY_READ2_MODE_9             0xbd
#define PINMUX_FOR_KEY_READ2_MODE_10            0xbe
#define PINMUX_FOR_KEY_READ2_MODE_11            0xbf
#define PINMUX_FOR_KEY_READ2_MODE_12            0xc0
#define PINMUX_FOR_KEY_READ2_MODE_13            0xc1
#define PINMUX_FOR_KEY_READ2_MODE_14            0xc2
#define PINMUX_FOR_KEY_READ3_MODE_1             0xc3
#define PINMUX_FOR_KEY_READ3_MODE_2             0xc4
#define PINMUX_FOR_KEY_READ3_MODE_3             0xc5
#define PINMUX_FOR_KEY_READ3_MODE_4             0xc6
#define PINMUX_FOR_KEY_READ3_MODE_5             0xc7
#define PINMUX_FOR_KEY_READ3_MODE_6             0xc8
#define PINMUX_FOR_KEY_READ3_MODE_7             0xc9
#define PINMUX_FOR_KEY_READ3_MODE_8             0xca
#define PINMUX_FOR_KEY_READ3_MODE_9             0xcb
#define PINMUX_FOR_KEY_READ3_MODE_10            0xcc
#define PINMUX_FOR_KEY_READ3_MODE_11            0xcd
#define PINMUX_FOR_KEY_READ3_MODE_12            0xce
#define PINMUX_FOR_KEY_READ3_MODE_13            0xcf
#define PINMUX_FOR_KEY_READ3_MODE_14            0xd0
#define PINMUX_FOR_KEY_READ4_MODE_1             0xd1
#define PINMUX_FOR_KEY_READ4_MODE_2             0xd2
#define PINMUX_FOR_KEY_READ4_MODE_3             0xd3
#define PINMUX_FOR_KEY_READ4_MODE_4             0xd4
#define PINMUX_FOR_KEY_READ4_MODE_5             0xd5
#define PINMUX_FOR_KEY_READ4_MODE_6             0xd6
#define PINMUX_FOR_KEY_READ4_MODE_7             0xd7
#define PINMUX_FOR_KEY_READ4_MODE_8             0xd8
#define PINMUX_FOR_KEY_READ4_MODE_9             0xd9
#define PINMUX_FOR_KEY_READ4_MODE_10            0xda
#define PINMUX_FOR_KEY_READ4_MODE_11            0xdb
#define PINMUX_FOR_KEY_READ4_MODE_12            0xdc
#define PINMUX_FOR_KEY_READ4_MODE_13            0xdd
#define PINMUX_FOR_KEY_READ4_MODE_14            0xde
#define PINMUX_FOR_KEY_READ5_MODE_1             0xdf
#define PINMUX_FOR_KEY_READ5_MODE_2             0xe0
#define PINMUX_FOR_KEY_READ5_MODE_3             0xe1
#define PINMUX_FOR_KEY_READ5_MODE_4             0xe2
#define PINMUX_FOR_KEY_READ5_MODE_5             0xe3
#define PINMUX_FOR_KEY_READ5_MODE_6             0xe4
#define PINMUX_FOR_KEY_READ5_MODE_7             0xe5
#define PINMUX_FOR_KEY_READ5_MODE_8             0xe6
#define PINMUX_FOR_KEY_READ5_MODE_9             0xe7
#define PINMUX_FOR_KEY_READ5_MODE_10            0xe8
#define PINMUX_FOR_KEY_READ5_MODE_11            0xe9
#define PINMUX_FOR_KEY_READ5_MODE_12            0xea
#define PINMUX_FOR_KEY_READ5_MODE_13            0xeb
#define PINMUX_FOR_KEY_READ5_MODE_14            0xec
#define PINMUX_FOR_KEY_READ6_MODE_1             0xed
#define PINMUX_FOR_KEY_READ6_MODE_2             0xee
#define PINMUX_FOR_KEY_READ6_MODE_3             0xef
#define PINMUX_FOR_KEY_READ6_MODE_4             0xf0
#define PINMUX_FOR_KEY_READ6_MODE_5             0xf1
#define PINMUX_FOR_KEY_READ6_MODE_6             0xf2
#define PINMUX_FOR_KEY_READ6_MODE_7             0xf3
#define PINMUX_FOR_KEY_READ6_MODE_8             0xf4
#define PINMUX_FOR_KEY_READ6_MODE_9             0xf5
#define PINMUX_FOR_KEY_READ6_MODE_10            0xf6
#define PINMUX_FOR_KEY_READ6_MODE_11            0xf7
#define PINMUX_FOR_KEY_READ6_MODE_12            0xf8
#define PINMUX_FOR_KEY_READ6_MODE_13            0xf9
#define PINMUX_FOR_KEY_READ6_MODE_14            0xfa
#define PINMUX_FOR_KEY_SCAN0_MODE_1             0xfb
#define PINMUX_FOR_KEY_SCAN0_MODE_2             0xfc
#define PINMUX_FOR_KEY_SCAN0_MODE_3             0xfd
#define PINMUX_FOR_KEY_SCAN0_MODE_4             0xfe
#define PINMUX_FOR_KEY_SCAN0_MODE_5             0xff
#define PINMUX_FOR_KEY_SCAN0_MODE_6             0x100
#define PINMUX_FOR_KEY_SCAN0_MODE_7             0x101
#define PINMUX_FOR_KEY_SCAN0_MODE_8             0x102
#define PINMUX_FOR_KEY_SCAN0_MODE_9             0x103
#define PINMUX_FOR_KEY_SCAN0_MODE_10            0x104
#define PINMUX_FOR_KEY_SCAN0_MODE_11            0x105
#define PINMUX_FOR_KEY_SCAN0_MODE_12            0x106
#define PINMUX_FOR_KEY_SCAN0_MODE_13            0x107
#define PINMUX_FOR_KEY_SCAN0_MODE_14            0x108
#define PINMUX_FOR_KEY_SCAN1_MODE_1             0x109
#define PINMUX_FOR_KEY_SCAN1_MODE_2             0x10a
#define PINMUX_FOR_KEY_SCAN1_MODE_3             0x10b
#define PINMUX_FOR_KEY_SCAN1_MODE_4             0x10c
#define PINMUX_FOR_KEY_SCAN1_MODE_5             0x10d
#define PINMUX_FOR_KEY_SCAN1_MODE_6             0x10e
#define PINMUX_FOR_KEY_SCAN1_MODE_7             0x10f
#define PINMUX_FOR_KEY_SCAN1_MODE_8             0x110
#define PINMUX_FOR_KEY_SCAN1_MODE_9             0x111
#define PINMUX_FOR_KEY_SCAN1_MODE_10            0x112
#define PINMUX_FOR_KEY_SCAN1_MODE_11            0x113
#define PINMUX_FOR_KEY_SCAN1_MODE_12            0x114
#define PINMUX_FOR_KEY_SCAN1_MODE_13            0x115
#define PINMUX_FOR_KEY_SCAN1_MODE_14            0x116
#define PINMUX_FOR_KEY_SCAN2_MODE_1             0x117
#define PINMUX_FOR_KEY_SCAN2_MODE_2             0x118
#define PINMUX_FOR_KEY_SCAN2_MODE_3             0x119
#define PINMUX_FOR_KEY_SCAN2_MODE_4             0x11a
#define PINMUX_FOR_KEY_SCAN2_MODE_5             0x11b
#define PINMUX_FOR_KEY_SCAN2_MODE_6             0x11c
#define PINMUX_FOR_KEY_SCAN2_MODE_7             0x11d
#define PINMUX_FOR_KEY_SCAN2_MODE_8             0x11e
#define PINMUX_FOR_KEY_SCAN2_MODE_9             0x11f
#define PINMUX_FOR_KEY_SCAN2_MODE_10            0x120
#define PINMUX_FOR_KEY_SCAN2_MODE_11            0x121
#define PINMUX_FOR_KEY_SCAN2_MODE_12            0x122
#define PINMUX_FOR_KEY_SCAN2_MODE_13            0x123
#define PINMUX_FOR_KEY_SCAN2_MODE_14            0x124
#define PINMUX_FOR_KEY_SCAN3_MODE_1             0x125
#define PINMUX_FOR_KEY_SCAN3_MODE_2             0x126
#define PINMUX_FOR_KEY_SCAN3_MODE_3             0x127
#define PINMUX_FOR_KEY_SCAN3_MODE_4             0x128
#define PINMUX_FOR_KEY_SCAN3_MODE_5             0x129
#define PINMUX_FOR_KEY_SCAN3_MODE_6             0x12a
#define PINMUX_FOR_KEY_SCAN3_MODE_7             0x12b
#define PINMUX_FOR_KEY_SCAN3_MODE_8             0x12c
#define PINMUX_FOR_KEY_SCAN3_MODE_9             0x12d
#define PINMUX_FOR_KEY_SCAN3_MODE_10            0x12e
#define PINMUX_FOR_KEY_SCAN3_MODE_11            0x12f
#define PINMUX_FOR_KEY_SCAN3_MODE_12            0x130
#define PINMUX_FOR_KEY_SCAN3_MODE_13            0x131
#define PINMUX_FOR_KEY_SCAN3_MODE_14            0x132
#define PINMUX_FOR_KEY_SCAN4_MODE_1             0x133
#define PINMUX_FOR_KEY_SCAN4_MODE_2             0x134
#define PINMUX_FOR_KEY_SCAN4_MODE_3             0x135
#define PINMUX_FOR_KEY_SCAN4_MODE_4             0x136
#define PINMUX_FOR_KEY_SCAN4_MODE_5             0x137
#define PINMUX_FOR_KEY_SCAN4_MODE_6             0x138
#define PINMUX_FOR_KEY_SCAN4_MODE_7             0x139
#define PINMUX_FOR_KEY_SCAN4_MODE_8             0x13a
#define PINMUX_FOR_KEY_SCAN4_MODE_9             0x13b
#define PINMUX_FOR_KEY_SCAN4_MODE_10            0x13c
#define PINMUX_FOR_KEY_SCAN4_MODE_11            0x13d
#define PINMUX_FOR_KEY_SCAN4_MODE_12            0x13e
#define PINMUX_FOR_KEY_SCAN4_MODE_13            0x13f
#define PINMUX_FOR_KEY_SCAN4_MODE_14            0x140
#define PINMUX_FOR_KEY_SCAN5_MODE_1             0x141
#define PINMUX_FOR_KEY_SCAN5_MODE_2             0x142
#define PINMUX_FOR_KEY_SCAN5_MODE_3             0x143
#define PINMUX_FOR_KEY_SCAN5_MODE_4             0x144
#define PINMUX_FOR_KEY_SCAN5_MODE_5             0x145
#define PINMUX_FOR_KEY_SCAN5_MODE_6             0x146
#define PINMUX_FOR_KEY_SCAN5_MODE_7             0x147
#define PINMUX_FOR_KEY_SCAN5_MODE_8             0x148
#define PINMUX_FOR_KEY_SCAN5_MODE_9             0x149
#define PINMUX_FOR_KEY_SCAN5_MODE_10            0x14a
#define PINMUX_FOR_KEY_SCAN5_MODE_11            0x14b
#define PINMUX_FOR_KEY_SCAN5_MODE_12            0x14c
#define PINMUX_FOR_KEY_SCAN5_MODE_13            0x14d
#define PINMUX_FOR_KEY_SCAN5_MODE_14            0x14e
#define PINMUX_FOR_KEY_SCAN6_MODE_1             0x14f
#define PINMUX_FOR_KEY_SCAN6_MODE_2             0x150
#define PINMUX_FOR_KEY_SCAN6_MODE_3             0x151
#define PINMUX_FOR_KEY_SCAN6_MODE_4             0x152
#define PINMUX_FOR_KEY_SCAN6_MODE_5             0x153
#define PINMUX_FOR_KEY_SCAN6_MODE_6             0x154
#define PINMUX_FOR_KEY_SCAN6_MODE_7             0x155
#define PINMUX_FOR_KEY_SCAN6_MODE_8             0x156
#define PINMUX_FOR_KEY_SCAN6_MODE_9             0x157
#define PINMUX_FOR_KEY_SCAN6_MODE_10            0x158
#define PINMUX_FOR_KEY_SCAN6_MODE_11            0x159
#define PINMUX_FOR_KEY_SCAN6_MODE_12            0x15a
#define PINMUX_FOR_KEY_SCAN6_MODE_13            0x15b
#define PINMUX_FOR_KEY_SCAN6_MODE_14            0x15c
#define PINMUX_FOR_KEY_FIX_MODE_1               0x15d
#define PINMUX_FOR_FUART_MODE_1                 0x15e
#define PINMUX_FOR_FUART_MODE_2                 0x15f
#define PINMUX_FOR_FUART_MODE_3                 0x160
#define PINMUX_FOR_FUART_MODE_4                 0x161
#define PINMUX_FOR_FUART_MODE_5                 0x162
#define PINMUX_FOR_FUART_MODE_6                 0x163
#define PINMUX_FOR_FUART_MODE_7                 0x164
#define PINMUX_FOR_FUART_MODE_8                 0x165
#define PINMUX_FOR_FUART_MODE_9                 0x166
#define PINMUX_FOR_FUART_MODE_10                0x167
#define PINMUX_FOR_FUART_MODE_11                0x168
#define PINMUX_FOR_FUART_MODE_12                0x169
#define PINMUX_FOR_UART0_MODE_1                 0x16a
#define PINMUX_FOR_UART0_MODE_2                 0x16b
#define PINMUX_FOR_UART0_MODE_3                 0x16c
#define PINMUX_FOR_UART0_MODE_4                 0x16d
#define PINMUX_FOR_UART0_MODE_5                 0x16e
#define PINMUX_FOR_UART1_MODE_1                 0x16f
#define PINMUX_FOR_UART1_MODE_2                 0x170
#define PINMUX_FOR_UART1_MODE_3                 0x171
#define PINMUX_FOR_UART1_MODE_4                 0x172
#define PINMUX_FOR_UART1_MODE_5                 0x173
#define PINMUX_FOR_UART1_MODE_6                 0x174
#define PINMUX_FOR_UART1_MODE_7                 0x175
#define PINMUX_FOR_UART1_MODE_8                 0x176
#define PINMUX_FOR_UART1_MODE_9                 0x177
#define PINMUX_FOR_UART2_MODE_1                 0x178
#define PINMUX_FOR_UART2_MODE_2                 0x179
#define PINMUX_FOR_UART2_MODE_3                 0x17a
#define PINMUX_FOR_UART2_MODE_4                 0x17b
#define PINMUX_FOR_UART2_MODE_5                 0x17c
#define PINMUX_FOR_UART2_MODE_6                 0x17d
#define PINMUX_FOR_UART2_MODE_7                 0x17e
#define PINMUX_FOR_PWM0_MODE_1                  0x17f
#define PINMUX_FOR_PWM0_MODE_2                  0x180
#define PINMUX_FOR_PWM0_MODE_3                  0x181
#define PINMUX_FOR_PWM0_MODE_4                  0x182
#define PINMUX_FOR_PWM0_MODE_5                  0x183
#define PINMUX_FOR_PWM0_MODE_6                  0x184
#define PINMUX_FOR_PWM0_MODE_7                  0x185
#define PINMUX_FOR_PWM0_MODE_8                  0x186
#define PINMUX_FOR_PWM0_MODE_9                  0x187
#define PINMUX_FOR_PWM0_MODE_10                 0x188
#define PINMUX_FOR_PWM1_MODE_1                  0x189
#define PINMUX_FOR_PWM1_MODE_2                  0x18a
#define PINMUX_FOR_PWM1_MODE_3                  0x18b
#define PINMUX_FOR_PWM1_MODE_4                  0x18c
#define PINMUX_FOR_PWM1_MODE_5                  0x18d
#define PINMUX_FOR_PWM1_MODE_6                  0x18e
#define PINMUX_FOR_PWM1_MODE_7                  0x18f
#define PINMUX_FOR_PWM1_MODE_8                  0x190
#define PINMUX_FOR_PWM1_MODE_9                  0x191
#define PINMUX_FOR_PWM1_MODE_10                 0x192
#define PINMUX_FOR_PWM2_MODE_1                  0x193
#define PINMUX_FOR_PWM2_MODE_2                  0x194
#define PINMUX_FOR_PWM2_MODE_3                  0x195
#define PINMUX_FOR_PWM2_MODE_4                  0x196
#define PINMUX_FOR_PWM2_MODE_5                  0x197
#define PINMUX_FOR_PWM2_MODE_6                  0x198
#define PINMUX_FOR_PWM2_MODE_7                  0x199
#define PINMUX_FOR_PWM2_MODE_8                  0x19a
#define PINMUX_FOR_PWM2_MODE_9                  0x19b
#define PINMUX_FOR_PWM2_MODE_10                 0x19c
#define PINMUX_FOR_PWM2_MODE_11                 0x19d
#define PINMUX_FOR_PWM3_MODE_1                  0x19e
#define PINMUX_FOR_PWM3_MODE_2                  0x19f
#define PINMUX_FOR_PWM3_MODE_3                  0x1a0
#define PINMUX_FOR_PWM3_MODE_4                  0x1a1
#define PINMUX_FOR_PWM3_MODE_5                  0x1a2
#define PINMUX_FOR_PWM3_MODE_6                  0x1a3
#define PINMUX_FOR_PWM3_MODE_7                  0x1a4
#define PINMUX_FOR_PWM3_MODE_8                  0x1a5
#define PINMUX_FOR_PWM3_MODE_9                  0x1a6
#define PINMUX_FOR_PWM3_MODE_10                 0x1a7
#define PINMUX_FOR_DMIC_MODE_1                  0x1a8
#define PINMUX_FOR_DMIC_MODE_2                  0x1a9
#define PINMUX_FOR_DMIC_MODE_3                  0x1aa
#define PINMUX_FOR_DMIC_MODE_4                  0x1ab
#define PINMUX_FOR_DMIC_MODE_5                  0x1ac
#define PINMUX_FOR_DMIC_MODE_6                  0x1ad
#define PINMUX_FOR_DMIC_MODE_7                  0x1ae
#define PINMUX_FOR_DMIC_MODE_8                  0x1af
#define PINMUX_FOR_DMIC_MODE_9                  0x1b0
#define PINMUX_FOR_DMIC_MODE_10                 0x1b1
#define PINMUX_FOR_DMIC_MODE_11                 0x1b2
#define PINMUX_FOR_DMIC_MODE_12                 0x1b3
#define PINMUX_FOR_DMIC_MODE_13                 0x1b4
#define PINMUX_FOR_I2S_MCK_MODE_1               0x1b5
#define PINMUX_FOR_I2S_MCK_MODE_2               0x1b6
#define PINMUX_FOR_I2S_MCK_MODE_3               0x1b7
#define PINMUX_FOR_I2S_MCK_MODE_4               0x1b8
#define PINMUX_FOR_I2S_MCK_MODE_5               0x1b9
#define PINMUX_FOR_I2S_MCK_MODE_6               0x1ba
#define PINMUX_FOR_I2S_MCK_MODE_7               0x1bb
#define PINMUX_FOR_I2S_RX_MODE_1                0x1bc
#define PINMUX_FOR_I2S_RX_MODE_2                0x1bd
#define PINMUX_FOR_I2S_RX_MODE_3                0x1be
#define PINMUX_FOR_I2S_RX_MODE_4                0x1bf
#define PINMUX_FOR_I2S_RX_MODE_5                0x1c0
#define PINMUX_FOR_I2S_RX_MODE_6                0x1c1
#define PINMUX_FOR_I2S_TX_MODE_1                0x1c2
#define PINMUX_FOR_I2S_TX_MODE_2                0x1c3
#define PINMUX_FOR_I2S_TX_MODE_3                0x1c4
#define PINMUX_FOR_I2S_TX_MODE_4                0x1c5
#define PINMUX_FOR_I2S_TX_MODE_5                0x1c6
#define PINMUX_FOR_I2S_TX_MODE_6                0x1c7
#define PINMUX_FOR_I2S_RXTX_MODE_1              0x1c8
#define PINMUX_FOR_I2S_RXTX_MODE_2              0x1c9
#define PINMUX_FOR_I2S_RXTX_MODE_3              0x1ca
#define PINMUX_FOR_I2S_RXTX_MODE_4              0x1cb
#define PINMUX_FOR_I2S_RXTX_MODE_5              0x1cc
#define PINMUX_FOR_I2S_RXTX_MODE_6              0x1cd
#define PINMUX_FOR_BT1120_MODE_1                0x1ce
#define PINMUX_FOR_BT1120_MODE_2                0x1cf
#define PINMUX_FOR_BT1120_MODE_3                0x1d0
#define PINMUX_FOR_PM_SPI_GPIO_0                0x1d1
#define PINMUX_FOR_PM_SPIWPN_GPIO_0             0x1d2
#define PINMUX_FOR_PM_SPIHOLDN_MODE_0           0x1d3
#define PINMUX_FOR_PM_SPICSZ1_GPIO_0            0x1d4
#define PINMUX_FOR_PM_SPICSZ2_GPIO_0            0x1d5
#define PINMUX_FOR_PM_PWM0_MODE_1               0x1d6
#define PINMUX_FOR_PM_PWM1_MODE_1               0x1d7
#define PINMUX_FOR_PM_PWM2_MODE_1               0x1d8
#define PINMUX_FOR_PM_PWM3_MODE_1               0x1d9
#define PINMUX_FOR_PM_UART1_MODE_1              0x1da
#define PINMUX_FOR_PM_VID_MODE_1                0x1db
#define PINMUX_FOR_PM_VID_MODE_2                0x1dc
#define PINMUX_FOR_PM_VID_MODE_3                0x1dd
#define PINMUX_FOR_PM_SD_CDZ_MODE_1             0x1de
#define PINMUX_FOR_PM_LED_MODE_1                0x1df
#define PINMUX_FOR_PM_LED_MODE_2                0x1e0
#define PINMUX_FOR_PM_LED_MODE_3                0x1e1
#define PINMUX_FOR_PM_PAD_EXT_MODE_0_1          0x1e2
#define PINMUX_FOR_PM_PAD_EXT_MODE_1_1          0x1e3
#define PINMUX_FOR_PM_PAD_EXT_MODE_2_1          0x1e4
#define PINMUX_FOR_PM_PAD_EXT_MODE_3_1          0x1e5
#define PINMUX_FOR_PM_PAD_EXT_MODE_4_1          0x1e6
#define PINMUX_FOR_PM_PAD_EXT_MODE_5_1          0x1e7
#define PINMUX_FOR_PM_PAD_EXT_MODE_6_1          0x1e8
#define PINMUX_FOR_PM_PAD_EXT_MODE_7_1          0x1e9
#define PINMUX_FOR_PM_PAD_EXT_MODE_8_1          0x1ea
#define PINMUX_FOR_PM_PAD_EXT_MODE_9_1          0x1eb
#define PINMUX_FOR_PM_PAD_EXT_MODE_10_1         0x1ec
#define PINMUX_FOR_ETH_GPIO_EN_MODE             0x1ed
#define PINMUX_FOR_SAR_MODE                     0x1ef

#define PINMUX_FOR_UNKNOWN_MODE                 0xFFF

#endif    // __PADMUX_H__