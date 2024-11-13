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
        mockExtensions.push_back({"src", "10.0.0.1"});
        mockExtensions.push_back({"action", "blocked"});
        mockExtensions.push_back({"dst", "10.0.0.1"});
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

        auto extensions = event.GetExtensions();

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

    Severity mockSeverity;

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

    right.SetName("Some other name");

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

    right.SetSeverity(Severity::Low);

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
    const auto severity = std::string(SeverityToString(event.GetSeverity()));

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
    std::string deviceVendor = "|Software Vendor|";
    std::string deviceProduct = "|\\Antivirus\\|";
    std::string deviceVersion = "7.1";
    std::string deviceEventClassId = "200";
    std::string name = "Worm -== successfully ==- \\stopped\\";
    Severity severity = Severity::Medium;

    std::vector<CEFEventExtension> extensions;

    extensions.push_back({"src", "10.0.0.1"});
    extensions.push_back({"action", "blocked"});
    extensions.push_back({"dst", "10.0.0.1"});
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

    std::string expected = "CEF:2|\\|Software Vendor\\||\\|\\\\Antivirus\\\\\\||7.1|"
                           "200|Worm -== successfully ==- \\\\stopped\\\\|Medium|"
                           "src=10.0.0.1 action=blocked dst=10.0.0.1 "
                           "filePath=/user/username/dir/my file name.txt "
                           "id=---\\=\\=\\=235\\=\\=\\=---";

    EXPECT_EQ(oss.str(), expected);
}