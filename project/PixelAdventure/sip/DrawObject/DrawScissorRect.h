#ifndef SIP_DRAW_SCISSIR_RECT_H_
#define SIP_DRAW_SCISSIR_RECT_H_
#pragma once

// INCLUDE
#include "Base/DrawObject.h"

namespace sip
{
	class DrawScissorRect : public DrawObject
	{
		using super = DrawObject;
	public:

		DrawScissorRect(define::Layer layer);
		virtual ~DrawScissorRect();

		virtual void draw() const override;

		virtual void setRect(const Rect& scissorRect);

		virtual void fill();

	protected:

		Rect m_scissorRect;
	};

}
#endif // !SIP_DRAW_SCISSIR_RECT_H_
