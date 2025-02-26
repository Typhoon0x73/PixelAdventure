#ifndef SIP_IMISSION_FLAG_H_
#define SIP_IMISSION_FLAG_H_
#pragma once

namespace sip
{
    class IMissionFlag
    {
    public:
        virtual ~IMissionFlag() = default;
        
        virtual bool isValid() const = 0;
    };
}


#endif //! SIP_IMISSION_FLAG_H_