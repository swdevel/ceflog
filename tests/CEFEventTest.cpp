#include "gtest/gtest.h"

#include "CEFEvent.h"

class CEFEventTest : public testing::Test
{
public:
    CEFEventTest()
        : mockFormatVersion(2),
          mockDeviceVendor("Software Vendor"),
          mockDeviceProduct("Antivirus"),
          mockDeviceVersion("7.1"),
          mockDeviceEventClassId("200"),
          mockName("Worm successfully stopped"),
          mockSeverity(Severity::VeryHigh)
    {
    }

    void CheckEventFields(const CEFEvent& event) const
    {
        EXPECT_EQ(event.GetFormatVersion(), mockFormatVersion);
        EXPECT_EQ(event.GetDeviceVendor(), mockDeviceVendor);
        EXPECT_EQ(event.GetDeviceProduct(), mockDeviceProduct);
        EXPECT_EQ(event.GetDeviceVersion(), mockDeviceVersion);
        EXPECT_EQ(event.GetDeviceEventClassId(), mockDeviceEventClassId);
        EXPECT_EQ(event.GetName(), mockName);
        EXPECT_EQ(event.GetSeverity(), mockSeverity);
    }

protected:
    uint8_t mockFormatVersion;

    std::string mockDeviceVendor;

    std::string mockDeviceProduct;

    std::string mockDeviceVersion;

    std::string mockDeviceEventClassId;

    std::string mockName;

    Severity mockSeverity;
};

TEST_F(CEFEventTest, ConstructorTest)
{

    CEFEvent event(mockFormatVersion,
                   mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    CheckEventFields(event);
}

TEST_F(CEFEventTest, CopyConstructorTest)
{
    CEFEvent event(mockFormatVersion,
                   mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    CEFEvent copy(event);

    CheckEventFields(copy);
}

TEST_F(CEFEventTest, CopyAssignmentTest)
{
    CEFEvent event(mockFormatVersion,
                   mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    CEFEvent copy{};

    copy = event;

    CheckEventFields(copy);
}

TEST_F(CEFEventTest, MoveConstructorTest)
{
    CEFEvent event(mockFormatVersion,
                   mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    CEFEvent copy(std::move(event));

    CheckEventFields(copy);

    EXPECT_EQ(event.GetDeviceVendor(), "");
    EXPECT_EQ(event.GetDeviceProduct(), "");
    EXPECT_EQ(event.GetDeviceVersion(), "");
    EXPECT_EQ(event.GetDeviceEventClassId(), "");
    EXPECT_EQ(event.GetName(), "");
    EXPECT_EQ(event.GetSeverity(), Severity::Undefined);
}

TEST_F(CEFEventTest, MoveAssignmentTest)
{
    CEFEvent event(mockFormatVersion,
                   mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    CEFEvent copy{};

    copy = std::move(event);

    CheckEventFields(copy);

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

    event.SetFormatVersion(mockFormatVersion);
    event.SetDeviceVendor(mockDeviceVendor);
    event.SetDeviceProduct(mockDeviceProduct);
    event.SetDeviceVersion(mockDeviceVersion);
    event.SetDeviceEventClassId(mockDeviceEventClassId);
    event.SetName(mockName);
    event.SetSeverity(mockSeverity);

    CheckEventFields(event);
}

TEST_F(CEFEventTest, OverloadedEqualOperatorTest)
{
    CEFEvent left(mockFormatVersion,
                  mockDeviceVendor,
                  mockDeviceProduct,
                  mockDeviceVersion,
                  mockDeviceEventClassId,
                  mockName,
                  mockSeverity);

    CEFEvent right(left);

    EXPECT_TRUE(left == right);
}

TEST_F(CEFEventTest, OverloadedNotEqualOperatorTest)
{
    CEFEvent left(mockFormatVersion,
                  mockDeviceVendor,
                  mockDeviceProduct,
                  mockDeviceVersion,
                  mockDeviceEventClassId,
                  mockName,
                  mockSeverity);

    CEFEvent right(left);
    right.SetName("some other name");

    EXPECT_TRUE(left != right);
}

TEST_F(CEFEventTest, OverloadedInsertionOperatorTest)
{
    CEFEvent event(mockFormatVersion,
                   mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity);

    const auto prefix = std::string("CEF:") + std::to_string(mockFormatVersion);
    const auto severity = std::string(SeverityToString(event.GetSeverity()));

    std::string expected = prefix + '|' +
                           mockDeviceVendor + '|' +
                           mockDeviceProduct + '|' +
                           mockDeviceVersion + '|' +
                           mockDeviceEventClassId + '|' +
                           mockName + '|' +
                           severity + '|';

    std::ostringstream oss;
    oss << event;

    EXPECT_EQ(oss.str(), expected);
}