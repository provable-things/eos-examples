#include "provable/eos_api.hpp"

class urlrequests : public eosio::contract
{
  private:
    void request(
        const std::string _query,
        const std::string _method,
        const std::string _url,
        const std::string _kwargs
    )
    {
        std::vector<std::vector<unsigned char>> args = {
            string_to_vector(_query),
            string_to_vector(_method),
            string_to_vector(_url),
            string_to_vector(_kwargs)
        };
        std::vector<unsigned char> myquery = provable_set_computation_args(args);
        oraclize_query("computation", myquery);
    }

  public:
    using contract::contract;

    urlrequests(eosio::name receiver, eosio::name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

    [[eosio::action]]
    void reqheadscust()
    {
        print("Sending query to Provable...");
        request("json(QmdKK319Veha83h6AYgQqhx9YRsJ9MJE7y33oCXyZ4MqHE).headers",
                "GET",
                "http://httpbin.org/headers",
                "{'headers': {'content-type': 'json'}}"
               );
    }

    [[eosio::action]]
    void reqbasauth()
    {
        request("QmdKK319Veha83h6AYgQqhx9YRsJ9MJE7y33oCXyZ4MqHE",
                "GET",
                "http://httpbin.org/basic-auth/myuser/secretpass",
                "{'auth': ('myuser','secretpass'), 'headers': {'content-type': 'json'}}"
               );
    }

    [[eosio::action]]
    void reqpost()
    {
        request("QmdKK319Veha83h6AYgQqhx9YRsJ9MJE7y33oCXyZ4MqHE",
                "POST",
                "https://api.postcodes.io/postcodes",
                "{\"json\": {\"postcodes\" : [\"OX49 5NU\"]}}"
               );
    }

    [[eosio::action]]
    void reqput()
    {
        request("QmdKK319Veha83h6AYgQqhx9YRsJ9MJE7y33oCXyZ4MqHE",
                "PUT",
                "http://httpbin.org/anything",
                "{'json' : {'testing':'it works'}}"
               );
    }

    [[eosio::action]]
    void reqcookies()
    {
        request("QmdKK319Veha83h6AYgQqhx9YRsJ9MJE7y33oCXyZ4MqHE",
                "GET",
                "http://httpbin.org/cookies",
                "{'cookies' : {'thiscookie':'should be saved and visible :)'}}"
               );
    }

    [[eosio::action]]
    void callback(
        const eosio::checksum256 queryId,
        const std::vector<unsigned char> result,
        const std::vector<unsigned char> proof
    )
    {
        require_auth(provable_cbAddress());
        const std::string result_str = vector_to_string(result);
        print("Response: ", result_str);
    }
};

EOSIO_DISPATCH(urlrequests, (reqheadscust)(reqbasauth)(reqpost)(reqput)(reqcookies)(callback))
