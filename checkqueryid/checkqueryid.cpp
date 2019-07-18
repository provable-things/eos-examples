#define CONTRACT_NAME "checkqueryid"

#include "oraclize/eos_api.hpp"

class checkqueryid : public eosio::contract
{
  public:
    using contract::contract;

    checkqueryid(eosio::name receiver, eosio::name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

    [[eosio::action]]
    void checkquery()
    {
        eosio::checksum256 myQueryId = oraclize_query("URL", "json(https://api.kraken.com/0/public/Ticker?pair=EOSUSD).result.EOSUSD.l.0");
        oraclize_queryId_localEmplace(myQueryId);
        print(" Oraclize query was sent & queryId saved in a tbl record, standing by for the answer...");
    }

    [[eosio::action]]
    void callback(
        eosio::checksum256 queryId,
        std::vector<unsigned char> result,
        std::vector<unsigned char> proof
    )
    {
        require_auth(provable_cbAddress());
        if (!oraclize_queryId_match(queryId))
        {
            // The query Id match has failed, manage this use case...
            print(" UNEXPECTED Query ID!");
        }
        else
        {
            print(" Query ID: ", queryId);
            const std::string result_str = vector_to_string(result);
            print(" Result: ", result_str);
        }
    }
};

EOSIO_DISPATCH(checkqueryid, (checkquery)(callback))
