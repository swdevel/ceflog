#include <sstream>

#include "CEFEventStringSerializer.h"

namespace ceflog::event
{

std::string CEFEventStringSerializer::Serialize(const CEFEvent& event) const
{
    std::ostringstream oss;
    oss << event;

    return oss.str();
}

} // namespace ceflog::event