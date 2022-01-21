#include "new_chat_tester.hpp"

new_chat_tester::new_chat_tester()
    : m_chat_api(N(chat.adex), this)
{
    create_accounts({
        N(alice),
        N(bob),
        N(carol),
    });

    channels_init();
}

void new_chat_tester::channels_init()
{
    BOOST_REQUIRE_EQUAL(success(), m_chat_api.create_private_channel(N(alice), N(testch1), N(alice), "description", fc::crypto::public_key(std::string("EOS74g4jziVae5GXyWnkcaPEabGWkkXaXYRPRgrCprAXksa8zub59"))));

    BOOST_REQUIRE_EQUAL(success(), m_chat_api.create_public_channel(N(alice), N(testch1), N(alice), "description"));
}
