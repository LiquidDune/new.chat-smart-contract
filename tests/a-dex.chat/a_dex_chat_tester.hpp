#pragma once
#include "contracts.hpp"
#include "a_dex_chat_api.hpp"
#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

class a_dex_chat_tester : public tester
{
protected:
    a_dex_chat_api m_chat_api;

public:
    a_dex_chat_tester();
};