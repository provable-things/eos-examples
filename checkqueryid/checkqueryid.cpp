#include "oraclize/eos_api.hpp"

using namespace eosio;


class checkqueryid : public eosio::contract 
{
  public:
    using contract::contract;
    
    checkqueryid(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

    [[eosio::action]] 
    void checkquery() 
    {
        capi_checksum256 myQueryId = oraclize_query("URL", "json(https://api.kraken.com/0/public/Ticker?pair=EOSUSD).result.EOSUSD.l.0");
        oraclize_queryId_localEmplace(myQueryId);
        print("Oraclize query was sent & queryId saved in a tbl record, standing by for the answer...");
    }

    [[eosio::action]]
    void callback(capi_checksum256 queryId, std::vector<unsigned char> result, std::vector<unsigned char> proof) 
    {
        require_auth(oraclize_cbAddress());
      
        if (!oraclize_queryId_match(queryId))
        {
            print("UNEXPECTED QUERY ID");
        } 
        else 
        {      		
            print("QueryId: ", checksum256_to_string(queryId));
            const std::string result_str = vector_to_string(result);
            print(" Result: ", result_str);
        }
    }
};

EOSIO_DISPATCH(checkqueryid, (checkquery)(callback))
