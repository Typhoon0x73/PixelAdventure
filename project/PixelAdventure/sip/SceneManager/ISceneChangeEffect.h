#ifndef SIP_ISCENE_CHANGE_EFFECT_H_
#define SIP_ISCENE_CHANGE_EFFECT_H_
#pragma once

// INCLUDE
#include "IScene.h"

namespace sip
{
    /**
    * @brief シーンチェンジ効果インターフェース
    */
    class ISceneChangeEffect
    {
    public:

        /**
        * @brief デストラクタ
        */
        virtual ~ISceneChangeEffect() = default;
        
        /**
        * @brief 画面効果を更新する
        */
        virtual void fadeOut() = 0;
        virtual void fadeIn() = 0;
        virtual void draw() const = 0;

        /**
        * @brief 画面効果の終了フラグを取得する
        * @return true : 終了, false : 画面効果中
        */
        virtual bool isEnd() const = 0;

        /**
        * @brief フェードアウトが完了しているかを返す
        */
        virtual bool isDoneFadeOut() const = 0;
    };

}

#endif // !SIP_ISCENE_CHANGE_EFFECT_H_
