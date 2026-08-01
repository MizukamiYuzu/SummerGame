#include "CardContent.h"


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
	DrawFormatString(50, 50, GetColor(255, 0, 0), "%d", m_randStart);
	DrawFormatString(50, 70, GetColor(255, 0, 0), "%d", m_randFinish);
}

std::string CardContent::GetContent()
{
	m_OverallProbability = GetRand(100);
	if (m_OverallProbability <= 10)
	{
		m_ContentProbability = GetRand(1);
		if (m_ContentProbability <= 0)
		{
			m_cardContent = "ミントを植える";
		}
		else
		{
			m_cardContent = "ミントを枯らす";
		}
	}
	if (m_OverallProbability <= 30)
	{
		m_ContentProbability = GetRand(9);
		if (m_ContentProbability <= 0)
		{
			m_variable = 3;
			m_cardContent = "自分のHPが%dの倍数になったら勝利",m_variable;
		}
		if (m_ContentProbability <= 1)
		{
			m_variable = 4;
			m_cardContent = "自分のHPが%dの倍数になったら勝利", m_variable;
		}
		if (m_ContentProbability <= 2)
		{
			m_variable = 6;
			m_cardContent = "相手のHPが%dの倍数になったら勝利", m_variable;
		}
		if (m_ContentProbability <= 3)
		{
			m_rand = GetRand(100);
			m_cardContent = "自分のHPが残り%dになったら勝利", m_rand;
		}
		if (m_ContentProbability <= 4)
		{
			m_rand = GetRand(100);
			m_cardContent = "相手のHPが残り%dになったら勝利", m_rand;
		}
		if (m_ContentProbability <= 5)
		{
			m_variable = 9;
			m_cardContent = "相手のHPが%dの倍数になったら勝利", m_variable;
		}
		if (m_ContentProbability <= 6)
		{
			m_rand = GetRand(100);
			m_cardContent = "ミントのエネルギーが%dになったらミントが育つ", m_rand;
		}
		if (m_ContentProbability <= 7)
		{
			m_variable = 8;
			m_cardContent = "ミントのエネルギーが%dの倍数になったら勝利", m_variable;
		}
		if (m_ContentProbability <= 8)
		{
			m_variable = 12;
			m_cardContent = "ミントのエネルギーが%dの倍数になったら勝利", m_variable;
		}
		if (m_ContentProbability <= 9)
		{
			m_variable = 25;
			m_cardContent = "ミントのエネルギーが%dの倍数になったら勝利", m_variable;
		}
		if (m_ContentProbability <= 10)
		{
			m_cardContent = "勝利条件の1番古い条件を削除する", m_rand;
		}

	}
	if (m_OverallProbability <= 60)
	{
		m_ContentProbability = GetRand(1);
		if (m_ContentProbability <= 0)
		{
			m_rand = GetRand(100);
			m_cardContent = "ミントにエネルギーを%d与える", m_rand;
		}
		if (m_ContentProbability <= 1)
		{
			m_randStart = GetRand(50 / 10);
			m_randFinish = GetRand(100 / 10);
			while (m_randFinish <= m_randStart) m_randFinish = GetRand(100 / 10);
			m_cardContent = "ミントに%d～%dのランダな数のエネルギーを与える", m_randStart, m_randFinish;
		}
	}
	else
	{
		m_ContentProbability = GetRand(3);
		if (m_ContentProbability <= 0)
		{
			m_rand = GetRand(100);
			m_cardContent = "自分のHPを%d回復する", m_rand;
		}
		if (m_ContentProbability <= 1)
		{
			m_randStart = GetRand(50 / 10);
			m_randFinish = GetRand(100 / 10);
			while (m_randFinish <= m_randStart) m_randFinish = GetRand(100 / 10);
			m_cardContent = "%d～%dのランダな数回復する", m_randStart, m_randFinish;
		}
		if (m_ContentProbability <= 2)
		{
			m_rand = GetRand(100);
			m_cardContent = "相手に%dダメージを与える", m_rand;
		}
		if (m_ContentProbability <= 3)
		{
			m_randStart = GetRand(50 / 10);
			m_randFinish = GetRand(100 / 10);
			while (m_randFinish <= m_randStart) m_randFinish = GetRand(100 / 10);
			m_cardContent = "相手に%d～%dのランダムな数のダメージを与える", m_randStart, m_randFinish;
		}
	}

	return m_cardContent;
}
