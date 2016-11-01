#ifndef __MOVI_H__
#define __MOVI_H__

#define MOVI_INIT_REQUIRED			0
#define EMBEDSKY_MODIFY_MOVI_H		1
#if defined(CONFIG_S3C2416)
#define TCM_BASE					0x40004000
#define BL2_BASE					0x33E00000
#else
# error TCM_BASE or BL2_BASE is not defined
#endif

/* TCM function for bl2 load */
#if defined(CONFIG_S3C2416)
//#define CopyMovitoMem(a,b,c,d)	(((int(*)(uint, ushort, uint *, int))(*((uint *)(TCM_BASE + 0x8))))(a,b,c,d))
#define CopyMovitoMem(a,b,c,d)	(((uint(*)(uint, ushort, uint *, int))(0x1B68))(a,b,c,d))
#endif

/* size information */
#define SS_SIZE					(8 * 1024)
#define eFUSE_SIZE					(1 * 1024)	// 0.5k eFuse, 0.5k reserved`

/* movinand definitions */
#define MOVI_BLKSIZE			512
#define MOVI_RW_MAXBLKS			40960
#define MOVI_TOTAL_BLKCNT		*((volatile unsigned int*)(TCM_BASE - 0x4))
#define MOVI_HIGH_CAPACITY		*((volatile unsigned int*)(TCM_BASE - 0x8))
//#define MOVI_HIGH_CAPACITY		*((volatile unsigned int*)(0x40003FF4))
/* partition information */
#if EMBEDSKY_MODIFY_MOVI_H
#define PART_SIZE_BL			(512 * 1024)//(512 * 1024)//
#else
#define PART_SIZE_BL			(256 * 1024)//(512 * 1024)
#endif
#define PART_SIZE_KERNEL		(4 * 1024 * 1024)
#define PART_SIZE_ROOTFS		(56 * 1024 * 1024)

#define MOVI_LAST_BLKPOS		(MOVI_TOTAL_BLKCNT - (eFUSE_SIZE / MOVI_BLKSIZE))
#define MOVI_BL1_BLKCNT			(SS_SIZE / MOVI_BLKSIZE)
#define MOVI_ENV_BLKCNT			(CONFIG_ENV_SIZE / MOVI_BLKSIZE)
#define MOVI_BL2_BLKCNT			((PART_SIZE_BL / MOVI_BLKSIZE) - MOVI_ENV_BLKCNT)
#define MOVI_ZIMAGE_BLKCNT		(PART_SIZE_KERNEL / MOVI_BLKSIZE)
#define MOVI_BL2_POS			(MOVI_LAST_BLKPOS - MOVI_BL1_BLKCNT - MOVI_BL2_BLKCNT - MOVI_ENV_BLKCNT)
#define MOVI_ROOTFS_BLKCNT		(PART_SIZE_ROOTFS / MOVI_BLKSIZE)

struct movi_offset_t {
	uint	last;
	uint	bl1;
	uint	env;
	uint	bl2;
	uint	kernel;
	uint	rootfs;
};

/* external functions */
extern void hsmmc_set_base(void);
extern void hsmmc_set_gpio(void);
extern void hsmmc_reset (void);
extern int hsmmc_init (void);
extern int movi_init(void);
extern void movi_set_capacity(void);
extern int movi_set_ofs(uint last);
extern void movi_write (uint addr, uint start_blk, uint blknum);
extern void movi_read (uint addr, uint start_blk, uint blknum);
extern void movi_write_env(ulong addr);
extern void movi_read_env(ulong addr);

#if defined(CONFIG_S3C2416)
extern ulong virt_to_phy_tq2416(ulong addr);
//extern phys_addr_t virt_to_phys(void * vaddr);
#endif

extern void test_hsmmc (uint width, uint test, uint start_blk, uint blknum);

/* external variables */
extern int movi_ch;
extern uint movi_hc;
extern struct movi_offset_t ofsinfo;

#endif /*__MOVI_H__*/
