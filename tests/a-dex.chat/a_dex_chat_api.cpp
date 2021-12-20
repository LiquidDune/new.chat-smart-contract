#include "a_dex_chat_api.hpp"

a_dex_chat_api::a_dex_chat_api(name acnt, tester *tester)
{
    contract = acnt;
    _tester = tester;

    _tester->create_accounts({contract});

    _tester->set_code(contract, contracts::a_dex_chat_wasm());
    _tester->set_abi(contract, contracts::a_dex_chat_abi().data());

    const auto &accnt = _tester->control->db().get<account_object, by_name>(contract);

    abi_def abi;
    BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
    abi_ser.set_abi(abi, base_tester::abi_serializer_max_time);
}

action_result a_dex_chat_api::send_direct_message(const account_name &signer, const account_name &from, const account_name &to,
                                                 const string &iv, const string &ephem_key,
                                                 const string &cipher_text, const string &mac)
{
    auto data = mutable_variant_object()
    ("from", from)
    ("to", to)
    ("iv", iv)
    ("ephem_key", ephem_key)
    ("cipher_text", cipher_text)
    ("mac", mac);

    return push_action(signer, contract, N(senddm), data);
}

action_result a_dex_chat_api::push_action(const name &signer, const name &cnt, const action_name &name, const variant_object &data)
{
    string action_type_name = abi_ser.get_action_type(name);
    action act;
    act.account = cnt;
    act.name = name;
    act.data = abi_ser.variant_to_binary(action_type_name, data, base_tester::abi_serializer_max_time);

    return _tester->push_action(std::move(act), signer.to_uint64_t());
}