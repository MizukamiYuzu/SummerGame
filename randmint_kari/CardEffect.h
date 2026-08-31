#pragma once
#include <string>
/// <summary>
/// カードの効果を保持しておくクラス
/// </summary>
class CardEffect
{
public:
	CardEffect();
	~CardEffect();
	enum class Effect
	{
		None,		//空
		Damage,
		Heal,
		Plant,		//ミントを植える
		Wither,		//ミントを枯らす
		Grow,		//ミントにエネルギーを与える
		Rule		//ルールに関する効果
	};
	enum class RuleEffect
	{
		None,			//空
		MyMltiWin,		//自分のHPがN倍なら勝利
		YourMltiWin,	//相手のHPがN倍なら勝利
		MySameWin,		//自分のHPがNなら勝利
		YourSameWin,	//相手のHPがNなら勝利
		MintoSameGrow,	//ミントのエネルギーがNなら育つ
		MintoMltiWin,	//ミントのエネルギーがN倍なら勝利
		Delete			//古い条件の削除
	};

	//カード効果
	Effect GetEffect()const { return m_effect; }
	void SetEffect(Effect eff) { m_effect = eff; }

	// カードタイトル
	std::string GetTitle()const { return m_title; }
	void SetTitle(std::string title) { m_title = title; }

	//効果量
	int GetValue()const { return m_value; }
	void SetValue(int value) { m_value = value; }

	//効果テキスト
	std::string GetContent()const { return m_content; }
	void SetContent(std::string text) { m_content = text; }

	//ルール
	RuleEffect GetRuleEffect()const { return m_ruleEffect; }
	void SetRuleEffect(RuleEffect eff) { m_ruleEffect = eff; }

	//ランダム始め
	int GetRandStart()const { return m_randStart; }
	void SetRandStart(int value) { m_randStart = value; }
	//ランダム終わり
	int GetRandFinish()const { return m_randFinish; }
	void SetRandFinish(int value) { m_randFinish = value; }

private:
	//カードの効果
	Effect m_effect = Effect::None;

	// カードタイトル
	std::string m_title = "";

	//効果量
	int m_value = 0;

	//効果テキスト
	std::string m_content = "";

	//ルール専用変数
	RuleEffect m_ruleEffect = RuleEffect::None;

	//ランダム始め
	int m_randStart = 0;

	//ランダム終わり
	int m_randFinish = 0;
};

