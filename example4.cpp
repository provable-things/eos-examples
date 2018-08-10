#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include "oraclize/eos_api.hpp"

using namespace eosio;


class example4 : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void execquery() {
         oraclize_query("URL", "json(https://min-api.cryptocompare.com/data/price?fsym=EOS&tsyms=USD).USD",\
           (proofType_TLSNotary | proofStorage_IPFS));
      }

      /// @abi action
      void callback( checksum256 queryId, std::vector<unsigned char> result, std::vector<unsigned char> proof ) {
         require_auth(oraclize_cbAddress());

         print("Proof: ", proof.size());
      }

};

EOSIO_ABI(example4, (execquery)(callback))
