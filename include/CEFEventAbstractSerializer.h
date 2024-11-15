#pragma once

#include "CEFEvent.h"

template <typename T>
class CEFEventAbstractSerializer
{
protected:
    virtual T Serialize(const CEFEvent& event) const = 0;
};