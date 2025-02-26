#ifndef SIP_SCENE_BASE_H_
#define SIP_SCENE_BASE_H_
#pragma once

// INCLUDE
#include "IScene.h"

namespace sip
{
    class SceneBase : public IScene
    {
    public:
        virtual ~SceneBase() = default;

        virtual void setSceneChanger(ISceneChanger* pSceneChanger) override { m_pSceneChanger = pSceneChanger; }
        virtual ISceneChanger* getSceneChanger() const { return m_pSceneChanger; }

    private:

        ISceneChanger* m_pSceneChanger;
    };
}

#endif //! SIP_SCENE_BASE_H_
