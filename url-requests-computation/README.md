# Oraclize's URL Requests Computation Example 

This repo is to demonstrate how you would work with the Oraclize **computation** datasource.

The `urlrequests.cpp` example allows you *to retrieve the response of several URL requests*.

## :page_with_curl: *Instructions*

**1)**: Compile your contract (launch this command **inside** the folder `url-requests-computation`):

**`❍ eosio-cpp -abigen urlrequests.cpp -o urlrequests.wasm`**

**2)**: Unlock your wallet:

**`❍ cleos wallet unlock -n <your-wallet-name> --password <your-wallet-password>`**

**3)**: Deploy your contract on EOS (launch this command **outside** the folder `url-requests-computation`):

**`❍ cleos set contract <your-account-name> url-requests-computation urlrequests.wasm -p <your-account-name>@<permission>`**

**4)**: Call the `reqheadscust` action of the contract `urlrequests`:

**`❍ cleos push action <your-account-name> reqheadscust '[]' -p <your-account-name>@<permission>`**

**5)**: Call the `reqbasauth` action of the contract `urlrequests`:

**`❍ cleos push action <your-account-name> reqbasauth '[]' -p <your-account-name>@<permission>`**

**6)**: Call the `reqpost` action of the contract `urlrequests`:

**`❍ cleos push action <your-account-name> reqpost '[]' -p <your-account-name>@<permission>`**

**7)**: Call the `reqput` action of the contract `urlrequests`:

**`❍ cleos push action <your-account-name> reqput '[]' -p <your-account-name>@<permission>`**

**9)**: Call the `reqcookies` action of the contract `urlrequests`:

**`❍ cleos push action <your-account-name> reqcookies '[]' -p <your-account-name>@<permission>`**

## :pen: Notes

Oraclize replies to your `oraclize_query` by calling your `callback(...)` with the *respose body result*. 
You can search for your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Blocks.io](https://jungle.bloks.io/): A block explorer for the Jungle 2.0 testnet.

* :palm_tree::lion::palm_tree: [Jungle 2.0](https://monitor.jungletestnet.io/#home): A transaction explorer is available by selecting *Get TX* on the Jungle 2.0 testnet website.

## :ambulance: Support

❍ If you have any issues, head on over to our [Gitter](https://gitter.im/oraclize/eos-api) channel
to get timely support!

***Happy developing!***
