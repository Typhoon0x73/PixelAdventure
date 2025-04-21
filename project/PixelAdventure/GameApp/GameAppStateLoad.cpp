#include "GameAppStateLoad.h"
#include "Common/PixCommon.h"
#include "Common/AssetTextureDefine.h"
#include "Common/AssetLayoutDefine.h"

namespace pix
{

	namespace
	{
		int32 LoadFunc()
		{
			auto* pAssetLocator = AssetLocator::getInstance().get();
			if (auto* pTable = pAssetLocator->getTable<Texture>())
			{
				for (const auto& it : asset::define::TextureAssetNames)
				{
					if (!pTable->load(it))
					{
						return -1;
					}
				}
			}
			if (auto* pTable = pAssetLocator->getTable<sip::layout::Data>())
			{
				for (const auto& it : asset::define::LayoutFileInfos)
				{
					if (!pTable->load(it.key))
					{
						return -1;
					}
				}
			}

			return 0;
		}
	}


	GameAppStateLoad::GameAppStateLoad()
		: m_loadTask{ none }
		, m_taskResult{ -1 }
	{
	}

	GameAppStateLoad::~GameAppStateLoad()
	{
	}

	bool GameAppStateLoad::onCreate()
	{
		auto* pAssetLocator = AssetLocator::getInstance().get();
		if (pAssetLocator == nullptr)
		{
			return false;
		}

		using asset::define::TextureKind;
		using asset::define::TextureAssetNames;
		auto* pTextureTable = pAssetLocator->getTable<Texture>();
		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::RuleMask1)], U"resources/rule_pattern/rule800/1.png");
		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::RuleMask2)], U"resources/rule_pattern/rule800/2.png");
		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::Fade1)], U"resources/Pixel Adventure 1/Free/Hello.png"); // 仮

		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::Background_Blue)], U"resources/Pixel Adventure 1/Free/Background/Blue.png");
		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::Background_Brown)], U"resources/Pixel Adventure 1/Free/Background/Brown.png");
		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::Background_Gray)], U"resources/Pixel Adventure 1/Free/Background/Gray.png");
		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::Background_Green)], U"resources/Pixel Adventure 1/Free/Background/Green.png");
		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::Background_Pink)], U"resources/Pixel Adventure 1/Free/Background/Pink.png");
		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::Background_Purple)], U"resources/Pixel Adventure 1/Free/Background/Purple.png");
		pTextureTable->add(TextureAssetNames[FromEnum(TextureKind::Background_Yellow)], U"resources/Pixel Adventure 1/Free/Background/Yellow.png");

		using asset::define::LayoutFileInfos;
		auto* pLayoutTable = pAssetLocator->getTable<sip::layout::Data>();
		for (const auto& it : LayoutFileInfos)
		{
			pLayoutTable->add(it.key, it.path);
		}

		m_loadTask = Async(LoadFunc);
        
        // MAC側でうまく動かなかったのでMainと同じスレッドで読み込み。
        auto ps = HLSL{ U"resources/shader/rule_fade.hlsl", U"PS" }
        | GLSL{ U"resources/shader/rule_fade.frag", {{ U"PSConstants2D", 0 }, { U"RuleFade", 1 } } };
        PixelShaderAsset::Register(U"rule_fade", ps);
        if (!PixelShaderAsset::Load(U"rule_fade"))
        {
            return false;
        }
		return true;
	}

	void GameAppStateLoad::onUpdate()
	{
		if (!m_loadTask.has_value())
		{
			return;
		}
		if (!m_loadTask->isReady())
		{
			return;
		}
		m_taskResult = m_loadTask->get();
		if (m_taskResult < 0)
		{
			SIP_DEBUG_BREAK(false);
		}
		m_loadTask.reset();
	}

	void GameAppStateLoad::onRelease()
	{
	}

	Optional<GameAppState> GameAppStateLoad::getNextState() const
	{
		if (m_loadTask.has_value())
		{
			return none;
		}
		return GameAppState::Idle;
	}

}
