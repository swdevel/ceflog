#include "gtest/gtest.h"

#include "SyslogBoostClientBackend.h"

TEST(SyslogBoostClientBackend, ConstructorTest_InvalidParams)
{
    EXPECT_THROW(SyslogBoostClientBackend("127.0.0", "mockApplicationName"), std::exception);
    EXPECT_THROW(SyslogBoostClientBackend("::1", "mockApplicationName"), std::exception);
    EXPECT_THROW(SyslogBoostClientBackend("1", "mockApplicationName"), std::exception);
    EXPECT_THROW(SyslogBoostClientBackend("127.0.0.1", ""), std::exception);
}