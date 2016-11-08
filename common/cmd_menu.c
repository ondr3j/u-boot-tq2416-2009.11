/*
 * tq_668@126.com, www.embedsky.net
 *
 */

#include <common.h>
#include <command.h>
#include <nand.h>
#ifdef CONFIG_EMBEDSKY_FAT
#include <def.h>
#include <embedsky_FAT.h>
#endif
#ifdef CONFIG_EmbedSky_LCD
#include <lcd/s3c2416_fb.h>
#endif /* CONFIG_EmbedSky_LCD */
#define EMBEDSKY_MODIFY_MENU	1

extern char console_buffer[];
extern int readline (const char *const prompt);
extern char awaitkey(unsigned long delay, int* error_p);

#ifdef CONFIG_EmbedSky_LCD
void lcd_menu_usage()
{
	printf("\r\n##### LCD select Menu #####\r\n");
	printf("[1] T43\" screen.\r\n");
	printf("[2] A70TN92\" screen.\r\n");
	printf("[3] A104\" screen.\r\n");
	printf("[4] VGA1024768\" screen.\r\n");
	printf("[5] W35\" screen.\r\n");
	printf("[6] VGA640480\" screen.\r\n");
	printf("[r] Reboot u-boot\r\n");
	printf("[q] Return Parameter Menu \r\n");
	printf("Enter your selection: ");
}
void lcd_menu_shell()
{
	char c;
	char cmd_buf[256];
	while (1)
	{
		lcd_menu_usage();
		c = getc();
		printf("%c\n", c);
		switch (c)
		{

			case '1':
			{
				sprintf(cmd_buf, "setenv lcdtype X480Y272;");
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);
				break;
			}

			case '2':
			{
				sprintf(cmd_buf, "setenv lcdtype X800Y480;");
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);
				break;
			}

			case '3':
			{
				sprintf(cmd_buf, "setenv lcdtype X800Y600;");
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);
				break;
			}

			case '4':
			{
				sprintf(cmd_buf, "setenv lcdtype X1024Y768;");
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);
				break;
			}

			case '5':
			{
				sprintf(cmd_buf, "setenv lcdtype X320Y240;");
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);
				break;
			}

			case '6':
			{
				sprintf(cmd_buf, "setenv lcdtype X640Y480;");
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);
				break;
				break;
			}

			case 'R':
			case 'r':
			{
				strcpy(cmd_buf, "reset");
				run_command(cmd_buf, 0);
				break;
			}

			case 'Q':
			case 'q':
			{
				return;
				break;
			}

		}
	}
}
#endif /* CONFIG_EmbedSky_LCD */


void param_menu_usage(void)
{
	printf("\r\n##### Parameter Menu #####\r\n");
	printf("[1] Set NFS boot parameter \r\n");
	printf("[2] Set Yaffs boot parameter for Standard Linux \r\n");
	printf("[3] Set UBIfs boot parameter for Standard Linux \r\n");
	printf("[4] Set parameter \r\n");
	printf("[5] View the parameters \r\n");
	printf("[d] Delete parameter \r\n");
	printf("[s] Save the parameters to Nand Flash \r\n");
	printf("[q] Return main Menu \r\n");
	printf("Enter your selection: ");
}


void param_menu_shell(void)
{
	char c;
	char cmd_buf[256];
	char name_buf[20];
	char val_buf[256];
	char param_buf1[25];
	char param_buf2[25];
	char param_buf3[25];
	char param_buf4[64];
	char param_buf5[10];

	while (1)
	{
		param_menu_usage();
#if EMBEDSKY_MODIFY_MENU
		c = getc();
#else
		c = awaitkey(-1, NULL);
#endif
		printf("%c\n", c);
		switch (c)
		{
			case '1':
			{
				sprintf(cmd_buf, "setenv bootargs ");

				printf("Enter the PC IP address:(xxx.xxx.xxx.xxx)\n");
				readline(NULL);
				strcpy(param_buf1,console_buffer);
				printf("Enter the SKY2416/TQ2416 IP address:(xxx.xxx.xxx.xxx)\n");
				readline(NULL);
				strcpy(param_buf2,console_buffer);
				printf("Enter the Mask IP address:(xxx.xxx.xxx.xxx)\n");
				readline(NULL);
				strcpy(param_buf3,console_buffer);
				printf("Enter NFS directory:(eg: /opt/EmbedSky/root_nfs)\n");
				readline(NULL);
				strcpy(param_buf4,console_buffer);
				sprintf(cmd_buf, "setenv bootargs noinitrd init=/linuxrc console=ttySAC0 root=/dev/nfs nfsroot=%s:%s ip=%s:%s:%s:%s:www.embedsky.com:eth0:off", param_buf1, param_buf4, param_buf2, param_buf1, param_buf2, param_buf3);
				printf("bootargs: noinitrd init=/linuxrc console=ttySAC0 root=/dev/nfs nfsroot=%s:%s ip=%s:%s:%s:%s:www.embedsky.net:eth0:off\n", param_buf5, param_buf1, param_buf4, param_buf2, param_buf1, param_buf2, param_buf3);

				run_command(cmd_buf, 0);
				break;
			}

			case '2':
			{
				sprintf(cmd_buf, "setenv bootargs noinitrd root=/dev/mtdblock3 rootfstype=yaffs2 init=/linuxrc console=ttySAC0");
				printf("bootargs: noinitrd root=/dev/mtdblock3 rootfstype=yaffs2 init=/linuxrc console=ttySAC0\n");

				run_command(cmd_buf, 0);
				break;
			}

			case '3':
			{
				sprintf(cmd_buf, "setenv bootargs noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/linuxrc console=ttySAC0");
				printf("bootargs: noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/linuxrc console=ttySAC0\n");

				run_command(cmd_buf, 0);
				break;
			}

			case '4':
			{
				sprintf(cmd_buf, "setenv ");

				printf("Name: ");
				readline(NULL);
				strcat(cmd_buf, console_buffer);

				printf("Value: ");
				readline(NULL);
				strcat(cmd_buf, " ");
				strcat(cmd_buf, console_buffer);
				printf("%s\n",cmd_buf);

				run_command(cmd_buf, 0);
				break;
			}

			case '5':
			{
				strcpy(cmd_buf, "printenv ");
				printf("Name(enter to view all paramters): ");
				readline(NULL);
				strcat(cmd_buf, console_buffer);
				run_command(cmd_buf, 0);
				break;
			}

			case 'D':
			case 'd':
			{
				sprintf(cmd_buf, "setenv ");

				printf("Name: ");
				readline(NULL);
				strcat(cmd_buf, console_buffer);

				run_command(cmd_buf, 0);
				break;
			}

			case 'S':
			case 's':
			{
				sprintf(cmd_buf, "saveenv");
				run_command(cmd_buf, 0);
				break;
			}

			case 'Q':
			case 'q':
			{
				//sprintf(cmd_buf, "saveenv");
				//run_command(cmd_buf, 0);
				return;
				break;
			}
		}
	}
}


#define USE_USB_DOWN		1
#define USE_TFTP_DOWN		2
#define USE_SD_DOWN			3

void main_menu_usage(char menu_type)
{

	printf("\r\n#####	 Boot for SKY2416/TQ2416 Main Menu	#####\r\n");

	if( menu_type == USE_USB_DOWN)
	{
		printf("#####     EmbedSky USB download mode     #####\r\n\n");
	}
	else if( menu_type == USE_TFTP_DOWN)
	{
		printf("#####     EmbedSky TFTP download mode     #####\r\n\n");
	}
#ifdef CONFIG_CMD_MENU_SD
	else if( menu_type == USE_SD_DOWN)
	{
		printf("#####     EmbedSky SD download mode     #####\r\n\n");
	}
#endif

	if( menu_type == USE_USB_DOWN)
	{
#ifdef CONFIG_WINCE_NK
		printf("[1] Download u-boot or other bootloader to Nand Flash\r\n");
#else
		printf("[1] Download u-boot or STEPLDR.nb1 or other bootloader to Nand Flash\r\n");
#endif
	}
	else if(( menu_type == USE_TFTP_DOWN) || ( menu_type == USE_SD_DOWN))
	{
		printf("[1] Download u-boot.bin to Nand Flash\r\n");
	}
	printf("[2] Download Eboot (eboot.nb0) to Nand Flash\r\n");
	printf("[3] Download Linux Kernel (zImage.bin) to Nand Flash\r\n");
	printf("[4] Download LOGO Picture (logo.bin) to Nand  Flash\r\n");
	printf("[5] Download UBIFS image (root.ubi) to Nand Flash\r\n");
	printf("[6] Download YAFFS image (root.bin) to Nand Flash\r\n");
	printf("[7] Download Program to SDRAM and Run it\r\n");

	printf("[8] Boot the system\r\n");
	printf("[9] Format the Nand Flash\r\n");
	printf("[0] Set the boot parameters\r\n");
	printf("[a] Download User Program\r\n");
#ifdef CONFIG_EmbedSky_LCD
	printf("[c] Choice lcd type.\r\n");
#endif /* CONFIG_EmbedSky_LCD */

	if( menu_type == USE_USB_DOWN)
	{
		printf("[n] Enter TFTP download mode menu\r\n");
	}
	else if( menu_type == USE_TFTP_DOWN)
	{
		printf("[n] Set TFTP parameters(PC IP,SKY2416/TQ2416 IP,Mask IP...)\r\n");
	}

	if( menu_type == USE_TFTP_DOWN)
	{
		printf("[p] Test network (TQ2416 Ping PC's IP)\r\n");
	}

	printf("[r] Reboot u-boot\r\n");

	if( menu_type == USE_USB_DOWN)
	{
#ifdef CONFIG_CMD_MENU_SD
		printf("[s] Enter SD download mode menu\r\n");
#endif
	}
	else if(( menu_type == USE_TFTP_DOWN) || ( menu_type == USE_SD_DOWN))
	{
		printf("[s] Download STEPLDR.nb1 to Nand Flash\r\n");
	}

	printf("[t] Test Linux Image (zImage)\r\n");
#ifdef CONFIG_TQ2416
	if( menu_type == USE_USB_DOWN)
	{
		printf("[q] quit from menu\r\n");
	}
	else
#endif
	if(( menu_type == USE_TFTP_DOWN) || ( menu_type == USE_SD_DOWN))
	{
		printf("[q] Return main Menu \r\n");
	}

	printf("Enter your selection: ");
}


void tftp_menu_shell(void)
{
	char keyselect;
	char cmd_buf[200];

	while (1)
	{
		main_menu_usage(USE_TFTP_DOWN);
#if 0
		while(!(((keyselect >= '0') && (keyselect <= '9')) ||
			((keyselect == 'a') || (keyselect == 'A')) ||
			((keyselect == 'n') || (keyselect == 'N')) ||
			((keyselect == 'p') || (keyselect == 'P')) ||
			((keyselect == 'r') || (keyselect == 'R')) ||
			((keyselect == 's') || (keyselect == 'S')) ||
			((keyselect == 't') || (keyselect == 'T')) ||
			((keyselect == 'q') || (keyselect == 'Q')) ))
		{
			keyselect = serial_getc();
		}
#else
#if EMBEDSKY_MODIFY_MENU
		keyselect = getc();
#else
		keyselect = awaitkey(-1, NULL);
#endif
#endif
		printf("%c\n", keyselect);
		switch (keyselect)
		{
			case '1':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "tftp 0xc0000000 u-boot.bin; nand erase bios; nand write.jffs2 0xc0000000 bios $(filesize)");
#else
				strcpy(cmd_buf, "tftp 0xc0000000 u-boot.bin; nand erase 0x0 0x80000; nand write.jffs2 0xc0000000 0x0 $(filesize)");
#endif
				run_command(cmd_buf, 0);
			break;
			}

			case '2':
			{
				sprintf(cmd_buf, "tftp 0xc0000000 eboot.nb0; nand erase 0x80000 0x80000; nand write.jffs2 0xc0000000 0x80000 $(filesize)");
				run_command(cmd_buf, 0);
				break;
			}

			case '3':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "tftp 0xc0000000 zImage.bin; nand erase kernel; nand write.jffs2 0xc0000000 kernel $(filesize)");
#else
				strcpy(cmd_buf, "tftp 0xc0000000 zImage.bin; nand erase 0x300000 0x400000; nand write.jffs2 0xc0000000 0x300000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '4':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "tftp 0xc0000000 logo.bin; nand erase logo; nand write.jffs2 0xc0000000 logo $(filesize)");
#else
				strcpy(cmd_buf, "tftp 0xc0000000 logo.bin; nand erase 0x100000 0x200000; nand write.jffs2 0xc0000000 0x100000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '5':
			{
				strcpy(cmd_buf, "tftp 0xc0000000 root.ubi;nand erase root;ubi part root;ubi create rootfs;ubi write 0xc0000000 rootfs $(filesize)");
				run_command(cmd_buf, 0);
				break;
			}

			case '6':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "tftp 0xc0000000 root.bin; nand erase root; nand write.yaffs 0xc0000000 root $(filesize)");
#else
				strcpy(cmd_buf, "tftp 0xc0000000 root.bin; nand erase 0x700000 0xF8D0000; nand write.yaffs 0xc0000000 0x700000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '7':
			{
				char tftpaddress[12];
				char filename[32];

				printf("Enter downloads to SDRAM address:\n");
				readline(NULL);
				strcpy(tftpaddress, console_buffer);

				printf("Enter program name:\n");
				readline(NULL);
				strcpy(filename, console_buffer);

				sprintf(cmd_buf, "tftp %s %s", tftpaddress, filename);
				printf("tftp %s %s\n", tftpaddress, filename);
				run_command(cmd_buf, 0);

				sprintf(cmd_buf, "go %s", tftpaddress);
				run_command(cmd_buf, 0);
				break;
			}

			case '8':
			{
				printf("Start Linux ...\n");
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "nand read.jffs2 0xc0008000 kernel;bootm 0xc0008000");
#else
				strcpy(cmd_buf, "nand read.jffs2 0xc0008000 0x300000 0x400000;bootm 0xc0008000");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '9':
			{
				strcpy(cmd_buf, "nand scrub ");
				run_command(cmd_buf, 0);
				break;
			}

			case '0':
			{
				param_menu_shell();
				break;
			}

			case 'A':
			case 'a':
			{
				char filename[32];

				printf("Enter program name:\n");
				readline(NULL);
				strcpy(filename, console_buffer);

				sprintf(cmd_buf, "tftp 0xc0000000 %s; nand erase 0x0 $(filesize+1); nand write.jffs2 0xc0000000 0x0 $(filesize+1)", filename);
				run_command(cmd_buf, 0);
				break;
			}

#ifdef CONFIG_EmbedSky_LCD
			case 'C':
			case 'c':
			{
				lcd_menu_shell();
				break;
			}
#endif /* CONFIG_EmbedSky_LCD */

			case 'N':
			case 'n':
			{
				char param_buf1[25];
				char param_buf2[25];
				char param_buf3[25];

				printf("Enter the TFTP Server(PC) IP address:(xxx.xxx.xxx.xxx)\n");
				readline(NULL);
				strcpy(param_buf1,console_buffer);
				sprintf(cmd_buf, "setenv serverip %s",param_buf1);
				run_command(cmd_buf, 0);

				printf("Enter the SKY2416/TQ2416 IP address:(xxx.xxx.xxx.xxx)\n");
				readline(NULL);
				strcpy(param_buf2,console_buffer);
				sprintf(cmd_buf, "setenv ipaddr %s",param_buf2);
				run_command(cmd_buf, 0);

				printf("Enter the Mask IP address:(xxx.xxx.xxx.xxx)\n");
				readline(NULL);
				strcpy(param_buf3,console_buffer);
				sprintf(cmd_buf, "setenv netmask %s",param_buf3);
				run_command(cmd_buf, 0);

				printf("Save TFTP IP parameters?(y/n)\n");
				if (getc() == 'y' )
				{
					printf("y");
					getc() == '\r';
					printf("\n");
					sprintf(cmd_buf, "saveenv");
					run_command(cmd_buf, 0);
				}
				else
				{
					printf("Not Save it!!!\n");
				}
				break;
			}

			case 'P':
			case 'p':
			{
				char *serverip;
				serverip=getenv("serverip");
				printf("TQ2416 ping PC IP:ping %s\n",serverip);
				sprintf(cmd_buf, "ping %s",serverip);
				run_command(cmd_buf, 0);
				break;
			}

			case 'R':
			case 'r':
			{
				strcpy(cmd_buf, "reset");
				run_command(cmd_buf, 0);
				break;
			}

			case 's':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "tftp 0xc0000000 stepldr.nb1; nand erase bios; nand write.jffs2 0xc0000000 bios $(filesize)");
#else
				strcpy(cmd_buf, "tftp 0xc0000000 stepldr.nb1; nand erase 0x0 0x80000; nand write.jffs2 0xc0000000 0x0 $(filesize)");
#endif
				run_command(cmd_buf, 0);
			break;
			}

			case 'T':
			case 't':
			{
				strcpy(cmd_buf, "tftp 0xc0008000 zImage.bin; bootm 0xc0008000");
				run_command(cmd_buf, 0);
				break;
			}

			case 'Q':
			case 'q':
			{
				return;
				break;
			}
		}
	}

}

#ifdef CONFIG_CMD_MENU_SD
void sd_menu_shell(void)
{
	char keyselect;
	char cmd_buf[200];

	while (1)
	{
		main_menu_usage(USE_SD_DOWN);
		keyselect = awaitkey(-1, NULL);
		printf("%c\n", keyselect);
		switch (keyselect)
		{
			case '1':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 u-boot.bin; nand erase bios; nand write.jffs2 0xc0000000 bios $(filesize)");
#else
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 u-boot.bin; nand erase 0x0 0x80000; nand write.jffs2 0xc0000000 0x0 $(filesize)");
#endif
				run_command(cmd_buf, 0);
			break;
			}

			case '2':
			{
				sprintf(cmd_buf, "fatload mmc 0 0xc0000000 eboot.nb0; nand erase 0x80000 0x80000; nand write.jffs2 0xc0000000 0x80000 $(filesize)");
				run_command(cmd_buf, 0);
				break;
			}

			case '3':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 zImage.bin; nand erase kernel; nand write.jffs2 0xc0000000 kernel $(filesize)");
#else
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 zImage.bin; nand erase 0x300000 0x400000; nand write.jffs2 0xc0000000 0x300000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

#if 1
			case '4':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 logo.bin; nand erase logo; nand write.jffs2 0xc0000000 logo $(filesize)");
#else
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 logo.bin; nand erase 0x100000 0x200000; nand write.jffs2 0xc0000000 0x100000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}
#else
			case '4':
			{
				FAT_Init();
				strcpy(cmd_buf, "nand erase root;ubi part root;ubi create rootfs;ubi OEMwrite 0xc0000000 rootfs images\\\\root_big.ubi");
				//strcpy(cmd_buf, "nand write.OEMyaffs 0xc0000000 root images\\\\root.bin");
				printf("%s\n",cmd_buf);
				run_command(cmd_buf, 0);
				break;
			}
#endif
			case '5':
			{
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 root.ubi;nand erase root;ubi part root;ubi create rootfs;ubi write 0xc0000000 rootfs $(filesize)");
				run_command(cmd_buf, 0);
				break;
			}

			case '6':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 root.bin; nand erase root; nand write.yaffs 0xc0000000 root $(filesize)");
#else
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 root.bin; nand erase 0x700000 0xF8D0000; nand write.yaffs 0xc0000000 0x700000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '7':
			{
				char sdaddress[12];
				char filename[32];
				printf("Enter downloads to SDRAM address:\n");
				readline(NULL);
				strcpy(sdaddress, console_buffer);

				printf("Enter program name:\n");
				readline(NULL);
				strcpy(filename, console_buffer);

				sprintf(cmd_buf, "fatload mmc 0 %s %s", sdaddress, filename);
				printf("fatload mmc 0 %s %s\n", sdaddress, filename);
				run_command(cmd_buf, 0);

				sprintf(cmd_buf, "go %s", sdaddress);
				run_command(cmd_buf, 0);
				break;
			}

			case '8':
			{
				printf("Start Linux ...\n");
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "nand read.jffs2 0xc0008000 kernel;bootm 0xc0008000");
#else
				strcpy(cmd_buf, "nand read.jffs2 0xc0008000 0x300000 0x400000;bootm 0xc0008000");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '9':
			{
				strcpy(cmd_buf, "nand scrub ");
				run_command(cmd_buf, 0);
				break;
			}

			case '0':
			{
				param_menu_shell();
				break;
			}

			case 'A':
			case 'a':
			{
				char filename[32];

				printf("Enter program name:\n");
				readline(NULL);
				strcpy(filename, console_buffer);

				sprintf(cmd_buf, "fatload mmc 0 0xc0000000 %s; nand erase 0x0 $(filesize+1); nand write.jffs2 0xc0000000 0x0 $(filesize+1)", filename);
				run_command(cmd_buf, 0);
				break;
			}

#ifdef CONFIG_EmbedSky_LCD
			case 'C':
			case 'c':
			{
				lcd_menu_shell();
				break;
			}
#endif /* CONFIG_EmbedSky_LCD */

			case 'R':
			case 'r':
			{
				strcpy(cmd_buf, "reset");
				run_command(cmd_buf, 0);
				break;
			}

			case 's':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 stepldr.nb1; nand erase bios; nand write.jffs2 0xc0000000 bios $(filesize)");
#else
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 stepldr.nb1; nand erase 0x0 0x80000; nand write.jffs2 0xc0000000 0x0 $(filesize)");
#endif
				run_command(cmd_buf, 0);
			break;
			}

			case 'T':
			case 't':
			{
				strcpy(cmd_buf, "fatload mmc 0 0xc0000000 zImage.bin; bootm 0xc0008000");
				run_command(cmd_buf, 0);
				break;
			}

			case 'Q':
			case 'q':
			{
				return;
				break;
			}
		}
	}

}
#endif

void menu_shell(void)
{
	char keyselect;
	char cmd_buf[200];

#ifdef CONFIG_EMBEDSKY_FAT
#if 0
	char c;
	if (!FAT_Init())						//初始化SD卡和FAT成功
	{
		printf("SD and FAT initialize success!\n");
		c = UbootStructInit();
		if (c == 0)						//配置文件内容不对
			printf("EmbedSky.ini is bad file!\n");
		else if (c == 1)					//获取配置文件成功
		{
			printf("Get EmbedSky.ini success!\n");
		}
	}
#endif
#endif
	while (1)
	{
		main_menu_usage(USE_USB_DOWN);
#if 0
		while(!(((keyselect >= '0') && (keyselect <= '9')) ||
			((keyselect == 'a') || (keyselect == 'A')) ||
			((keyselect == 'n') || (keyselect == 'N')) ||
			((keyselect == 'r') || (keyselect == 'R')) ||
			((keyselect == 't') || (keyselect == 'T')) ||
			((keyselect == 'q') || (keyselect == 'Q')) ))
		{
			keyselect = serial_getc();
		}
#else

#if EMBEDSKY_MODIFY_MENU
		keyselect = getc();
#else
		keyselect = awaitkey(-1, NULL);
#endif
#endif
		printf("%c\n", keyselect);
		switch (keyselect)
		{
			case '1':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "dnw 0xc0000000; nand erase bios; nand write.jffs2 0xc0000000 bios $(filesize)"); //0x80000");//
#else
				strcpy(cmd_buf, "dnw 0xc0000000; nand erase 0x0 0x80000; nand write.jffs2 0xc0000000 0x0 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '2':
			{
				sprintf(cmd_buf, "dnw 0xc0000000; nand erase 0x80000 0x80000; nand write.jffs2 0xc0000000 0x80000 $(filesize)");
				run_command(cmd_buf, 0);
				break;
			}

			case '3':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "dnw 0xc0008000; nand erase kernel; nand write.jffs2 0xc0008000 kernel $(filesize)");//0x400000");//
#else
				strcpy(cmd_buf, "dnw 0xc0008000; nand erase 0x300000 0x400000; nand write.jffs2 0xc0008000 0x300000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '4':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "dnw 0xc0000000; nand erase logo; nand write.jffs2 0xc0000000 logo  $(filesize)");
#else
				strcpy(cmd_buf, "dnw 0xc0000000; nand erase 0x100000 0x200000; nand write.jffs2 0xc0000000 0x100000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '5':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "dnw 0xc0000000;nand erase root;ubi part root;ubi create rootfs;ubi write 0xc0000000 rootfs  $(filesize)");
#else
				strcpy(cmd_buf, "dnw 0xc0000000; nand erase 0x700000 0xF8D0000; nand write.jffs2 0xc0000000 0x700000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '6':
			{
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "dnw 0xc0000000; nand erase root; nand write.yaffs 0xc0000000 root $(filesize)");
#else
				strcpy(cmd_buf, "dnw 0xc0000000; nand erase 0x700000 0xF8D0000; nand write.yaffs 0xc0000000 0x700000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '7':
			{
				char addr_buff[12];
				printf("Enter download address:(eg: 0xc0000000)\n");
				readline(NULL);
				strcpy(addr_buff,console_buffer);
				sprintf(cmd_buf, "dnw %s;go %s", addr_buff, addr_buff);
				run_command(cmd_buf, 0);
				break;
			}

			case '8':
			{
				printf("Start Linux ...\n");
				embedsky_user_logo();
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "nand read.jffs2 0xc0008000 kernel;bootm 0xc0008000");
#else
				strcpy(cmd_buf, "nand read.jffs2 0xc0008000 0x300000 0x400000;bootm 0xc0008000");
#endif
				run_command(cmd_buf, 0);
				break;
			}

			case '9':
			{
				strcpy(cmd_buf, "nand scrub ");
				run_command(cmd_buf, 0);
				break;
			}

			case '0':
			{
				param_menu_shell();
				break;
			}

			case 'A':
			case 'a':
			{
				strcpy(cmd_buf, "dnw 0xc0000000; nand erase 0x0 $(filesize+1); nand write.jffs2 0xc0000000 0x0 $(filesize+1)");
				run_command(cmd_buf, 0);
				break;
			}

#ifdef CONFIG_EmbedSky_LCD
			case 'C':
			case 'c':
			{
				lcd_menu_shell();
				break;
			}
#endif /* CONFIG_EmbedSky_LCD */

			case 'N':
			case 'n':
			{
				tftp_menu_shell();
				break;
			}

			case 'R':
			case 'r':
			{
				strcpy(cmd_buf, "reset");
				run_command(cmd_buf, 0);
				break;
			}

#ifdef CONFIG_CMD_MENU_SD
			case 'S':
			case 's':
			{
				sd_menu_shell();
				break;
			}
#endif

			case 'T':
			case 't':
			{
				strcpy(cmd_buf, "dnw 0xc0008000; bootm 0xc0008000");
				run_command(cmd_buf, 0);
				break;
			}
#if 0
			case 'C':
			case 'c':
			{
				strcpy(cmd_buf, "dnw 0xc1000000; relocateNK 0xc1000000 $(filesize); wince");
				run_command(cmd_buf, 0);
				break;
			}

			case 'F':
			case 'f':
			{
				strcpy(cmd_buf, "sdread 0xc0008000; bootm 0xc0008000");
				run_command(cmd_buf, 0);
				break;
			}
#endif
#if 0
			case 'L':
			case 'l':
			{
				char *t_ma=NULL ;
				t_ma=(char *)malloc(1024*512);
				if(!t_ma)
				{
					printf("malloc failed!\n");
				}
				else{
					printf("malloc success!\n");
					free(t_ma);
					t_ma=NULL;
				}
				break;
			}
#endif
#if 1
			case 'F':
			case 'f':
			{
				if (!FAT_Init())
				{
					printf("fat filesystem ok!\n");
				}
				else{
					printf("fat filesystem initial failed! ret=%d\n",FAT_Init());
				}

				break;
			}
#endif
#if 0
			case 'D':
			case 'd':
			{
				embedsky_user_logo();
				break;
			}
#endif
#ifdef CONFIG_TQ2416
			case 'Q':
			case 'q':
			{
				return;
				break;
			}
#endif
		}

	}
}

int do_menu (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	menu_shell();
	return 0;
}

U_BOOT_CMD(
	menu,	3,	0,	do_menu,
	"display a menu, to select the items to do something",
	"\n"
	"\tdisplay a menu, to select the items to do something"
);

