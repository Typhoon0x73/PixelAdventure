#include "PixCharacter.h"
#include "../Common/PixTextureDefine.h"

namespace pix
{
	namespace
	{
		struct
		{
			Character::Kind charaKind;
			TextureKind texturenKindBegin;
			TextureKind texturenKindEnd;
		}
		static const CharacterInfoTable[] =
		{
			{ Character::Kind::MuskDude, TextureKind::Character_MaskDude_Begin, TextureKind::Character_MaskDude_End, },
		};

		static const HashTable<Character::State, AnimationInfo> AnimationInfoTable =
		{
			{ Character::State::Desappearing, {{{ { 0, 0, 96, 96 }, 0.016s },{ { 96 * 1, 0, 96, 96 }, 0.016s },{ { 96 * 2, 0, 96, 96 }, 0.016s },{ { 96 * 3, 0, 96, 96 }, 0.016s },{ { 96 * 4, 0, 96, 96 }, 0.016s },{ { 96 * 5, 0, 96, 96 }, 0.016s },{ { 96 * 6, 0, 96, 96 }, 0.016s }, }, false } },
			{ Character::State::Appearing   , {{{ { 0, 0, 96, 96 }, 0.016s },{ { 96 * 1, 0, 96, 96 }, 0.016s },{ { 96 * 2, 0, 96, 96 }, 0.016s },{ { 96 * 3, 0, 96, 96 }, 0.016s },{ { 96 * 4, 0, 96, 96 }, 0.016s },{ { 96 * 5, 0, 96, 96 }, 0.016s },{ { 96 * 6, 0, 96, 96 }, 0.016s }, }, false } },
			{ Character::State::DoubleJump  , {{{ { 0, 0, 32, 32 }, 0.016s },{ { 32 * 1, 0, 32, 32 }, 0.016s },{ { 32 * 2, 0, 32, 32 }, 0.016s },{ { 32 * 3, 0, 32, 32 }, 0.016s },{ { 32 * 4, 0, 32, 32 }, 0.016s },{ { 32 * 5, 0, 32, 32 }, 0.016s },}, false } },
			{ Character::State::Fall        , {{{ { 0, 0, 32, 32 }, 0.016s },}, true } },
			{ Character::State::Hit         , {{{ { 0, 0, 32, 32 }, 0.016s },{ { 32 * 1, 0, 32, 32 }, 0.016s },{ { 32 * 2, 0, 32, 32 }, 0.016s },{ { 32 * 3, 0, 32, 32 }, 0.016s },{ { 32 * 4, 0, 32, 32 }, 0.016s },{ { 32 * 5, 0, 32, 32 }, 0.016s },{ { 32 * 6, 0, 32, 32 }, 0.016s }, }, false } },
			{ Character::State::Idle        , {{{ { 0, 0, 32, 32 }, 0.016s },{ { 32 * 1, 0, 32, 32 }, 0.016s },{ { 32 * 2, 0, 32, 32 }, 0.016s },{ { 32 * 3, 0, 32, 32 }, 0.016s },{ { 32 * 4, 0, 32, 32 }, 0.016s },{ { 32 * 5, 0, 32, 32 }, 0.016s },{ { 32 * 6, 0, 32, 32 }, 0.016s },{ { 32 * 7, 0, 32, 32 }, 0.016s },{ { 32 * 8, 0, 32, 32 }, 0.016s },{ { 32 * 9, 0, 32, 32 }, 0.016s },}, true } },
			{ Character::State::Jump        , {{{ { 0, 0, 32, 32 }, 0.016s },}, true } },
			{ Character::State::Run         , {{{ { 0, 0, 32, 32 }, 0.016s },{ { 32 * 1, 0, 32, 32 }, 0.016s },{ { 32 * 2, 0, 32, 32 }, 0.016s },{ { 32 * 3, 0, 32, 32 }, 0.016s },{ { 32 * 4, 0, 32, 32 }, 0.016s },{ { 32 * 5, 0, 32, 32 }, 0.016s },{ { 32 * 6, 0, 32, 32 }, 0.016s },{ { 32 * 7, 0, 32, 32 }, 0.016s },{ { 32 * 8, 0, 32, 32 }, 0.016s },{ { 32 * 9, 0, 32, 32 }, 0.016s },{ { 32 * 10, 0, 32, 32 }, 0.016s },{ { 32 * 11, 0, 32, 32 }, 0.016s },}, true } },
			{ Character::State::WallJump    , {{{ { 0, 0, 32, 32 }, 0.016s },{ { 32 * 1, 0, 32, 32 }, 0.016s },{ { 32 * 2, 0, 32, 32 }, 0.016s },{ { 32 * 3, 0, 32, 32 }, 0.016s },{ { 32 * 4, 0, 32, 32 }, 0.016s },{ { 32 * 5, 0, 32, 32 }, 0.016s },}, true } },
		};
	}

	Character::Character(Kind kind)
		: m_state{ State::Appearing }
		, m_animPatternIndex{ 0 }
		, m_animTimer{ 0.0 }
		, m_centerPos{ 0.0, 0.0 }
		, m_move{ 0.0, 0.0 }
	{
	}

	Character::~Character()
	{
	}

	void Character::update()
	{
	}

	void Character::draw() const
	{
	}

	const RectF Character::getHitRect() const
	{
		return RectF();
	}

	void Character::changeState(State state)
	{
	}

}
