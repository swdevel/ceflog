#include "gtest/gtest.h"

#include "CEFEventStringSerializer.h"

TEST(CEFEventStringSerializerTest, SerializationTest)
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

    CEFEvent event(mockFormatVersion,
                   mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity,
                   mockExtensions);

    std::ostringstream oss;
    oss << event;

    const auto expectedString = oss.str();

    CEFEventStringSerializer serializer;

    EXPECT_EQ(serializer.Serialize(event), expectedString);
}