#include "CEFEventFactory.h"

namespace ceflog::event
{

CEFEvent CEFEventFactory::CreateEvent(const std::string& deviceEventClassId,
                                      const std::string& name,
                                      const CEFSeverity severity,
                                      const std::vector<CEFEventExtension>& extensions) const noexcept
{
    return CEFEvent(formatVersion,
                    deviceVendor,
                    deviceProduct,
                    deviceVersion,
                    deviceEventClassId,
                    name,
                    severity,
                    extensions);
}

} // namespace ceflog::event