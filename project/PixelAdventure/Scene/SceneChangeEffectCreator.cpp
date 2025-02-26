#include "SceneChangeEffectCreator.h"
#include "sip/SceneChangeEffect/SceneChangeEffectFade.h"

namespace pix
{
	sip::ISceneChangeEffect* pix::SceneChangeEffect::Create(
		const Texture* pFadeOutMask
		, const Texture* pFadeInMask
		, const Texture* pFade
		, bool isSkipFadeOut
		, float fadeTime
		, float softRange)
	{
		return new sip::SceneChangeEffectFade(
			pFadeOutMask,
			pFadeInMask,
			pFade,
			U"rule_fade",
			isSkipFadeOut,
			fadeTime,
			softRange
		);
	}

}
