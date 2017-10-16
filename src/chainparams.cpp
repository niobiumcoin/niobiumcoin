// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//
class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0x3c;
        pchMessageStart[2] = 0x2e;
        pchMessageStart[3] = 0xf9;
        vAlertPubKey = ParseHex("04c244288a8c6ebbf491443ebfa1207275d71cb009f201c118b00cf8e77641c7f1e63e330ba909842c009af375c0f5c1c7368e8d7e2066168c40ce3cb629cf212f");
        nDefaultPort = 55550;
        nRPCPort = 55551;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 18);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 18);

        const char* pszTimestamp = "Niobium-containing compounds are rarely encountered by most people, but some are toxic and should be treated with care";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].nValue = nGenesisBlockReward;
        vout[0].SetEmpty();
        CTransaction txNew(1, 1493596800, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1493596800; // Mon, 01 May 2017 00:00:00 GMT
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 192744;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == 8073789a56f4706337cec10a882a9b02f12ccad4261c79642384869feec6d52e
        block.nTime = 1493596800
        block.nNonce = 192744
        block.GetHash = 31dc15995a124ee3a5e50e8c04a2da31351304a863e81e6562ded51cdfc073e3
        */
        hashGenesisBlock = genesis.GetHash();
        //printf("MAIN genesis.BlockHash = %s\n", genesis.GetHash().ToString().c_str());
        //printf("MAIN genesis.MerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());

        assert(hashGenesisBlock == uint256("0x31dc15995a124ee3a5e50e8c04a2da31351304a863e81e6562ded51cdfc073e3"));
        assert(genesis.hashMerkleRoot == uint256("0x8073789a56f4706337cec10a882a9b02f12ccad4261c79642384869feec6d52e"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,53);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,57);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,53 + 128);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,59);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("niobium.org",  "seed.niobiumcoin.org"));
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "N11E4FCn6BS2kFbYiMhcrrzZp18KjAHtzK";
        nEndPoWBlock = 0x7fffffff;
        nStartPoSBlock = 0;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2c;
        pchMessageStart[1] = 0xcc;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xca;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04ac24ab003c828cdd9cf4db2ebbde8e1cecb3bbfa8b3127fcb9dd9b84d44112080827ed7c49a648af9fe788ff42e316aee665879c553f099e55299d6b54edd7e0");
        nDefaultPort = 45550;
        nRPCPort = 45551;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = 1493596800+30;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 5925;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == e7dba9a3b6015db6a7e3184106c0f813f525b9d4528f36d6f4da0927c9bf0a5f
        block.nTime = 1493596830
        block.nNonce = 5925
        block.GetHash = 0000ae1d0aaeda3c5554fc4d5192c481d002174e33985bb8c855edd899fd0346
        */
        hashGenesisBlock = genesis.GetHash();
        //printf("TESTNET genesis.BlockHash = %s\n", genesis.GetHash().ToString().c_str());

        assert(hashGenesisBlock == uint256("0x5c9eaa3aef77889b18360320e0f95b8800324fa4498473f79506dd27ee8ba0da"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,112 + 128);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,37);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nEndPoWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x1e;
        pchMessageStart[1] = 0xaf;
        pchMessageStart[2] = 0x4f;
        pchMessageStart[3] = 0x3e;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1493596800+90;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 55530;
        strDataDir = "regtest";

        /** Genesis Block TestNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == e7dba9a3b6015db6a7e3184106c0f813f525b9d4528f36d6f4da0927c9bf0a5f
        block.nTime = 1493596890
        block.nNonce = 8
        block.GetHash = 5a30cee8127a63aadf0b88d814fbf075814bc0a431cdb7d543c685c400fa54c1
        */
        //printf("REGTEST genesis.BlockHash = %s\n", genesis.GetHash().ToString().c_str());

        assert(hashGenesisBlock == uint256("0x5a30cee8127a63aadf0b88d814fbf075814bc0a431cdb7d543c685c400fa54c1"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
