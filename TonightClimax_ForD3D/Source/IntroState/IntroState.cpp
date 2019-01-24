//#include "IntroState.h"
//
//
//
//void IState::SetChara(std::shared_ptr<Sprite> sp, std::shared_ptr<Texture> tex)
//{
//	CSprite = sp;
//	CTex = tex;
//}
//
//void IState::SetBallon(std::shared_ptr<Sprite> sp, std::shared_ptr<Texture> tex)
//{
//	BSprite = sp;
//	BTex = tex;
//}
//
//void IState::Render()
//{
//	auto cs = CSprite.lock();
//	auto ct = CTex.lock();
//
//	//	ƒLƒƒƒ‰
//	cs->RenderAtlas(
//		ct->GetTexture(),
//		cAtlas.x, cAtlas.y
//	);
//
//	if (!isBalloon) { return; }
//	auto bs = BSprite.lock();
//	auto bt = BTex.lock();
//
//	//	ƒoƒ‹[ƒ“
//	bs->RenderAtlas(
//		bt->GetTexture(),
//		bAtlas.x, bAtlas.y
//	);
//}
//
//
//void PlayerRun::Update()
//{
//	cnt++;
//}
