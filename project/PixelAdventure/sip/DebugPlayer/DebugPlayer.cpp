#ifdef _DEBUG
# include "DebugPlayer.h"

void sip::DebugPlayer::refresh()
{
	m_isStep = false;

	if (m_pauseKey.down())
	{
		m_isPause = true;
	}

	if (m_resumeKey.down())
	{
		m_isPause = false;
	}

	if (m_isPause)
	{
		if (m_transportKey.pressed())
		{
			m_isStep = true;
		}
		if (m_oneStepKey.down())
		{
			m_isStep = true;
		}
	}
}

void sip::DebugPlayer::setPauseKey(const Input& key)
{
	m_pauseKey = key;
}

void sip::DebugPlayer::setResumeKey(const Input& key)
{
	m_resumeKey = key;
}

void sip::DebugPlayer::setTransportKey(const Input& key)
{
	m_transportKey = key;
}

void sip::DebugPlayer::setOneStepKey(const Input& key)
{
	m_oneStepKey = key;
}

bool sip::DebugPlayer::isPause() const noexcept
{
	if (m_isStep)
	{
		return false;
	}
	return m_isPause;
}

#endif // _DEBUG