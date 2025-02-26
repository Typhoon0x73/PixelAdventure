#include "DrawTextureParts.h"
#include "../DebugLog/DebugLog.h"

namespace sip
{

	DrawTextureParts::DrawTextureParts(define::Layer layer, const Texture* pTexture)
		: super{ layer }
		, m_pTexture{ pTexture }
		, m_srcRect{ RectF::Empty() }
	{
		if (m_pTexture)
		{
			m_srcRect.x = 0.0;
			m_srcRect.y = 0.0;
			m_srcRect.w = static_cast<double>(m_pTexture->width());
			m_srcRect.h = static_cast<double>(m_pTexture->height());
		}
	}

	DrawTextureParts::~DrawTextureParts()
	{
	}

	void DrawTextureParts::draw() const
	{
		if (not m_pTexture)
		{
			DebugLog::Print(DebugLog::LogType::Warning, U"{}: texture isNull."_fmt(m_name.getName()));
			return;
		}

		if (m_srcRect.isEmpty())
		{
			DebugLog::Print(DebugLog::LogType::Warning, U"{}: srcRect isEmpty."_fmt(m_name.getName()));
			return;
		}

		(*m_pTexture)(m_srcRect)
			.scaled(getWorldScale())
			.rotated(getWorldRotateZ())
			.drawAt(getWorldPosition());
	}

	void DrawTextureParts::setTexture(const Texture* pTexture)
	{
		m_pTexture = pTexture;
	}

	void DrawTextureParts::setSrcRect(const RectF& srcRect)
	{
		m_srcRect = srcRect;
	}

}
