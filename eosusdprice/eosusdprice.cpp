#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include "oraclize/eos_api.hpp"

using namespace eosio;


class eosusdprice : public eosio::contract 
{
  public:
      using contract::contract;

      eosusdprice(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

      [[eosio::action]]
      void execquery() {
          print("Sending query to Oraclize...");
          oraclize_query("URL", "json(https://min-api.cryptocompare.com/data/price?fsym=EOS&tsyms=USD).USD",\
           (proofType_Android | proofStorage_IPFS));
      }

      [[eosio::action]]
      void callback( checksum256 queryId, std::vector<uint8_t> result, std::vector<uint8_t> proof ) {
          require_auth(oraclize_cbAddress());
          const std::string result_str = vector_to_string(result);
          print("Result: ", result_str);
          print(" Proof length: ", proof.size());
      }
};

EOSIO_DISPATCH(eosusdprice, (execquery)(callback))
