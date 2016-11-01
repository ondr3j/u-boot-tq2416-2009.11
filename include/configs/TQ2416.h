/*
 * (C) Copyright 2010-2016
 * <www.embedsky.com>
 *
 * Configuation settings for the EmbedSky TQ2416 board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define EMBEDSKY_ADD					1
#define EMBEDSKY_DELETE					1
#define EMBEDSKY_MODIFY					1
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_EMBEDSKY_MENU
#define CONFIG_EmbedSky_LCD
#define CONFIG_DEBUG_MSG 

#ifdef CONFIG_EmbedSky_LCD
#define CONFIG_LCD_TYPE					X480Y272
#else
#undef CONFIG_LCD_TYPE
#endif /* CONFIG_EmbedSky_LCD */

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_S3C2416					1		/* in a SAMSUNG S3C2416 SoC     */
#define CONFIG_S3C24XX					1		/* in a SAMSUNG S3C24XX Family  */
#define CONFIG_TQ2416					1		/* on a EmbedSky TQ2416 Board  */
#define CONFIG_EMBEDSKY_FAT				1
#define CONFIG_OEM_SDREAD				1
#define CONFIG_GENERIC_MMC				1
//#define CONFIG_S3C_HSMMC				1
#define MEMORY_BASE_ADDRESS				0x30000000

/* input clock of PLL */
#define CONFIG_SYS_CLK_FREQ				12000000	/* the TQ2416 has 12MHz input clock */

#if 1
#define CONFIG_CMD_MENU
#else
#undef CONFIG_CMD_MENU
#endif


#define CONFIG_ENABLE_MMU
//#undef  CONFIG_ENABLE_MMU
#ifdef CONFIG_ENABLE_MMU
#define CONFIG_BUILD_MMU_TABLE_RUNTIME	1
#ifdef CONFIG_BUILD_MMU_TABLE_RUNTIME
//#define MMU_TABLE_BASE				(CONFIG_PHY_UBOOT_BASE + 0xa0000 - 0x4000)
#define MMU_TABLE_BASE					(CONFIG_PHY_UBOOT_BASE + 0xb0000 - 0x4000)
#define MMU_IO_AREA_START				(0x00000000)
#define MMU_RESERVED1_START				(0x60000000)
#define MMU_MEM_AREA_START				(0xc0000000)
#define MMU_RESERVED2_START				(0xc4000000)
#endif /* CONFIG_BUILD_MMU_TABLE_RUNTIME */
#define virt_to_phys(x)					virt_to_phy_tq2416(x)
#else /* CONFIG_ENABLE_MMU */
#define virt_to_phys(x)					(x)
#endif /* CONFIG_ENABLE_MMU */
#define CONFIG_SYS_PROMPT_HUSH_PS2		"> "
#define CONFIG_SYS_HUSH_PARSER 			1
#define CONFIG_MEMORY_UPPER_CODE

#undef CONFIG_USE_IRQ				/* we don't need IRQ/FIQ stuff */

#define CONFIG_INCLUDE_TEST

#define CONFIG_ZIMAGE_BOOT
#define CONFIG_IMAGE_BOOT 

#define BOARD_LATE_INIT

#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_CMDLINE_TAG
#define CONFIG_INITRD_TAG

/*
 * Architecture magic and machine type
 */
#define MACH_TYPE						1685
#define UBOOT_MAGIC						(0x43090000 | MACH_TYPE)

/* Power Management is enabled */
#define CONFIG_PM

#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#undef CONFIG_SKIP_RELOCATE_UBOOT
#undef CONFIG_USE_NOR_BOOT

/*
 * Size of malloc() pool
 */
#if 1
#define CONFIG_MALLOC_LEN				(2*1024*1024)	//2M
#else
#define CONFIG_MALLOC_LEN				(CONFIG_ENV_SIZE + 1024*1024)
#endif
#define CONFIG_SYS_MALLOC_LEN			CONFIG_MALLOC_LEN

#define CONFIG_GBL_DATA_SIZE			128//	/* size in bytes reserved for initial data */

#define CONFIG_STACK_SIZE				0x80000	/* 256k */


/*
 * select serial console configuration
 */
#define CONFIG_SERIAL1					1	/* we use SERIAL 1 on TQ2416 */

#define CONFIG_HUSH_PARSER				/* use "hush" command parser	*/
#ifdef CONFIG_HUSH_PARSER
#define CONFIG_PROMPT_HUSH_PS2			"> "
#endif

#define CONFIG_CMDLINE_EDITING

#undef CONFIG_S3C24XX_I2C		/* this board has H/W I2C */
#ifdef CONFIG_S3C24XX_I2C
#define CONFIG_HARD_I2C					1
#define CONFIG_I2C_SPEED				50000
#define CONFIG_I2C_SLAVE				0xFE
#endif

#define CONFIG_DOS_PARTITION
#define CONFIG_SUPPORT_VFAT

#define CONFIG_USB_OHCI
#define CONFIG_USB_STORAGE
#define CONFIG_S3C_USBD

#define USBD_DOWN_ADDR					0xc0000000

/************************************************************
 * RTC
 ************************************************************/
#define CONFIG_RTC_S3C24XX				1

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE					115200

/***********************************************************
 * Command definition
 ***********************************************************/
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_USB
#define CONFIG_CMD_REGINFO
#ifndef EMBEDSKY_DELETE
#define CONFIG_CMD_NAND
#endif
#define CONFIG_CMD_MOVINAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_DATE
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_NET
#define CONFIG_COMMANDS					1 
#define CONFIG_CMD_NAND					1
#define CONFIG_CMD_FAT
#define CONFIG_CMD_MMC

#if 1

//#define CONFIG_JFFS2_NAND
//#define CONFIG_CMD_JFFS2

#define MTDIDS_DEFAULT					"nand0=nandflash0"
#if 1
#define MTDPARTS_DEFAULT				"mtdparts=nandflash0:512k@0(bios)," \
										"512k(params)," \
										/*"256k(toc),"*/ \
										/*"384k(eboot),"*/ \
										"2048K(logo)," \
										"4m(kernel)," \
										"-(root)"

#else
#define MTDPARTS_DEFAULT				"mtdparts=nandflash0:512k@0(bios)," \
										"256k(params)," \
										/*"256k(toc),"*/ \
										/*"384k(eboot),"*/ \
										"2304k(logo)," \
										"4m(kernel)," \
										"-(root)"
	
#endif
#if 1
#define CONFIG_BOOTARGS					"noinitrd root=/dev/mtdblock3 rootfstype=yaffs2 init=/linuxrc console=ttySAC0"
#else
#define CONFIG_BOOTARGS					"noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/linuxrc console=ttySAC0"
#endif
#if 1 //Added support of UBI filesystem
#define CONFIG_MTD_PARTITIONS
#define CONFIG_RBTREE
#define CONFIG_LZO
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#endif
#endif


#include <config_cmd_default.h>

#define CONFIG_CMD_ELF
#define CONFIG_CMD_DHCP
//#define CONFIG_CMD_I2C

#define CONFIG_BOOTDELAY				1
#define CONFIG_ETHADDR					10:23:45:67:89:ab
#define CONFIG_NETMASK					255.255.255.0
#define CONFIG_IPADDR					192.168.1.6
#define CONFIG_SERVERIP					192.168.1.8
#define CONFIG_GATEWAYIP				192.168.1.2

#define CONFIG_ZERO_BOOTDELAY_CHECK

#define CONFIG_NET_MULTI
#define CONFIG_DRIVER_DM9000			1
//#define CONFIG_DM9000_NO_SROM
//#define CONFIG_DM9000_BASE			0x08000300
#define CONFIG_DM9000_BASE				0x20000300
#define DM9000_IO						CONFIG_DM9000_BASE
#define DM9000_DATA						(CONFIG_DM9000_BASE + 8)
#define CONFIG_DM9000_USE_16BIT

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE			115200		/* speed to run kgdb serial port */
/* what's this ? it's not used anywhere */
#define CONFIG_KGDB_SER_INDEX			1		/* which serial port to use */
#endif

/*
 * Miscellaneous configurable options
 */
#define CONFIG_LONGHELP				/* undef to save memory		*/
#define CONFIG_PROMPT					"TQ2416 # "	/* Monitor Command Prompt	*/
#define CONFIG_SYS_PROMPT				"TQ2416 # "	/* Monitor Command Prompt	*/
#define CONFIG_CBSIZE					256		/* Console I/O Buffer Size	*/
#define CONFIG_SYS_CBSIZE				256		/* Console I/O Buffer Size	*/
#define CONFIG_SYS_CBSIZE				256		/* Console I/O Buffer Size	*/
#define CONFIG_PBSIZE					384		/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE				384		/* Print Buffer Size */
#define CONFIG_MAXARGS					16		/* max number of command args	*/
#define CONFIG_SYS_MAXARGS				16		/* max number of command args	*/
#define CONFIG_BARGSIZE					CONFIG_CBSIZE	/* Boot Argument Buffer Size	*/
#define CONFIG_SYS_BARGSIZE				CONFIG_CBSIZE	/* Boot Argument Buffer Size	*/
#define CONFIG_MEMTEST_START			MEMORY_BASE_ADDRESS	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_START		MEMORY_BASE_ADDRESS	/* memtest works on	*/
#define CONFIG_MEMTEST_END				(MEMORY_BASE_ADDRESS + 0x3E00000)
#define CONFIG_SYS_MEMTEST_END			(MEMORY_BASE_ADDRESS + 0x3E00000)	/* 62 MB in DRAM	*/

#undef  CONFIG_CLKS_IN_HZ						/* everything, incl board info, in Hz */

#define CONFIG_LOAD_ADDR				MEMORY_BASE_ADDRESS	/* default load address	*/
#define CONFIG_SYS_LOAD_ADDR			MEMORY_BASE_ADDRESS	/* default load address	*/
/* the PWM TImer 4 uses a counter of 15625 for 10 ms, so we need */
/* it to wrap 100 times (total 1562500) to get 1 sec. */
#define CONFIG_HZ						1562500
#define CONFIG_SYS_HZ					1000

/* valid baudrates */
#define CONFIG_BAUDRATE_TABLE			{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_SYS_BAUDRATE_TABLE		{ 9600, 19200, 38400, 57600, 115200 }
/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE				0x80000		/* regular stack 256KB */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ			(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ			(4*1024)	/* FIQ stack */
#endif

/*-----------------------------------------------------------------------
 * Clock Configuration
 */

//#define CONFIG_CLK_534_133_66
#define CONFIG_CLK_400_133_66
//#define CONFIG_CLK_267_133_66

/* 
MSYSCLK = MPLL = (Startup_MDIV*Fin)/(Startup_PDIV*(2<<Startup_SDIV))
HCLK = MSYSCLK/HCLK_Ratio = MSYSCLK/((PREDIV+1)*(HCLKDIV+1))
ARMCLK = MSYSCLK/ARMCLK_Ratio = MSYSCLK/((ARMDIV[12]+1)*(ARMDIV[11:9]+1))
 */
#if defined(CONFIG_CLK_400_133_66)/* Output CLK 800MHz 2:4:8*/
#define ARMCLKVAL						400
#define HCLKVAL							133
#define PCLKVAL							66
#define Startup_MDIV					400
#define Startup_PDIV					3
#define Startup_SDIV					1
#define Startup_MPLLSTOP				0
#define Startup_EMDIV					32
#define Startup_EPDIV					1
#define Startup_ESDIV					2
#define Startup_EPLLSTOP				0
#define Startup_ARMCLKdiv				1
#define Startup_PREdiv					0x2
#define Startup_HCLKdiv					0x1
#define Startup_PCLKdiv					1
#define Startup_SSMCdiv					1
#elif defined (CONFIG_CLK_534_133_66)
#define ARMCLKVAL						534
#define HCLKVAL							133
#define PCLKVAL							66
#define Startup_MDIV					267
#define Startup_PDIV					3
#define Startup_SDIV					1
#define Startup_MPLLSTOP				0
#define Startup_EMDIV					32
#define Startup_EPDIV					1
#define Startup_ESDIV					2
#define Startup_EPLLSTOP				0
#define Startup_ARMCLKdiv				0
#define Startup_PREdiv					0x1
#define Startup_HCLKdiv					0x1
#define Startup_PCLKdiv					1
#define Startup_SSMCdiv					1
#elif defined (CONFIG_CLK_267_133_66)
#define ARMCLKVAL						267
#define HCLKVAL							133
#define PCLKVAL							66
#define Startup_MDIV					267
#define Startup_PDIV					3
#define Startup_SDIV					1
#define Startup_MPLLSTOP				0
#define Startup_EMDIV					32
#define Startup_EPDIV					1
#define Startup_ESDIV					2
#define Startup_EPLLSTOP				0
#define Startup_ARMCLKdiv				1
#define Startup_PREdiv					0x1
#define Startup_HCLKdiv					0x1
#define Startup_PCLKdiv					1
#define Startup_SSMCdiv					1
#else
# error Must define CONFIG_CLK_534_133_66 or CONFIG_CLK_400_133_66
#endif

#define CLK_DIV_VAL						((Startup_ARMCLKdiv<<9)|(Startup_PREdiv<<4)|(Startup_SSMCdiv<<3)|(Startup_PCLKdiv<<2)|(Startup_HCLKdiv))
#define MPLL_VAL						((Startup_MPLLSTOP<<24)|(Startup_MDIV<<14)|(Startup_PDIV<<5)|(Startup_SDIV))
#define EPLL_VAL						((Startup_EPLLSTOP<<24)|(Startup_EMDIV<<16)|(Startup_EPDIV<<8)|(Startup_ESDIV<<0))//96MHz

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */

#define CONFIG_SDRAM_AUTO_DETECT
						/* Memoery Type mSDRAM or mDDR */
#define CFG_BANK_CFG_VAL				0x0004920d
#define CFG_BANK_CON1_VAL				0x04000040
#define CFG_BANK_CFG_VAL_ALT			0x00048904
#define CFG_BANK_CON1_VAL_ALT			0x04000040
#define CFG_BANK_CFG_VAL_DDR2			0x00049253
#define CFG_BANK_CON1_VAL_DDR2			0x44000040

#define CFG_BANK_CON2_VAL				0x0057003a
#define CFG_BANK_CON2_VAL_DDR2			0x005D0035
#define CFG_BANK_CON3_VAL				0x80000030
#define CFG_BANK_REFRESH_VAL			0x00000313

//======================================================================================
//	MEM config	[SDR, DDR, DDR2]
//======================================================================================
//#define TQ2416_mSDRAM
//#define TQ2416_mDDR
#define TQ2416_DDR2

#if defined(TQ2416_mSDRAM)

//---------------------------------------
// BANKCONFIG register  : SDRAM configure
//---------------------------------------
#define RASBW0							2			//	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit
#define RASBW1							2			//	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit
#define CASBW0							1			//	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit
#define CASBW1							1			//	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit
#define ADDRCFG0						1			// 	addre configure 00={BA,RAS,CAS}, 01={RAS,BA,CAS}
#define ADDRCFG1						1			// 	addre configure 00={BA,RAS,CAS}, 01={RAS,BA,CAS}
#define MEMCFG							2			// 	Ext.Mem 000=SDR,010=MSDR,100=DDRz,110=MDDR,001=DDR2
#define BW								0			// 	Bus width 00=32bit,01=16bit

//---------------------------------------
// BANKCON1 register : SDRAM timing control
//---------------------------------------
#define BStop							0			//	read burst stop control
#define WBUF							1			//	write buffer control
//#define AP							1			//	disable auto precharge control
#define AP								0			//	enable auto precharge control
//#define PWRDN							0			//	not support power down mode
#define PWRDN							1			//	support power down mode
#define DQSDelay						4			//	DQS delay

//-----------------------[SDRAM]-------------------------------
// HCLK		tRAS	tARFC	CAS	tRCD	RP	REFCYC
//---------------------------------------------------------------
// 18MHz		0	1	3	0	0	140
// 36MHz		1	2	3	0	0	280
// 100Mhz		5	7	3	1	1	780
// 110Mhz		5	7	3	2	2	858
// 120Mhz		6	7	3	2	2	936
// 133Mhz		6	10	3	2	2	1037
// 133.5Mhz		6	10	3	2	2	1041
// 135Mhz		6	10	3	2	2	1053
// 136Mhz		6	10	3	2	2	1060
// 136.5Mhz		6	10	3	2	2	1064
// 137.3Mhz		6	10	3	2	2	1070
// 138Mhz		6	10	3	2	2	1076
// 138.67Mhz	6	10	3	2	2	1081
// 140Mhz		6	11	3	3	3	1092 (out of spec)
// 141Mhz		6	11	3	3	3	1099
// 142Mhz		7	11	3	3	3	1107 (out of spec)
// 143.6Mhz		7	11	3	3	3	1120 (out of spec)
//---------------------------------------------------------------
//---------------------------------------
// BANKCON2 register : SDRAM timing control
//---------------------------------------
#if (HCLKVAL == 18)
#define tRAS							4			//	Row active time
#define tARFC							6			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							1			//	RAS to CAS delay
#define tRP								1			// 	Row pre-charge time
#elif (HCLKVAL == 100)
#define tRAS							5			//	Row active time
#define tARFC							7			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							2			//	RAS to CAS delay
#define tRP								2			// 	Row pre-charge time
#elif (HCLKVAL == 133)
#define tRAS							6			//	Row active time
#define tARFC							10			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							2			//	RAS to CAS delay
#define tRP								2			// 	Row pre-charge time
#endif
//---------------------------------------
// BANKCON3 register : SDRAM MRS/EMRS register
//---------------------------------------
#define BA_EMRS							2			//	BA : EMRS
#define DS								0			//	Driver strength
#define PASR							0			//	PASR
#define BA_MRS							0			//	BA : MRS
#define TM								0			// 	Test Mode - mode register set
#define CL_MRS							3			// 	CAS Latency

//---------------------------------------
// REFRESH register : SDRAM refresh register
#if (HCLKVAL == 18)
#define REFCYC							140			// 	refresh cycle
#elif (HCLKVAL == 100)
#define REFCYC							780			// 	refresh cycle
#elif (HCLKVAL == 133)
#define REFCYC							1037			// 	refresh cycle
#endif

#elif defined(TQ2416_mDDR)
//---------------------------------------
// BANKCONFIG register  : mDDR SDRAM configure
//---------------------------------------
#define RASBW0							2			//	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit
#define RASBW1							2			//	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit
#define CASBW0							2			//	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit
#define CASBW1							2			//	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit
#define ADDRCFG0						1			// 	addre configure 00={BA,RAS,CAS}, 01={RAS,BA,CAS}
#define ADDRCFG1						1			// 	addre configure 00={BA,RAS,CAS}, 01={RAS,BA,CAS}
#define MEMCFG							6			// 	Ext.Mem 000=SDR,010=MSDR,100=DDRz,110=MDDR,001=DDR2
#define BW								1			// 	Bus width 00=32bit,01=16bit

//---------------------------------------
// BANKCON1 register : mDDR SDRAM timing control
//---------------------------------------
#define BStop							0			//	read burst stop control
#define WBUF							1			//	write buffer control
//#define AP							1			//	disable auto precharge control
#define AP								0			//	enable auto precharge control
//#define PWRDN							0			//	not support power down mode
#define PWRDN							1			//	support power down mode
#define DQSDelay						4			//	DQS delay

//-----------------------[mDDR SDRAM]--------------------------
// HCLK		tRAS	tARFC	CAS	tRCD	tRP	REFCYC
//---------------------------------------------------------------
// 18MHz		0	1	3	0	0	140
// 36MHz		1	2	3	0	0	280
// 100Mhz		4	7	3	2	2	780
// 110Mhz		4	8	3	2	2	858
// 120Mhz		5	9	3	2	2	936
// 133Mhz		5	10	3	2	2	1037
//---------------------------------------------------------------

//---------------------------------------
// BANKCON2 register : mDDR SDRAM timing control
//---------------------------------------
#if (HCLKVAL == 18)
#define tRAS							0			//	Row active time
#define tARFC							1			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							0			//	RAS to CAS delay
#define tRP								0			// 	Row pre-charge time
#elif (HCLKVAL == 100)
#define tRAS							4			//	Row active time
#define tARFC							7			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							2			//	RAS to CAS delay
#define tRP								2			// 	Row pre-charge time
#elif (HCLKVAL == 133)
#define tRAS							5			//	Row active time
#define tARFC							10			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							2			//	RAS to CAS delay
#define tRP								2			// 	Row pre-charge time
#endif
//---------------------------------------
// BANKCON3 register : mDDR SDRAM MRS/EMRS register
//---------------------------------------
#define BA_EMRS							2			//	BA : EMRS
#define DS								0			//	Driver strength
#define PASR							0			//	PASR
#define BA_MRS							0			//	BA : MRS
#define TM								0			// 	Test Mode - mode register set
#define CL_MRS							3			// 	CAS Latency

//---------------------------------------
// REFRESH register : mDDR SDRAM refresh register
//--------------------------------------
#if (HCLKVAL == 18)
#define REFCYC							140			// 	refresh cycle
#elif (HCLKVAL == 100)
#define REFCYC							780			// 	refresh cycle
#elif (HCLKVAL == 133)
#define REFCYC							1037			// 	refresh cycle
#endif

#elif defined(TQ2416_DDR2)
//---------------------------------------
// BANKCONFIG register  : DDR2 SDRAM configure
//---------------------------------------
#define RASBW0							2			//	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit
#define RASBW1							2			//	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit
#define CASBW0							2			//	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit
#define CASBW1							2			//	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit
#define ADDRCFG0						1			// 	addre configure 00={BA,RAS,CAS}, 01={RAS,BA,CAS}
#define ADDRCFG1						1			// 	addre configure 00={BA,RAS,CAS}, 01={RAS,BA,CAS}
#define MEMCFG							1			// 	Ext.Mem 000=SDR,010=MSDR,100=DDRz,110=MDDR,001=DDR2
#define BW								1			// 	Bus width 00=32bit,01=16bit


//---------------------------------------
// BANKCON1 register : DDR2 SDRAM timing control
//---------------------------------------
#define PADLOAD							1
#define BStop							0			//	read burst stop control
#define WBUF							1			//	write buffer control
//#define AP							1			//	disable auto precharge control
#define AP								0			//	enable auto precharge control
//#define PWRDN							0			//	not support power down mode
#define PWRDN							1			//	support power down mode
#define DQSDelay						4			//	DQS delay

//-----------------------[DDR2 SDRAM]--------------------------
// HCLK		tRAS	tARFC	CAS	tRCD	tRP	REFCYC
//--------------------------------------------------------------
// 18MHz		0	1	3	0	0	140
// 36MHz		1	3	3	1	1	280
// 100Mhz		4	10	3	1	1	780
// 110Mhz		4	11	3	1	1	858
// 120Mhz		4	12	3	1	1	936
// 133Mhz		5	13	3	1	1	1037
//---------------------------------------------------------------

//---------------------------------------
// BANKCON2 register : DDR2 SDRAM timing control
//---------------------------------------
#if (HCLKVAL == 18)
#define tRAS							0			//	Row active time
#define tARFC							1			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							0			//	RAS to CAS delay
#define tRP								0			// 	Row pre-charge time
#elif (HCLKVAL == 100)
#define tRAS							4			//	Row active time
#define tARFC							10			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							1			//	RAS to CAS delay
#define tRP								1			// 	Row pre-charge time
#elif (HCLKVAL == 133)
#define tRAS							5			//	Row active time
#define tARFC							13			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							1			//	RAS to CAS delay
#define tRP								1			// 	Row pre-charge time
#endif
//---------------------------------------
// BANKCON3 register : DDR2 SDRAM MRS/EMRS register
//---------------------------------------
#define BA_EMRS1						1			//	BA : EMRS
#define DLL_DIS							1
#define DLL_EN							0
#define nDQS_DIS						1
#define RDQS_DIS						0
#define OCD_MODE_EXIT					0
#define OCD_MODE_DEFAULT				7
#define BA_EMRS2						2			//	BA : EMRS
#define BA_EMRS3						3			//	BA : EMRS
#define DS								0			//	Driver strength
#define PASR							0			//	PASR
#define BA_MRS							0			//	BA : MRS
#define TM								0			// 	Test Mode - mode register set
#define CL_MRS							3			// 	CAS Latency
#define DLL_RESET_HIGH					1
#define DLL_RESET_LOW					0

//---------------------------------------
// REFRESH register : DDR2 SDRAM refresh register
//---------------------------------------
#if (HCLKVAL == 18)
#define REFCYC							140			// 	refresh cycle
#elif (HCLKVAL == 100)
#define REFCYC							780			// 	refresh cycle
#elif (HCLKVAL == 133)
#define REFCYC							1037			// 	refresh cycle
#endif

#endif

#define BANKCFGVAL						((RASBW0<<17)+(RASBW1<<14)+(CASBW0<<11)+(CASBW1<<8)+(ADDRCFG0<<6)+(ADDRCFG1<<4)+(MEMCFG<<1)+(BW<<0))
#define BANKCON1VAL						((DQSDelay<<28)+(1<<26)+(BStop<<7)+(WBUF<<6)+(AP<<5)+(PWRDN<<4))
#define BANKCON2VAL						((tRAS<<20)+(tARFC<<16)+(CL<<4)+(tRCD<<2)+(tRP<<0))
#if defined(TQ2416_mSDRAM)
#define BANKCON3VAL						((BA_EMRS<<30)+(DS<<21)+(PASR<<16)+(BA_MRS<<14)+(TM<<7)+(CL_MRS<<4))
#elif defined(TQ2416_mDDR)
#define BANKCON3VAL						((BA_EMRS<<30)+(DS<<21)+(PASR<<16)+(BA_MRS<<14)+(TM<<7)+(CL_MRS<<4))
#endif

#define CONFIG_NR_DRAM_BANKS			1	   /* we have 2 bank of DRAM */
#define PHYS_SDRAM_1					MEMORY_BASE_ADDRESS /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE				0x04000000 /* 128 MB */

#define CONFIG_FLASH_BASE				0x08000000


/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CONFIG_MAX_FLASH_BANKS			1	/* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_BANKS		1	/* max number of memory banks */
#define CONFIG_MAX_FLASH_SECT			1024
#ifdef EMBEDSKY_ADD
#define CONFIG_SYS_MAX_FLASH_SECT		1024
#endif
#define CONFIG_AMD_LV800
#define PHYS_FLASH_SIZE					0x100000

/* timeout values are in ticks */
#define CONFIG_FLASH_ERASE_TOUT			(5*CONFIG_HZ) /* Timeout for Flash Erase */
#define CONFIG_FLASH_WRITE_TOUT			(5*CONFIG_HZ) /* Timeout for Flash Write */

#define CONFIG_ENV_ADDR					0
#define CONFIG_ENV_OFFSET 				0x00080000//0x0003c000
#define CONFIG_ENV_SIZE					0x4000	/* Total Size of Environment Sector */

/*
 * TQ2416 board specific data
 */

#define CONFIG_IDENT_STRING				" for TQ2416"

/* total memory required by uboot */
#define CONFIG_UBOOT_SIZE				(2*1024*1024)

/* base address for u-boot */
#ifdef CONFIG_ENABLE_MMU
#define CONFIG_UBOOT_BASE				0xc3E00000
#else /* CONFIG_ENABLE_MMU */
#define CONFIG_UBOOT_BASE				0x33E00000
#endif /* CONFIG_ENABLE_MMU */

#define CONFIG_PHY_UBOOT_BASE			(MEMORY_BASE_ADDRESS + 0x3E00000)



/* NAND configuration */
#define CONFIG_MAX_NAND_DEVICE			1
#define CONFIG_SYS_MAX_NAND_DEVICE		CONFIG_MAX_NAND_DEVICE
#define CONFIG_NAND_BASE				(0x4e000010)
#define CONFIG_SYS_NAND_BASE			CONFIG_NAND_BASE
#define CONFIG_NAND_SKIP_BAD_DOT_I		1  /* ".i" read skips bad blocks   */
#define CONFIG_NAND_WP					1
#define CONFIG_NAND_YAFFS_WRITE			1  /* support yaffs write */
#define CONFIG_CMD_NAND_YAFFS			1
#if 0
//#define CONFIG_NAND_FLASH_BBT
#define CONFIG_NAND_BL1_8BIT_ECC
#define CONFIG_NAND_HWECC
#endif 
#define NAND_MAX_CHIPS					1
#define NAND_DISABLE_CE()				(NFCONT_REG |= (1 << 1))
#define NAND_ENABLE_CE()				(NFCONT_REG &= ~(1 << 1))
#define NF_TRANSRnB()					do { while(!(NFSTAT_REG & (1 << 0))); } while(0)
#define CONFIG_MMC		
//#define CONFIG_MTDPARTITION			"40000 3C0000 3000000"
#define CONFIG_ONENAND_BASE				(0x00000000)
//#define CONFIG_MAX_ONENAND_DEVICE	1
//#define CONFIG_ENV_IS_IN_AUTO
#define CONFIG_MMC_BASE					(0xf0000000)

#define CONFIG_ENABLE_IROM_BOOT			1

/* nand copy size from nand to DRAM.*/
#define COPY_BL2_SIZE					0x100000//0x80000

/* Boot configuration (define only one of next) */
//#define CONFIG_BOOT_NOR
//#define CONFIG_BOOT_NAND
#define CONFIG_BOOT_MOVINAND
//#define CONFIG_BOOT_ONENAND

#define CONFIG_NAND
//#define CONFIG_ONENAND
#define CONFIG_MOVINAND

/* Settings as above boot configuration */
#if 1
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_NAND_LARGEPAGE_SAVEENV
#define CONFIG_BOOTCOMMAND				"nand read.jffs2 c0008000 kernel;bootm c0008000"
#else
#if (defined(CONFIG_BOOT_NAND) && !defined(CONFIG_BOOT_MOVINAND))
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_NAND_LARGEPAGE_SAVEENV
#define CONFIG_BOOTCOMMAND				"nand read c0008000 40000 1c0000;bootm c0008000"
#elif defined(CONFIG_BOOT_MOVINAND)
#define CONFIG_ENV_IS_IN_MOVINAND
#define CONFIG_BOOTCOMMAND				"movi read kernel c0008000;movi read rootfs c0800000 800000;bootm c0008000"
#else
# error Define one of CONFIG_BOOT_{NAND|MOVINAND|ONENAND}
#endif
#endif

#define CONFIG_JFFS2_NAND				1	/* jffs2 on nand support */
#define NAND_CACHE_PAGES				16	/* size of nand cache in 512 bytes pages */

/*
 * JFFS2 partitions
 */
#undef CONFIG_JFFS2_CMDLINE
#define CONFIG_JFFS2_DEV				"nand0"
#define CONFIG_JFFS2_PART_SIZE			0xffffffff
#define CONFIG_JFFS2_PART_OFFSET		0x00200000

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootargs_defaults=setenv bootargs " \
		"${bootargs} " \
		"lcd=${lcdtype}\0"  

#endif	/* __CONFIG_H */
