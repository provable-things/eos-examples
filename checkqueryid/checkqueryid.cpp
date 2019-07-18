#define CONTRACT_NAME "checkqueryid"

#include "provable/eos_api.hpp"

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
        print(" Provable query was sent & queryId saved in the queryId table as a record, standing by for the answer...");
    }

    [[eosio::action]]
    void callback(
        const eosio::checksum256 queryId,
        const std::vector<unsigned char> result,
        const std::vector<unsigned char> proof
    )
    {
        require_auth(provable_cbAddress());
        if (!oraclize_queryId_match(queryId))
        {
            // The query Id match has failed, manage this use case...
            print(" Unexpected query ID!");
        }
        else
        {
            const std::string result_str = vector_to_string(result);
            print(" Result: ", result_str);
        }
    }
};

EOSIO_DISPATCH(checkqueryid, (checkquery)(callback))
