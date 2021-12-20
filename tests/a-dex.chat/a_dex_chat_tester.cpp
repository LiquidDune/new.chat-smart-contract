#include "a_dex_chat_tester.hpp"

a_dex_chat_tester::a_dex_chat_tester()
    : m_chat_api(N(chat.adex), this)
{
    create_accounts({
        N(alice),
        N(bob),
        N(carol),
    });
}