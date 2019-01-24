#pragma once
#include  "../Singleton.h"
#include "../Action/Action.h"
#include <queue>
class IntroStage
	:public Singleton<IntroStage> 
{
public:
	//~IntroStage() { delete m_pPAction, delete m_pOAction; };

	void Init();
	void Update();
	void Render();
	void SetNextAction();
private:
	IntroStage() {};
	friend class Singleton<IntroStage>;
	struct ActionData {

		ActionBase* pAction;
		int frame;
	};
	struct ActionList
	{
		std::queue<ActionData> actionQueue;
	};
	int pcnt;
	int ocnt;
	ActionBase* ConvertAction(int info);
	ActionData m_Player;
	ActionData m_Owner;

	std::queue<ActionList>m_PActionList;
	std::queue<ActionList>m_OActionList;
};