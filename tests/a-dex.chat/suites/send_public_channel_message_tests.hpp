#include "a_dex_chat_tester.hpp"

BOOST_AUTO_TEST_SUITE(send_public_channel_message_tests)

BOOST_FIXTURE_TEST_CASE(send_public_channel_message_test, a_dex_chat_tester)
try
{
    const std::string iv = "e29f631e46e79e3de14bfb8b6fbedbbc";
    const std::string ephem_key = "EOS74g4jziVae5GXyWnkcaPEabGWkkXaXYRPRgrCprAXksa8zub59";
    const std::string cipher_text = "808abe25ad64d96c9efbcd260702508f4cc55f82c54910c99e";
    const std::string mac = "b835cae2f63e0876e5a00aee0c916f73a72bd34320f662df444b9b1ffb169c81";

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("send_public_channel_message : channel is not exist"),
                        m_chat_api.send_public_channel_message(N(alice), N(alice), N(notexisten), iv, ephem_key, cipher_text, mac));

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("send_public_channel_message : initialization vector should not be empty"),
                        m_chat_api.send_public_channel_message(N(alice), N(alice), N(testch1), "", ephem_key, cipher_text, mac));

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("send_public_channel_message : cipher_text should not be empty"),
                        m_chat_api.send_public_channel_message(N(alice), N(alice), N(testch1), iv, ephem_key, "", mac));

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("send_public_channel_message : mac should not be empty"),
                        m_chat_api.send_public_channel_message(N(alice), N(alice), N(testch1), iv, ephem_key, cipher_text, ""));

    BOOST_REQUIRE_EQUAL(success(), m_chat_api.send_public_channel_message(N(alice), N(alice), N(testch1), iv, ephem_key, cipher_text, mac));
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()