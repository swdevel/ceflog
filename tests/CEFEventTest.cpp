#include "gtest/gtest.h"

#include "CEFEvent.h"

class CEFEventTest : public testing::Test
{
public:
    CEFEventTest()
        : mockDeviceVendor("Software Vendor"),
          mockDeviceProduct("Antivirus"),
          mockDeviceVersion("7.1"),
          mockDeviceEventClassId("200"),
          mockName("Worm successfully stopped"),
          mockSeverity(Severity::VeryHigh)
    {
    }

    void CheckFields(const CEFEvent& event) const
    {
        EXPECT_EQ(event.GetDeviceVendor(), mockDeviceVendor);
        EXPECT_EQ(event.GetDeviceProduct(), mockDeviceProduct);
        EXPECT_EQ(event.GetDeviceVersion(), mockDeviceVersion);
        EXPECT_EQ(event.GetDeviceEventClassId(), mockDeviceEventClassId);
        EXPECT_EQ(event.GetName(), mockName);
        EXPECT_EQ(event.GetSeverity(), mockSeverity);
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

    CheckFields(event);
}

TEST_F(CEFEventTest, CopyConstructorTest)
{
    CEFEvent event(mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    CEFEvent copy(event);

    CheckFields(copy);
}

TEST_F(CEFEventTest, CopyAssignmentTest)
{
    CEFEvent event(mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    CEFEvent copy{};

    copy = event;

    CheckFields(copy);
}

TEST_F(CEFEventTest, MoveConstructorTest)
{
    CEFEvent event(mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    CEFEvent copy(std::move(event));

    CheckFields(copy);

    EXPECT_EQ(event.GetDeviceVendor(), "");
    EXPECT_EQ(event.GetDeviceProduct(), "");
    EXPECT_EQ(event.GetDeviceVersion(), "");
    EXPECT_EQ(event.GetDeviceEventClassId(), "");
    EXPECT_EQ(event.GetName(), "");
    EXPECT_EQ(event.GetSeverity(), Severity::Undefined);
}

TEST_F(CEFEventTest, MoveAssignmentTest)
{
    CEFEvent event(mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    CEFEvent copy{};

    copy = std::move(event);

    CheckFields(copy);

    EXPECT_EQ(event.GetDeviceVendor(), "");
    EXPECT_EQ(event.GetDeviceProduct(), "");
    EXPECT_EQ(event.GetDeviceVersion(), "");
    EXPECT_EQ(event.GetDeviceEventClassId(), "");
    EXPECT_EQ(event.GetName(), "");
    EXPECT_EQ(event.GetSeverity(), Severity::Undefined);
}

TEST_F(CEFEventTest, SettersTest)
{
    CEFEvent event;

    event.SetDeviceVendor(mockDeviceVendor);
    event.SetDeviceProduct(mockDeviceProduct);
    event.SetDeviceVersion(mockDeviceVersion);
    event.SetDeviceEventClassId(mockDeviceEventClassId);
    event.SetName(mockName);
    event.SetSeverity(mockSeverity);

    CheckFields(event);
}