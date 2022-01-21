#include "new_chat_api.hpp"

new_chat_api::new_chat_api(name acnt, tester *tester)
{
    contract = acnt;
    _tester = tester;

    _tester->create_accounts({contract});

    _tester->set_code(contract, contracts::new_chat_wasm());
    _tester->set_abi(contract, contracts::new_chat_abi().data());

    const auto &accnt = _tester->control->db().get<account_object, by_name>(contract);

    abi_def abi;
    BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
    abi_ser.set_abi(abi, base_tester::abi_serializer_max_time);
}

fc::variant new_chat_api::get_public_channel(const account_name &channel)
{
    vector<char> data = _tester->get_row_by_account(contract, contract, N(pubchannels), channel);
    return data.empty() ? fc::variant() : abi_ser.binary_to_variant("channel", data, base_tester::abi_serializer_max_time);
}

fc::variant new_chat_api::get_private_channel(const account_name &channel)
{
    vector<char> data = _tester->get_row_by_account(contract, contract, N(prvchannels), channel);
    return data.empty() ? fc::variant() : abi_ser.binary_to_variant("channel", data, base_tester::abi_serializer_max_time);
}

action_result new_chat_api::create_public_channel(const account_name &signer, const account_name &channel,
                                                    const account_name &owner, const std::string &description)
{
    auto data = mutable_variant_object()
    ("channel", channel)
    ("owner", owner)
    ("description", description);

    return push_action(signer, contract, N(crtpubch), data);
}

action_result new_chat_api::create_private_channel(const account_name &signer, const account_name &channel,
                                                     const account_name &owner, const std::string &description, const fc::crypto::public_key& public_key)
{
    auto data = mutable_variant_object()
    ("channel", channel)
    ("owner", owner)
    ("description", description)
    ("public_key", public_key);

    return push_action(signer, contract, N(crtprvch), data);
}

action_result new_chat_api::send_direct_message(const account_name &signer, const account_name &from, const account_name &to,
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

action_result new_chat_api::send_public_channel_message(const account_name &signer, const account_name &from, const account_name &channel,
                                                          const string &iv, const string &ephem_key,
                                                          const string &cipher_text, const string &mac)
{
    auto data = mutable_variant_object()
    ("from", from)
    ("channel", channel)
    ("iv", iv)
    ("ephem_key", ephem_key)
    ("cipher_text", cipher_text)
    ("mac", mac);

    return push_action(signer, contract, N(sendpubchmsg), data);
}

action_result new_chat_api::send_private_channel_message(const account_name &signer, const account_name &from, const account_name &channel,
                                                           const string &iv, const string &ephem_key,
                                                           const string &cipher_text, const string &mac)
{
    auto data = mutable_variant_object()
    ("from", from)
    ("channel", channel)
    ("iv", iv)
    ("ephem_key", ephem_key)
    ("cipher_text", cipher_text)
    ("mac", mac);

    return push_action(signer, contract, N(sendprvchmsg), data);
}

action_result new_chat_api::push_action(const name &signer, const name &cnt, const action_name &name, const variant_object &data)
{
    string action_type_name = abi_ser.get_action_type(name);
    action act;
    act.account = cnt;
    act.name = name;
    act.data = abi_ser.variant_to_binary(action_type_name, data, base_tester::abi_serializer_max_time);

    return _tester->push_action(std::move(act), signer.to_uint64_t());
}