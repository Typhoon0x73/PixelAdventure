#include "DrawScissorRect.h"

namespace sip
{

	DrawScissorRect::DrawScissorRect(define::Layer layer)
		: super{ layer }
		, m_scissorRect{ Rect::Empty() }
	{
	}

	DrawScissorRect::~DrawScissorRect()
	{
	}

	void DrawScissorRect::draw() const
	{
		Graphics2D::SetScissorRect(m_scissorRect);
	}

	void DrawScissorRect::setRect(const Rect& scissorRect)
	{
		m_scissorRect = scissorRect;
	}

	void DrawScissorRect::fill()
	{
		m_scissorRect = Rect{ 0, 0, Scene::Size() };
	}

}
