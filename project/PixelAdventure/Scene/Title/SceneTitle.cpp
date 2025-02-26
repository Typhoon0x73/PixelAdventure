#include "SceneTitle.h"
#include "Common/PixCommon.h"
#include "Parts/Background/Background.h"

namespace pix
{
	SceneTitle::SceneTitle()
		: m_pSceneChanger{ SceneChangerLocator::getInstance().get() }
		, m_pBackground{ nullptr }
	{
		//const auto* pTitleLayout = AssetLocator::getInstance().get()->getTable<sip::layout::Data>()->getData(U"SceneTitle");
	}

	SceneTitle::~SceneTitle()
	{
	}

	void SceneTitle::init()
	{
		m_pBackground = std::make_unique<Background>(Background::Kind::Brown);
		m_pBackground->setSpeed(0.2f);
	}

	void SceneTitle::update()
	{
		if (m_pBackground)
		{
			m_pBackground->update();
		}
	}

	void SceneTitle::release()
	{
	}

	bool SceneTitle::isFadeInEnable() const
	{
		return true;
	}

}
