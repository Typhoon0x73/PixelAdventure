#ifndef SIP_SCENE_MANAGER_H_
#define SIP_SCENE_MANAGER_H_
#pragma once

// INCLUDE
#include "ISceneChanger.h"
#include "IsceneCreator.h"
#include <Siv3D.hpp>

namespace sip
{
    /**
    * @brief シーン管理インターフェース
    */
    class ISceneManager : public ISceneChanger
    {
    public:
        /**
        * @brief デストラクタ
        */
        virtual ~ISceneManager() = default;

        /**
        * @brief シーン管理を更新する
        */
        virtual void update() = 0;

        /**
        * @brief シーン管理を開放する
        */
        virtual void release() = 0;
    };
    //---------------------------------------------------------------------

    /**
    * @brief シーン管理クラス
    */
    class SceneManager : public ISceneManager
    {
    public:
        /**
        * @brief シーン生成クラス
        * @tparam T シーン継承クラス
        */
        template < class T >
        class SceneCreator : public ISceneCreator
        {
        public:
            /**
            * @brief シーンを生成する
            * @return 生成されたシーンポインタ
            */
            virtual IScene* create() override
            {
                return new T();
            }
        };

    public:
        /**
        * @brief コンストラクタ
        */
        SceneManager();

        /**
        * @brief デストラクタ
        */
        virtual ~SceneManager();

        /**
        * @brief シーンを登録する
        * @tparam T シーン継承クラス
        * @param[in] key 登録するキー
        */
        template < class T >
        SceneManager& add(SceneKey key)
        {
            m_sceneMap[key] = std::make_unique<SceneCreator<T>>();
        	return *this;
        }

        /**
        * @brief 指定したシーンへ変更する
        * @param[in] key    変更するシーンのキー
        * @param[in] effect 変更するシーンの画面効果
        * @return true : 変更完了, false : 変更失敗
        */
        virtual bool change(SceneKey key, ISceneChangeEffect* effect) override;

        /**
        * @brief シーン変更中のフラグを取得する
        * @return true : 変更中, false : 変更完了
        */
        virtual bool isChange() override;

        /**
        * @brief シーン管理を更新する
        */
        virtual void update() override;

        /**
        * @brief シーン管理を開放する
        */
        virtual void release() override;

    private:

        std::unique_ptr<IScene>                             m_pScene;        //!< シーン
        Optional<SceneKey>                                  m_nextScene;     //!< 切り替え先のシーン
        std::unique_ptr<ISceneChangeEffect>                 m_pChangeEffect; //!< 画面変更効果
        HashTable<SceneKey, std::unique_ptr<ISceneCreator>> m_sceneMap;      //!< シーン生成マップ
    };

}


#endif // !SIP_SCENE_MANAGER_H_
