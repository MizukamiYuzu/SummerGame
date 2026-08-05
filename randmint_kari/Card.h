#pragma once
#include <vector>

class Card
{
public:
	Card();
	~Card();

	void Init();
	void End();
	void Update();
	void Draw();

	
	
	void SetHandleHand(int handleHand) { m_graphHand = handleHand; }	// 手札のハンドル

	bool GetCard() { return m_isCard; }	// 戻り値を渡す関数
	void SetCard(bool card) { m_isCard = card; }	// 引数を変数に代入する関数

	void SetDrawPos(int x, int y) { m_drawPosX = x; m_drawPosY = y; }
	int GetDrawPosX() { return m_drawPosX; }
	int GetDrawPosY() { return m_drawPosY; }
	int GetCardWidth();
	int GetCardHeight();

private:
	
	int m_graphHand;	// 手札のハンドル変数

	int m_mouseX;			// マウスのX座標取得するための変数
	int m_mouseY;			// マウスのY座標取得するための変数

	int m_drawPosX;	// カードマネージャーからカードのX座標を受け取るための変数
	int m_drawPosY; // カードマネージャーからカードのY座標を受け取るための変数

	int m_playerCardPosX;

	bool m_isCard;	// 自分がいるかいないか

	//カードの種類

	//効果量

	//効果テキスト

};

