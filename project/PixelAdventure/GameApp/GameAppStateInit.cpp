#include "GameAppStateInit.h"

namespace pix
{
	GameAppStateInit::GameAppStateInit()
	{
	}

	GameAppStateInit::~GameAppStateInit()
	{
	}

	bool GameAppStateInit::onCreate()
	{
		return true;
	}

	void GameAppStateInit::onUpdate()
	{
	}

	void GameAppStateInit::onRelease()
	{
	}

	Optional<GameAppState> GameAppStateInit::getNextState() const
	{
		return GameAppState::Load;
	}

}
