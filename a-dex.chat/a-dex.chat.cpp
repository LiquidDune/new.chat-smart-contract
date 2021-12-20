#include "a-dex.chat.hpp"

chat::chat(name receiver, name code, datastream<const char *> ds)
    : contract::contract(receiver, code, ds)
{
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
    require_recipient(to);
}