#pragma once
#include "contracts.hpp"
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/testing/tester.hpp>

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;

using namespace std;

using action_result = base_tester::action_result;
using mvo = fc::mutable_variant_object;

class a_dex_chat_api
{
public:
  a_dex_chat_api(name acnt, tester *tester);

   action_result send_direct_message(const account_name &signer, const account_name &from, const account_name &to,
                                     const string &iv, const string &ephem_key,
                                     const string &cipher_text, const string &mac);

  name contract;

private:
  action_result push_action(const name &signer, const name &cnt, const action_name &name, const variant_object &data);
  
  abi_serializer abi_ser;
  tester *_tester;
};