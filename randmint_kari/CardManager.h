#pragma once
#include "Card.h"
#include "CardContent.h"
#include "minto.h"
#include "TurnManager.h"
#include "Player.h"
#include "Enemy.h"
#include "timer.h"
#include <vector>


class CardEffect;
class Player;
class Enemy;
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

	// 描画ハンドル
	void SetHandleDeck(int handleDeck) { m_graphDeckHandle = handleDeck; }	// 山札のハンドル
	void SteHandleSkip(int skipHandle) { m_graphSkipHandle = skipHandle; }	// スキップのハンドル


	
	//カードを使う処理
	void UseCard(Player* target, Player* mySelf, CardEffect& cardEffect);

	bool GetDead() { return m_isDead; }

	bool GetGrow() { return m_isGrow; }

	bool GetWin() { return m_isWin; }

	bool GetDrewCard() { return m_isPlayerDrewCard; }

	void CheckRule(CardEffect& cardEffect);

	// プレイヤーの勝利かどうか
	bool GetWhoWin() { return m_isMyWin; }

private:
	// 画像の場合は
	int m_graphDeckHandle;		// 山札の画像ハンドル
	int m_graphSkipHandle;		// スキップの画像
	int m_cardGraphHandle;	// 手札のハンドル変数
	int m_cardBackGraphHandle;
	
	int m_fontHandle;
	int m_fontRuleHandle;
	int m_fontTitleRuleHandle;


	int m_mouseX;			// マウスのX座標取得するための変数
	int m_mouseY;			// マウスのY座標取得するための変数


	int m_playerCardPosX;

	int m_selectCardIndex = -1;	// マウスが乗っているカードの番号

	

	bool m_isClickBefore;	// 1フレーム前にクリックされたかどうか
	bool m_isClickNow;		// 現在クリックされているか

	bool m_isDead = false;
	
	bool m_isGrow = false;

	bool m_isWin = false;

	bool m_isPlayerDrewCard = false;	// そのターンにカードが引かれたかどうか
	bool m_isEnemyDrewCard = false;

	bool m_isDrewCardDeck = false;	// 山札からカードを引いたかどうか

	bool m_isMyHandFull = false;	// 手持ちのカードがいっぱいかどうか

	bool m_isEnemyHandFull = false;

	bool m_isMyWin = false;	// プレイヤーが勝利したかどうか
	

	

	//プレイヤー
	Player* m_player;
	//敵
	Enemy* m_enemy;	// プレイヤーを継承した子クラスEnemy

	// ミント
	minto* m_pMinto;

	// ターンマネージャー
	TurnManager* m_pTurnManager;

	// タイマー
	Timer* m_pTimer;



	std::vector<CardEffect> m_myCardEffect;	// 自分のカードの効果が入る動的配列
	std::vector<CardEffect> m_enemyCardEffect;	// カードの効果が入る動的配列

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

