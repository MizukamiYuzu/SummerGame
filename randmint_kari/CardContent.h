#pragma once
#include <vector>
#include <string>
#include "Dxlib.h"

class CardEffect;
class CardContent
{
public:
	CardContent();
	~CardContent();

	void Init();
	void End();
	void Update();
	void Draw();


	//ドローしたカードの作成
	CardEffect CreateCardEffect();


private:
	int m_OverallProbability;	// 全体の確率
	int m_ContentProbability;	// 細かい内容の確率
	int m_rand;					// カード内容の確率	 <- 例:自分の体力が1~5のランダムな数...
	int m_variable;				// カード内容に使う確率(倍数)  <- 例:自分の体力が〇の倍数になったら...
	int m_randStart;			// カード内容(〇～〇のランダムな数)の最小値
	int m_randFinish;			// カード内容(〇～〇のランダムな数)の最大値

	// 確率10%	<- 全体の確率
	//"ミントを植える",		//確率50% 　<- 細かい内容の確率
	//"ミントを枯らす",		//確率50%
	// 確率20%
	//"ルールを1個追加する", 
	//"ルールを1個削除する", 
	// 確率30%
	//"ミントにエネルギーを与える", 
	// 確率40%
	//"相手にダメージを与える", 
	//"HP回復", 


//	std::vector<std::string> content;
	std::string m_cardContent;

	// カードのタイトルを保存する変数
	std::string m_cardTitle;

};

