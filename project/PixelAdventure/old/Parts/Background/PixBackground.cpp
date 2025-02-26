#include "PixBackground.h"
#include "../../Common/PixTextureDefine.h"

namespace pix
{

	Background::Background()
		: m_kind{ Kind::Invalid }
		, m_timer{ 0.0f }
		, m_speed{ 0.0f }
		, m_texture{ none }
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
		if (not m_texture.has_value())
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
		if (not m_texture.has_value())
		{
			return;
		}

		const ScopedRenderStates2D renderState{ SamplerState::RepeatLinear };


		const Size& sceneSize = s3d::Scene::Size();
		const Size& textureSize = m_texture->size();

		TextureRegion{
			*m_texture,
			0.0f, m_timer,
			static_cast<float>(sceneSize.x) / textureSize.x,
			m_timer - static_cast<float>(sceneSize.y) / textureSize.y,
			static_cast<double>(sceneSize.x), static_cast<double>(sceneSize.y)
		}.draw(Vec2::Zero());
	}

	void Background::changeKind(Kind kind)
	{
		m_kind = kind;
		size_t index = FromEnum(TextureKind::BackGround_Begin) + FromEnum(m_kind);

		if (std::size(TextureFileInfos) <= index)
		{
			PIX_ASSERT(false);
			return;
		}

		const auto& assetKey = TextureFileInfos[index].assetKey;
		if (not TextureAsset::IsReady(assetKey))
		{
			PIX_ASSERT(false);
			return;
		}

		m_texture = TextureAsset(assetKey);
	}

	void Background::setSpeed(float speed)
	{
		m_speed = speed;
	}

}
