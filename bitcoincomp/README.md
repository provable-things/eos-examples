# Provable's Bitcoin Computation Example

This repo is to demonstrate how you would work with the Provable **computation** datasource.

The `bitcoincomp.cpp` example allows you to *retrieve the balance of a Bitcoin address*.

## :page_with_curl: *Instructions*

**1)** Compile your contract (launch this command **inside** the folder `bitcoin-computation`):

**`❍ eosio-cpp -abigen bitcoincomp.cpp -o bitcoincomp.wasm`**

**2)** Unlock your wallet:

**`❍ cleos wallet unlock -n <your-wallet-name> --password <your-wallet-password>`**

**3)** Deploy your contract on EOS (launch this command **outside** the folder `bitcoin-computation`):

**`❍ cleos set contract <your-account-name> bitcoin-computation bitcoincomp.wasm bitcoincomp.abi -p <your-account-name>@<permission>`**

**4)** Call the `compute` action of the contract `bitcoincomp`:

**`❍ cleos push action <your-account-name> compute '[]' -p <your-account-name>@<permission>`**

## :pen: Notes

Provable replies to your `provable_query` by calling your `callback(...)` with the *balance result* .
You can search for your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Jungle 3 Blocks.io](https://jungle3.bloks.io/): A block explorer for the Jungle 3.0 testnet.

* :mag_right::ledger: [Kylin Blocks.io](https://kylin.bloks.io/): A block explorer for the Kylin testnet.

## :ambulance: Support

❍  If you have any issues, head on over to our [Gitter](https://gitter.im/provable/eos-api) channel to get timely support!

***Happy developing!***

