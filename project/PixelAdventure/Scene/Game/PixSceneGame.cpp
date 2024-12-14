#include "PixSceneGame.h"
#include "../../Parts/Background/PixBackground.h"

namespace pix
{

	SceneGame::SceneGame(const super::InitData& init)
		: super{ init }
		, m_pBackground{ nullptr }
	{
		setRegistTextures({ TextureKind::BackGround_Blue });
	}

	SceneGame::~SceneGame()
	{
	}

	bool SceneGame::onFadeOut()
	{

		if (m_pBackground)
		{
			m_pBackground->update();
		}

		return super::onFadeOut();
	}

	void SceneGame::onLoadEnd()
	{
		// 背景の作成
		{
			m_pBackground = std::make_unique<Background>(Background::Kind::Blue);
			m_pBackground->setSpeed(0.2f);
		}
	}

	void SceneGame::onUpdate()
	{
		if (m_pBackground)
		{
			m_pBackground->update();
		}

	}

	void SceneGame::onDraw() const
	{
		if (m_pBackground == nullptr)
		{
			return;
		}

		m_pBackground->draw();
	}

}

