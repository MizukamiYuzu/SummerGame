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

	int GetHp()const{ return m_hp; }


private :
	//体力
	int m_hp = 100;
};

