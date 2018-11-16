#include "oraclize/eos_api.hpp"

using namespace eosio;


class randomsample : public eosio::contract
{
public:
  using contract::contract;

  /// @abi action
  void callback(checksum256 queryId, std::vector<uint8_t> result, std::vector<uint8_t> proof)
  {
    require_auth(oraclize_cbAddress());

    if (oraclize_randomDS_proofVerify(queryId, result, proof, _self) != 0)
    {
      // The proof verification has failed, manage this use case...
    }
    else
    {
      uint8_t result_int = 0;
      std::memcpy(&result_int, &result[0], result.size());
      print("Number: ", result_int);
    }
  }

  /// @abi action        
  void getrandnum()
  {    
    uint8_t N = 1; // Possible outputs: [0-255]
    unsigned long delay = 10; 
    oraclize_newRandomDSQuery(delay, N);
  }
};

EOSIO_ABI(randomsample, (getrandnum)(callback))
