#ifndef SIP_DRAW_TEXTURE_PARTS_H_
#define SIP_DRAW_TEXTURE_PARTS_H_
#pragma once

// INCLUDE
#include "Base/DrawObject.h"

namespace sip
{
	class DrawTextureParts : public DrawObject
	{
		using super = DrawObject;
	public:

		DrawTextureParts(define::Layer layer, const Texture* pTexture);
		virtual ~DrawTextureParts();

		virtual void draw() const override;

		virtual void setTexture(const Texture* pTexture);

		virtual void setSrcRect(const RectF& srcRect);

	protected:

		const Texture* m_pTexture;
		RectF m_srcRect;
	};
}

#endif // !SIP_DRAW_TEXTURE_PARTS_H_
