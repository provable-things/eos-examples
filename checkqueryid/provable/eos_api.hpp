/*********************************************************************************
 * Oraclize API                                                                  *
 *                                                                               *
 * Copyright (c) 2015-2016 Oraclize SRL                                          *
 * Copyright (c) 2016 Oraclize LTD                                               *
 * Permission is hereby granted, free of charge, to any person obtaining a copy  *
 * of this software and associated documentation files (the "Software"), to deal *
 * in the Software without restriction, including without limitation the rights  *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     *
 * copies of the Software, and to permit persons to whom the Software is         *
 * furnished to do so, subject to the following conditions:                      *
 * The above copyright notice and this permission notice shall be included in    *
 * all copies or substantial portions of the Software.                           *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE  *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     *
 * THE SOFTWARE.                                                                 *
 *********************************************************************************/

#ifndef ORACLIZEAPI_H
    #define ORACLIZEAPI_H


/**************************************************
 *                    INCLUDE                     *
 *                   Libraries                    *
 **************************************************/
#include <eosio/transaction.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <stdio.h>
#include <vector>


/**************************************************
 *                      MACRO                     *
 *                   Definitions                  *
 **************************************************/
#ifndef ORACLIZE_NETWORK_NAME
    #warning ORACLIZE_NETWORK_NAME is not set, setting it to "eosio_unknown".. [possible values are "eosio_mainnet"/"eosio_testnet_jungle"/"eosio_testnet_kylin"/"eosio_unknown"]
    #define ORACLIZE_NETWORK_NAME "eosio_unknown"
#endif // ORACLIZE_NETWORK_NAME

#ifndef CONTRACT_NAME
    #warning CONTRACT_NAME is not set, setting it to "".. [write the "contract.name" not the account name]
    #define CONTRACT_NAME "unknown"
#endif // CONTRACT_NAME

#ifndef ORACLIZE_PAYER
   #define ORACLIZE_PAYER _self
#endif // ORACLIZE_PAYER

#define oraclize_query(...) __oraclize_query(ORACLIZE_PAYER, __VA_ARGS__, _self)
#define oraclize_newRandomDSQuery(...) __oraclize_newRandomDSQuery(ORACLIZE_PAYER, __VA_ARGS__, _self)
#define oraclize_queryId_localEmplace(...) __oraclize_queryId_localEmplace(__VA_ARGS__, _self)
#define oraclize_queryId_match(...) __oraclize_queryId_match(__VA_ARGS__, _self)


/**************************************************
 *                   NAMESPACES                   *
 *                  Declarations                  *
 **************************************************/
using namespace eosio;
using namespace std;


/**************************************************
 *                    CONSTANTS                   *
 *                   Proof Types                  *
 **************************************************/
const uint8_t proofType_NONE = 0x00;
const uint8_t proofType_TLSNotary = 0x10;
const uint8_t proofType_Ledger = 0x30;
const uint8_t proofType_Android = 0x40;
const uint8_t proofType_Native = 0xF0;
const uint8_t proofStorage_IPFS = 0x01;

const uint8_t CODE_HASH_RANDOMDS[32] = {
    253, 148, 250, 113, 188, 11, 161, 13, 57, 212, 100, 208, 216, 244, 101, 239, 238, 240, 162, 118, 78, 56, 135, 252, 201, 223, 65, 222, 210, 15, 80, 92
};
const uint8_t LEDGERKEY[64] = {
    127, 185, 86, 70, 156, 92, 155, 137, 132, 13, 85, 180, 53, 55, 230, 106, 152, 221, 72, 17, 234, 10, 39, 34, 66, 114, 194, 229, 98, 41, 17, 232, 83, 122, 47, 142, 134, 164, 107, 174, 200, 40, 100, 233, 141, 208, 30, 156, 204, 47, 139, 197, 223, 201, 203, 229, 169, 26, 41, 4, 152, 221, 150, 228
};


/**************************************************
 *                ORACLIZE  TABLE                 *
 *                   Definition                   *
 **************************************************/
struct [[eosio::table, eosio::contract("provableconn")]] snonce
{
    name sender;
    uint32_t nonce;

    uint64_t primary_key() const { return sender.value; }
};

struct [[eosio::table, eosio::contract("provableconn")]] cbaddr
{
    name sender;

    uint64_t  primary_key() const { return sender.value; }
};

struct [[eosio::table, eosio::contract("provableconn")]] spubkey
{
    name key;
    eosio::checksum256 randomDS_lastSessionPubkeyHash;

    uint64_t primary_key() const { return key.value; }
    eosio::checksum256 get_randomDS_lastSessionPubkeyHash() const { return randomDS_lastSessionPubkeyHash; }
};


/**************************************************
 *                ORACLIZE  TABLE                 *
 *                   Definition                   *
 **************************************************/

struct [[eosio::table, eosio::contract(CONTRACT_NAME)]] scommitment
{
    name shortqueryid;
    eosio::checksum256 queryid;
    eosio::checksum256 commitment;

    uint64_t primary_key() const { return shortqueryid.value; }
};

struct [[eosio::table, eosio::contract(CONTRACT_NAME)]] queryid
{
    name key;
    eosio::checksum256 qid;
    uint8_t active;

    uint64_t primary_key() const { return key.value; }
};

typedef eosio::multi_index<name("snonce"), snonce> ds_snonce;
typedef eosio::multi_index<name("cbaddr"), cbaddr> ds_cbaddr;
typedef eosio::multi_index<name("spubkey"), spubkey> ds_spubkey;
typedef eosio::multi_index<name("scommitment"), scommitment> ds_scommitment;
typedef eosio::multi_index<name("queryid"), queryid> ds_queryid;


/**************************************************
 *                PUBLIC FUNCTIONS                *
 *                 Implementation                 *
 **************************************************/
eosio::name provable_cbAddress()
{
    ds_cbaddr cb_addrs("provableconn"_n, "provableconn"_n.value); // go to the connector table which identify the sender
    auto itr = cb_addrs.begin(); // point to the first element of the table
    const uint64_t cbaddr_uint64t = (itr != cb_addrs.end()) ? itr->sender.value : 0;
    eosio::name cbaddr_name = eosio::name(cbaddr_uint64t);
    return cbaddr_name;
}

std::string vector_uc_to_string(const std::vector<unsigned char> v)
{
    std::string v_str(v.begin(), v.end());
    return v_str;
}

std::vector<unsigned char> provable_set_computation_args(
    const std::vector<std::vector<unsigned char>> _args
)
{
    // [args_number][first_arg_len][[first_arg][second_arg_len][[second_arg][...][...][last_arg_len][last_arg]
    const unsigned char args_size = _args.size();
    std::vector<unsigned char> query;
    // Prepare computation query
    query.push_back(args_size); // Max arguments allowed are 255
    for (int i = 0; i < args_size; i++)
    {
      query.push_back(_args[i].size()); // argument length
      query.insert(query.end(), _args[i].begin(), _args[i].end()); // argument
    }
    return query;
}

eosio::checksum256 invert_checksum256(const eosio::checksum256 _cs)
{
    uint8_t *first_word = (uint8_t *) &_cs.get_array()[0];
    uint8_t *second_word = (uint8_t *) &_cs.get_array()[1];
    eosio::checksum256 cs_inverted;
    uint8_t *first_word_inverted = (uint8_t *) &cs_inverted.get_array()[0];
    uint8_t *second_word_inverted = (uint8_t *) &cs_inverted.get_array()[1];
    for (int i = 0; i < 16; i++)
    {
       first_word_inverted[15 - i] = first_word[i];
       second_word_inverted[15 - i] = second_word[i];
    }
    return cs_inverted;
}


bool checksum256_is_empty(const eosio::checksum256 cs)
{
    uint8_t *first_word = (uint8_t *)&cs.get_array()[0];
    uint8_t *second_word = (uint8_t *)&cs.get_array()[1];
    for(int i = 0; i < 16; i++)
        if(first_word[i] != 0 && second_word[i] != 0)
            return false;
    return true;
}

std::vector<uint8_t> string_to_vector(const std::string s)
{
    std::vector<uint8_t> s_v(s.begin(), s.end());
    return s_v;
}

std::string vector_to_string(const std::vector<uint8_t> v)
{
    std::string v_str(v.begin(), v.end());
    return v_str;
}

std::vector<unsigned char> hexstring_to_vector32(std::string s)
{
    std::vector<unsigned char> v32;
    for(unsigned int i = 0; i < 32; i++)
    {
        unsigned int ui;
        sscanf(s.data() + (i * 2), "%02x", &ui);
        unsigned char uc = (unsigned char) ui;
        v32.push_back(uc);
    }
    return v32;
}

eosio::checksum256 hexstring_to_checksum256(const std::string hs)
{
    std::vector hs_bytes = hexstring_to_vector32(hs);
    eosio::checksum256 cs;
    uint8_t *first_word = (uint8_t *) &cs.get_array()[0];
    uint8_t *second_word = (uint8_t *) &cs.get_array()[1];
    for (int i = 0; i < 16; i++)
    {
       first_word[i] = hs_bytes[i];
       second_word[i] = hs_bytes[i + 16];
    }
    return cs;
}

std::string checksum256_to_string(const eosio::checksum256 cs)
{
    uint8_t *first_word = (uint8_t *) &cs.get_array()[0];
    uint8_t *second_word = (uint8_t *) &cs.get_array()[1];
    char hexstr[64];
    for (int i = 0; i < 16; i++)
        sprintf(hexstr + i * 2, "%02x", first_word[i]);
    for (int i = 16; i < 32; i++)
        sprintf(hexstr + i * 2, "%02x", second_word[i - 16]);
    std::string c_str = std::string(hexstr);
    return c_str;
}

std::string chara_to_hexstring(uint8_t *input, const int size)
{
    char hexstr[size * 2];
    for (int i = 0; i < size; i++)
        sprintf(hexstr + i * 2, "%02x", input[i]);
    std::string c_str = std::string(hexstr);
    return c_str;
}

std::string vector_to_hexstring(std::vector<uint8_t> *input)
{
    int size = input->size();
    char hexstr[size * 2];
    for (int i = 0; i < size; i++)
        sprintf(hexstr + i * 2, "%02x", input->at(i));
    std::string c_str = std::string(hexstr);
    return c_str;
}

std::vector<uint8_t> uint32_to_vector8(uint32_t num)
{
    std::vector<uint8_t> ba(8);
    const uint32_t mask = 0xFF;
    for(int i = 0; i < 8; i++)
    {
	    ba[i] = num & mask;
	    num = num >> 8;
    }
    return ba;
}

std::vector<uint8_t> uint32_to_vector32_bigendian(uint32_t num)
{
    std::vector<uint8_t> ba(32);
    const uint32_t mask = 0xFF;
    for(int i = 31; i > -1; i--)
    {
	    ba[i] = num & mask;
	    num = num >> 8;
    }
    return ba;
}

std::vector<uint8_t> checksum256_to_vector32(const eosio::checksum256 cs)
{
    uint8_t *first_word = (uint8_t *)&cs.get_array()[0];
    uint8_t *second_word = (uint8_t *)&cs.get_array()[1];
    std::vector<uint8_t> ba(32);
    for (int i = 0; i < 16; i++)
    {
        ba[i] = first_word[i];
    }
    for (int i = 16; i < 32; i++)
    {
        ba[i] = second_word[i - 16];
    }
    return ba;
}


/**************************************************
 *               INTERNAL FUNCTIONS               *
 *                  Definitions                   *
 **************************************************/
eosio::checksum256 __oraclize_randomDS_getSessionPubkeyHash()
{
    ds_spubkey spubkeys("provableconn"_n, "provableconn"_n.value);
    name index = "1"_n; // only one value in the table with key = 1
    auto itr = spubkeys.find(index.value);
    eosio::checksum256 sessionPubkeyHash;
    if (itr != spubkeys.end())
    {
        sessionPubkeyHash = itr->get_randomDS_lastSessionPubkeyHash();
    }
    return sessionPubkeyHash;
}

uint32_t __oraclize_getSenderNonce(name sender)
{
    ds_snonce last_nonces("provableconn"_n, "provableconn"_n.value);
    auto itr = last_nonces.find(sender.value);
    uint32_t nonce = 0;
    if (itr != last_nonces.end())
    {
        nonce = itr->nonce;
    }
    return nonce;
}

eosio::checksum256 __oraclize_getNextQueryId(const name sender)
{
    const uint32_t nonce = __oraclize_getSenderNonce(sender); // get values to generate the queryId
    const size_t tx_size = transaction_size();
    uint8_t tbh[sizeof(sender) + sizeof(nonce) + sizeof(tx_size)]; // calculate the hash of the previous values
    std::memcpy(tbh, &sender, sizeof(sender));
    std::memcpy(tbh + sizeof(sender), &nonce, sizeof(nonce));
    std::memcpy(tbh + sizeof(sender) + sizeof(nonce), &tx_size, sizeof(tx_size));
    eosio::checksum256 calc_hash = sha256((char *)tbh, sizeof(tbh));
    return calc_hash;
}

// Check that the queryId being passed matches with the one in the customer local table, return true/false accordingly
bool __oraclize_queryId_match(const eosio::checksum256 queryId, const name sender)
{
    name myQueryId_short;
    std::memcpy(&myQueryId_short, &queryId, sizeof(myQueryId_short));
    // Access the local query table and find the right row
    ds_queryid queryids(sender, sender.value);
    auto itr = queryids.find(myQueryId_short.value);
    // Get the local queryId value
    eosio::checksum256 queryId_expected;
    std::memcpy(&queryId_expected, 0, sizeof(queryId_expected));
    // Get the queryId from the table
    if (itr != queryids.end())
        queryId_expected = itr->qid;
    else
        return false;
    // Check if the value retrieved is only 0
    if(checksum256_is_empty(queryId_expected))
        return false;
    // Convert queryId and queryId_expected to string, to compare them
    const std::string queryId_str__expected = checksum256_to_string(queryId_expected);
    const std::string queryId_str = checksum256_to_string(queryId);
    // Compare the queryids and check if string values are empty
    if (queryId_str != queryId_str__expected || queryId_str.empty() || queryId_str__expected.empty())
        return false;
    else
        return true;
}

void __oraclize_queryId_localEmplace(const eosio::checksum256 myQueryId, const name sender)
{
    // Retreive the short queryId to use it as an index
    name myQueryId_short;
    std::memcpy(&myQueryId_short, &myQueryId, sizeof(myQueryId_short));
    // Save the queryId in the local table
    ds_queryid queryids(sender, sender.value);
    queryids.emplace(sender, [&](auto& o) {
        o.key = myQueryId_short;
        o.qid = myQueryId;
        o.active = true;
    });
}


/**************************************************
 *                  Oraclize Query                *
 *                    Strings                     *
 **************************************************/
eosio::checksum256 __oraclize_query(const name user, const unsigned int timestamp, const std::string datasource, const std::string query, const uint8_t prooftype, const name sender)
{
    const eosio::checksum256 queryId = __oraclize_getNextQueryId(sender);
    action(permission_level{user, "active"_n},
        "provableconn"_n,
        "querystr"_n,
        std::make_tuple(sender, (int8_t)1, (uint32_t)timestamp, queryId, datasource, query, prooftype)
    ).send();
    return queryId;
}

eosio::checksum256 __oraclize_query(const name user, const std::string datasource, const std::string query, const name sender)
{
    return __oraclize_query(user, 0, datasource, query, 0, sender);
}

eosio::checksum256 __oraclize_query(const name user, const unsigned int timestamp, const std::string datasource, const std::string query, const name sender)
{
    return __oraclize_query(user, timestamp, datasource, query, 0, sender);
}

eosio::checksum256 __oraclize_query(const name user, const std::string datasource, const std::string query, const uint8_t prooftype, const name sender)
{
    return __oraclize_query(user, 0, datasource, query, prooftype, sender);
}


/**************************************************
 *                 Oraclize Query                 *
 *                   Bytearrays                   *
 **************************************************/
eosio::checksum256 __oraclize_query(const name user, const unsigned int timestamp, const std::string datasource, const vector<uint8_t> query, const uint8_t prooftype, const name sender)
{
    const eosio::checksum256 queryId = __oraclize_getNextQueryId(sender);
    printhex(query.data(), query.size());
    auto n = name{user};
    const std::string str = n.to_string();
    action(permission_level{user, "active"_n},
        "provableconn"_n,
        "queryba"_n,
        std::make_tuple(sender, (int8_t)1, (uint32_t)timestamp, queryId, datasource, query, prooftype)
    ).send();
    return queryId;
}

eosio::checksum256 __oraclize_query(const name user, const std::string datasource, const vector<uint8_t> query, const name sender)
{
    return __oraclize_query(user, 0, datasource, query, 0, sender);
}

eosio::checksum256 __oraclize_query(const name user, const unsigned int timestamp, const std::string datasource, const vector<uint8_t> query, const name sender)
{
    return __oraclize_query(user, timestamp, datasource, query, 0, sender);
}

eosio::checksum256 __oraclize_query(const name user, const std::string datasource, const vector<uint8_t> query, const uint8_t prooftype, const name sender)
{
    return __oraclize_query(user, 0, datasource, query, prooftype, sender);
}


/**************************************************
 *                 Oraclize Query                 *
 *                   Random DS                    *
 **************************************************/
void __oraclize_randomDS_setCommitment(const eosio::checksum256 queryId, const eosio::checksum256 commitment, const name payer)
{
    name myQueryId_short; // Calculate the short queryId, to use it as a key of the table
    std::memcpy(&myQueryId_short, &queryId.get_array()[0], sizeof(myQueryId_short));
    ds_scommitment last_commitments(payer, payer.value); // Set the commitment in the eos table of the caller
    last_commitments.emplace(payer, [&](auto &o) { // The key must be a uint64_t so a short query Id is used
        o.shortqueryid = myQueryId_short;
        o.queryid = queryId;
        o.commitment = commitment;
    });
}

eosio::checksum256 __oraclize_newRandomDSQuery(const name user, const uint32_t _delay, const uint8_t _nbytes, const name sender)
{
    // 1. NBYTES - Convert nbytes to bytearray
    std::vector<uint8_t> nbytesBa(1);
    nbytesBa[0] = _nbytes;

    // 2. SESSIONKEYHASH - Get the sessionKeyHash from the ledger public key.
    const eosio::checksum256 sessionPubkeyHash = __oraclize_randomDS_getSessionPubkeyHash();
    std::vector<uint8_t> sessionPubkeyHashBa(32);
    std::vector<uint8_t> sessionPubkeyHashBa2(32);
    sessionPubkeyHashBa = checksum256_to_vector32(sessionPubkeyHash);

    // 3. UNONCE - Need something block dependent so we decided to perform the hash of those 4 block dependent fields. This value have to be unpredictable from Oraclize
    const size_t tx_size = transaction_size();
    const int tapos_block_num_ = tapos_block_num();
    const int tapos_block_prefix_ = tapos_block_prefix();
    uint8_t unonce[sizeof(tx_size) + sizeof(tapos_block_num_) + sizeof(tapos_block_prefix_)]; // Fill the unonce array: now() + transaction_size + tapos_block_num + tapos_block_prefix
    std::memcpy(unonce, &tx_size, sizeof(tx_size));
    std::memcpy(unonce + sizeof(tx_size), &tapos_block_num_, sizeof(tapos_block_num_));
    std::memcpy(unonce + sizeof(tx_size) + sizeof(tapos_block_num_), &tapos_block_prefix_, sizeof(tapos_block_prefix_));
    eosio::checksum256 unonceHash = sha256((char *)unonce, sizeof(unonce)); // Container for the unonce hash
    std::vector<uint8_t> unonceHashBa(32); // Convert the unonce hash in bytearray
    unonceHashBa = checksum256_to_vector32(unonceHash);

    // 4. DELAY - Delay converted in a big endian bytearray
    const uint32_t delayLedgerTime = _delay * 10; // Convert from seconds to ledger timer ticks
    std::vector<uint8_t> delayBaBigEndian(32);
    delayBaBigEndian = uint32_to_vector32_bigendian(delayLedgerTime);

    // Set args2 to be passed as params of the oraclize "random" query
    std::vector<std::vector<uint8_t>> args;
    args.push_back(unonceHashBa);
    args.push_back(nbytesBa);
    args.push_back(sessionPubkeyHashBa);
    args.push_back(delayBaBigEndian);
    std::vector<uint8_t> args2;
    for(auto && a : args)
        args2.insert(args2.end(), a.begin(), a.end());

    // Call the oraclize_query and get the queryId
    const eosio::checksum256 queryId = __oraclize_query(user,"random", args2, proofType_Ledger, sender); // proofType and datasource are always fixed in this function

    // Calculate the commitment and call a function to set it
    std::vector<uint8_t> delayBa(8); // delay converted to 8 byte
    delayBa = uint32_to_vector8(delayLedgerTime);
    uint8_t* charArray = &unonceHashBa[0];
    eosio::checksum256 unonceHashBaHash = invert_checksum256(sha256((char *) charArray, unonceHashBa.size())); // unonce has to be passed hashed
    uint8_t commitmentTbh[8 + 1 + 32 + args[2].size()]; // Calculate the commitment to be hashed with the size of: 8 + 1 + 32 + 32
    std::memcpy(commitmentTbh, &delayBa[0], 8); // 8
    std::memcpy(commitmentTbh + 8, &args[1][0], 1); // 8 + 1
    std::memcpy(commitmentTbh + 8 + 1, &unonceHashBaHash.get_array()[0], 16); // 8 + 1 + 16
    std::memcpy(commitmentTbh + 8 + 1 + 16, &unonceHashBaHash.get_array()[1], 16); // 8 + 1 + 32 == commitmentSlice1
    std::memcpy(commitmentTbh + delayBa.size() + args[1].size() + 32, &args[2][0], args[2].size()); // 8 + 1 + 32 + 32 (commitmentSlice1 + sessionPubkeyHashBa)
    eosio::checksum256 commitment = sha256((char *)commitmentTbh, sizeof(commitmentTbh)); // Container for the commitment hash
    const name payer = user; // Payer for setting the commitment
    __oraclize_randomDS_setCommitment(queryId, commitment, payer); // Call the function to set query Id and commitment in the table

    return queryId;
}

void __oraclize_randomDS_get_signature_component(uint8_t component[32], const uint8_t signature[], const uint8_t signature_len, const uint8_t length_idx)
{
    eosio::internal_use_do_not_use::eosio_assert(signature_len > length_idx, "Invalid index");
    uint8_t component_len = signature[length_idx];
    uint8_t byte_to_jump = component_len % 32;
    std::memcpy(component, &signature[length_idx + 1 + byte_to_jump], component_len - byte_to_jump);
}

bool __oraclize_randomDS_matchBytes32Prefix(const eosio::checksum256 content, const uint8_t prefix[], const uint8_t prefix_len, const uint8_t n_random_bytes)
{
    eosio::internal_use_do_not_use::eosio_assert(prefix_len == n_random_bytes, "Prefix length and random bytes number should match.");
    const eosio::checksum256 content_inverted = invert_checksum256(content);
    uint8_t *first_word = (uint8_t *)&content_inverted.get_array()[0];
    uint8_t *second_word = (uint8_t *)&content_inverted.get_array()[1];
    for (int i = 0; i < n_random_bytes; ++i)
    {
        if (i < 16)
        {
            if (first_word[i] != prefix[i])
                return false;
        }
        else
        {
            if (second_word[i] != prefix[i])
                return false;
        }
    }
    return true;
}

bool __oraclize_randomDS_test_pubkey_signature(const uint8_t whatever, const uint8_t v, const uint8_t r[32], const uint8_t s[32], const eosio::checksum256 digest, const uint8_t pubkey[64])
{
    eosio::signature sig;

    sig.type = whatever;
    sig.data[0] = v;
    for (int i = 0; i < 32; i++)
      sig.data[i + 1] = r[i];
    for (int i = 0; i < 32; i++)
      sig.data[i + 1 + 32] = s[i];

    const eosio::public_key pubkey_recovered = recover_key(digest, sig);

    if (pubkey_recovered.data.size() != 33)
         return false;
    if (pubkey_recovered.data[0] != 0x02 && pubkey_recovered.data[0] != 0x03)
        return false;
    // Discard the first (0x00) and the second byte (0x02 or 0x03)
    for (int i = 0; i < 32; i++)
        if ((uint8_t)pubkey_recovered.data[i + 1] != pubkey[i])
            return false;
    return true;
}

bool __oraclize_randomDS_verifySig(const eosio::checksum256 digest, const uint8_t der_signature[], const uint8_t der_signature_len, const uint8_t pubkey[64])
{
    uint8_t r[32];
    uint8_t s[32];
    __oraclize_randomDS_get_signature_component(r, der_signature, der_signature_len, 3);
    __oraclize_randomDS_get_signature_component(s, der_signature, der_signature_len, 4 + der_signature[3] + 1);
    // We try either with v=27 or with v=28
    bool test_v27 = __oraclize_randomDS_test_pubkey_signature(0, 27, r, s, digest, pubkey);
    bool test_v28 = __oraclize_randomDS_test_pubkey_signature(0, 28, r, s, digest, pubkey);
    return test_v27 || test_v28;
}

uint8_t oraclize_randomDS_proofVerify(const eosio::checksum256 queryId, const std::vector<uint8_t> result, const std::vector<uint8_t> proof, const name payer)
{
    /*******************************************************************************************
     *                                                                                         *
     *   Step 1: the prefix has to match 'LP\x01' (Ledger Proof version 1)                     *
     *                                                                                         *
     *******************************************************************************************/
    if (proof[0] != 'L' || proof[1] != 'P' || proof[2] != 1)
        return 1;


    /********************************************************************************************
     *                                                                                          *
     *   Step 2: the unique keyhash has to match with the sha256 of (context name +  queryId)    *
     *                                                                                          *
     ********************************************************************************************/
    const uint8_t ledgerProofLength = 3 + 65 + (proof[3 + 65 + 1] + 2) + 32;
    uint8_t keyhash[32];
    std::memcpy(keyhash, &proof.data()[ledgerProofLength], 32);
    eosio::checksum256 keyhash_sha = sha256((char *)keyhash, 32);
    std::string keyhash_sha_str = checksum256_to_string(keyhash_sha);
    uint8_t *first_word = (uint8_t *) &keyhash_sha.get_array()[0];
    uint8_t *second_word = (uint8_t *) &keyhash_sha.get_array()[1];
    std::string context_name_str = ORACLIZE_NETWORK_NAME;
    char context_name[context_name_str.size()];
    context_name_str.copy(context_name, context_name_str.size());
    uint8_t tbh2[sizeof(context_name) + 32];
    std::memcpy(tbh2, &context_name, sizeof(context_name));
    std::memcpy(tbh2 + sizeof(context_name), &queryId.get_array()[0], 16);
    std::memcpy(tbh2 + sizeof(context_name) + 16, &queryId.get_array()[1], 16);
    eosio::checksum256 calc_hash = invert_checksum256(sha256((char *)tbh2, sizeof(context_name) +
16 + 16));
    uint8_t tbh3[32];
    std::memcpy(tbh3, &calc_hash.get_array()[0], 16);
    std::memcpy(tbh3 + 16, &calc_hash.get_array()[1], 16);
    eosio::checksum256 calc_hash_2 = sha256((char *)tbh3, 16 + 16);
    uint8_t *first_word3 = (uint8_t *) &calc_hash_2.get_array()[0];
    uint8_t *second_word3 = (uint8_t *) &calc_hash_2.get_array()[1];
    if(checksum256_to_string(keyhash_sha) != checksum256_to_string(calc_hash_2))
        return 2;


    /********************************************************************************************
     *                                                                                          *
     *   Step 3: we assume sig1 is valid (it will be verified during step 5)                    *
     *           and we verify if 'result' is the prefix of sha256(sig1)                        *
     *                                                                                          *
     ********************************************************************************************/
    const uint8_t sig1_len = proof[ledgerProofLength + (32 + 8 + 1 + 32) + 1] + 2;
    uint8_t sig1[sig1_len];
    std::memcpy(sig1, &proof.data()[ledgerProofLength + (32 + 8 + 1 + 32)], sig1_len);
    eosio::checksum256 sig1_hash = sha256((char *)sig1, sizeof(sig1));
    if (!__oraclize_randomDS_matchBytes32Prefix(sig1_hash, result.data(), result.size(), proof[ledgerProofLength + 32 + 8]))
        return 3;


    /********************************************************************************************
     *                                                                                          *
     *   Step 4: commitment match verification,                                                 *
     *           sha256(delay, nbytes, unonce, sessionKeyHash) == commitment in table.          *
     *                                                                                          *
     ********************************************************************************************/
    const uint8_t slice_offset = 8 + 1 + 32; // delay + nbytes + unonceHashBa
    uint8_t commitmentSlice1[slice_offset];
    std::memcpy(commitmentSlice1, &proof.data()[ledgerProofLength + 32], sizeof(commitmentSlice1));
    // Extract the session public key and calculate the session publick key hash
    uint8_t sessionPubKey[64];
    const uint16_t sig2offset = ledgerProofLength + 32 + (8 + 1 + 32) + sig1_len + 65; // ledgerProofLength+32+(8+1+32)+sig1.len+65
    std::memcpy(sessionPubKey, &proof.data()[sig2offset - 64], sizeof(sessionPubKey));
    eosio::checksum256 sessionPubkeyHash = invert_checksum256(sha256((char *)sessionPubKey,
sizeof(sessionPubKey))); // Calculate the key hash
    vector<uint8_t> sessionPubkeyHashBa(32); // Convert to bytearray the public key hash
    sessionPubkeyHashBa = checksum256_to_vector32(sessionPubkeyHash);
    // Recreate the lastCommitment to compare with the table one
    uint8_t tbh[slice_offset + 32];
    std::memcpy(tbh, &commitmentSlice1, slice_offset);
    std::memcpy(tbh + slice_offset, &sessionPubkeyHashBa[0], 32);
    eosio::checksum256 lastCommitment = sha256((char *)tbh, sizeof(tbh));
    // Retrieve the table commitment
    ds_scommitment last_commitments(payer, payer.value);
    name myQueryId_short;
    std::memcpy(&myQueryId_short, &queryId.get_array()[0], sizeof(myQueryId_short));
    // Check if the key value exists
    auto itr = last_commitments.find(myQueryId_short.value);
    if (itr == last_commitments.end())
        return 4;
    // Check the query id with the one in the table
    const std::string queryId_str__expected = checksum256_to_string(itr->queryid);
    const std::string queryId_str = checksum256_to_string(queryId);
    if (queryId_str != queryId_str__expected)
        return 4;
    // Check the commitment with the one in the table
    const std::string lastCommitment_str__expected = checksum256_to_string(itr->commitment);
    const std::string lastCommitment_str = checksum256_to_string(lastCommitment);
    if (lastCommitment_str != lastCommitment_str__expected)
        return 4;


    /********************************************************************************************
     *                                                                                          *
     *   Step 5: validity verification for sig1 (keyhash and args signed with the sessionKey)   *
     *                                                                                          *
     ********************************************************************************************/
    uint8_t toSign1[32 + 8 + 1 + 32];
    std::memcpy(toSign1, &proof.data()[ledgerProofLength], sizeof(toSign1));
    eosio::checksum256 toSign1_hash = sha256((char *)toSign1, sizeof(toSign1));
    if (!__oraclize_randomDS_verifySig(toSign1_hash, sig1, sizeof(sig1), sessionPubKey))
        return 5;


    /********************************************************************************************
     *                                                                                          *
     *   Step 6:  verify the attestation signature,                                             *
     *            APPKEY1 must sign the sessionKey from the correct ledger app (CODEHASH)       *
     *                                                                                          *
     ********************************************************************************************/
    uint8_t sig2[proof[sig2offset + 1] + 2];
    std::memcpy(sig2, &proof.data()[sig2offset], sizeof(sig2));
    uint8_t appkey_pubkey[64];
    std::memcpy(appkey_pubkey, &proof.data()[3 + 1], sizeof(appkey_pubkey));
    uint8_t toSign2[1 + 65 + 32];
    toSign2[0] = 1; // role
    std::memcpy(toSign2 + 1, &proof.data()[sig2offset - 65], 65);
    std::memcpy(toSign2 + 65 + 1, CODE_HASH_RANDOMDS, 32);
    eosio::checksum256 toSign2_hash = sha256((char *)toSign2, sizeof(toSign2));
    if (!__oraclize_randomDS_verifySig(toSign2_hash, sig2, sizeof(sig2), appkey_pubkey))
        return 6;


    /********************************************************************************************
     *                                                                                          *
     *   Step 7: verify the APPKEY1 provenance (must be signed by Ledger)                       *
     *                                                                                          *
     ********************************************************************************************/
    uint8_t toSign3[1 + 65];
    toSign3[0] = 0xfe;
    std::memcpy(toSign3 + 1, &proof.data()[3], 65);
    uint8_t sig3[proof[3 + 65 + 1] + 2];
    std::memcpy(sig3, &proof.data()[3 + 65], sizeof(sig3));
    eosio::checksum256 toSign3_hash = sha256((char *)toSign3, sizeof(toSign3));
    if (!__oraclize_randomDS_verifySig(toSign3_hash, sig3, sizeof(sig3), LEDGERKEY))
        return 7;


    // Erase the commitment after the proof is verified
    auto itr2 = last_commitments.find(myQueryId_short.value);
    last_commitments.erase(itr2);
    return 0;
}

#endif
