#include <gtest/gtest.h>
#include <boost/nowide/args.hpp>
#include "binance_http.h"
#include "binance_types.h"

using namespace binance;

class HttpTest : public ::testing::Test
{
protected:
    HttpTest() : m_client{"https://www.t.zp.ua"}
    {
    }
    void SetUp() override
    {
    }
    void TearDown() override {}

    HTTPProvider m_client;
};

TEST_F(HttpTest, TestGetRequest)
{
    auto r = m_client.get<types::Array<types::response::KLine>>("/");
    ASSERT_EQ(true, true);
}

int main(int argc, char **argv)
{
    boost::nowide::args _(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}