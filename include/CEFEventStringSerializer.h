#pragma once

#include "CEFEventAbstractSerializer.h"

namespace ceflog::event
{

class CEFEventStringSerializer : protected CEFEventAbstractSerializer<std::string>
{
public:
    virtual std::string Serialize(const CEFEvent& event) const override;
};

} // namespace ceflog::event