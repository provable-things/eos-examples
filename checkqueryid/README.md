# :wrench: :construction: Testing Oraclize's checkqueryid Example 

This repo is to demonstrate how you would work with the Oraclize **URL** datasource.

The `checkqueryid` example allows you to *retreive the eos token price in usd, and check that the query id of
your query matches the one provided by Oraclize in the callback*.

## Notes

Oraclize replies to your `oraclize_query` with the *price result* calling your `callback(...)`.
You can search your transaction ID in one of the following links to verify it:

  * :mag_right::ledger: **Blocks.io**: 

        https://jungle.bloks.io/

  * :palm_tree::lion::palm_tree: **Jungle 2.0** (Get TX): 
    
        https://monitor.jungletestnet.io/#tx
