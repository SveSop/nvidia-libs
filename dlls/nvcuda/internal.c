/*
 * Copyright (C) 2014-2015 Michael Müller
 * Copyright (C) 2014-2015 Sebastian Lackner
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

#include "config.h"
#include <dlfcn.h>
#include <stdarg.h>
#include <stdio.h>

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"
#include "wine/list.h"
#include "cuda.h"
#include "nvcuda.h"

WINE_DEFAULT_DEBUG_CHANNEL(nvcuda);

struct tls_callback_entry
{
    struct list entry;
    void (CDECL *callback)(DWORD, void *);
    void *userdata;
    ULONG count;
};

static struct list tls_callbacks = LIST_INIT( tls_callbacks );

static RTL_CRITICAL_SECTION tls_callback_section;
static RTL_CRITICAL_SECTION_DEBUG critsect_debug =
{
    0, 0, &tls_callback_section,
    { &critsect_debug.ProcessLocksList, &critsect_debug.ProcessLocksList },
      0, 0, { (DWORD_PTR)(__FILE__ ": tls_callback_section") }
};
static RTL_CRITICAL_SECTION tls_callback_section = { &critsect_debug, -1, 0, 0, 0, 0 };

void cuda_process_tls_callbacks(DWORD reason)
{
    struct list *ptr;

    TRACE("(%d)\n", reason);

    if (reason != DLL_THREAD_DETACH)
        return;

    EnterCriticalSection( &tls_callback_section );
    ptr = list_head( &tls_callbacks );
    while (ptr)
    {
        struct tls_callback_entry *callback = LIST_ENTRY( ptr, struct tls_callback_entry, entry );
        callback->count++;

        TRACE("calling handler %p(0, %p)\n", callback->callback, callback->userdata);
        callback->callback(0, callback->userdata);
        TRACE("handler %p returned\n", callback->callback);

        ptr = list_next( &tls_callbacks, ptr );
        if (!--callback->count)  /* removed during execution */
        {
            list_remove( &callback->entry );
            HeapFree( GetProcessHeap(), 0, callback );
        }
    }
    LeaveCriticalSection( &tls_callback_section );
}

static const CUuuid UUID_Unknown1                   = {{0x6B, 0xD5, 0xFB, 0x6C, 0x5B, 0xF4, 0xE7, 0x4A,
                                                        0x89, 0x87, 0xD9, 0x39, 0x12, 0xFD, 0x9D, 0xF9}};
                                                    // {6Bd5fB6c-5Bf4-e74A-8987-d93912fd9df9}
static const CUuuid UUID_Unknown2                   = {{0xA0, 0x94, 0x79, 0x8C, 0x2E, 0x74, 0x2E, 0x74,
                                                        0x93, 0xF2, 0x08, 0x00, 0x20, 0x0C, 0x0A, 0x66}};
                                                    // {a094798c-2e74-2e74-93f2-0800200c0a66}
static const CUuuid UUID_Unknown3                   = {{0x42, 0xD8, 0x5A, 0x81, 0x23, 0xF6, 0xCB, 0x47,
                                                        0x82, 0x98, 0xF6, 0xE7, 0x8A, 0x3A, 0xEC, 0xDC}};
                                                    // {42d85a81-23f6-cb47-8298-f6e78a3aecdc}
static const CUuuid UUID_ContextStorage             = {{0xC6, 0x93, 0x33, 0x6E, 0x11, 0x21, 0xDF, 0x11,
                                                        0xA8, 0xC3, 0x68, 0xF3, 0x55, 0xD8, 0x95, 0x93}};
                                                    // {c693336e-1121-df11-a8c3-68f355d89593}
static const CUuuid UUID_Unknown5                   = {{0x0C, 0xA5, 0x0B, 0x8C, 0x10, 0x04, 0x92, 0x9A,
                                                        0x89, 0xA7, 0xD0, 0xDF, 0x10, 0xE7, 0x72, 0x86}};
                                                    // {0ca50b8c-1004-929a-89a7-f0ff10e77286}
static const CUuuid UUID_TlsNotifyInterface         = {{0x19, 0x5B, 0xCB, 0xF4, 0xD6, 0x7D, 0x02, 0x4A,
                                                        0xAC, 0xC5, 0x1D, 0x29, 0xCE, 0xA6, 0x31, 0xAE}};
                                                    // {195bcbf4-d67d-024a-acc5-1d29cea631ae}
static const CUuuid UUID_Unknown7                   = {{0xD4, 0x08, 0x20, 0x55, 0xBD, 0xE6, 0x70, 0x4B,
                                                        0x8D, 0x34, 0xBA, 0x12, 0x3C, 0x66, 0xE1, 0xF2}};
                                                    // {d4082055-bde6-704b-8d34-ba123c66e1f2}
static const CUuuid UUID_Unknown8                   = {{0x21, 0x31, 0x8C, 0x60, 0x97, 0x14, 0x32, 0x48,
                                                        0x8C, 0xA6, 0x41, 0xFF, 0x73, 0x24, 0xC8, 0xF2}};
                                                    // {21318c60-9714-3248-8ca6-41ff7324c8f2}
static const CUuuid UUID_Unknown9                   = {{0x6E, 0x16, 0x3F, 0xBE, 0xB9, 0x58, 0x44, 0x4D,
                                                        0x83, 0x5C, 0xE1, 0x82, 0xAF, 0xF1, 0x99, 0x1E}};
                                                    // {6e163fbe-b958-444d-835c-e182aff1991e}
static const CUuuid UUID_Unknown10                  = {{0x26, 0x3E, 0x88, 0x60, 0x7C, 0xD2, 0x61, 0x43,
                                                        0x92, 0xF6, 0xBB, 0xD5, 0x00, 0x6D, 0xFA, 0x7E}};
                                                    // {263e8860-7cd2-6143-92f6-bbd5006dfa7e}

struct cuda_table
{
    int size;
    void *functions[0];
};

/*
 * Unknown1
 */
struct Unknown1_table
{
    int size;
    void* (WINAPI *func0)(void *param0, void *param1);
    void* (WINAPI *func1)(void *param0, void *param1);
    void* (WINAPI *func2)(void *param0, void *param1);
    void* (WINAPI *func3)(void *param0, void *param1);
    void* (WINAPI *func4)(void *param0);
    void* (WINAPI *func5)(void *param0, void *param1);
    void* (WINAPI *func6)(void *param0, void *param1);
    void* (WINAPI *func7)(void *param0, void *param1);
    void* (WINAPI *func8)(void *param0, void *param1);
    void* (WINAPI *func9)(void *param0, void *param1);
};
static const struct
{
    int size;
    void* (*func0)(void *param0, void *param1);
    void* (*func1)(void *param0, void *param1);
    void* (*func2)(void *param0, void *param1);
    void* (*func3)(void *param0, void *param1);
    void* (*func4)(void *param0);
    void* (*func5)(void *param0, void *param1);
    void* (*func6)(void *param0, void *param1);
    void* (*func7)(void *param0, void *param1);
    void* (*func8)(void *param0, void *param1);
    void* (*func9)(void *param0, void *param1);
} *Unknown1_orig = NULL;

/*
 * Unknown2
 */
struct Unknown2_table
{
    int size;
    void* (WINAPI *func0)(void *param0, void *param1);
    void* (WINAPI *func1)(void *param0, void *param1);
    void* (WINAPI *func2)(void *param0, void *param1, void *param2);
    void* (WINAPI *func3)(void *param0, void *param1);
    void* (WINAPI *func4)(void *param0, void *param1);
    void* (WINAPI *func5)(void *param0, void *param1);
};
static const struct
{
    int size;
    void* (*func0)(void *param0, void *param1);
    void* (*func1)(void *param0, void *param1);
    void* (*func2)(void *param0, void *param1, void *param2);
    void* (*func3)(void *param0, void *param1);
    void* (*func4)(void *param0, void *param1);
    void* (*func5)(void *param0, void *param1);
} *Unknown2_orig = NULL;

/*
 * Unknown3
 */
struct Unknown3_table
{
    int size;
    void* (WINAPI *func0)(void *param0);
    void* (WINAPI *func1)(void *param0);
};
static const struct
{
    int size;
    void* (*func0)(void *param0);
    void* (*func1)(void *param0);
} *Unknown3_orig = NULL;

/*
 * ContextStorage
 */
struct ContextStorage_table
{
    CUresult (WINAPI *Set)(CUcontext ctx, void *key, void *value, void *callback);
    CUresult (WINAPI *Remove)(CUcontext ctx, void *key);
    CUresult (WINAPI *Get)(void **value, CUcontext ctx, void *key);
};
static const struct
{
    CUresult (*Set)(CUcontext ctx, void *key, void *value, void *callback);
    CUresult (*Remove)(CUcontext ctx, void *key);
    CUresult (*Get)(void **value, CUcontext ctx, void *key);
} *ContextStorage_orig = NULL;

/*
 * Unknown5
 */
struct Unknown5_table
{
    int size;
    void* (WINAPI *func0)(void *param0, void *param1, void *param2);
};
static const struct
{
    int size;
    void* (*func0)(void *param0, void *param1, void *param2);
} *Unknown5_orig = NULL;


/*
 * TlsNotifyInterface
 */
struct TlsNotifyInterface_table
{
    int size;
    CUresult (WINAPI *Set)(void **handle, void *callback, void *data);
    CUresult (WINAPI *Remove)(void *handle, void *param1);
};

/*
 * Unknown7
 */
struct Unknown7_table
{
    int size;
    void* (WINAPI *func0)(unsigned int cudaVersion, void *param1, void *param2);
    void* (WINAPI *func1)(void *param0);
};
static const struct
{
    int size;
    void* (*func0)(unsigned int cudaVersion, void *param1, void *param2);
    void* (*func1)(void *param0);
} *Unknown7_orig = NULL;

/*
 * Unknown8
 */
struct Unknown8_table
{
    int size;
    void* (WINAPI *func0)(void *param0, void *param1);
    void* (WINAPI *func1)(void *param0, void *param1);
    void* (WINAPI *func2)(void *param0, void *param1);
    void* (WINAPI *func3)(void *param0, void *param1);
    void* (WINAPI *func4)(void *param0, void *param1);
    void* (WINAPI *func5)(void *param0, void *param1);
    void* (WINAPI *func6)(void *param0, void *param1);
    void* (WINAPI *func7)(void *param0, void *param1);
    void* (WINAPI *func8)(void *param0, void *param1);
    void* (WINAPI *func9)(void *param0, void *param1);
    void* (WINAPI *func10)(void *param0, void *param1);
    void* (WINAPI *func11)(void *param0, void *param1);
    void* (WINAPI *func12)(void *param0, void *param1);
    void* (WINAPI *func13)(void *param0, void *param1);
    void* (WINAPI *func14)(void *param0, void *param1);
    void* (WINAPI *func15)(void *param0, void *param1);
    void* (WINAPI *func16)(void *param0, void *param1);
    void* (WINAPI *func17)(void *param0, void *param1);
    void* (WINAPI *func18)(void *param0, void *param1);
    void* (WINAPI *func19)(void *param0, void *param1);
    void* (WINAPI *func20)(void *param0, void *param1);
    void* (WINAPI *func21)(void *param0, void *param1);
    void* (WINAPI *func22)(void *param0, void *param1);
    void* (WINAPI *func23)(void *param0, void *param1);
    void* (WINAPI *func24)(void *param0, void *param1);
    void* (WINAPI *func25)(void *param0, void *param1);
    void* (WINAPI *func26)(void *param0, void *param1);
    void* (WINAPI *func27)(void *param0, void *param1);
    void* (WINAPI *func28)(void *param0, void *param1);
    void* (WINAPI *func29)(void *param0, void *param1);
    void* (WINAPI *func30)(void *param0, void *param1);
    void* (WINAPI *func31)(void *param0, void *param1);
    void* (WINAPI *func32)(void *param0, void *param1);
    void* (WINAPI *func33)(void *param0, void *param1);
    void* (WINAPI *func34)(void *param0, void *param1);
    void* (WINAPI *func35)(void *param0, void *param1);
    void* (WINAPI *func36)(void *param0, void *param1);
    void* (WINAPI *func37)(void *param0, void *param1);
    void* (WINAPI *func38)(void *param0, void *param1, void *param2);
    void* (WINAPI *func39)(void *param0, void *param1);
    void* (WINAPI *func40)(void *param0, void *param1);
    void* (WINAPI *func41)(void *param0, void *param1);
    void* (WINAPI *func42)(void *param0, void *param1);
    void* (WINAPI *func43)(void *param0, void *param1);
    void* (WINAPI *func44)(void *param0, void *param1);
    void* (WINAPI *func45)(void *param0, void *param1);
    void* (WINAPI *func46)(void *param0, void *param1);
    void* (WINAPI *func47)(void *param0, void *param1);
    void* (WINAPI *func48)(void *param0, void *param1);
    void* (WINAPI *func49)(void *param0, void *param1);
    void* (WINAPI *func50)(void *param0, void *param1, void *param2);
    void* (WINAPI *func51)(void *param0, void *param1);
    void* (WINAPI *func52)(void *param0, void *param1);
    void* (WINAPI *func53)(void *param0, void *param1);
    void* (WINAPI *func54)(void *param0, void *param1);
    void* (WINAPI *func55)(void *param0, void *param1);
    void* (WINAPI *func56)(void *param0, void *param1);
    void* (WINAPI *func57)(void *param0, void *param1);
    void* (WINAPI *func58)(void *param0, void *param1);
    void* (WINAPI *func59)(void *param0, void *param1);
    void* (WINAPI *func60)(void *param0, void *param1);
    void* (WINAPI *func61)(void *param0, void *param1);
    void* (WINAPI *func62)(void *param0, void *param1);
    void* (WINAPI *func63)(void *param0, void *param1);
    void* (WINAPI *func64)(void *param0, void *param1);
    void* (WINAPI *func65)(void *param0, void *param1);
    void* (WINAPI *func66)(void *param0, void *param1);
    void* (WINAPI *func67)(void *param0, void *param1);
    void* (WINAPI *func68)(void *param0, void *param1);
    void* (WINAPI *func69)(void *param0, void *param1);
    void* (WINAPI *func70)(void *param0, void *param1);
    void* (WINAPI *func71)(void *param0, void *param1);
    void* (WINAPI *func72)(void *param0, void *param1);
    void* (WINAPI *func73)(void *param0, void *param1);
    void* (WINAPI *func74)(void *param0, void *param1);
    void* (WINAPI *func75)(void *param0, void *param1);
    void* (WINAPI *func76)(void *param0, void *param1);
};
static const struct
{
    int size;
    void* (*func0)(void *param0, void *param1);
    void* (*func1)(void *param0, void *param1);
    void* (*func2)(void *param0, void *param1);
    void* (*func3)(void *param0, void *param1);
    void* (*func4)(void *param0, void *param1);
    void* (*func5)(void *param0, void *param1);
    void* (*func6)(void *param0, void *param1);
    void* (*func7)(void *param0, void *param1);
    void* (*func8)(void *param0, void *param1);
    void* (*func9)(void *param0, void *param1);
    void* (*func10)(void *param0, void *param1);
    void* (*func11)(void *param0, void *param1);
    void* (*func12)(void *param0, void *param1);
    void* (*func13)(void *param0, void *param1);
    void* (*func14)(void *param0, void *param1);
    void* (*func15)(void *param0, void *param1);
    void* (*func16)(void *param0, void *param1);
    void* (*func17)(void *param0, void *param1);
    void* (*func18)(void *param0, void *param1);
    void* (*func19)(void *param0, void *param1);
    void* (*func20)(void *param0, void *param1);
    void* (*func21)(void *param0, void *param1);
    void* (*func22)(void *param0, void *param1);
    void* (*func23)(void *param0, void *param1);
    void* (*func24)(void *param0, void *param1);
    void* (*func25)(void *param0, void *param1);
    void* (*func26)(void *param0, void *param1);
    void* (*func27)(void *param0, void *param1);
    void* (*func28)(void *param0, void *param1);
    void* (*func29)(void *param0, void *param1);
    void* (*func30)(void *param0, void *param1);
    void* (*func31)(void *param0, void *param1);
    void* (*func32)(void *param0, void *param1);
    void* (*func33)(void *param0, void *param1);
    void* (*func34)(void *param0, void *param1);
    void* (*func35)(void *param0, void *param1);
    void* (*func36)(void *param0, void *param1);
    void* (*func37)(void *param0, void *param1);
    void* (*func38)(void *param0, void *param1, void *param2);
    void* (*func39)(void *param0, void *param1);
    void* (*func40)(void *param0, void *param1);
    void* (*func41)(void *param0, void *param1);
    void* (*func42)(void *param0, void *param1);
    void* (*func43)(void *param0, void *param1);
    void* (*func44)(void *param0, void *param1);
    void* (*func45)(void *param0, void *param1);
    void* (*func46)(void *param0, void *param1);
    void* (*func47)(void *param0, void *param1);
    void* (*func48)(void *param0, void *param1);
    void* (*func49)(void *param0, void *param1);
    void* (*func50)(void *param0, void *param1, void *param2);
    void* (*func51)(void *param0, void *param1);
    void* (*func52)(void *param0, void *param1);
    void* (*func53)(void *param0, void *param1);
    void* (*func54)(void *param0, void *param1);
    void* (*func55)(void *param0, void *param1);
    void* (*func56)(void *param0, void *param1);
    void* (*func57)(void *param0, void *param1);
    void* (*func58)(void *param0, void *param1);
    void* (*func59)(void *param0, void *param1);
    void* (*func60)(void *param0, void *param1);
    void* (*func61)(void *param0, void *param1);
    void* (*func62)(void *param0, void *param1);
    void* (*func63)(void *param0, void *param1);
    void* (*func64)(void *param0, void *param1);
    void* (*func65)(void *param0, void *param1);
    void* (*func66)(void *param0, void *param1);
    void* (*func67)(void *param0, void *param1);
    void* (*func68)(void *param0, void *param1);
    void* (*func69)(void *param0, void *param1);
    void* (*func70)(void *param0, void *param1);
    void* (*func71)(void *param0, void *param1);
    void* (*func72)(void *param0, void *param1);
    void* (*func73)(void *param0, void *param1);
    void* (*func74)(void *param0, void *param1);
    void* (*func75)(void *param0, void *param1);
    void* (*func76)(void *param0, void *param1);
} *Unknown8_orig = NULL;

/*
 * Unknown9
 */
struct Unknown9_table
{
    int size;
    void* (WINAPI *func0)(void *param0, void *param1);
    void* (WINAPI *func1)(void *param0, void *param1);
    void* (WINAPI *func2)(void *param0, void *param1);
    void* (WINAPI *func3)(void *param0, void *param1);
    void* (WINAPI *func4)(void *param0, void *param1);
    void* (WINAPI *func5)(void *param0, void *param1);
    void* (WINAPI *func6)(void *param0, void *param1);
    void* (WINAPI *func7)(void *param0, void *param1);
    void* (WINAPI *func8)(void *param0, void *param1);
    void* (WINAPI *func9)(void *param0, void *param1);
    void* (WINAPI *func10)(void *param0, void *param1);
    void* (WINAPI *func11)(void *param0, void *param1);
    void* (WINAPI *func12)(void *param0, void *param1);
    void* (WINAPI *func13)(void *param0, void *param1);
    void* (WINAPI *func14)(void *param0, void *param1);
    void* (WINAPI *func15)(void *param0, void *param1);
    void* (WINAPI *func16)(void *param0, void *param1);
    void* (WINAPI *func17)(void *param0, void *param1);
    void* (WINAPI *func18)(void *param0, void *param1);
    void* (WINAPI *func19)(void *param0, void *param1);
    void* (WINAPI *func20)(void *param0, void *param1);
    void* (WINAPI *func21)(void *param0, void *param1);
    void* (WINAPI *func22)(void *param0, void *param1);
    void* (WINAPI *func23)(void *param0, void *param1);
    void* (WINAPI *func24)(void *param0, void *param1);
    void* (WINAPI *func25)(void *param0, void *param1);
    void* (WINAPI *func26)(void *param0, void *param1);
    void* (WINAPI *func27)(void *param0, void *param1);
    void* (WINAPI *func28)(void *param0, void *param1);
    void* (WINAPI *func29)(void *param0, void *param1);
    void* (WINAPI *func30)(void *param0, void *param1);
    void* (WINAPI *func31)(void *param0, void *param1);
    void* (WINAPI *func32)(void *param0, void *param1);
    void* (WINAPI *func33)(void *param0, void *param1);
    void* (WINAPI *func34)(void *param0, void *param1);
    void* (WINAPI *func35)(void *param0, void *param1);
    void* (WINAPI *func36)(void *param0, void *param1);
    void* (WINAPI *func37)(void *param0, void *param1);
    void* (WINAPI *func38)(void *param0, void *param1);
    void* (WINAPI *func39)(void *param0, void *param1);
    void* (WINAPI *func40)(void *param0, void *param1);
    void* (WINAPI *func41)(void *param0, void *param1);
    void* (WINAPI *func42)(void *param0, void *param1);
    void* (WINAPI *func43)(void *param0, void *param1);
    void* (WINAPI *func44)(void *param0, void *param1);
    void* (WINAPI *func45)(void *param0, void *param1);
    void* (WINAPI *func46)(void *param0, void *param1);
    void* (WINAPI *func47)(void *param0, void *param1);
    void* (WINAPI *func48)(void *param0, void *param1);
    void* (WINAPI *func49)(void *param0, void *param1);
    void* (WINAPI *func50)(void *param0, void *param1);
    void* (WINAPI *func51)(void *param0, void *param1);
    void* (WINAPI *func52)(void *param0, void *param1);
    void* (WINAPI *func53)(void *param0, void *param1);
    void* (WINAPI *func54)(void *param0, void *param1);
    void* (WINAPI *func55)(void *param0, void *param1);
    void* (WINAPI *func56)(void *param0, void *param1);
    void* (WINAPI *func57)(void *param0, void *param1);
    void* (WINAPI *func58)(void *param0, void *param1);
    void* (WINAPI *func59)(void *param0, void *param1);
    void* (WINAPI *func60)(void *param0, void *param1);
    void* (WINAPI *func61)(void *param0, void *param1);
    void* (WINAPI *func62)(void *param0, void *param1);
    void* (WINAPI *func63)(void *param0, void *param1);
    void* (WINAPI *func64)(void *param0, void *param1);
    void* (WINAPI *func65)(void *param0, void *param1);
    void* (WINAPI *func66)(void *param0, void *param1);
    void* (WINAPI *func67)(void *param0, void *param1);
    void* (WINAPI *func68)(void *param0, void *param1);
    void* (WINAPI *func69)(void *param0, void *param1);
    void* (WINAPI *func70)(void *param0, void *param1);
    void* (WINAPI *func71)(void *param0, void *param1);
    void* (WINAPI *func72)(void *param0, void *param1);
    void* (WINAPI *func73)(void *param0, void *param1);
    void* (WINAPI *func74)(void *param0, void *param1);
    void* (WINAPI *func75)(void *param0, void *param1);
    void* (WINAPI *func76)(void *param0, void *param1);
    void* (WINAPI *func77)(void *param0, void *param1);
    void* (WINAPI *func78)(void *param0, void *param1);
    void* (WINAPI *func79)(void *param0, void *param1);
    void* (WINAPI *func80)(void *param0, void *param1);
    void* (WINAPI *func81)(void *param0, void *param1);
    void* (WINAPI *func82)(void *param0, void *param1);
    void* (WINAPI *func83)(void *param0, void *param1);
    void* (WINAPI *func84)(void *param0, void *param1);
    void* (WINAPI *func85)(void *param0, void *param1);
    void* (WINAPI *func86)(void *param0, void *param1);
};
static const struct
{
    int size;
    void* (*func0)(void *param0, void *param1);
    void* (*func1)(void *param0, void *param1);
    void* (*func2)(void *param0, void *param1);
    void* (*func3)(void *param0, void *param1);
    void* (*func4)(void *param0, void *param1);
    void* (*func5)(void *param0, void *param1);
    void* (*func6)(void *param0, void *param1);
    void* (*func7)(void *param0, void *param1);
    void* (*func8)(void *param0, void *param1);
    void* (*func9)(void *param0, void *param1);
    void* (*func10)(void *param0, void *param1);
    void* (*func11)(void *param0, void *param1);
    void* (*func12)(void *param0, void *param1);
    void* (*func13)(void *param0, void *param1);
    void* (*func14)(void *param0, void *param1);
    void* (*func15)(void *param0, void *param1);
    void* (*func16)(void *param0, void *param1);
    void* (*func17)(void *param0, void *param1);
    void* (*func18)(void *param0, void *param1);
    void* (*func19)(void *param0, void *param1);
    void* (*func20)(void *param0, void *param1);
    void* (*func21)(void *param0, void *param1);
    void* (*func22)(void *param0, void *param1);
    void* (*func23)(void *param0, void *param1);
    void* (*func24)(void *param0, void *param1);
    void* (*func25)(void *param0, void *param1);
    void* (*func26)(void *param0, void *param1);
    void* (*func27)(void *param0, void *param1);
    void* (*func28)(void *param0, void *param1);
    void* (*func29)(void *param0, void *param1);
    void* (*func30)(void *param0, void *param1);
    void* (*func31)(void *param0, void *param1);
    void* (*func32)(void *param0, void *param1);
    void* (*func33)(void *param0, void *param1);
    void* (*func34)(void *param0, void *param1);
    void* (*func35)(void *param0, void *param1);
    void* (*func36)(void *param0, void *param1);
    void* (*func37)(void *param0, void *param1);
    void* (*func38)(void *param0, void *param1);
    void* (*func39)(void *param0, void *param1);
    void* (*func40)(void *param0, void *param1);
    void* (*func41)(void *param0, void *param1);
    void* (*func42)(void *param0, void *param1);
    void* (*func43)(void *param0, void *param1);
    void* (*func44)(void *param0, void *param1);
    void* (*func45)(void *param0, void *param1);
    void* (*func46)(void *param0, void *param1);
    void* (*func47)(void *param0, void *param1);
    void* (*func48)(void *param0, void *param1);
    void* (*func49)(void *param0, void *param1);
    void* (*func50)(void *param0, void *param1);
    void* (*func51)(void *param0, void *param1);
    void* (*func52)(void *param0, void *param1);
    void* (*func53)(void *param0, void *param1);
    void* (*func54)(void *param0, void *param1);
    void* (*func55)(void *param0, void *param1);
    void* (*func56)(void *param0, void *param1);
    void* (*func57)(void *param0, void *param1);
    void* (*func58)(void *param0, void *param1);
    void* (*func59)(void *param0, void *param1);
    void* (*func60)(void *param0, void *param1);
    void* (*func61)(void *param0, void *param1);
    void* (*func62)(void *param0, void *param1);
    void* (*func63)(void *param0, void *param1);
    void* (*func64)(void *param0, void *param1);
    void* (*func65)(void *param0, void *param1);
    void* (*func66)(void *param0, void *param1);
    void* (*func67)(void *param0, void *param1);
    void* (*func68)(void *param0, void *param1);
    void* (*func69)(void *param0, void *param1);
    void* (*func70)(void *param0, void *param1);
    void* (*func71)(void *param0, void *param1);
    void* (*func72)(void *param0, void *param1);
    void* (*func73)(void *param0, void *param1);
    void* (*func74)(void *param0, void *param1);
    void* (*func75)(void *param0, void *param1);
    void* (*func76)(void *param0, void *param1);
    void* (*func77)(void *param0, void *param1);
    void* (*func78)(void *param0, void *param1);
    void* (*func79)(void *param0, void *param1);
    void* (*func80)(void *param0, void *param1);
    void* (*func81)(void *param0, void *param1);
    void* (*func82)(void *param0, void *param1);
    void* (*func83)(void *param0, void *param1);
    void* (*func84)(void *param0, void *param1);
    void* (*func85)(void *param0, void *param1);
    void* (*func86)(void *param0, void *param1);
} *Unknown9_orig = NULL;

/*
 * Unknown10
 */
struct Unknown10_table
{
    int size;
    void* (WINAPI *func0)(void *param0);
    void* (WINAPI *func1)(void *param0, void *param1);
};
static const struct
{
    int size;
    void* (*func0)(void *param0);
    void* (*func1)(void *param0, void *param1);
} *Unknown10_orig = NULL;

static void* WINAPI Unknown1_func0_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown1_orig->func0(param0, param1);
}

static void* WINAPI Unknown1_func1_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown1_orig->func1(param0, param1);
}

static void* WINAPI Unknown1_func2_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown1_orig->func2(param0, param1);
}

static void* WINAPI Unknown1_func3_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown1_orig->func3(param0, param1);
}

static void* WINAPI Unknown1_func4_relay(void *param0)
{
    TRACE("(%p)\n", param0);
    return Unknown1_orig->func4(param0);
}

static void* WINAPI Unknown1_func5_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown1_orig->func5(param0, param1);
}

static void* WINAPI Unknown1_func6_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown1_orig->func6(param0, param1);
}

static void* WINAPI Unknown1_func7_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown1_orig->func7(param0, param1);
}

static void* WINAPI Unknown1_func8_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown1_orig->func8(param0, param1);
}

static void* WINAPI Unknown1_func9_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown1_orig->func9(param0, param1);
}

struct Unknown1_table Unknown1_Impl =
{
    sizeof(struct Unknown1_table),
    Unknown1_func0_relay,
    Unknown1_func1_relay,
    Unknown1_func2_relay,
    Unknown1_func3_relay,
    Unknown1_func4_relay,
    Unknown1_func5_relay,
    Unknown1_func6_relay,
    Unknown1_func7_relay,
    Unknown1_func8_relay,
    Unknown1_func9_relay,
};

static void* WINAPI Unknown2_func0_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown2_orig->func0(param0, param1);
}

static void* WINAPI Unknown2_func1_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown2_orig->func1(param0, param1);
}

static void* WINAPI Unknown2_func2_relay(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return Unknown2_orig->func2(param0, param1, param2);
}

static void* WINAPI Unknown2_func3_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown2_orig->func3(param0, param1);
}

static void* WINAPI Unknown2_func4_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown2_orig->func4(param0, param1);
}

static void* WINAPI Unknown2_func5_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown2_orig->func5(param0, param1);
}

struct Unknown2_table Unknown2_Impl =
{
    sizeof(struct Unknown2_table),
    Unknown2_func0_relay,
    Unknown2_func1_relay,
    Unknown2_func2_relay,
    Unknown2_func3_relay,
    Unknown2_func4_relay,
    Unknown2_func5_relay,
};

static void* WINAPI Unknown3_func0_relay(void *param0)
{
    TRACE("(%p)\n", param0);
    return Unknown3_orig->func0(param0);
}

static void* WINAPI Unknown3_func1_relay(void *param0)
{
    TRACE("(%p)\n", param0);
    return Unknown3_orig->func1(param0);
}

static struct Unknown3_table Unknown3_Impl =
{
    sizeof(struct Unknown3_table),
    Unknown3_func0_relay,
    Unknown3_func1_relay,
};

struct context_storage
{
    void *value;
    void (WINAPI *callback)(CUcontext ctx, void *key, void *value);
};

static void storage_destructor_callback(CUcontext ctx, void *key, void *value)
{
    struct context_storage *storage = value;

    TRACE("(%p, %p, %p)\n", ctx, key, value);

    if (storage->callback)
    {
        TRACE("calling destructor callback %p(%p, %p, %p)\n",
              storage->callback, ctx, key, storage->value);
        storage->callback(ctx, key, storage->value);
        TRACE("destructor callback %p returned\n", storage->callback);
    }

    HeapFree( GetProcessHeap(), 0, storage );
}

static CUresult WINAPI ContextStorage_Set(CUcontext ctx, void *key, void *value, void *callback)
{
    struct context_storage *storage;
    CUresult ret;

    TRACE("(%p, %p, %p, %p)\n", ctx, key, value, callback);

    storage = HeapAlloc( GetProcessHeap(), 0, sizeof(*storage) );
    if (!storage)
        return CUDA_ERROR_OUT_OF_MEMORY;

    storage->callback = callback;
    storage->value = value;

    ret = ContextStorage_orig->Set(ctx, key, storage, storage_destructor_callback);
    if (ret) HeapFree( GetProcessHeap(), 0, storage );
    return ret;
}

static CUresult WINAPI ContextStorage_Remove(CUcontext ctx, void *key)
{
    struct context_storage *storage;

    TRACE("(%p, %p)\n", ctx, key);

    /* FIXME: This is not completely race-condition save, but using a mutex
     * could have a relatively big overhead. Can still be added later when it
     * turns out to be necessary. */
    if (!ContextStorage_orig->Get((void **)&storage, ctx, key))
        HeapFree( GetProcessHeap(), 0, storage );

    return ContextStorage_orig->Remove(ctx, key);
}

static CUresult WINAPI ContextStorage_Get(void **value, CUcontext ctx, void *key)
{
    struct context_storage *storage;
    CUresult ret;

    TRACE("(%p, %p, %p)\n", value, ctx, key);

    ret = ContextStorage_orig->Get((void **)&storage, ctx, key);
    if (!ret) *value = storage->value;
    return ret;
}

struct ContextStorage_table ContextStorage_Impl =
{
    ContextStorage_Set,
    ContextStorage_Remove,
    ContextStorage_Get,
};

static void* WINAPI Unknown5_func0_relay(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return Unknown5_orig->func0(param0, param1, param2);
}

struct Unknown5_table Unknown5_Impl =
{
    sizeof(struct Unknown5_table),
    Unknown5_func0_relay,
};

static CUresult WINAPI TlsNotifyInterface_Set(void **handle, void *callback, void *userdata)
{
    struct tls_callback_entry *new_entry;

    TRACE("(%p, %p, %p)\n", handle, callback, userdata);

    new_entry = HeapAlloc( GetProcessHeap(), 0, sizeof(*new_entry) );
    if (!new_entry)
        return CUDA_ERROR_OUT_OF_MEMORY;

    new_entry->callback = callback;
    new_entry->userdata = userdata;
    new_entry->count = 1;

    EnterCriticalSection( &tls_callback_section );
    list_add_tail( &tls_callbacks, &new_entry->entry );
    LeaveCriticalSection( &tls_callback_section );

    *handle = new_entry;
    return CUDA_SUCCESS;
}

static CUresult WINAPI TlsNotifyInterface_Remove(void *handle, void *param1)
{
    CUresult ret = CUDA_ERROR_INVALID_VALUE;
    struct tls_callback_entry *to_free = NULL;
    struct list *ptr;

    TRACE("(%p, %p)\n", handle, param1);

    if (param1)
        FIXME("semi stub: param1 != 0 not supported.\n");

    EnterCriticalSection( &tls_callback_section );
    LIST_FOR_EACH( ptr, &tls_callbacks )
    {
        struct tls_callback_entry *callback = LIST_ENTRY( ptr, struct tls_callback_entry, entry );
        if (callback == handle)
        {
            if (!--callback->count)
            {
                list_remove( ptr );
                to_free = callback;
            }
            ret = CUDA_SUCCESS;
            break;
        }
    }
    LeaveCriticalSection( &tls_callback_section );
    HeapFree( GetProcessHeap(), 0, to_free );
    return ret;
}

struct TlsNotifyInterface_table TlsNotifyInterface_Impl =
{
    sizeof(struct TlsNotifyInterface_table),
    TlsNotifyInterface_Set,
    TlsNotifyInterface_Remove,
};

static void* WINAPI Unknown7_func0_relay(unsigned int cudaVersion, void *param1, void *param2)
{
    TRACE("(%u, %p, %p)\n", cudaVersion, param1, param2);

    // After CUDA SDK 11.6 some checks is done by the CudaRuntimeLibrary (CudaRT)
    // This fails for some reason when using wine, so this is somewhat of a hack
    // altering the return address to skip this check.
    void *retAddr = (char *)__builtin_frame_address(0) + 0x8;
    if(cudaVersion >= 12000)
    {
        FIXME("Cuda Version >= 12.x detected! Workaround implemented\n");
        *((long int*)retAddr) += 0x76;
    }
    else if(cudaVersion >= 11070)
    {
        FIXME("Cuda Version 11.7 or 11.8 detected! Workaround implemented\n");
        *((long int*)retAddr) += 0x1b7;
    }
    else if(cudaVersion >= 11060)
    {
        FIXME("Cuda Version 11.6 detected! Workaround implemented\n");
        *((long int*)retAddr) += 0x1ca;
    }
    return Unknown7_orig->func0(cudaVersion, param1, param2);
}

static void* WINAPI Unknown7_func1_relay(void *param0)
{
    TRACE("(%p)\n", param0);
    return Unknown7_orig->func1(param0);
}

struct Unknown7_table Unknown7_Impl =
{
    sizeof(struct Unknown7_table),
    Unknown7_func0_relay,
    Unknown7_func1_relay,
};

static void* WINAPI Unknown8_func0_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func0(param0, param1);
}

static void* WINAPI Unknown8_func1_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func1(param0, param1);
}

static void* WINAPI Unknown8_func2_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func2(param0, param1);
}

static void* WINAPI Unknown8_func3_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func3(param0, param1);
}

static void* WINAPI Unknown8_func4_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func4(param0, param1);
}

static void* WINAPI Unknown8_func5_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func5(param0, param1);
}

static void* WINAPI Unknown8_func6_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func6(param0, param1);
}

static void* WINAPI Unknown8_func7_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func7(param0, param1);
}

static void* WINAPI Unknown8_func8_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func8(param0, param1);
}

static void* WINAPI Unknown8_func9_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func9(param0, param1);
}

static void* WINAPI Unknown8_func10_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func10(param0, param1);
}

static void* WINAPI Unknown8_func11_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func11(param0, param1);
}

static void* WINAPI Unknown8_func12_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func12(param0, param1);
}

static void* WINAPI Unknown8_func13_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func13(param0, param1);
}

static void* WINAPI Unknown8_func14_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func14(param0, param1);
}

static void* WINAPI Unknown8_func15_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func15(param0, param1);
}

static void* WINAPI Unknown8_func16_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func16(param0, param1);
}

static void* WINAPI Unknown8_func17_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func17(param0, param1);
}

static void* WINAPI Unknown8_func18_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func18(param0, param1);
}

static void* WINAPI Unknown8_func19_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func19(param0, param1);
}

static void* WINAPI Unknown8_func20_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func20(param0, param1);
}

static void* WINAPI Unknown8_func21_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func21(param0, param1);
}

static void* WINAPI Unknown8_func22_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func22(param0, param1);
}

static void* WINAPI Unknown8_func23_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func23(param0, param1);
}

static void* WINAPI Unknown8_func24_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func24(param0, param1);
}

static void* WINAPI Unknown8_func25_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func25(param0, param1);
}

static void* WINAPI Unknown8_func26_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func26(param0, param1);
}

static void* WINAPI Unknown8_func27_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func27(param0, param1);
}

static void* WINAPI Unknown8_func28_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func28(param0, param1);
}

static void* WINAPI Unknown8_func29_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func29(param0, param1);
}

static void* WINAPI Unknown8_func30_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func30(param0, param1);
}

static void* WINAPI Unknown8_func31_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func31(param0, param1);
}

static void* WINAPI Unknown8_func32_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func32(param0, param1);
}

static void* WINAPI Unknown8_func33_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func33(param0, param1);
}

static void* WINAPI Unknown8_func34_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func34(param0, param1);
}

static void* WINAPI Unknown8_func35_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func35(param0, param1);
}

static void* WINAPI Unknown8_func36_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func36(param0, param1);
}

static void* WINAPI Unknown8_func37_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func37(param0, param1);
}

static void* WINAPI Unknown8_func38_relay(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return Unknown8_orig->func38(param0, param1, param2);
}

static void* WINAPI Unknown8_func39_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func39(param0, param1);
}

static void* WINAPI Unknown8_func40_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func40(param0, param1);
}

static void* WINAPI Unknown8_func41_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func41(param0, param1);
}

static void* WINAPI Unknown8_func42_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func42(param0, param1);
}

static void* WINAPI Unknown8_func43_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func43(param0, param1);
}

static void* WINAPI Unknown8_func44_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func44(param0, param1);
}

static void* WINAPI Unknown8_func45_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func45(param0, param1);
}

static void* WINAPI Unknown8_func46_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func46(param0, param1);
}

static void* WINAPI Unknown8_func47_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func47(param0, param1);
}

static void* WINAPI Unknown8_func48_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func48(param0, param1);
}

static void* WINAPI Unknown8_func49_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func49(param0, param1);
}

static void* WINAPI Unknown8_func50_relay(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return Unknown8_orig->func50(param0, param1, param2);
}

static void* WINAPI Unknown8_func51_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func51(param0, param1);
}

static void* WINAPI Unknown8_func52_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func52(param0, param1);
}

static void* WINAPI Unknown8_func53_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func53(param0, param1);
}

static void* WINAPI Unknown8_func54_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func54(param0, param1);
}

static void* WINAPI Unknown8_func55_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func55(param0, param1);
}

static void* WINAPI Unknown8_func56_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func56(param0, param1);
}

static void* WINAPI Unknown8_func57_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func57(param0, param1);
}

static void* WINAPI Unknown8_func58_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func58(param0, param1);
}

static void* WINAPI Unknown8_func59_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func59(param0, param1);
}

static void* WINAPI Unknown8_func60_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func60(param0, param1);
}

static void* WINAPI Unknown8_func61_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func61(param0, param1);
}

static void* WINAPI Unknown8_func62_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func62(param0, param1);
}

static void* WINAPI Unknown8_func63_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func63(param0, param1);
}

static void* WINAPI Unknown8_func64_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func64(param0, param1);
}

static void* WINAPI Unknown8_func65_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func65(param0, param1);
}

static void* WINAPI Unknown8_func66_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func66(param0, param1);
}

static void* WINAPI Unknown8_func67_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func67(param0, param1);
}

static void* WINAPI Unknown8_func68_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func68(param0, param1);
}

static void* WINAPI Unknown8_func69_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func69(param0, param1);
}

static void* WINAPI Unknown8_func70_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func70(param0, param1);
}

static void* WINAPI Unknown8_func71_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func71(param0, param1);
}

static void* WINAPI Unknown8_func72_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func72(param0, param1);
}

static void* WINAPI Unknown8_func73_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func73(param0, param1);
}

static void* WINAPI Unknown8_func74_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func74(param0, param1);
}

static void* WINAPI Unknown8_func75_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func75(param0, param1);
}

static void* WINAPI Unknown8_func76_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown8_orig->func76(param0, param1);
}

static struct Unknown8_table Unknown8_Impl =
{
    sizeof(struct Unknown8_table),
    Unknown8_func0_relay,
    Unknown8_func1_relay,
    Unknown8_func2_relay,
    Unknown8_func3_relay,
    Unknown8_func4_relay,
    Unknown8_func5_relay,
    Unknown8_func6_relay,
    Unknown8_func7_relay,
    Unknown8_func8_relay,
    Unknown8_func9_relay,
    Unknown8_func10_relay,
    Unknown8_func11_relay,
    Unknown8_func12_relay,
    Unknown8_func13_relay,
    Unknown8_func14_relay,
    Unknown8_func15_relay,
    Unknown8_func16_relay,
    Unknown8_func17_relay,
    Unknown8_func18_relay,
    Unknown8_func19_relay,
    Unknown8_func20_relay,
    Unknown8_func21_relay,
    Unknown8_func22_relay,
    Unknown8_func23_relay,
    Unknown8_func24_relay,
    Unknown8_func25_relay,
    Unknown8_func26_relay,
    Unknown8_func27_relay,
    Unknown8_func28_relay,
    Unknown8_func29_relay,
    Unknown8_func30_relay,
    Unknown8_func31_relay,
    Unknown8_func32_relay,
    Unknown8_func33_relay,
    Unknown8_func34_relay,
    Unknown8_func35_relay,
    Unknown8_func36_relay,
    Unknown8_func37_relay,
    Unknown8_func38_relay,
    Unknown8_func39_relay,
    Unknown8_func40_relay,
    Unknown8_func41_relay,
    Unknown8_func42_relay,
    Unknown8_func43_relay,
    Unknown8_func44_relay,
    Unknown8_func45_relay,
    Unknown8_func46_relay,
    Unknown8_func47_relay,
    Unknown8_func48_relay,
    Unknown8_func49_relay,
    Unknown8_func50_relay,
    Unknown8_func51_relay,
    Unknown8_func52_relay,
    Unknown8_func53_relay,
    Unknown8_func54_relay,
    Unknown8_func55_relay,
    Unknown8_func56_relay,
    Unknown8_func57_relay,
    Unknown8_func58_relay,
    Unknown8_func59_relay,
    Unknown8_func60_relay,
    Unknown8_func61_relay,
    Unknown8_func62_relay,
    Unknown8_func63_relay,
    Unknown8_func64_relay,
    Unknown8_func65_relay,
    Unknown8_func66_relay,
    Unknown8_func67_relay,
    Unknown8_func68_relay,
    Unknown8_func69_relay,
    Unknown8_func70_relay,
    Unknown8_func71_relay,
    Unknown8_func72_relay,
    Unknown8_func73_relay,
    Unknown8_func74_relay,
    Unknown8_func75_relay,
    Unknown8_func76_relay,
};

static void* WINAPI Unknown9_func0_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func0(param0, param1);
}

static void* WINAPI Unknown9_func1_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func1(param0, param1);
}

static void* WINAPI Unknown9_func2_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func2(param0, param1);
}

static void* WINAPI Unknown9_func3_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func3(param0, param1);
}

static void* WINAPI Unknown9_func4_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func4(param0, param1);
}

static void* WINAPI Unknown9_func5_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func5(param0, param1);
}

static void* WINAPI Unknown9_func6_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func6(param0, param1);
}

static void* WINAPI Unknown9_func7_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func7(param0, param1);
}

static void* WINAPI Unknown9_func8_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func8(param0, param1);
}

static void* WINAPI Unknown9_func9_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func9(param0, param1);
}

static void* WINAPI Unknown9_func10_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func10(param0, param1);
}

static void* WINAPI Unknown9_func11_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func11(param0, param1);
}

static void* WINAPI Unknown9_func12_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func12(param0, param1);
}

static void* WINAPI Unknown9_func13_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func13(param0, param1);
}

static void* WINAPI Unknown9_func14_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func14(param0, param1);
}

static void* WINAPI Unknown9_func15_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func15(param0, param1);
}

static void* WINAPI Unknown9_func16_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func16(param0, param1);
}

static void* WINAPI Unknown9_func17_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func17(param0, param1);
}

static void* WINAPI Unknown9_func18_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func18(param0, param1);
}

static void* WINAPI Unknown9_func19_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func19(param0, param1);
}

static void* WINAPI Unknown9_func20_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func20(param0, param1);
}

static void* WINAPI Unknown9_func21_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func21(param0, param1);
}

static void* WINAPI Unknown9_func22_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func22(param0, param1);
}

static void* WINAPI Unknown9_func23_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func23(param0, param1);
}

static void* WINAPI Unknown9_func24_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func24(param0, param1);
}

static void* WINAPI Unknown9_func25_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func25(param0, param1);
}

static void* WINAPI Unknown9_func26_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func26(param0, param1);
}

static void* WINAPI Unknown9_func27_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func27(param0, param1);
}

static void* WINAPI Unknown9_func28_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func28(param0, param1);
}

static void* WINAPI Unknown9_func29_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func29(param0, param1);
}

static void* WINAPI Unknown9_func30_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func30(param0, param1);
}

static void* WINAPI Unknown9_func31_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func31(param0, param1);
}

static void* WINAPI Unknown9_func32_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func32(param0, param1);
}

static void* WINAPI Unknown9_func33_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func33(param0, param1);
}

static void* WINAPI Unknown9_func34_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func34(param0, param1);
}

static void* WINAPI Unknown9_func35_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func35(param0, param1);
}

static void* WINAPI Unknown9_func36_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func36(param0, param1);
}

static void* WINAPI Unknown9_func37_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func37(param0, param1);
}

static void* WINAPI Unknown9_func38_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func38(param0, param1);
}

static void* WINAPI Unknown9_func39_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func39(param0, param1);
}

static void* WINAPI Unknown9_func40_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func40(param0, param1);
}

static void* WINAPI Unknown9_func41_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func41(param0, param1);
}

static void* WINAPI Unknown9_func42_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func42(param0, param1);
}

static void* WINAPI Unknown9_func43_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func43(param0, param1);
}

static void* WINAPI Unknown9_func44_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func44(param0, param1);
}

static void* WINAPI Unknown9_func45_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func45(param0, param1);
}

static void* WINAPI Unknown9_func46_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func46(param0, param1);
}

static void* WINAPI Unknown9_func47_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func47(param0, param1);
}

static void* WINAPI Unknown9_func48_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func48(param0, param1);
}

static void* WINAPI Unknown9_func49_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func49(param0, param1);
}

static void* WINAPI Unknown9_func50_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func50(param0, param1);
}

static void* WINAPI Unknown9_func51_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func51(param0, param1);
}

static void* WINAPI Unknown9_func52_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func52(param0, param1);
}

static void* WINAPI Unknown9_func53_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func53(param0, param1);
}

static void* WINAPI Unknown9_func54_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func54(param0, param1);
}

static void* WINAPI Unknown9_func55_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func55(param0, param1);
}

static void* WINAPI Unknown9_func56_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func56(param0, param1);
}

static void* WINAPI Unknown9_func57_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func57(param0, param1);
}

static void* WINAPI Unknown9_func58_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func58(param0, param1);
}

static void* WINAPI Unknown9_func59_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func59(param0, param1);
}

static void* WINAPI Unknown9_func60_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func60(param0, param1);
}

static void* WINAPI Unknown9_func61_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func61(param0, param1);
}

static void* WINAPI Unknown9_func62_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func62(param0, param1);
}

static void* WINAPI Unknown9_func63_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func63(param0, param1);
}

static void* WINAPI Unknown9_func64_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func64(param0, param1);
}

static void* WINAPI Unknown9_func65_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func65(param0, param1);
}

static void* WINAPI Unknown9_func66_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func66(param0, param1);
}

static void* WINAPI Unknown9_func67_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func67(param0, param1);
}

static void* WINAPI Unknown9_func68_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func68(param0, param1);
}

static void* WINAPI Unknown9_func69_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func69(param0, param1);
}

static void* WINAPI Unknown9_func70_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func70(param0, param1);
}

static void* WINAPI Unknown9_func71_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func71(param0, param1);
}

static void* WINAPI Unknown9_func72_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func72(param0, param1);
}

static void* WINAPI Unknown9_func73_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func73(param0, param1);
}

static void* WINAPI Unknown9_func74_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func74(param0, param1);
}

static void* WINAPI Unknown9_func75_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func75(param0, param1);
}

static void* WINAPI Unknown9_func76_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func76(param0, param1);
}

static void* WINAPI Unknown9_func77_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func77(param0, param1);
}

static void* WINAPI Unknown9_func78_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func78(param0, param1);
}

static void* WINAPI Unknown9_func79_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func79(param0, param1);
}

static void* WINAPI Unknown9_func80_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func80(param0, param1);
}

static void* WINAPI Unknown9_func81_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func81(param0, param1);
}

static void* WINAPI Unknown9_func82_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func82(param0, param1);
}

static void* WINAPI Unknown9_func83_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func83(param0, param1);
}

static void* WINAPI Unknown9_func84_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func84(param0, param1);
}

static void* WINAPI Unknown9_func85_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func85(param0, param1);
}

static void* WINAPI Unknown9_func86_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown9_orig->func86(param0, param1);
}

struct Unknown9_table Unknown9_Impl =
{
    sizeof(struct Unknown9_table),
    Unknown9_func0_relay,
    Unknown9_func1_relay,
    Unknown9_func2_relay,
    Unknown9_func3_relay,
    Unknown9_func4_relay,
    Unknown9_func5_relay,
    Unknown9_func6_relay,
    Unknown9_func7_relay,
    Unknown9_func8_relay,
    Unknown9_func9_relay,
    Unknown9_func10_relay,
    Unknown9_func11_relay,
    Unknown9_func12_relay,
    Unknown9_func13_relay,
    Unknown9_func14_relay,
    Unknown9_func15_relay,
    Unknown9_func16_relay,
    Unknown9_func17_relay,
    Unknown9_func18_relay,
    Unknown9_func19_relay,
    Unknown9_func20_relay,
    Unknown9_func21_relay,
    Unknown9_func22_relay,
    Unknown9_func23_relay,
    Unknown9_func24_relay,
    Unknown9_func25_relay,
    Unknown9_func26_relay,
    Unknown9_func27_relay,
    Unknown9_func28_relay,
    Unknown9_func29_relay,
    Unknown9_func30_relay,
    Unknown9_func31_relay,
    Unknown9_func32_relay,
    Unknown9_func33_relay,
    Unknown9_func34_relay,
    Unknown9_func35_relay,
    Unknown9_func36_relay,
    Unknown9_func37_relay,
    Unknown9_func38_relay,
    Unknown9_func39_relay,
    Unknown9_func40_relay,
    Unknown9_func41_relay,
    Unknown9_func42_relay,
    Unknown9_func43_relay,
    Unknown9_func44_relay,
    Unknown9_func45_relay,
    Unknown9_func46_relay,
    Unknown9_func47_relay,
    Unknown9_func48_relay,
    Unknown9_func49_relay,
    Unknown9_func50_relay,
    Unknown9_func51_relay,
    Unknown9_func52_relay,
    Unknown9_func53_relay,
    Unknown9_func54_relay,
    Unknown9_func55_relay,
    Unknown9_func56_relay,
    Unknown9_func57_relay,
    Unknown9_func58_relay,
    Unknown9_func59_relay,
    Unknown9_func60_relay,
    Unknown9_func61_relay,
    Unknown9_func62_relay,
    Unknown9_func63_relay,
    Unknown9_func64_relay,
    Unknown9_func65_relay,
    Unknown9_func66_relay,
    Unknown9_func67_relay,
    Unknown9_func68_relay,
    Unknown9_func69_relay,
    Unknown9_func70_relay,
    Unknown9_func71_relay,
    Unknown9_func72_relay,
    Unknown9_func73_relay,
    Unknown9_func74_relay,
    Unknown9_func75_relay,
    Unknown9_func76_relay,
    Unknown9_func77_relay,
    Unknown9_func78_relay,
    Unknown9_func79_relay,
    Unknown9_func80_relay,
    Unknown9_func81_relay,
    Unknown9_func82_relay,
    Unknown9_func83_relay,
    Unknown9_func84_relay,
    Unknown9_func85_relay,
    Unknown9_func86_relay,
};

static void* WINAPI Unknown10_func0_relay(void *param0)
{
    TRACE("(%p)\n", param0);
    return Unknown10_orig->func0(param0);
}

static void* WINAPI Unknown10_func1_relay(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Unknown10_orig->func1(param0, param1);
}

static struct Unknown10_table Unknown10_Impl =
{
    sizeof(struct Unknown10_table),
    Unknown10_func0_relay,
    Unknown10_func1_relay,
};

static BOOL cuda_check_table(const struct cuda_table *orig, struct cuda_table *impl, const char *name)
{
    if (!orig)
        return FALSE;

    /* FIXME: better check for size, verify that function pointers are != NULL */

    if (orig->size > impl->size)
    {
        FIXME("WARNING: Your CUDA version supports a newer interface for %s then the Wine implementation.\n", name);
    }
    else if (orig->size < impl->size)
    {
        FIXME("Your CUDA version supports only an older interface for %s, downgrading version.\n", name);
        impl->size = orig->size;
    }

    return TRUE;
}

static inline BOOL cuda_equal_uuid(const CUuuid *id1, const CUuuid *id2)
{
    return !memcmp(id1, id2, sizeof(CUuuid));
}

static char* cuda_print_uuid(const CUuuid *id, char *buffer, int size)
{
    snprintf(buffer, size, "{%02x%02x%02x%02x-%02x%02x-%02x%02x-"\
                            "%02x%02x-%02x%02x%02x%02x%02x%02x}",
             id->bytes[0] & 0xFF, id->bytes[1] & 0xFF, id->bytes[2] & 0xFF, id->bytes[3] & 0xFF,
             id->bytes[4] & 0xFF, id->bytes[5] & 0xFF, id->bytes[6] & 0xFF, id->bytes[7] & 0xFF,
             id->bytes[8] & 0xFF, id->bytes[9] & 0xFF, id->bytes[10] & 0xFF, id->bytes[11] & 0xFF,
             id->bytes[12] & 0xFF, id->bytes[13] & 0xFF, id->bytes[14] & 0xFF, id->bytes[15] & 0xFF);
    return buffer;
}

CUresult cuda_get_table(const void **table, const CUuuid *uuid, const void *orig_table, CUresult orig_result)
{
    char buffer[128];

    if (cuda_equal_uuid(uuid, &UUID_Unknown1))
    {
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Unknown1_Impl, "Unknown1"))
            return CUDA_ERROR_UNKNOWN;

        Unknown1_orig = orig_table;
        *table = (void *)&Unknown1_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Unknown2))
    {
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Unknown2_Impl, "Unknown2"))
            return CUDA_ERROR_UNKNOWN;

        Unknown2_orig = orig_table;
        *table = (void *)&Unknown2_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Unknown3))
    {
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Unknown3_Impl, "Unknown3"))
            return CUDA_ERROR_UNKNOWN;

        Unknown3_orig = orig_table;
        *table = (void *)&Unknown3_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_ContextStorage))
    {
        if (orig_result)
            return orig_result;
        if (!orig_table)
            return CUDA_ERROR_UNKNOWN;

        ContextStorage_orig = orig_table;
        *table = (void *)&ContextStorage_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Unknown5))
    {
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Unknown5_Impl, "Unknown5"))
            return CUDA_ERROR_UNKNOWN;

        Unknown5_orig = orig_table;
        *table = (void *)&Unknown5_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_TlsNotifyInterface))
    {
        /* the following interface is not implemented in the Linux
         * CUDA driver, we provide a replacement implementation */
        *table = (void *)&TlsNotifyInterface_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Unknown7))
    {
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Unknown7_Impl, "Unknown7"))
            return CUDA_ERROR_UNKNOWN;

        Unknown7_orig = orig_table;
        *table = (void *)&Unknown7_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Unknown8))
    {
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Unknown8_Impl, "Unknown8"))
            return CUDA_ERROR_UNKNOWN;

        Unknown8_orig = orig_table;
        *table = (void *)&Unknown8_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Unknown9))
    {
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Unknown9_Impl, "Unknown9"))
            return CUDA_ERROR_UNKNOWN;

        Unknown9_orig = orig_table;
        *table = (void *)&Unknown9_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Unknown10))
    {
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Unknown10_Impl, "Unknown10"))
            return CUDA_ERROR_UNKNOWN;

        Unknown10_orig = orig_table;
        *table = (void *)&Unknown10_Impl;
        return CUDA_SUCCESS;
    }

    FIXME("Unknown UUID: %s, error: %d\n", cuda_print_uuid(uuid, buffer, sizeof(buffer)), orig_result);
    return CUDA_ERROR_UNKNOWN;
}
