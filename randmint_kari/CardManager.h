#pragma once
#include "Card.h"
#include "Game.h"
#include <vector>

class CardManager
{
public:
	CardManager();
	~CardManager();

	void Init();
	void End();

	void Update();
	void Draw();

	void SetHandleDeck(int handleDeck) { m_graphDeck = handleDeck; }	// 山札のハンドル

private:

	int m_graphDeck;	// 山札のハンドル変数

	int MouseX;			// マウスのX座標取得するための変数
	int MouseY;			// マウスのY座標取得するための変数

	int PlayerCardPosX;

	std::vector<Card> m_card;		// カードの持ってるか持ってないかの配列

	// カード型の配列	←クラスのデータをいくつか持ってる

//	クラス名
//	{
//		メンバー名1;
//		メンバー名2;
//		・・・
//
//	}
// 
// 	↑いっぱいあるよ！
};

