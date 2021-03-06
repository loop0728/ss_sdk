/*
* camclk_id.h- Sigmastar
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

#ifndef __CAMCLK_ID_H__
#define __CAMCLK_ID_H__
typedef enum
{
    HAL_CAMCLK_SRC_CLK_VOID, 
    HAL_CAMCLK_SRC_CLK_utmi_480m, 
    HAL_CAMCLK_SRC_CLK_mpll_432m, 
    HAL_CAMCLK_SRC_CLK_upll_384m, 
    HAL_CAMCLK_SRC_CLK_upll_320m, 
    HAL_CAMCLK_SRC_CLK_mpll_288m, 
    HAL_CAMCLK_SRC_CLK_utmi_240m, 
    HAL_CAMCLK_SRC_CLK_mpll_216m, 
    HAL_CAMCLK_SRC_CLK_utmi_192m, 
    HAL_CAMCLK_SRC_CLK_mpll_172m, 
    HAL_CAMCLK_SRC_CLK_utmi_160m, 
    HAL_CAMCLK_SRC_CLK_mpll_123m, 
    HAL_CAMCLK_SRC_CLK_mpll_86m, 
    HAL_CAMCLK_SRC_CLK_mpll_288m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_288m_div4, 
    HAL_CAMCLK_SRC_CLK_mpll_288m_div8, 
    HAL_CAMCLK_SRC_CLK_mpll_288m_div32, 
    HAL_CAMCLK_SRC_CLK_mpll_216m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_216m_div4, 
    HAL_CAMCLK_SRC_CLK_mpll_216m_div8, 
    HAL_CAMCLK_SRC_CLK_mpll_123m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_86m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_86m_div4, 
    HAL_CAMCLK_SRC_CLK_mpll_86m_div16, 
    HAL_CAMCLK_SRC_CLK_utmi_192m_div4, 
    HAL_CAMCLK_SRC_CLK_utmi_160m_div4, 
    HAL_CAMCLK_SRC_CLK_utmi_160m_div5, 
    HAL_CAMCLK_SRC_CLK_utmi_160m_div8, 
    HAL_CAMCLK_SRC_CLK_xtali_12m, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div8, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div16, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div40, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div64, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div128, 
    HAL_CAMCLK_SRC_CLK_xtali_24m, 
    HAL_CAMCLK_SRC_CLK_lpll_clk, 
    HAL_CAMCLK_SRC_CLK_lpll_clk_div2, 
    HAL_CAMCLK_SRC_CLK_lpll_clk_div4, 
    HAL_CAMCLK_SRC_CLK_lpll_clk_div8, 
    HAL_CAMCLK_SRC_CLK_spi_synth_pll, 
    HAL_CAMCLK_SRC_CLK_fuart0_synth_out, 
    HAL_CAMCLK_SRC_CLK_miu_p, 
    HAL_CAMCLK_SRC_CLK_mcu_p, 
    HAL_CAMCLK_SRC_CLK_emac_testrx125_in_lan, 
    HAL_CAMCLK_SRC_CLK_armpll_37p125m, 
    HAL_CAMCLK_SRC_CLK_boot, 
    HAL_CAMCLK_SRC_CLK_mpll_144m, 
    HAL_CAMCLK_SRC_CLK_mpll_144m_div2, 
    HAL_CAMCLK_SRC_CLK_mpll_144m_div4, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div2, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div4, 
    HAL_CAMCLK_SRC_CLK_xtali_12m_div12, 
    HAL_CAMCLK_SRC_CLK_rtc_32k, 
    HAL_CAMCLK_SRC_CLK_rtc_32k_div4, 
    HAL_CAMCLK_SRC_CLK_ddr_syn, 
    HAL_CAMCLK_SRC_CLK_miu_rec, 
    HAL_CAMCLK_SRC_CLK_mcu, 
    HAL_CAMCLK_SRC_CLK_riubrdg, 
    HAL_CAMCLK_SRC_CLK_bdma, 
    HAL_CAMCLK_SRC_CLK_bdma2, 
    HAL_CAMCLK_SRC_CLK_bdma3, 
    HAL_CAMCLK_SRC_CLK_spi, 
    HAL_CAMCLK_SRC_CLK_uart0, 
    HAL_CAMCLK_SRC_CLK_uart1, 
    HAL_CAMCLK_SRC_CLK_uart2, 
    HAL_CAMCLK_SRC_CLK_fuart0_synth_in, 
    HAL_CAMCLK_SRC_CLK_fuart, 
    HAL_CAMCLK_SRC_CLK_mspi0, 
    HAL_CAMCLK_SRC_CLK_mspi1, 
    HAL_CAMCLK_SRC_CLK_miic0, 
    HAL_CAMCLK_SRC_CLK_miic1, 
    HAL_CAMCLK_SRC_CLK_keypad, 
    HAL_CAMCLK_SRC_CLK_bist, 
    HAL_CAMCLK_SRC_CLK_pwr_ctl, 
    HAL_CAMCLK_SRC_CLK_xtali, 
    HAL_CAMCLK_SRC_CLK_live_c, 
    HAL_CAMCLK_SRC_CLK_live, 
    HAL_CAMCLK_SRC_CLK_sr00_mclk, 
    HAL_CAMCLK_SRC_CLK_sr01_mclk, 
    HAL_CAMCLK_SRC_CLK_sata_phy_108, 
    HAL_CAMCLK_SRC_CLK_sata_phy_432, 
    HAL_CAMCLK_SRC_CLK_disp_432, 
    HAL_CAMCLK_SRC_CLK_pspi0, 
    HAL_CAMCLK_SRC_CLK_pspi1, 
    HAL_CAMCLK_SRC_CLK_upll_synth, 
    HAL_CAMCLK_SRC_CLK_xtali_sc_gp, 
    HAL_CAMCLK_SRC_CLK_bist_sc_gp, 
    HAL_CAMCLK_SRC_CLK_bist_isp_gp, 
    HAL_CAMCLK_SRC_CLK_bist_mcu, 
    HAL_CAMCLK_SRC_CLK_emac_ahb, 
    HAL_CAMCLK_SRC_CLK_jpe, 
    HAL_CAMCLK_SRC_CLK_aesdma, 
    HAL_CAMCLK_SRC_CLK_sdio, 
    HAL_CAMCLK_SRC_CLK_isp, 
    HAL_CAMCLK_SRC_CLK_fclk1, 
    HAL_CAMCLK_SRC_CLK_dip, 
    HAL_CAMCLK_SRC_CLK_ge, 
    HAL_CAMCLK_SRC_CLK_mop, 
    HAL_CAMCLK_SRC_CLK_disp_216, 
    HAL_CAMCLK_SRC_CLK_sc_pixel, 
    HAL_CAMCLK_SRC_CLK_sata_pm, 
    HAL_CAMCLK_SRC_CLK_sata_axi, 
    HAL_CAMCLK_SRC_CLK_mipi_tx_dsi, 
    HAL_CAMCLK_SRC_CLK_csi_mac_lptx_top_i_m00, 
    HAL_CAMCLK_SRC_CLK_csi_mac_top_i_m00, 
    HAL_CAMCLK_SRC_CLK_ns_top_i_m00, 
    HAL_CAMCLK_SRC_CLK_csi_mac_lptx_top_i_m01, 
    HAL_CAMCLK_SRC_CLK_csi_mac_top_i_m01, 
    HAL_CAMCLK_SRC_CLK_ns_top_i_m01, 
    HAL_CAMCLK_SRC_CLK_spi_pm, 
    HAL_CAMCLK_SRC_CLK_pm_sleep, 
    HAL_CAMCLK_SRC_CLK_pwm, 
    HAL_CAMCLK_SRC_CLK_sar, 
    HAL_CAMCLK_SRC_CLK_rtc, 
    HAL_CAMCLK_SRC_CLK_ir, 
    HAL_CAMCLK_SRC_Id_MAX
} HalCamClkSrcId_e;
#endif
