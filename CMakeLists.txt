#
# Copyright (c) 2019, Ari Suutari <ari@stonepile.fi>.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. The name of the author may not be used to endorse or promote
#     products derived from this software without specific prior written
#     permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
# INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.

include_guard(GLOBAL)

set(ML mbedtls/library)
set(SRC_CRYPTO
    ${ML}/aes.c
    ${ML}/aesni.c
    ${ML}/arc4.c
    ${ML}/asn1parse.c
    ${ML}/asn1write.c
    ${ML}/base64.c
    ${ML}/bignum.c
    ${ML}/blowfish.c
    ${ML}/camellia.c
    ${ML}/ccm.c
    ${ML}/cipher.c
    ${ML}/cipher_wrap.c
    ${ML}/cmac.c
    ${ML}/ctr_drbg.c
    ${ML}/des.c
    ${ML}/dhm.c
    ${ML}/ecdh.c
    ${ML}/ecdsa.c
    ${ML}/ecjpake.c
    ${ML}/ecp.c
    ${ML}/ecp_curves.c
    ${ML}/entropy.c
    ${ML}/entropy_poll.c
    ${ML}/error.c
    ${ML}/gcm.c
    ${ML}/havege.c
    ${ML}/hmac_drbg.c
    ${ML}/md.c
    ${ML}/md2.c
    ${ML}/md4.c
    ${ML}/md5.c
    ${ML}/md_wrap.c
    ${ML}/memory_buffer_alloc.c
    ${ML}/oid.c
    ${ML}/padlock.c
    ${ML}/pem.c
    ${ML}/pk.c
    ${ML}/pk_wrap.c
    ${ML}/pkcs12.c
    ${ML}/pkcs5.c
    ${ML}/pkparse.c
    ${ML}/pkwrite.c
    ${ML}/platform.c
    ${ML}/ripemd160.c
    ${ML}/rsa.c
    ${ML}/sha1.c
    ${ML}/sha256.c
    ${ML}/sha512.c
    ${ML}/threading.c
    ${ML}/timing.c
    ${ML}/version.c
    ${ML}/version_features.c
    ${ML}/xtea.c)

set(SRC_X509
    ${ML}/certs.c
    ${ML}/pkcs11.c
    ${ML}/x509.c
    ${ML}/x509_create.c
    ${ML}/x509_crl.c
    ${ML}/x509_crt.c
    ${ML}/x509_csr.c
    ${ML}/x509write_crt.c
    ${ML}/x509write_csr.c)

set(SRC_TLS
    ${ML}/debug.c
    ${ML}/net_sockets.c
    ${ML}/ssl_cache.c
    ${ML}/ssl_ciphersuites.c
    ${ML}/ssl_cli.c
    ${ML}/ssl_cookie.c
    ${ML}/ssl_srv.c
    ${ML}/ssl_ticket.c
    ${ML}/ssl_tls.c)

set(SRC_ALT
    threading_alt.c
    timing_alt.c
    nv_seed_alt.c)

add_peer_directory(${PICOOS_DIR})
add_peer_directory(../picoos-lwip)
add_peer_directory(../picoos-micro)

add_library(picoos-mbedtls STATIC ${SRC_CRYPTO} ${SRC_X509} ${SRC_TLS} ${SRC_ALT})

target_include_directories(picoos-mbedtls
  PUBLIC mbedtls/include ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(picoos-mbedtls picoos-ow picoos-lwip picoos-micro picoos)
target_compile_definitions(picoos-mbedtls PUBLIC MBEDTLS_CONFIG_FILE=<mbedtls-cfg.h>)
target_include_directories(picoos-mbedtls PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} mbedtls/include)
target_compile_options(picoos-mbedtls PRIVATE -Wno-unused-variable)
