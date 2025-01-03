#include "PixSceneGame.h"
#include "../../Parts/Background/PixBackground.h"
#include "../../Character/PixCharacter.h"

namespace pix
{

	SceneGame::SceneGame(const super::InitData& init)
		: super{ init }
		, m_pBackground{ nullptr }
		, m_pCharacter{ nullptr }
	{
		setRegistTextures({
			TextureKind::BackGround_Blue,
			TextureKind::Character_MaskDude_DoubleJump,
			TextureKind::Character_MaskDude_Fall,
			TextureKind::Character_MaskDude_Hit,
			TextureKind::Character_MaskDude_Idle,
			TextureKind::Character_MaskDude_Jump,
			TextureKind::Character_MaskDude_Run,
			TextureKind::Character_MaskDude_WallJump,
			});
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
		// キャラクターの作成
		{
			m_pCharacter = std::make_unique<Character>(Character::Kind::MuskDude);
			m_pCharacter->setCenterPos(s3d::Scene::CenterF());
		}
	}

	void SceneGame::onUpdate()
	{
		if (m_pBackground)
		{
			m_pBackground->update();
		}
		if (m_pCharacter)
		{
			m_pCharacter->update();
		}
	}

	void SceneGame::onDraw() const
	{
		if (m_pBackground == nullptr
			|| m_pCharacter == nullptr)
		{
			return;
		}

		m_pBackground->draw();
		m_pCharacter->draw();
	}

}

