#include "CharacterController.h"
#include "../Owner/Owner.h"
#include "../Customer/Customer.h"
#include "../../Board/Board.h"
#include "../../CSV/CSVReader.h"
#include "../../MyGame.h"
#include <algorithm>
using namespace std;
using namespace DirectX;

const float CharacterController::c_Diff = 1;


CharacterController::CharacterController()
{
}


CharacterController::~CharacterController()
{
}

void CharacterController::Init()
{
	m_CustomerNumber = 18;

	//	スプライト
	m_pSprite = make_shared<Sprite>();

	//	店長
	auto owner = make_shared<Owner>();
	m_Characters.push_back(owner);

	auto&csv = CSVReader::GetInstance();
	csv.Load("../Resource/csv/Customer.csv");
	auto cells = csv.GetCells();
	const XMINT2 c_Offset = { 0,1 };

	//	テクスチャ
	for (size_t i = 0; i < GetArraySize(m_CustomerTex); ++i) {
		m_CustomerTex[i] = make_shared<Texture>();
		m_CustomerTex[i]->Load(cells[c_Offset.y + i][0]);
	}

	//	客
	for (size_t i = 0; i < m_CustomerNumber; i++)
	{
		int x = c_Offset.x + 1;
		auto data = make_shared<Customer>();
		XMFLOAT2 comp;
		comp.x = static_cast<float>(atof(cells[c_Offset.y + i][x++].c_str()));
		comp.y = static_cast<float>(atof(cells[c_Offset.y + i][x++].c_str()));
		data->SetComp(comp);
		XMINT2 split;
		split.x = atoi(cells[c_Offset.y + i][x++].c_str());
		split.y = atoi(cells[c_Offset.y + i][x++].c_str());
		data->SetSplit(split);
		XMINT2 index;
		index.x = atoi(cells[c_Offset.y + i][x++].c_str());
		index.y = atoi(cells[c_Offset.y + i][x++].c_str());
		data->SetLTIndex(index);
		XMINT2 atlas;
		atlas.x = atoi(cells[c_Offset.y + i][x++].c_str());
		atlas.y = atoi(cells[c_Offset.y + i][x++].c_str());
		data->SetInitAtlasIndex(atlas);
		int no= atoi(cells[c_Offset.y + i][x].c_str());
		data->SetTextureWP(m_CustomerTex[no]);
		data->SetSpriteWP(m_pSprite);
		m_Characters.push_back(data);
	}

	//	Init
	for (auto it : m_Characters) {
		it->Init();
	}
}

void CharacterController::Update()
{
	for (auto it : m_Characters) {
		it->Update();
	}
}

void CharacterController::Render()
{
	for (auto it : m_Characters) {
		it->Render();
	}
}

shared_ptr<ICharacter> CharacterController::GetCharacter(DirectX::XMINT2 ltIndex)
{
	auto it=find_if(m_Characters.begin(),m_Characters.end(),
		[&](shared_ptr<ICharacter> ic) {
		return (ic->GetLTIndex().x == ltIndex.x&&ic->GetLTIndex().y == ltIndex.y);
	});
	if (it != m_Characters.end()) {
		return m_Characters[(it - m_Characters.begin())];
	}
	return nullptr;
}

std::shared_ptr<ICharacter> CharacterController::GetCharacter(DirectX::XMFLOAT2 pos)
{
	auto it = find_if(m_Characters.begin(), m_Characters.end(),
		[&](shared_ptr<ICharacter> ic) {

		bool x = abs(ic->GetPos().x - pos.x) < c_Diff;
		bool y = abs(ic->GetPos().y - pos.y) < c_Diff;
		return ( x && y );
	});
	if (it != m_Characters.end()) {
		return m_Characters[(it - m_Characters.begin())];
	}
	return nullptr;
}
