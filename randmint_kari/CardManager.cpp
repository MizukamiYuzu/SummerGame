#include "CardManager.h"
#include "Dxlib.h"

namespace
{
	constexpr int firstHandNum = 4;	// 初期の手札枚数
}

CardManager::CardManager() :
	m_graphDeck(-1),
	MouseX(0),
	MouseY(0),
	handNum(0),
	PlayerCardPosX(0),
	_isClickBefore(false),
	_isClickNow(false)
{
}

CardManager::~CardManager()
{
}

void CardManager::Init()
{
	handNum = 4;
	m_graphDeck = LoadGraph("data/img/deck.png");	// 山札のハンドル
	m_card.resize(firstHandNum+200);
	for (int i = 0; i < firstHandNum; i++)
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
	_isClickBefore = _isClickNow;
	_isClickNow = (GetMouseInput() & MOUSE_INPUT_LEFT);
	for (int i = 0; i < handNum; i++)
	{
		m_card[i].Update();
	}
	GetMousePoint(&MouseX, &MouseY);
}

void CardManager::Draw()
{
	

	DrawExtendGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, Game::kScreenWidth / 2 + 100, Game::kScreenHeight / 2 + 100, m_graphDeck, true);	// 山札描画
	
	int drawCount = 0;	// 消されていないならカウントをする
	bool _isDeleteCard = false;	// このフレーム（ワンクリック）でカードが消されたかどうか	←　一回のクリックで一枚だけ消すようにする変数
	// ↑ワンフレームでしか使わないからここで宣言して良き
	for (int i = 0; i < handNum; i++)	// 手札を並ばせる
	{
		PlayerCardPosX = 100 * drawCount + 50;
		int y1 = Game::kScreenHeight / 2;
		int y2 = Game::kScreenHeight / 2 + 100;

		/*条件掃出し*/
		// ↓山札カード
		bool isMouseOutLeft_y = MouseX >= Game::kScreenWidth / 2;
		bool isMouseOutRight_y = MouseX <= Game::kScreenHeight / 2;
		bool isMouseOutUp_y = MouseY >= Game::kScreenWidth / 2 + 100;
		bool isMouseOutDown_y = MouseY <= Game::kScreenHeight / 2 + 100;
		bool isInsideCard_y = isMouseOutLeft_y && isMouseOutRight_y && isMouseOutUp_y && isMouseOutDown_y;
		DrawBox (Game::kScreenWidth / 2, Game::kScreenHeight / 2, Game::kScreenWidth / 2 + 100, Game::kScreenHeight / 2 + 100, GetColor(255,255,255),true);

		// ↓手札カード
		bool isMouseOutLeft = MouseX >= PlayerCardPosX;//カードの左側より内側にマウスがいる
		bool isMouseOutRight = MouseX <= PlayerCardPosX + 80;
		bool isMouseOutUp = MouseY >= y1;
		bool isMouseOutDown = MouseY <= y2;
		bool isInsideCard = isMouseOutLeft && isMouseOutRight && isMouseOutUp && isMouseOutDown;






		// bool isInCard = 




		// ↓手札
		//上下左右どちらにも出ていない(カード内にマウスポインタがあるとき)
		if (isInsideCard)
		{
			y1 -= 10;
			y2 -= 10;
			if ((_isClickBefore == false) && (_isClickNow == true) && _isDeleteCard == false)
			{
				m_card[i].SetCard(false); // m_card[i]に引数をぶち込む
				_isDeleteCard = true;
			}
		}
		if (isInsideCard_y)
		{
			if ((_isClickBefore == false) && (_isClickNow == true))
			{
				handNum++;
				m_card[handNum].Draw(PlayerCardPosX, y1, PlayerCardPosX + 80, y2);
				
				drawCount++;
			}
		}

		
		if (m_card[i].GetCard()==true) // 戻り値を取得して条件に使っている
		{
			m_card[i].Draw(PlayerCardPosX, y1, PlayerCardPosX + 80, y2);
			drawCount++;
		}
		
	}
	
	
	
	
}
