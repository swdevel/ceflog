#pragma once

#include "CEFEvent.h"

namespace ceflog::event
{

template <typename T>
class CEFEventAbstractSerializer
{
protected:
    virtual T Serialize(const CEFEvent& event) const = 0;

    virtual ~CEFEventAbstractSerializer() = default;
};

} // namespace ceflog::event