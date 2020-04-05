// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2019-2020 The Wazzle Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include "pow.h"
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
// $ date --date='@1544800000'
// Fri Dec 14 09:06:40 CST 2018

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{  
    const char* pszTimestamp = "The Times 05/April/2020 Corona Kill my friend";
    const CScript genesisOutputScript = CScript() << ParseHex("4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac
") << OP_CHECKSIG;
   return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}



/**
 * Main network
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main"; 
        consensus.nSubsidyHalvingInterval = 210000; // #blocks before halving occurs. every 4 years
        consensus.BIP16Exception = uint256S();
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S();
        consensus.BIP65Height = 0; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.BIP66Height = 0; // 00000000000000000379eaa19dce8c9b722d46ae6a57c2f1a988119488b50931

        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing   

        consensus.CSVHeight = 1;//419328; // 000000000000000004a1b34462cb8aeebd5799177f7a29cf28f2d1961716b5b5
        consensus.SegwitHeight = 1;//481824; // 0000000000000000001c8018d9cb3b742ef25114f27563e3fc4a1902167f9893
     
        consensus.MinBIP9WarningHeight = consensus.SegwitHeight + consensus.nMinerConfirmationWindow;
        consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 8 * 60 * 60;  // 8 hours, difficulty update time in seconds
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008


        // nMinimumChainWork is a value that is updated at every release. It is retrieved from the Debug command
        //            getblockchaininfo 
        consensus.nMinimumChainWork = uint256S("0000000000000000000000000000000000000000000000000000000100010001");

                                                
        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("000000000000000000000000000000000000000000000000000002e002e002e0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xe9;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xb1;
        pchMessageStart[3] = 0xa2;
        nDefaultPort = 7222;
        nPruneAfterHeight = 100000;

        uint32_t nTime=1584397119;
        uint32_t nNonce=644556601;
		
		m_assumed_blockchain_size = 240;
		m_assumed_chain_state_size = 3;
       
        // @"consensus.hashGenesisBlock: 000000004c2738ff52ee6dc039d4fde2f3292fed9afa9d712f895d7094f8d350\r\n"
        // @"genesis.hashMerkleRoot: c36c4216baf256beb34d939e7aa158a54b7488be996e8bdab8d83ff9c73f1f4d\r\n"
        // @"genesis.nNonce: 771851678\r\n"
        // Difficulty bits:
        // Using following formula target can be obtained from any block. For example if a target packed in a block appears as 0x1b0404cb its hexadecimal version will look as following:
        // 0x0404cb * 2**(8*(0x1b - 3)) = 0x00000000000404CB000000000000000000000000000000000000000000000000
        bool proof_of_work_valid = false;
        for (nTime=1586075504; ;nTime++)
        {
            genesis = CreateGenesisBlock(nTime, nNonce, 0x1d00ffff, 1, 50 * COIN);

            for (genesis.nNonce = 2015000626; genesis.nNonce <= 0xfffffff0;genesis.nNonce++)
            {
                proof_of_work_valid = CheckProofOfWork(genesis.GetHash(), genesis.nBits, consensus);
                if (proof_of_work_valid) {
                    break;
                }
            }
            if (proof_of_work_valid) {
                break;
            }

        }

        
        consensus.hashGenesisBlock = genesis.GetHash();
        std::cout << "consensus.hashGenesisBlock: " << consensus.hashGenesisBlock.ToString() << std::endl;
        std::cout << "genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << std::endl;   
        std::cout << "genesis.nNonce: " << genesis.nNonce << std::endl;
        std::cout << "genesis.nTime: " << nTime << std::endl;

                                                         
        assert(consensus.hashGenesisBlock == uint256S("0000000005cd44e06799b38ee8b3e5419f3e363d6e64d9659af658931555db3a"));
        assert(genesis.hashMerkleRoot == uint256S("f76feaba19901283bc0bcceae3a088c42edde0597d3b53e18eadcc4031888d27"));


        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
        vSeeds.emplace_back("seed1.getwazzle.com");
        vSeeds.emplace_back("seed2.getwazzle.com");
        vSeeds.emplace_back("seed3.getwazzle.com");        
        vSeeds.emplace_back("seed4.getwazzle.com");
        vSeeds.emplace_back("seed5.getwazzle.com");
        vSeeds.emplace_back("seed6.getwazzle.com");
        vSeeds.emplace_back("seed7.getwazzle.com");
        vSeeds.emplace_back("seed8.getwazzle.com");
        vSeeds.emplace_back("seed9.getwazzle.com");




        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "bc";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;


        checkpointData = {
            {
                {0,     uint256S("0000000005cd44e06799b38ee8b3e5419f3e363d6e64d9659af658931555db3a")},
            }
        };

        chainTxData = ChainTxData{
            // type     getchaintxstats    in debug console
            /* nTime    */ 1584411581,
            /* nTxCount */ 200,
            /* dTxRate  */ 0.03986500738240877
        };

    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000; // #blocks before halving occurs. every 4 years
        consensus.BIP16Exception = uint256S("notyet");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("notyet");
        consensus.BIP65Height = 0; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.BIP66Height = 0; // 00000000000000000379eaa19dce8c9b722d46ae6a57c2f1a988119488b50931

        consensus.CSVHeight = 1; // 00000000025e930139bac5c6c31a403776da130831ab85be56578f3fa75369bb
        consensus.SegwitHeight = 1; // 00000000002b980fcd729daaa248fd9316a5200e9b367f4ff2c42453e84201ca
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing        
        consensus.MinBIP9WarningHeight = consensus.SegwitHeight + consensus.nMinerConfirmationWindow;
        consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 8 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0000000000000000000000000000000000000000000000000000000000010001");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("00009a004b86c066b21aaffe2325a2bf5cb80ccf572c137cb24086cc83ca0542");


        pchMessageStart[0] = 0xb3;
        pchMessageStart[1] = 0xe0;
        pchMessageStart[2] = 0x87;
        pchMessageStart[3] = 0xe3;
        nDefaultPort = 17222;
        nPruneAfterHeight = 100000;
		m_assumed_blockchain_size = 30;
		m_assumed_chain_state_size = 2;

        uint32_t nTime=1584397119;
        uint32_t nNonce=644556601;
		
		m_assumed_blockchain_size = 240;
		m_assumed_chain_state_size = 3;
       
        // @"consensus.hashGenesisBlock: 000000004c2738ff52ee6dc039d4fde2f3292fed9afa9d712f895d7094f8d350\r\n"
        // @"genesis.hashMerkleRoot: c36c4216baf256beb34d939e7aa158a54b7488be996e8bdab8d83ff9c73f1f4d\r\n"
        // @"genesis.nNonce: 771851678\r\n"
        // Difficulty bits:
        // Using following formula target can be obtained from any block. For example if a target packed in a block appears as 0x1b0404cb its hexadecimal version will look as following:
        // 0x0404cb * 2**(8*(0x1b - 3)) = 0x00000000000404CB000000000000000000000000000000000000000000000000
        bool proof_of_work_valid = false;
        for (nTime=1584397119; ;nTime++)
        {
            genesis = CreateGenesisBlock(nTime, nNonce, 0x1d00ffff, 1, 50 * COIN);

            for (genesis.nNonce = 644556601; genesis.nNonce <= 0xfffffff0;genesis.nNonce++)
            {
                proof_of_work_valid = CheckProofOfWork(genesis.GetHash(), genesis.nBits, consensus);
                if (proof_of_work_valid) {
                    break;
                }
            }
            if (proof_of_work_valid) {
                break;
            }

        }

        
        consensus.hashGenesisBlock = genesis.GetHash();
        std::cout << "consensus.hashGenesisBlock: " << consensus.hashGenesisBlock.ToString() << std::endl;
        std::cout << "genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << std::endl;   
        std::cout << "genesis.nNonce: " << genesis.nNonce << std::endl;
        std::cout << "genesis.nTime: " << nTime << std::endl;

                                                         
        assert(consensus.hashGenesisBlock == uint256S("notyet"));
        assert(genesis.hashMerkleRoot == uint256S("notyet"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet-seed.wazzle.jonasschnelli.ch");
        vSeeds.emplace_back("seed.tbtc.petertodd.org");
        vSeeds.emplace_back("seed.testnet.wazzle.sprovoost.nl");
        vSeeds.emplace_back("testnet-seed.bluematt.me"); // Just a static list of stable node(s), only supports x9

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tb";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;


        checkpointData = {
            {
                {1,   uint256S("0000000033cb83efac961393f5ee81c4da54442fbc243f3df2f5b5d5a648b90e")},

            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 4096 0000000000000037a8cd3e06cd5edbfe9dd1dbcc5dacab279376ef7cfc2b4c75
            /* nTime    */ 1531929919,
            /* nTxCount */ 19438708,
            /* dTxRate  */ 0.626
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 0; // BIP34 activated on regtest (Used in functional tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0; // BIP65 activated on regtest (Used in functional tests)
        consensus.BIP66Height = 0; // BIP66 activated on regtest (Used in functional tests)
        consensus.CSVHeight = 0; // CSV activated on regtest (Used in rpc activation tests)
        consensus.SegwitHeight = 0; // SEGWIT is always activated on regtest unless overridden
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xe3;
        pchMessageStart[1] = 0xdb;
        pchMessageStart[2] = 0xe9;
        pchMessageStart[3] = 0xf8;
        nDefaultPort = 18444;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

        genesis = CreateGenesisBlock(1296688602, 2, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));
        //assert(genesis.hashMerkleRoot == uint256S("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;

        checkpointData = {
            {
                {0, uint256S("0x00009a004b86c066b21aaffe2325a2bf5cb80ccf572c137cb24086cc83ca0542")},
            }

        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "bcrt";
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (gArgs.IsArgSet("-segwitheight")) {
        int64_t height = gArgs.GetArg("-segwitheight", consensus.SegwitHeight);
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
