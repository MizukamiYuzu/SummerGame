#include "Card.h"
#include "Dxlib.h"

namespace
{
	constexpr int handNum = 4;	// 初期の手札枚数
	constexpr int cardWidth = 100;
	constexpr int cardHeight = 120;
}

Card::Card():
	m_cardGraphHand(-1),
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
	m_isCard = true;
	m_playerCardPosX = 50;
}

void Card::End()
{
}

void Card::Update()
{
	GetMousePoint(&m_mouseX, &m_mouseY);
}

void Card::Draw()
{

	if (m_isCard)
	{
		DrawExtendGraph(m_drawPosX, m_drawPosY -5, m_drawPosX + cardWidth, m_drawPosY + cardHeight + 5, m_cardGraphHand, true);
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
