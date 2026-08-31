#pragma once
class Timer
{
public:
	Timer();
	~Timer();


	
	bool IsTimeOver();
	void SetReset(int timer);
	int GetTimer() { return m_timer; }
	

private:
	int m_timer = 60;

	bool m_isTimeOver = false;	// 考えている最中
};

