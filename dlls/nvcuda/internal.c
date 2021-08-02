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
#include "wine/port.h"

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
static const CUuuid UUID_Unknown2                   = {{0xA0, 0x94, 0x79, 0x8C, 0x2E, 0x74, 0x2E, 0x74,
                                                        0x93, 0xF2, 0x08, 0x00, 0x20, 0x0C, 0x0A, 0x66}};
static const CUuuid UUID_Unknown3                   = {{0x42, 0xD8, 0x5A, 0x81, 0x23, 0xF6, 0xCB, 0x47,
                                                        0x82, 0x98, 0xF6, 0xE7, 0x8A, 0x3A, 0xEC, 0xDC}};
static const CUuuid UUID_ContextStorage             = {{0xC6, 0x93, 0x33, 0x6E, 0x11, 0x21, 0xDF, 0x11,
                                                        0xA8, 0xC3, 0x68, 0xF3, 0x55, 0xD8, 0x95, 0x93}};
static const CUuuid UUID_Unknown5                   = {{0x0C, 0xA5, 0x0B, 0x8C, 0x10, 0x04, 0x92, 0x9A,
                                                        0x89, 0xA7, 0xD0, 0xDF, 0x10, 0xE7, 0x72, 0x86}};
static const CUuuid UUID_TlsNotifyInterface         = {{0x19, 0x5B, 0xCB, 0xF4, 0xD6, 0x7D, 0x02, 0x4A,
                                                        0xAC, 0xC5, 0x1D, 0x29, 0xCE, 0xA6, 0x31, 0xAE}};

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
};
static const struct
{
    int size;
    void* (*func0)(void *param0, void *param1);
    void* (*func1)(void *param0, void *param1);
    void* (*func2)(void *param0, void *param1);
    void* (*func3)(void *param0, void *param1);
    void* (*func4)(void *param0);
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
 * TlsNotifyInterface
 */
struct TlsNotifyInterface_table
{
    int size;
    CUresult (WINAPI *Set)(void **handle, void *callback, void *data);
    CUresult (WINAPI *Remove)(void *handle, void *param1);
};

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

struct Unknown1_table Unknown1_Impl =
{
    sizeof(struct Unknown1_table),
    Unknown1_func0_relay,
    Unknown1_func1_relay,
    Unknown1_func2_relay,
    Unknown1_func3_relay,
    Unknown1_func4_relay,
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
    snprintf(buffer, size, "{0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, " \
                            "0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X}",
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

    FIXME("Unknown UUID: %s, error: %d\n", cuda_print_uuid(uuid, buffer, sizeof(buffer)), orig_result);
    return CUDA_ERROR_UNKNOWN;
}
