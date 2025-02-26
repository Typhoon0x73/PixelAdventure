# include <Siv3D.hpp> // Siv3D v0.6.15
#include "GameApp/GameApp.h"
#include "Common/PixCommon.h"

void Main()
{
	pix::AssetsAccessor assetsAccessor;
	sip::DrawObjectManager drawObjectManager;
	pix::GameApp gameApp;

	// アセット管理クラスの登録
	pix::AssetLocator::getInstance().set(&assetsAccessor);

	// 描画オブジェクト管理クラスの登録
	sip::SingletonLocator<sip::DrawObjectManager>::getInstance().set(&drawObjectManager);

	while (System::Update())
	{
		gameApp.update();
		drawObjectManager.draw();
	}
}
