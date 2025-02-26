#pragma once
#include <Siv3D.hpp>

namespace pix::asset::define
{
	enum class TextureKind : size_t
	{
		RuleMask1,
		RuleMask2,
		Fade1,

		Background_Blue,
		Background_Brown,
		Background_Gray,
		Background_Green,
		Background_Pink,
		Background_Purple,
		Background_Yellow,

		Count,

		Background_Begin = Background_Blue,
	};

	constexpr const char32_t* TextureAssetNames[] =
	{
		U"rule_mask1",
		U"rule_mask2",
		U"fade1",
		U"background_blue",
		U"background_brown",
		U"background_gray",
		U"background_green",
		U"background_pink",
		U"background_purple",
		U"background_yellow",
	};
}
