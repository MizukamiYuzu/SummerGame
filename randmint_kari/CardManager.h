#pragma once
#include "Card.h"
#include "Game.h"
#include <vector>

class CardManager
{
public:
	// コンストラクタ(強制初期化)
	CardManager();
	// デストラクタ(メモリから消す)
	~CardManager();

	// 任意初期化(自分がやりたいときにする初期化)
	void Init();
	// 終了処理(メモリから消したくはないけど、ゲーム上から出しときたいとき。自分が終了させたいときにさせることができる)
	void End();

	// 更新
	void Update();
	// 描画
	void Draw();

	// セッター(変更したいときに使う)
	// ゲッター(値を受け取りたいときに使う)
	void SetHandleDeck(int handleDeck) { m_graphDeck = handleDeck; }	// 山札のハンドル


private:
	// 画像の場合は
	int m_graphDeck;	// 山札の画像ハンドル

	int MouseX;			// マウスのX座標取得するための変数
	int MouseY;			// マウスのY座標取得するための変数


	int PlayerCardPosX;

	bool _isClickBefore;	// 1フレーム前にクリックされたかどうか
	bool _isClickNow;		// 現在クリックされているか

	std::vector<Card> m_card;		// カードの持ってるか持ってないかの配列
									// vectorは動的配列
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

