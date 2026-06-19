#!/bin/bash
g++ -std=c++20 -O0 \
  -I include \
  -o beldex_test \
  beldex_test.cpp \
  Build/src/libbchat-network.a \
  Build/src/libbchat-util.a \
  Build/src/libbchat-crypto.a \
  Build/src/libbchat-config.a \
  Build/src/libversion.a \
  Build/proto/libbchat-protos.a \
  Build/external/session-router/src/libsession-router.a \
  Build/external/session-router/src/libsession-router-core.a \
  Build/external/session-router/src/libsession-router-core-utils.a \
  Build/external/session-router/src/libsession-router-conf.a \
  Build/external/session-router/src/libsession-router-cryptography.a \
  Build/external/session-router/src/libsession-router-addressing.a \
  Build/external/session-router/src/libsession-router-utils.a \
  Build/external/session-router/src/libsession-router-contact.a \
  Build/external/session-router/src/libsession-router-dns.a \
  Build/external/session-router/src/libsession-router-ip.a \
  Build/external/session-router/src/libsession-router-nodedb.a \
  Build/external/session-router/src/libsession-router-path.a \
  Build/external/session-router/external/libmlkem_native768.a \
  Build/external/session-router/external/oxen-libquic/src/libquic.a \
  Build/external/session-router/external/oxen-libquic/external/oxen-logging/liboxen-logging.a \
  Build/external/session-router/external/oxen-libquic/external/oxen-logging/spdlog/libspdlog.a \
  Build/external/session-router/external/oxen-libquic/external/oxen-logging/fmt/libfmt.a \
  Build/external/libsodium-internal/libsodium-internal.a \
  Build/external/zstd/build/cmake/lib/libzstd.a \
  Build/external/simdutf/src/libsimdutf.a \
  Build/external/protobuf/libprotobuf-lite.a \
  Build/static-deps/lib/libgnutls.a \
  Build/static-deps/lib/libnettle.a \
  Build/static-deps/lib/libhogweed.a \
  Build/static-deps/lib/libgmp.a \
  Build/static-deps/lib/libngtcp2.a \
  Build/static-deps/lib/libngtcp2_crypto_gnutls.a \
  Build/static-deps/lib/libidn2.a \
  Build/static-deps/lib/libunistring.a \
  Build/static-deps/lib/libtasn1.a \
  Build/static-deps/lib/libevent.a \
  Build/static-deps/lib/libevent_core.a \
  Build/static-deps/lib/libevent_pthreads.a \
  Build/static-deps/lib/libiconv.a \
  Build/static-deps/lib/libcharset.a \
  -lpthread -lm -ldl
