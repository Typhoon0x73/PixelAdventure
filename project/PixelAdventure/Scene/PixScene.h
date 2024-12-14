#pragma once
#ifndef PIX_SCENE_H_
#define PIX_SCENE_H_

#include "../Common/PixCommon.h"
#include "../Common/PixTextureDefine.h"
#include <bitset>

namespace pix
{
	class Scene : public SceneManager::Scene
	{
		using super = SceneManager::Scene;

	private:

		enum class State
		{
			LoadRegist,
			LoadWait,

			FadeOut,

			Idle,
		};

	public:

		explicit Scene(const super::InitData& init);
		virtual ~Scene();

		virtual void update() override;

		virtual void draw() const override;

	protected:

		virtual void onUpdate() = 0;
		virtual void onDraw() const = 0;

		virtual void onLoadRegist();
		/// @brief 読み込み待機中の処理
		/// @return trueを返すと読み込み完了
		virtual bool onLoadWait();
		virtual void onLoadEnd() {}

		/// @brief フェードアウトの処理
		/// @return trueでフェードアウト終了
		virtual bool onFadeOut();

		virtual void onLoadDraw() const;
		virtual void onFadeOutDraw() const;

		virtual void setBackgroundColor(ColorF backgroundColor);
		virtual void setFadeTime(Duration fadeTime);

		virtual void setRegistTextures(const Array<TextureKind>& textureKinds);

	private:

		void release();

	private:

		State m_state;

		double m_fadeTimer;
		Duration m_fadeTime;

		ColorF m_backgroundColor;

		Array<TextureKind> m_textureKinds;

	};
}

#endif // !PIX_SCENE_H_
