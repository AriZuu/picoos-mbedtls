/*
 * Copyright (c) 2017, Ari Suutari <ari@stonepile.fi>.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)

#include "picoos-mbedtls.h"
#include "mbedtls/platform.h"

#if defined(MBEDTLS_PLATFORM_NV_SEED_ALT)

static int nvSeedRead(unsigned char* buf, size_t bufLen)
{
  FILE *file;
  size_t len;

  file = fopen(MBEDTLS_PLATFORM_STD_NV_SEED_FILE, "r");
  if (file == NULL) {

    // If seedfile is not found, read initial one from rom.
    file = fopen(MBEDTLS_PLATFORM_STD_NV_SEED_FILE_INIT, "r");
    if (file == NULL)
      return -1;
  }

  len = fread(buf, 1, bufLen, file);
  fclose(file);

  if (len != bufLen)
    return -1;

  return len;
}

static int nvSeedWrite(unsigned char *buf, size_t bufLen)
{
  FILE* file;
  size_t len;

  file = fopen(MBEDTLS_PLATFORM_STD_NV_SEED_FILE, "w");
  if (file == NULL)
    return -1;

  len = fwrite(buf, 1, bufLen, file);
  fclose(file);

  if (len != bufLen)
    return -1;

  return len;
}

void mbedtls_platform_set_nv_seed_picoos()
{
  mbedtls_platform_set_nv_seed(nvSeedRead, nvSeedWrite);
}

#endif
#endif
