/*
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

#ifndef __FUNCTION_MAPPINGS_H
#define __FUNCTION_MAPPINGS_H

#include <stddef.h>

typedef void (*FunctionPtr)(void);

typedef struct {
    const char* symbol;
    int minVersion;
    size_t flags;
    FunctionPtr function;
} FunctionMapping;

extern const __attribute((visibility("hidden"))) FunctionMapping mappings[];
extern const __attribute((visibility("hidden"))) size_t mappings_count;

#endif  /* __FUNCTION_MAPPINGS_H */
