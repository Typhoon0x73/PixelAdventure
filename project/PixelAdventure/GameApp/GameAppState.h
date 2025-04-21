#pragma once

namespace pix
{
	enum class GameAppState
	{
		Init,
		Load,
		Idle,
	};

    struct GameAppData
    {
        
    };
    
    using StateBase = sip::StateBase<GameAppState, GameAppData>;
}
