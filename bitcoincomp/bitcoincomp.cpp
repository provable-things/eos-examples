#include "provable/eos_api.hpp"

class bitcoincomp : public eosio::contract
{
  public:
    using contract::contract;

    bitcoincomp(eosio::name receiver, eosio::name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

    [[eosio::action]]
    void compute()
    {
        // Prepare computation arguments: IPFS Multihash and Bitcoin Address
        std::string bitcoinAddress = "3D2oetdNuZUqQHPJmcMDDHYoqkyNVsFk9r";
        std::vector<std::vector<unsigned char>> args = {
             string_to_vector("QmYe37uvAUvZZ8ksV726BZt6dJFWP764sTPisNQtuDZVom"),
             string_to_vector(bitcoinAddress)
        };
        std::vector<unsigned char> query = provable_set_computation_args(args);
        // Send Provable query
        print("Sending query to Provable...");
        oraclize_query("computation", query);
    }

    [[eosio::action]]
    void callback(
        const eosio::checksum256 queryId,
        const std::vector<unsigned char> result,
        const std::vector<unsigned char> proof
    )
    {
         // Check that Provable is the callback action caller
         require_auth(provable_cbAddress());
         // Print the account balance of the Bitcoin account
         const std::string result_str = vector_to_string(result);
         print("Account balance:", result_str);
    }
};

EOSIO_DISPATCH(bitcoincomp, (compute)(callback))
