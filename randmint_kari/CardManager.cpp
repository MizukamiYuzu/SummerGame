#include "CardManager.h"
#include "Dxlib.h"

namespace
{
	constexpr int kFirstHandNum = 4;	// 初期の手札枚数
	constexpr int kCardWidthMaxCount = 11;
}

CardManager::CardManager() :
	m_graphDeck(-1),
	MouseX(0),
	MouseY(0),
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
	m_graphDeck = LoadGraph("data/img/deck.png");	// 山札のハンドル
	m_card.resize(kFirstHandNum);
	for (int i = 0; i < kFirstHandNum; i++)
	{
		m_card[i].Init();
	}
	
}

void CardManager::End()
{
	DeleteGraph(m_graphDeck);
	for (int i = 0; i < m_card.size(); i++)	// m_card.size() <- size()で配列の数を出すことができる
	{
		m_card[i].End();
	}
}

void CardManager::Update()
{

	_isClickBefore = _isClickNow;
	_isClickNow = (GetMouseInput() & MOUSE_INPUT_LEFT);
	for (int i = 0; i < m_card.size(); i++)
	{
		m_card[i].Update();
	}
	GetMousePoint(&MouseX, &MouseY);

	/*条件掃出し*/
		// ↓山札カード
	bool isMouseOutLeft_y = MouseX >= Game::kScreenWidth / 2;
	bool isMouseOutRight_y = MouseX <= Game::kScreenWidth / 2 + 100;
	bool isMouseOutUp_y = MouseY >= Game::kScreenHeight / 2-50;
	bool isMouseOutDown_y = MouseY <= Game::kScreenHeight / 2 + 50;
	bool isInsideCard_y = isMouseOutLeft_y && isMouseOutRight_y && isMouseOutUp_y && isMouseOutDown_y;

	if (isInsideCard_y)
	{
		if ((_isClickBefore == false) && (_isClickNow == true))
		{
			Card card;				// 新しくCard型の変数を宣言(push_backに追加する時にしか使わない)
			card.Init();			// 初期化するよ
			m_card.push_back(card);	// 今ある配列の後ろに一つ要素を追加する
									// Card型の変数を入れている理由は、m_cardはcard型の動的配列で、Card型の変数を入れてあげることで、もう一つcardを用意する

		}
	}
	//	DrawBox(Game::kScreenWidth / 2, Game::kScreenHeight / 2-50, Game::kScreenWidth / 2 + 100, Game::kScreenHeight / 2 + 50, GetColor(255, 255, 255), true);
	int drawCount = 0;	// 消されていないならカウントをする
	bool _isDeleteCard = false;	// このフレーム（ワンクリック）でカードが消されたかどうか	←　一回のクリックで一枚だけ消すようにする変数
	// ↑ワンフレームでしか使わないからここで宣言して良き
	for (int i = 0; i < m_card.size(); i++)	// 手札を並ばせる
	{
		if (!m_card[i].GetCard())continue;	// カードが存在してなかったら次のループに移動

		int cardPosX = 100 * (drawCount % kCardWidthMaxCount) +50;
		int cardPosY = Game::kScreenHeight / 2 + 100 * (drawCount / kCardWidthMaxCount) +50;

		// ↓手札カード
		bool isMouseOutLeft = MouseX >= cardPosX;//カードの左側より内側にマウスがいる
		bool isMouseOutRight = MouseX <= cardPosX + m_card[i].GetCardWidth();
		bool isMouseOutUp = MouseY >= cardPosY;
		bool isMouseOutDown = MouseY <= cardPosY + m_card[i].GetCardHeight();
		bool isInsideCard = isMouseOutLeft && isMouseOutRight && isMouseOutUp && isMouseOutDown;	// マウスカーソルがカードの上に乗っているとき

		// ↓手札
		//上下左右どちらにも出ていない(カード内にマウスポインタがあるとき)
		if (isInsideCard)
		{
			cardPosY -= 10;

			bool isClickThisFrame = !_isClickBefore && _isClickNow;	// このフレームでクリックされた

			if (isClickThisFrame && _isDeleteCard == false)
			{
				// カードを無効にする
				m_card[i].SetCard(false); // m_card[i]に引数をぶち込む
				_isDeleteCard = true;
			}
		}
		m_card[i].SetDrawPos(cardPosX, cardPosY);
		drawCount++;
		
	}
}

void CardManager::Draw()
{
	

	DrawExtendGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2 - 50, Game::kScreenWidth / 2 + 100, Game::kScreenHeight / 2 + 50, m_graphDeck, true);	// 山札描画

	for (int i = 0; i < m_card.size(); i++)
	{
		m_card[i].Draw();
		DrawFormatString(m_card[i].GetDrawPosX()+50, m_card[i].GetDrawPosY()+50,GetColor(255, 0, 0), "%d", i);
		
	}

		
	
	
	
	
	
	
	
}
