#pragma once
#include <eosio/eosio.hpp>

using namespace eosio;

struct [[eosio::contract("a-dex.chat"), eosio::table]] channel
{
    name channel;
    name owner;
    std::string description;
    public_key public_key;

    uint64_t primary_key() const {
        return channel.value;
    }

    uint64_t owner_key() const {
        return owner.value;
    }

    checksum256 description_key() const {
        return sha256(description.data(), description.size());
    }
};
using by_owner = indexed_by<name("byowner"), const_mem_fun<channel, uint64_t, &channel::owner_key>>;
using by_description = indexed_by<name("bydescr"), const_mem_fun<channel, checksum256, &channel::description_key>>;

using public_channel = multi_index<name("pubchannels"), channel, by_owner, by_description>;
using private_channel = multi_index<name("prvchannels"), channel, by_owner, by_description>;