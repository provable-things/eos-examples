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
          provable_query(
            "URL",
            "BI1E+MtXQJXDFHVm38/YRZHMVe3s99a0rmQbdtUaa3w+EL/JALVJrvAKVIJi8OxON8vTo5K8x9P78qwQXovsDazeyV8tybIbcO6GlEy/tQXvtHClCPFjQREZ7uZfVd+0wWB1dqQO/WxCunCfgj8uiGFNQrlwwmyqc6/A/9lUUfoTf/koCI44sIOvsybELCg0m1ICaGKx1GhC8qJkChQwkACbY6Y=",\
            (proofType_Native)
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
