#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Damage(int damage)
{
	//体力減らす
	m_hp -= damage;
	if (m_hp < 0)
	{
		m_hp = 0;
	}
}

void Player::Heal(int heal)
{
}
