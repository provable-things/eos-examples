#include "provable/eos_api.hpp"

class eosusdprice : public eosio::contract
{
  public:
      using contract::contract;

      eosusdprice(eosio::name receiver, eosio::name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

      [[eosio::action]]
      void execquery()
      {
          print("Sending query to Provable...");
          oraclize_query("URL", "json(https://min-api.cryptocompare.com/data/price?fsym=EOS&tsyms=USD).USD",\
           (proofType_Android | proofStorage_IPFS));
      }

      [[eosio::action]]
      void callback(
          const std::string queryId,
          const std::vector<uint8_t> result,
          const std::vector<uint8_t> proof
      )
      {
          require_auth(provable_cbAddress());
          const std::string result_str = vector_to_string(result);
          print(" Result: ", result_str);
          print(" Proof length: ", proof.size());
      }
};

EOSIO_DISPATCH(eosusdprice, (execquery)(callback))
