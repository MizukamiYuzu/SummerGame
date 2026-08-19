#include "Dxlib.h"
#include "CardManager.h"
#include "CardEffect.h"
#include "Game.h"
#include "Player.h"

namespace
{
	constexpr int kFirstHandNum = 4;	// 初期の手札枚数
	constexpr int kCardWidthMaxCount = 11;
}

CardManager::CardManager() :
	m_graphDeck(-1),
	m_mouseX(0),
	m_mouseY(0),
	m_playerCardPosX(0),
	m_isClickBefore(false),
	m_isClickNow(false)
{
}

CardManager::~CardManager()
{
}

void CardManager::Init()
{
	//プレイヤーと敵作成
	m_player = new Player();
	m_enemy = new Player();
	m_pTurnManager = new TurnManager();

	m_pMinto = new minto();
	m_pMinto->Init();
	m_pCardContent = new CardContent;
	m_pCardContent->Init();
	m_graphDeck = LoadGraph("data/img/deck.png");	// 山札のハンドル
	m_MyCard.resize(kFirstHandNum);
	m_EnemyCard.resize(kFirstHandNum);
	m_cardEffect.resize(kFirstHandNum);
	for (int i = 0; i < kFirstHandNum; i++)
	{
		m_MyCard[i].Init();
		m_EnemyCard[i].Init();
	}

}

void CardManager::End()
{
	m_pMinto->End();
	m_pCardContent->End();
	DeleteGraph(m_graphDeck);
	for (int i = 0; i < m_MyCard.size(); i++)	// m_card.size() <- size()で配列の数を出すことができる
	{
		m_MyCard[i].End();
	}
	for (int i = 0; i < m_EnemyCard.size(); i++)	// m_card.size() <- size()で配列の数を出すことができる
	{
		m_EnemyCard[i].End();
	}
}

void CardManager::Update()
{
	m_pMinto->Update();
	m_pCardContent->Update();
	m_isClickBefore = m_isClickNow;
	m_isClickNow = (GetMouseInput() & MOUSE_INPUT_LEFT);
	for (int i = 0; i < m_MyCard.size(); i++)
	{
		if (!m_MyCard[i].GetCard())continue;
	//	m_card[i].Update();
		//カードの効果が空なら
		if (m_cardEffect[i].GetEffect() == CardEffect::Effect::None)
		{
			//カード効果を得る
			m_cardEffect[i] = m_pCardContent->CreateCardEffect();
		}
	}
	for (int i = 0; i < m_EnemyCard.size(); i++)
	{
		if (!m_EnemyCard[i].GetCard())continue;
		if (m_cardEffect[i].GetEffect() == CardEffect::Effect::None)
		{
			//カード効果を得る
			m_cardEffect[i] = m_pCardContent->CreateCardEffect();
		}
	}
	GetMousePoint(&m_mouseX, &m_mouseY);

	{
		/*条件掃出し*/
		// ↓山札カード
		bool isMouseOutLeft_y = m_mouseX >= Game::kScreenWidth / 2;
		bool isMouseOutRight_y = m_mouseX <= Game::kScreenWidth / 2 + 100;
		bool isMouseOutUp_y = m_mouseY >= Game::kScreenHeight / 2 - 50;
		bool isMouseOutDown_y = m_mouseY <= Game::kScreenHeight / 2 + 50;
		bool isInsideCard_y = isMouseOutLeft_y && isMouseOutRight_y && isMouseOutUp_y && isMouseOutDown_y;

		//山札からカードを引いたとき
		if (isInsideCard_y)
		{
			if ((m_isClickBefore == false) && (m_isClickNow == true))
			{
				if (m_pTurnManager->GetMyTurn())
				{
					//カード作成
					Card card;				// 新しくCard型の変数を宣言(push_backに追加する時にしか使わない)
					card.Init();			// 初期化するよ
					m_MyCard.push_back(card);	// 今ある配列の後ろに一つ要素を追加する
					// Card型の変数を入れている理由は、m_cardはcard型の動的配列で、Card型の変数を入れてあげることで、もう一つcardを用意する

		//カードの効果を作成(中身は空)
					CardEffect cardEffect;
					m_cardEffect.push_back(cardEffect);
				}
				

			}
		}
		//	DrawBox(Game::kScreenWidth / 2, Game::kScreenHeight / 2-50, Game::kScreenWidth / 2 + 100, Game::kScreenHeight / 2 + 50, GetColor(255, 255, 255), true);
		int drawMyCount = 0;	// 消されていないならカウントをする
		int drawEnemyCount = 0;	// 消されていないならカウントをする
		bool _isDeleteCard = false;	// このフレーム（ワンクリック）でカードが消されたかどうか	←　一回のクリックで一枚だけ消すようにする変数
		// ↑ワンフレームでしか使わないからここで宣言して良き
		for (int i = 0; i < m_MyCard.size(); i++)	// 手札を並ばせる
		{
			if (!m_MyCard[i].GetCard())continue;	// カードが存在してなかったら次のループに移動

			int cardMyPosX = 100 * (drawMyCount % kCardWidthMaxCount) + 50;
			int cardMyPosY = Game::kScreenHeight / 2 + 100 * (drawMyCount / kCardWidthMaxCount) + 50;

			// ↓手札カード
			bool isMouseOutLeft = m_mouseX >= cardMyPosX;//カードの左側より内側にマウスがいる
			bool isMouseOutRight = m_mouseX <= cardMyPosX + m_MyCard[i].GetCardWidth();
			bool isMouseOutUp = m_mouseY >= cardMyPosY;
			bool isMouseOutDown = m_mouseY <= cardMyPosY + m_MyCard[i].GetCardHeight();
			bool isInsideCard = isMouseOutLeft && isMouseOutRight && isMouseOutUp && isMouseOutDown;	// マウスカーソルがカードの上に乗っているとき

			// ↓手札
			//上下左右どちらにも出ていない(カード内にマウスポインタがあるとき)
			if (isInsideCard)
			{
				cardMyPosY -= 10;

				bool isClickThisFrame = !m_isClickBefore && m_isClickNow;	// このフレームでクリックされた

				if (isClickThisFrame && _isDeleteCard == false)
				{
					if (m_pTurnManager->GetMyTurn())
					{
						//カードを使う処理(敵に対して)
						UseCard(m_enemy, m_cardEffect[i]);

						// カードを無効にする
						m_MyCard[i].SetCard(false); // m_card[i]に引数をぶち込む
						//m_cardContent.erase(m_cardContent.begin() + i);

						_isDeleteCard = true;
						m_pTurnManager->SetMyTurn(false);
						
					}
					
				}
			}
			m_MyCard[i].SetDrawPos(cardMyPosX, cardMyPosY);
			drawMyCount++;

		}
		for (int i = 0; i < m_EnemyCard.size(); i++)	// 手札を並ばせる
		{
			if (!m_EnemyCard[i].GetCard())continue;	// カードが存在してなかったら次のループに移動

			int cardEnemyPosX = Game::kScreenWidth-200 - (100 * (drawEnemyCount % kCardWidthMaxCount) - 50);
			int cardEnemyPosY =( Game::kScreenHeight / 2-200 -( 100 *(drawEnemyCount / kCardWidthMaxCount) -50));

			
			if (CheckHitKey(KEY_INPUT_UP))
			{
				m_pTurnManager->SetMyTurn(true);
			}

			m_EnemyCard[i].SetDrawPos(cardEnemyPosX, cardEnemyPosY);
			drawEnemyCount++;

		}
		if (m_player->GetHp() <= 0)
		{
			m_isDead = true;
		}
	}
	
	if (m_pMinto->GetGrow() >= 100)
	{
		m_isGrow = true;
	}

}

void CardManager::Draw()
{

	m_pCardContent->Draw();
	m_pMinto->Draw();
	// 山札描画
	DrawExtendGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2 - 50, Game::kScreenWidth / 2 + 100, Game::kScreenHeight / 2 + 50, m_graphDeck, true);	
	DrawFormatString(0, 64, GetColor(255, 255, 255), "TURN:%d", m_pTurnManager->GetMyTurn());
	DrawFormatString(0, 96, GetColor(255, 255, 255), "HP:%d", m_enemy->GetHp());
	// 手札描画
	for (int i = 0; i < m_MyCard.size(); i++)
	{
		m_MyCard[i].Draw();
		DrawFormatString(m_MyCard[i].GetDrawPosX() + 50, m_MyCard[i].GetDrawPosY() + 50, GetColor(255, 0, 0), "%d", i);
		//	DrawString(100, i+100, m_pCardContent->GetContent().c_str(), GetColor(255, 255, 255));
		DrawFormatString(100, i * 20, GetColor(255, 255, 255), m_cardEffect[i].GetContent().c_str());
		
	}
	for (int i = 0; i < m_EnemyCard.size(); i++)
	{
		m_EnemyCard[i].Draw();
		DrawFormatString(m_EnemyCard[i].GetDrawPosX() + 50, m_EnemyCard[i].GetDrawPosY() + 50, GetColor(255, 0, 0), "%d", i);
		//	DrawString(100, i+100, m_pCardContent->GetContent().c_str(), GetColor(255, 255, 255));
		DrawFormatString(100, i * 20, GetColor(255, 255, 255), m_cardEffect[i].GetContent().c_str());

	}

}

void CardManager::UseCard(Player* target, CardEffect& cardEffect)
{
	switch (cardEffect.GetEffect())
	{
	// ダメージ
	case CardEffect::Effect::Damage:
		if (cardEffect.GetRandStart() == 0 && cardEffect.GetRandFinish() == 0)
		{
			//固定値
			target->Damage(cardEffect.GetValue());
		}
		else
		{
			//ランダムなダメージ
			target->Damage(MyRandom(cardEffect.GetRandStart(), cardEffect.GetRandFinish()));
		}
		break;

	// 回復
	case CardEffect::Effect::Heal:
		if (cardEffect.GetRandStart() == 0 && cardEffect.GetRandFinish() == 0)
		{
			//固定値
			target->Heal(cardEffect.GetValue());
		}
		else
		{
			//ランダムな値で回復
			target->Heal(MyRandom(cardEffect.GetRandStart(), cardEffect.GetRandFinish()));
		}
		break;

	// ミントを植える
	case CardEffect::Effect::Plant:
		if (!m_pMinto->GetPlant())
		{
			m_pMinto->SetPlant(true);
		}
		

	case CardEffect::Effect::Wither:
		m_pMinto->GetWither();
		
	// 成長(ミントにエネルギーを与える)
	case CardEffect::Effect::Grow:
		if (m_pMinto->GetPlant())
		{
			if (cardEffect.GetRandStart() == 0 && cardEffect.GetRandFinish() == 0)
			{
				//固定値
				m_pMinto->GetAddEnergy(cardEffect.GetValue());
			}
			else
			{
				//ランダムな値で回復
				m_pMinto->GetAddEnergy(MyRandom(cardEffect.GetRandStart(), cardEffect.GetRandFinish()));
			}
		}
		break;
	// ルール
	case CardEffect::Effect::Rule:
		//ルールを追加
		m_rules.push_back(cardEffect);
		break;
	default:
		break;

	}

	
	//ルールチェック　(また後で行う)
	CheckRule(cardEffect);
}

void CardManager::CheckRule(CardEffect& cardEffect)
{
	int deleteCount = 0;
	for (CardEffect rule : m_rules)		// <- for (int i = 0; i < m_rules.size(); i++) と同じ
	{
		switch (rule.GetRuleEffect())
		{
		case CardEffect::RuleEffect::MyMltiWin:
		{
			int value = rule.GetValue();
			//自分の体力がvalue倍なら勝利
			if (m_player->GetHp() % value == 0)
			{
				m_isWin = true;
			}

			break;
		}
		case CardEffect::RuleEffect::YourMltiWin:
		{
			int value = rule.GetValue();
			// 相手の体力がvalue倍なら勝利
			if (m_enemy->GetHp() % value == 0)
			{
				m_isWin = true;
			}
			break;
		}
		case CardEffect::RuleEffect::MySameWin:
		{
			int value = rule.GetValue();
			// 自分のHPがvalueなら勝利
			if (m_player->GetHp() - value == 0)
			{
				m_isWin = true;
			}
			break;
		}
		case CardEffect::RuleEffect::YourSameWin:
		{
			int value = rule.GetValue();
			// 相手のHPがvalueなら勝利
			if (m_enemy->GetHp() - value == 0)
			{
				m_isWin = true;
			}
			break;
		}
		case CardEffect::RuleEffect::MintoSameGrow:
		{
			int value = rule.GetValue();
			// ミントのエネルギーがNなら育つ
			if (m_pMinto->GetGrow() - value == 0)
			{
				m_isWin = true;
			}
			break;
		}
		case CardEffect::RuleEffect::MintoMltiWin:
		{
			int value = rule.GetValue();
			// ミントのエネルギーがN倍なら勝利
			if (m_pMinto->GetGrow() % value == 0)
			{
				m_isWin = true;
			}
			break;
		}
		case CardEffect::RuleEffect::Delete:
		{
			// 一番古いルールを削除
			//m_rules.erase(m_rules.begin());
			deleteCount++;

			break;
		}
		default:
			break;
		}
	}

	for (int i = 0; i < deleteCount; i++)
	{
		m_rules.erase(m_rules.begin());
	}

	cardEffect.SetContent("");
}
