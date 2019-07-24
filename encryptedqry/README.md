# Provable's Encrypted Query Example

This repo is to demonstrate how you would work with the Provable **encrypted queries**.

The `encryptedqry.cpp` example allows you to *send an encrypted query*.

&nbsp;

## :squirrel: _Query Encryption_

**1)** Decide the Provable query you want to encrypt, the one in this example is:

```
oraclize_query(
  "URL",
  "json(https://min-api.cryptocompare.com/data/price?fsym=EOS&tsyms=USD).USD",
)
```

**2)** Fire up your favourite console & clone the Provable encyption tool repo somewhere:

__`❍ git clone https://github.com/provable-things/encrypted-queries.git`__

**3)** Enter the directory and brace yourself to encrypt your query with the Provable public key & install python modules:

__`❍ cd encrypted-queries/tools && pip install base58`__

Provable public key:

```
044992e9473b7d90ca54d2886c7addd14a61109af202f1c95e218b0c99eb060c7134c4ae46345d0383ac996185762f04997d6fd6c393c86e4325c469741e64eca9
```

**4)** Encrypt the first query argument:

__`❍  python encrypted_queries_tools.py -e -p 044992e9473b7d90ca54d2886c7addd14a61109af202f1c95e218b0c99eb060c7134c4ae46345d0383ac996185762f04997d6fd6c393c86e4325c469741e64eca9 "json(https://min-api.cryptocompare.com/data/price?fsym=EOS&tsyms=USD).USD"`__

it will generate a unique encrypted string (each re-run will generate a new unique string, as each encrypted string is meant to be used only by a single contract at a time):

```
BFGZ3gbbKxeypLaf/8L/q6m1jgRG1s5P8OkRofvcjlvIlF6qtesDRtwxomTpfCsJSPfk8z/rw7rYzz8kZOzeh+bFOJyzsojnFektOk8aJuGvFWijFtZvtYAfnFmBDce/f+dcTLsnrmWW4DQIQ2+2LKrOHKliYImtjQlHsPXpQG3giaY5cRkDBCEXdDmJiWMQ8lRFatZYjXa95Q==
```

**5)** Use the previous non-deterministic output and plug it into the query function:

```
oraclize_query(
  "URL",
  "BFGZ3gbbKxeypLaf/8L/q6m1jgRG1s5P8OkRofvcjlvIlF6qtesDRtwxomTpfCsJSPfk8z/rw7rYzz8kZOzeh+bFOJyzsojnFektOk8aJuGvFWijFtZvtYAfnFmBDce/f+dcTLsnrmWW4DQIQ2+2LKrOHKliYImtjQlHsPXpQG3giaY5cRkDBCEXdDmJiWMQ8lRFatZYjXa95Q==",
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

