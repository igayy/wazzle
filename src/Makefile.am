# Copyright (c) 2013-2016 The Wazzle Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

WAZZLE_INCLUDES=-I$(builddir) $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

WAZZLE_INCLUDES += -I$(srcdir)/secp256k1/include
WAZZLE_INCLUDES += $(UNIVALUE_CFLAGS)

LIBWAZZLE_SERVER=libwazzle_server.a
LIBWAZZLE_COMMON=libwazzle_common.a
LIBWAZZLE_CONSENSUS=libwazzle_consensus.a
LIBWAZZLE_CLI=libwazzle_cli.a
LIBWAZZLE_UTIL=libwazzle_util.a
LIBWAZZLE_CRYPTO_BASE=crypto/libwazzle_crypto_base.a
LIBWAZZLEQT=qt/libwazzleqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBWAZZLE_ZMQ=libwazzle_zmq.a
endif
if BUILD_WAZZLE_LIBS
LIBWAZZLECONSENSUS=libwazzleconsensus.la
endif
if ENABLE_WALLET
LIBWAZZLE_WALLET=libwazzle_wallet.a
LIBWAZZLE_WALLET_TOOL=libwazzle_wallet_tool.a
endif

LIBWAZZLE_CRYPTO= $(LIBWAZZLE_CRYPTO_BASE)
if ENABLE_SSE41
LIBWAZZLE_CRYPTO_SSE41 = crypto/libwazzle_crypto_sse41.a
LIBWAZZLE_CRYPTO += $(LIBWAZZLE_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBWAZZLE_CRYPTO_AVX2 = crypto/libwazzle_crypto_avx2.a
LIBWAZZLE_CRYPTO += $(LIBWAZZLE_CRYPTO_AVX2)
endif
if ENABLE_SHANI
LIBWAZZLE_CRYPTO_SHANI = crypto/libwazzle_crypto_shani.a
LIBWAZZLE_CRYPTO += $(LIBWAZZLE_CRYPTO_SHANI)
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBWAZZLE_CRYPTO) \
  $(LIBWAZZLE_UTIL) \
  $(LIBWAZZLE_COMMON) \
  $(LIBWAZZLE_CONSENSUS) \
  $(LIBWAZZLE_SERVER) \
  $(LIBWAZZLE_CLI) \
  $(LIBWAZZLE_WALLET) \
  $(LIBWAZZLE_WALLET_TOOL) \
  $(LIBWAZZLE_ZMQ)

lib_LTLIBRARIES = $(LIBWAZZLECONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_WAZZLED
  bin_PROGRAMS += wazzled
endif

if BUILD_WAZZLE_CLI
  bin_PROGRAMS += wazzle-cli
endif
if BUILD_WAZZLE_TX
  bin_PROGRAMS += wazzle-tx
endif
if ENABLE_WALLET
if BUILD_WAZZLE_WALLET
  bin_PROGRAMS += wazzle-wallet
endif
endif

.PHONY: FORCE check-symbols check-security
# wazzle core #
WAZZLE_CORE_H = \
  addrdb.h \
  addrman.h \
  attributes.h \
  banman.h \
  base58.h \
  bech32.h \
  bloom.h \
  blockencodings.h \
  blockfilter.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/assumptions.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_check.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  flatfile.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  index/base.h \
  index/blockfilterindex.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  interfaces/chain.h \
  interfaces/handler.h \
  interfaces/node.h \
  interfaces/wallet.h \
  key.h \
  key_io.h \
  dbwrapper.h \
  limitedmap.h \
  logging.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_permissions.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  node/coin.h \
  node/coinstats.h \
  node/psbt.h \
  node/transaction.h \
  noui.h \
  optional.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  policy/settings.h \
  pow.h \
  protocol.h \
  psbt.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/rawtransaction_util.h \
  rpc/register.h \
  rpc/request.h \
  rpc/server.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/keyorigin.h \
  script/sigcache.h \
  script/sign.h \
  script/signingprovider.h \
  script/standard.h \
  shutdown.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util/bip32.h \
  util/bytevectorhash.h \
  util/error.h \
  util/fees.h \
  util/system.h \
  util/memory.h \
  util/moneystr.h \
  util/rbf.h \
  util/string.h \
  util/threadnames.h \
  util/time.h \
  util/translation.h \
  util/url.h \
  util/validation.h \
  validation.h \
  validationinterface.h \
  variable_block_reward.h \
  versionbits.h \
  versionbitsinfo.h \
  walletinitinterface.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/ismine.h \
  wallet/load.h \
  wallet/psbtwallet.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/wallettool.h \
  wallet/walletutil.h \
  wallet/coinselection.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libwazzle_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between wazzled and wazzle-qt
# Contains code accessing mempool and chain state that is meant to be separated
# from wallet and gui code (see node/README.md). Shared code should go in
# libwazzle_common or libwazzle_util libraries, instead.
libwazzle_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libwazzle_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libwazzle_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  banman.cpp \
  blockencodings.cpp \
  blockfilter.cpp \
  chain.cpp \
  consensus/tx_verify.cpp \
  flatfile.cpp \
  httprpc.cpp \
  httpserver.cpp \
  index/base.cpp \
  index/blockfilterindex.cpp \
  index/txindex.cpp \
  interfaces/chain.cpp \
  interfaces/node.cpp \
  init.cpp \
  dbwrapper.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  node/coin.cpp \
  node/coinstats.cpp \
  node/psbt.cpp \
  node/transaction.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/rbf.cpp \
  policy/settings.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  shutdown.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  variable_block_reward.cpp \
  versionbits.cpp \
  $(WAZZLE_CORE_H)

if ENABLE_WALLET
libwazzle_server_a_SOURCES += wallet/init.cpp
endif
if !ENABLE_WALLET
libwazzle_server_a_SOURCES += dummywallet.cpp
endif

if ENABLE_ZMQ
libwazzle_zmq_a_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES) $(ZMQ_CFLAGS)
libwazzle_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libwazzle_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp \
  zmq/zmqrpc.cpp
endif


# wallet: shared between wazzled and wazzle-qt, but only linked
# when wallet enabled
libwazzle_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES)
libwazzle_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libwazzle_wallet_a_SOURCES = \
  interfaces/wallet.cpp \
  wallet/coincontrol.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/ismine.cpp \
  wallet/load.cpp \
  wallet/psbtwallet.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  wallet/coinselection.cpp \
  $(WAZZLE_CORE_H)

libwazzle_wallet_tool_a_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES)
libwazzle_wallet_tool_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libwazzle_wallet_tool_a_SOURCES = \
  wallet/wallettool.cpp \
  $(WAZZLE_CORE_H)

# crypto primitives library
crypto_libwazzle_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libwazzle_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libwazzle_crypto_base_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha_poly_aead.h \
  crypto/chacha_poly_aead.cpp \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hkdf_sha256_32.cpp \
  crypto/hkdf_sha256_32.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/poly1305.h \
  crypto/poly1305.cpp \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/siphash.cpp \
  crypto/siphash.h

if USE_ASM
crypto_libwazzle_crypto_base_a_SOURCES += crypto/sha256_sse4.cpp
endif

crypto_libwazzle_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libwazzle_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libwazzle_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libwazzle_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libwazzle_crypto_sse41_a_SOURCES = crypto/sha256_sse41.cpp

crypto_libwazzle_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libwazzle_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libwazzle_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libwazzle_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libwazzle_crypto_avx2_a_SOURCES = crypto/sha256_avx2.cpp

crypto_libwazzle_crypto_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libwazzle_crypto_shani_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libwazzle_crypto_shani_a_CXXFLAGS += $(SHANI_CXXFLAGS)
crypto_libwazzle_crypto_shani_a_CPPFLAGS += -DENABLE_SHANI
crypto_libwazzle_crypto_shani_a_SOURCES = crypto/sha256_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libwazzle_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES)
libwazzle_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libwazzle_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/tx_check.cpp \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/wazzleconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  span.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  util/strencodings.cpp \
  util/strencodings.h \
  version.h

# common: shared between wazzled, and wazzle-qt and non-server tools
libwazzle_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES)
libwazzle_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libwazzle_common_a_SOURCES = \
  base58.cpp \
  bech32.cpp \
  bloom.cpp \
  chainparams.cpp \
  chain.cpp \
  pow.cpp \  
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  key_io.cpp \
  merkleblock.cpp \
  netaddress.cpp \
  netbase.cpp \
  net_permissions.cpp \
  outputtype.cpp \
  policy/feerate.cpp \
  policy/policy.cpp \
  protocol.cpp \
  psbt.cpp \
  rpc/rawtransaction_util.cpp \
  rpc/util.cpp \
  scheduler.cpp \
  script/descriptor.cpp \
  script/sign.cpp \
  script/signingprovider.cpp \
  script/standard.cpp \
  variable_block_reward.cpp \
  versionbitsinfo.cpp \
  warnings.cpp \
  $(WAZZLE_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libwazzle_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES)
libwazzle_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libwazzle_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity_fdelt.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  interfaces/handler.cpp \
  logging.cpp \
  random.cpp \
  rpc/request.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util/bip32.cpp \
  util/bytevectorhash.cpp \
  util/error.cpp \
  util/fees.cpp \
  util/system.cpp \
  util/moneystr.cpp \
  util/rbf.cpp \
  util/threadnames.cpp \
  util/strencodings.cpp \
  util/string.cpp \
  util/time.cpp \
  util/url.cpp \
  util/validation.cpp \
  $(WAZZLE_CORE_H)

if GLIBC_BACK_COMPAT
libwazzle_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between wazzle-cli and wazzle-qt
libwazzle_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES)
libwazzle_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libwazzle_cli_a_SOURCES = \
  rpc/client.cpp \
  $(WAZZLE_CORE_H)

nodist_libwazzle_util_a_SOURCES = $(srcdir)/obj/build.h
#

# wazzled binary #
wazzled_SOURCES = wazzled.cpp
wazzled_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES)
wazzled_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
wazzled_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
wazzled_SOURCES += wazzled-res.rc
endif

# Libraries below may be listed more than once to resolve circular dependencies (see
# https://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking#circular-dependency)
wazzled_LDADD = \
  $(LIBWAZZLE_SERVER) \
  $(LIBWAZZLE_WALLET) \
  $(LIBWAZZLE_SERVER) \
  $(LIBWAZZLE_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBWAZZLE_UTIL) \
  $(LIBWAZZLE_ZMQ) \
  $(LIBWAZZLE_CONSENSUS) \
  $(LIBWAZZLE_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

wazzled_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# wazzle-cli binary #
wazzle_cli_SOURCES = wazzle-cli.cpp
wazzle_cli_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES) $(EVENT_CFLAGS)
wazzle_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
wazzle_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
wazzle_cli_SOURCES += wazzle-cli-res.rc
endif

wazzle_cli_LDADD = \
  $(LIBWAZZLE_CLI) \
  $(LIBUNIVALUE) \
  $(LIBWAZZLE_UTIL) \
  $(LIBWAZZLE_CRYPTO)

wazzle_cli_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# wazzle-tx binary #
wazzle_tx_SOURCES = wazzle-tx.cpp
wazzle_tx_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES)
wazzle_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
wazzle_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
wazzle_tx_SOURCES += wazzle-tx-res.rc
endif

wazzle_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBWAZZLE_COMMON) \
  $(LIBWAZZLE_UTIL) \
  $(LIBWAZZLE_CONSENSUS) \
  $(LIBWAZZLE_CRYPTO) \
  $(LIBSECP256K1)

wazzle_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# wazzle-wallet binary #
wazzle_wallet_SOURCES = wazzle-wallet.cpp
wazzle_wallet_CPPFLAGS = $(AM_CPPFLAGS) $(WAZZLE_INCLUDES)
wazzle_wallet_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
wazzle_wallet_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
wazzle_wallet_SOURCES += wazzle-wallet-res.rc
endif

wazzle_wallet_LDADD = \
  $(LIBWAZZLE_WALLET_TOOL) \
  $(LIBWAZZLE_WALLET) \
  $(LIBWAZZLE_COMMON) \
  $(LIBWAZZLE_CONSENSUS) \
  $(LIBWAZZLE_UTIL) \
  $(LIBWAZZLE_CRYPTO) \
  $(LIBWAZZLE_ZMQ) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1) \
  $(LIBUNIVALUE)

wazzle_wallet_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(CRYPTO_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(MINIUPNPC_LIBS) $(ZMQ_LIBS)
#

# wazzleconsensus library #
if BUILD_WAZZLE_LIBS
include_HEADERS = script/wazzleconsensus.h
libwazzleconsensus_la_SOURCES = support/cleanse.cpp $(crypto_libwazzle_crypto_base_a_SOURCES) $(libwazzle_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libwazzleconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libwazzleconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libwazzleconsensus_la_LIBADD = $(LIBSECP256K1)
libwazzleconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_WAZZLE_INTERNAL
libwazzleconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/wazzle-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/wazzle-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/wazzle-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/wazzle-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(PYTHON) $(top_srcdir)/contrib/devtools/security-check.py $(bin_PROGRAMS)
endif

if ENABLE_BIP70
%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<
endif

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
