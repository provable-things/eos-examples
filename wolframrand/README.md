# :wrench: :construction: Testing Oraclize's wolframrand Example

This repo is to demonstrate how you would work with the Oraclize **WolframAlpha** datasource.

The `wolframrand` example allows you to *retreive a random number from 1 to 6; and, if the number is
not 6, the callback launches a new query*.

## Notes

Oraclize replies to your `oraclize_query` with the *random number between 1 and 6 result* calling your `callback(...)`.
You can search your transaction ID in one of the following links to verify it:

  * :mag_right::ledger: **Blocks.io**: 

      https://jungle.bloks.io/

  * :palm_tree::lion::palm_tree: **Jungle 2.0** (Get TX): 
    
      https://monitor.jungletestnet.io/#tx
