#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include "oraclize/eos_api.hpp"

using namespace eosio;


// @abi table
struct queryid
{
    uint64_t key;
    checksum256 qid;
    uint8_t active;

    uint64_t primary_key() const { return key; }
};

typedef eosio::multi_index<N(queryid), queryid> ds_queryid;


class example3 : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void testquery() {
         checksum256 myQueryId = oraclize_query("URL", "json(https://api.kraken.com/0/public/Ticker?pair=EOSUSD).result.EOSUSD.l.0");

         // let's save the queryid in a local table
         ds_queryid queryids(_self, _self);
         uint64_t myQueryId_short;
         std::memcpy(&myQueryId_short, &myQueryId.hash, sizeof(myQueryId_short));
         queryids.emplace( _self, [&]( auto& o ) {
             o.key = myQueryId_short;
             o.qid = myQueryId;
             o.active = true;
           });

         print("Oraclize query was sent & queryId saved in a tbl record, standing by for the answer..");  
      }

      /// @abi action
      void callback( checksum256 queryId, std::vector<unsigned char> result, std::vector<unsigned char> proof ) {
         require_auth(oraclize_cbAddress());

         ds_queryid queryids(_self, _self);
         uint64_t myQueryId_short;
         std::memcpy(&myQueryId_short, &queryId.hash, sizeof(myQueryId_short));
         std::string queryId_str__expected = checksum256_to_string(queryids.find(myQueryId_short)->qid);

         std::string queryId_str = checksum256_to_string(queryId);
         if (queryId_str != queryId_str__expected){
             print("UNEXPECTED QUERY ID - ", queryId_str, " != ", queryId_str__expected);
         } else {
             print("QueryId:", queryId_str);
             
             std::string result_str = vector_to_string(result);
             print("Result:", result_str);
         }
      }

};

EOSIO_ABI(example3, (testquery)(callback))
