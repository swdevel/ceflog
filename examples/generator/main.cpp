#include <chrono>
#include <iostream>
#include <thread>

#include "CEFLog.h"

int main()
{
    using namespace std::chrono_literals;

    const uint8_t formatVersion = 0;
    const std::string deviceVendor = "Security";
    const std::string deviceProduct = "threatmanager";
    const std::string deviceVersion = "1.0";

    const CEFEventFactory factory(formatVersion, deviceVendor, deviceProduct, deviceVersion);

    const std::string deviceEventClassId = "100";
    const std::string eventName = "worm successfully stopped";
    const CEFSeverity severity = CEFSeverity::VeryHigh;

    const std::vector<CEFEventExtension> extensions = {{"src", "10.0.0.1"},
                                                       {"dst", "2.1.2.2"},
                                                       {"spt", "1232"}};

    while (true) {

        const auto event = factory.CreateEvent(deviceEventClassId,
                                               eventName,
                                               severity,
                                               extensions);

        CEFEventStringSerializer serializer;

        std::cout << serializer.Serialize(event) << '\n';

        std::this_thread::sleep_for(500ms);
    }

    return 0;
}