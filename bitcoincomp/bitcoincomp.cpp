#include "oraclize/eos_api.hpp"

using namespace eosio;


class bitcoincomp  : public eosio::contract
{
  public:
    using contract::contract;

    /// @abi action
    void callback(checksum256 queryId, std::vector<uint8_t> result, std::vector<uint8_t> proof)
    {
        require_auth(oraclize_cbAddress());
  
        std::string result_str = vector_to_string(result); 
        print("Account balance: ", result_str);
    }

    /// @abi action        
    void compute()
    {    
        std::string bitcoinAddress = "3D2oetdNuZUqQHPJmcMDDHYoqkyNVsFk9r";
        std::vector<std::vector<uint8_t>> myquery = {
            string_to_vector("QmaMFiHXSqCFKkGPbWZh5zKmM827GWNpk9Y1EYhoLfwdHq"), 
            string_to_vector(bitcoinAddress)
        };
        print("Sending query to Oraclize...");
        oraclize_query("computation", myquery);
    }
};

EOSIO_ABI(bitcoincomp, (compute)(callback))
