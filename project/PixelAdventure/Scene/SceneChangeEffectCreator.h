#pragma once
#include "sip/SceneManager/ISceneChangeEffect.h"

namespace pix::SceneChangeEffect
{
	sip::ISceneChangeEffect* Create(
		  const Texture* pFadeOutMask
		, const Texture* pFadeInMask
		, const Texture* pFade
		, bool isSkipFadeOut = false
		, float fadeTime = 1.0f
		, float softRange = 0.25f
	);
}
