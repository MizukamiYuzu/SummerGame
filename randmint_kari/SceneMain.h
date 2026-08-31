#pragma once
#include "Dxlib.h"
#include "CardManager.h"
#include "TurnManager.h"
#include "minto.h"
#include "Game.h"


class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();

	void Update();
	void Draw();
	// Alt + Enter → 一番上選択すると、cppのほうで、関数を作ることが可能

	bool isEnd() { return m_isEnd; }

private:

private:
	bool m_isEnd;

	bool m_isKeyDownBefore;

	bool m_isTimerStart = false;

	int m_skipGraphHandle;


	// フォントのハンドル
	int m_fontHandle;

	// 画像の読み込み
	// 山札のハンドル
	int m_deckHandle;
	int m_graphBgMainHandle;	// 背景画像ハンドル
	int m_graphCardBgHandle;	// カード下に引く画像

	// クリック判定用変数
	bool m_isClickBefore;	// 1フレーム前にクリックされたかどうか
	bool m_isClickNow;		// 現在クリックされているかどうか
	

	// 現在のシーンの実行時間(フレーム数)
	int m_frameCount;

	// 勝利した時のテキスト表示
	std::string m_WinText;

	// カードマネージャーのポインター
	CardManager* m_pCardManager;

	// タイマーのポインター
	Timer* m_pTimer;
	
};

