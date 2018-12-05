# Oraclize's EOS/USD Price Example

This repo is to demonstrate how you would work with the Oraclize **URL** datasource.

The `eosusdprice.cpp` example allows you to *retrieve the eos token price in usd* and ***provides
you an authenticity proof of the fetched data***.

## :page_with_curl: *Instructions*

**1)**: Compile your contract (launch this command **inside** the folder `eos-usd-price`):

**`❍ eosio-cpp -abigen eosusdprice.cpp -o eosusdprice.wasm`**

**2)**: Unlock your wallet:

**`❍ cleos wallet unlock -n <your-wallet-name> --password <your-wallet-password>`**

**3)**: Deploy your contract on EOS (launch this command **outside** the folder `eos-usd-price`):

**`❍ cleos set contract <your-account-name> eos-usd-price eosusdprice.wasm -p <your-account-name>@<permission>`**

**4)**: Call the `execquery` action of the contract `eosusdprice`:

**`❍ cleos push action <your-account-name> execquery '[]' -p <your-account-name>@<permission>`**

## :pen: Notes

Oraclize replies to your `oraclize_query` by calling your `callback(...)` with the *price result*.
You can search your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Blocks.io](https://jungle.bloks.io/): A block explorer for the Jungle 2.0 testnet.

* :palm_tree::lion::palm_tree: [Jungle 2.0](https://monitor.jungletestnet.io/#home): A transaction explorer is available by selecting *Get TX* on the Jungle 2.0 testnet website.

## :ambulance: Support

❍ If you have any issues, head on over to our [Gitter](https://gitter.im/oraclize/eos-api) channel to get timely support!

***Happy developing!***
