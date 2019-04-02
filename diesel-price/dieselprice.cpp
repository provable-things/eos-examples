#include "oraclize/eos_api.hpp"

using namespace eosio;


class dieselprice : public eosio::contract 
{
  public:
      using contract::contract;

      dieselprice(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

      [[eosio::action]]
      void execquery()
      {
          print("Sending query to Oraclize...");
          oraclize_query(60, "URL", "xml(https://www.fueleconomy.gov/ws/rest/fuelprices).fuelPrices.diesel");
      }

      [[eosio::action]]
      void callback(checksum256 queryId, std::vector<uint8_t> result, std::vector<uint8_t> proof)
      {
          require_auth(oraclize_cbAddress());

          const std::string result_str = vector_to_string(result);
          print("Diesel Price USD: ", result_str);
      }
};

EOSIO_DISPATCH(dieselprice, (execquery)(callback))
