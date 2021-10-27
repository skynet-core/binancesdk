#include <gtest/gtest.h>

class ClientTest : public ::testing::Test
{
protected:
    ClientTest()
    {
    }
    void SetUp() override
    {
    }
    void TearDown() override {}
};

// TEST_F(ClientTest, JsonTest)
// {
//     types::request::KLines req{};
//     auto js = req.to_json().serialize();
//     ASSERT_STREQ(js.c_str(), _SU("{\"interval\":\"\",\"symbol\":\"\"}"));
//     req.symbol = _SU("BTCUSDT");
//     auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
//         std::chrono::system_clock::now().time_since_epoch());
//     req.start_time = ms;
//     js = req.to_json().serialize();

//     utility::stringstream_t ss;
//     ss << "{\"interval\":\"\",\"startTime\":";
//     ss << ms.count();
//     ss << ",\"symbol\":\"BTCUSDT\"}";
//     ASSERT_STREQ(js.c_str(), ss.str().c_str());
// }

// TEST_F(ClientTest, TestTrait)
// {
//     auto v = has_from_json<types::request::KLines>::value;
//     ASSERT_EQ(true, v);
//     v = has_from_json<types::response::KLine>::value;
//     ASSERT_EQ(true, v);
//     v = has_from_json<types::Array<types::response::KLine>>::value;
//     ASSERT_EQ(true, v);
// }

// TEST_F(ClientTest, Queries)
// {
//     types::request::KLines req{};
//     req.symbol = _SU("BTCUSDT");
//     req.interval = _SU("1m");
//     auto qp = req.to_query_params<params_map>();
//     auto str = to_query_string(qp);
//     ASSERT_STREQ(_SU("?interval=1m&symbol=BTCUSDT"), str.c_str());
// }

// TEST_F(ClientTest, TestGet)
// {
//     ASSERT_THROW(
//         {
//             types::request::KLines req{};
//             req.symbol = _SU("BTCUSDT");
//             // req.interval = U("1m");
//             auto j = req.to_query_params();
//             auto r = client.get<types::Array<types::response::KLine>>(_SU("/api/v3/klines"), j);
//         },
//         types::response::Error);
//     ASSERT_NO_THROW(
//         {
//             types::request::KLines req{};
//             req.symbol = _SU("BTCUSDT");
//             req.interval = _SU("1m");

//             constexpr system_clock::time_point tp =
//                 sys_days{2019_y / jan / 1_d};
//             req.start_time =
//                 std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());

//             auto j = req.to_query_params();
//             auto r = client.get<types::Array<types::response::KLine>>(_SU("/api/v3/klines"), j);
//             ASSERT_EQ(req.start_time.count(), r.values[0].open_time.count());
//         });
// }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}