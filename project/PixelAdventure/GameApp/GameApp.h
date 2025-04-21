#pragma once
#include "sip/StateMachine/StateMachine.h"
#include "GameAppState.h"

namespace pix
{

	class GameApp
	{
	public:

		GameApp();
		virtual ~GameApp();

		virtual void update();


	private:

		sip::StateMachine<GameAppState, GameAppData> m_stateMachine;
	};
}
