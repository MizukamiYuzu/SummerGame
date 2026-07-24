#include "CardManager.h"
#include "Dxlib.h"

namespace
{
	constexpr int handNum = 4;	// 初期の手札枚数
}

CardManager::CardManager():
	m_graphDeck(-1)
{
}

CardManager::~CardManager()
{
}

void CardManager::Init()
{
	m_graphDeck = LoadGraph("data/img/deck.png");	// 山札のハンドル
	for (int i = 0; i < handNum; i++)
	{
		m_card[i].Init();
	}
	
}

void CardManager::End()
{
	DeleteGraph(m_graphDeck);
	for (int i = 0; i < handNum; i++)
	{
		m_card[i].End();
	}
}

void CardManager::Update()
{
	for (int i = 0; i < handNum; i++)
	{
		m_card[i].Update();
	}
	GetMousePoint(&MouseX, &MouseY);
}

void CardManager::Draw()
{
	
	DrawExtendGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, Game::kScreenWidth / 2 + 100, Game::kScreenHeight / 2 + 100, m_graphDeck, true);	// 山札描画
	for (int i = 0; i < handNum; i++)	// 手札を並ばせる
	{
		PlayerCardPosX = 100 * i + 50;
		int y1 = Game::kScreenHeight / 2;
		int y2 = Game::kScreenHeight / 2 + 100;

		/*条件掃出し*/
		bool isMouseOutleft = MouseX >= PlayerCardPosX;//カードの左側にマウスが出ている



		// bool isInCard = 




		// ↓手札
		//上下左右どちらにも出ていない(カード内にマウスポインタがあるとき)
		if (MouseX >= PlayerCardPosX && MouseX <= PlayerCardPosX + 80 && MouseY >= Game::kScreenHeight / 2 && MouseY <= Game::kScreenHeight / 2 + 100)
		{
			y1 -= 10;
			y2 -= 10;
		}

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{

		}

		m_card[i].Draw(PlayerCardPosX, y1, PlayerCardPosX + 80,y2);
	}
	
	
	
	
}
