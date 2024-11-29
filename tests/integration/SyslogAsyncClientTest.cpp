#include <chrono>
#include <ctime>

#include <fstream>
#include <thread>

#include "gtest/gtest.h"

#include "SyslogAsyncClient.h"

class SyslogAsyncClientTest : public testing::Test
{
protected:
    SyslogAsyncClientTest()
        : syslogPath("/var/log/syslog")
    {
    }

    std::string GetLastStringFromFile(std::ifstream& ifstream) const
    {
        std::string result;

        while (ifstream >> std::ws && std::getline(ifstream, result))
            ;

        return result;
    }

    std::string GetTime()
    {
        const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string string = std::ctime(&time);

        return string.substr(0, string.size() - 1);
    }

    void SendMockMessageWithSpecifiedSeverity(const SyslogSeverity severity)
    {
        SyslogAsyncClient client("127.0.0.1", "mockApplicationName");

        const auto message = GetTime() +
                             std::string(" Mock message with syslog severity level = ") +
                             SyslogSeverityToString(severity);

        // Отправка сообщения
        client.PushMessage(severity, message);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Чтение последней строки из файла "/var/log/syslog"
        std::ifstream syslogFile{syslogPath};
        auto lastString = GetLastStringFromFile(syslogFile);

        // Поиск отправленного сообщения в прочитанной строке
        EXPECT_TRUE(lastString.find(message) != std::string::npos);
    }

protected:
    std::string syslogPath;
};

TEST_F(SyslogAsyncClientTest, ConstructorTest_InvalidParams)
{
    EXPECT_THROW(SyslogAsyncClient("127.0.0", "mockApplicationName"), std::exception);
    EXPECT_THROW(SyslogAsyncClient("::1", "mockApplicationName"), std::exception);
    EXPECT_THROW(SyslogAsyncClient("1", "mockApplicationName"), std::exception);
    EXPECT_THROW(SyslogAsyncClient("127.0.0.1", ""), std::exception);

    EXPECT_THROW(SyslogAsyncClient("127.0.0.1", "mockApplicationName", 0), std::exception);

    EXPECT_NO_THROW(SyslogAsyncClient("127.0.0.1", "mockApplicationName"));
}

TEST_F(SyslogAsyncClientTest, SetMaxTransmittedMessagesPerSecondTest)
{
    SyslogAsyncClient client("127.0.0.1", "mockApplicationName");

    EXPECT_THROW(client.SetMaxTransmittedMessagesPerSecond(0), std::exception);

    const uint32_t value = 10000;
    client.SetMaxTransmittedMessagesPerSecond(value);
    EXPECT_EQ(client.GetMaxTransmittedMessagesPerSecond(), value);
}

// FIXME: apparmor="DENIED" operation="open" class="file"

#if 0
TEST_F(SyslogAsyncClientTest, SendEmergencyMessageTest)
{
    SendMockMessageWithSpecifiedSeverity(SyslogSeverity::Emergency);
}

TEST_F(SyslogAsyncClientTest, SendAlertMessageTest)
{
    SendMockMessageWithSpecifiedSeverity(SyslogSeverity::Alert);
}
#endif

TEST_F(SyslogAsyncClientTest, SendCriticalMessageTest)
{
    SendMockMessageWithSpecifiedSeverity(SyslogSeverity::Critical);
}

TEST_F(SyslogAsyncClientTest, SendErrorMessageTest)
{
    SendMockMessageWithSpecifiedSeverity(SyslogSeverity::Error);
}

TEST_F(SyslogAsyncClientTest, SendWarningMessageTest)
{
    SendMockMessageWithSpecifiedSeverity(SyslogSeverity::Warning);
}

TEST_F(SyslogAsyncClientTest, SendNoticeMessageTest)
{
    SendMockMessageWithSpecifiedSeverity(SyslogSeverity::Notice);
}

TEST_F(SyslogAsyncClientTest, SendInfoMessageTest)
{
    SendMockMessageWithSpecifiedSeverity(SyslogSeverity::Info);
}

TEST_F(SyslogAsyncClientTest, SendDebugMessageTest)
{
    SendMockMessageWithSpecifiedSeverity(SyslogSeverity::Debug);
}