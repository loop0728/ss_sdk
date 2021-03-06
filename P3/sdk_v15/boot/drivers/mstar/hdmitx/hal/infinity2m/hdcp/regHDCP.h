/*
* regHDCP.h- Sigmastar
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

#ifndef _HDCP_REG_MCU_H_
#define _HDCP_REG_MCU_H_

#define DEF_HDCP14_TX_KEY_REG_BANK  0x072B00U
#define DEF_HDCP22_TX_KEY_REG_BANK  0x072700U // 0x172700U
#define DEF_HDCP14_TX_REG_BANK      0x072B00U // 0x172B00U
#define DEF_HDCP22_TX_REG_BANK      0x072F00U // 0x172F00U
#define DEF_HDMITX_PHY_REG_BANK     0x073000U // 0x173000U
#define DEF_HDCPKEY_REG_BANK        0x072500U // 0x172500U
#define DEF_COMBO_GP_TOP_REG_BANK   0x072600U // 0x172600U

#define DEF_HDCP14_RX_KEY_REG_BANK  0x000000U
#define DEF_HDCP22_RX_KEY_REG_BANK  0x072700U // 0x172700U
#define DEF_HDCP14_RX_REG_BANK      0x072200U // 0x172200U
#define DEF_HDCP22_RX_REG_BANK      0x072200U // 0x172200U

#define REG_HDCP14_TX_00_L          0x00U
#define REG_HDCP14_TX_01_L          0x01U
#define REG_HDCP14_TX_02_L          0x02U
#define REG_HDCP14_TX_03_L          0x03U
#define REG_HDCP14_TX_04_L          0x04U
#define REG_HDCP14_TX_05_L          0x05U
#define REG_HDCP14_TX_06_L          0x06U
#define REG_HDCP14_TX_07_L          0x07U
#define REG_HDCP14_TX_08_L          0x08U
#define REG_HDCP14_TX_09_L          0x09U
#define REG_HDCP14_TX_0A_L          0x0AU
#define REG_HDCP14_TX_0B_L          0x0BU
#define REG_HDCP14_TX_0C_L          0x0CU
#define REG_HDCP14_TX_0D_L          0x0DU
#define REG_HDCP14_TX_0E_L          0x0EU
#define REG_HDCP14_TX_0F_L          0x0FU
#define REG_HDCP14_TX_10_L          0x10U
#define REG_HDCP14_TX_11_L          0x11U
#define REG_HDCP14_TX_12_L          0x12U
#define REG_HDCP14_TX_13_L          0x13U
#define REG_HDCP14_TX_14_L          0x14U
#define REG_HDCP14_TX_15_L          0x15U
#define REG_HDCP14_TX_16_L          0x16U
#define REG_HDCP14_TX_17_L          0x17U
#define REG_HDCP14_TX_18_L          0x18U
#define REG_HDCP14_TX_19_L          0x19U
#define REG_HDCP14_TX_1A_L          0x1AU
#define REG_HDCP14_TX_1B_L          0x1BU
#define REG_HDCP14_TX_1C_L          0x1CU
#define REG_HDCP14_TX_1D_L          0x1DU
#define REG_HDCP14_TX_1E_L          0x1EU
#define REG_HDCP14_TX_1F_L          0x1FU
#define REG_HDCP14_TX_20_L          0x20U
#define REG_HDCP14_TX_21_L          0x21U
#define REG_HDCP14_TX_22_L          0x22U
#define REG_HDCP14_TX_23_L          0x23U
#define REG_HDCP14_TX_24_L          0x24U
#define REG_HDCP14_TX_25_L          0x25U
#define REG_HDCP14_TX_26_L          0x26U
#define REG_HDCP14_TX_27_L          0x27U
#define REG_HDCP14_TX_28_L          0x28U
#define REG_HDCP14_TX_29_L          0x29U
#define REG_HDCP14_TX_2A_L          0x2AU
#define REG_HDCP14_TX_2B_L          0x2BU
#define REG_HDCP14_TX_2C_L          0x2CU
#define REG_HDCP14_TX_2D_L          0x2DU
#define REG_HDCP14_TX_2E_L          0x2EU
#define REG_HDCP14_TX_2F_L          0x2FU
#define REG_HDCP14_TX_30_L          0x30U
#define REG_HDCP14_TX_31_L          0x31U
#define REG_HDCP14_TX_32_L          0x32U
#define REG_HDCP14_TX_33_L          0x33U
#define REG_HDCP14_TX_34_L          0x34U
#define REG_HDCP14_TX_35_L          0x35U
#define REG_HDCP14_TX_36_L          0x36U
#define REG_HDCP14_TX_37_L          0x37U
#define REG_HDCP14_TX_38_L          0x38U
#define REG_HDCP14_TX_39_L          0x39U
#define REG_HDCP14_TX_3A_L          0x3AU
#define REG_HDCP14_TX_3B_L          0x3BU
#define REG_HDCP14_TX_3C_L          0x3CU
#define REG_HDCP14_TX_3D_L          0x3DU
#define REG_HDCP14_TX_3E_L          0x3EU
#define REG_HDCP14_TX_3F_L          0x3FU

#define REG_HDCP22_TX_00_L          0x00U
#define REG_HDCP22_TX_01_L          0x01U
#define REG_HDCP22_TX_02_L          0x02U
#define REG_HDCP22_TX_03_L          0x03U
#define REG_HDCP22_TX_04_L          0x04U
#define REG_HDCP22_TX_05_L          0x05U
#define REG_HDCP22_TX_06_L          0x06U
#define REG_HDCP22_TX_07_L          0x07U
#define REG_HDCP22_TX_08_L          0x08U
#define REG_HDCP22_TX_09_L          0x09U
#define REG_HDCP22_TX_0A_L          0x0AU
#define REG_HDCP22_TX_0B_L          0x0BU
#define REG_HDCP22_TX_0C_L          0x0CU
#define REG_HDCP22_TX_0D_L          0x0DU
#define REG_HDCP22_TX_0E_L          0x0EU
#define REG_HDCP22_TX_0F_L          0x0FU
#define REG_HDCP22_TX_10_L          0x10U
#define REG_HDCP22_TX_11_L          0x11U
#define REG_HDCP22_TX_12_L          0x12U
#define REG_HDCP22_TX_13_L          0x13U
#define REG_HDCP22_TX_14_L          0x14U
#define REG_HDCP22_TX_15_L          0x15U
#define REG_HDCP22_TX_16_L          0x16U
#define REG_HDCP22_TX_17_L          0x17U
#define REG_HDCP22_TX_18_L          0x18U
#define REG_HDCP22_TX_19_L          0x19U
#define REG_HDCP22_TX_1A_L          0x1AU
#define REG_HDCP22_TX_1B_L          0x1BU
#define REG_HDCP22_TX_1C_L          0x1CU
#define REG_HDCP22_TX_1D_L          0x1DU
#define REG_HDCP22_TX_1E_L          0x1EU
#define REG_HDCP22_TX_1F_L          0x1FU
#define REG_HDCP22_TX_20_L          0x20U
#define REG_HDCP22_TX_21_L          0x21U
#define REG_HDCP22_TX_22_L          0x22U
#define REG_HDCP22_TX_23_L          0x23U
#define REG_HDCP22_TX_24_L          0x24U
#define REG_HDCP22_TX_25_L          0x25U
#define REG_HDCP22_TX_26_L          0x26U
#define REG_HDCP22_TX_27_L          0x27U
#define REG_HDCP22_TX_28_L          0x28U
#define REG_HDCP22_TX_29_L          0x29U
#define REG_HDCP22_TX_2A_L          0x2AU
#define REG_HDCP22_TX_2B_L          0x2BU
#define REG_HDCP22_TX_2C_L          0x2CU
#define REG_HDCP22_TX_2D_L          0x2DU
#define REG_HDCP22_TX_2E_L          0x2EU
#define REG_HDCP22_TX_2F_L          0x2FU
#define REG_HDCP22_TX_30_L          0x30U
#define REG_HDCP22_TX_31_L          0x31U
#define REG_HDCP22_TX_32_L          0x32U
#define REG_HDCP22_TX_33_L          0x33U
#define REG_HDCP22_TX_34_L          0x34U
#define REG_HDCP22_TX_35_L          0x35U
#define REG_HDCP22_TX_36_L          0x36U
#define REG_HDCP22_TX_37_L          0x37U
#define REG_HDCP22_TX_38_L          0x38U
#define REG_HDCP22_TX_39_L          0x39U
#define REG_HDCP22_TX_3A_L          0x3AU
#define REG_HDCP22_TX_3B_L          0x3BU
#define REG_HDCP22_TX_3C_L          0x3CU
#define REG_HDCP22_TX_3D_L          0x3DU
#define REG_HDCP22_TX_3E_L          0x3EU
#define REG_HDCP22_TX_3F_L          0x3FU

#define REG_HDMITX_PHY_00_L         0x00U
#define REG_HDMITX_PHY_01_L         0x01U
#define REG_HDMITX_PHY_02_L         0x02U
#define REG_HDMITX_PHY_03_L         0x03U
#define REG_HDMITX_PHY_04_L         0x04U
#define REG_HDMITX_PHY_05_L         0x05U
#define REG_HDMITX_PHY_06_L         0x06U
#define REG_HDMITX_PHY_07_L         0x07U
#define REG_HDMITX_PHY_08_L         0x08U
#define REG_HDMITX_PHY_09_L         0x09U
#define REG_HDMITX_PHY_0A_L         0x0AU
#define REG_HDMITX_PHY_0B_L         0x0BU
#define REG_HDMITX_PHY_0C_L         0x0CU
#define REG_HDMITX_PHY_0D_L         0x0DU
#define REG_HDMITX_PHY_0E_L         0x0EU
#define REG_HDMITX_PHY_0F_L         0x0FU
#define REG_HDMITX_PHY_10_L         0x10U
#define REG_HDMITX_PHY_11_L         0x11U
#define REG_HDMITX_PHY_12_L         0x12U
#define REG_HDMITX_PHY_13_L         0x13U
#define REG_HDMITX_PHY_14_L         0x14U
#define REG_HDMITX_PHY_15_L         0x15U
#define REG_HDMITX_PHY_16_L         0x16U
#define REG_HDMITX_PHY_17_L         0x17U
#define REG_HDMITX_PHY_18_L         0x18U
#define REG_HDMITX_PHY_19_L         0x19U
#define REG_HDMITX_PHY_1A_L         0x1AU
#define REG_HDMITX_PHY_1B_L         0x1BU
#define REG_HDMITX_PHY_1C_L         0x1CU
#define REG_HDMITX_PHY_1D_L         0x1DU
#define REG_HDMITX_PHY_1E_L         0x1EU
#define REG_HDMITX_PHY_1F_L         0x1FU
#define REG_HDMITX_PHY_20_L         0x20U
#define REG_HDMITX_PHY_21_L         0x21U
#define REG_HDMITX_PHY_22_L         0x22U
#define REG_HDMITX_PHY_23_L         0x23U
#define REG_HDMITX_PHY_24_L         0x24U
#define REG_HDMITX_PHY_25_L         0x25U
#define REG_HDMITX_PHY_26_L         0x26U
#define REG_HDMITX_PHY_27_L         0x27U
#define REG_HDMITX_PHY_28_L         0x28U
#define REG_HDMITX_PHY_29_L         0x29U
#define REG_HDMITX_PHY_2A_L         0x2AU
#define REG_HDMITX_PHY_2B_L         0x2BU
#define REG_HDMITX_PHY_2C_L         0x2CU
#define REG_HDMITX_PHY_2D_L         0x2DU
#define REG_HDMITX_PHY_2E_L         0x2EU
#define REG_HDMITX_PHY_2F_L         0x2FU
#define REG_HDMITX_PHY_30_L         0x30U
#define REG_HDMITX_PHY_31_L         0x31U
#define REG_HDMITX_PHY_32_L         0x32U
#define REG_HDMITX_PHY_33_L         0x33U
#define REG_HDMITX_PHY_34_L         0x34U
#define REG_HDMITX_PHY_35_L         0x35U
#define REG_HDMITX_PHY_36_L         0x36U
#define REG_HDMITX_PHY_37_L         0x37U
#define REG_HDMITX_PHY_38_L         0x38U
#define REG_HDMITX_PHY_39_L         0x39U
#define REG_HDMITX_PHY_3A_L         0x3AU
#define REG_HDMITX_PHY_3B_L         0x3BU
#define REG_HDMITX_PHY_3C_L         0x3CU
#define REG_HDMITX_PHY_3D_L         0x3DU
#define REG_HDMITX_PHY_3E_L         0x3EU
#define REG_HDMITX_PHY_3F_L         0x3FU

#define REG_HDCPKEY_BANK_00_L       0x00U
#define REG_HDCPKEY_BANK_01_L       0x01U
#define REG_HDCPKEY_BANK_02_L       0x02U
#define REG_HDCPKEY_BANK_03_L       0x03U
#define REG_HDCPKEY_BANK_04_L       0x04U
#define REG_HDCPKEY_BANK_05_L       0x05U
#define REG_HDCPKEY_BANK_06_L       0x06U
#define REG_HDCPKEY_BANK_07_L       0x07U
#define REG_HDCPKEY_BANK_08_L       0x08U
#define REG_HDCPKEY_BANK_09_L       0x09U
#define REG_HDCPKEY_BANK_0A_L       0x0AU
#define REG_HDCPKEY_BANK_0B_L       0x0BU
#define REG_HDCPKEY_BANK_0C_L       0x0CU
#define REG_HDCPKEY_BANK_0D_L       0x0DU
#define REG_HDCPKEY_BANK_0E_L       0x0EU
#define REG_HDCPKEY_BANK_0F_L       0x0FU
#define REG_HDCPKEY_BANK_10_L       0x10U
#define REG_HDCPKEY_BANK_11_L       0x11U
#define REG_HDCPKEY_BANK_12_L       0x12U
#define REG_HDCPKEY_BANK_13_L       0x13U
#define REG_HDCPKEY_BANK_14_L       0x14U
#define REG_HDCPKEY_BANK_15_L       0x15U
#define REG_HDCPKEY_BANK_16_L       0x16U
#define REG_HDCPKEY_BANK_17_L       0x17U
#define REG_HDCPKEY_BANK_18_L       0x18U
#define REG_HDCPKEY_BANK_19_L       0x19U
#define REG_HDCPKEY_BANK_1A_L       0x1AU
#define REG_HDCPKEY_BANK_1B_L       0x1BU
#define REG_HDCPKEY_BANK_1C_L       0x1CU
#define REG_HDCPKEY_BANK_1D_L       0x1DU
#define REG_HDCPKEY_BANK_1E_L       0x1EU
#define REG_HDCPKEY_BANK_1F_L       0x1FU
#define REG_HDCPKEY_BANK_20_L       0x20U
#define REG_HDCPKEY_BANK_21_L       0x21U
#define REG_HDCPKEY_BANK_22_L       0x22U
#define REG_HDCPKEY_BANK_23_L       0x23U
#define REG_HDCPKEY_BANK_24_L       0x24U
#define REG_HDCPKEY_BANK_25_L       0x25U
#define REG_HDCPKEY_BANK_26_L       0x26U
#define REG_HDCPKEY_BANK_27_L       0x27U
#define REG_HDCPKEY_BANK_28_L       0x28U
#define REG_HDCPKEY_BANK_29_L       0x29U
#define REG_HDCPKEY_BANK_2A_L       0x2AU
#define REG_HDCPKEY_BANK_2B_L       0x2BU
#define REG_HDCPKEY_BANK_2C_L       0x2CU
#define REG_HDCPKEY_BANK_2D_L       0x2DU
#define REG_HDCPKEY_BANK_2E_L       0x2EU
#define REG_HDCPKEY_BANK_2F_L       0x2FU
#define REG_HDCPKEY_BANK_30_L       0x30U
#define REG_HDCPKEY_BANK_31_L       0x31U
#define REG_HDCPKEY_BANK_32_L       0x32U
#define REG_HDCPKEY_BANK_33_L       0x33U
#define REG_HDCPKEY_BANK_34_L       0x34U
#define REG_HDCPKEY_BANK_35_L       0x35U
#define REG_HDCPKEY_BANK_36_L       0x36U
#define REG_HDCPKEY_BANK_37_L       0x37U
#define REG_HDCPKEY_BANK_38_L       0x38U
#define REG_HDCPKEY_BANK_39_L       0x39U
#define REG_HDCPKEY_BANK_3A_L       0x3AU
#define REG_HDCPKEY_BANK_3B_L       0x3BU
#define REG_HDCPKEY_BANK_3C_L       0x3CU
#define REG_HDCPKEY_BANK_3D_L       0x3DU
#define REG_HDCPKEY_BANK_3E_L       0x3EU
#define REG_HDCPKEY_BANK_3F_L       0x3FU

#define REG_COMBO_GP_TOP_00_L       0x00U
#define REG_COMBO_GP_TOP_01_L       0x01U
#define REG_COMBO_GP_TOP_02_L       0x02U
#define REG_COMBO_GP_TOP_03_L       0x03U
#define REG_COMBO_GP_TOP_04_L       0x04U
#define REG_COMBO_GP_TOP_05_L       0x05U
#define REG_COMBO_GP_TOP_06_L       0x06U
#define REG_COMBO_GP_TOP_07_L       0x07U
#define REG_COMBO_GP_TOP_08_L       0x08U
#define REG_COMBO_GP_TOP_09_L       0x09U
#define REG_COMBO_GP_TOP_0A_L       0x0AU
#define REG_COMBO_GP_TOP_0B_L       0x0BU
#define REG_COMBO_GP_TOP_0C_L       0x0CU
#define REG_COMBO_GP_TOP_0D_L       0x0DU
#define REG_COMBO_GP_TOP_0E_L       0x0EU
#define REG_COMBO_GP_TOP_0F_L       0x0FU
#define REG_COMBO_GP_TOP_10_L       0x10U
#define REG_COMBO_GP_TOP_11_L       0x11U
#define REG_COMBO_GP_TOP_12_L       0x12U
#define REG_COMBO_GP_TOP_13_L       0x13U
#define REG_COMBO_GP_TOP_14_L       0x14U
#define REG_COMBO_GP_TOP_15_L       0x15U
#define REG_COMBO_GP_TOP_16_L       0x16U
#define REG_COMBO_GP_TOP_17_L       0x17U
#define REG_COMBO_GP_TOP_18_L       0x18U
#define REG_COMBO_GP_TOP_19_L       0x19U
#define REG_COMBO_GP_TOP_1A_L       0x1AU
#define REG_COMBO_GP_TOP_1B_L       0x1BU
#define REG_COMBO_GP_TOP_1C_L       0x1CU
#define REG_COMBO_GP_TOP_1D_L       0x1DU
#define REG_COMBO_GP_TOP_1E_L       0x1EU
#define REG_COMBO_GP_TOP_1F_L       0x1FU
#define REG_COMBO_GP_TOP_20_L       0x20U
#define REG_COMBO_GP_TOP_21_L       0x21U
#define REG_COMBO_GP_TOP_22_L       0x22U
#define REG_COMBO_GP_TOP_23_L       0x23U
#define REG_COMBO_GP_TOP_24_L       0x24U
#define REG_COMBO_GP_TOP_25_L       0x25U
#define REG_COMBO_GP_TOP_26_L       0x26U
#define REG_COMBO_GP_TOP_27_L       0x27U
#define REG_COMBO_GP_TOP_28_L       0x28U
#define REG_COMBO_GP_TOP_29_L       0x29U
#define REG_COMBO_GP_TOP_2A_L       0x2AU
#define REG_COMBO_GP_TOP_2B_L       0x2BU
#define REG_COMBO_GP_TOP_2C_L       0x2CU
#define REG_COMBO_GP_TOP_2D_L       0x2DU
#define REG_COMBO_GP_TOP_2E_L       0x2EU
#define REG_COMBO_GP_TOP_2F_L       0x2FU
#define REG_COMBO_GP_TOP_30_L       0x30U
#define REG_COMBO_GP_TOP_31_L       0x31U
#define REG_COMBO_GP_TOP_32_L       0x32U
#define REG_COMBO_GP_TOP_33_L       0x33U
#define REG_COMBO_GP_TOP_34_L       0x34U
#define REG_COMBO_GP_TOP_35_L       0x35U
#define REG_COMBO_GP_TOP_36_L       0x36U
#define REG_COMBO_GP_TOP_37_L       0x37U
#define REG_COMBO_GP_TOP_38_L       0x38U
#define REG_COMBO_GP_TOP_39_L       0x39U
#define REG_COMBO_GP_TOP_3A_L       0x3AU
#define REG_COMBO_GP_TOP_3B_L       0x3BU
#define REG_COMBO_GP_TOP_3C_L       0x3CU
#define REG_COMBO_GP_TOP_3D_L       0x3DU
#define REG_COMBO_GP_TOP_3E_L       0x3EU
#define REG_COMBO_GP_TOP_3F_L       0x3FU
#define REG_COMBO_GP_TOP_40_L       0x40U

#endif // #ifndef _HDCP_REG_MCU_H_
