#pragma once
#ifndef PIX_TEXTURE_DEFINE_H_
#define PIX_TEXTURE_DEFINE_H_

#include <Siv3D.hpp>

namespace pix
{

	enum class TextureKind : size_t
	{
		BackGround_Blue,
		BackGround_Brown,
		BackGround_Gray,
		BackGround_Green,
		BackGround_Pink,
		BackGround_Purple,
		BackGround_Yellow,

		Max,

		BackGround_Begin = BackGround_Blue,
		BackGround_End = BackGround_Yellow,

	};

	struct AssetInfo
	{
		const char32_t* assetKey;
		const char32_t* fileName;
	};

	constexpr AssetInfo TextureFileInfos[] = {
		{ U"PIX_BG_BLUE"	, U"resources/Pixel Adventure 1/Free/Background/Blue.png"	},
		{ U"PIX_BG_BROWN"	, U"resources/Pixel Adventure 1/Free/Background/Brown.png"	},
		{ U"PIX_BG_GRAY"	, U"resources/Pixel Adventure 1/Free/Background/Gray.png"	},
		{ U"PIX_BG_GREEN"	, U"resources/Pixel Adventure 1/Free/Background/Green.png"	},
		{ U"PIX_BG_PINK"	, U"resources/Pixel Adventure 1/Free/Background/Pink.png"	},
		{ U"PIX_BG_PURPLE"	, U"resources/Pixel Adventure 1/Free/Background/Purple.png"	},
		{ U"PIX_BG_YELLOW"	, U"resources/Pixel Adventure 1/Free/Background/Yellow.png"	},

	};

}

#endif // !PIX_TEXTURE_DEFINE_H_
