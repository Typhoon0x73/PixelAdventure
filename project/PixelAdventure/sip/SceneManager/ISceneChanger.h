#ifndef SIP_ISCENE_CHANGER_H_
#define SIP_ISCENE_CHANGER_H_
#pragma once

// INCLUDE
#include "IScene.h"
#include "ISceneChangeEffect.h"
#include "SceneDefine.h"

namespace sip
{
    /**
    * @brief シーンチェンジインターフェース
    */
    class ISceneChanger
    {
    public:

        /**
        * @brief デストラクタ
        */
        virtual ~ISceneChanger() = default;
        
        /**
        * @brief 指定したシーンへ変更する
        * @param[in] key    変更するシーンのキー
        * @param[in] effect 変更するシーンの画面効果
        * @return true : 変更完了, false : 変更失敗
        */
        virtual bool change(SceneKey key, ISceneChangeEffect* effect) = 0;
        
        /**
        * @brief シーン変更中のフラグを取得する
        * @return true : 変更中, false : 変更完了
        */
        virtual bool isChange() = 0;
    };

}

#endif // !SIP_ISCENE_CHANGER_H_
