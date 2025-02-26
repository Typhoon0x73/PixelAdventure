#ifndef SIP_COMMON_H_
#define SIP_COMMON_H_

#ifdef _DEBUG
#define SIP_DEBUG_BREAK(b) if (!!!(b)) __debugbreak()
#else
#define SIP_DEBUG_BREAK(b) ((void)0)
#endif // _DEBUG


namespace sip
{
}

#endif //! SIP_COMMON_H_