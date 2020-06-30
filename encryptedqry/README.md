# Provable's Encrypted Query Example

This repo is to demonstrate how you would work with the Provable **encrypted queries**.

The `encryptedqry.cpp` example allows you to *send an encrypted query*.

&nbsp;

## :lock: _Query Encryption_

**1)** Decide the Provable query you want to encrypt, the one in this example is:

```
provable_query(
  "URL",
  "json(https://min-api.cryptocompare.com/data/price?fsym=EOS&tsyms=USD&sign=true).USD",\
  (proofType_Native)
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

__`❍  python encrypted_queries_tools.py -e -p 044992e9473b7d90ca54d2886c7addd14a61109af202f1c95e218b0c99eb060c7134c4ae46345d0383ac996185762f04997d6fd6c393c86e4325c469741e64eca9 "json(https://min-api.cryptocompare.com/data/price?fsym=EOS&tsyms=USD&sign=true).USD"`__

it will generate a unique encrypted string (each re-run will generate a new unique string, as each encrypted string is meant to be used only by a single contract at a time):

```
BI1E+MtXQJXDFHVm38/YRZHMVe3s99a0rmQbdtUaa3w+EL/JALVJrvAKVIJi8OxON8vTo5K8x9P78qwQXovsDazeyV8tybIbcO6GlEy/tQXvtHClCPFjQREZ7uZfVd+0wWB1dqQO/WxCunCfgj8uiGFNQrlwwmyqc6/A/9lUUfoTf/koCI44sIOvsybELCg0m1ICaGKx1GhC8qJkChQwkACbY6Y=
```

**5)** Use the previous non-deterministic output and plug it into the query function:

```
provable_query(
  "URL",
  "BI1E+MtXQJXDFHVm38/YRZHMVe3s99a0rmQbdtUaa3w+EL/JALVJrvAKVIJi8OxON8vTo5K8x9P78qwQXovsDazeyV8tybIbcO6GlEy/tQXvtHClCPFjQREZ7uZfVd+0wWB1dqQO/WxCunCfgj8uiGFNQrlwwmyqc6/A/9lUUfoTf/koCI44sIOvsybELCg0m1ICaGKx1GhC8qJkChQwkACbY6Y=",\
  (proofType_Native)
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

Provable replies to your `provable_query` by calling your `callback(...)` with the *request status result* .
You can search for your transaction ID in one of the following links to verify it:

* :mag_right::ledger: [Blocks.io](https://jungle3.bloks.io/): A block explorer for the Jungle 3.0 testnet.

* :palm_tree::lion::palm_tree: [Jungle 3.0](https://monitor3.jungletestnet.io/#home): A transaction explorer is available by selecting *Get TX* on the Jungle 3.0 testnet website.

## :ambulance: Support

❍  If you have any issues, head on over to our [Gitter](https://gitter.im/provable/eos-api) channel to get timely support!

***Happy developing!***

