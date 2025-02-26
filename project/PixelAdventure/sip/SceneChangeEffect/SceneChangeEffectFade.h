#ifndef SIP_SCENE_CHANGE_EFFECT_FADE_H_
#define SIP_SCENE_CHANGE_EFFECT_FADE_H_
#pragma once

// INCLUDE
#include "../SceneManager/ISceneChangeEffect.h"
#include "../DrawObject/Base/DrawObject.h"
#include <Siv3D.hpp>

namespace sip 
{
    /**
    * @brief シーンチェンジフェード効果クラス
    */
    class SceneChangeEffectFade : public ISceneChangeEffect, DrawObject
    {
    public:
        /**
        * @brief コンストラクタ
        * @param[in] fadeTime  フェード時間
        * @param[in] softRange 境界値
        * @param[in] isSkipFadeOut フェードアウト状態から開始
        */
        explicit SceneChangeEffectFade(
			  const Texture* pFadeOutMask
			, const Texture* pFadeInMask
            , const Texture* pFade
            , const String& pixelShaderKey
            , bool isSkipFadeOut = false
			, float fadeTime = 1.0f
			, float softRange = 0.25f
		);

        /**
        * @brief デストラクタ
        */
        virtual ~SceneChangeEffectFade();

        /**
        * @brief フェード効果を更新する
        */
        virtual void fadeOut() override;
        virtual void fadeIn() override;
        virtual void draw() const override;

        /**
        * @brief 画面効果の終了フラグを取得する
        * @return true : 終了, false : 画面効果中
        */
        virtual bool isEnd() const override;

        virtual bool isDoneFadeOut() const override;

    private:

        /**
        * @brief フェードシェーダー用コンスタントバッファ
        */
        struct RuleFade
        {
            float  softRange; //!< 境界値
            float  fadeTime;  //!< フェード時間
            //float  dummy[2]; //!< アライメント用
        };

        float          m_fadeTime{ 0.5f };          //!< フェードにかける時間
        bool           m_isDoneFadeOut{ false };    //!< フェードOUT完了フラグ
		RuleFade       m_cbRuleFade{ 0.25f, 0.0f }; //!< ルールフェード値
		const Texture* m_pFadeTexture;              //!< フェード用画像
		const Texture* m_pFadeOutMaskTexture;       //!< フェードアウト用マスク画像
		const Texture* m_pFadeInMaskTexture;        //!< フェードイン用マスク画像
        PixelShader    m_psObj;                     //!< フェード用ピクセルシェーダー
    };
}

#endif // !SIP_SCENE_CHANGE_EFFECT_FADE_H_
