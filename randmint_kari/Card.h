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
	void Draw(int PlayerCardPosX_s, int y1, int PlayerCardPosX_f, int y2);


	
	void SetHandleHand(int handleHand) { m_graphHand = handleHand; }	// 手札のハンドル

private:
	
	int m_graphHand;	// 手札のハンドル変数

	int MouseX;			// マウスのX座標取得するための変数
	int MouseY;			// マウスのY座標取得するための変数

	int PlayerCardPosX;

	bool m_isCard;



};

