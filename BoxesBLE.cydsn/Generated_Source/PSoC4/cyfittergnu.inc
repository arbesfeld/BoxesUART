.ifndef INCLUDED_CYFITTERGNU_INC
.set INCLUDED_CYFITTERGNU_INC, 1
.include "cydevicegnu_trm.inc"

/* LED */
.set LED__0__DR, CYREG_GPIO_PRT2_DR
.set LED__0__DR_CLR, CYREG_GPIO_PRT2_DR_CLR
.set LED__0__DR_INV, CYREG_GPIO_PRT2_DR_INV
.set LED__0__DR_SET, CYREG_GPIO_PRT2_DR_SET
.set LED__0__HSIOM, CYREG_HSIOM_PORT_SEL2
.set LED__0__HSIOM_MASK, 0x0F000000
.set LED__0__HSIOM_SHIFT, 24
.set LED__0__INTCFG, CYREG_GPIO_PRT2_INTR_CFG
.set LED__0__INTR, CYREG_GPIO_PRT2_INTR
.set LED__0__INTR_CFG, CYREG_GPIO_PRT2_INTR_CFG
.set LED__0__INTSTAT, CYREG_GPIO_PRT2_INTR
.set LED__0__MASK, 0x40
.set LED__0__PA__CFG0, CYREG_UDB_PA2_CFG0
.set LED__0__PA__CFG1, CYREG_UDB_PA2_CFG1
.set LED__0__PA__CFG10, CYREG_UDB_PA2_CFG10
.set LED__0__PA__CFG11, CYREG_UDB_PA2_CFG11
.set LED__0__PA__CFG12, CYREG_UDB_PA2_CFG12
.set LED__0__PA__CFG13, CYREG_UDB_PA2_CFG13
.set LED__0__PA__CFG14, CYREG_UDB_PA2_CFG14
.set LED__0__PA__CFG2, CYREG_UDB_PA2_CFG2
.set LED__0__PA__CFG3, CYREG_UDB_PA2_CFG3
.set LED__0__PA__CFG4, CYREG_UDB_PA2_CFG4
.set LED__0__PA__CFG5, CYREG_UDB_PA2_CFG5
.set LED__0__PA__CFG6, CYREG_UDB_PA2_CFG6
.set LED__0__PA__CFG7, CYREG_UDB_PA2_CFG7
.set LED__0__PA__CFG8, CYREG_UDB_PA2_CFG8
.set LED__0__PA__CFG9, CYREG_UDB_PA2_CFG9
.set LED__0__PC, CYREG_GPIO_PRT2_PC
.set LED__0__PC2, CYREG_GPIO_PRT2_PC2
.set LED__0__PORT, 2
.set LED__0__PS, CYREG_GPIO_PRT2_PS
.set LED__0__SHIFT, 6
.set LED__DR, CYREG_GPIO_PRT2_DR
.set LED__DR_CLR, CYREG_GPIO_PRT2_DR_CLR
.set LED__DR_INV, CYREG_GPIO_PRT2_DR_INV
.set LED__DR_SET, CYREG_GPIO_PRT2_DR_SET
.set LED__INTCFG, CYREG_GPIO_PRT2_INTR_CFG
.set LED__INTR, CYREG_GPIO_PRT2_INTR
.set LED__INTR_CFG, CYREG_GPIO_PRT2_INTR_CFG
.set LED__INTSTAT, CYREG_GPIO_PRT2_INTR
.set LED__MASK, 0x40
.set LED__PA__CFG0, CYREG_UDB_PA2_CFG0
.set LED__PA__CFG1, CYREG_UDB_PA2_CFG1
.set LED__PA__CFG10, CYREG_UDB_PA2_CFG10
.set LED__PA__CFG11, CYREG_UDB_PA2_CFG11
.set LED__PA__CFG12, CYREG_UDB_PA2_CFG12
.set LED__PA__CFG13, CYREG_UDB_PA2_CFG13
.set LED__PA__CFG14, CYREG_UDB_PA2_CFG14
.set LED__PA__CFG2, CYREG_UDB_PA2_CFG2
.set LED__PA__CFG3, CYREG_UDB_PA2_CFG3
.set LED__PA__CFG4, CYREG_UDB_PA2_CFG4
.set LED__PA__CFG5, CYREG_UDB_PA2_CFG5
.set LED__PA__CFG6, CYREG_UDB_PA2_CFG6
.set LED__PA__CFG7, CYREG_UDB_PA2_CFG7
.set LED__PA__CFG8, CYREG_UDB_PA2_CFG8
.set LED__PA__CFG9, CYREG_UDB_PA2_CFG9
.set LED__PC, CYREG_GPIO_PRT2_PC
.set LED__PC2, CYREG_GPIO_PRT2_PC2
.set LED__PORT, 2
.set LED__PS, CYREG_GPIO_PRT2_PS
.set LED__SHIFT, 6

/* Pin_1 */
.set Pin_1__0__DR, CYREG_GPIO_PRT3_DR
.set Pin_1__0__DR_CLR, CYREG_GPIO_PRT3_DR_CLR
.set Pin_1__0__DR_INV, CYREG_GPIO_PRT3_DR_INV
.set Pin_1__0__DR_SET, CYREG_GPIO_PRT3_DR_SET
.set Pin_1__0__HSIOM, CYREG_HSIOM_PORT_SEL3
.set Pin_1__0__HSIOM_MASK, 0x0000000F
.set Pin_1__0__HSIOM_SHIFT, 0
.set Pin_1__0__INTCFG, CYREG_GPIO_PRT3_INTR_CFG
.set Pin_1__0__INTR, CYREG_GPIO_PRT3_INTR
.set Pin_1__0__INTR_CFG, CYREG_GPIO_PRT3_INTR_CFG
.set Pin_1__0__INTSTAT, CYREG_GPIO_PRT3_INTR
.set Pin_1__0__MASK, 0x01
.set Pin_1__0__PA__CFG0, CYREG_UDB_PA3_CFG0
.set Pin_1__0__PA__CFG1, CYREG_UDB_PA3_CFG1
.set Pin_1__0__PA__CFG10, CYREG_UDB_PA3_CFG10
.set Pin_1__0__PA__CFG11, CYREG_UDB_PA3_CFG11
.set Pin_1__0__PA__CFG12, CYREG_UDB_PA3_CFG12
.set Pin_1__0__PA__CFG13, CYREG_UDB_PA3_CFG13
.set Pin_1__0__PA__CFG14, CYREG_UDB_PA3_CFG14
.set Pin_1__0__PA__CFG2, CYREG_UDB_PA3_CFG2
.set Pin_1__0__PA__CFG3, CYREG_UDB_PA3_CFG3
.set Pin_1__0__PA__CFG4, CYREG_UDB_PA3_CFG4
.set Pin_1__0__PA__CFG5, CYREG_UDB_PA3_CFG5
.set Pin_1__0__PA__CFG6, CYREG_UDB_PA3_CFG6
.set Pin_1__0__PA__CFG7, CYREG_UDB_PA3_CFG7
.set Pin_1__0__PA__CFG8, CYREG_UDB_PA3_CFG8
.set Pin_1__0__PA__CFG9, CYREG_UDB_PA3_CFG9
.set Pin_1__0__PC, CYREG_GPIO_PRT3_PC
.set Pin_1__0__PC2, CYREG_GPIO_PRT3_PC2
.set Pin_1__0__PORT, 3
.set Pin_1__0__PS, CYREG_GPIO_PRT3_PS
.set Pin_1__0__SHIFT, 0
.set Pin_1__DR, CYREG_GPIO_PRT3_DR
.set Pin_1__DR_CLR, CYREG_GPIO_PRT3_DR_CLR
.set Pin_1__DR_INV, CYREG_GPIO_PRT3_DR_INV
.set Pin_1__DR_SET, CYREG_GPIO_PRT3_DR_SET
.set Pin_1__INTCFG, CYREG_GPIO_PRT3_INTR_CFG
.set Pin_1__INTR, CYREG_GPIO_PRT3_INTR
.set Pin_1__INTR_CFG, CYREG_GPIO_PRT3_INTR_CFG
.set Pin_1__INTSTAT, CYREG_GPIO_PRT3_INTR
.set Pin_1__MASK, 0x01
.set Pin_1__PA__CFG0, CYREG_UDB_PA3_CFG0
.set Pin_1__PA__CFG1, CYREG_UDB_PA3_CFG1
.set Pin_1__PA__CFG10, CYREG_UDB_PA3_CFG10
.set Pin_1__PA__CFG11, CYREG_UDB_PA3_CFG11
.set Pin_1__PA__CFG12, CYREG_UDB_PA3_CFG12
.set Pin_1__PA__CFG13, CYREG_UDB_PA3_CFG13
.set Pin_1__PA__CFG14, CYREG_UDB_PA3_CFG14
.set Pin_1__PA__CFG2, CYREG_UDB_PA3_CFG2
.set Pin_1__PA__CFG3, CYREG_UDB_PA3_CFG3
.set Pin_1__PA__CFG4, CYREG_UDB_PA3_CFG4
.set Pin_1__PA__CFG5, CYREG_UDB_PA3_CFG5
.set Pin_1__PA__CFG6, CYREG_UDB_PA3_CFG6
.set Pin_1__PA__CFG7, CYREG_UDB_PA3_CFG7
.set Pin_1__PA__CFG8, CYREG_UDB_PA3_CFG8
.set Pin_1__PA__CFG9, CYREG_UDB_PA3_CFG9
.set Pin_1__PC, CYREG_GPIO_PRT3_PC
.set Pin_1__PC2, CYREG_GPIO_PRT3_PC2
.set Pin_1__PORT, 3
.set Pin_1__PS, CYREG_GPIO_PRT3_PS
.set Pin_1__SHIFT, 0

/* UART_1_BUART */
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__0__MASK, 0x01
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__0__POS, 0
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__1__MASK, 0x02
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__1__POS, 1
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_AUX_CTL_REG, CYREG_UDB_W8_ACTL_03
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG, CYREG_UDB_W8_CTL_03
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_ST_REG, CYREG_UDB_CAT16_CTL_ST_03
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__COUNT_REG, CYREG_UDB_W8_CTL_03
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__COUNT_ST_REG, CYREG_UDB_CAT16_CTL_ST_03
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__MASK, 0x03
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__MASK_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_03
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__PER_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_03
.set UART_1_BUART_sCR_SyncCtl_CtrlReg__PERIOD_REG, CYREG_UDB_W8_MSK_03
.set UART_1_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG, CYREG_UDB_W16_ACTL_02
.set UART_1_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG, CYREG_UDB_W16_CTL_02
.set UART_1_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG, CYREG_UDB_W16_CTL_02
.set UART_1_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG, CYREG_UDB_W16_CTL_02
.set UART_1_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG, CYREG_UDB_W16_CTL_02
.set UART_1_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG, CYREG_UDB_W16_MSK_02
.set UART_1_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG, CYREG_UDB_W16_MSK_02
.set UART_1_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG, CYREG_UDB_W16_MSK_02
.set UART_1_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG, CYREG_UDB_W16_MSK_02
.set UART_1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG, CYREG_UDB_W8_ACTL_02
.set UART_1_BUART_sRX_RxBitCounter__CONTROL_REG, CYREG_UDB_W8_CTL_02
.set UART_1_BUART_sRX_RxBitCounter__CONTROL_ST_REG, CYREG_UDB_CAT16_CTL_ST_02
.set UART_1_BUART_sRX_RxBitCounter__COUNT_REG, CYREG_UDB_W8_CTL_02
.set UART_1_BUART_sRX_RxBitCounter__COUNT_ST_REG, CYREG_UDB_CAT16_CTL_ST_02
.set UART_1_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_02
.set UART_1_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_02
.set UART_1_BUART_sRX_RxBitCounter__PERIOD_REG, CYREG_UDB_W8_MSK_02
.set UART_1_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG, CYREG_UDB_W16_ACTL_02
.set UART_1_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG, CYREG_UDB_W16_ST_02
.set UART_1_BUART_sRX_RxBitCounter_ST__MASK_REG, CYREG_UDB_W8_MSK_02
.set UART_1_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_02
.set UART_1_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG, CYREG_UDB_CAT16_ACTL_MSK_02
.set UART_1_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG, CYREG_UDB_W8_ACTL_02
.set UART_1_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG, CYREG_UDB_CAT16_CTL_ST_02
.set UART_1_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG, CYREG_UDB_CAT16_CTL_ST_02
.set UART_1_BUART_sRX_RxBitCounter_ST__STATUS_REG, CYREG_UDB_W8_ST_02
.set UART_1_BUART_sRX_RxShifter_u0__16BIT_A0_REG, CYREG_UDB_W16_A0_00
.set UART_1_BUART_sRX_RxShifter_u0__16BIT_A1_REG, CYREG_UDB_W16_A1_00
.set UART_1_BUART_sRX_RxShifter_u0__16BIT_D0_REG, CYREG_UDB_W16_D0_00
.set UART_1_BUART_sRX_RxShifter_u0__16BIT_D1_REG, CYREG_UDB_W16_D1_00
.set UART_1_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG, CYREG_UDB_W16_ACTL_00
.set UART_1_BUART_sRX_RxShifter_u0__16BIT_F0_REG, CYREG_UDB_W16_F0_00
.set UART_1_BUART_sRX_RxShifter_u0__16BIT_F1_REG, CYREG_UDB_W16_F1_00
.set UART_1_BUART_sRX_RxShifter_u0__32BIT_A0_REG, CYREG_UDB_W32_A0_00
.set UART_1_BUART_sRX_RxShifter_u0__32BIT_A1_REG, CYREG_UDB_W32_A1_00
.set UART_1_BUART_sRX_RxShifter_u0__32BIT_D0_REG, CYREG_UDB_W32_D0_00
.set UART_1_BUART_sRX_RxShifter_u0__32BIT_D1_REG, CYREG_UDB_W32_D1_00
.set UART_1_BUART_sRX_RxShifter_u0__32BIT_DP_AUX_CTL_REG, CYREG_UDB_W32_ACTL_00
.set UART_1_BUART_sRX_RxShifter_u0__32BIT_F0_REG, CYREG_UDB_W32_F0_00
.set UART_1_BUART_sRX_RxShifter_u0__32BIT_F1_REG, CYREG_UDB_W32_F1_00
.set UART_1_BUART_sRX_RxShifter_u0__A0_A1_REG, CYREG_UDB_CAT16_A_00
.set UART_1_BUART_sRX_RxShifter_u0__A0_REG, CYREG_UDB_W8_A0_00
.set UART_1_BUART_sRX_RxShifter_u0__A1_REG, CYREG_UDB_W8_A1_00
.set UART_1_BUART_sRX_RxShifter_u0__D0_D1_REG, CYREG_UDB_CAT16_D_00
.set UART_1_BUART_sRX_RxShifter_u0__D0_REG, CYREG_UDB_W8_D0_00
.set UART_1_BUART_sRX_RxShifter_u0__D1_REG, CYREG_UDB_W8_D1_00
.set UART_1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG, CYREG_UDB_W8_ACTL_00
.set UART_1_BUART_sRX_RxShifter_u0__F0_F1_REG, CYREG_UDB_CAT16_F_00
.set UART_1_BUART_sRX_RxShifter_u0__F0_REG, CYREG_UDB_W8_F0_00
.set UART_1_BUART_sRX_RxShifter_u0__F1_REG, CYREG_UDB_W8_F1_00
.set UART_1_BUART_sRX_RxSts__0__MASK, 0x01
.set UART_1_BUART_sRX_RxSts__0__POS, 0
.set UART_1_BUART_sRX_RxSts__1__MASK, 0x02
.set UART_1_BUART_sRX_RxSts__1__POS, 1
.set UART_1_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG, CYREG_UDB_W16_ACTL_00
.set UART_1_BUART_sRX_RxSts__16BIT_STATUS_REG, CYREG_UDB_W16_ST_00
.set UART_1_BUART_sRX_RxSts__3__MASK, 0x08
.set UART_1_BUART_sRX_RxSts__3__POS, 3
.set UART_1_BUART_sRX_RxSts__32BIT_MASK_REG, CYREG_UDB_W32_MSK_00
.set UART_1_BUART_sRX_RxSts__32BIT_STATUS_AUX_CTL_REG, CYREG_UDB_W32_ACTL_00
.set UART_1_BUART_sRX_RxSts__32BIT_STATUS_REG, CYREG_UDB_W32_ST_00
.set UART_1_BUART_sRX_RxSts__4__MASK, 0x10
.set UART_1_BUART_sRX_RxSts__4__POS, 4
.set UART_1_BUART_sRX_RxSts__5__MASK, 0x20
.set UART_1_BUART_sRX_RxSts__5__POS, 5
.set UART_1_BUART_sRX_RxSts__MASK, 0x3B
.set UART_1_BUART_sRX_RxSts__MASK_REG, CYREG_UDB_W8_MSK_00
.set UART_1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG, CYREG_UDB_W8_ACTL_00
.set UART_1_BUART_sRX_RxSts__STATUS_REG, CYREG_UDB_W8_ST_00

/* UART_1_IntClock */
.set UART_1_IntClock__CTRL_REGISTER, CYREG_PERI_PCLK_CTL11
.set UART_1_IntClock__DIV_ID, 0x00000040
.set UART_1_IntClock__DIV_REGISTER, CYREG_PERI_DIV_16_CTL00
.set UART_1_IntClock__PA_DIV_ID, 0x000000FF

/* isr_UART_1 */
.set isr_UART_1__INTC_CLR_EN_REG, CYREG_CM0_ICER
.set isr_UART_1__INTC_CLR_PD_REG, CYREG_CM0_ICPR
.set isr_UART_1__INTC_MASK, 0x02
.set isr_UART_1__INTC_NUMBER, 1
.set isr_UART_1__INTC_PRIOR_MASK, 0xC000
.set isr_UART_1__INTC_PRIOR_NUM, 3
.set isr_UART_1__INTC_PRIOR_REG, CYREG_CM0_IPR0
.set isr_UART_1__INTC_SET_EN_REG, CYREG_CM0_ISER
.set isr_UART_1__INTC_SET_PD_REG, CYREG_CM0_ISPR

/* Miscellaneous */
.set CYDEV_BCLK__HFCLK__HZ, 48000000
.set CYDEV_BCLK__HFCLK__KHZ, 48000
.set CYDEV_BCLK__HFCLK__MHZ, 48
.set CYDEV_BCLK__SYSCLK__HZ, 48000000
.set CYDEV_BCLK__SYSCLK__KHZ, 48000
.set CYDEV_BCLK__SYSCLK__MHZ, 48
.set CYDEV_CHIP_DIE_LEOPARD, 1
.set CYDEV_CHIP_DIE_PANTHER, 6
.set CYDEV_CHIP_DIE_PSOC4A, 3
.set CYDEV_CHIP_DIE_PSOC5LP, 5
.set CYDEV_CHIP_DIE_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_PSOC3, 1
.set CYDEV_CHIP_FAMILY_PSOC4, 2
.set CYDEV_CHIP_FAMILY_PSOC5, 3
.set CYDEV_CHIP_FAMILY_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_USED, CYDEV_CHIP_FAMILY_PSOC4
.set CYDEV_CHIP_JTAG_ID, 0x0E34119E
.set CYDEV_CHIP_MEMBER_3A, 1
.set CYDEV_CHIP_MEMBER_4A, 3
.set CYDEV_CHIP_MEMBER_4D, 2
.set CYDEV_CHIP_MEMBER_4F, 4
.set CYDEV_CHIP_MEMBER_5A, 6
.set CYDEV_CHIP_MEMBER_5B, 5
.set CYDEV_CHIP_MEMBER_UNKNOWN, 0
.set CYDEV_CHIP_MEMBER_USED, CYDEV_CHIP_MEMBER_4F
.set CYDEV_CHIP_DIE_EXPECT, CYDEV_CHIP_MEMBER_USED
.set CYDEV_CHIP_DIE_ACTUAL, CYDEV_CHIP_DIE_EXPECT
.set CYDEV_CHIP_REV_LEOPARD_ES1, 0
.set CYDEV_CHIP_REV_LEOPARD_ES2, 1
.set CYDEV_CHIP_REV_LEOPARD_ES3, 3
.set CYDEV_CHIP_REV_LEOPARD_PRODUCTION, 3
.set CYDEV_CHIP_REV_PANTHER_ES0, 0
.set CYDEV_CHIP_REV_PANTHER_ES1, 1
.set CYDEV_CHIP_REV_PANTHER_PRODUCTION, 1
.set CYDEV_CHIP_REV_PSOC4A_ES0, 17
.set CYDEV_CHIP_REV_PSOC4A_PRODUCTION, 17
.set CYDEV_CHIP_REV_PSOC5LP_ES0, 0
.set CYDEV_CHIP_REV_PSOC5LP_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_3A_ES1, 0
.set CYDEV_CHIP_REVISION_3A_ES2, 1
.set CYDEV_CHIP_REVISION_3A_ES3, 3
.set CYDEV_CHIP_REVISION_3A_PRODUCTION, 3
.set CYDEV_CHIP_REVISION_4A_ES0, 17
.set CYDEV_CHIP_REVISION_4A_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4D_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_5A_ES0, 0
.set CYDEV_CHIP_REVISION_5A_ES1, 1
.set CYDEV_CHIP_REVISION_5A_PRODUCTION, 1
.set CYDEV_CHIP_REVISION_5B_ES0, 0
.set CYDEV_CHIP_REVISION_5B_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_USED, CYDEV_CHIP_REVISION_4F_PRODUCTION
.set CYDEV_CHIP_REV_EXPECT, CYDEV_CHIP_REVISION_USED
.set CYDEV_CONFIG_READ_ACCELERATOR, 1
.set CYDEV_CONFIG_UNUSED_IO_AllowButWarn, 0
.set CYDEV_CONFIG_UNUSED_IO, CYDEV_CONFIG_UNUSED_IO_AllowButWarn
.set CYDEV_CONFIG_UNUSED_IO_AllowWithInfo, 1
.set CYDEV_CONFIG_UNUSED_IO_Disallowed, 2
.set CYDEV_CONFIGURATION_COMPRESSED, 1
.set CYDEV_CONFIGURATION_MODE_COMPRESSED, 0
.set CYDEV_CONFIGURATION_MODE, CYDEV_CONFIGURATION_MODE_COMPRESSED
.set CYDEV_CONFIGURATION_MODE_DMA, 2
.set CYDEV_CONFIGURATION_MODE_UNCOMPRESSED, 1
.set CYDEV_DEBUG_PROTECT_KILL, 4
.set CYDEV_DEBUG_PROTECT_OPEN, 1
.set CYDEV_DEBUG_PROTECT, CYDEV_DEBUG_PROTECT_OPEN
.set CYDEV_DEBUG_PROTECT_PROTECTED, 2
.set CYDEV_DEBUGGING_DPS_Disable, 3
.set CYDEV_DEBUGGING_DPS_SWD, 2
.set CYDEV_DEBUGGING_DPS, CYDEV_DEBUGGING_DPS_SWD
.set CYDEV_DEBUGGING_ENABLE, 1
.set CYDEV_HEAP_SIZE, 0x80
.set CYDEV_PROJ_TYPE, 0
.set CYDEV_PROJ_TYPE_BOOTLOADER, 1
.set CYDEV_PROJ_TYPE_LOADABLE, 2
.set CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER, 3
.set CYDEV_PROJ_TYPE_STANDARD, 0
.set CYDEV_STACK_SIZE, 0x0800
.set CYDEV_USE_BUNDLED_CMSIS, 1
.set CYDEV_VARIABLE_VDDA, 1
.set CYDEV_VDDA_MV, 3300
.set CYDEV_VDDD_MV, 3300
.set CYDEV_VDDR_MV, 3300
.set CYIPBLOCK_m0s8bless_VERSION, 1
.set CYIPBLOCK_m0s8cpussv2_VERSION, 1
.set CYIPBLOCK_m0s8csd_VERSION, 1
.set CYIPBLOCK_m0s8ioss_VERSION, 1
.set CYIPBLOCK_m0s8lcd_VERSION, 2
.set CYIPBLOCK_m0s8lpcomp_VERSION, 2
.set CYIPBLOCK_m0s8peri_VERSION, 1
.set CYIPBLOCK_m0s8scb_VERSION, 2
.set CYIPBLOCK_m0s8srssv2_VERSION, 1
.set CYIPBLOCK_m0s8tcpwm_VERSION, 2
.set CYIPBLOCK_m0s8udbif_VERSION, 1
.set CYIPBLOCK_s8pass4al_VERSION, 1
.set CYDEV_BOOTLOADER_ENABLE, 0
.endif