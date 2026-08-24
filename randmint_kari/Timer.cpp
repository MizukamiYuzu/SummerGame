#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

bool Timer::EnemyThinkTimer()
{
    // タイマーを減らす(考え中なら-1を返す)
    m_thinkTimer--;
    if (m_thinkTimer > 0)
    {
        return -1;
    }
    else
    {
        m_thinking = false;
    }

}
