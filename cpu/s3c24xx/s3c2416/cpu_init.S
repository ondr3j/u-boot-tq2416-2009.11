/*
 *  cpu/s3c24xx/s3c2416/cpu_init.S
 *
 *  Memory controller and cache code for U-Boot
 *
 *  Copyright (c) 2006,  Samsung Electronics
 *  All rights reserved.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * $Id: cpu_init.S,v 1.2 2008/03/24 12:27:06 boyko Exp $
 */

#include <config.h>
#include <s3c2416.h>

/*
 * sdr_ram_asm_init: Initialize memory controller
 *
 * r0: input argument that contains memory setting value
 * r1: BANKCON1 Value
 * r2: BANKCON1 Value Modified
 * r3: Temp value
 * r4: MEMCON Base Address
 * r5-r11: setting value
 *
 */

	.globl sdr_ctrl_asm_init
sdr_ctrl_asm_init:
	mov	r13, #2

#if 1
#if defined(TQ2416_mSDRAM)
	/* Set GPK port when using x32 bus width. */
	ldr	r0,=GPKCON_REG
	ldr	r1,=0xaaaaaaaa	@ set Sdata[31:16]
	str	r1, [r0]

	ldr	r0, =BANKCFGREG
	ldr	r1, =BANKCFGVAL
	str	r1, [r0]

	ldr	r0, =BANKCON1REG
	ldr	r1, =BANKCON1VAL
	str	r1, [r0]

	ldr	r0, =BANKCON2REG
	ldr	r1, =BANKCON2VAL
	str	r1, [r0]

	ldr	r0, =BANKCON3REG
	ldr	r1, =BANKCON3VAL
	str	r1, [r0]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x1<<0)
	str	r1, [r2]

	ldr	r4, =REFRESHREG
	ldr	r0, =0xFF
	str	r0, [r4]

	mov	r0, #0x100
2:
	subs	r0, r0, #1
	bne	2b

	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x2<<0)
	str	r1, [r2]

	ldr	r4, =REFRESHREG
	ldr	r0, =REFCYC
	str	r0, [r4]

	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	bic	r1, r1, #(0x3<<0)
	str	r1, [r2]

#elif defined(TQ2416_mDDR)
	/* Set GPK port when using x32 bus width. */
	ldr	r0,=GPKCON_REG
	ldr	r1,=0xaaaaaaaa	@ set Sdata[31:16]
	str	r1, [r0]

	ldr	r0, =BANKCFGREG
	ldr	r1, =BANKCFGVAL
	str	r1, [r0]

	ldr	r0, =BANKCON1REG
	ldr	r1, =BANKCON1VAL
	str	r1, [r0]

	ldr	r0, =BANKCON2REG
	ldr	r1, =BANKCON2VAL
	str	r1, [r0]

	ldr	r0, =BANKCON3REG
	ldr	r1, =BANKCON3VAL
	str	r1, [r0]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x1<<0)
	str	r1, [r2]

	ldr	r4, =REFRESHREG
	ldr	r0, =0xFF
	str	r0, [r4]

	mov	r0, #0x100
2:
	subs	r0, r0, #1
	bne	2b

	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x2<<0)
	str	r1, [r2]

	ldr	r4, =REFRESHREG
	ldr	r0, =REFCYC
	str	r0, [r4]

	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	bic	r1, r1, #(0x3<<0)
	str	r1, [r2]

#elif defined(TQ2416_DDR2)
	/* Set GPK port when using x32 bus width. */
	ldr	r0,=GPKCON_REG
	ldr	r1,=0xaaaaaaaa	@ set Sdata[31:16]
	str	r1, [r0]

	ldr	r0, =BANKCFGREG
	ldr	r1, =BANKCFGVAL
	str	r1, [r0]

	ldr	r0, =BANKCON1REG
	ldr	r1, =BANKCON1VAL
	str	r1, [r0]

	ldr	r0, =BANKCON2REG
	ldr	r1, =BANKCON2VAL
	str	r1, [r0]

//	ldr	r2, =RSTSTAT_REG
//	ldr	r1, [r2]
//	cmp	r1, #0x1
//	bne	GOM

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x1<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, #(BA_EMRS2<<30)
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, #(BA_EMRS3<<30)
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r4, =((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_EXIT<<23)+(DLL_EN<<16))

	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, r4
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, #((BA_MRS<<14)+(DLL_RESET_HIGH<<8)+(TM<<7)+(CL_MRS<<4))
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x2<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x1<<0)
	str	r1, [r2]

	ldr	r4, =REFRESHREG
	ldr	r0, =0x20
	str	r0, [r4]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, #((BA_MRS<<14)+(DLL_RESET_LOW<<8)+(TM<<7)+(CL_MRS<<4))
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x2<<0)
	str	r1, [r2]

	mov	r0, #0x100
2:
	subs	r0, r0, #1
	bne	2b

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r4, =((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_DEFAULT<<23)+(DLL_EN<<16))
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, r4	//#((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_DEFAULT<<23)+(DLL_EN<<16))
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r4, =((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_EXIT<<23)+(DLL_EN<<16))
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, r4	//#((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_DEFAULT<<23)+(DLL_EN<<16))
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r4, =REFRESHREG
	ldr	r0, =REFCYC
	str	r0, [r4]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	str	r1, [r2]

#endif
GOM:
	mov	pc, lr
#else
	/* Set GPK port when using x32 bus width. */
	ldr	r2,=GPKCON_REG
	ldr	r1,=0xaaaaaaaa	@ set Sdata[31:16]
	str	r1, [r2]

	/* read setting value from structure */
	ldr	r4, =ELFIN_MEMCTL_BASE
	ldmia	r0!, {r5-r11}
	stmia	r4!, {r5-r9}

#ifdef CONFIG_PM
	/* compare INFORM2 register to confirm the dram type*/
	ldr	r1, =INFORM2_REG
	ldr	r1, [r1]
	ldr	r2, =0xDA
	cmp	r2, r1

	ldreq	r4, =ELFIN_MEMCTL_BASE
	beq	1002f
#endif

1000:	ldr	r4, =ELFIN_MEMCTL_BASE

	ldr	r1, [r4, #BANKCON1_OFFSET]
	ldr	r2, =0x40000000			/* DDR DSQInDLL Value Setting */
	orr	r1, r1, r2
	bic	r1, r1, #INIT_MASK

	/* Step 1: issue PALL */
	orr	r2, r1, #INIT_PALL
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 2: write 0xff into the refresh timer */
	mov	r3, #0xff
	str	r3, [r4, #REFRESH_OFFSET]

	/* Step 3: wait more than 120 clk */
	mov	r3, #0x100
1:	subs	r3, r3, #1
	bne	1b

	/* Step 4: issue MRS */
	orr	r2, r1, #INIT_MRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 5: nornal operation value into the refresh timer */
	str	r9, [r4, #REFRESH_OFFSET]

	/* Step 6: issue EMRS */
	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 7: Normal Mode */
	orr	r2, r1, #INIT_NORMAL
	str	r2, [r4, #BANKCON1_OFFSET]

	ldr	r6, =(PHYS_SDRAM_1+0x4)
	ldr	r7, =0x24564236
	swp	r8, r7, [r6]
	swp	r5, r8, [r6]
	cmp	r7, r5
	beq	1001f

	sub	r13, r13, #1
	cmp	r13, #0
	beq	1004f

1002:	stmia	r4!, {r10-r11}
	b	1000b

/* boyko : Memory Type DDR2 */
1004:	ldr	r4, =ELFIN_MEMCTL_BASE

	/* Step 1: BANKCFG Setting */
	ldr	r2, =CFG_BANK_CFG_VAL_DDR2
	str	r2, [r4, #BANKCFG_OFFSET]

	ldr	r1, =0x44000040
	str	r1, [r4, #BANKCON1_OFFSET]

	/* Step 2: BANKCON2 Setting */
	ldr	r2, =CFG_BANK_CON2_VAL_DDR2
	str	r2, [r4, #BANKCON2_OFFSET]

	/* Step 3: issue PALL */
	orr	r2, r1, #INIT_PALL
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 4: Issue a EMRS2 command */
	ldr	r2, =0x80000000
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 5: Issue a EMRS3 command */
	ldr	r2, =0xc0000000
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 6: Issue a EMRS1 command */
	ldr	r2, =0x44000000
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 7: issue MRS */
	ldr	r2, =0x44000130
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_MRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 8: issue PALL */
	orr	r2, r1, #INIT_PALL
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 9: write 0xff into the refresh timer */
	mov	r3, #0xff
	str	r3, [r4, #REFRESH_OFFSET]

	/* Step 10: wait more than 120 clk */
	mov	r3, #0x100
10:	subs	r3, r3, #1
	bne	10b

	/* Step 11: issue MRS */
	ldr	r2, =0x44000030
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_MRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 12: Issue a EMRS1 command */
	ldr	r2, =0x47800030
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	ldr	r2, =0x44000030
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 13: write 0x87 into the refresh timer */
	mov	r3, #0x87
	str	r3, [r4, #REFRESH_OFFSET]

	/* Step 14: Normal Mode */
	orr	r2, r1, #INIT_NORMAL
	str	r2, [r4, #BANKCON1_OFFSET]
/* boyko : END - Memory Type DDR2 */

1001:	mov	pc, lr
#endif

	.ltorg


/* Below code is for ARM926EJS and ARM1026EJS */
	.globl cleanDCache
cleanDCache:
	mrc	p15, 0, pc, c7, c10, 3	/* test/clean D-Cache */
	bne	cleanDCache
	mov	pc, lr

	.globl cleanFlushDCache
cleanFlushDCache:
	mrc	p15, 0, pc, c7, c14, 3	/* test/cleanflush D-Cache */
	bne	cleanFlushDCache
	mov	pc, lr

	.globl cleanFlushCache
cleanFlushCache:
	mrc	p15, 0, pc, c7, c14, 3	/* test/cleanflush D-Cache */
	bne	cleanFlushCache
	mcr	p15, 0, r0, c7, c5, 0	/* flush I-Cache */
	mov	pc, lr

	.ltorg

