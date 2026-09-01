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
	m_fontHandle = CreateFontToHandle("クラフト明朝", 20, 9, -1);
	m_handle = LoadGraph("data/img/minto_1.png");
	SetHandle(m_handle);
}

void minto::End()
{
	DeleteGraph(m_handle);
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
		(
		Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 50,
		//	0,0,
		//	posX * kWidth, posY * kHeight,
		kWidth * posX + 50, kHeight * posY,
		kWidth, kHeight, 0.6, 0,
		m_handle, true
		);
		DrawBox(Game::kScreenWidth / 2 - 201, Game::kScreenHeight / 2 -1, Game::kScreenWidth / 2 - 9, Game::kScreenHeight / 2 + 51, GetColor(0, 0, 0), false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		DrawBox(Game::kScreenWidth / 2 -200, Game::kScreenHeight / 2 , Game::kScreenWidth / 2 - 10, Game::kScreenHeight / 2 + 50, GetColor(255,255,255), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatStringToHandle(Game::kScreenWidth / 2 - 200, Game::kScreenHeight / 2 ,
		GetColor(0, 255, 0), m_fontHandle, "現在のエネルギー量");
		DrawFormatStringToHandle(Game::kScreenWidth / 2 - 150, Game::kScreenHeight / 2 +20,
		GetColor(0, 255, 0), m_fontHandle, "%d / 100", m_energy);
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

