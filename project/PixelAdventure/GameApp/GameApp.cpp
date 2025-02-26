#include "GameApp.h"
#include "GameAppStateInit.h"
#include "GameAppStateLoad.h"
#include "GameAppStateIdle.h"

namespace pix
{
	GameApp::GameApp()
		: m_stateMachine{}
	{
		m_stateMachine
			.add<GameAppStateInit>(GameAppState::Init)
			.add<GameAppStateLoad>(GameAppState::Load)
			.add<GameAppStateIdle>(GameAppState::Idle)
			.change(GameAppState::Init);
	}

	GameApp::~GameApp()
	{
	}

	void GameApp::update()
	{
		m_stateMachine.update();
	}


}
