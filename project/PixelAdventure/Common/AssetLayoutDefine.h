#pragma once

namespace pix::asset::define
{
	enum class LayoutKind
	{
		Popup_Credit,
		Popup_GamePause,
		Popup_Option,
		Popup_OptionPage1,
		Popup_OptionPage2,
		Popup_StageResult,
		Scene_Game,
		Scene_StageSelect,
		Scene_StageSelectFooter,
		Scene_StageSelectHeader,
		Scene_StageSelectStageList,
		Scene_Title,
	};

	struct {
		const char32_t* key;
		const char32_t* path;
	}
	constexpr LayoutFileInfos[] = {
		{ U"PopupCredit", U"resources/Layout/popup_credit.csv" },
		{ U"PopupGamePause", U"resources/Layout/popup_game_pause.csv" },
		{ U"PopupOption", U"resources/Layout/popup_option.csv" },
		{ U"PopupOptionPage1", U"resources/Layout/popup_option_page1.csv" },
		{ U"PopupOptionPage2", U"resources/Layout/popup_option_page2.csv" },
		{ U"PopupStageResult", U"resources/Layout/popup_stage_result.csv" },
		{ U"SceneGame", U"resources/Layout/scene_game.csv" },
		{ U"SceneStageSelect", U"resources/Layout/scene_stage_select.csv" },
		{ U"SceneStageSelectFooter", U"resources/Layout/scene_stage_select_footer.csv" },
		{ U"SceneStageSelectHeader", U"resources/Layout/scene_stage_select_header.csv" },
		{ U"SceneStageSelectStageList", U"resources/Layout/scene_stage_select_stage_list.csv" },
		{ U"SceneTitle", U"resources/Layout/scene_title.csv" },
	};
}
