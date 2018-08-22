// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2018 The InstaDEX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
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
    (0, uint256("00000696af0c5452ae8e272b95bed12466e76866c3f767954e1593951eefaba6"))
    (500, uint256S("0000031cab066a8c4c44b9831cdc146f0a0cbeacc2e36e578d8b4f5cc08be649"))
	(1000, uint256S("0000001c097b1afc3ed97ec2ebf144a8837747a8ee5af30a2626c631b920338e"))
	(5000, uint256S("bf48b1bd6770728dba205939716118127c95d0ce22f0006eda529c2504a61002"))
	(10000, uint256S("ceea70591c3b7c8849460bc840ab8cd582443d359c41f7b7442c7e04ab6befc2"))
	(15000, uint256S("b1280d0a0ed338dbc2fa75140b9f5e1b3bb44a801ca5248ceda1495c7d48ee36"))
	(20000, uint256S("681c07f83d457cc968a05b78a524ee4edb3ea8e9f9eff9c2f1f121b3972eb190"))
	(25000, uint256S("60d9f941ffce0e60dfaba6745154c3b77ddd1a27ccf662e71e74ed7e67752527"))
	(26500, uint256S("a3aa0950cacad603ec20a9f5cb0ca97345c14ae70ea029720f3d6bab50c2fbf7"))
	(26550, uint256S("b0389e243d947d274b625362c8e4fd96b9f37ae9c6ce9475fa78c331289e520b"))// Fork block/rollback point
	(26551, uint256S("f235df68d2bdbdf2c7db02a70314aa54a16e8ade9bafcdda128e12b15d762920"))// First block on Forked chain
	(26600, uint256S("150ac67005473d1990bf7ff63f082a4faf5560a0450fff7ab113314fcc54ad29"));
	



static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1514407942, // * UNIX timestamp of last checkpoint block
    52496,    // * total number of tx between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1527610876,
    1,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1527610994,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        pchMessageStart[0] = 0x19;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0x91;
        pchMessageStart[3] = 0xf3;
        vAlertPubKey = ParseHex("058045f32ac7aeb9f592e91267e95d5b77b6dc24600d51fcbe8fa9f2b047a0d1c4eb1bb962112e4cb0229b260f9ba7be8e2fc7d816619e98bb20acbc429c353179");
        nDefaultPort = 8889;
        bnProofOfWorkLimit = ~uint256() >> 12;
        nSubsidyHalvingInterval = 9999999;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 7 * 60; // InstaDEX: 1 minute
        nTargetSpacing = 1 * 60;  // InstaDEX: 1 minute
        nLastPOWBlock = 1000;
        nMaturity = 5;
        nMasternodeCountDrift = 200;
        nModifierUpdateBlock = 1;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Bank of America May Fall by 10% on Slower Growth - 25 June 2018";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04892afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1529949552;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 456766;
				 
        hashGenesisBlock = genesis.GetHash();
	assert(hashGenesisBlock == uint256("0x00000696af0c5452ae8e272b95bed12466e76866c3f767954e1593951eefaba6"));
        assert(genesis.hashMerkleRoot == uint256("0x60ebebae9b90655e009504142d07460cc6542f4aa0af1252c8ba74775579a6c4"));
		
	//vSeeds.push_back(CDNSSeedData("instadex.seeds.mn.zone", "instadex.seeds.mn.zone"));
	vSeeds.push_back(CDNSSeedData("209.250.241.176", "209.250.241.176"));
    vSeeds.push_back(CDNSSeedData("209.250.243.131", "209.250.243.131"));
    vSeeds.push_back(CDNSSeedData("45.77.239.108", "45.77.239.108"));
	vSeeds.push_back(CDNSSeedData("45.32.235.211", "45.32.235.211"));	
	vSeeds.push_back(CDNSSeedData("107.191.44.102", "107.191.44.102"));
	vSeeds.push_back(CDNSSeedData("108.61.188.67", "108.61.188.67"));	
	vSeeds.push_back(CDNSSeedData("178.62.68.177", "178.62.68.177"));
    vSeeds.push_back(CDNSSeedData("178.62.67.100", "178.62.67.100")); 
	vSeeds.push_back(CDNSSeedData("178.62.67.105", "178.62.67.105")); 
	vSeeds.push_back(CDNSSeedData("178.62.67.165", "178.62.67.165")); 
	vSeeds.push_back(CDNSSeedData("178.62.71.128", "178.62.71.128")); 


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 102);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 154);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >(); // xpub prefix
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >(); // xprv prefix
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md - TBD InstaDEX
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x148).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        strObfuscationPoolDummyAddress = "D87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
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
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x8f;
        pchMessageStart[1] = 0xaf;
        pchMessageStart[2] = 0xae;
        pchMessageStart[3] = 0xac;
        vAlertPubKey = ParseHex("048045f32ac7aeb9f592e91267e95d5b77b6dc24600d51fcbe8fa9f2b047a0d1c4eb1bb962112e4cb0229b260f9ba7be8e2fc7d816619e98bb20acbc429c353179");
        nDefaultPort = 41474;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // InstaDEX: 1 day
        nTargetSpacing = 1 * 60;  // InstaDEX: 1 minute
        nLastPOWBlock = 2000;
        nMaturity = 15;
        nModifierUpdateBlock = 1; 

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1527610876;
        genesis.nNonce = 2713556;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet instadex addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet instadex script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet instadex BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet instadex BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet instadex BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04fa931cb76c6cdf39a6c7bf2e42ac6429ebea664c62fdb962158466b39583f436f5c29f499050c74bd4204352db9123b54144823380271ee07cab9c3b427b7193";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
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
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // InstaDEX: 1 day
        nTargetSpacing = 1 * 60;        // InstaDEX: 1 minutes
        bnProofOfWorkLimit = ~uint256() >> 1;
        genesis.nTime = 1527610994;
        genesis.nNonce = 491087;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 40003;
        //assert(hashGenesisBlock == uint256("0x00000bd0a548c88821bad8e69917339863e3af206bd6c7546a0d7834cf905c6e"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
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
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
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
