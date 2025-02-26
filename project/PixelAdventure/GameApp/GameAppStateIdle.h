#pragma once
#include "sip/StateMachine/StateMachine.h"
#include "sip/SceneManager/SceneManager.h"
#include "GameAppState.h"

namespace pix
{
	class GameAppStateIdle : public sip::IState<GameAppState>
	{
	public:

		GameAppStateIdle();
		virtual ~GameAppStateIdle();

		virtual bool onCreate() override;
		virtual void onUpdate() override;
		virtual void onRelease() override;
		virtual Optional<GameAppState> getNextState() const override;

	private:

		sip::SceneManager m_sceneManager;
	};
}
