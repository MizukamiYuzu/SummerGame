#pragma once
class Timer
{
public:
	Timer();
	~Timer();


	
	bool EnemyThinkTimer();

private:
	int m_thinkTimer = 60;

	bool m_thinking = false;	// 考えている最中
};

