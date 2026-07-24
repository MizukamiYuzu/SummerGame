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

	int handNum;

	int PlayerCardPosX;

	bool _isClickBefore;	// 1フレーム前にクリックされたかどうか
	bool _isClickNow;		// 現在クリックされているか

	std::vector<Card> m_card;		// カードの持ってるか持ってないかの配列
//	std::vector<クラス名> 変数名;

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

