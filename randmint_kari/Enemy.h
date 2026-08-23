#pragma once
#include "Player.h"
#include "CardEffect.h"
#include <vector>
#include "Dxlib.h"

class Enemy : public Player	// 継承
{
public:
	Enemy();
	~Enemy();

	void Init();

	// 手札の何番目を使うを返す関数
	int ThinkAction(const std::vector<int>& validIndices, int playerHp, int enemyHp, int mintoEnergy);

private:
	
	int m_thinkTimer = 60; // 考える時間の変数 ←フレーム
};

