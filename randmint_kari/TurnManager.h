#pragma once
class TurnManager
{
public:

	TurnManager();
	~TurnManager();


	bool GetMyTurn()const { return m_myTurn; }
	void SetMyTurn(bool turn) { m_myTurn = turn; }

private:

	bool m_myTurn = false;	// ターンを確認する変数

	
};

