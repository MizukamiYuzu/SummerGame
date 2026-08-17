#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::End()
{
}

void Player::Update()
{
	TurnManager turnManager;
	switch (TurnManager::Player::Player1)
	{
	default:
		break;
	}
}

void Player::Draw()
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
