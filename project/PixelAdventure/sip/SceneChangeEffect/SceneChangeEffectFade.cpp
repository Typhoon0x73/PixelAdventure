// INCLUDE
#include "SceneChangeEffectFade.h"
#include <assert.h>
#include <algorithm>
#include "../DrawObject/Base/DrawObjectManager.h"

/**
* @brief コンストラクタ
* @param[in] softRange 境界値
*/
sip::SceneChangeEffectFade::SceneChangeEffectFade(
			  const Texture* pFadeOutMask
			, const Texture* pFadeInMask
			, const Texture* pFade
			, const String& pixelShaderKey
			, bool isSkipFadeOut
			, float fadeTime
			, float softRange
)
    : DrawObject{ define::Layer::Fade }
	, m_cbRuleFade{ RuleFade{ softRange, 0.0f } }
    , m_isDoneFadeOut{ isSkipFadeOut }
    , m_fadeTime{ fadeTime }
	, m_pFadeTexture{ pFade }
	, m_pFadeOutMaskTexture{ pFadeOutMask }
	, m_pFadeInMaskTexture{ pFadeInMask }
    , m_psObj{ PixelShaderAsset(pixelShaderKey) }
{
    // 0以下にならないようにする
    if (m_fadeTime <= 0.0f)
    {
        m_fadeTime = 0.01f;
    }
    if (isSkipFadeOut)
    {
        m_cbRuleFade.fadeTime = 1.0f;
    }

	const auto& fadeTextureSize = m_pFadeTexture->size();
	const auto& sceneSize = Scene::Size();
	setScale(
		static_cast<double>(sceneSize.x) / fadeTextureSize.x,
		static_cast<double>(sceneSize.y) / fadeTextureSize.y
	);
}

/**
* @brief デストラクタ
*/
sip::SceneChangeEffectFade::~SceneChangeEffectFade()
{
}

/**
* @brief フェード効果を更新する
*/
void sip::SceneChangeEffectFade::fadeOut()
{
    if (m_isDoneFadeOut)
    {
        return;
    }
    // フェード値更新
    m_cbRuleFade.fadeTime += static_cast<float>(Scene::DeltaTime()) / m_fadeTime;
    if (1.0f <= m_cbRuleFade.fadeTime)
    {
        m_cbRuleFade.fadeTime = 1.0f;
        m_isDoneFadeOut = true;
    }
}

void sip::SceneChangeEffectFade::fadeIn()
{
    // フェード値更新
    m_cbRuleFade.fadeTime -= static_cast<float>(Scene::DeltaTime()) / m_fadeTime;
    // フェード値を(0.0 ~ 1.0)でクリッピング
    m_cbRuleFade.fadeTime = std::clamp(m_cbRuleFade.fadeTime, 0.0f, 1.0f);
}

/**
* @brief フェード効果を描画する
*/
void sip::SceneChangeEffectFade::draw() const
{
	// マスク用画像
	const Texture* pMaskTexture = (m_isDoneFadeOut ? m_pFadeInMaskTexture : m_pFadeOutMaskTexture);
	// コンスタントバッファの設定
	ConstantBuffer<RuleFade> cb{ m_cbRuleFade };
	Graphics2D::SetPSTexture(1, *pMaskTexture);
	Graphics2D::SetPSConstantBuffer(1, cb);
	// シェーダーで描画
	{
		const ScopedCustomShader2D shader{ m_psObj };
		m_pFadeTexture->scaled(getScale()).drawAt(Scene::CenterF());
	}
}

/**
* @brief 画面効果の終了フラグを取得する
* @return true : 終了, false : 画面効果中
*/
bool sip::SceneChangeEffectFade::isEnd() const
{
    return m_isDoneFadeOut && (m_cbRuleFade.fadeTime == 0.0f);
}

bool sip::SceneChangeEffectFade::isDoneFadeOut() const
{
    return m_isDoneFadeOut;
}
