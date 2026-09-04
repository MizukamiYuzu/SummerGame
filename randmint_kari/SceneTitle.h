#pragma once
#include "Game.h"
#include "Dxlib.h"

class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void End();
	void Update();
	void Draw();

	bool isEnd() const { return m_isEnd; }

private:

	int m_soundHandle;

	int m_fontHandle;


	bool m_isEnd;
	bool m_isKeyDownBefore;

	bool m_showRule = false;

	// タイトル背景画像
	int m_BgTitleGraph;
	// ルール画像
	int RuleSousa1Handle;
	int RuleSousa2Handle;
	int RuleSousa3Handle;
	int RuleWin1Handle;
	int RuleWin2Handle;
	int RuleWin3Handle;
	int RuleWin4Handle;
	int RuleFinaleHandle;
	int RuleArrowHandle;
	int RuleCloseHandle;
	// 今何番目のルール画像か
	int m_isClickIndex = 0;
};

