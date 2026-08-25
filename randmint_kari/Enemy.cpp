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
    m_pTimer = new Timer;
    m_pMinto = new minto;
    m_pMinto->Init();
}

void Enemy::End()
{
    m_pMinto->End();
}

int Enemy::ThinkAction(const std::vector<int>& validIndices, int playerHp, int enemyHp, int mintoEnergy, const std::vector<CardEffect>& handEffects, const std::vector<CardEffect>& rules)
{
    if (!m_pTimer->IsTimeOver())
    {
        return -1;
    }
    m_pTimer->SetReset(60);



    // 使えるカード一覧の中からランダムに1つ選んでその番号を返す
    // GetRandで0～validIndicesの要素から大きさの間から選ぶ
    // 選んだ数の要素番号にアクセスし要素をrandomIndexに代入する    <- 要素はリストに入っている中身のこと、要素番号は個々の箱を指す数字
    // validIndices.size() -1で-1をする理由は、validIndices.size()で返されるのは要素数なので、
    // 0~4の要素番号があったとするなら要素数は5,要素番号5はないため-1をしてあげる必要がある
    // ただ要素番号の最大値(上の例を使用するなら要素番号は5)のときはスキップをしたいためそのまま使用する
    int randomIndex = GetRand(validIndices.size());
    if (randomIndex == validIndices.size())
    {
        return -2;  // スキップ
    }
    return validIndices[randomIndex];

    // 何番目のカードを返すか
    int bestIndex = -2; // デフォルトはスキップにするため、-2にしておく
    // 
    int maxScore = -999;    // -999にする理由は…
                            // この後にif (score > maxScore)の判定があり、
                            // 1枚目の時に
                            // もし、scoreが-50になった時でも、
                            // maxScoreにscoreを代入することができるため
                            // 
    for (int idx : validIndices)    // validIndex分繰り返す
    {
        // CardEffect型(動的配列)で中は手札の中身1枚のデータが入っている
        const auto& effect = handEffects[idx];  // const auto& …
                                                // auto& <- これは変数宣言の型を右辺の型にしてくれる
                                                // auto& effect = handEffect
                                                // auto& (右辺がCardEffect型のhandEffectであるからCardEffectにするかあ)
                                                // CardEffect effect = handEffect;
                                                //    
        int score = 0;
        if (effect.GetEffect() == CardEffect::Effect::Damage)   // Damage <- エフェクトカードであれば
        {
            int expectedDmg = effect.GetValue();
            if(expectedDmg == 0) expectedDmg = (effect.GetRandStart() + effect.GetRandStart() / 2); // GetValueがゼロになる理由は、カードが手札にあって未使用なため、まだGetValueに値が入ってない
            
            if (playerHp - expectedDmg <= 0)    // 手札にあるカードによって相手のHPがゼロになるなら
            {
                score += 1000;  
            }
            else
            {
                score += expectedDmg;   // なぜスコアにプラスするかというと、
                                        //一撃ダメージ入れれない場合、このカードはこのぐらい役立つよっていうのをスコアに代入してあげる
                                        // 
            }
        }
        else if (effect.GetEffect() == CardEffect::Effect::Heal)
        {
            int expectedHeal = effect.GetValue();
            if (expectedHeal == 0) expectedHeal = (effect.GetRandStart() + effect.GetRandStart() / 2);

            if (enemyHp <= 30)
            {
                // 自分のHPが低いときほど評価アップ
                score += 500 + expectedHeal;    
                
            }
            else
            {
                score += expectedHeal / 2;  // ピンチじゃないときは回復カードの価値を半減にする
            }
        }
        else if (effect.GetEffect() == CardEffect::Effect::Plant)
        {
            if (m_pMinto->GetPlant() == false)  // ミントが植えられてなければ
            {
                score += 500;
            }
            score += 0;
        }
        else if (effect.GetEffect() == CardEffect::Effect::Grow)
        {
            int expectedMinto = effect.GetValue();
            if (expectedMinto == 0) expectedMinto = (effect.GetRandStart() + effect.GetRandFinish() / 2);
            if (m_pMinto->GetPlant() == true) // ミントが植えられてたら
            {
                if (m_pMinto->GetGrow() - expectedMinto <= 0) // 手札のカードがミントを育てることが可能であれば
                {
                    score += 1000;
                }
                else
                {
                    score += expectedMinto;
                }
            }
        }
        else if (effect.GetEffect() == CardEffect::Effect::Wither)
        {
            if (m_pMinto->GetGrow() >= 70)  // ミントが育つのに必要なエネルギーが少なかったら
            {
                score += 1000;
            }
            else
            {
                score += 20;
            }
        }
        // ルール追加カードの評価から
    }
}

