#include <eosiolib/eosio.hpp>                       
#include <eosiolib/print.hpp>                       

#include "oraclize/eos_api.hpp"                  

using namespace eosio;


class example1 : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action
      void getprice() {
         oraclize_query("URL", "json(https://api.binance.com/api/v3/ticker/price?symbol=EOSUSDT).price");               
         print("Oraclize query was sent, standing by for the answer..");                          
      }

      /// @abi action
      void callback( checksum256 queryId, std::vector<unsigned char> result, std::vector<unsigned char> proof ) {
         require_auth(oraclize_cbAddress());
         
         std::string result_str = vector_to_string(result);                                              
         print("EOSUSD:", result_str);
      }

};

EOSIO_ABI(example1, (getprice)(callback))
