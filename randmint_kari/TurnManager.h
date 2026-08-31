#pragma once
class TurnManager
{
public:

	TurnManager();
	~TurnManager();


	bool GetMyTurn()const { return m_myTurn; }

	bool GetEnemyTurn()const { return m_enemyTurn; }
	
	void SetMyTurn(bool turn) { m_myTurn = turn; }

	void SetEnemyTurn(bool turn) { m_enemyTurn = turn; }

private:

	bool m_myTurn = false;	// ターンを確認する変数

	bool m_enemyTurn = false;

	
};

