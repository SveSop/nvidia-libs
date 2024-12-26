/*
 * Copyright (C) 2014-2015 Michael Müller
 * Copyright (C) 2023-2024 Sveinar Søpler
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_NVCUDA_H
#define __WINE_NVCUDA_H

#include "windef.h"
#include "winbase.h"
#include "cuda.h"

void __attribute((visibility("hidden"))) cuda_process_tls_callbacks(DWORD reason);
CUresult __attribute((visibility("hidden"))) cuda_get_table(const void **table, const CUuuid *uuid, const void *orig_table, CUresult orig_result);
int __attribute((visibility("hidden"))) get_shared_resource_fd(HANDLE win32_handle);
HANDLE __attribute((visibility("hidden"))) open_shared_resource(HANDLE kmt_handle, LPCWSTR name);

#endif
