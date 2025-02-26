#include "SceneManager.h"

namespace sip
{
    /**
    * @brief コンストラクタ
    */
    SceneManager::SceneManager()
        : m_pScene{ nullptr }
        , m_nextScene{ none }
        , m_pChangeEffect{ nullptr }
        , m_sceneMap{}
    {
    }

    /**
    * @brief デストラクタ
    */
    SceneManager::~SceneManager() 
    {
    }

    /**
    * @brief 指定したシーンへ変更する
    * @param[in] key    変更するシーンのキー
    * @param[in] effect 変更するシーンの画面効果
    * @return true : 変更完了, false : 変更失敗
    */
    bool SceneManager::change(SceneKey key, ISceneChangeEffect* effect)
    {
        if (m_pChangeEffect)
        {
            return false;
        }
        // エフェクトを保存
        m_pChangeEffect.reset(effect);
        m_nextScene = key;
        return true;
    }

    /**
    * @brief シーン変更中のフラグを取得する
    * @return true : 変更中, false : 変更完了
    */
    bool SceneManager::isChange()
    {
        return (m_pChangeEffect != nullptr);
    }

    /**
    * @brief シーン管理を更新する
    */
    void SceneManager::update()
    {
        if (m_pScene) 
        { 
            m_pScene->update();
        }
        
        if (m_pChangeEffect)
        {
            if (!m_pChangeEffect->isDoneFadeOut())
            {
                m_pChangeEffect->fadeOut();
            }
            else
            {
                if (m_nextScene.has_value())
                {
                    if (m_pScene)
                    {
                        m_pScene->release();
                    }
                    m_pScene.reset(m_sceneMap[(*m_nextScene)]->create());
                    m_pScene->init();
                    m_nextScene.reset();
                }
                if (m_pScene->isFadeInEnable())
                {
                    m_pChangeEffect->fadeIn();
                }
            }
            if (m_pChangeEffect->isEnd())
            {
                m_pChangeEffect.reset();
            }
        }
    }

    /**
    * @brief シーン管理を開放する
    */
    void SceneManager::release()
    {
        if (m_pScene)
        {
            m_pScene->release();
            m_pScene.reset();
        }
        if(m_pChangeEffect)
        {
            m_pChangeEffect.reset();
        }
        m_sceneMap.clear();
    }
    
}
