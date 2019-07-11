# Provable's Encrypted Query Example

This repo is to demonstrate how you would work with the Provable **encrypted queries**.

The `encryptedqry.cpp` example allows you to *send an encrypted query*.

&nbsp;

## :squirrel: _Query Encryption_

**1)** Decide the Provable query you want to encrypt, the one in this example is:

```
oraclize_query(
  "URL",
  "json(https://api.postcodes.io/postcodes).status",
  '{"postcodes" : ["OX49 5NU", "M32 0JG", "NE30 1DP"]}'
)
```

**2)** Fire up your favourite console & clone the Provable encyption tool repo somewhere:

__`❍ git clone https://github.com/provable-things/encrypted-queries.git`__

**3)** Enter the directory and brace yourself to encrypt your query with the Provable public key:

__`❍ cd encrypted-queries`__

Provable public key:

```
044992e9473b7d90ca54d2886c7addd14a61109af202f1c95e218b0c99eb060c7134c4ae46345d0383ac996185762f04997d6fd6c393c86e4325c469741e64eca9
```

**4)** Encrypt the first query argument:

__`❍  python encrypted_queries_tools.py -e -p 044992e9473b7d90ca54d2886c7addd14a61109af202f1c95e218b0c99eb060c7134c4ae46345d0383ac996185762f04997d6fd6c393c86e4325c469741e64eca9 "json(https://api.postcodes.io/postcodes).status"`__

that returns a non-determinist result:

```
BMqMhIFTTzsDbUSfPT233dVWB6wp0ksci7R/c6Jezcy3nEsnX7EQTaqRbej3shF7NlOwGRJAs1IBtYS32f6HrexffY+z1XMCHp+W6vFaIpDSVP0sVxiokuO0fr+ePxHOkvUh9x49BSmageBbHM1RB6QY/xhhvwJtssZOspEHvic=
```

**5)** Encrypt the second query argument:

__`❍  python encrypted_queries_tools.py -e -p 044992e9473b7d90ca54d2886c7addd14a61109af202f1c95e218b0c99eb060c7134c4ae46345d0383ac996185762f04997d6fd6c393c86e4325c469741e64eca9 '{"postcodes" : ["OX49 5NU", "M32 0JG", "NE30 1DP"]}'`__

that returns a non-determinist result:

```
BDfT0gaCqtru/YRL/qEDEPTopcKe04wXtkRlDw0PNa8hazsDgKXv1G0pBVaHK5um6eTzAggrLKlXVLSUqI6rVzd9oaDST4Zo1NtLf2iMwWI0yx7sWwuhFY0Ot+OltgHLf8SclyRuHZHiOq+Ubx1pBtFGImYH4yMon1PgR+V9iWqN2gzv
```

**6)** Use the non-deterministic outputs to send your Provable query:

```
oraclize_query(
  "URL",
  "BMqMhIFTTzsDbUSfPT233dVWB6wp0ksci7R/c6Jezcy3nEsnX7EQTaqRbej3shF7NlOwGRJAs1IBtYS32f6HrexffY+z1XMCHp+W6vFaIpDSVP0sVxiokuO0fr+ePxHOkvUh9x49BSmageBbHM1RB6QY/xhhvwJtssZOspEHvic=",
  "BDfT0gaCqtru/YRL/qEDEPTopcKe04wXtkRlDw0PNa8hazsDgKXv1G0pBVaHK5um6eTzAggrLKlXVLSUqI6rVzd9oaDST4Zo1NtLf2iMwWI0yx7sWwuhFY0Ot+OltgHLf8SclyRuHZHiOq+Ubx1pBtFGImYH4yMon1PgR+V9iWqN2gzv"
);
```

&nbsp;

## :page_with_curl: *Instructions*

**1)** Fire up your favourite console & clone this repo somewhere:

__`❍ git clone https://github.com/provable-things/eos-examples.git`__

**2)** Enter this directory & compile your contract:

__`❍ cd encryptedqry && eosio-cpp -abigen encryptedqry.cpp -o encryptedqry.wasm`__

**3)** Unlock your wallet:

__`❍ cleos wallet unlock -n <your-wallet-name> --password <your-wallet-password>`__

**4)** Go back to the root folder & deploy your contract on the EOS blockchain:

__`❍ cleos set contract <your-account-name> encryptedqry encryptedqry.wasm encryptedqry.abi -p <your-account-name>@<permission>`__

**5)** Call the `execquery` action of the contract `encryptedqry`:

__`❍ cleos push action <your-account-name> execquery '[]' -p <your-account-name>@<permission>`__

## :pen: Notes

Provable replies to your `oraclize_query` by calling your `callback(...)` with the *request status result* .
You can search for your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Blocks.io](https://jungle.bloks.io/): A block explorer for the Jungle 2.0 testnet.

* :palm_tree::lion::palm_tree: [Jungle 2.0](https://monitor.jungletestnet.io/#home): A transaction explorer is available by selecting *Get TX* on the Jungle 2.0 testnet website.

## :ambulance: Support

❍  If you have any issues, head on over to our [Gitter](https://gitter.im/provable/eos-api) channel to get timely support!

***Happy developing!***

