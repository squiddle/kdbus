/*
 * Copyright (C) 2013-2014 Kay Sievers
 * Copyright (C) 2013-2014 Greg Kroah-Hartman <gregkh@linuxfoundation.org>
 * Copyright (C) 2013-2014 Daniel Mack <daniel@zonque.org>
 * Copyright (C) 2013-2014 Linux Foundation
 *
 * kdbus is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 */

#ifndef __KDBUS_METADATA_H
#define __KDBUS_METADATA_H

/**
 * struct kdbus_meta - metadata buffer
 * @attached:		Flags for already attached data
 * @domain:		Domain the metadata belongs to
 * @data:		Allocated buffer
 * @size:		Number of bytes used
 * @allocated_size:	Size of buffer
 * @creds_item_off	The offset of the creds item in the @data
 *			buffer field, if the user requested this
 *			metainfo in its attach flags. 0 if unused.
 * @auxgrps_item_off	The offset of the auxgroups item in the
 *			@data buffer field, if the user requested
 *			this metainfo. 0 if unused.
 * @audit_item_off	The offset of the audit item in the @data
 *			buffer field, if the user requested this
 *			metainfo. 0 if unused.
 *
 * Used to collect and store connection metadata in a pre-compiled
 * buffer containing struct kdbus_item.
 */
struct kdbus_meta {
	u64 attached;
	const struct pid_namespace *domain;
	struct kdbus_item *data;
	size_t size;
	size_t allocated_size;

	off_t creds_item_off;
	off_t auxgrps_item_off;
	off_t audit_item_off;
};

struct kdbus_conn;

int kdbus_meta_new(struct kdbus_meta **meta);
int kdbus_meta_append_data(struct kdbus_meta *meta, u64 type,
			   const void *buf, size_t len);
int kdbus_meta_append(struct kdbus_meta *meta,
		      struct kdbus_conn *conn,
		      u64 seq,
		      u64 which);
void kdbus_meta_free(struct kdbus_meta *meta);
#endif
