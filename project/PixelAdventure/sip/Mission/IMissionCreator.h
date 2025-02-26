#ifndef SIP_IMISSION_CREATOR_H_
#define SIP_IMISSION_CREATOR_H_
#pragma once

namespace sip
{
    class IMission;
    class IMissionCreator
    {
    public:
        virtual ~IMissionCreator() = default;
        virtual IMission* create() = 0;
    };
}

#endif //! SIP_IMISSION_CREATOR_H_