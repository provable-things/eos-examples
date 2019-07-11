# Provable's Wolfram Alpha Example

This repo is to demonstrate how you would work with the Provable **WolframAlpha** datasource.

The `wolframrand.cpp` example allows you to *retrieve a random number from 1 to 6; and, if the number is
not 6, the `callback` launches a new query*.

## :page_with_curl: *Instructions*

**1)** Compile your contract (launch this command **inside** the folder `wolfram-alpha`):

**`❍ eosio-cpp -abigen wolframrand.cpp -o wolframrand.wasm`**

**2)** Unlock your wallet:

**`❍ cleos wallet unlock -n <your-wallet-name> --password <your-wallet-password>`**

**3)** Deploy your contract on EOS (launch this command **outside** the folder `wolfram-alpha`):

**`❍ cleos set contract <your-account-name> wolfram-alpha wolframrand.wasm wolframrand.abi -p <your-account-name>@<permission>`**

**4)** Call the `getrandomnum` action of the contract `wolframrand`:

**`❍ cleos push action <your-account-name> getrandomnum '[]' -p <your-account-name>@<permission>`**

## :pen: Notes

Provable replies to your `oraclize_query` by calling your `callback(...)` with the *random number between 1 and 6 result*.
You can search for your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Blocks.io](https://jungle.bloks.io/): A block explorer for the Jungle 2.0 testnet.

* :palm_tree::lion::palm_tree: [Jungle 2.0](https://monitor.jungletestnet.io/#home): A transaction explorer is available by selecting *Get TX* on the Jungle 2.0 testnet website.

## :ambulance: Support

❍  If you have any issues, head on over to our [Gitter](https://gitter.im/provable/eos-api) channel
to get timely support!

***Happy developing!***

