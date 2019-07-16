#include "provable/eos_api.hpp"

class encryptedqry : public eosio::contract
{
  public:
      using contract::contract;

      encryptedqry(eosio::name receiver, eosio::name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

      [[eosio::action]]
      void execquery()
      {
          print("Sending encrypted query to Provable...");
          oraclize_query(
            "URL",
            "BFGZ3gbbKxeypLaf/8L/q6m1jgRG1s5P8OkRofvcjlvIlF6qtesDRtwxomTpfCsJSPfk8z/rw7rYzz8kZOzeh+bFOJyzsojnFektOk8aJuGvFWijFtZvtYAfnFmBDce/f+dcTLsnrmWW4DQIQ2+2LKrOHKliYImtjQlHsPXpQG3giaY5cRkDBCEXdDmJiWMQ8lRFatZYjXa95Q==",\
            (proofType_Android | proofStorage_IPFS)
          );
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
          print(" EOSUSD Price: ", result_str);
          print(" Proof length: ", proof.size());
      }
};

EOSIO_DISPATCH(encryptedqry, (execquery)(callback))
