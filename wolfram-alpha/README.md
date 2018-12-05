# Oraclize's Wolfram Alpha Example

This repo is to demonstrate how you would work with the Oraclize **WolframAlpha** datasource.

The `wolframrand` example allows you to *retrive a random number from 1 to 6; and, if the number is
not 6, the callback launches a new query*.

## Notes

Oraclize replies to your `oraclize_query` by calling your `callback(...)` with the *random number between 1 and 6 result*.
You can search for your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Blocks.io](https://jungle.bloks.io/): A block explorer for the Jungle 2.0 testnet.

* :palm_tree::lion::palm_tree: [Jungle 2.0](https://monitor.jungletestnet.io/#home): a transaction explorer is available selecting *Get TX* on the Jungle 2.0 testnet website.
