#pragma once
#include "CardManager.h"

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

private:

private:
	// 現在のシーンの実行時間(フレーム数)
	int m_frameCount;
	// カードマネージャーのポインター
	CardManager* m_pCardManager;
};

