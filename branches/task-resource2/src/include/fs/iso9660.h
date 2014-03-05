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

#include <stdint.h>
#include <fs/iso9660_format.h>

typedef int64_t off64_t;


#define CDFS_BLOCKSIZE         2048
#define CDFS_POOLDEPTH         10

#define PS1                     '/'     /* Primary path separator */
#define PS2                     '\\'    /* Alternate path separator */


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
