#include "new_chat_tester.hpp"

BOOST_AUTO_TEST_SUITE(create_public_channel_tests)

BOOST_FIXTURE_TEST_CASE(create_public_channel_test, new_chat_tester)
try
{
    const std::string description = "some description";

    BOOST_REQUIRE_EQUAL(error("missing authority of alice"),
                        m_chat_api.create_public_channel(N(bob), N(testch3), N(alice), description));

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("create_public_channel : channel already exist"),
                        m_chat_api.create_public_channel(N(alice), N(testch1), N(alice), description));

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("create_public_channel : description has more than 256 bytes"),
                        m_chat_api.create_public_channel(N(alice), N(testch3), N(alice), std::string("a",300)));

    BOOST_REQUIRE_EQUAL(success(), m_chat_api.create_public_channel(N(alice), N(testch3), N(alice), description));

    // auto channel = m_chat_api.get_public_channel(N(testch3));

    // std::cout << channel << std::endl;

    // BOOST_REQUIRE_EQUAL(channel["channel"], fc::variant("testch3"));
    // BOOST_REQUIRE_EQUAL(channel["owner"], fc::variant("alice"));
    // BOOST_REQUIRE_EQUAL(channel["description"], fc::variant("some description"));
    // BOOST_REQUIRE_EQUAL(channel["public_key"], fc::variant("EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV"));
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()