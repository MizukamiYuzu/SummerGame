#include "DxLib.h"
#include "Game.h"
#include "SceneMain.h"
#include "SceneTitle.h"

namespace
{
	enum SceneType
	{
		kSceneTitle,
		kSceneMain,
	};
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windowモードで起動する
	ChangeWindowMode(1);

	// ウィンドウサイズを16:9に
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kScreenDepth);

	// ウィンドウのタイトル表示を変更
	SetMainWindowText("RandMint");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームシーンの作成
	SceneMain sceneMain;
	SceneTitle  sceneTitle;/*
	sceneMain.Init();
	sceneTitle.Init();*/

	// 現在実行したいシーンを変数で持つ
	SceneType type = kSceneTitle;

	switch (type)
	{
	case kSceneTitle:
		sceneTitle.Init();
		break;
	case kSceneMain:
		sceneMain.Init();
		break;
	}

	while (ProcessMessage()==0)
	{
		// 現在のフレーム開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();

		// 画面をクリア
		ClearDrawScreen();

		switch (type)
		{
		case kSceneTitle:
			sceneTitle.Update();
			sceneTitle.Draw();
			if (sceneTitle.isEnd())
			{
				sceneTitle.End();

				type = kSceneMain;

				sceneMain.Init();
			}

			break;
		case kSceneMain:
			sceneMain.Update();
			sceneMain.Draw();
			if (sceneMain.isEnd())
			{
				sceneMain.End();

				type = kSceneTitle;

				sceneTitle.Init();
			}
			break;
		}

		//// ゲームの処理
		//sceneTitle.Update();
		//sceneMain.Update();
		//sceneTitle.Draw();
		//sceneMain.Draw();
	

		// 画面の書き換えを待つ
		ScreenFlip();

		// escキーを押したらゲームを強制終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}

		// 画面のリフレッシュレートにかかわらず1/60経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 時間経過まで何もせずに待つ
		}

	}
	/*
	sceneTitle.End();
	sceneMain.End();*/
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}