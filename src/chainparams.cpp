// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
//Copyright (c) 2019 The Dicenode developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (      0, uint256("000008595c4d29988f4653f65be09f49b6300395023dbc0da026ce94a417c5d3"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1643500023, // * UNIX timestamp of last checkpoint block
    0,       // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    0        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("000008595c4d29988f4653f65be09f49b6300395023dbc0da026ce94a417c5d3"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1643500023, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    0        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("000008595c4d29988f4653f65be09f49b6300395023dbc0da026ce94a417c5d3"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1643500023, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    0        // * estimated number of transactions per day after checkpoint
};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID                      = CBaseChainParams::MAIN;
        strNetworkID                   = "main";

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0]             = 0xa3;
        pchMessageStart[1]             = 0x1d;
        pchMessageStart[2]             = 0x3c;
        pchMessageStart[3]             = 0xd6;
        vAlertPubKey                   = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort                   = 99999;
        nSubsidyHalvingInterval        = 525600;
        nMaxReorganizationDepth        = 100;
        nEnforceBlockUpgradeMajority   = 750;
        nRejectBlockOutdatedMajority   = 950;
        nToCheckBlockUpgradeMajority   = 1000;
        nMinerThreads                  = 0;

        bnProofOfWorkLimit             = ~uint256(0) >> 20;
        nTargetTimespan                =  1 * 60; 
        nTargetSpacing                 =  1 * 60;  // Dicenode: 1 minute blocks during POW (block 1-200)

        bnProofOfStakeLimit            = ~uint256(0) >> 20;
        nTargetTimespanPOS             = 40 * 60; 
        nTargetSpacingPOS              =  1 * 60;  // Dicenode: 1 minute blocks during POS

        nMaturity                      = 5; // 6 block maturity (+1 elsewhere)
        nMasternodeCountDrift          = 20;
        nMaxMoneyOut                   = 100000000 * COIN; // 100 millions max supply

        /** Height or Time Based Activations **/
        nLastPOWBlock                  = 1000;
        nModifierUpdateBlock           = 1;

/*
---------------
algorithm: quark
pzTimestamp: 03-05-2019 The Day of Dicenode launch.
pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
bits: 504365040
time: 1556899200
merkle root hash: 0f4bfb64f20884b3d28142a6a5d6f9effd4dfddf813985b665dd12d4923c1449
Searching for genesis hash...
nonce: 1562799
genesis hash: 00000c9cbc78555e74fea2ddab4a9d3815ddbec5bca992e1137e9a74ee658267
*/

        const char* pszTimestamp       = "Don't work for weekends, work for our goals - 18/Jan/2018.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig         = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue           = 1 * COIN;
        txNew.vout[0].scriptPubKey     = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock          = 0;
        genesis.hashMerkleRoot         = genesis.BuildMerkleTree();
        genesis.nVersion               = 1;
        genesis.nTime                  = 1643500023;
        genesis.nBits                  = 504365040;
        genesis.nNonce                 = 98716;


        hashGenesisBlock               = genesis.GetHash();
        assert(hashGenesisBlock        == uint256("000008595c4d29988f4653f65be09f49b6300395023dbc0da026ce94a417c5d3"));
        assert(genesis.hashMerkleRoot  == uint256("ce6764d831bb03467e298c30db5f98b2379b155519c3b9e4dbb9b184bdc07047"));
 
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,  30);  // Start with 'B' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,  31);  // Start with '7' or 'x' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 198);  // from https://en.bitcoin.it/wiki/List_of_address_prefixes
        
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >(); // SecureCloud BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >(); // SecureCloud BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x92)(0xf1).convert_to_container<std::vector<unsigned char> >(); // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x800092f1

        vFixedSeeds.clear();
        vSeeds.clear();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

       // vSeeds.push_back(CDNSSeedData("104.156.238.77", "104.156.238.77"));


        fMiningRequiresPeers           = true;
        fAllowMinDifficultyBlocks      = false;
        fDefaultConsistencyChecks      = false;
        fRequireStandard               = true;
        fMineBlocksOnDemand            = false;
        fSkipProofOfWorkCheck          = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive     = false;

        nPoolMaxTransactions           = 3;
        strSporkKey                    = "04b17ecfc47382b9d418392bdee01622023a3131048d4864f2de94527aea570f025c3839eb4c7425b1d1f5392f3283105cbb55786d5276a1b31bc4717be676788d";
        strMasternodePoolDummyAddress  = "DSNPxNiMAGBc7v4B1HhTPjPvv8KuTY9DwT";
        nStartMasternodePayments       = 1550620800; 

        nBudget_Fee_Confirmations      = 6; // Number of confirmations for the finalization fee

        strTreasuryAddress             = "DQFeM25wsfasHqSYue8FErPMLLqt4XN4HC";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID                      = CBaseChainParams::TESTNET;
        strNetworkID                   = "test";
        pchMessageStart[0]             = 0xa4;
        pchMessageStart[1]             = 0xd2;
        pchMessageStart[2]             = 0x23;
        pchMessageStart[3]             = 0xcb;
        vAlertPubKey                   = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort                   = 90007;
        nEnforceBlockUpgradeMajority   = 51;
        nRejectBlockOutdatedMajority   = 75;
        nToCheckBlockUpgradeMajority   = 100;
        nMinerThreads                  = 0;

        bnProofOfWorkLimit             = ~uint256(0) >> 20;
        nTargetTimespan                =  1 * 60; 
        nTargetSpacing                 =  1 * 60;  // Dicenode: 1 minute blocks during POW (block 1-200) on testnet

        bnProofOfStakeLimit            = ~uint256(0) >> 20;
        nTargetTimespanPOS             =  40 * 60; 
        nTargetSpacingPOS              =   1 * 60;  // Dicenode: 1 minute blocks during POS on testnet

        nLastPOWBlock                  = 1000;
        nMaturity                      = 5;
        nMasternodeCountDrift          = 4;
        nModifierUpdateBlock           = 1;
        nMaxMoneyOut                   = 100000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime                  = 1643500023;
        genesis.nBits                  = 504365040;
        genesis.nNonce                 = 98716;


        hashGenesisBlock               = genesis.GetHash();
        assert(hashGenesisBlock        == uint256("000008595c4d29988f4653f65be09f49b6300395023dbc0da026ce94a417c5d3"));
        assert(genesis.hashMerkleRoot  == uint256("ce6764d831bb03467e298c30db5f98b2379b155519c3b9e4dbb9b184bdc07047"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 90);  // Start with 'b' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 91);  // Start with 'c' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 193);  // from https://en.bitcoin.it/wiki/List_of_address_prefixes

        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >(); // SecureCloud BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >(); // SecureCloud BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
        // Testnet Dicenode BIP44 coin type is '1' (All coin's testnet default)
        
        vFixedSeeds.clear();
        vSeeds.clear();

        fMiningRequiresPeers           = true;
        fAllowMinDifficultyBlocks      = false;
        fDefaultConsistencyChecks      = false;
        fRequireStandard               = false;
        fMineBlocksOnDemand            = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions           = 2;
        strSporkKey                    = "04548068a71f5bd6588cd1183b4e7bdb5f71a9de0053bcd4c81bc1ee538ea43f01d225089e920b1b2e19fa305d6306bd640406d7c25c080ad0c94f431bf5fda650";
        strMasternodePoolDummyAddress  = "bF2y3udz9rMHf1evwzfsgu4oYZLiNh2EP8";
        nStartMasternodePayments       = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations      = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        strTreasuryAddress             = "b1k54s3sqmU4z2bxty1vak3iDAt1ApP15y";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x20;
        pchMessageStart[1] = 0xee;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0xbc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Dicenode: 1 day
        nTargetSpacing = 2 * 60;        // Dicenode: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1606702992;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 78341;


        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 30005;
        assert(hashGenesisBlock == uint256("0000cfdea824426b77fb0d9f8c69f76db7872683863afe8f66bebde735dcb00f"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 30003;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
