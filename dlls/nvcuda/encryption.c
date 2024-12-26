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

#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "wine/debug.h"
#include "wine/wgl.h"
#include "cuda.h"
#include "encryption.h"

WINE_DEFAULT_DEBUG_CHANNEL(nvcuda);

// Encryption hash tables of sorts
static const unsigned char encryptPart1Table[64] = {
    0x6b, 0xcf, 0x32, 0x0f, 0xa4, 0x49, 0xd3, 0xa8, 0x33, 0xf8, 0xd0, 0x8e, 0x12, 0x4e, 0xa8, 0x00,
    0xeb, 0x94, 0x2c, 0x8f, 0x34, 0x49, 0xde, 0xf6, 0xbf, 0x29, 0x91, 0x20, 0xc7, 0x65, 0xf6, 0xba,
    0x78, 0x5c, 0x66, 0x27, 0xa7, 0xb2, 0x73, 0x92, 0xdb, 0x22, 0x1e, 0x20, 0x14, 0x6f, 0x87, 0xff,
    0xa5, 0xc3, 0x18, 0x01, 0x66, 0x64, 0xa5, 0x0e, 0x70, 0x51, 0x52, 0xa7, 0x80, 0x4b, 0xdf, 0xef,
};

static const unsigned char encryptRoundTable[256] = {
    0x29, 0x2E, 0x43, 0xC9, 0xA2, 0xD8, 0x7C, 0x01, 0x3D, 0x36, 0x54, 0xA1, 0xEC, 0xF0, 0x06, 0x13,
    0x62, 0xA7, 0x05, 0xF3, 0xC0, 0xC7, 0x73, 0x8C, 0x98, 0x93, 0x2B, 0xD9, 0xBC, 0x4C, 0x82, 0xCA,
    0x1E, 0x9B, 0x57, 0x3C, 0xFD, 0xD4, 0xE0, 0x16, 0x67, 0x42, 0x6F, 0x18, 0x8A, 0x17, 0xE5, 0x12,
    0xBE, 0x4E, 0xC4, 0xD6, 0xDA, 0x9E, 0xDE, 0x49, 0xA0, 0xFB, 0xF5, 0x8E, 0xBB, 0x2F, 0xEE, 0x7A,
    0xA9, 0x68, 0x79, 0x91, 0x15, 0xB2, 0x07, 0x3F, 0x94, 0xC2, 0x10, 0x89, 0x0B, 0x22, 0x5F, 0x21,
    0x80, 0x7F, 0x5D, 0x9A, 0x5A, 0x90, 0x32, 0x27, 0x35, 0x3E, 0xCC, 0xE7, 0xBF, 0xF7, 0x97, 0x03,
    0xFF, 0x19, 0x30, 0xB3, 0x48, 0xA5, 0xB5, 0xD1, 0xD7, 0x5E, 0x92, 0x2A, 0xAC, 0x56, 0xAA, 0xC6,
    0x4F, 0xB8, 0x38, 0xD2, 0x96, 0xA4, 0x7D, 0xB6, 0x76, 0xFC, 0x6B, 0xE2, 0x9C, 0x74, 0x04, 0xF1,
    0x45, 0x9D, 0x70, 0x59, 0x64, 0x71, 0x87, 0x20, 0x86, 0x5B, 0xCF, 0x65, 0xE6, 0x2D, 0xA8, 0x02,
    0x1B, 0x60, 0x25, 0xAD, 0xAE, 0xB0, 0xB9, 0xF6, 0x1C, 0x46, 0x61, 0x69, 0x34, 0x40, 0x7E, 0x0F,
    0x55, 0x47, 0xA3, 0x23, 0xDD, 0x51, 0xAF, 0x3A, 0xC3, 0x5C, 0xF9, 0xCE, 0xBA, 0xC5, 0xEA, 0x26,
    0x2C, 0x53, 0x0D, 0x6E, 0x85, 0x28, 0x84, 0x09, 0xD3, 0xDF, 0xCD, 0xF4, 0x41, 0x81, 0x4D, 0x52,
    0x6A, 0xDC, 0x37, 0xC8, 0x6C, 0xC1, 0xAB, 0xFA, 0x24, 0xE1, 0x7B, 0x08, 0x0C, 0xBD, 0xB1, 0x4A,
    0x78, 0x88, 0x95, 0x8B, 0xE3, 0x63, 0xE8, 0x6D, 0xE9, 0xCB, 0xD5, 0xFE, 0x3B, 0x00, 0x1D, 0x39,
    0xF2, 0xEF, 0xB7, 0x0E, 0x66, 0x58, 0xD0, 0xE4, 0xA6, 0x77, 0x72, 0xF8, 0xEB, 0x75, 0x4B, 0x0A,
    0x31, 0x44, 0x50, 0xB4, 0x8F, 0xED, 0x1F, 0x1A, 0xDB, 0x99, 0x8D, 0x33, 0x9F, 0x11, 0x83, 0x14,
};

static void WINAPI encrypt_hash_round1(unsigned char input[], const unsigned char constant)
{
    unsigned char index = input[64];
    input[index + 32] = input[index] ^ constant;
    input[index + 16] = constant;
    input[index + 48] ^= encryptRoundTable[input[65] ^ constant];
    unsigned char temp = input[index + 48];
    index = (index + 1) & 0xf;
    input[64] = index;
    input[65] = temp;
    if (index != 0)
        return;
    unsigned char i = 0;
    for (unsigned char j = 0 ; j < 18 ; j++) {
        for (int k = 0 ; k < 48 ; k++) {
            input[k] ^= encryptRoundTable[i];
            i = input[k];
        }
        i += j;
    }
}

static inline void WINAPI encrypt_part1(unsigned char aux[])
{
    unsigned char i = 13;
    unsigned char temp = 0x8b;
    do {
        unsigned char part1 = encryptPart1Table[i + 16] ^
            encryptPart1Table[i + 32] ^
            encryptPart1Table[i + 48];
        unsigned char part2 = temp ^
            encryptPart1Table[i] ^
            encryptPart1Table[i + 16];
        temp = ~(part1 ^ temp);
        i = (part2 & 0xf);
        aux[part2 >> 4] = part1;
    } while (i != 13);
}

static inline void WINAPI encrypt_part2(unsigned char res[], unsigned char aux[16])
{
    for (int i = 0 ; i < 16 ; i++)
        encrypt_hash_round1(res, aux[i] ^ 0x36);
}

static inline void WINAPI encrypt_part3(unsigned char res[], EncryptInput1 *input1)
{
    for (int i = 0 ; i < 48 ; i++)
        encrypt_hash_round1(res, ((unsigned char *)input1)[i]);
}

static inline CUresult WINAPI get_part2(int ordinal, EncryptInput2 *part2)
{
    int device;
    if (wine_cuDeviceGet(&device, ordinal)) return CUDA_ERROR_UNKNOWN;
    if (wine_cuDeviceGetUuid(&part2->uuid, device)) return CUDA_ERROR_UNKNOWN;
    if (wine_cuDeviceGetAttribute(&part2->pciBus, CU_DEVICE_ATTRIBUTE_PCI_BUS_ID, device)) return CUDA_ERROR_UNKNOWN;
    if (wine_cuDeviceGetAttribute(&part2->pciDevice, CU_DEVICE_ATTRIBUTE_PCI_DEVICE_ID, device)) return CUDA_ERROR_UNKNOWN;
    if (wine_cuDeviceGetAttribute(&part2->pciDomain, CU_DEVICE_ATTRIBUTE_PCI_DOMAIN_ID, device)) return CUDA_ERROR_UNKNOWN;
    return CUDA_SUCCESS;
}

static inline void WINAPI encrypt_part4(unsigned char res[])
{
    int count;
    if (wine_cuDeviceGetCount(&count)){
        TRACE("Error getting Device Count\n");
        return;
    }
    for (int i = 0 ; i < count ; i++) {
        EncryptInput2 part2;
        if (get_part2(i, &part2)){
            TRACE("Error getting GPU data\n");
            return;
        }
        for (int j = 0 ; j < 28 ; j++)
            encrypt_hash_round1(res, ((unsigned char *)&part2)[j]);
    }
}

static inline void WINAPI encrypt_part5(unsigned char res[])
{
    unsigned char rounds = (unsigned char)16 - res[64];
    for (unsigned char i = 0 ; i < rounds ; i++)
        encrypt_hash_round1(res, rounds);
}

static inline void WINAPI encrypt_part6(unsigned char res[])
{
    for (int i = 48 ; i < 64 ; i++)
        encrypt_hash_round1(res, res[i]);
}

static inline void WINAPI encrypt_part7(unsigned char res[], unsigned char aux[])
{
    unsigned char buf[16];
    memcpy(buf, res, 16);
    memset(res, 0, 16);
    memset(res + 48, 0, 18);
    for (unsigned char i = 0 ; i < 16 ; i++)
        encrypt_hash_round1(res, aux[i] ^ 0x5c);
    for (unsigned char i = 0 ; i < 16 ; i++)
        encrypt_hash_round1(res, buf[i]);
}

CUresult __attribute((visibility("hidden"))) WINAPI encrypt(EncryptInput1 *input1, __uint128_t *res) {
    if (input1->cudaVersion % 10 < 2) {
        static unsigned char code[16] = {
            0x5c, 0x67, 0xcb, 0x03, 0x1c, 0x18, 0x41, 0x33,
            0xe8, 0xd1, 0x4c, 0x1f, 0xaa, 0x83, 0xd3, 0x8e
        };
        memcpy(res, code, sizeof(__uint128_t));
        if (input1->cudaVersion % 10 == 1) {
            ((unsigned char *)res)[7] = 24;
        }
    } else {
        unsigned char result[66] = {};
        unsigned char aux[16] = {};
        encrypt_part1(aux);
        encrypt_part2(result, aux);
        encrypt_part3(result, input1);
        encrypt_part4(result);
        encrypt_part5(result);
        encrypt_part6(result);
        encrypt_part7(result, aux);
        encrypt_part5(result);
        encrypt_part6(result);
        memcpy(res, result, sizeof(__uint128_t));
    }
    return CUDA_SUCCESS;
}
