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
	int m_frameCount;

	CardManager m_cardMana;
};

