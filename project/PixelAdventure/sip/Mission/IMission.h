#ifndef SIP_IMISSION_H_
#define SIP_IMISSION_H_
#pragma once

namespace sip
{
    class IMission
    {
    public:
        virtual ~IMission() = default;

        virtual bool isSucceeded() const = 0;
        virtual bool isFailed() const = 0;
    };

}

#endif //! SIP_IMISSION_H_