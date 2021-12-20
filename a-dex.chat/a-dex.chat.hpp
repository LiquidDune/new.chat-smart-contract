#pragma once
#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>

using namespace eosio;

class[[eosio::contract("a-dex.chat")]] chat : public contract
{
public:
    chat(name receiver, name code, datastream<const char *> ds);

    //For managing messages
    [[eosio::action("senddm")]] void send_direct_message(const name &from, const name &to,
                                                         const std::vector<char> &iv, const public_key &ephem_key,
                                                         const std::vector<char> &cipher_text, const checksum256 &mac);
};