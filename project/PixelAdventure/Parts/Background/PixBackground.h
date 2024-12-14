#pragma once
#ifndef PIX_BACKGROUND_H_
#define PIX_BACKGROUND_H_

#include "../../Common/PixCommon.h"

namespace pix
{
	class Background
	{
	public:

		enum class Kind : size_t
		{
			Invalid = -1,

			Blue = 0,
			Brown,
			Gray,
			Green,
			Pink,
			Purple,
			Yellow,
		};

		Background();
		Background(Kind kind);
		virtual ~Background();

		virtual void update();
		virtual void draw() const;

		virtual void changeKind(Kind kind);
		virtual void setSpeed(float speed);

	protected:

		Kind m_kind;

		float m_timer;
		float m_speed;

		Optional<Texture> m_texture;
	};
}


#endif // !PIX_BACKGROUND_H_
