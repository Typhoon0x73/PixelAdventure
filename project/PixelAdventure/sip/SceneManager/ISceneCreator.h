#ifndef SIP_ISCENE_CREATOR_H_
#define SIP_ISCENE_CREATOR_H_
#pragma once

// INCLUDE
#include "IScene.h"

namespace sip
{
    /**
    * @brief シーンクリエイターインターフェース
    */
    class ISceneCreator
    {
    public:
    
        /**
        * @brief デストラクタ
        */
        virtual ~ISceneCreator() = default;

        /**
        * @brief シーンを生成する
        * @return 生成されたシーンポインタ
        */
        virtual IScene* create() = 0;
    };

}

#endif // !SIP_ISCENE_CREATOR_H_
