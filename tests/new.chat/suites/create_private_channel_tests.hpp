#include "new_chat_tester.hpp"

BOOST_AUTO_TEST_SUITE(create_private_channel_tests)

BOOST_FIXTURE_TEST_CASE(create_private_channel_test, new_chat_tester)
try
{
    const std::string description = "some description";
    const std::string public_key = "EOS74g4jziVae5GXyWnkcaPEabGWkkXaXYRPRgrCprAXksa8zub59";
    auto key =  fc::crypto::public_key(public_key);

    BOOST_REQUIRE_EQUAL(error("missing authority of alice"),
                        m_chat_api.create_private_channel(N(bob), N(testch3), N(alice), description, key));

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("create_private_channel : channel already exist"),
                        m_chat_api.create_private_channel(N(alice), N(testch1), N(alice), description, key));

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("create_private_channel : description has more than 256 bytes"),
                        m_chat_api.create_private_channel(N(alice), N(testch3), N(alice), std::string("a",300), key));

    BOOST_REQUIRE_EQUAL(success(), m_chat_api.create_private_channel(N(alice), N(testch3), N(alice), description, key));

    // auto channel = m_chat_api.get_private_channel(N(testch3));
    // std::cout << channel << std::endl;

    // BOOST_REQUIRE_EQUAL(channel["channel"], fc::variant("testch3"));
    // BOOST_REQUIRE_EQUAL(channel["owner"], fc::variant("alice"));
    // BOOST_REQUIRE_EQUAL(channel["description"], fc::variant("some description"));
    // BOOST_REQUIRE_EQUAL(channel["public_key"], fc::variant("EOS74g4jziVae5GXyWnkcaPEabGWkkXaXYRPRgrCprAXksa8zub59"));
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()