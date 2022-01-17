#include "a-dex.chat.hpp"

chat::chat(name receiver, name code, datastream<const char *> ds)
    : contract::contract(receiver, code, ds)
{
}

void chat::create_public_channel(const name &channel, const name &owner, const std::string &description)
{
    require_auth(owner);
    public_channel _public_channel(get_self(), get_self().value);
    auto it = _public_channel.find(channel.value);
    check(it == _public_channel.end(), "create_public_channel : channel already exist");
    check(description.size() <= 256, "create_public_channel : description has more than 256 bytes");

    ecc_public_key default_key;
    std::memcpy(default_key.data(), DEFAULT_PUB_KEY.c_str(), default_key.size());
    public_key var_key(std::in_place_index<0>, default_key);

    _public_channel.emplace(owner, [&](auto &a) {
        a.channel = channel;
        a.owner = owner;
        a.description = description;
        a.public_key = var_key;
    });
}

void chat::create_private_channel(const name &channel, const name &owner, const std::string &description, const public_key& public_key)
{
    require_auth(owner);
    private_channel _private_channel(get_self(), get_self().value);
    auto it = _private_channel.find(channel.value);
    check(it == _private_channel.end(), "create_private_channel : channel already exist");
    check(description.size() <= 256, "create_private_channel : description has more than 256 bytes");

    _private_channel.emplace(owner, [&](auto &a) {
        a.channel = channel;
        a.owner = owner;
        a.description = description;
        a.public_key = public_key;
    });
}

void chat::send_direct_message(const name &from, const name &to,
                               const std::vector<char> &iv, const public_key &ephem_key,
                               const std::vector<char> &cipher_text, const checksum256 &mac)
{
    require_auth(from);
    check(from != to, "send_direct_message : can not send to self");
    check(is_account(to), "send_direct_message : to account does not exist");
    check(!iv.empty(), "send_direct_message : initialization vector should not be empty");
    check(!cipher_text.empty(), "send_direct_message : cipher_text should not be empty");
    check(mac != checksum256(), "send_direct_message : mac should not be empty");
    require_recipient(from);
    require_recipient(to);
}

void chat::send_public_channel_message(const name &from, const name &channel,
                                       const std::vector<char> &iv, const public_key &ephem_key,
                                       const std::vector<char> &cipher_text, const checksum256 &mac)
{
    require_auth(from);
    check(is_public_channel_exist(channel), "send_public_channel_message : channel is not exist");
    check(!iv.empty(), "send_public_channel_message : initialization vector should not be empty");
    check(!cipher_text.empty(), "send_public_channel_message : cipher_text should not be empty");
    check(mac != checksum256(), "send_public_channel_message : mac should not be empty");
    require_recipient(from);
}

void chat::send_private_channel_message(const name &from, const name &channel,
                                        const std::vector<char> &iv, const public_key &ephem_key,
                                        const std::vector<char> &cipher_text, const checksum256 &mac)
{
    require_auth(from);
    check(is_private_channel_exist(channel), "send_private_channel_message : channel is not exist");
    check(!iv.empty(), "send_private_channel_message : initialization vector should not be empty");
    check(!cipher_text.empty(), "send_private_channel_message : cipher_text should not be empty");
    check(mac != checksum256(), "send_private_channel_message : mac should not be empty");
    require_recipient(from);
}

bool chat::is_public_channel_exist(const name& channel)
{
    public_channel _public_channel(get_self(), get_self().value);
    auto it = _public_channel.find(channel.value);
    return it != _public_channel.end() ? true : false;
}

bool chat::is_private_channel_exist(const name& channel)
{
    private_channel _private_channel(get_self(), get_self().value);
    auto it = _private_channel.find(channel.value);
    return it != _private_channel.end() ? true : false;
}