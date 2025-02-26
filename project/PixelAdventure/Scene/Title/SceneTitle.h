#pragma once
#include "sip/SceneManager/IScene.h"
#include "sip/SceneManager/ISceneChanger.h"
#include <memory>

namespace pix
{
	class Background;
	class SceneTitle : public sip::IScene
	{
	public:

		SceneTitle();
		virtual ~SceneTitle();

		/**
		* @brief シーンを初期化する
		*/
		virtual void init() override;

		/**
		* @brief シーンを更新する
		*/
		virtual void update() override;

		/**
		* @brief シーンを解放する
		*/
		virtual void release() override;

		/**
		* @brief フェードイン可能な状態かを返す
		*/
		virtual bool isFadeInEnable() const override;


	protected:

		sip::ISceneChanger* m_pSceneChanger;
		std::unique_ptr<Background> m_pBackground;

	};
}
