#include "gtest/gtest.h"

#include "CEFEvent.h"

class CEFEventTest : public testing::Test
{
public:
    CEFEventTest()
        : mockFormatVersion(2),
          mockDeviceVendor("Security"),
          mockDeviceProduct("threatmanager"),
          mockDeviceVersion("1.0"),
          mockDeviceEventClassId("100"),
          mockName("worm successfully stopped"),
          mockSeverity(CEFSeverity::VeryHigh)
    {
        mockExtensions.push_back({"src", "10.0.0.1"});
        mockExtensions.push_back({"action", "blocked"});
        mockExtensions.push_back({"dst", "2.1.2.2"});
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

        const auto extensions = event.GetExtensions();

        EXPECT_TRUE(
            std::equal(extensions.begin(), extensions.end(),
                       mockExtensions.begin(), mockExtensions.end(),
                       [](auto const& left, auto const& right) {
                           return (left.key == right.key) && (left.value == right.value);
                       }));
    }

protected:
    uint8_t mockFormatVersion;

    std::string mockDeviceVendor;

    std::string mockDeviceProduct;

    std::string mockDeviceVersion;

    std::string mockDeviceEventClassId;

    std::string mockName;

    CEFSeverity mockSeverity;

    std::vector<CEFEventExtension> mockExtensions;
};

TEST_F(CEFEventTest, ConstructorTest)
{

    CEFEvent event(mockFormatVersion,
                   mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity,
                   mockExtensions);

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
                   mockSeverity,
                   mockExtensions);

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
                   mockSeverity,
                   mockExtensions);

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
                   mockSeverity,
                   mockExtensions);

    CEFEvent copy(std::move(event));

    CheckEventFields(copy);

    EXPECT_EQ(event.GetDeviceVendor(), "");
    EXPECT_EQ(event.GetDeviceProduct(), "");
    EXPECT_EQ(event.GetDeviceVersion(), "");
    EXPECT_EQ(event.GetDeviceEventClassId(), "");
    EXPECT_EQ(event.GetName(), "");

    EXPECT_EQ(event.GetSeverity(), CEFSeverity::Undefined);

    EXPECT_TRUE(event.GetExtensions().empty());
}

TEST_F(CEFEventTest, MoveAssignmentTest)
{
    CEFEvent event(mockFormatVersion,
                   mockDeviceVendor,
                   mockDeviceProduct,
                   mockDeviceVersion,
                   mockDeviceEventClassId,
                   mockName,
                   mockSeverity,
                   mockExtensions);

    CEFEvent copy{};

    copy = std::move(event);

    CheckEventFields(copy);

    EXPECT_EQ(event.GetDeviceVendor(), "");
    EXPECT_EQ(event.GetDeviceProduct(), "");
    EXPECT_EQ(event.GetDeviceVersion(), "");
    EXPECT_EQ(event.GetDeviceEventClassId(), "");
    EXPECT_EQ(event.GetName(), "");

    EXPECT_EQ(event.GetSeverity(), CEFSeverity::Undefined);

    EXPECT_TRUE(event.GetExtensions().empty());
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

    for (const auto& entry : mockExtensions) {
        event.PushExtension(entry);
    }

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
                  mockSeverity,
                  mockExtensions);

    CEFEvent right(left);

    EXPECT_TRUE(left == right);
}

TEST_F(CEFEventTest, OverloadedNotEqualOperatorTest1)
{
    CEFEvent left(mockFormatVersion,
                  mockDeviceVendor,
                  mockDeviceProduct,
                  mockDeviceVersion,
                  mockDeviceEventClassId,
                  mockName,
                  mockSeverity,
                  mockExtensions);

    CEFEvent right(left);

    right.SetName("Detected a threat. No action needed");

    EXPECT_TRUE(left != right);
}

TEST_F(CEFEventTest, OverloadedNotEqualOperatorTest2)
{
    CEFEvent left(mockFormatVersion,
                  mockDeviceVendor,
                  mockDeviceProduct,
                  mockDeviceVersion,
                  mockDeviceEventClassId,
                  mockName,
                  mockSeverity,
                  mockExtensions);

    CEFEvent right(left);

    right.SetSeverity(CEFSeverity::Low);

    EXPECT_TRUE(left != right);
}

TEST_F(CEFEventTest, OverloadedNotEqualOperatorTest3)
{
    CEFEvent left(mockFormatVersion,
                  mockDeviceVendor,
                  mockDeviceProduct,
                  mockDeviceVersion,
                  mockDeviceEventClassId,
                  mockName,
                  mockSeverity);

    CEFEvent right(left);

    right.PushExtension(mockExtensions[0]);
    right.PushExtension(mockExtensions[1]);

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
                   mockSeverity,
                   mockExtensions);

    const auto prefix = std::string("CEF:") + std::to_string(mockFormatVersion);
    const auto severity = std::string(CEFSeverityToString(event.GetSeverity()));

    std::string expected = prefix + '|' +
                           mockDeviceVendor + '|' +
                           mockDeviceProduct + '|' +
                           mockDeviceVersion + '|' +
                           mockDeviceEventClassId + '|' +
                           mockName + '|' +
                           severity + '|';

    std::string extensions;

    for (const auto& entry : mockExtensions) {

        if (!extensions.empty()) {
            extensions += ' ';
        }

        extensions += entry.key + "=" + entry.value;
    }

    expected += extensions;

    std::ostringstream oss;
    oss << event;

    EXPECT_EQ(oss.str(), expected);
}

TEST_F(CEFEventTest, EscapeCharactersTest)
{
    uint8_t formatVersion = 2;
    std::string deviceVendor = "|Security|";
    std::string deviceProduct = "|\\threatmanager\\|";
    std::string deviceVersion = "1.0";
    std::string deviceEventClassId = "100";
    std::string name = "worm -== successfully ==- \\stopped\\";
    CEFSeverity severity = CEFSeverity::VeryHigh;

    std::vector<CEFEventExtension> extensions;

    extensions.push_back({"src", "10.0.0.1"});
    extensions.push_back({"action", "blocked"});
    extensions.push_back({"dst", "2.1.2.2"});
    extensions.push_back({"filePath", "/user/username/dir/my file name.txt"});
    extensions.push_back({"id", "---===235===---"});

    CEFEvent event(formatVersion,
                   deviceVendor,
                   deviceProduct,
                   deviceVersion,
                   deviceEventClassId,
                   name,
                   severity,
                   extensions);

    std::ostringstream oss;
    oss << event;

    std::string expected = "CEF:2|\\|Security\\||\\|\\\\threatmanager\\\\\\||1.0|"
                           "100|worm -== successfully ==- \\\\stopped\\\\|VeryHigh|"
                           "src=10.0.0.1 action=blocked dst=2.1.2.2 "
                           "filePath=/user/username/dir/my file name.txt "
                           "id=---\\=\\=\\=235\\=\\=\\=---";

    EXPECT_EQ(oss.str(), expected);
}