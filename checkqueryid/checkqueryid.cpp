#include "oraclize/eos_api.hpp"

using namespace eosio;


class checkqueryid : public eosio::contract 
{  
  public:
    using contract::contract;

    /// @abi action 
    void checkquery() 
    {
        checksum256 myQueryId = oraclize_query("URL", "json(https://api.kraken.com/0/public/Ticker?pair=EOSUSD).result.EOSUSD.l.0");	
        oraclize_emplaceQueryId_local(myQueryId);
        print("Oraclize query was sent & queryId saved in a tbl record, standing by for the answer..");  
    }

    /// @abi action
    void callback( checksum256 queryId, std::vector<uint8_t> result, std::vector<uint8_t> proof ) 
    {
        require_auth(oraclize_cbAddress());
      
        // Get the queryid saved in the local table after calling the testquery action
        std::string queryId_str__expected = checksum256_to_string(oraclize_getQueryId_local(queryId));
        std::string queryId_str = checksum256_to_string(queryId);
      
        // Compare the queryids 
        if (queryId_str != queryId_str__expected)
        {
            print("UNEXPECTED QUERY ID - ", queryId_str, " != ", queryId_str__expected);
        } 
        else 
        {      
            print("QueryId: ", queryId_str);
            std::string result_str = vector_to_string(result);
            print(" Result: ", result_str);
        }
    }
};

EOSIO_ABI(checkqueryid, (checkquery)(callback))
