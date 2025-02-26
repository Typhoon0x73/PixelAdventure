#pragma once
#include "sip/Common/Common.h"
#include "sip/Locator/SingletonLocator.h"
#include "sip/AssetAccessor/AssetAccessor.hpp"
#include "sip/DrawObject/Base/DrawObjectManager.h"
#include "sip/LayoutData/LayoutData.h"
#include "sip/SceneManager/ISceneChanger.h"

namespace pix
{
	using AssetsAccessor = sip::AssetAccessor<
		Texture, Font, Audio, sip::layout::Data
	>;

	using AssetLocator = sip::SingletonLocator<AssetsAccessor>;
	using SceneChangerLocator = sip::SingletonLocator<sip::ISceneChanger>;
}
