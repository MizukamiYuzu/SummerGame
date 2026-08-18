#include "minto.h"

namespace
{
	constexpr int kWidth = 300;
	constexpr int kHeight = 400;
}

minto::minto()
{
}

minto::~minto()
{
}

void minto::Init()
{
	m_handle = LoadGraph("data/img/minto_1.png");
	SetHandle(m_handle);
}

void minto::End()
{
	DeleteGraph(m_handle);
}

void minto::Update()
{
}

void minto::Draw()
{
	int posX = 0;
	int posY = 0;
	if (m_energy >= 50)
	{
		posX = (m_energy - 50) / 10;
		posY = 1;
	}
	else
	{

		posX = m_energy / 10;
	}
	if (posX <= 0)
	{
		posX = 0;
	}
	if(m_plant)
	{
		DrawRectRotaGraph
		(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 50,
		//	0,0,
		//	posX * kWidth, posY * kHeight,
			kWidth * posX + 50, kHeight * posY,
			kWidth, kHeight, 0.4, 0,
			m_handle, true);
	}
	

	DrawFormatString(0, 32, GetColor(255, 255, 255), "minto : %d", m_energy);
	
	
	
}

void minto::GetAddEnergy(int addEnergy)
{
	m_energy += addEnergy;
}

void minto::GetWither()
{
	m_plant = false;
	m_energy = 0;
}

