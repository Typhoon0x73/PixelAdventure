#pragma once
#ifndef PIX_SCENE_GAME_H_
#define PIX_SCENE_GAME_H_

#include "../PixScene.h"

namespace pix
{
	class Background;
	class Character;

	class SceneGame : public Scene
	{
		using super = Scene;

	public:

		explicit SceneGame(const super::InitData& init);
		virtual ~SceneGame();

		virtual bool onFadeOut() override;
		virtual void onLoadEnd() override;

		virtual void onUpdate() override;
		virtual void onDraw() const override;

	protected:

		std::unique_ptr<Background> m_pBackground;
		std::unique_ptr<Character> m_pCharacter;
	};
}

#endif // !PIX_SCENE_GAME_H_
