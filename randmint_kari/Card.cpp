#include "Card.h"
#include "Game.h"
#include "Dxlib.h"

namespace
{
	constexpr int handNum = 4;	// 初期の手札枚数
	constexpr int cardWidth = 80;
	constexpr int cardHeight = 100;
}

Card::Card():
	m_graphHand(-1),
	m_mouseX(0),
	m_mouseY(0),
	m_drawPosX(0),
	m_drawPosY(0),
	m_playerCardPosX(0),
	m_isCard(false)
{
}

Card::~Card()
{
}

void Card::Init()
{
	m_graphHand = LoadGraph("data/img/hand.png");	// 手札のハンドル
	m_isCard = true;
	m_playerCardPosX = 50;
}

void Card::End()
{
	DeleteGraph(m_graphHand);
}

void Card::Update()
{
	GetMousePoint(&m_mouseX, &m_mouseY);
}

void Card::Draw()
{

	if (m_isCard)
	{
		DrawExtendGraph(m_drawPosX, m_drawPosY, m_drawPosX + cardWidth, m_drawPosY + cardHeight, m_graphHand, true);
	}
	
	
	
}

int Card::GetCardWidth()
{
	return cardWidth;
}

int Card::GetCardHeight()
{
	return cardHeight;
}
