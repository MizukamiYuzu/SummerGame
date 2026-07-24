#include "Card.h"
#include "Game.h"
#include "Dxlib.h"

namespace
{
	constexpr int handNum = 4;	// 初期の手札枚数
}

Card::Card():
	m_graphHand(-1),
	MouseX(0),
	MouseY(0),
	PlayerCardPosX(0),
	_isCard(false)
{
}

Card::~Card()
{
}

void Card::Init()
{
	m_graphHand = LoadGraph("data/img/hand.png");	// 手札のハンドル
	_isCard = true;
	PlayerCardPosX = 50;
}

void Card::End()
{
	DeleteGraph(m_graphHand);
}

void Card::Update()
{
	GetMousePoint(&MouseX, &MouseY);
}

void Card::Draw(int PlayerCardPosX_s, int y1, int PlayerCardPosX_f, int y2)
{
	//if (m_card[i]==0)return;
	//if (m_card[i - 1] == 0) 
	//{
	//	i = i - 1;
	//}
	//// ↓手札
	//PlayerCardPosX = 100*i+50;
	//if (MouseX >= PlayerCardPosX && MouseX <= PlayerCardPosX + 80 && MouseY >= Game::kScreenHeight / 2 && MouseY <= Game::kScreenHeight / 2 + 100)
	//{
	//	DrawExtendGraph(PlayerCardPosX, Game::kScreenHeight / 2 - 10, PlayerCardPosX + 80, Game::kScreenHeight / 2 + 100 - 10, m_graphHand, true);
	//	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	//	{
	//		m_card[i] = 0;
	//	}
	//}
	//else
	//{
	//	DrawExtendGraph(PlayerCardPosX, Game::kScreenHeight / 2, PlayerCardPosX + 80, Game::kScreenHeight / 2 + 100, m_graphHand, true);	// 通常描画
	//}
	
	DrawExtendGraph(PlayerCardPosX_s, y1, PlayerCardPosX_f, y2, m_graphHand, true);
	
	
}
