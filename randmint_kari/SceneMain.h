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

	int m_skipGraphHandle;

	// 画像の読み込み
	// 山札のハンドル
	int m_deckHandle;

	// クリック判定用変数
	bool m_isClickBefore;	// 1フレーム前にクリックされたかどうか
	bool m_isClickNow;		// 現在クリックされているかどうか
	

	// 現在のシーンの実行時間(フレーム数)
	int m_frameCount;
	// カードマネージャーのポインター
	CardManager* m_pCardManager;
	
};

