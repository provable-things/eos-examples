#define PROVABLE_NETWORK_NAME "eosio_testnet_jungle"
#define CONTRACT_NAME "randomsample"

#include "provable/eos_api.hpp"

class randomsample : public eosio::contract
{
  public:
    using contract::contract;

    randomsample(eosio::name receiver, eosio::name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

    [[eosio::action]]
    void getrandnum()
    {
        print("Sending query to Provable...");
        uint8_t N = 1; // Possible outputs: [0-255]
        uint32_t delay = 0;
        provable_newRandomDSQuery(delay, N);
    }

    [[eosio::action]]
    void callback(
        const eosio::checksum256 queryId,
        const std::vector<unsigned char> result,
        const std::vector<unsigned char> proof
    )
    {
        require_auth(provable_cbAddress());
        if (provable_randomDS_proofVerify(queryId, result, proof, _self) != 0)
        {
            // The proof verification has failed, manage this use case...
            print("Number: ", result[0]);
            print(" Proof failed has failed...");
        }
        else
        {
            print("Number: ", result[0]);
        }
    }
};
