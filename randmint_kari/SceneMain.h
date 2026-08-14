#pragma once
#include "Dxlib.h"
#include "CardManager.h"
#include "minto.h"

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



	// 現在のシーンの実行時間(フレーム数)
	int m_frameCount;
	// カードマネージャーのポインター
	CardManager* m_pCardManager;
	minto* m_minto;

	
};

