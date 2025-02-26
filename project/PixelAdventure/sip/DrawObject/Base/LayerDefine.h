#ifndef SIP_LAYER_DEFINE_H_
#define SIP_LAYER_DEFINE_H_
#pragma once

// INCLUDE
#include <cstddef>

namespace sip::define
{
	enum class Layer : std::size_t
	{
		Background = 0,
		Main,
		UI,
		Fade,
		Front,

		Count, //!< 最大数
		Default = Main,
	};
}

#endif // !SIP_LAYER_DEFINE_H_
