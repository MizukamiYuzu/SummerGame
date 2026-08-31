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

	bool m_isEnd;
	bool m_isKeyDownBefore;

	// タイトル背景画像
	int m_BgTitleGraph;
};

