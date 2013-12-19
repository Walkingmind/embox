/**
 * @file
 * @brief
 *
 * @date 20.08.2012
 * @author Andrey Gazukin
 */


#ifndef ISO9660_H_
#define ISO9660_H_


/*
 * iso9660.h
 *
 * ISO-9660 CD-ROM file system definitions
 *
 * Copyright (C) 2002 Michael Ringgaard. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/stat.h>
#include <fs/vfs.h>

#define ISO_VD_BOOT         0
#define ISO_VD_PRIMARY      1
#define ISO_VD_SUPPLEMENTAL 2
#define ISO_VD_PARTITION    3
#define ISO_VD_END          255

#define CDFS_BLOCKSIZE         2048
#define CDFS_POOLDEPTH         10

#define PS1                     '/'     /* Primary path separator */
#define PS2                     '\\'    /* Alternate path separator */

#define F_DIR                   0x200000  /* File is a directory */

#define __int64 long long
typedef __int64 off64_t;

#define ISODCL(from, to) (to - from + 1)

#pragma pack(push, 1)

typedef struct iso_volume_descriptor {
  unsigned char type                    [ISODCL(  1,   1)]; /* 711 */
  unsigned char id                      [ISODCL(  2,   6)];
  unsigned char version                 [ISODCL(  7,   7)]; /* 711 */
  unsigned char flags                   [ISODCL(  8,   8)];
  unsigned char system_id               [ISODCL(  9,  40)]; /* achars */
  unsigned char volume_id               [ISODCL( 41,  72)]; /* dchars */
  unsigned char unused1                 [ISODCL( 73,  80)];
  unsigned char volume_space_size       [ISODCL( 81,  88)]; /* 733 */
  unsigned char escape_sequences        [ISODCL( 89, 120)];
  unsigned char volume_set_size         [ISODCL(121, 124)]; /* 723 */
  unsigned char volume_sequence_number  [ISODCL(125, 128)]; /* 723 */
  unsigned char logical_block_size      [ISODCL(129, 132)]; /* 723 */
  unsigned char path_table_size         [ISODCL(133, 140)]; /* 733 */
  unsigned char type_l_path_table       [ISODCL(141, 144)]; /* 731 */
  unsigned char opt_type_l_path_table   [ISODCL(145, 148)]; /* 731 */
  unsigned char type_m_path_table       [ISODCL(149, 152)]; /* 732 */
  unsigned char opt_type_m_path_table   [ISODCL(153, 156)]; /* 732 */
  unsigned char root_directory_record   [ISODCL(157, 190)]; /* 9.1 */
  unsigned char volume_set_id           [ISODCL(191, 318)]; /* dchars */
  unsigned char publisher_id            [ISODCL(319, 446)]; /* achars */
  unsigned char preparer_id             [ISODCL(447, 574)]; /* achars */
  unsigned char application_id          [ISODCL(575, 702)]; /* achars */
  unsigned char copyright_file_id       [ISODCL(703, 739)]; /* 7.5 dchars */
  unsigned char abstract_file_id        [ISODCL(740, 776)]; /* 7.5 dchars */
  unsigned char bibliographic_file_id   [ISODCL(777, 813)]; /* 7.5 dchars */
  unsigned char creation_date           [ISODCL(814, 830)]; /* 8.4.26.1 */
  unsigned char modification_date       [ISODCL(831, 847)]; /* 8.4.26.1 */
  unsigned char expiration_date         [ISODCL(848, 864)]; /* 8.4.26.1 */
  unsigned char effective_date          [ISODCL(865, 881)]; /* 8.4.26.1 */
  unsigned char file_structure_version  [ISODCL(882, 882)]; /* 711 */
  unsigned char unused2                 [ISODCL(883, 883)];
  unsigned char application_data        [ISODCL(884, 1395)];
  unsigned char unused3                 [ISODCL(1396, 2048)];
} iso_volume_descriptor_t;

typedef struct iso_directory_record {
  unsigned char length                  [ISODCL( 1,  1)]; /* 711 */
  unsigned char ext_attr_length         [ISODCL( 2,  2)]; /* 711 */
  unsigned char extent                  [ISODCL( 3, 10)]; /* 733 */
  unsigned char size                    [ISODCL(11, 18)]; /* 733 */
  unsigned char date                    [ISODCL(19, 25)]; /* 7 by 711 */
  unsigned char flags                   [ISODCL(26, 26)];
  unsigned char file_unit_size          [ISODCL(27, 27)]; /* 711 */
  unsigned char interleave              [ISODCL(28, 28)]; /* 711 */
  unsigned char volume_sequence_number  [ISODCL(29, 32)]; /* 723 */
  unsigned char name_len                [ISODCL(33, 33)]; /* 711 */
  unsigned char name                    [0];
} iso_directory_record_t;

typedef struct iso_extended_attributes {
  unsigned char owner                   [ISODCL(  1,   4)]; /* 723 */
  unsigned char group                   [ISODCL(  5,   8)]; /* 723 */
  unsigned char perm                    [ISODCL(  9,  10)]; /* 9.5.3 */
  unsigned char ctime                   [ISODCL( 11,  27)]; /* 8.4.26.1 */
  unsigned char mtime                   [ISODCL( 28,  44)]; /* 8.4.26.1 */
  unsigned char xtime                   [ISODCL( 45,  61)]; /* 8.4.26.1 */
  unsigned char ftime                   [ISODCL( 62,  78)]; /* 8.4.26.1 */
  unsigned char recfmt                  [ISODCL( 79,  79)]; /* 711 */
  unsigned char recattr                 [ISODCL( 80,  80)]; /* 711 */
  unsigned char reclen                  [ISODCL( 81,  84)]; /* 723 */
  unsigned char system_id               [ISODCL( 85, 116)]; /* achars */
  unsigned char system_use              [ISODCL(117, 180)];
  unsigned char version                 [ISODCL(181, 181)]; /* 711 */
  unsigned char len_esc                 [ISODCL(182, 182)]; /* 711 */
  unsigned char reserved                [ISODCL(183, 246)];
  unsigned char len_au                  [ISODCL(247, 250)]; /* 723 */
} iso_extended_attributes_t;

typedef struct iso_pathtable_record {
  unsigned char length;
  unsigned char ext_attr_length;
  unsigned long extent;
  unsigned short int parent;
  char name[0];
} iso_pathtable_record_t;

#pragma pack(pop)

typedef struct cdfs {
	void *bdev;
	int blks;
	int volblks;
	int vdblk;
	int joliet;
	unsigned char *path_table_buffer;
	struct iso_pathtable_record **path_table;
	int path_table_records;
} cdfs_t;

typedef struct cdfs_fs_info {
	struct fsops *ops;
	char mntto[PATH_MAX];
	void *data;
} cdfs_fs_info_t;

typedef struct cdfs_file_info {
	int flags;
	off64_t pos;
	int extent;
	int size;
	time_t date;
} cdfs_file_info_t;

#endif /* ISO9660_H_ */