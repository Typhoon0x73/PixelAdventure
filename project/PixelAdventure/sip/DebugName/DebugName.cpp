#include "DebugName.h"

namespace sip
{

	DebugName::DebugName(StringView name)
#ifdef _DEBUG
		: m_name{ name }
#endif // _DEBUG
	{
	}

	DebugName::~DebugName()
	{
	}

	void DebugName::setName(StringView name)
	{
#ifdef _DEBUG
		m_name = name;
#endif // _DEBUG
	}

	StringView DebugName::getName() const
	{
#ifdef _DEBUG
		return m_name;
#else // _DEBUG
		return U"";
#endif // _DEBUG
	}

}
