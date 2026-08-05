#pragma once
class Player
{
public :
	Player();
	~Player();

	void Damage(int damage);

	void Heal(int heal);
private :
	//体力
	int m_hp = 100;
};

