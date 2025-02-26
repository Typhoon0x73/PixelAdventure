#ifndef SIP_SCENE_DEFINE_H_
#define SIP_SCENE_DEFINE_H_
#pragma once

namespace sip
{
    enum class SceneKind
    {
		Title,
		StageSelect,
		Game,
    };

    using SceneKey = SceneKind;
}


#endif //! SIP_SCENE_DEFINE_H_
