#ifndef SIP_LOCATOR_H_
#define SIP_LOCATOR_H_
#pragma once

namespace sip
{
    template<class T>
    class Locator
    {
    public:
        Locator() = default;
        virtual ~Locator() = default;
        
        virtual void set(T* pInstance) { m_pInstance = pInstance; }
        virtual T* get() { return m_pInstance; }
        virtual const T* get() const { return m_pInstance; }

    private:
        T* m_pInstance{ nullptr };

    };

}

#endif //! SIP_LOCATOR_H_