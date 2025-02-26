#include "GameAppStateIdle.h"
#include "Common/PixCommon.h"
#include "Common/AssetTextureDefine.h"
#include "Scene/Title/SceneTitle.h"
#include "Scene/SceneChangeEffectCreator.h"

namespace pix
{
	GameAppStateIdle::GameAppStateIdle()
		: m_sceneManager{}
	{
		SceneChangerLocator::getInstance().set(&m_sceneManager);
	}

	GameAppStateIdle::~GameAppStateIdle()
	{
	}

	bool GameAppStateIdle::onCreate()
	{
		const auto* pAssetLocator = AssetLocator::getInstance().get();
		if (pAssetLocator == nullptr)
		{
			return false;
		}
		const auto* pTextureTable = pAssetLocator->getTable<Texture>();

		using asset::define::TextureKind;
		using asset::define::TextureAssetNames;

		m_sceneManager
			.add<SceneTitle>(sip::SceneKey::Title)
			.change(
				sip::SceneKey::Title
				, SceneChangeEffect::Create(
					nullptr
					, pTextureTable->getData(TextureAssetNames[FromEnum(TextureKind::RuleMask2)])
					, pTextureTable->getData(TextureAssetNames[FromEnum(TextureKind::Fade1)])
					, true
				)
			);
		return true;
	}

	void GameAppStateIdle::onUpdate()
	{
		m_sceneManager.update();
	}

	void GameAppStateIdle::onRelease()
	{
	}

	Optional<GameAppState> GameAppStateIdle::getNextState() const
	{
		return none;
	}

}
