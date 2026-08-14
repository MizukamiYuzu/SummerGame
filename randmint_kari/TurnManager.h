#pragma once
class TurnManager
{
public:

	TurnManager();
	~TurnManager();

	void Init();
	void End();
	void Update();
	void Draw();

	enum class Player	// プレイヤーの情報
	{
		Player1,	// 自分のデータ
		Player2		// 敵のデータ
	};

	bool GetMyTurn()const { return m_myTurn; }
	void SetMyTurn(bool turn) { m_myTurn = turn; }

private:

	bool m_myTurn;	// ターンを確認する変数

	
};

