#include "Background.h"
#include "Common/PixCommon.h"
#include "Common/AssetTextureDefine.h"

namespace pix
{

	Background::Background()
		: super{ sip::define::Layer::Background }
		, m_kind{ Kind::Invalid }
		, m_timer{ 0.0f }
		, m_speed{ 0.0f }
		, m_pTexture{ nullptr }
	{
	}

	Background::Background(Kind kind)
		: Background{}
	{
		changeKind(kind);
	}

	Background::~Background()
	{
	}

	void Background::update()
	{
		if (m_pTexture == nullptr)
		{
			return;
		}
		m_timer += m_speed * static_cast<float>(Scene::DeltaTime());

		if (1.0f <= m_timer)
		{
			m_timer -= 1.0f;
		}
	}

	void Background::draw() const
	{
		if (m_pTexture == nullptr)
		{
			return;
		}

		const ScopedRenderStates2D renderState{ SamplerState::RepeatLinear };


		const Size& sceneSize = s3d::Scene::Size();
		const Size& textureSize = m_pTexture->size();

		TextureRegion{
			*m_pTexture,
			0.0f, m_timer,
			static_cast<float>(sceneSize.x) / textureSize.x,
			m_timer - static_cast<float>(sceneSize.y) / textureSize.y,
			static_cast<double>(sceneSize.x), static_cast<double>(sceneSize.y)
		}.draw(Vec2::Zero());
	}

	void Background::changeKind(Kind kind)
	{
		m_kind = kind;
		size_t index = FromEnum(asset::define::TextureKind::Background_Begin) + FromEnum(m_kind);

		if (std::size(asset::define::TextureAssetNames) <= index)
		{
			SIP_DEBUG_BREAK(false);
			return;
		}

		const auto* pAssetLocator = AssetLocator::getInstance().get();
		if (pAssetLocator == nullptr)
		{
			SIP_DEBUG_BREAK(false);
			return;
		}

		const auto* pTextureTable = pAssetLocator->getTable<Texture>();
		if (pTextureTable == nullptr)
		{
			SIP_DEBUG_BREAK(false);
			return;
		}

		const auto& assetKey = asset::define::TextureAssetNames[index];
		if (not pTextureTable->isReady(assetKey))
		{
			SIP_DEBUG_BREAK(false);
			return;
		}

		m_pTexture = pTextureTable->getData(assetKey);
	}

	void Background::setSpeed(float speed)
	{
		m_speed = speed;
	}

}
