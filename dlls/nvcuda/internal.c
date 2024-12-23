/*
 * Copyright (C) 2014-2015 Michael Müller
 * Copyright (C) 2014-2015 Sebastian Lackner
 * Copyright (C) 2022-2024 Sveinar Søpler
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
#include <unistd.h>
#include <time.h>
#include <inttypes.h>

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"
#include "wine/list.h"
#include "cuda.h"
#include "nvcuda.h"
#include "encryption.h"

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
    // Check if the list is empty before entering the critical section
    if (list_empty(&tls_callbacks)) {
        return;
    }

    struct list *ptr;

    TRACE("(%d)\n", reason);

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

static const CUuuid UUID_Relay1                     = {{0x6B, 0xD5, 0xFB, 0x6C, 0x5B, 0xF4, 0xE7, 0x4A,
                                                        0x89, 0x87, 0xD9, 0x39, 0x12, 0xFD, 0x9D, 0xF9}};
                                                    // {6bd5fb6c-5bf4-e74a-8987-d93912fd9df9}
static const CUuuid UUID_Relay2                     = {{0xA0, 0x94, 0x79, 0x8C, 0x2E, 0x74, 0x2E, 0x74,
                                                        0x93, 0xF2, 0x08, 0x00, 0x20, 0x0C, 0x0A, 0x66}};
                                                    // {a094798c-2e74-2e74-93f2-0800200c0a66}
static const CUuuid UUID_Relay3                     = {{0x42, 0xD8, 0x5A, 0x81, 0x23, 0xF6, 0xCB, 0x47,
                                                        0x82, 0x98, 0xF6, 0xE7, 0x8A, 0x3A, 0xEC, 0xDC}};
                                                    // {42d85a81-23f6-cb47-8298-f6e78a3aecdc}
static const CUuuid UUID_ContextStorage             = {{0xC6, 0x93, 0x33, 0x6E, 0x11, 0x21, 0xDF, 0x11,
                                                        0xA8, 0xC3, 0x68, 0xF3, 0x55, 0xD8, 0x95, 0x93}};
                                                    // {c693336e-1121-df11-a8c3-68f355d89593}
static const CUuuid UUID_Relay5                     = {{0x0C, 0xA5, 0x0B, 0x8C, 0x10, 0x04, 0x92, 0x9A,
                                                        0x89, 0xA7, 0xD0, 0xDF, 0x10, 0xE7, 0x72, 0x86}};
                                                    // {0ca50b8c-1004-929a-89a7-f0ff10e77286}
static const CUuuid UUID_TlsNotifyInterface         = {{0x19, 0x5B, 0xCB, 0xF4, 0xD6, 0x7D, 0x02, 0x4A,
                                                        0xAC, 0xC5, 0x1D, 0x29, 0xCE, 0xA6, 0x31, 0xAE}};
                                                    // {195bcbf4-d67d-024a-acc5-1d29cea631ae}
static const CUuuid UUID_Encryption                 = {{0xD4, 0x08, 0x20, 0x55, 0xBD, 0xE6, 0x70, 0x4B,
                                                        0x8D, 0x34, 0xBA, 0x12, 0x3C, 0x66, 0xE1, 0xF2}};
                                                    // {d4082055-bde6-704b-8d34-ba123c66e1f2}
static const CUuuid UUID_Relay8                     = {{0x21, 0x31, 0x8C, 0x60, 0x97, 0x14, 0x32, 0x48,
                                                        0x8C, 0xA6, 0x41, 0xFF, 0x73, 0x24, 0xC8, 0xF2}};
                                                    // {21318c60-9714-3248-8ca6-41ff7324c8f2}
static const CUuuid UUID_Relay9                     = {{0x6E, 0x16, 0x3F, 0xBE, 0xB9, 0x58, 0x44, 0x4D,
                                                        0x83, 0x5C, 0xE1, 0x82, 0xAF, 0xF1, 0x99, 0x1E}};
                                                    // {6e163fbe-b958-444d-835c-e182aff1991e}
static const CUuuid UUID_Relay10                    = {{0x26, 0x3E, 0x88, 0x60, 0x7C, 0xD2, 0x61, 0x43,
                                                        0x92, 0xF6, 0xBB, 0xD5, 0x00, 0x6D, 0xFA, 0x7E}};
                                                    // {263e8860-7cd2-6143-92f6-bbd5006dfa7e}
static const CUuuid UUID_OpticalFlow                = {{0x9A, 0xF0, 0x70, 0x7B, 0x8E, 0x2D, 0xD8, 0x4C,
                                                        0x8E, 0x4E, 0xB9, 0x94, 0xC8, 0x2D, 0xDC, 0x35}};
                                                    // {9af0707b-8e2d-d84c-8e4e-b994c82ddc35}

struct cuda_table
{
    int size;
    void *functions[0];
};

/*
 * Relay1
 */
struct Relay1_table
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
    void* (WINAPI *func10)(void *param0, void *param1);
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
    void* (*func10)(void *param0, void *param1);
} *Relay1_orig = NULL;

/*
 * Relay2
 */
struct Relay2_table
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
} *Relay2_orig = NULL;

/*
 * Relay3
 */
struct Relay3_table
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
} *Relay3_orig = NULL;

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
 * Relay5
 */
struct Relay5_table
{
    int size;
    void* (WINAPI *func0)(void *param0, void *param1, void *param2);
};
static const struct
{
    int size;
    void* (*func0)(void *param0, void *param1, void *param2);
} *Relay5_orig = NULL;


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
 * Encryption
 */
struct Encryption_table
{
    int size;
    CUresult (WINAPI *encrypt0)(unsigned int cudaVersion, time_t timestamp, __uint128_t *res);
    CUresult (WINAPI *encrypt1)(void *param0);
};

/*
 * Relay8
 */
struct Relay8_table
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
    void* (WINAPI *func87)(void *param0, void *param1);
    void* (WINAPI *func88)(void *param0, void *param1);
    void* (WINAPI *func89)(void *param0, void *param1);
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
    void* (*func87)(void *param0, void *param1);
    void* (*func88)(void *param0, void *param1);
    void* (*func89)(void *param0, void *param1);
} *Relay8_orig = NULL;

/*
 * Relay9
 */
struct Relay9_table
{
    int size;
    void* (WINAPI *func0)(void *param0, void *param1);
    void* (WINAPI *func1)(void *param0, void *param1);
    void* (WINAPI *func2)(void *param0, void *param1);
    void* (WINAPI *func3)(void *param0, void *param1);
    void* (WINAPI *func4)(void *param0, void *param1);
    void* (WINAPI *func5)(void *param0, void *param1);
    void* (WINAPI *func6)(void *param0, void *param1, void *param2, void *param3);
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
    void* (WINAPI *func87)(void *param0, void *param1);
    void* (WINAPI *func88)(void *param0, void *param1);
    void* (WINAPI *func89)(void *param0, void *param1);
    void* (WINAPI *func90)(void *param0, void *param1);
    void* (WINAPI *func91)(void *param0, void *param1);
    void* (WINAPI *func92)(void *param0, void *param1);
    void* (WINAPI *func93)(void *param0, void *param1);
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
    void* (*func6)(void *param0, void *param1, void *param2, void *param3);
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
    void* (*func87)(void *param0, void *param1);
    void* (*func88)(void *param0, void *param1);
    void* (*func89)(void *param0, void *param1);
    void* (*func90)(void *param0, void *param1);
    void* (*func91)(void *param0, void *param1);
    void* (*func92)(void *param0, void *param1);
    void* (*func93)(void *param0, void *param1);
} *Relay9_orig = NULL;

/*
 * Relay10
 */
struct Relay10_table
{
    int size;
    void* (WINAPI *func0)(void *param0);
    void* (WINAPI *func1)(void *param0, void *param1);
    void* (WINAPI *func2)(void);
    void* (WINAPI *func3)(void *param0);
};
static const struct
{
    int size;
    void* (*func0)(void *param0);
    void* (*func1)(void *param0, void *param1);
    void* (*func2)(void);
    void* (*func3)(void *param0);
} *Relay10_orig = NULL;

/*
 * OpticalFlow
*/
struct OpticalFlow_table
{
    int size;
    void* (WINAPI* func0)(void *param0);
    void* (WINAPI* func1)(void *param0, void *param1);
    void* (WINAPI* func2)(void *param0, void *param1);
    void* (WINAPI* func3)(void *param0, void *param1);
    void* (WINAPI* func4)(void *param0, void *param1);
    void* (WINAPI* func5)(void *param0, void *param1);
    void* (WINAPI* func6)(void *param0);
    void* (WINAPI* func7)(void *param0);
    void* (WINAPI* func8)(void *param0, void *param1, void *param2);
    void* (WINAPI* func9)(void *param0, void *param1);
    void* (WINAPI* func10)(void *param0, void *param1);
    void* (WINAPI* func11)(void *param0, void *param1);
    void* (WINAPI* func12)(void *param0, void *param1);
    void* (WINAPI* func13)(void *param0, void *param1);
    void* (WINAPI* func14)(void *param0, void *param1);
    void* (WINAPI* func15)(void *param0, void *param1);
    void* (WINAPI* func16)(void *param0, void *param1);
    void* (WINAPI* func17)(void *param0, void *param1);
    void* (WINAPI* func18)(void *param0, void *param1, void *param2);
    void* (WINAPI* func19)(void *param0, void *param1);
    void* (WINAPI* func20)(void *param0, void *param1);
    void* (WINAPI* func21)(void *param0, void *param1);
};
static const struct
{
    int size;
    void* (*func0)(void *param0);
    void* (*func1)(void *param0, void *param1);
    void* (*func2)(void *param0, void *param1);
    void* (*func3)(void *param0, void *param1);
    void* (*func4)(void *param0, void *param1);
    void* (*func5)(void *param0, void *param1);
    void* (*func6)(void *param0);
    void* (*func7)(void *param0);
    void* (*func8)(void *param0, void *param1, void *param2);
    void* (*func9)(void *param0, void *param1);
    void* (*func10)(void *param0, void *param1);
    void* (*func11)(void *param0, void *param1);
    void* (*func12)(void *param0, void *param1);
    void* (*func13)(void *param0, void *param1);
    void* (*func14)(void *param0, void *param1);
    void* (*func15)(void *param0, void *param1);
    void* (*func16)(void *param0, void *param1);
    void* (*func17)(void *param0, void *param1);
    void* (*func18)(void *param0, void *param1, void *param2);
    void* (*func19)(void *param0, void *param1);
    void* (*func20)(void *param0, void *param1);
    void* (*func21)(void *param0, void *param1);
} *OpticalFlow_orig = NULL;

static void* WINAPI Relay1_func0(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func0(param0, param1);
}

static void* WINAPI Relay1_func1(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func1(param0, param1);
}

static void* WINAPI Relay1_func2(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func2(param0, param1);
}

static void* WINAPI Relay1_func3(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func3(param0, param1);
}

static void* WINAPI Relay1_func4(void *param0)
{
    TRACE("(%p)\n", param0);
    return Relay1_orig->func4(param0);
}

static void* WINAPI Relay1_func5(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func5(param0, param1);
}

static void* WINAPI Relay1_func6(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func6(param0, param1);
}

static void* WINAPI Relay1_func7(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func7(param0, param1);
}

static void* WINAPI Relay1_func8(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func8(param0, param1);
}

static void* WINAPI Relay1_func9(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func9(param0, param1);
}

static void* WINAPI Relay1_func10(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay1_orig->func10(param0, param1);
}

struct Relay1_table Relay1_Impl =
{
    sizeof(struct Relay1_table),
    Relay1_func0,
    Relay1_func1,
    Relay1_func2,
    Relay1_func3,
    Relay1_func4,
    Relay1_func5,
    Relay1_func6,
    Relay1_func7,
    Relay1_func8,
    Relay1_func9,
    Relay1_func10,
};

static void* WINAPI Relay2_func0(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay2_orig->func0(param0, param1);
}

static void* WINAPI Relay2_func1(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay2_orig->func1(param0, param1);
}

static void* WINAPI Relay2_func2(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return Relay2_orig->func2(param0, param1, param2);
}

static void* WINAPI Relay2_func3(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay2_orig->func3(param0, param1);
}

static void* WINAPI Relay2_func4(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay2_orig->func4(param0, param1);
}

static void* WINAPI Relay2_func5(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay2_orig->func5(param0, param1);
}

struct Relay2_table Relay2_Impl =
{
    sizeof(struct Relay2_table),
    Relay2_func0,
    Relay2_func1,
    Relay2_func2,
    Relay2_func3,
    Relay2_func4,
    Relay2_func5,
};

static void* WINAPI Relay3_func0(void *param0)
{
    TRACE("(%p)\n", param0);
    return Relay3_orig->func0(param0);
}

static void* WINAPI Relay3_func1(void *param0)
{
    TRACE("(%p)\n", param0);
    return Relay3_orig->func1(param0);
}

static struct Relay3_table Relay3_Impl =
{
    sizeof(struct Relay3_table),
    Relay3_func0,
    Relay3_func1,
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

    TRACE("(%p, %p, %p, %p)\n", ctx, key, value, callback);

    storage = HeapAlloc( GetProcessHeap(), 0, sizeof(*storage) );
    if (!storage)
        return CUDA_ERROR_OUT_OF_MEMORY;

    storage->callback = callback;
    storage->value = value;

    CUresult ret = ContextStorage_orig->Set(ctx, key, storage, storage_destructor_callback);
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

    TRACE("(%p, %p, %p)\n", value, ctx, key);

    CUresult ret = ContextStorage_orig->Get((void **)&storage, ctx, key);
    if (!ret) *value = storage->value;
    return ret;
}

struct ContextStorage_table ContextStorage_Impl =
{
    ContextStorage_Set,
    ContextStorage_Remove,
    ContextStorage_Get,
};

static void* WINAPI Relay5_func0(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return Relay5_orig->func0(param0, param1, param2);
}

struct Relay5_table Relay5_Impl =
{
    sizeof(struct Relay5_table),
    Relay5_func0,
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

extern struct Encryption_table Encryption_Impl;
static CUresult WINAPI Encryption_encrypt0(unsigned int cudaVersion, time_t timestamp, __uint128_t *res)
{
    TRACE("%u, (%ld, %p)\n", cudaVersion, timestamp, res);
    // After CUDA SDK 11.6 some checks is done by the CudaRuntimeLibrary (CudaRT)
    // This fails, so implementing encryption function from ZLUDA for this

    int version;
    if (wine_cuDriverGetVersion(&version)) return CUDA_ERROR_UNKNOWN;

    EncryptInput1 input1 = {
        .driverVersion = (unsigned int)version,
        .cudaVersion = cudaVersion,
        .processID = (unsigned int)GetCurrentProcessId(),
        .threadID = (unsigned int)GetCurrentThreadId(),
        .exportTable1 = &Relay1_Impl,
        .exportTable2 = &Encryption_Impl,
        .funcPtr = &Encryption_encrypt0,
        .timestamp = timestamp,
    };
    return encrypt(&input1, res);
}

static CUresult WINAPI Encryption_encrypt1(void *param0)
{
    TRACE("(%p)\n", param0);
    return CUDA_ERROR_UNKNOWN;
}

struct Encryption_table Encryption_Impl =
{
    sizeof(struct Encryption_table),
    Encryption_encrypt0,
    Encryption_encrypt1,
};

static void* WINAPI Relay8_func0(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func0(param0, param1);
}

static void* WINAPI Relay8_func1(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func1(param0, param1);
}

static void* WINAPI Relay8_func2(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func2(param0, param1);
}

static void* WINAPI Relay8_func3(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func3(param0, param1);
}

static void* WINAPI Relay8_func4(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func4(param0, param1);
}

static void* WINAPI Relay8_func5(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func5(param0, param1);
}

static void* WINAPI Relay8_func6(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func6(param0, param1);
}

static void* WINAPI Relay8_func7(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func7(param0, param1);
}

static void* WINAPI Relay8_func8(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func8(param0, param1);
}

static void* WINAPI Relay8_func9(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func9(param0, param1);
}

static void* WINAPI Relay8_func10(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func10(param0, param1);
}

static void* WINAPI Relay8_func11(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func11(param0, param1);
}

static void* WINAPI Relay8_func12(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func12(param0, param1);
}

static void* WINAPI Relay8_func13(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func13(param0, param1);
}

static void* WINAPI Relay8_func14(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func14(param0, param1);
}

static void* WINAPI Relay8_func15(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func15(param0, param1);
}

static void* WINAPI Relay8_func16(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func16(param0, param1);
}

static void* WINAPI Relay8_func17(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func17(param0, param1);
}

static void* WINAPI Relay8_func18(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func18(param0, param1);
}

static void* WINAPI Relay8_func19(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func19(param0, param1);
}

static void* WINAPI Relay8_func20(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func20(param0, param1);
}

static void* WINAPI Relay8_func21(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func21(param0, param1);
}

static void* WINAPI Relay8_func22(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func22(param0, param1);
}

static void* WINAPI Relay8_func23(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func23(param0, param1);
}

static void* WINAPI Relay8_func24(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func24(param0, param1);
}

static void* WINAPI Relay8_func25(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func25(param0, param1);
}

static void* WINAPI Relay8_func26(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func26(param0, param1);
}

static void* WINAPI Relay8_func27(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func27(param0, param1);
}

static void* WINAPI Relay8_func28(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func28(param0, param1);
}

static void* WINAPI Relay8_func29(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func29(param0, param1);
}

static void* WINAPI Relay8_func30(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func30(param0, param1);
}

static void* WINAPI Relay8_func31(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func31(param0, param1);
}

static void* WINAPI Relay8_func32(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func32(param0, param1);
}

static void* WINAPI Relay8_func33(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func33(param0, param1);
}

static void* WINAPI Relay8_func34(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func34(param0, param1);
}

static void* WINAPI Relay8_func35(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func35(param0, param1);
}

static void* WINAPI Relay8_func36(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func36(param0, param1);
}

static void* WINAPI Relay8_func37(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func37(param0, param1);
}

static void* WINAPI Relay8_func38(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return Relay8_orig->func38(param0, param1, param2);
}

static void* WINAPI Relay8_func39(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func39(param0, param1);
}

static void* WINAPI Relay8_func40(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func40(param0, param1);
}

static void* WINAPI Relay8_func41(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func41(param0, param1);
}

static void* WINAPI Relay8_func42(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func42(param0, param1);
}

static void* WINAPI Relay8_func43(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func43(param0, param1);
}

static void* WINAPI Relay8_func44(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func44(param0, param1);
}

static void* WINAPI Relay8_func45(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func45(param0, param1);
}

static void* WINAPI Relay8_func46(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func46(param0, param1);
}

static void* WINAPI Relay8_func47(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func47(param0, param1);
}

static void* WINAPI Relay8_func48(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func48(param0, param1);
}

static void* WINAPI Relay8_func49(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func49(param0, param1);
}

static void* WINAPI Relay8_func50(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return Relay8_orig->func50(param0, param1, param2);
}

static void* WINAPI Relay8_func51(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func51(param0, param1);
}

static void* WINAPI Relay8_func52(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func52(param0, param1);
}

static void* WINAPI Relay8_func53(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func53(param0, param1);
}

static void* WINAPI Relay8_func54(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func54(param0, param1);
}

static void* WINAPI Relay8_func55(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func55(param0, param1);
}

static void* WINAPI Relay8_func56(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func56(param0, param1);
}

static void* WINAPI Relay8_func57(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func57(param0, param1);
}

static void* WINAPI Relay8_func58(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func58(param0, param1);
}

static void* WINAPI Relay8_func59(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func59(param0, param1);
}

static void* WINAPI Relay8_func60(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func60(param0, param1);
}

static void* WINAPI Relay8_func61(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func61(param0, param1);
}

static void* WINAPI Relay8_func62(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func62(param0, param1);
}

static void* WINAPI Relay8_func63(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func63(param0, param1);
}

static void* WINAPI Relay8_func64(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func64(param0, param1);
}

static void* WINAPI Relay8_func65(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func65(param0, param1);
}

static void* WINAPI Relay8_func66(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func66(param0, param1);
}

static void* WINAPI Relay8_func67(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func67(param0, param1);
}

static void* WINAPI Relay8_func68(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func68(param0, param1);
}

static void* WINAPI Relay8_func69(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func69(param0, param1);
}

static void* WINAPI Relay8_func70(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func70(param0, param1);
}

static void* WINAPI Relay8_func71(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func71(param0, param1);
}

static void* WINAPI Relay8_func72(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func72(param0, param1);
}

static void* WINAPI Relay8_func73(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func73(param0, param1);
}

static void* WINAPI Relay8_func74(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func74(param0, param1);
}

static void* WINAPI Relay8_func75(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func75(param0, param1);
}

static void* WINAPI Relay8_func76(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func76(param0, param1);
}

static void* WINAPI Relay8_func77(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func77(param0, param1);
}

static void* WINAPI Relay8_func78(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func78(param0, param1);
}

static void* WINAPI Relay8_func79(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func79(param0, param1);
}

static void* WINAPI Relay8_func80(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func80(param0, param1);
}

static void* WINAPI Relay8_func81(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func81(param0, param1);
}

static void* WINAPI Relay8_func82(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func82(param0, param1);
}

static void* WINAPI Relay8_func83(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func83(param0, param1);
}

static void* WINAPI Relay8_func84(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func84(param0, param1);
}

static void* WINAPI Relay8_func85(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func85(param0, param1);
}

static void* WINAPI Relay8_func86(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func86(param0, param1);
}

static void* WINAPI Relay8_func87(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func87(param0, param1);
}

static void* WINAPI Relay8_func88(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func88(param0, param1);
}

static void* WINAPI Relay8_func89(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay8_orig->func89(param0, param1);
}

static struct Relay8_table Relay8_Impl =
{
    sizeof(struct Relay8_table),
    Relay8_func0,
    Relay8_func1,
    Relay8_func2,
    Relay8_func3,
    Relay8_func4,
    Relay8_func5,
    Relay8_func6,
    Relay8_func7,
    Relay8_func8,
    Relay8_func9,
    Relay8_func10,
    Relay8_func11,
    Relay8_func12,
    Relay8_func13,
    Relay8_func14,
    Relay8_func15,
    Relay8_func16,
    Relay8_func17,
    Relay8_func18,
    Relay8_func19,
    Relay8_func20,
    Relay8_func21,
    Relay8_func22,
    Relay8_func23,
    Relay8_func24,
    Relay8_func25,
    Relay8_func26,
    Relay8_func27,
    Relay8_func28,
    Relay8_func29,
    Relay8_func30,
    Relay8_func31,
    Relay8_func32,
    Relay8_func33,
    Relay8_func34,
    Relay8_func35,
    Relay8_func36,
    Relay8_func37,
    Relay8_func38,
    Relay8_func39,
    Relay8_func40,
    Relay8_func41,
    Relay8_func42,
    Relay8_func43,
    Relay8_func44,
    Relay8_func45,
    Relay8_func46,
    Relay8_func47,
    Relay8_func48,
    Relay8_func49,
    Relay8_func50,
    Relay8_func51,
    Relay8_func52,
    Relay8_func53,
    Relay8_func54,
    Relay8_func55,
    Relay8_func56,
    Relay8_func57,
    Relay8_func58,
    Relay8_func59,
    Relay8_func60,
    Relay8_func61,
    Relay8_func62,
    Relay8_func63,
    Relay8_func64,
    Relay8_func65,
    Relay8_func66,
    Relay8_func67,
    Relay8_func68,
    Relay8_func69,
    Relay8_func70,
    Relay8_func71,
    Relay8_func72,
    Relay8_func73,
    Relay8_func74,
    Relay8_func75,
    Relay8_func76,
    Relay8_func77,
    Relay8_func78,
    Relay8_func79,
    Relay8_func80,
    Relay8_func81,
    Relay8_func82,
    Relay8_func83,
    Relay8_func84,
    Relay8_func85,
    Relay8_func86,
    Relay8_func87,
    Relay8_func88,
    Relay8_func89,
};

static void* WINAPI Relay9_func0(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func0(param0, param1);
}

static void* WINAPI Relay9_func1(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func1(param0, param1);
}

static void* WINAPI Relay9_func2(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func2(param0, param1);
}

static void* WINAPI Relay9_func3(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func3(param0, param1);
}

static void* WINAPI Relay9_func4(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func4(param0, param1);
}

static void* WINAPI Relay9_func5(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func5(param0, param1);
}

/* Some hackery here to relay a function with different calling convention */
static void* (WINAPI *Relay9_func6_wine)(void *param0, void *param1, void *param2);

static void* Relay9_func6_cuda(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    /* Return the parameters to WINAPI function Relay9_func6_wine */
    return Relay9_func6_wine(param0, param1, param2);
}

static void* WINAPI Relay9_func6(void *param0, void *param1, void *param2, void *param3)
{
    TRACE("(%p, %p, %p, %p)\n", param0, param1, param2, param3);
    /* Use the funcptr from param2 to this Relay9_func6_wine */
    /* function as this call needs to run with WINAPI */
    Relay9_func6_wine = (void* (WINAPI *)(void*, void*, void*))param2;
    /* Return with a funcptr to the __cdecl call Relay9_func6_cuda */
    return Relay9_orig->func6(param0, param1, Relay9_func6_cuda, param3);
}

static void* WINAPI Relay9_func7(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func7(param0, param1);
}

static void* WINAPI Relay9_func8(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func8(param0, param1);
}

static void* WINAPI Relay9_func9(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func9(param0, param1);
}

static void* WINAPI Relay9_func10(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func10(param0, param1);
}

static void* WINAPI Relay9_func11(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func11(param0, param1);
}

static void* WINAPI Relay9_func12(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func12(param0, param1);
}

static void* WINAPI Relay9_func13(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func13(param0, param1);
}

static void* WINAPI Relay9_func14(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func14(param0, param1);
}

static void* WINAPI Relay9_func15(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func15(param0, param1);
}

static void* WINAPI Relay9_func16(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func16(param0, param1);
}

static void* WINAPI Relay9_func17(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func17(param0, param1);
}

static void* WINAPI Relay9_func18(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func18(param0, param1);
}

static void* WINAPI Relay9_func19(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func19(param0, param1);
}

static void* WINAPI Relay9_func20(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func20(param0, param1);
}

static void* WINAPI Relay9_func21(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func21(param0, param1);
}

static void* WINAPI Relay9_func22(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func22(param0, param1);
}

static void* WINAPI Relay9_func23(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func23(param0, param1);
}

static void* WINAPI Relay9_func24(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func24(param0, param1);
}

static void* WINAPI Relay9_func25(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func25(param0, param1);
}

static void* WINAPI Relay9_func26(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func26(param0, param1);
}

static void* WINAPI Relay9_func27(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func27(param0, param1);
}

static void* WINAPI Relay9_func28(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func28(param0, param1);
}

static void* WINAPI Relay9_func29(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func29(param0, param1);
}

static void* WINAPI Relay9_func30(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func30(param0, param1);
}

static void* WINAPI Relay9_func31(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func31(param0, param1);
}

static void* WINAPI Relay9_func32(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func32(param0, param1);
}

static void* WINAPI Relay9_func33(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func33(param0, param1);
}

static void* WINAPI Relay9_func34(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func34(param0, param1);
}

static void* WINAPI Relay9_func35(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func35(param0, param1);
}

static void* WINAPI Relay9_func36(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func36(param0, param1);
}

static void* WINAPI Relay9_func37(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func37(param0, param1);
}

static void* WINAPI Relay9_func38(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func38(param0, param1);
}

static void* WINAPI Relay9_func39(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func39(param0, param1);
}

static void* WINAPI Relay9_func40(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func40(param0, param1);
}

static void* WINAPI Relay9_func41(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func41(param0, param1);
}

static void* WINAPI Relay9_func42(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func42(param0, param1);
}

static void* WINAPI Relay9_func43(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func43(param0, param1);
}

static void* WINAPI Relay9_func44(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func44(param0, param1);
}

static void* WINAPI Relay9_func45(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func45(param0, param1);
}

static void* WINAPI Relay9_func46(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func46(param0, param1);
}

static void* WINAPI Relay9_func47(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func47(param0, param1);
}

static void* WINAPI Relay9_func48(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func48(param0, param1);
}

static void* WINAPI Relay9_func49(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func49(param0, param1);
}

static void* WINAPI Relay9_func50(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func50(param0, param1);
}

static void* WINAPI Relay9_func51(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func51(param0, param1);
}

static void* WINAPI Relay9_func52(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func52(param0, param1);
}

static void* WINAPI Relay9_func53(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func53(param0, param1);
}

static void* WINAPI Relay9_func54(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func54(param0, param1);
}

static void* WINAPI Relay9_func55(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func55(param0, param1);
}

static void* WINAPI Relay9_func56(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func56(param0, param1);
}

static void* WINAPI Relay9_func57(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func57(param0, param1);
}

static void* WINAPI Relay9_func58(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func58(param0, param1);
}

static void* WINAPI Relay9_func59(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func59(param0, param1);
}

static void* WINAPI Relay9_func60(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func60(param0, param1);
}

static void* WINAPI Relay9_func61(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func61(param0, param1);
}

static void* WINAPI Relay9_func62(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func62(param0, param1);
}

static void* WINAPI Relay9_func63(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func63(param0, param1);
}

static void* WINAPI Relay9_func64(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func64(param0, param1);
}

static void* WINAPI Relay9_func65(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func65(param0, param1);
}

static void* WINAPI Relay9_func66(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func66(param0, param1);
}

static void* WINAPI Relay9_func67(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func67(param0, param1);
}

static void* WINAPI Relay9_func68(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func68(param0, param1);
}

static void* WINAPI Relay9_func69(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func69(param0, param1);
}

static void* WINAPI Relay9_func70(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func70(param0, param1);
}

static void* WINAPI Relay9_func71(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func71(param0, param1);
}

static void* WINAPI Relay9_func72(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func72(param0, param1);
}

static void* WINAPI Relay9_func73(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func73(param0, param1);
}

static void* WINAPI Relay9_func74(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func74(param0, param1);
}

static void* WINAPI Relay9_func75(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func75(param0, param1);
}

static void* WINAPI Relay9_func76(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func76(param0, param1);
}

static void* WINAPI Relay9_func77(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func77(param0, param1);
}

static void* WINAPI Relay9_func78(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func78(param0, param1);
}

static void* WINAPI Relay9_func79(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func79(param0, param1);
}

static void* WINAPI Relay9_func80(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func80(param0, param1);
}

static void* WINAPI Relay9_func81(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func81(param0, param1);
}

static void* WINAPI Relay9_func82(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func82(param0, param1);
}

static void* WINAPI Relay9_func83(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func83(param0, param1);
}

static void* WINAPI Relay9_func84(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func84(param0, param1);
}

static void* WINAPI Relay9_func85(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func85(param0, param1);
}

static void* WINAPI Relay9_func86(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func86(param0, param1);
}

static void* WINAPI Relay9_func87(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func87(param0, param1);
}

static void* WINAPI Relay9_func88(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func88(param0, param1);
}

static void* WINAPI Relay9_func89(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func89(param0, param1);
}

static void* WINAPI Relay9_func90(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func90(param0, param1);
}

static void* WINAPI Relay9_func91(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func91(param0, param1);
}

static void* WINAPI Relay9_func92(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func92(param0, param1);
}

static void* WINAPI Relay9_func93(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay9_orig->func93(param0, param1);
}

struct Relay9_table Relay9_Impl =
{
    sizeof(struct Relay9_table),
    Relay9_func0,
    Relay9_func1,
    Relay9_func2,
    Relay9_func3,
    Relay9_func4,
    Relay9_func5,
    Relay9_func6,
    Relay9_func7,
    Relay9_func8,
    Relay9_func9,
    Relay9_func10,
    Relay9_func11,
    Relay9_func12,
    Relay9_func13,
    Relay9_func14,
    Relay9_func15,
    Relay9_func16,
    Relay9_func17,
    Relay9_func18,
    Relay9_func19,
    Relay9_func20,
    Relay9_func21,
    Relay9_func22,
    Relay9_func23,
    Relay9_func24,
    Relay9_func25,
    Relay9_func26,
    Relay9_func27,
    Relay9_func28,
    Relay9_func29,
    Relay9_func30,
    Relay9_func31,
    Relay9_func32,
    Relay9_func33,
    Relay9_func34,
    Relay9_func35,
    Relay9_func36,
    Relay9_func37,
    Relay9_func38,
    Relay9_func39,
    Relay9_func40,
    Relay9_func41,
    Relay9_func42,
    Relay9_func43,
    Relay9_func44,
    Relay9_func45,
    Relay9_func46,
    Relay9_func47,
    Relay9_func48,
    Relay9_func49,
    Relay9_func50,
    Relay9_func51,
    Relay9_func52,
    Relay9_func53,
    Relay9_func54,
    Relay9_func55,
    Relay9_func56,
    Relay9_func57,
    Relay9_func58,
    Relay9_func59,
    Relay9_func60,
    Relay9_func61,
    Relay9_func62,
    Relay9_func63,
    Relay9_func64,
    Relay9_func65,
    Relay9_func66,
    Relay9_func67,
    Relay9_func68,
    Relay9_func69,
    Relay9_func70,
    Relay9_func71,
    Relay9_func72,
    Relay9_func73,
    Relay9_func74,
    Relay9_func75,
    Relay9_func76,
    Relay9_func77,
    Relay9_func78,
    Relay9_func79,
    Relay9_func80,
    Relay9_func81,
    Relay9_func82,
    Relay9_func83,
    Relay9_func84,
    Relay9_func85,
    Relay9_func86,
    Relay9_func87,
    Relay9_func88,
    Relay9_func89,
    Relay9_func90,
    Relay9_func91,
    Relay9_func92,
    Relay9_func93,
};

static void* WINAPI Relay10_func0(void *param0)
{
    TRACE("(%p)\n", param0);
    return Relay10_orig->func0(param0);
}

static void* WINAPI Relay10_func1(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return Relay10_orig->func1(param0, param1);
}

static void* WINAPI Relay10_func2(void)
{
    TRACE("()\n");
    return Relay10_orig->func2();
}

static void* WINAPI Relay10_func3(void *param0)
{
    TRACE("(%p)\n", param0);
    return Relay10_orig->func3(param0);
}

static struct Relay10_table Relay10_Impl =
{
    sizeof(struct Relay10_table),
    Relay10_func0,
    Relay10_func1,
    Relay10_func2,
    Relay10_func3,
};

static void* WINAPI OpticalFlow_func0(void *param0)
{
    TRACE("(%p)\n", param0);
    return OpticalFlow_orig->func0(param0);
}

static void* WINAPI OpticalFlow_func1(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func1(param0, param1);
}

static void* WINAPI OpticalFlow_func2(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func2(param0, param1);
}

static void* WINAPI OpticalFlow_func3(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func3(param0, param1);
}

static void* WINAPI OpticalFlow_func4(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func4(param0, param1);
}

static void* WINAPI OpticalFlow_func5(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func5(param0, param1);
}

static void* WINAPI OpticalFlow_func6(void *param0)
{
    TRACE("(%p)\n", param0);
    return OpticalFlow_orig->func6(param0);
}

static void* WINAPI OpticalFlow_func7(void *param0)
{
    TRACE("(%p)\n", param0);
    return OpticalFlow_orig->func7(param0);
}

static void* WINAPI OpticalFlow_func8(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return OpticalFlow_orig->func8(param0, param1, param2);
}

static void* WINAPI OpticalFlow_func9(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func9(param0, param1);
}

static void* WINAPI OpticalFlow_func10(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func10(param0, param1);
}

static void* WINAPI OpticalFlow_func11(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func11(param0, param1);
}

static void* WINAPI OpticalFlow_func12(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func12(param0, param1);
}

static void* WINAPI OpticalFlow_func13(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func13(param0, param1);
}

static void* WINAPI OpticalFlow_func14(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func14(param0, param1);
}

static void* WINAPI OpticalFlow_func15(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func15(param0, param1);
}

static void* WINAPI OpticalFlow_func16(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func16(param0, param1);
}

static void* WINAPI OpticalFlow_func17(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func17(param0, param1);
}

static void* WINAPI OpticalFlow_func18(void *param0, void *param1, void *param2)
{
    TRACE("(%p, %p, %p)\n", param0, param1, param2);
    return OpticalFlow_orig->func18(param0, param1, param2);
}

static void* WINAPI OpticalFlow_func19(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func19(param0, param1);
}

static void* WINAPI OpticalFlow_func20(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func20(param0, param1);
}

static void* WINAPI OpticalFlow_func21(void *param0, void *param1)
{
    TRACE("(%p, %p)\n", param0, param1);
    return OpticalFlow_orig->func21(param0, param1);
}

static struct OpticalFlow_table OpticalFlow_Impl =
{
    sizeof(struct OpticalFlow_table),
    OpticalFlow_func0,
    OpticalFlow_func1,
    OpticalFlow_func2,
    OpticalFlow_func3,
    OpticalFlow_func4,
    OpticalFlow_func5,
    OpticalFlow_func6,
    OpticalFlow_func7,
    OpticalFlow_func8,
    OpticalFlow_func9,
    OpticalFlow_func10,
    OpticalFlow_func11,
    OpticalFlow_func12,
    OpticalFlow_func13,
    OpticalFlow_func14,
    OpticalFlow_func15,
    OpticalFlow_func16,
    OpticalFlow_func17,
    OpticalFlow_func18,
    OpticalFlow_func19,
    OpticalFlow_func20,
    OpticalFlow_func21,
};

static BOOL cuda_check_table(const struct cuda_table *orig, struct cuda_table *impl, const char *name)
{
    if (!orig)
        return FALSE;

    /* FIXME: better check for size, verify that function pointers are != NULL */

    if (orig->size > impl->size)
    {
        FIXME("WARNING: Your CUDA version supports a newer interface for %s then the Wine implementation.\n", name);
        FIXME("WARNING: Driver implementation size: %d, Wine implementation size: %d\n", orig->size, impl->size);
    }
    else if (orig->size < impl->size)
    {
        FIXME("Your CUDA version supports only an older interface for %s, downgrading version.\n", name);
        FIXME("WARNING: Driver implementation size: %d, Wine implementation size: %d\n", orig->size, impl->size);
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

    if (cuda_equal_uuid(uuid, &UUID_Relay1))
    {
        TRACE("(%p, Relay1_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Relay1_Impl, "Relay1"))
            return CUDA_ERROR_UNKNOWN;

        Relay1_orig = orig_table;
        *table = (void *)&Relay1_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Relay2))
    {
        TRACE("(%p, Relay2_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Relay2_Impl, "Relay2"))
            return CUDA_ERROR_UNKNOWN;

        Relay2_orig = orig_table;
        *table = (void *)&Relay2_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Relay3))
    {
        TRACE("(%p, Relay3_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Relay3_Impl, "Relay3"))
            return CUDA_ERROR_UNKNOWN;

        Relay3_orig = orig_table;
        *table = (void *)&Relay3_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_ContextStorage))
    {
        TRACE("(%p, ContextStorage_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        if (orig_result)
            return orig_result;
        if (!orig_table)
            return CUDA_ERROR_UNKNOWN;

        ContextStorage_orig = orig_table;
        *table = (void *)&ContextStorage_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Relay5))
    {
        TRACE("(%p, Relay5_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Relay5_Impl, "Relay5"))
            return CUDA_ERROR_UNKNOWN;

        Relay5_orig = orig_table;
        *table = (void *)&Relay5_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_TlsNotifyInterface))
    {
        TRACE("(%p, TlsNotifyInterface_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        /* the following interface is not implemented in the Linux
         * CUDA driver, we provide a replacement implementation */
        *table = (void *)&TlsNotifyInterface_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Encryption))
    {
        TRACE("(%p, Encryption_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        *table = (void *)&Encryption_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Relay8))
    {
        TRACE("(%p, Relay8_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Relay8_Impl, "Relay8"))
            return CUDA_ERROR_UNKNOWN;

        Relay8_orig = orig_table;
        *table = (void *)&Relay8_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Relay9))
    {
        TRACE("(%p, Relay9_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Relay9_Impl, "Relay9"))
            return CUDA_ERROR_UNKNOWN;

        Relay9_orig = orig_table;
        *table = (void *)&Relay9_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_Relay10))
    {
        TRACE("(%p, Relay10_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&Relay10_Impl, "Relay10"))
            return CUDA_ERROR_UNKNOWN;

        Relay10_orig = orig_table;
        *table = (void *)&Relay10_Impl;
        return CUDA_SUCCESS;
    }
    else if (cuda_equal_uuid(uuid, &UUID_OpticalFlow))
    {
        TRACE("(%p, OpticalFlow_UUID: %s)\n", table, cuda_print_uuid(uuid, buffer, sizeof(buffer)));
        if (orig_result)
            return orig_result;
        if (!cuda_check_table(orig_table, (void *)&OpticalFlow_Impl, "OpticalFlow"))
            return CUDA_ERROR_UNKNOWN;

        OpticalFlow_orig = orig_table;
        *table = (void *)&OpticalFlow_Impl;
        return CUDA_SUCCESS;
    }

    FIXME("Unknown UUID: %s, error: %d\n", cuda_print_uuid(uuid, buffer, sizeof(buffer)), orig_result);
    return CUDA_ERROR_UNKNOWN;
}
