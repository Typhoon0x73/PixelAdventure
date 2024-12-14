#include "PixScene.h"

namespace pix
{

	Scene::Scene(const super::InitData& init)
		: super{ init }
		, m_state{ State::LoadRegist }
		, m_fadeTimer{ 0.0 }
		, m_fadeTime{ 0.5s }
		, m_backgroundColor{ Palette::Black }
		, m_textureKinds{}
	{
	}

	Scene::~Scene()
	{
		release();
		Logger << U"Scene::DESTRUCTOR";
	}

	void Scene::update()
	{
		switch (m_state)
		{
		case pix::Scene::State::LoadRegist:
		{
			onLoadRegist();
			m_state = State::LoadWait;
			Logger << U"Scene::LoadRegisted";
		}
		[[fallthrough]];

		case pix::Scene::State::LoadWait:
		{
			if (not onLoadWait())
			{
				break;
			}
			onLoadEnd();
			m_state = State::FadeOut;
			Logger << U"Scene::LoadCompleted";
		}
		[[fallthrough]];

		case pix::Scene::State::FadeOut:
		{
			if (not onFadeOut())
			{
				break;
			}
			m_state = State::Idle;
			Logger << U"Scene::FadeOuted";
		}
		[[fallthrough]];

		case pix::Scene::State::Idle:
		{
			onUpdate();
			break;
		}

		default:
			PIX_ASSERT(false);
			break;
		}
	}

	void Scene::draw() const
	{
		switch (m_state)
		{
		case pix::Scene::State::LoadRegist:
		case pix::Scene::State::LoadWait:
		{
			onLoadDraw();
			break;
		}

		case pix::Scene::State::FadeOut:
		{
			onDraw();
			onFadeOutDraw();
			break;
		}

		case pix::Scene::State::Idle:
		{
			onDraw();
			break;
		}

		default:
			break;
		}
	}

	void Scene::onLoadRegist()
	{
		for (const auto& kind : m_textureKinds)
		{
			TextureAsset::LoadAsync(TextureFileInfos[FromEnum(kind)].assetKey);
		}
	}

	bool Scene::onLoadWait()
	{
		for (const auto& kind : m_textureKinds)
		{
			if (not TextureAsset::IsReady(TextureFileInfos[FromEnum(kind)].assetKey))
			{
				return false;
			}
		}
		return true;
	}

	bool Scene::onFadeOut()
	{
		m_fadeTimer += s3d::Scene::DeltaTime();
		double alpha = m_fadeTimer / m_fadeTime.count();

		return (1.0 <= alpha);
	}

	void Scene::onLoadDraw() const
	{
		Rect{ Point::Zero(), s3d::Scene::Size() }
			.draw(m_backgroundColor);
	}

	void Scene::onFadeOutDraw() const
	{
		double alpha = 1.0 - (m_fadeTimer / m_fadeTime.count());
		alpha = Clamp(alpha, 0.0, 1.0);

		Rect{ Point::Zero(), s3d::Scene::Size() }
			.draw(m_backgroundColor.withAlpha(alpha));
	}

	void Scene::setBackgroundColor(ColorF backgroundColor)
	{
		m_backgroundColor = backgroundColor;
	}

	void Scene::setFadeTime(Duration fadeTime)
	{
		m_fadeTime = fadeTime;
	}

	void Scene::setRegistTextures(const Array<TextureKind>& textureKinds)
	{
		m_textureKinds.clear();
		m_textureKinds = textureKinds;
	}

	void Scene::release()
	{
		for (const auto& kind : m_textureKinds)
		{
			TextureAsset::Release(TextureFileInfos[FromEnum(kind)].assetKey);
		}
	}

}
