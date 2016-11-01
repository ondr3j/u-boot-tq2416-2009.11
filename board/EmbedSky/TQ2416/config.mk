#
# (C) Copyright 2002
# Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
# David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
#
# (C) Copyright 2008
# Guennadi Liakhovetki, DENX Software Engineering, <lg@denx.de>
#
# EmbedSky TQ2416 board with mDirac3 (ARM926) cpu
#
# see http://www.embedsky.net/ for more information on EmbedSky

# On TQ2416 we use the 64/128 MB SDRAM bank at
#
# 0x30000000 to 0x34000000
#
# Linux-Kernel is expected to be at 0x30008000, entry 0x30008000
#
# we load ourselves to 0x33e00000 without MMU
# with MMU, load address is changed to 0xc3e00000
#
# download area is 0x3000c000

sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

ifndef CONFIG_NAND_SPL
TEXT_BASE = $(RAM_TEXT)
else
TEXT_BASE = 0
endif

LDSCRIPT := $(SRCTREE)/board/$(BOARDDIR)/u-boot.lds
