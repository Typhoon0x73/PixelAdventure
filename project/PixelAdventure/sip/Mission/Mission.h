#ifndef SIP_MISSION_H_
#define SIP_MISSION_H_
#pragma once

// INCLUDE
#include <memory>
#include "IMission.h"
#include "IMissionFlag.h"

namespace sip
{
    class Mission : public IMission
    {
    public:
        Mission() = default;
        virtual ~Mission() = default;

        virtual bool isSucceeded() const override;
        virtual bool isFailed() const override;

    protected:
        std::unique_ptr<IMissionFlag> m_pSucceededFlag{ nullptr };
        std::unique_ptr<IMissionFlag> m_pFailedFlag{ nullptr };
    
    };
}

#endif //! SIP_MISSION_H_