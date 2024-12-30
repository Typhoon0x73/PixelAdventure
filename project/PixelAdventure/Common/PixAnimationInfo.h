#pragma once
#ifndef PIX_ANIMATION_INFO_H_
#define PIX_ANIMATION_INFO_H_

#include <Siv3D.hpp>

namespace pix
{
	struct AnimationPattern
	{
		RectF srcRect;
		Duration playTime;
	};

	struct AnimationInfo
	{
		Array<AnimationPattern> patterns;
		bool isLoop;
	};
}


#endif // !PIX_ANIMATION_INFO_H_
