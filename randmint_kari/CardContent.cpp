#include "CardContent.h"
#include "CardEffect.h"

CardContent::CardContent() :
	m_OverallProbability(0),
	m_ContentProbability(0),
	m_cardContent("")
{
	
}

CardContent::~CardContent()
{
}

void CardContent::Init()
{
}

void CardContent::End()
{
}

void CardContent::Update()
{
	
}

void CardContent::Draw()
{
	/*DrawFormatString(50, 50, GetColor(255, 0, 0), "m_randStart:%d", m_randStart);
	DrawFormatString(50, 70, GetColor(255, 0, 0), "m_randFinish:%d", m_randFinish);
	DrawFormatString(50, 90, GetColor(255, 0, 0), m_cardContent.c_str());
	DrawFormatString(50, 110, GetColor(255, 0, 0), "m_OverallProbability:%d", m_OverallProbability);*/
}
//山札からカード引く
CardEffect CardContent::CreateCardEffect()
{
	CardEffect cardEffect;

	m_OverallProbability = GetRand(100);

	if (m_OverallProbability <= 10)	// 10%の確率
	{
		// ミントに関するカード
		m_cardTitle = "ミント";	
		cardEffect.SetTitle(m_cardTitle);
		m_ContentProbability = GetRand(1);
		if (m_ContentProbability <= 0)
		{
			m_cardContent = "ミントを植える";

			//植える効果を持つカードだよ
			cardEffect.SetEffect(CardEffect::Effect::Plant);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else
		{
			m_cardContent = "ミントを枯らす";

			//枯らす効果を持つカードだよ
			cardEffect.SetEffect(CardEffect::Effect::Wither);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
	}
	else if (m_OverallProbability <= 30)	// 20%の確率
	{
		// ルールの変更
		m_cardTitle = "ルール変更";
		cardEffect.SetTitle(m_cardTitle);

		//ルール追加効果
		cardEffect.SetEffect(CardEffect::Effect::Rule);

		m_ContentProbability = GetRand(9);
		if (m_ContentProbability <= 0)
		{
			m_variable = 3;
			m_cardContent = "自分のHPが"+std::to_string(m_variable)+"の倍数になったら勝利";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::MyMltiWin);
			//効果量
			cardEffect.SetValue(m_variable);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 1)
		{
			m_variable = 4;
			m_cardContent = "自分のHPが" + std::to_string(m_variable) + "の倍数になったら勝利";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::MyMltiWin);
			//効果量
			cardEffect.SetValue(m_variable);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 2)
		{
			m_variable = 6;
			m_cardContent = "相手のHPが" + std::to_string(m_variable) + "の倍数になったら勝利";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::YourMltiWin);
			//効果量
			cardEffect.SetValue(m_variable);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 3)
		{
			m_rand = GetRand(100);
			while (m_rand == 0)	m_rand = GetRand(100);
			m_cardContent = "自分のHPが残り" + std::to_string(m_rand) + "になったら勝利";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::MySameWin);
			//効果量
			cardEffect.SetValue(m_rand);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 4)
		{
			m_rand = GetRand(100);
			m_cardContent = "相手のHPが残り" + std::to_string(m_rand) + "になったら勝利";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::YourSameWin);
			//効果量
			cardEffect.SetValue(m_rand);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 5)
		{
			m_variable = 9;
			m_cardContent = "相手のHPが" + std::to_string(m_variable) + "の倍数になったら勝利";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::YourMltiWin);
			//効果量
			cardEffect.SetValue(m_variable);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 6)
		{
			m_rand = GetRand(100);
			while (m_rand == 0)	m_rand = GetRand(100);
			m_cardContent = "ミントのエネルギーが" + std::to_string(m_rand) + "になったらミントが育つ";

			
			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::MintoSameGrow);
			//効果量
			cardEffect.SetValue(m_rand);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 7)
		{
			m_variable = 8;
			m_cardContent = "ミントのエネルギーが" + std::to_string(m_variable) + "の倍数になったら勝利";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::MintoMltiWin);
			//効果量
			cardEffect.SetValue(m_variable);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 8)
		{
			m_variable = 12;
			m_cardContent = "ミントのエネルギーが" + std::to_string(m_variable) + "の倍数になったら勝利";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::MintoMltiWin);
			//効果量
			cardEffect.SetValue(m_variable);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 9)
		{
			m_variable = 25;
			m_cardContent = "ミントのエネルギーが" + std::to_string(m_variable) + "の倍数になったら勝利";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::MintoMltiWin);
			//効果量
			cardEffect.SetValue(m_variable);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 10)
		{
			m_cardContent = "勝利条件の1番古い条件を削除する";

			//ルールの種類
			cardEffect.SetRuleEffect(CardEffect::RuleEffect::Delete);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}

	}
	else if (m_OverallProbability <= 60)	// 30%の確率
	{
		// ミント
		m_cardTitle = "ミント";
		cardEffect.SetTitle(m_cardTitle);

		m_ContentProbability = GetRand(100);

		if (m_ContentProbability <= 49)	// 49%
		{
			m_rand = GetRand(50);
			while (m_rand == 0 || m_rand == 100)	m_rand = GetRand(100);
			m_cardContent = "ミントにエネルギーを" + std::to_string(m_rand) + "与える";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Grow);
			//効果量
			cardEffect.SetValue(m_rand);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 50)	// 1%
		{
			m_rand = GetRand(100);
			while (m_rand == 0 || m_rand == 100)	m_rand = GetRand(100);
			m_cardContent = "ミントにエネルギーを" + std::to_string(m_rand) + "与える";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Grow);
			//効果量
			cardEffect.SetValue(m_rand);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 99)	// 49%
		{
			m_randStart = GetRand(3);
			m_randFinish = GetRand(5);
			while (m_randFinish <= m_randStart) m_randFinish = GetRand(10);
			m_cardContent = "ミントに" + std::to_string(m_randStart * 10) + "～" + std::to_string(m_randFinish * 10) + "のランダな数のエネルギーを与える";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Grow);
			//はじめとおわり
			cardEffect.SetRandStart(m_randStart*10);
			cardEffect.SetRandFinish(m_randFinish*10);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 100)	// 1%
		{
			m_randStart = GetRand(5);
			m_randFinish = GetRand(10);
			while (m_randFinish <= m_randStart) m_randFinish = GetRand(10);
			m_cardContent = "ミントに" + std::to_string(m_randStart * 10) + "～" + std::to_string(m_randFinish * 10) + "のランダな数のエネルギーを与える";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Grow);
			//はじめとおわり
			cardEffect.SetRandStart(m_randStart * 10);
			cardEffect.SetRandFinish(m_randFinish * 10);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
	}
	else
	{
		

		m_ContentProbability = GetRand(100);
		if (m_ContentProbability <= 30)	// 30%
		{
			// 回復
			m_cardTitle = "回復";
			cardEffect.SetTitle(m_cardTitle);

			m_rand = GetRand(50);
			while (m_rand == 0 || m_rand == 100)	m_rand = GetRand(100);
			m_cardContent = "自分のHPを" + std::to_string(m_rand) + "回復する";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Heal);
			//効果量
			cardEffect.SetValue(m_rand);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		if (m_ContentProbability <= 40)	// 20%
		{
			// 回復
			m_cardTitle = "回復";
			cardEffect.SetTitle(m_cardTitle);

			m_rand = GetRand(100);
			while (m_rand == 0 || m_rand == 100)	m_rand = GetRand(100);
			m_cardContent = "自分のHPを" + std::to_string(m_rand) + "回復する";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Heal);
			//効果量
			cardEffect.SetValue(m_rand);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 49)	// 9%
		{
			// 回復
			m_cardTitle = "回復";
			cardEffect.SetTitle(m_cardTitle);

			m_randStart = GetRand(3);
			m_randFinish = GetRand(5);
			while (m_randFinish <= m_randStart) m_randFinish = GetRand(10);
			m_cardContent = std::to_string(m_randStart * 10) + "～" + std::to_string(m_randFinish * 10) + "のランダムな数回復する";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Heal);
			//はじめとおわり
			cardEffect.SetRandStart(m_randStart*10);
			cardEffect.SetRandFinish(m_randFinish*10);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 50)	// 1%
		{
			// 回復
			m_cardTitle = "回復";
			cardEffect.SetTitle(m_cardTitle);

			m_randStart = GetRand(5);
			m_randFinish = GetRand(10);
			while (m_randFinish <= m_randStart) m_randFinish = GetRand(10);
			m_cardContent = std::to_string(m_randStart * 10) + "～" + std::to_string(m_randFinish * 10) + "のランダムな数回復する";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Heal);
			//はじめとおわり
			cardEffect.SetRandStart(m_randStart * 10);
			cardEffect.SetRandFinish(m_randFinish * 10);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 80)	// 30%
		{
			// ダメージ
			m_cardTitle = "ダメージ";
			cardEffect.SetTitle(m_cardTitle);

			m_rand = GetRand(50);
			while (m_rand == 0 || m_rand == 100)	m_rand = GetRand(100);
			m_cardContent = "相手に" + std::to_string(m_rand) + "ダメージを与える";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Damage);
			//効果量
			cardEffect.SetValue(m_rand);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 90)	// 10%
		{
			// ダメージ
			m_cardTitle = "ダメージ";
			cardEffect.SetTitle(m_cardTitle);

			m_rand = GetRand(100);
			while (m_rand == 0 || m_rand == 100)	m_rand = GetRand(100);
			m_cardContent = "相手に" + std::to_string(m_rand) + "ダメージを与える";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Damage);
			//効果量
			cardEffect.SetValue(m_rand);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 9)	// 9%
		{
			// ダメージ
			m_cardTitle = "ダメージ";
			cardEffect.SetTitle(m_cardTitle);

			m_randStart = GetRand(3);
			m_randFinish = GetRand(5);
			while (m_randFinish <= m_randStart) m_randFinish = GetRand(10);
			m_cardContent = "相手に" + std::to_string(m_randStart * 10) + "～" + std::to_string(m_randFinish * 10) + "のランダムな数のダメージを与える";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Damage);
			//はじめとおわり
			cardEffect.SetRandStart(m_randStart*10);
			cardEffect.SetRandFinish(m_randFinish*10);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
		else if (m_ContentProbability <= 100)	// 1%
		{
			// ダメージ
			m_cardTitle = "ダメージ";
			cardEffect.SetTitle(m_cardTitle);

			m_randStart = GetRand(5);
			m_randFinish = GetRand(10);
			while (m_randFinish <= m_randStart) m_randFinish = GetRand(10);
			m_cardContent = "相手に" + std::to_string(m_randStart * 10) + "～" + std::to_string(m_randFinish * 10) + "のランダムな数のダメージを与える";

			//カードの効果
			cardEffect.SetEffect(CardEffect::Effect::Damage);
			//はじめとおわり
			cardEffect.SetRandStart(m_randStart * 10);
			cardEffect.SetRandFinish(m_randFinish * 10);
			//テキスト
			cardEffect.SetContent(m_cardContent);
		}
	}

	return cardEffect;
}
