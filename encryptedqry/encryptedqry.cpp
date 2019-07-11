#include "provable/eos_api.hpp"

class encryptedqry : public eosio::contract
{
  public:
      using contract::contract;

      eosusdprice(eosio::name receiver, eosio::name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

      [[eosio::action]]
      void execquery()
      {
          print("Sending encrypted query to Provable...");
          oraclize_query(
            "URL",
            "BMqMhIFTTzsDbUSfPT233dVWB6wp0ksci7R/c6Jezcy3nEsnX7EQTaqRbej3shF7NlOwGRJAs1IBtYS32f6HrexffY+z1XMCHp+W6vFaIpDSVP0sVxiokuO0fr+ePxHOkvUh9x49BSmageBbHM1RB6QY/xhhvwJtssZOspEHvic=",
            "BDfT0gaCqtru/YRL/qEDEPTopcKe04wXtkRlDw0PNa8hazsDgKXv1G0pBVaHK5um6eTzAggrLKlXVLSUqI6rVzd9oaDST4Zo1NtLf2iMwWI0yx7sWwuhFY0Ot+OltgHLf8SclyRuHZHiOq+Ubx1pBtFGImYH4yMon1PgR+V9iWqN2gzv",\
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
          print(" Status: ", result_str);
          print(" Proof length: ", proof.size());
      }
};

EOSIO_DISPATCH(encryptedqry, (execquery)(callback))
