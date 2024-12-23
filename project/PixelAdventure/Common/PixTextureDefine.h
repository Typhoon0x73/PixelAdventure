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

		Character_MaskDude_DoubleJump,
		Character_MaskDude_Fall,
		Character_MaskDude_Hit,
		Character_MaskDude_Idle,
		Character_MaskDude_Jump,
		Character_MaskDude_Run,
		Character_MaskDude_WallJump,

		Character_Appearing,
		Character_Desappearing,

		Other_DustParticle,

		Max,

		BackGround_Begin = BackGround_Blue,
		BackGround_End = BackGround_Yellow,

		Character_MaskDude_Begin = Character_MaskDude_DoubleJump,
		Character_MaskDude_End = Character_MaskDude_WallJump,

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

		
		{ U"PIX_CHARA_MASKDUDE_DOUBLEJUMP"	, U"resources/Pixel Adventure 1/Free/Main Characters/Mask Dude/Double Jump (32x32).png"	},
		{ U"PIX_CHARA_MASKDUDE_FALL"		, U"resources/Pixel Adventure 1/Free/Main Characters/Mask Dude/Fall (32x32).png"		},
		{ U"PIX_CHARA_MASKDUDE_HIT"			, U"resources/Pixel Adventure 1/Free/Main Characters/Mask Dude/Hit (32x32).png"			},
		{ U"PIX_CHARA_MASKDUDE_IDLE"		, U"resources/Pixel Adventure 1/Free/Main Characters/Mask Dude/Idle (32x32).png"		},
		{ U"PIX_CHARA_MASKDUDE_JUMP"		, U"resources/Pixel Adventure 1/Free/Main Characters/Mask Dude/Jump (32x32).png"		},
		{ U"PIX_CHARA_MASKDUDE_RUN"			, U"resources/Pixel Adventure 1/Free/Main Characters/Mask Dude/Run (32x32).png"			},
		{ U"PIX_CHARA_MASKDUDE_WALLJUMP"	, U"resources/Pixel Adventure 1/Free/Main Characters/Mask Dude/Wall Jump (32x32).png"		},

		{ U"PIX_CHARA_APPEARING"	, U"resources/Pixel Adventure 1/Free/Main Characters/Appearing (96x96).png"		},
		{ U"PIX_CHARA_DESAPPEARING"	, U"resources/Pixel Adventure 1/Free/Main Characters/Desappearing (96x96).png"	},

		{ U"PIX_OTHER_DUSTPARTICLE"	, U"resources/Pixel Adventure 1/Free/Other/Dust Particle.png"	},

	};

}

#endif // !PIX_TEXTURE_DEFINE_H_
