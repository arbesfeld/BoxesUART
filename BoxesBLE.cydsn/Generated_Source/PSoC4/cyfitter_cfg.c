/*******************************************************************************
* FILENAME: cyfitter_cfg.c
* PSoC Creator  3.1 SP2
*
* Description:
* This file is automatically generated by PSoC Creator with device 
* initialization code.  Except for the user defined sections in
* CyClockStartupError(), this file should not be modified.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <string.h>
#include <cytypes.h>
#include <cydevice_trm.h>
#include <cyfitter.h>
#include <CyLib.h>
#include <cyfitter_cfg.h>


#if defined(__GNUC__) || defined(__ARMCC_VERSION)
    #define CYPACKED 
    #define CYPACKED_ATTR __attribute__ ((packed))
    #define CYALIGNED __attribute__ ((aligned))
    #define CY_CFG_UNUSED __attribute__ ((unused))
    #define CY_CFG_SECTION __attribute__ ((section(".psocinit")))
    
    #if defined(__ARMCC_VERSION)
        #define CY_CFG_MEMORY_BARRIER() __memory_changed()
    #else
        #define CY_CFG_MEMORY_BARRIER() __sync_synchronize()
    #endif
    
#elif defined(__ICCARM__)
    #include <intrinsics.h>

    #define CYPACKED __packed
    #define CYPACKED_ATTR 
    #define CYALIGNED _Pragma("data_alignment=4")
    #define CY_CFG_UNUSED _Pragma("diag_suppress=Pe177")
    #define CY_CFG_SECTION _Pragma("location=\".psocinit\"")
    
    #define CY_CFG_MEMORY_BARRIER() __DMB()
    
#else
    #error Unsupported toolchain
#endif


CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n);
CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n)
{
	(void)memset(s, 0, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}



/* Clock startup error codes                                                   */
#define CYCLOCKSTART_NO_ERROR    0u
#define CYCLOCKSTART_XTAL_ERROR  1u
#define CYCLOCKSTART_32KHZ_ERROR 2u
#define CYCLOCKSTART_PLL_ERROR   3u

#ifdef CY_NEED_CYCLOCKSTARTUPERROR
/*******************************************************************************
* Function Name: CyClockStartupError
********************************************************************************
* Summary:
*  If an error is encountered during clock configuration (crystal startup error,
*  PLL lock error, etc.), the system will end up here.  Unless reimplemented by
*  the customer, this function will stop in an infinite loop.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode);
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode)
{
    /* To remove the compiler warning if errorCode not used.                */
    errorCode = errorCode;

    /* `#START CyClockStartupError` */

    /* If we have a clock startup error (bad MHz crystal, PLL lock, etc.),  */
    /* we will end up here to allow the customer to implement something to  */
    /* deal with the clock condition.                                       */

    /* `#END` */

    /* If nothing else, stop here since the clocks have not started         */
    /* correctly.                                                           */
    while(1) {}
}
#endif

#define CY_CFG_BASE_ADDR_COUNT 9u
CYPACKED typedef struct
{
	uint8 offset;
	uint8 value;
} CYPACKED_ATTR cy_cfg_addrvalue_t;



/*******************************************************************************
* Function Name: cfg_write_bytes32
********************************************************************************
* Summary:
*  This function is used for setting up the chip configuration areas that
*  contain relatively sparse data.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
static void cfg_write_bytes32(const uint32 addr_table[], const cy_cfg_addrvalue_t data_table[]);
static void cfg_write_bytes32(const uint32 addr_table[], const cy_cfg_addrvalue_t data_table[])
{
	/* For 32-bit little-endian architectures */
	uint32 i, j = 0u;
	for (i = 0u; i < CY_CFG_BASE_ADDR_COUNT; i++)
	{
		uint32 baseAddr = addr_table[i];
		uint8 count = (uint8)baseAddr;
		baseAddr &= 0xFFFFFF00u;
		while (count != 0u)
		{
			CY_SET_XTND_REG8((void CYFAR *)(baseAddr + data_table[j].offset), data_table[j].value);
			j++;
			count--;
		}
	}
}

/*******************************************************************************
* Function Name: SetIMOBGTrims
********************************************************************************
*
* Summary:
*   Performs the configuration of the bandgap trim for the IMO based on the given
*   expected frequency of the IMO. 
*
* Parameters:
*   imoFreq: Frequency for operation of the IMO.
*
* Return:
*   void
*
*******************************************************************************/
static void SetIMOBGTrims(uint8 imoFreq);
CY_CFG_SECTION
static void SetIMOBGTrims(uint8 imoFreq)
{
	CYPACKED typedef struct {
		uint8 freq;
		uint8 absolute;
		uint8 tmpco;
	} CYPACKED_ATTR imo_trim_entry_t;

	CYPACKED typedef struct {
		imo_trim_entry_t entries[4];
	} CYPACKED_ATTR imo_trim_table_t;

	static const imo_trim_table_t *imo_trim_table = (const imo_trim_table_t *)CYREG_SFLASH_IMO_MAXF0;
	static const uint32 IMO_TRIM_FREQ_TABLE_ENTRIES = sizeof(imo_trim_table->entries)/sizeof(imo_trim_table->entries[0]);

	int32 imoTrimIndex;
	uint8 setAbs;
	uint8 setTmpCo;

	/* Traverse the SFLASH IMO frequency-dependent bandgap trim table to
	 * locate the appropriate value to trim the IMO bandgap based on freq. */
	setAbs = CY_GET_REG8((const void *)CYREG_SFLASH_IMO_ABS4);
	setTmpCo = CY_GET_REG8((const void *)CYREG_SFLASH_IMO_TMPCO4);
	for (imoTrimIndex = ((int32)IMO_TRIM_FREQ_TABLE_ENTRIES)-1;
	     (imoTrimIndex >= 0) && (imoFreq <= imo_trim_table->entries[imoTrimIndex].freq);
	     imoTrimIndex--)
	{
		setAbs = imo_trim_table->entries[imoTrimIndex].absolute;
		setTmpCo = imo_trim_table->entries[imoTrimIndex].tmpco;
	}

	CY_SET_REG32((void *)CYREG_PWR_BG_TRIM4, setAbs);
	CY_SET_REG32((void *)CYREG_PWR_BG_TRIM5, setTmpCo);
}



/*******************************************************************************
* Function Name: ClockSetup
********************************************************************************
*
* Summary:
*   Performs the initialization of all of the clocks in the device based on the
*   settings in the Clock tab of the DWR.  This includes enabling the requested
*   clocks and setting the necessary dividers to produce the desired frequency. 
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
static void ClockSetup(void);
CY_CFG_SECTION
static void ClockSetup(void)
{

	/* Set Flash Cycles based on max possible frequency in case a glitch occurs during ClockSetup(). */
	CY_SET_REG32((void CYXDATA *)(CYREG_CPUSS_FLASH_CTL), (0x0012u));
	/* Trim IMO BG based on desired frequency. */
	SetIMOBGTrims(48u);

	/* Going faster than 24MHz, so update trim value then adjust to new clock speed. */
	CY_SET_REG32((void CYXDATA *)(CYREG_CLK_IMO_TRIM1), (CY_GET_REG8((void *)CYREG_SFLASH_IMO_TRIM45)));
	CyDelayUs(5u);
	CY_SET_REG32((void CYXDATA *)(CYREG_CLK_IMO_TRIM2), (53u));

	/* Start the WCO */
	CySysClkWcoStart();
	CyDelay(500u); /* WCO may take up to 500ms to start */
	(void)CySysClkWcoSetPowerMode(CY_SYS_CLK_WCO_LPM);    /* Switch to the low power mode */
	/* CYDEV_CLK_ILO_CONFIG Starting address: CYDEV_CLK_ILO_CONFIG */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_CLK_ILO_CONFIG), 0x80000006u);

	/* CYDEV_WDT_CONFIG Starting address: CYDEV_WDT_CONFIG */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_WDT_CONFIG), 0x40000000u);


	CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLERD_BB_XO_CAPTRIM), 0x00003E2Du);
	/* Disable Crystal Stable Interrupt before enabling ECO */
	CY_SET_REG32((void*)CYREG_BLE_BLESS_LL_DSM_CTRL, CY_GET_REG32((void*)CYREG_BLE_BLESS_LL_DSM_CTRL) & (~(uint32)0x08u));
	/* Start the ECO and do not check status since it is not needed for HFCLK */
	(void)CySysClkEcoStart(2000u);
	CyDelayUs(1500u); /* Wait to stabalize */

	/* Setup phase aligned clocks */
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL00, 0x00003300u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF40u);

	/* CYDEV_CLK_IMO_CONFIG Starting address: CYDEV_CLK_IMO_CONFIG */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_CLK_IMO_CONFIG), 0x80000000u);

	/* CYDEV_CLK_SELECT Starting address: CYDEV_CLK_SELECT */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_CLK_SELECT), 0x00040000u);

	/* CYDEV_PERI_PCLK_CTL11 Starting address: CYDEV_PERI_PCLK_CTL11 */
	CY_SET_XTND_REG32((void CYFAR *)(CYREG_PERI_PCLK_CTL11), 0x00000040u);

}


/* Analog API Functions */


/*******************************************************************************
* Function Name: AnalogSetDefault
********************************************************************************
*
* Summary:
*  Sets up the analog portions of the chip to default values based on chip
*  configuration options from the project.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void AnalogSetDefault(void);
static void AnalogSetDefault(void)
{
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTBM0_DFT_CTRL, 0x00000003u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTBM1_DFT_CTRL, 0x00000003u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_PASS_DSAB_DSAB_CTRL, 0x00000000u);
}

#define CY_AMUX_UNUSED CYREG_CM0_ROM_DWT


/*******************************************************************************
* Function Name: cyfitter_cfg
********************************************************************************
* Summary:
*  This function is called by the start-up code for the selected device. It
*  performs all of the necessary device configuration based on the design
*  settings.  This includes settings from the Design Wide Resources (DWR) such
*  as Clocks and Pins as well as any component configuration that is necessary.
*
* Parameters:  
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_SECTION
void cyfitter_cfg(void)
{
	/* Disable interrupts by default. Let user enable if/when they want. */
	CyGlobalIntDisable;

	CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLESS_LL_DSM_CTRL), 0x00000000u);

	/* Enable the clock in the interrupt controller for the routed interrupts */
	CY_SET_REG8((void *)CYREG_UDB_UDBIF_INT_CLK_CTL, 0x01u);
	{
		static const uint32 CYCODE cy_cfg_addr_table[] = {
			0x400F0002u, /* Base address: 0x400F0000 Count: 2 */
			0x400F3023u, /* Base address: 0x400F3000 Count: 35 */
			0x400F313Fu, /* Base address: 0x400F3100 Count: 63 */
			0x400F325Du, /* Base address: 0x400F3200 Count: 93 */
			0x400F334Fu, /* Base address: 0x400F3300 Count: 79 */
			0x400F4002u, /* Base address: 0x400F4000 Count: 2 */
			0x400F4103u, /* Base address: 0x400F4100 Count: 3 */
			0x400F4304u, /* Base address: 0x400F4300 Count: 4 */
			0x400F6002u, /* Base address: 0x400F6000 Count: 2 */
		};

		static const cy_cfg_addrvalue_t CYCODE cy_cfg_data_table[] = {
			{0x80u, 0x3Bu},
			{0x82u, 0x72u},
			{0x80u, 0x08u},
			{0x81u, 0x03u},
			{0x84u, 0x0Bu},
			{0x85u, 0xF0u},
			{0x88u, 0x0Bu},
			{0x8Bu, 0x03u},
			{0x8Du, 0x80u},
			{0x90u, 0x04u},
			{0x92u, 0x08u},
			{0x93u, 0x03u},
			{0x97u, 0x03u},
			{0x98u, 0x01u},
			{0x99u, 0x23u},
			{0x9Au, 0x02u},
			{0x9Bu, 0x58u},
			{0x9Cu, 0x02u},
			{0x9Du, 0x03u},
			{0x9Eu, 0x01u},
			{0xA1u, 0x42u},
			{0xA3u, 0x24u},
			{0xA9u, 0xF0u},
			{0xAAu, 0x04u},
			{0xADu, 0x11u},
			{0xAFu, 0x24u},
			{0xB1u, 0x0Cu},
			{0xB3u, 0x80u},
			{0xB4u, 0x0Cu},
			{0xB5u, 0x70u},
			{0xB6u, 0x03u},
			{0xB7u, 0x03u},
			{0xBEu, 0x10u},
			{0xBFu, 0x01u},
			{0xD8u, 0x04u},
			{0xD9u, 0x04u},
			{0xDFu, 0x01u},
			{0x00u, 0x90u},
			{0x02u, 0x10u},
			{0x04u, 0x2Au},
			{0x06u, 0x80u},
			{0x0Au, 0x10u},
			{0x0Bu, 0x80u},
			{0x0Cu, 0x01u},
			{0x0Eu, 0x4Au},
			{0x10u, 0x21u},
			{0x12u, 0x40u},
			{0x13u, 0x01u},
			{0x17u, 0x10u},
			{0x18u, 0x14u},
			{0x1Au, 0x01u},
			{0x1Bu, 0x01u},
			{0x1Eu, 0x06u},
			{0x1Fu, 0x80u},
			{0x20u, 0x02u},
			{0x21u, 0x10u},
			{0x23u, 0xA1u},
			{0x24u, 0x40u},
			{0x26u, 0x18u},
			{0x27u, 0x11u},
			{0x28u, 0x01u},
			{0x29u, 0x21u},
			{0x2Fu, 0x89u},
			{0x31u, 0x08u},
			{0x32u, 0x80u},
			{0x33u, 0x50u},
			{0x34u, 0x10u},
			{0x35u, 0x01u},
			{0x36u, 0x98u},
			{0x39u, 0x28u},
			{0x3Bu, 0x01u},
			{0x3Du, 0x08u},
			{0x3Eu, 0x80u},
			{0x3Fu, 0x21u},
			{0x40u, 0x40u},
			{0x42u, 0x14u},
			{0x43u, 0x40u},
			{0x48u, 0x21u},
			{0x4Au, 0x40u},
			{0x51u, 0x04u},
			{0x52u, 0x10u},
			{0x53u, 0x40u},
			{0x5Bu, 0xA1u},
			{0x5Cu, 0x02u},
			{0x5Eu, 0x01u},
			{0x60u, 0x06u},
			{0x63u, 0x40u},
			{0x7Bu, 0x01u},
			{0x87u, 0x40u},
			{0xC0u, 0x77u},
			{0xC2u, 0xDCu},
			{0xC4u, 0x45u},
			{0xCAu, 0xBDu},
			{0xCCu, 0xFEu},
			{0xCEu, 0xF7u},
			{0xD0u, 0x0Fu},
			{0xD2u, 0x08u},
			{0xD6u, 0x0Du},
			{0xD8u, 0x0Du},
			{0xDEu, 0x08u},
			{0x00u, 0x79u},
			{0x01u, 0xE7u},
			{0x02u, 0x02u},
			{0x03u, 0x18u},
			{0x05u, 0x20u},
			{0x06u, 0x1Eu},
			{0x09u, 0xECu},
			{0x0Au, 0x01u},
			{0x0Bu, 0x13u},
			{0x0Cu, 0x44u},
			{0x0Du, 0x03u},
			{0x0Fu, 0x1Cu},
			{0x10u, 0x01u},
			{0x11u, 0xFBu},
			{0x12u, 0x06u},
			{0x13u, 0x04u},
			{0x14u, 0x65u},
			{0x15u, 0x01u},
			{0x16u, 0x12u},
			{0x18u, 0x01u},
			{0x1Au, 0x80u},
			{0x1Bu, 0x1Fu},
			{0x1Cu, 0x67u},
			{0x1Du, 0x8Fu},
			{0x1Eu, 0x08u},
			{0x1Fu, 0x70u},
			{0x20u, 0x19u},
			{0x21u, 0x02u},
			{0x22u, 0x66u},
			{0x24u, 0x24u},
			{0x25u, 0x03u},
			{0x28u, 0x64u},
			{0x29u, 0x60u},
			{0x2Cu, 0x04u},
			{0x2Du, 0x40u},
			{0x32u, 0x7Fu},
			{0x34u, 0x80u},
			{0x35u, 0x80u},
			{0x37u, 0x7Fu},
			{0x3Bu, 0x80u},
			{0x3Eu, 0x04u},
			{0x3Fu, 0x10u},
			{0x56u, 0x02u},
			{0x57u, 0x11u},
			{0x58u, 0x04u},
			{0x59u, 0x04u},
			{0x5Bu, 0x04u},
			{0x5Fu, 0x01u},
			{0x80u, 0x02u},
			{0x83u, 0x3Fu},
			{0x85u, 0x11u},
			{0x86u, 0x9Bu},
			{0x88u, 0xE3u},
			{0x89u, 0x07u},
			{0x8Au, 0x10u},
			{0x8Cu, 0x42u},
			{0x8Du, 0x12u},
			{0x90u, 0x80u},
			{0x91u, 0x77u},
			{0x92u, 0x0Bu},
			{0x93u, 0x80u},
			{0x94u, 0x63u},
			{0x95u, 0x13u},
			{0x9Au, 0x04u},
			{0x9Bu, 0x3Fu},
			{0x9Cu, 0x63u},
			{0x9Du, 0xE8u},
			{0x9Eu, 0x98u},
			{0x9Fu, 0x13u},
			{0xA0u, 0x98u},
			{0xA1u, 0x12u},
			{0xA2u, 0x63u},
			{0xA4u, 0x21u},
			{0xA7u, 0x24u},
			{0xA8u, 0x03u},
			{0xA9u, 0x7Fu},
			{0xABu, 0x80u},
			{0xACu, 0xF8u},
			{0xADu, 0xC8u},
			{0xAFu, 0x17u},
			{0xB0u, 0x78u},
			{0xB1u, 0x80u},
			{0xB2u, 0xE0u},
			{0xB3u, 0x7Fu},
			{0xB4u, 0x07u},
			{0xB9u, 0x02u},
			{0xBAu, 0x22u},
			{0xBFu, 0x04u},
			{0xD2u, 0x03u},
			{0xD8u, 0x04u},
			{0xD9u, 0x04u},
			{0xDBu, 0x04u},
			{0xDFu, 0x01u},
			{0x01u, 0x20u},
			{0x02u, 0x01u},
			{0x03u, 0x50u},
			{0x05u, 0x10u},
			{0x06u, 0x41u},
			{0x07u, 0x10u},
			{0x08u, 0x44u},
			{0x0Au, 0x40u},
			{0x0Bu, 0x08u},
			{0x0Cu, 0x40u},
			{0x0Eu, 0x48u},
			{0x0Fu, 0x22u},
			{0x10u, 0x21u},
			{0x11u, 0x10u},
			{0x12u, 0x80u},
			{0x17u, 0x65u},
			{0x19u, 0x21u},
			{0x1Au, 0x10u},
			{0x1Bu, 0x11u},
			{0x1Du, 0x10u},
			{0x1Fu, 0x04u},
			{0x20u, 0x80u},
			{0x21u, 0x08u},
			{0x26u, 0x90u},
			{0x27u, 0x01u},
			{0x28u, 0x01u},
			{0x29u, 0x20u},
			{0x2Au, 0x49u},
			{0x2Cu, 0x14u},
			{0x2Du, 0x80u},
			{0x2Fu, 0x80u},
			{0x30u, 0x04u},
			{0x31u, 0x05u},
			{0x32u, 0x80u},
			{0x33u, 0x10u},
			{0x35u, 0x01u},
			{0x36u, 0x84u},
			{0x37u, 0x10u},
			{0x38u, 0x80u},
			{0x39u, 0x16u},
			{0x3Au, 0x04u},
			{0x3Du, 0x04u},
			{0x3Eu, 0x40u},
			{0x3Fu, 0x21u},
			{0x41u, 0x01u},
			{0x42u, 0x40u},
			{0x5Eu, 0x20u},
			{0x69u, 0x10u},
			{0x6Au, 0x40u},
			{0x6Cu, 0x55u},
			{0x6Du, 0x08u},
			{0x6Fu, 0x48u},
			{0x74u, 0x20u},
			{0x75u, 0x84u},
			{0x76u, 0x05u},
			{0x77u, 0x24u},
			{0x8Eu, 0x04u},
			{0x8Fu, 0x01u},
			{0x93u, 0x01u},
			{0x94u, 0x2Au},
			{0x96u, 0x50u},
			{0x97u, 0x02u},
			{0x98u, 0x10u},
			{0x9Au, 0x48u},
			{0x9Bu, 0x10u},
			{0x9Du, 0x21u},
			{0xA3u, 0x80u},
			{0xA4u, 0x40u},
			{0xA5u, 0x0Cu},
			{0xA6u, 0x84u},
			{0xA7u, 0x18u},
			{0xAEu, 0x48u},
			{0xC0u, 0xFFu},
			{0xC2u, 0xFFu},
			{0xC4u, 0xFFu},
			{0xCAu, 0xFFu},
			{0xCCu, 0xFFu},
			{0xCEu, 0xFFu},
			{0xD6u, 0x20u},
			{0x86u, 0x40u},
			{0xE6u, 0x40u},
			{0x6Eu, 0x80u},
			{0xA2u, 0x40u},
			{0xDAu, 0x80u},
			{0x01u, 0x08u},
			{0x8Du, 0x08u},
			{0xC0u, 0x08u},
			{0xE2u, 0x02u},
			{0x10u, 0x01u},
			{0x11u, 0x01u},
		};



		CYPACKED typedef struct {
			void CYFAR *address;
			uint16 size;
		} CYPACKED_ATTR cfg_memset_t;


		CYPACKED typedef struct {
			void CYFAR *dest;
			const void CYCODE *src;
			uint16 size;
		} CYPACKED_ATTR cfg_memcpy_t;

		static const cfg_memset_t CYCODE cfg_memset_list [] = {
			/* address, size */
			{(void CYFAR *)(CYDEV_UDB_P0_U1_BASE), 896u},
			{(void CYFAR *)(CYDEV_UDB_DSI0_BASE), 1024u},
		};

		/* UDB_0_1_0_CONFIG Address: CYDEV_UDB_P0_U0_BASE Size (bytes): 128 */
		static const uint8 CYCODE BS_UDB_0_1_0_CONFIG_VAL[] = {
			0x00u, 0x38u, 0x00u, 0x43u, 0x20u, 0x18u, 0x00u, 0xC0u, 0x08u, 0x00u, 0x04u, 0x04u, 0x00u, 0x00u, 0x10u, 0x00u, 
			0x00u, 0x00u, 0x10u, 0x00u, 0x00u, 0x07u, 0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x72u, 0x00u, 0x39u, 0x00u, 0x40u, 
			0x00u, 0x5Bu, 0x00u, 0x20u, 0x00u, 0x00u, 0x02u, 0x00u, 0x00u, 0x2Bu, 0x00u, 0x40u, 0x14u, 0x00u, 0x29u, 0xFBu, 
			0x0Cu, 0x40u, 0x01u, 0x80u, 0x30u, 0x07u, 0x02u, 0x78u, 0x00u, 0x00u, 0x00u, 0x80u, 0x00u, 0x00u, 0x51u, 0x05u, 
			0x12u, 0x05u, 0x03u, 0x00u, 0x04u, 0xBCu, 0xFEu, 0x0Du, 0x1Fu, 0xFFu, 0xFFu, 0xFFu, 0x62u, 0xA0u, 0xF0u, 0x41u, 
			0x0Cu, 0x00u, 0x00u, 0x00u, 0x1Bu, 0x00u, 0x04u, 0x00u, 0x04u, 0x04u, 0x04u, 0x04u, 0x00u, 0x00u, 0x00u, 0x05u, 
			0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x40u, 0x02u, 0x00u, 0x10u, 0x30u, 0x10u, 0x00u, 0x10u, 0x10u, 0x12u, 
			0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u};

		static const cfg_memcpy_t CYCODE cfg_memcpy_list [] = {
			/* dest, src, size */
			{(void CYFAR *)(CYDEV_UDB_P0_U0_BASE), BS_UDB_0_1_0_CONFIG_VAL, 128u},
		};

		uint8 CYDATA i;

		/* Zero out critical memory blocks before beginning configuration */
		for (i = 0u; i < (sizeof(cfg_memset_list)/sizeof(cfg_memset_list[0])); i++)
		{
			const cfg_memset_t CYCODE * CYDATA ms = &cfg_memset_list[i];
			CYMEMZERO(ms->address, (size_t)(uint32)(ms->size));
		}

		/* Copy device configuration data into registers */
		for (i = 0u; i < (sizeof(cfg_memcpy_list)/sizeof(cfg_memcpy_list[0])); i++)
		{
			const cfg_memcpy_t CYCODE * CYDATA mc = &cfg_memcpy_list[i];
			void * CYDATA destPtr = mc->dest;
			const void CYCODE * CYDATA srcPtr = mc->src;
			uint16 CYDATA numBytes = mc->size;
			CYCONFIGCPYCODE(destPtr, srcPtr, numBytes);
		}

		cfg_write_bytes32(cy_cfg_addr_table, cy_cfg_data_table);

		/* Perform normal device configuration. Order is not critical for these items. */
		CY_SET_XTND_REG16((void CYFAR *)(CYREG_UDB_BCTL0_DRV), 0x0100u);
		CY_SET_XTND_REG8((void CYFAR *)(CYREG_UDB_BCTL0_DRV + 0x2u), 0x01u);

		/* HSIOM Starting address: CYDEV_HSIOM_BASE */
		CY_SET_XTND_REG32((void CYFAR *)(CYDEV_HSIOM_BASE), 0xEE000000u);

		/* IOPINS0_0 Starting address: CYDEV_GPIO_PRT0_DR */
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_GPIO_PRT0_PC), 0x00D80000u);

		/* IOPINS0_2 Starting address: CYDEV_GPIO_PRT2_DR */
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_GPIO_PRT2_PC), 0x00180000u);

		/* IOPINS0_3 Starting address: CYDEV_GPIO_PRT3_DR */
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_GPIO_PRT3_PC), 0x00000001u);

		/* UDB_PA_0 Starting address: CYDEV_UDB_PA0_BASE */
		CY_SET_XTND_REG32((void CYFAR *)(CYDEV_UDB_PA0_BASE), 0x00990000u);

		/* UDB_PA_2 Starting address: CYDEV_UDB_PA2_BASE */
		CY_SET_XTND_REG32((void CYFAR *)(CYDEV_UDB_PA2_BASE), 0x00990000u);

		/* UDB_PA_3 Starting address: CYDEV_UDB_PA3_BASE */
		CY_SET_XTND_REG32((void CYFAR *)(CYDEV_UDB_PA3_BASE), 0x00990004u);
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_UDB_PA3_CFG4), 0x00020000u);

		/* INT_SELECT Starting address: CYDEV_CPUSS_INT_SEL */
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_CPUSS_INT_SEL), 0x00000002u);

		/* INT_CONFIG Starting address: CYDEV_UDB_INT_CFG */
		CY_SET_XTND_REG32((void CYFAR *)(CYREG_UDB_INT_CFG), 0x00000002u);

		/* Enable digital routing */
		CY_SET_XTND_REG8((void *)CYREG_UDB_UDBIF_BANK_CTL, CY_GET_XTND_REG8((void *)CYREG_UDB_UDBIF_BANK_CTL) | 0x02u);

		/* Enable UDB array */
		CY_SET_XTND_REG8((void *)CYREG_UDB_UDBIF_WAIT_CFG, (uint8)((CY_GET_XTND_REG8((void *)CYREG_UDB_UDBIF_WAIT_CFG) & 0xC3u) | 0x14u));
		CY_SET_XTND_REG8((void *)CYREG_UDB_UDBIF_BANK_CTL, (uint8)(CY_GET_XTND_REG8((void *)CYREG_UDB_UDBIF_BANK_CTL) | 0x16u));
	}

	/* Setup clocks based on selections from Clock DWR */
	ClockSetup();

	/* Perform basic analog initialization to defaults */
	AnalogSetDefault();

}
