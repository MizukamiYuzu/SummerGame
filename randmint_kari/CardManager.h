#pragma once
#include "Card.h"
#include "CardContent.h"
#include "minto.h"
#include "TurnManager.h"
#include <vector>


class CardEffect;
class Player;
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

	
	//カードを使う処理
	void UseCard(Player* target, CardEffect& cardEffect);

	bool GetDead() { return m_isDead; }

	bool GetGrow() { return m_isGrow; }

	bool GetWin() { return m_isWin; }

	void CheckRule(CardEffect& cardEffect);

private:
	// 画像の場合は
	int m_graphDeck;	// 山札の画像ハンドル

	int m_mouseX;			// マウスのX座標取得するための変数
	int m_mouseY;			// マウスのY座標取得するための変数


	int m_playerCardPosX;

	bool m_isClickBefore;	// 1フレーム前にクリックされたかどうか
	bool m_isClickNow;		// 現在クリックされているか

	bool m_isDead = false;
	
	bool m_isGrow = false;

	bool m_isWin = false;

	

	//プレイヤー
	Player* m_player;
	//敵
	Player* m_enemy;

	// ミント
	minto* m_pMinto;

	// ターンマネージャー
	TurnManager* m_pTurnManager;



	std::vector<CardEffect> m_cardEffect;	// カードの効果が入る動的配列

	//ルール
	std::vector<CardEffect> m_rules;

	CardContent* m_pCardContent;

	std::vector<Card> m_MyCard;		// カードの持ってるか持ってないかの配列
									// vectorは動的配列
									// 
	std::vector<Card> m_EnemyCard;

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

