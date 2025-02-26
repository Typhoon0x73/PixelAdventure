#pragma once
#include "sip/StateMachine/StateMachine.h"
#include "GameAppState.h"

namespace pix
{
	class GameAppStateInit : public sip::IState<GameAppState>
	{
	public:

		GameAppStateInit();
		virtual ~GameAppStateInit();

		virtual bool onCreate() override;
		virtual void onUpdate() override;
		virtual void onRelease() override;
		virtual Optional<GameAppState> getNextState() const override;

	private:
	};
}
