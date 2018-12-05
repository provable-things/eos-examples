# Oraclize's Bitcoin Computation Example

This repo is to demonstrate how you would work with the Oraclize **computation** datasource.

The `bitcoincomp.cpp` example allows you to *retrieve the balance of a Bitcoin address*.

## Notes

Oraclize replies to your `oraclize_query` by calling your `callback(...)` with the *balance result* .
You can search for your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Blocks.io](https://jungle.bloks.io/): a block explorer for the Jungle 2.0 testnet.

* :palm_tree::lion::palm_tree: [Jungle 2.0](https://monitor.jungletestnet.io/#home): a transaction explorer is available selecting *Get TX* on the Jungle 2.0 testnet website.
