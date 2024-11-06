#include "gtest/gtest.h"

#include "CEFEvent.h"

class CEFEventTest : public testing::Test
{
public:
    CEFEventTest()
        : mockDeviceVendor(""),
          mockDeviceProduct(""),
          mockDeviceVersion(""),
          mockDeviceEventClassId(""),
          mockName(""),
          mockSeverity(Severity::VeryHigh)
    {
    }

protected:
    std::string mockDeviceVendor;

    std::string mockDeviceProduct;

    std::string mockDeviceVersion;

    std::string mockDeviceEventClassId;

    std::string mockName;

    Severity mockSeverity;
};

TEST_F(CEFEventTest, ConstructorTest)
{

    CEFEvent event(mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    EXPECT_EQ(event.GetDeviceVendor(), mockDeviceVendor);
    EXPECT_EQ(event.GetDeviceProduct(), mockDeviceProduct);
    EXPECT_EQ(event.GetDeviceVersion(), mockDeviceVersion);
    EXPECT_EQ(event.GetDeviceEventClassId(), mockDeviceEventClassId);
    EXPECT_EQ(event.GetName(), mockName);
    EXPECT_EQ(event.GetSeverity(), mockSeverity);
}