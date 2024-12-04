#include "gtest/gtest.h"

#include "CEFEventFactory.h"

using namespace ceflog::event;

TEST(CEFEventFactoryTest, CreateEventTest)
{
    const uint8_t mockFormatVersion = 1;
    const std::string mockDeviceVendor = "Security";
    const std::string mockDeviceProduct = "threatmanager";
    const std::string mockDeviceVersion = "1.0";
    const std::string mockDeviceEventClassId = "100";
    const std::string mockName = "worm successfully stopped";

    const CEFSeverity mockSeverity = CEFSeverity::VeryHigh;

    const std::vector<CEFEventExtension> mockExtensions = {{"src", "10.0.0.1"},
                                                           {"action", "blocked"},
                                                           {"dst", "2.1.2.2"}};

    CEFEvent expectedEvent(mockFormatVersion,
                           mockDeviceVendor,
                           mockDeviceProduct,
                           mockDeviceVersion,
                           mockDeviceEventClassId,
                           mockName,
                           mockSeverity,
                           mockExtensions);

    CEFEventFactory factory(mockFormatVersion, mockDeviceVendor, mockDeviceProduct, mockDeviceVersion);

    auto event = factory.CreateEvent(mockDeviceEventClassId, mockName, mockSeverity, mockExtensions);

    EXPECT_EQ(event, expectedEvent);
}