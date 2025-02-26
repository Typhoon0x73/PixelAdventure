#include "Mission.h"

namespace sip
{
    bool Mission::isSucceeded() const
    {
        if (m_pSucceededFlag == nullptr)
        {
            return false;
        }
        return m_pSucceededFlag->isValid();
    }

    bool Mission::isFailed() const
    {
        if (m_pFailedFlag == nullptr)
        {
            return false;
        }
        return m_pFailedFlag->isValid();
    }

}