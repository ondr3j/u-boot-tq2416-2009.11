#ifdef CONFIG_EmbedSky_LCD

#if 0
#define TFT240320				1
#define TFT320240				2
#define TFT480272				3//T43(天嵌4.3寸屏)
#define VGA640480				4
#define TFT800480				5//A70(群创7.0寸屏)
#define TFT800600				6//A104(友达10.4寸屏)
#define VGA1024768				7//VGA1024x768
#define TFT800480TN92			8

#define LCD_TFT					TFT480272

#if(LCD_TFT == TFT240320)
#define	CONFIG_LCD_VBPD				1
#define	CONFIG_LCD_VFPD				2
#define	CONFIG_LCD_VSPW				1
#define	CONFIG_LCD_HBPD				6
#define	CONFIG_LCD_HFPD				3
#define	CONFIG_LCD_HSPW				1
#define	CONFIG_LCD_CLKVAL			2
#define CONFIG_LCD_BPP				16
#define LCD_XSIZE_TFT				240
#define LCD_YSIZE_TFT				320

#elif(LCD_TFT == TFT320240)
#define	CONFIG_LCD_VBPD				12
#define	CONFIG_LCD_VFPD				4
#define	CONFIG_LCD_VSPW				5
#define	CONFIG_LCD_HBPD				21
#define	CONFIG_LCD_HFPD				32
#define	CONFIG_LCD_HSPW				44
#define	CONFIG_LCD_CLKVAL			6
#define CONFIG_LCD_BPP				16
#define LCD_XSIZE_TFT				240
#define LCD_YSIZE_TFT				320

#elif(LCD_TFT == TFT480272)
#define	CONFIG_LCD_VBPD				(2-1)
#define	CONFIG_LCD_VFPD				(2-1)
#define	CONFIG_LCD_VSPW				(10-1)
#define	CONFIG_LCD_HBPD				(2-1)
#define	CONFIG_LCD_HFPD				(2-1)
#define	CONFIG_LCD_HSPW				(41-1)
#define	CONFIG_LCD_CLKVAL			7
#define CONFIG_LCD_BPP				16
#define LCD_XSIZE_TFT				480
#define LCD_YSIZE_TFT				272

#elif(LCD_TFT == VGA640480)
#define	CONFIG_LCD_VBPD				29
#define	CONFIG_LCD_VFPD				5
#define	CONFIG_LCD_VSPW				4
#define	CONFIG_LCD_HBPD				71
#define	CONFIG_LCD_HFPD				40
#define	CONFIG_LCD_HSPW				31
#define	CONFIG_LCD_CLKVAL			1
#define CONFIG_LCD_BPP				16
#define LCD_XSIZE_TFT				640
#define LCD_YSIZE_TFT				480

#elif(LCD_TFT == TFT800480)
#define	CONFIG_LCD_VBPD				4
#define	CONFIG_LCD_VFPD				2
#define	CONFIG_LCD_VSPW				2
#define	CONFIG_LCD_HBPD				27
#define	CONFIG_LCD_HFPD				14
#define	CONFIG_LCD_HSPW				10
#define	CONFIG_LCD_CLKVAL			3
#define CONFIG_LCD_BPP				16
#define LCD_XSIZE_TFT				800
#define LCD_YSIZE_TFT				480

#elif(LCD_TFT == TFT800480TN92)
#define	CONFIG_LCD_VBPD				13
#define	CONFIG_LCD_VFPD				10
#define	CONFIG_LCD_VSPW				8
#define	CONFIG_LCD_HBPD				32
#define	CONFIG_LCD_HFPD				22
#define	CONFIG_LCD_HSPW				12
#define	CONFIG_LCD_CLKVAL			3
#define CONFIG_LCD_BPP				16
#define LCD_XSIZE_TFT				800
#define LCD_YSIZE_TFT				480

#elif(LCD_TFT == TFT800600)
#define	CONFIG_LCD_VBPD				4
#define	CONFIG_LCD_VFPD				2
#define	CONFIG_LCD_VSPW				2
#define	CONFIG_LCD_HBPD				27
#define	CONFIG_LCD_HFPD				14
#define	CONFIG_LCD_HSPW				8
#define	CONFIG_LCD_CLKVAL			4
#define CONFIG_LCD_BPP				16
#define LCD_XSIZE_TFT				800
#define LCD_YSIZE_TFT				600

#elif(LCD_TFT == VGA1024768)
#define	CONFIG_LCD_VBPD				4 
#define	CONFIG_LCD_VFPD				3
#define	CONFIG_LCD_VSPW				3
#define	CONFIG_LCD_HBPD				27 
#define	CONFIG_LCD_HFPD				14 
#define	CONFIG_LCD_HSPW				10 
#define	CONFIG_LCD_CLKVAL			4
#define CONFIG_LCD_BPP				16
#define LCD_XSIZE_TFT				1024
#define LCD_YSIZE_TFT				768
#endif
#else

typedef struct __LCD_CONFIG{
	u8 lcd_vbpd;
	u8 lcd_vfpd;
	u8 lcd_vspw;
	u8 lcd_hbpd;
	u8 lcd_hfpd;
	u8 lcd_hspw;
	u8 lcd_clkval;
	u8 lcd_bpp;
	u16 lcd_xsize;
	u16 lcd_ysize;
}lcd_config_info;
typedef enum _LCD_TYPE{
	X240Y320=0,
	X320Y240,
	X480Y272,
	X640Y480,
	X800Y480,
	X800Y600,
	X1024Y768,
	LCD_TYPE_MAX,
}LCD_TYPE;

extern lcd_config_info *curren_info;
extern const lcd_config_info tq_lcd_config_info[LCD_TYPE_MAX];

#define	CONFIG_LCD_VBPD				(curren_info->lcd_vbpd)
#define	CONFIG_LCD_VFPD				(curren_info->lcd_vfpd)
#define	CONFIG_LCD_VSPW				(curren_info->lcd_vspw)
#define	CONFIG_LCD_HBPD				(curren_info->lcd_hbpd) 
#define	CONFIG_LCD_HFPD				(curren_info->lcd_hfpd)
#define	CONFIG_LCD_HSPW				(curren_info->lcd_hspw)
#define	CONFIG_LCD_CLKVAL			(curren_info->lcd_clkval)
#define CONFIG_LCD_BPP				(curren_info->lcd_bpp)
#define LCD_XSIZE_TFT				(curren_info->lcd_xsize)
#define LCD_YSIZE_TFT				(curren_info->lcd_ysize)

#endif


#define NAND_CONTROL_ENABLE()			(NFCONT_REG |= (1 << 0))
#define NAND_DISABLE_CE()				(NFCONT_REG |= (1 << 1))
#define NAND_ENABLE_CE()				(NFCONT_REG &= ~(1 << 1))
#define NF_TRANSRnB()					do { while(!(NFSTAT_REG & (1 << 0))); } while(0)

#define SCR_XSIZE_TFT	 				(LCD_XSIZE_TFT)
#define SCR_YSIZE_TFT	 				(LCD_YSIZE_TFT)

#define HOZVAL_TFT						(LCD_XSIZE_TFT - 1 )
#define LINEVAL_TFT						(LCD_YSIZE_TFT - 1 )

#define LOGO_ZONE_OFFSET				0x100000
#define VIDEO_MEM_SIZE					0x200000					/*1024*768*2 = 0x180000Byte */
#define LCD_VIDEO_ADDR					0x37900000
#define LCD_VIDEO_BACKGROUND_ALPHA		(0xa)

void tq2416_lcd(void);
void embedsky_user_logo(void);
void embedsky_tq_logo(void);
#endif /* CONFIG_EmbedSky_LCD */

