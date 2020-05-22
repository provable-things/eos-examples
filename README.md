## __Provable EOS Examples__ - CDT 1.7 [![Join the chat at https://gitter.im/provable/eos-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/provable/eos-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) [![Docs@Provable.xyz](https://camo.githubusercontent.com/5e89710c6ae9ce0da822eec138ee1a2f08b34453/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f646f63732d536c6174652d627269676874677265656e2e737667)](http://docs.provable.xyz) [![Contributions Welcome!](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/provable-things/eos-examples/issues) [![HitCount](http://hits.dwyl.io/provable-things/eos-examples.svg)](http://hits.dwyl.io/provable-things/eos-examples)

Here you can find some code examples showing just how __easy__ it is to integrate the __Provable__ Service into your EOS smart-contracts! Thanks to our CDT 1.7 [__EOS API__](https://github.com/provable-things/eos-api) using __Provable__ in your projects couldn't be more straightforward.
In C++ it is as simple as importing __`provable/eos_api.hpp`__ in your contract like so:

```c++
    #include "provable/eos_api.hpp"
```

This provisions your contract with the __`oraclize_query()`__ function (and many others!), which makes it trivial to leverage our technology straight away.

:computer: Happy developing!

***

### :black_nib: __Notes__

This is a list of the features you will find amongst the examples, along with a reference to the relevant example:

* Sending simple __URL Queries!__ [#1](./eosusdprice/eosusdprice.cpp) [#2](./checkqueryid/checkqueryid.cpp) [#3](./dieselprice/dieselprice.cpp)
* Scheduling a query for a __future date!__ [#1](./wolframrand/wolframrand.cpp) [#2](./dieselprice/dieselprice.cpp)
* Sending calls __recursively__! [#1](./wolframrand/wolframrand.cpp)
* Requesting __Android__ authenticity __proofs!__ [#1](./eosusdprice/eosusdprice.cpp)
* Requesting __IPFS storage__ for the authenticity proofs! [#1](./eosusdprice/eosusdprice.cpp)
* Leveraging __JSONPATH__ parsing helpers! [#1](./eosusdprice/eosusdprice.cpp)
* Leveraging __XPATH__ parsing helpers! [#1](./dieselprice/dieselprice.cpp)
* Using the __random datasouce__! [#1](./randomsample/randomsample.cpp)
* Using the __computation datasouce__! [#1](./bitcoincomp/bitcoincomp.cpp) [#2](./urlrequests/urlrequests.cpp)
* Using the __WolframAlpha__ datasource! [#1](./wolframrand/wolframrand.cpp)

### :loudspeaker: __Support__

If you need any help working with the examples here, you can get timely support in the [__Provable Gitter__](https://gitter.im/provable/eos-api) channel.
