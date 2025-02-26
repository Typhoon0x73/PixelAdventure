#pragma once
#include "sip/DrawObject/Base/DrawObject.h"

namespace pix
{
	class Background : public sip::DrawObject
	{
		using super = sip::DrawObject;
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
		virtual void draw() const override;

		virtual void changeKind(Kind kind);
		virtual void setSpeed(float speed);

	protected:

		Kind m_kind;

		float m_timer;
		float m_speed;

		const Texture* m_pTexture;
	};
}
