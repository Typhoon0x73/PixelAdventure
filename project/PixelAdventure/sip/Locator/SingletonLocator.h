#ifndef SIP_SINGLETON_LOCATOR_H_
#define SIP_SINGLETON_LOCATOR_H_
#pragma once
#include "../Common/Singleton.h"
#include "Locator.h"

namespace sip
{
    template<class T>
    class SingletonLocator : public Singleton<Locator<T>>
    {
        friend class Singleton<Locator<T>>;
    };
    
}

#endif //! SIP_SINGLETON_LOCATOR_H_