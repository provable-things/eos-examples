# Provable's EOS/USD Price Example

This repo is to demonstrate how you would work with the Provable **URL** datasource.

The `eosusdprice.cpp` example allows you to *retrieve the eos token price in usd* and ***provides
you with the authenticity proof of the fetched data***.

## :page_with_curl: *Instructions*

**1)** Compile your contract (launch this command **inside** the folder `eos-usd-price`):

**`❍ eosio-cpp -abigen eosusdprice.cpp -o eosusdprice.wasm`**

**2)** Unlock your wallet:

**`❍ cleos wallet unlock -n <your-wallet-name> --password <your-wallet-password>`**

**3)** Deploy your contract on EOS (launch this command **outside** the folder `eos-usd-price`):

**`❍ cleos set contract <your-account-name> eos-usd-price eosusdprice.wasm eosusdprice.abi -p <your-account-name>@<permission>`**

**4)** Call the `execquery` action of the contract `eosusdprice`:

**`❍ cleos push action <your-account-name> execquery '[]' -p <your-account-name>@<permission>`**

## :pen: Notes

Provable replies to your `provable_query` by calling your `callback(...)` with the *price result*.
You can search your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Jungle 3 Blocks.io](https://jungle3.bloks.io/): A block explorer for the Jungle 3.0 testnet.

* :mag_right::ledger: [Kylin Blocks.io](https://kylin.bloks.io/): A block explorer for the Kylin testnet.

## :ambulance: Support

❍  If you have any issues, head on over to our [Gitter](https://gitter.im/provable/eos-api) channel to get timely support!

***Happy developing!***

