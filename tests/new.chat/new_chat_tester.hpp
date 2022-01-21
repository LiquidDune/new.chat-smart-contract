#pragma once
#include "contracts.hpp"
#include "new_chat_api.hpp"
#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

class new_chat_tester : public tester
{
protected:
    new_chat_api m_chat_api;

public:
    new_chat_tester();

private:
    void channels_init();
};