# include <Siv3D.hpp> // Siv3D v0.6.15

# include "Common/PixCommon.h"
# include "Scene/Title/PixSceneTitle.h"
# include "Scene/Select/PixSceneSelect.h"
# include "Scene/Game/PixSceneGame.h"


void Main()
{
	// 各アセットの登録
	for (const auto& it : pix::TextureFileInfos)
	{
		TextureAsset::Register(it.assetKey, it.fileName);
	}

	// シーン管理
	pix::SceneManager sceneManager;

	// シーンの追加
	sceneManager
		.add<pix::SceneTitle>(pix::SceneKind::Title)
		.add<pix::SceneSelect>(pix::SceneKind::Select)
		.add<pix::SceneGame>(pix::SceneKind::Game);

	// シーンの初期化
	sceneManager.init(pix::SceneKind::Game, 1s);



	while (System::Update())
	{
		sceneManager.update();
	}
}
