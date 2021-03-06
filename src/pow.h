// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2019-2020 The Wazzle Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef WAZZLE_POW_H
#define WAZZLE_POW_H

#include <consensus/params.h>
#include <primitives/block.h>

#include <stdint.h>

class CBlockHeader;
class CBlockIndex;
class uint256;

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params&);
unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params&);

/** Check whether a block hash satisfies the proof-of-work requirement specified by nBits */
bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params&);
bool CheckProofOfWork(int height, uint256 hash, CBlock &block, const Consensus::Params& params);

#endif // WAZZLE_POW_H
