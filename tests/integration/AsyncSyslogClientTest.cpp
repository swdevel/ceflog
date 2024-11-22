#include "gtest/gtest.h"

#include "AsyncSyslogClient.h"

class AsyncSyslogClientTest : public testing::Test
{
protected:
    AsyncSyslogClientTest()
        : syslogPath("/var/log/syslog")
    {
    }

protected:
    std::string syslogPath;
};

TEST_F(AsyncSyslogClientTest, ConstructorTest_InvalidParams)
{
    EXPECT_THROW(AsyncSyslogClient("127.0.0", "mockApplicationName"), std::exception);
    EXPECT_THROW(AsyncSyslogClient("::1", "mockApplicationName"), std::exception);
    EXPECT_THROW(AsyncSyslogClient("1", "mockApplicationName"), std::exception);
    EXPECT_THROW(AsyncSyslogClient("127.0.0.1", ""), std::exception);

    EXPECT_NO_THROW(AsyncSyslogClient("127.0.0.1", "mockApplicationName"));
}