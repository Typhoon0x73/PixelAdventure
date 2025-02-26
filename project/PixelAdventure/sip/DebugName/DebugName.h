#ifndef SIP_DEBUG_NAME_H_
#define SIP_DEBUG_NAME_H_
#pragma once

// INCLUDE
#include <Siv3D.hpp>

namespace sip
{
	class DebugName
	{
	public:

		DebugName(StringView name);
		virtual ~DebugName();

		void setName(StringView name);
		StringView getName() const;

	private:
#ifdef _DEBUG
		String m_name;
#endif // _DEBUG
	};
}

#endif // !SIP_DEBU_GNAME_H_
