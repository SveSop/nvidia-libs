/*
 * Copyright (C) 2024 Sveinar Søpler
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

#ifndef __WINE_CUFFT_H
#define __WINE_CUFFT_H

typedef enum cufftResult_t {
  CUFFT_SUCCESS                   = 0x0,
  CUFFT_INVALID_PLAN              = 0x1,
  CUFFT_ALLOC_FAILED              = 0x2,
  CUFFT_INVALID_TYPE              = 0x3,
  CUFFT_INVALID_VALUE             = 0x4,
  CUFFT_INTERNAL_ERROR            = 0x5,
  CUFFT_EXEC_FAILED               = 0x6,
  CUFFT_SETUP_FAILED              = 0x7,
  CUFFT_INVALID_SIZE              = 0x8,
  CUFFT_UNALIGNED_DATA            = 0x9,
  CUFFT_INCOMPLETE_PARAMETER_LIST = 0xA,
  CUFFT_INVALID_DEVICE            = 0xB,
  CUFFT_PARSE_ERROR               = 0xC,
  CUFFT_NO_WORKSPACE              = 0xD,
  CUFFT_NOT_IMPLEMENTED           = 0xE,
  CUFFT_LICENSE_ERROR             = 0x0F,
  CUFFT_NOT_SUPPORTED             = 0x10,
} cufftResult;

#endif // __WINE_CUFFT_H
