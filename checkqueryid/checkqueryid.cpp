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
        oraclize_emplaceQueryId_local(myQueryId);
        print("Oraclize query was sent & queryId saved in a tbl record, standing by for the answer..");
    }

    [[eosio::action]]
    void callback(capi_checksum256 queryId, std::vector<unsigned char> result, std::vector<unsigned char> proof)
	{
        require_auth(oraclize_cbAddress());
 
        // get the queryid saved in the local table after calling the testquery action
        const std::string queryId_str__expected = capi_checksum256_to_string(oraclize_getQueryId_local(queryId));
        const std::string queryId_str = capi_checksum256_to_string(queryId);

        // compare the queryids
        if (queryId_str != queryId_str__expected)
        {
            print("UNEXPECTED QUERY ID - ", queryId_str, " != ", queryId_str__expected);
        }
        else
        { 
            print("QueryId: ", queryId_str);
            const std::string result_str = vector_to_string(result);
            print(" Result: ", result_str);
        }
    }
};

EOSIO_DISPATCH(checkqueryid, (checkquery)(callback))
