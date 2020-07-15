/* mcci_bootloader_formats.h	Mon Jun 29 2020 10:14:36 tmm */

/*

Module:  mcci_bootloader_formats.h

Function:
	Format of on-media data for the MCCI bootloader.

Version:
	V0.1.0	Mon Jun 29 2020 10:14:36 tmm	Edit level 1

Copyright notice:
	This file copyright (C) 2020 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	An unpublished work.  All rights reserved.

	This file is proprietary information, and may not be disclosed or
	copied without the prior permission of MCCI Corporation.

Author:
	Terry Moore, MCCI Corporation	June 2020

Revision history:
   0.1.0  Mon Jun 29 2020 10:14:36  tmm
	Module created.

*/

#ifndef _MCCI_BOOTLOADER_FORMATS_H_		/* prevent multiple includes */
#define _MCCI_BOOTLOADER_FORMATS_H_

#ifndef _MCCI_BOOTLOADER_TYPES_H_
# include "mcci_bootloader_types.h"
#endif

MCCIADK_BEGIN_DECLS

/****************************************************************************\
|
|	Header for flash image blocks -- this follows the MCCI LSL media
|       structure.
|
\****************************************************************************/

typedef struct McciBootloaderFlashHeaderWire_s McciBootloaderFlashHeaderWire_t;
typedef struct McciBootloaderFlashBucketWire_s McciBootloaderFlashBucketWire_t;
typedef struct McciBootloaderFlashBucketEntryLongWire_s McciBootloaderFlashBucketEntryLongWire_t;
typedef struct McciBootloaderFlashBucketEntryShortWire_s McciBootloaderFlashBucketEntryShortWire_t;

/*
|| An LSL medium is identified via a header in each sheaf that 
|| identifies:
||
|| 1) itself
|| 2) the logical layout of the medium (sheaf [cylinder] size, 
||    sheet [track] size, total size -- this must match the
||    overall size of the medium, which we assume the lower-level
||    driver can tell us.
|| 3) a pointer to the BTREE root as of the time the header was written.
|| 
|| Any LSL sheaf (cylinder) without a valid header is assumed to be
|| invalid and partially erased; the scavenger will attempt to erase
|| and reuse it.
||
|| The on-disk structure is defined with UINT8s, for portability.
*/

/* here are some fundamental constants */
#define	MCCI_BOOTLOADER_LSL_LG2BKTSIZE	        9		/* 512-byte buckets */
#define	MCCI_BOOTLOADER_LSL_BKTSIZE	        (1u << MCCI_BOOTLOADER_LSL_LG2BKTSIZE)

#define MCCI_BOOTLOADER_LSLTAG_SIZE	        4u		/* 4-bytes per LSL tag */
#define	MCCI_BOOTLOADER_LSLTAG_SHORT_SIZE       2u		/* 2-bytes per short LSL tag */

#define	MCCI_BOOTLOADER_LSLSHEAFTAG	        UINT32_C(0x970811CD)	/* signature */

#define MCCI_BOOTLOADER_LSLVERSION_CURRENT	0x10		/* version number */
#define MCCI_BOOTLOADER_LSLVERSION_COMPAT(mVers, ourVers) (((mVers) & 0xF0) <= (ourVers))

#define MCCI_BOOTLOADER_LSLUINT32_SIZE          UINT32_C(4)	/* 4 bytes for that */

#define MCCI_BOOTLOADER_LSLUINT64_SIZE	        UINT32_C(64 / 8)	/* 8 bytes for 64 bits */
#define	MCCI_BOOTLOADER_LSLROOTGEN_SIZE	        MCCI_BOOTLOADER_LSLUINT64_SIZE		/* root generation -- 2^64
                                                                                        || is so large that it
                                                                                        || cannot conceivably 
                                                                                        || roll over.
                                                                                        */

/****************************************************************************\
|
|	A flash device is modelled as one or more erase units, which are
|       grouped together into "sheafs" (as in a sheaf of pages of paper).
|       Sheafs are treated as logical units. For small flash, we normally
|       use a sheaf size of 32k or 64k. Since the bootloader is not writing,
|       it just follows whatever it finds on the media. Each sheaf begins
|       with a header, shown below.
|
|       Sheaf headers are not updated in place, so generally speaking
|       when a sheaf header is written, the writer reserves a second (block)
|       sector where updated header can be written, and leaves a pointer in
|       lslsheaf_tNexthdr. An LSL tag is 32 bits, and addresses a 512-byte
|       unit; therefore this format supports up to 2^41 bytes of addressible
|       media (2T).
|
\****************************************************************************/

struct McciBootloaderFlashHeaderWire_s 
	{
	uint8_t	lslsheaf_ulSig[MCCI_BOOTLOADER_LSLUINT32_SIZE];		/* 0: the signature of a sheaf header */
	uint8_t	lslsheaf_ulLslid[MCCI_BOOTLOADER_LSLUINT32_SIZE];	/* 4: the signature of this lsl instance */
	uint8_t	lslsheaf_uqRootgen[MCCI_BOOTLOADER_LSLUINT64_SIZE];	/* 8: the root generation count */
	uint8_t	lslsheaf_uqPbnTotal[MCCI_BOOTLOADER_LSLUINT64_SIZE];	/* 10: the raw media size */

	uint8_t	lslsheaf_ulSheafsize[MCCI_BOOTLOADER_LSLUINT32_SIZE];   /* 18: the size of each sheaf on this
                                                                        || device, in bytes.
                                                                        */

	uint8_t	lslsheaf_ucLslvers;	                                /* 1C: the lsl version bcd (x.y) */
	uint8_t	lslsheaf_ucTagsize;	                                /* 1D: bytes per tag on the media */
	uint8_t	lslsheaf_ucLensize;	                                /* 1E: bytes per length element */
	uint8_t	lslsheaf_ucNumLog;	                                /* 1F: number of log entries */

	uint8_t	lslsheaf_tSelf[MCCI_BOOTLOADER_LSLTAG_SIZE];	        /* 20: pointer to self */
	uint8_t	lslsheaf_tRoot[MCCI_BOOTLOADER_LSLTAG_SIZE];	        /* 24: the tag of the root
						                        || when this block was
						                        || written
						                        */

	uint8_t	lslsheaf_tNexthdr[MCCI_BOOTLOADER_LSLTAG_SIZE];         /* 28: tag of next header in this sheaf */
						                        /* zero if none */

	uint8_t	lslsheaf_tLogBase[MCCI_BOOTLOADER_LSLTAG_SIZE];	        /* 2c: tag of base PBN for log */
	uint8_t	lslsheaf_uqLbnTotal[MCCI_BOOTLOADER_LSLUINT64_SIZE];    /* 30: largest LBN */

	uint8_t	lslsheaf_ucLg2BktSize;		                        /* 38: log2 of blk size */

        /* reserved space */
	uint8_t	lslsheaf_ucRsv39[3];		                        /* 39..3b:  reserved */
	uint8_t	lslsheaf_ulRsv3c[MCCI_BOOTLOADER_LSLUINT32_SIZE];
	uint8_t	lslsheaf_ulRsv40[MCCI_BOOTLOADER_LSLUINT32_SIZE];
	uint8_t	lslsheaf_ulRsv44[MCCI_BOOTLOADER_LSLUINT32_SIZE];
	uint8_t	lslsheaf_ulRsv48[MCCI_BOOTLOADER_LSLUINT32_SIZE];
	uint8_t	lslsheaf_ulRsv4c[MCCI_BOOTLOADER_LSLUINT32_SIZE];
	uint8_t	lslsheaf_ulRsv50[MCCI_BOOTLOADER_LSLUINT32_SIZE];
	uint8_t	lslsheaf_ulRsv54[MCCI_BOOTLOADER_LSLUINT32_SIZE];
	uint8_t	lslsheaf_ulRsv58[MCCI_BOOTLOADER_LSLUINT32_SIZE];

/* size of the log buffer */
#define	MCCI_BOOTLOADER_LSLDATA_SHEAF_LOGSIZE	(0x1FC - 0x5C)	        /* 416 bytes */

	uint8_t	lslsheaf_log[MCCI_BOOTLOADER_LSLDATA_SHEAF_LOGSIZE];    /* 0x60..0x1FB -- the log */
	uint8_t	lslsheaf_crc32[4];                        		/* the CRC */
	};

/* fields within a log entry -- use SHORT if tagsize is 2, LONG otherwise */
#define	MCCI_BOOTLOADER_LSLSHEAF_LOGENTRY_SHORT_usLbn	0	/* the base LBN */
#define	MCCI_BOOTLOADER_LSLSHEAF_LOGENTRY_SHORT_ucNlbn	2	/* the count of LBNs */
#define	MCCI_BOOTLOADER_LSLSHEAF_LOGENTRY_SHORT_SIZE	3	/* the size of this struct */

#define	MCCI_BOOTLOADER_LSLSHEAF_LOGENTRY_LONG_ulLbn	0	/* the base LBN */
#define	MCCI_BOOTLOADER_LSLSHEAF_LOGENTRY_LONG_usNlbn	4	/* the count of LBNs */
#define	MCCI_BOOTLOADER_LSLSHEAF_LOGENTRY_LONG_SIZE	6	/* the size of an entry */

/* an LSL bt bucket this is equivalent to the btree.h definition */
struct McciBootloaderFlashBucketWire_s
	{
	uint8_t	lslbucket_nc[2];	/* count of bytes in the bucket */
	uint8_t	lslbucket_right[MCCI_BOOTLOADER_LSLTAG_SIZE];
					/* right-pointing tag */
	uint8_t	lslbucket_height;	/* the height of this bucket,
					|| and the "isroot flag"
					*/
	uint8_t	lslbucket_spare;	/* the spare field */
	};

/* a Btree entry using long tags */
struct	McciBootloaderFlashBucketEntryLongWire_s
	{
	uint8_t	lslrec_base[MCCI_BOOTLOADER_LSLTAG_SIZE];	/* the base Disk block num */
	uint8_t	lslrec_len[MCCI_BOOTLOADER_LSLTAG_SIZE];	/* the number of blocks */
	uint8_t	lslrec_phys[MCCI_BOOTLOADER_LSLTAG_SIZE];	/* the base physical addr */
	};
         
/* a Btree entry using short tags */
struct	__LSLBTBUCKET_RECORD_SHORT
	{
	uint8_t	lslrec_base[MCCI_BOOTLOADER_LSLTAG_SHORT_SIZE];	/* the base Disk block num */
	uint8_t	lslrec_len[MCCI_BOOTLOADER_LSLTAG_SHORT_SIZE];	/* the number of blocks */
	uint8_t	lslrec_phys[MCCI_BOOTLOADER_LSLTAG_SHORT_SIZE];	/* the base physical addr */
	};

MCCIADK_END_DECLS
#endif /* _MCCI_BOOTLOADER_FORMATS_H_ */