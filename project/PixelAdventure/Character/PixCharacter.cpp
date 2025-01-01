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
		const auto& animationInfo = AnimationInfoTable.at(m_state);
		const auto& animationPattern = animationInfo.patterns[m_animPatternIndex];
		const auto& animTime = animationPattern.playTime;
		m_animTimer += Scene::DeltaTime();
		if (m_animTimer < animTime.count())
		{
			m_animPatternIndex++;
			m_animTimer = 0.0;
			int32 patternCount = static_cast<int32>(std::size(animationInfo.patterns));
			if (patternCount <= m_animPatternIndex)
			{
				if (animationInfo.isLoop)
				{
					m_animPatternIndex = 0;
				}
				else
				{
					m_animPatternIndex = patternCount - 1;
				}
			}
		}
	}

	void Character::draw() const
	{
		const auto& animationInfo = AnimationInfoTable.at(m_state);
		const auto& animationPattern = animationInfo.patterns[m_animPatternIndex];
		const auto& characterInfo = std::find_if(std::begin(CharacterInfoTable), std::end(CharacterInfoTable), [this](const auto& info) {});
		const char32_t* textureKey = TextureFileInfos[FromEnum(characterInfo->texturenKindBegin) + FromEnum(m_state)].assetKey;
		const auto& texture = TextureAsset(textureKey);
		texture(animationPattern.srcRect).drawAt(m_centerPos);
	}

	const RectF Character::getHitRect() const
	{
		return RectF();
	}

	void Character::changeState(State state)
	{
		if (m_state == state)
		{
			return;
		}
		m_state = state;
		m_animPatternIndex = 0;
		m_animTimer = 0.0;
	}

}
