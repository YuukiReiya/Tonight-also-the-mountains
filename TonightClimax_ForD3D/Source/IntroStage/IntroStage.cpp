#include "IntroStage.h"
#include "../CSV/CSVReader.h"

using namespace std;


void IntroStage::Init()
{

	auto&csv = CSVReader::GetInstance();
	csv.Load("../Resource/csv/PlayerActionList.csv");
	auto cells = csv.GetCells();

	//	player
	for (int y = 2; y < 10; ++y) {

		queue<ActionData>addQueue;
		ActionList addList;
		for (int x = 1;;) {

			int r = atoi(cells[y][x++].c_str());

			//
			if (r == -1) { break; }

			ActionData data;
			data.pAction = ConvertAction(r);
			r = atoi(cells[y][x++].c_str());
			data.frame = r;
			data.pAction->Init();
			addQueue.push(data);
		}
		addList.actionQueue = addQueue;
		m_PActionList.push(addList);
	}
	m_Player = m_PActionList.front().actionQueue.front();
	m_PActionList.front().actionQueue.pop();


	csv.Load("../Resource/csv/OwnerActionList.csv");
	cells = csv.GetCells();

	//	owner 
	for (int y = 2; y < 10; ++y) {

		queue<ActionData>addQueue;
		ActionList addList;
		for (int x = 1;;) {

			int r = atoi(cells[y][x++].c_str());

			//
			if (r == -1) { break; }

			ActionData data;
			data.pAction = ConvertAction(r);
			r = atoi(cells[y][x++].c_str());
			data.frame = r;
			data.pAction->Init();
			addQueue.push(data);
		}
		addList.actionQueue = addQueue;
		m_OActionList.push(addList);
	}
	m_Owner = m_OActionList.front().actionQueue.front();
	m_OActionList.front().actionQueue.pop();

	pcnt = 0;
	ocnt = 0;
	m_Player.pAction->Init();
	m_Owner.pAction->Init();
}

void IntroStage::Update()
{
	pcnt++;
	ocnt++;

	//	player
	m_Player.pAction->Update();
	if (pcnt > m_Player.frame) {
		delete m_Player.pAction;

  		if (!m_PActionList.empty()&&!m_PActionList.front().actionQueue.empty()) {
			m_Player = m_PActionList.front().actionQueue.front();
			m_PActionList.front().actionQueue.pop();
			m_Player.pAction->Init();
		}
		else {
			m_Player.pAction = new PlayerWait;
			m_Player.pAction->Init();

		}
		pcnt = 0;
	}

	//	owner
	m_Owner.pAction->Update();
	if (ocnt > m_Owner.frame) {
		delete m_Owner.pAction;

		if (!m_OActionList.empty() && !m_OActionList.front().actionQueue.empty()) {
			m_Owner = m_OActionList.front().actionQueue.front();
			m_OActionList.front().actionQueue.pop();
			m_Owner.pAction->Init();
		}
		else {
			m_Owner.pAction = new OwnerWait;
			m_Owner.pAction->Init();
		}
		ocnt = 0;
	}
}

void IntroStage::Render()
{
	m_Player.pAction->Render();
	m_Owner.pAction->Render();
}

void IntroStage::SetNextAction()
{
	if (!m_PActionList.empty()) { m_PActionList.pop(); }
	if (!m_PActionList.empty())
	{
		delete m_Player.pAction;
		m_Player = m_PActionList.front().actionQueue.front();
		m_PActionList.front().actionQueue.pop();
		m_Player.pAction->Init();
		pcnt = 0;
	}

	if (!m_OActionList.empty()) { m_OActionList.pop(); }
	if (!m_OActionList.empty())
	{
		delete m_Owner.pAction;
		m_Owner = m_OActionList.front().actionQueue.front();
		m_OActionList.front().actionQueue.pop();
		m_Owner.pAction->Init();
		ocnt = 0;
	}
}

ActionBase * IntroStage::ConvertAction(int info)
{
	switch (info)
	{
	case 0:return new PlayerWait;
	case 1:return new OwnerWait;
	case 2:return new PlayerStep; 
	case 3:return new OwnerStep;
	case 4:return new PlayerWord;
	case 6:return new PlayerJump;
	case 7:return new OwnerJump;
	case 9:return new OwnerAngry;
	case 10:return new PlayerWorry;
	case 12:return new PlayerCry;
	default:
		break;
	}
	return nullptr;
}
