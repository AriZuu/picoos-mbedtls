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

#if defined(MBEDTLS_THREADING_C) && defined(MBEDTLS_THREADING_ALT)

#include "mbedtls/threading.h"

static void mutexInit(mbedtls_threading_mutex_t *mutex)
{
  if (mutex == NULL || mutex->valid)
    return;

  mutex->mutex = nosMutexCreate(0, "tls*");
  mutex->valid = mutex->mutex != NULL;
}

static void mutexFree(mbedtls_threading_mutex_t *mutex)
{
  if (mutex == NULL || !mutex->valid)
    return;

  nosMutexDestroy(mutex->mutex);
  mutex->valid = 0;
}

static int mutexLock(mbedtls_threading_mutex_t *mutex)
{
  if (mutex == NULL || ! mutex->valid)
      return MBEDTLS_ERR_THREADING_BAD_INPUT_DATA;

  nosMutexLock(mutex->mutex);
  return 0;
}

static int mutexUnlock(mbedtls_threading_mutex_t *mutex)
{
  if (mutex == NULL || ! mutex->valid)
    return MBEDTLS_ERR_THREADING_BAD_INPUT_DATA;

  nosMutexUnlock(mutex->mutex);
  return 0;
}

void mbedtls_threading_set_picoos(void)
{
  mbedtls_threading_set_alt(mutexInit,
                            mutexFree,
                            mutexLock,
                            mutexUnlock);
}

#endif
