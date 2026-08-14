#pragma once
#include "TurnManager.h"

class Player
{
public :
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	void Damage(int damage);

	void Heal(int heal);


private :
	//体力
	int m_hp = 100;
};

