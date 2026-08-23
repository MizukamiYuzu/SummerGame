#include "Dxlib.h"
#include "CardManager.h"
#include "CardEffect.h"
#include "Game.h"

namespace
{
	constexpr int kFirstHandNum = 4;	// 初期の手札枚数
	constexpr int kCardWidthMaxCount = 8;	// 一行につき並べられる枚数
	constexpr int kMaxHand = kCardWidthMaxCount * 2;	// 持つことができるカードの最大枚数


	constexpr int kSkipGraphPosX = Game::kScreenWidth - 200;
	constexpr int kSkipGraphPosY = Game::kScreenHeight - 72;
	constexpr int kSkipGraphMargin = 30;
}

CardManager::CardManager() :
	m_graphDeckHandle(-1),
	m_graphSkipHandle(-1),
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
	m_enemy = new Enemy();
	m_pTurnManager = new TurnManager();

	m_pMinto = new minto();
	m_pMinto->Init();
	m_pCardContent = new CardContent;
	m_pCardContent->Init();
	m_MyCard.resize(kFirstHandNum);
	m_EnemyCard.resize(kFirstHandNum);
	m_myCardEffect.resize(kFirstHandNum);
	m_enemyCardEffect.resize(kFirstHandNum);
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
		if (m_myCardEffect[i].GetEffect() == CardEffect::Effect::None)
		{ 
			//カード効果を得る
			m_myCardEffect[i] = m_pCardContent->CreateCardEffect();
		}
	}
	for (int i = 0; i < m_EnemyCard.size(); i++)
	{
		if (!m_EnemyCard[i].GetCard())continue;
		if (m_enemyCardEffect[i].GetEffect() == CardEffect::Effect::None)
		{
			//カード効果を得る
			m_enemyCardEffect[i] = m_pCardContent->CreateCardEffect();
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
		if (isInsideCard_y && !m_isMyHandFull)
		{
			if ((m_isClickBefore == false) && (m_isClickNow == true) && (m_isDrewCard == false))
			{
				if (m_pTurnManager->GetMyTurn())
				{
					//カード作成
					Card card;				// 新しくCard型の変数を宣言(push_backに追加する時にしか使わない)
					card.Init();			// 初期化するよ
					m_MyCard.push_back(card);	// 今ある配列の後ろに一つ要素を追加する
					// Card型の変数を入れている理由は、m_cardはcard型の動的配列で、Card型の変数を入れてあげることで、もう一つcardを用意する
					m_isDrewCard = true;
		//カードの効果を作成(中身は空)
					CardEffect cardEffect;
					m_myCardEffect.push_back(cardEffect);
					m_isDrewCardDeck = true;
				}
				

			}
		}


		// スキップ
		/* 条件掃き出し */
		// スキップ画像の上にマウスが乗っているかの判定
		bool isMouseSkipInSideLeft = m_mouseX >= kSkipGraphPosX - kSkipGraphMargin;				// マウスがスキップ画像の左端より右側にいるか
		bool isMouseSkipInsideRight = m_mouseX <= Game::kScreenWidth - kSkipGraphMargin;		// マウスがスキップ画像の右端より左にいるか
		bool isMouseSkipInsideUp = m_mouseY >= kSkipGraphPosY - kSkipGraphMargin;				// マウスがスキップ画像の上端よりも下にいるか
		bool isMouseSkipInsideDown = m_mouseY <= Game::kScreenHeight - kSkipGraphMargin;		// マウスがスキップ画像の下端よりも上にいるか
		bool isMouseInsideSkip = isMouseSkipInSideLeft && isMouseSkipInsideRight && isMouseSkipInsideUp && isMouseSkipInsideDown;	// マウスがスキップ画像の上に乗っているか
		// フレーム判定
		bool isClickThisFrame = !m_isClickBefore && m_isClickNow;

		if (isClickThisFrame && isMouseInsideSkip && m_isDrewCardDeck)
		{
			m_isDrewCardDeck = false;
			m_pTurnManager->SetMyTurn(false);
		}

		// プレイヤー
		//	DrawBox(Game::kScreenWidth / 2, Game::kScreenHeight / 2-50, Game::kScreenWidth / 2 + 100, Game::kScreenHeight / 2 + 50, GetColor(255, 255, 255), true);
		int validCardCount = 0;
		for (int i = 0; i < m_MyCard.size(); i++)
		{
			if (m_MyCard[i].GetCard())validCardCount++;	// カードが存在している分だけカウントする
		}
		bool isDiscardMode = (validCardCount == kMaxHand+1);	// 手持ちに持てる最大の枚数より手札が多くあるか
		

		m_isMyHandFull = (validCardCount >= kMaxHand + 1);

		int drawMyCount = 0;	// 消されていないならカウントをする
		int drawEnemyCount = 0;	// 消されていないならカウントをする
		int replaceNomber = 0;	// 
		bool _isDeleteCard = false;	// このフレーム（ワンクリック）でカードが消されたかどうか	←　一回のクリックで一枚だけ消すようにする変数
		// ↑ワンフレームでしか使わないからここで宣言して良き
		for (int i = 0; i < m_MyCard.size(); i++)	// 手札を並ばせる
		{
			if (!m_MyCard[i].GetCard())continue;	// カードが存在してなかったら次のループに移動
			
			
			

			int cardMyPosX = 120 * (drawMyCount % kCardWidthMaxCount) + 50;
			int cardMyPosY = Game::kScreenHeight / 2 + 120 * (drawMyCount / kCardWidthMaxCount) + 100;

			int hitX = m_MyCard[i].GetDrawPosX();
			int hitY = m_MyCard[i].GetDrawPosY();

			// ↓手札カード
			bool isMouseOutLeft = m_mouseX >= hitX;//カードの左側より内側にマウスがいる
			bool isMouseOutRight = m_mouseX <= hitX + m_MyCard[i].GetCardWidth();
			bool isMouseOutUp = m_mouseY >= hitY;
			bool isMouseOutDown = m_mouseY <= hitY + m_MyCard[i].GetCardHeight();
			bool isInsideCard = isMouseOutLeft && isMouseOutRight && isMouseOutUp && isMouseOutDown;	// マウスカーソルがカードの上に乗っているとき

			// ↓手札
			//上下左右どちらにも出ていない(カード内にマウスポインタがあるとき)
			if (isInsideCard)
			{
				cardMyPosY -= 10;
				

				bool isClickThisFrame = !m_isClickBefore && m_isClickNow;	// このフレームでクリックされた

				if (isClickThisFrame && _isDeleteCard == false && m_isDrewCardDeck)
				{
					if (m_pTurnManager->GetMyTurn())
					{
						if (isDiscardMode)
						{
							// カードを無効にする
							m_MyCard[i].SetCard(false); // m_card[i]に引数をぶち込む
							m_myCardEffect[i].SetContent("");

							//m_cardContent.erase(m_cardContent.begin() + i);

							_isDeleteCard = true;
							m_isMyHandFull = false;
						}
						else
						{
							
							
							//カードを使う処理(敵に対して)
							UseCard(m_enemy, m_player, m_myCardEffect[i]);
							// カードを無効にする
							m_MyCard[i].SetCard(false); // m_card[i]に引数をぶち込む
							//m_cardContent.erase(m_cardContent.begin() + i);

							_isDeleteCard = true;
							m_isDrewCardDeck = false;
							m_pTurnManager->SetMyTurn(false);
						}
					}

				}
			}
			if (!(drawMyCount >= kMaxHand))
			{
				m_MyCard[i].SetDrawPos(cardMyPosX, cardMyPosY);
			}
			else
			{
				m_MyCard[i].SetDrawPos(50, 50);
			}
			
			drawMyCount++;
			if (drawMyCount >= kMaxHand + 1)
			{
				m_isMyHandFull = true;
			}

		}
		
		// 敵
		for (int i = 0; i < m_EnemyCard.size(); i++)	// 手札を並ばせる
		{
			
			if (!m_EnemyCard[i].GetCard())continue;	// カードが存在してなかったら次のループに移動

			int cardEnemyPosX = Game::kScreenWidth-200 - (120 * (drawEnemyCount % kCardWidthMaxCount) - 50);
			int cardEnemyPosY =( Game::kScreenHeight / 2-200 -( 120 *(drawEnemyCount / kCardWidthMaxCount) -50));

			
			if (CheckHitKey(KEY_INPUT_UP))
			{
				m_isDrewCard = false;
				m_pTurnManager->SetMyTurn(true);
			}

			m_EnemyCard[i].SetDrawPos(cardEnemyPosX, cardEnemyPosY);
			drawEnemyCount++;

		}
		if (!m_pTurnManager->GetMyTurn())
		{
			// 使用していないカードの番号を代入する
			/*
				例えば、1番目のカードを使った場合
				validIndices[0] = 0;
				validIndices[1] = 2;
				validIndices[2] = 3;
			*/ 
			std::vector<int> validIndices;
			
			for (int i = 0; i < m_EnemyCard.size(); i++)
			{
				if (m_EnemyCard[i].GetCard())	// もしカードが存在していたら
				{
					validIndices.push_back(i);
				}
			}
			if (!validIndices.empty())	// もしvalidIndicesが空じゃなければ(empty<-空という意味)
			{
				// 返ってきた数(何番目のカードを使うか)を代入
				int useCardIndex = m_enemy->ThinkAction(validIndices, m_player->GetHp(), m_enemy->GetHp(), m_pMinto->GetGrow());
				if (useCardIndex != -1)	// useCardIndex == -1のときは考えているとき　(m_thinkTimer--中)
				{
					UseCard(m_player, m_enemy, m_enemyCardEffect[useCardIndex]);
					m_EnemyCard[useCardIndex].SetCard(false);
					m_isDrewCard = false;
					m_pTurnManager->SetMyTurn(true);
				}
				
			}
			else 
			{
				m_isDrewCard = false;
				m_pTurnManager->SetMyTurn(true);
			}
		}
		if (m_player->GetHp() <= 0 || m_enemy->GetHp() <= 0)
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
	DrawExtendGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2 - 50, Game::kScreenWidth / 2 + 100, Game::kScreenHeight / 2 + 50, m_graphDeckHandle, true);	
	DrawFormatString(0, 64, GetColor(255, 255, 255), "TURN:%d", m_pTurnManager->GetMyTurn());
	DrawFormatString(0, 96, GetColor(255, 255, 255), "ENEMY_HP:%d", m_enemy->GetHp());
	DrawFormatString(0, 128, GetColor(255, 255, 255), "PLAYER_HP:%d", m_player->GetHp());

	if (m_pTurnManager->GetMyTurn())
	{
		DrawGraph(kSkipGraphPosX - kSkipGraphMargin, kSkipGraphPosY - kSkipGraphMargin, m_graphSkipHandle, true);
		
	}

	// 手札描画
	
	for (int i = 0; i < m_EnemyCard.size(); i++)
	{
		m_EnemyCard[i].Draw();
		DrawFormatString(m_EnemyCard[i].GetDrawPosX() + 50, m_EnemyCard[i].GetDrawPosY() + 50, GetColor(255, 0, 0), "%d", i);
		//	DrawString(100, i+100, m_pCardContent->GetContent().c_str(), GetColor(255, 255, 255));
		DrawFormatString(Game::kScreenWidth -500, i * 20, GetColor(255, 255, 255), m_enemyCardEffect[i].GetContent().c_str());

	}

	for (int i = 0; i < m_MyCard.size(); i++)
	{
		m_MyCard[i].Draw();
		DrawFormatString(m_MyCard[i].GetDrawPosX() + 50, m_MyCard[i].GetDrawPosY() + 50, GetColor(255, 0, 0), "%d", i);
		//	DrawString(100, i+100, m_pCardContent->GetContent().c_str(), GetColor(255, 255, 255));
		DrawFormatString(100, i * 20, GetColor(255, 255, 255), m_myCardEffect[i].GetContent().c_str());

	}
	for (int i = 0; i < m_rules.size(); i++)
	{
		DrawFormatString(900, i * 20, GetColor(255, 255, 255), m_rules[i].GetContent().c_str());
	}

}

void CardManager::UseCard(Player* target, Player* mySelf, CardEffect& cardEffect)
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
			mySelf->Heal(cardEffect.GetValue());
		}
		else
		{
			//ランダムな値で回復
			mySelf->Heal(MyRandom(cardEffect.GetRandStart(), cardEffect.GetRandFinish()));
		}
		break;

	// ミントを植える
	case CardEffect::Effect::Plant:
		if (!(m_pMinto->GetPlant()))
		{
			m_pMinto->SetPlant(true);
		}
		break;

	case CardEffect::Effect::Wither:
		m_pMinto->GetWither();
		break;
		
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
			if (m_player->GetHp() % value == 0 && m_player->GetHp() !=0)
			{
				m_isWin = true;
			}

			break;
		}
		case CardEffect::RuleEffect::YourMltiWin:
		{
			int value = rule.GetValue();
			// 相手の体力がvalue倍なら勝利
			if (m_enemy->GetHp() % value == 0 && m_enemy->GetHp() != 0)
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
			if (m_pMinto->GetGrow() % value == 0 && m_pMinto->GetGrow() != 0)
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
	if (m_rules.size() > 5)
	{
		for (int i = 0; m_rules.size() > 5; i++)
		{
			m_rules.erase(m_rules.begin());
		}
	}

	cardEffect.SetContent("");
}
