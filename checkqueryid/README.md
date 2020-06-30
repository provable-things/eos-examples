# Provable's Check Query ID Example

This repo is to demonstrate how you would work with the Provable **URL** datasource.

The `checkqueryid.cpp` example allows you to *retrieve the eos token price in usd, and check if the `queryId` of
your query matches the one provided by Provable in the callback*.

## :page_with_curl: *Instructions*

**1)** Compile your contract (launch this command **inside** the folder `check-queryid`):

**`❍ eosio-cpp -abigen checkqueryid.cpp -o checkqueryid.wasm`**

**2)** Unlock your wallet:

**`❍ cleos wallet unlock -n <your-wallet-name> --password <your-wallet-password>`**

**3)** Deploy your contract on EOS (launch this command **outside** the folder `check-queryid`):

**`❍ cleos set contract <your-account-name> check-queryid checkqueryid.wasm checkqueryid.abi -p <your-account-name>@<permission>`**

**4)** Call the `checkquery` action of the contract `checkqueryid`:

**`❍ cleos push action <your-account-name> checkquery '[]' -p <your-account-name>@<permission>`**

## :pen: Notes

Provable replies to your `provable_query` by calling your `callback(...)` with the *price result*.
You can search for your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Jungle 3 Blocks.io](https://jungle3.bloks.io/): A block explorer for the Jungle 3.0 testnet.

* :mag_right::ledger: [Kylin Blocks.io](https://kylin.bloks.io/): A block explorer for the Kylin testnet.

## :ambulance: Support

❍  If you have any issues, head on over to our [Gitter](https://gitter.im/provable/eos-api) channel to get timely support!

***Happy developing!***
