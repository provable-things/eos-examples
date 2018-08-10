#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include "oraclize/eos_api.hpp"

using namespace eosio;


class example2 : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void getrandomnum() {
         oraclize_query(10, "WolframAlpha", "random number between 1 and 6");
         print("Oraclize query was sent, standing by for the answer..");  
      }

      /// @abi action
      void callback( checksum256 queryId, std::vector<unsigned char> result, std::vector<unsigned char> proof ) {
         require_auth(oraclize_cbAddress());

         std::string result_str = vector_to_string(result);
         print("Result:", result_str); 

         if (result_str != "6") getrandomnum();
      }

};

EOSIO_ABI(example2, (getrandomnum)(callback))
