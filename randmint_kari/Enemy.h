#pragma once
#include "Player.h"
#include "CardEffect.h"
#include "Timer.h"
#include "minto.h"
#include <vector>
#include "Dxlib.h"

class Enemy : public Player	// 継承
{
public:
	Enemy();
	~Enemy();


	void Init();
	void End();

	// 手札の何番目を使うを返す関数
	int ThinkAction
	(
		const std::vector<int>& validIndices,			// 使われていないカードの番号を記録する動的配列
		int playerHp,									// プレイヤーのHP
		int enemyHp,									// エネミーのHP
		int mintoEnergy,								// ミントエネルギー
		const std::vector<CardEffect>& handEffects,
		const std::vector<CardEffect>& rules
	);

private:

	int m_thinkTimer = 60; // 考える時間の変数 ←フレーム

	// タイマーの生成
	Timer* m_pTimer;

	// ミントの生成
	minto* m_pMinto;
};

