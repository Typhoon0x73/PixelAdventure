#pragma once
#include "sip/StateMachine/StateMachine.h"
#include "GameAppState.h"
#include <Siv3D.hpp>

namespace pix
{
	class GameAppStateLoad : public StateBase
	{
	public:

		GameAppStateLoad();
		virtual ~GameAppStateLoad();

		virtual bool onCreate() override;
		virtual void onUpdate() override;
		virtual void onRelease() override;
		virtual Optional<GameAppState> getNextState() const override;

	private:

		Optional<AsyncTask<int32>> m_loadTask;
		int32 m_taskResult;
	};
}
