#pragma once
#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>
#include "resources.hpp"
#include "channel.hpp"

using namespace eosio;

class[[eosio::contract("a-dex.chat")]] chat : public contract
{
public:
    chat(name receiver, name code, datastream<const char *> ds);

    //For managing channels
    [[eosio::action("crtpubch")]] void create_public_channel(const name &channel, const name &owner, const std::string &description);

    [[eosio::action("crtprvch")]] void create_private_channel(const name &channel, const name &owner, const std::string &description, const public_key& public_key);

    //For managing messages
    [[eosio::action("senddm")]] void send_direct_message(const name &from, const name &to,
                                                         const std::vector<char> &iv, const public_key &ephem_key,
                                                         const std::vector<char> &cipher_text, const checksum256 &mac);

    [[eosio::action("sendpubchmsg")]] void send_public_channel_message(const name &from, const name &channel,
                                                                       const std::vector<char> &iv, const public_key &ephem_key,
                                                                       const std::vector<char> &cipher_text, const checksum256 &mac);

    [[eosio::action("sendprvchmsg")]] void send_private_channel_message(const name &from, const name &channel,
                                                                        const std::vector<char> &iv, const public_key &ephem_key,
                                                                        const std::vector<char> &cipher_text, const checksum256 &mac);

private:
    bool is_public_channel_exist(const name& channel);
    bool is_private_channel_exist(const name& channel);
};