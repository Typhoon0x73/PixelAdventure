#pragma once
#ifndef PIX_CHARACTER_H_
#define PIX_CHARACTER_H_

#include "../Common/PixCommon.h"
#include "../Common/PixAnimationInfo.h"

namespace pix
{
	class Character
	{
	public:

		enum class Kind : size_t
		{
			MuskDude,
			NinjaFrog,
			PinkMan,
			VirtualGuy,
		};

		enum class State : size_t
		{
			DoubleJump,
			Fall,
			Hit,
			Idle,
			Jump,
			Run,
			WallJump,
			Appearing,
			Desappearing,
		};

	public:

		Character(Kind kind);
		virtual ~Character();

		virtual void update();
		virtual void draw() const;

		virtual const RectF getHitRect() const;

	protected:

		virtual void changeState(State state);

	protected:

		State m_state;

		Texture m_dustParticleTexture;

		int32 m_animPatternIndex;
		double m_animTimer;

		Vec2 m_centerPos;
		Vec2 m_move;



	};
}

#endif // !PIX_CHARACTER_H_
