#pragma once
#ifndef PIX_SCENE_SELECT_H_
#define PIX_SCENE_SELECT_H_

#include "../PixScene.h"

namespace pix
{
	class SceneSelect : public Scene
	{
		using super = Scene;

	public:

		using Scene::Scene;

		//explicit SceneSelect(const super::InitData& init);
		//virtual ~SceneSelect();

		virtual void onUpdate() override {}
		virtual void onDraw() const override {}
	};
}

#endif // !PIX_SCENE_SELECT_H_
