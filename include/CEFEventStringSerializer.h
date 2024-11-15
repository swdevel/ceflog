#pragma once

#include "CEFEventAbstractSerializer.h"

class CEFEventStringSerializer : protected CEFEventAbstractSerializer<std::string>
{
public:
    virtual std::string Serialize(const CEFEvent& event) const override;
};