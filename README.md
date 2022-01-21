<p align="center">
	<img src="./public/new.chat-logo.png" width="600">
</p>

# new.chat-smart-contract

The new.chat smart contract is designed for encrypted messaging on EOSIO chains via ECDHE protocol.

# Dependencies

* eosio 2.0^
* eosio.cdt 1.6^
* cmake 3.5^

# Compiling

```
./build.sh -e /root/eosio/2.0 -c /usr/opt/eosio.cdt
```

# Deploying

```
cleos set contract <your_account> ./build/Release/new.chat new.chat.wasm new.chat.abi
```