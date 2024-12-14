#pragma once
#ifndef PIX_SCENE_TITLE_H_
#define PIX_SCENE_TITLE_H_

#include "../PixScene.h"

namespace pix
{
	class SceneTitle : public Scene
	{
		using super = Scene;

	public:

		explicit SceneTitle(const super::InitData& init);
		virtual ~SceneTitle();

		virtual void onUpdate() override;
		virtual void onDraw() const override;
	};
}

#endif // !PIX_SCENE_TITLE_H_
