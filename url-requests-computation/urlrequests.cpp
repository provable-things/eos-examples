#include "oraclize/eos_api.hpp"

using namespace eosio;


class urlrequests : public eosio::contract
{
  private:
    void request(const std::string _query, const std::string _method, const std::string _url, const std::string _kwargs) 
    { 
        std::vector<std::vector<unsigned char>> myquery = {
            string_to_vector(_query),
            string_to_vector(_method),
            string_to_vector(_url),
            string_to_vector(_kwargs)
        };
        oraclize_query("computation", myquery);
    }
 
  public:
    using contract::contract;

    urlrequests(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

    [[eosio::action]]
    void reqheadscust()
    {
        print("Sending query to Oraclize...");
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
    void callback(capi_checksum256 queryId, std::vector<unsigned char> result, std::vector<unsigned char> proof)
    {
        require_auth(oraclize_cbAddress());
 
        const std::string result_str = vector_to_string(result);
        print("Response: ", result_str);
    }
};

EOSIO_DISPATCH(urlrequests, (reqheadscust)(reqbasauth)(reqpost)(reqput)(reqcookies)(callback))
