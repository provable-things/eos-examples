# Oraclize's Check Query ID Example 

This repo is to demonstrate how you would work with the Oraclize **URL** datasource.

The `checkqueryid.cpp` example allows you to retrieve the eos token price in usd, and check if the `queryId` of
your query matches the one provided by Oraclize in the callback*.

## Notes

Oraclize replies to your `oraclize_query` with the *price result* calling your `callback(...)`.
You can search your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Blocks.io](https://jungle.bloks.io/): a block explorer for the Jungle 2.0 testnet.

* :palm_tree::lion::palm_tree: [Jungle 2.0](https://monitor.jungletestnet.io/#home): a transaction explorer is available selecting *Get TX* on the Jungle 2.0 testnet website.
