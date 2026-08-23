#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
    m_thinkTimer = 60;
}

int Enemy::ThinkAction(const std::vector<int>& validIndices, int playerHp, int enemyHp, int mintoEnergy)
{
    // タイマーを減らす(考え中なら-1を返す)
    m_thinkTimer--;
    if (m_thinkTimer > 0)
    {
        return -1;
    }

    // タイマーリセット
    m_thinkTimer = 60;

    // 使えるカード一覧の中からランダムに1つ選んでその番号を返す
    // GetRandで0～validIndicesの要素から大きさの間から選ぶ
    // 選んだ数の要素番号にアクセスし要素をrandomIndexに代入する    <- 要素はリストに入っている中身のこと、要素番号は個々の箱を指す数字
    // validIndices.size() -1で-1をする理由は、validIndices.size()で返されるのは要素数なので、
    // 0~4の要素番号があったとするなら要素数は5,要素番号5はないため-1をしてあげる必要がある
    int randomIndex = GetRand(validIndices.size() -1);
    return validIndices[randomIndex];
}
