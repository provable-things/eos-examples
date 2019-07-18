#include "provable/eos_api.hpp"

class dieselprice : public eosio::contract
{
  public:
      using contract::contract;

      dieselprice(eosio::name receiver, eosio::name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

      [[eosio::action]]
      void execquery()
      {
          print("Sending query to Provable...");
          oraclize_query(60, "URL", "xml(https://www.fueleconomy.gov/ws/rest/fuelprices).fuelPrices.diesel");
      }

      [[eosio::action]]
      void callback(
          const eosio::checksum256 queryId,
          const std::vector<uint8_t> result,
          const std::vector<uint8_t> proof
      )
      {
          require_auth(provable_cbAddress());
          const std::string result_str = vector_to_string(result);
          print("Diesel Price USD: ", result_str);
      }
};

EOSIO_DISPATCH(dieselprice, (execquery)(callback))
