#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

bool Timer::IsTimeOver()
{
    // タイマーを減らす
    
    if (m_timer > 0)
    {
        m_timer--;
        m_isTimeOver = false;
    }
    else
    {
        m_isTimeOver = true;
    }
    return m_isTimeOver;
}

void Timer::SetReset(int timer)
{
    m_timer = timer;
    m_isTimeOver = false;

}
