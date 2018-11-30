#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include "oraclize/eos_api.hpp"

using namespace eosio;


class wolframrand : public eosio::contract 
{
  public:
    using contract::contract;

    wolframrand(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

    [[eosio::action]]
	void getrandomnum() 
	{
        oraclize_query(10, "WolframAlpha", "random number between 1 and 6");
        print(" Oraclize query was sent, standing by for the answer...");
    }

    [[eosio::action]]
    void callback( checksum256 queryId, std::vector<uint8_t> result, std::vector<uint8_t> proof ) 
	{
        require_auth(oraclize_cbAddress());

        const std::string result_str = vector_to_string(result);
        print("Result:", result_str);

        if (result_str != "6") getrandomnum();
    }
};

EOSIO_DISPATCH(wolframrand, (getrandomnum)(callback))
