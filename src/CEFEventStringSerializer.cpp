#include <sstream>

#include "CEFEventStringSerializer.h"

std::string CEFEventStringSerializer::Serialize(const CEFEvent& event) const
{
    std::ostringstream oss;
    oss << event;

    return oss.str();
}