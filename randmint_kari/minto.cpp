#include "minto.h"

namespace
{
	constexpr int kWidth = 135;
	constexpr int kHeight = 185;
}

minto::minto()
{
}

minto::~minto()
{
}

void minto::Init()
{
	m_handle = LoadGraph("data/img/minto.png");
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
		posX = m_energy / 10;
		posY = 1;
	}
	else
	{
		posX = (m_energy - 50) / 10;
	}
	DrawRectRotaGraph
	(Game::kScreenWidth / 2 - 100 , Game::kScreenHeight / 2 - 50,
	//	0,0,
	//	posX * kWidth, posY * kHeight,
		kWidth*0, kHeight*0,
		kWidth, kHeight, 1.0,0,
		m_handle, true);
	
	
	
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

