#pragma once
#include "../Scene.h"
#include "../../Sprite/SpriteReader.h"
#include "../../ResultCharacter/ResultCharacter.h"
#include "../../LastTrain/LastTrain.h"
#include <memory>

class Result
	:public Scene 
{
public:
	virtual void Initialize()override;
	void Finalize()override;
	virtual Scene* Update(SceneRoot* root)abstract;
	virtual void Render()override;

protected:
	ResultCharacter m_rc;
	SpriteReader::ReadData m_Sprites;
	LastTrain m_lastTrain;

	int cnt;
};

//	Success
class ResultS final 
	:public Result
{
public:
	virtual void Initialize()override;
	Scene* Update(SceneRoot* root)override;
	virtual void Render()override;
private:
	bool isRenderChara;
	int flashCnt;
};

//	Failed
class ResultF final
	:public Result
{
public:
	virtual void Initialize()override;
	Scene* Update(SceneRoot* root)override;
	virtual void Render()override;
private:
};