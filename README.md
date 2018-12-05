## __Oraclize EOS Examples__ [![Join the chat at https://gitter.im/oraclize/eos-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/oraclize/eos-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) [![Docs@Oraclize.it](https://camo.githubusercontent.com/5e89710c6ae9ce0da822eec138ee1a2f08b34453/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f646f63732d536c6174652d627269676874677265656e2e737667)](http://docs.oraclize.it) [![Contributions Welcome!](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/oraclize/eos-examples/issues) [![HitCount](http://hits.dwyl.io/oraclize/eos-examples.svg)](http://hits.dwyl.io/oraclize/eos-examples)

Here you can find some code examples showing just how __easy__ it is to integrate the __Oraclize__ Service into your EOS smart-contracts! Thanks to our [__EOS API__](https://github.com/oraclize/eos-api) using __Oraclize__ in your projects couldn't be more straightforward.
In C++ it is as simple as importing __`oraclize/eos_api.hpp`__ in your contract like so:

```
    #include "oraclize/eos_api.hpp"
```

This provisions your contract with the __`oraclize_query()`__ function (and many others!), which makes it trivial to leverage our technology straight away.

:computer: Happy developing!

***

### :black_nib: __Notes__

This is a list of the features you will find amongst the examples, along with a reference to the relevant example:

* Sending simple __URL Queries!__ [#1](./eos-usd-price/eosusdprice.cpp) [#2](./check-queryid/checkqueryid.cpp)
* Sending calls __recursively__! [#1](./wolfram-alpha/wolframrand.cpp)
* Requesting __Android__ authenticity __proofs!__ [#1](./eos-usd-price/eosusdprice.cpp)
* Requesting __IPFS storage__ for the authenticity proofs! [#1](./eos-usd-price/eosusdprice.cpp)
* Leveraging __JSONPATH__ parsing helpers! [#1](./eos-usd-price/eosusdprice.cpp)
* Using the __random datasouce__! [#1](./random-datasource/randomsample.cpp)
* Using the __computation datasouce__! [#1](./bitcoin-computation/bitcoincomp.cpp) [#2](./url-requests-computation/urlrequests.cpp)
* Using the __WolframAlpha__ datasource! [#1](./wolfram-alpha/wolframrand.cpp)

### :loudspeaker: __Support__

If you need any help working with the examples here, you can get timely support in the [__Oraclize Gitter__](https://gitter.im/oraclize) channel.