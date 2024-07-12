#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"
void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
//	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	//===================================================================
	// 乱数実験場
	//===================================================================
	int randRes[10] = {};

	//如何にrand()が偏るか
	//srand((unsigned)time(NULL));
	//for (int i = 0; i < 100000000; i++)
	//{
	//	//0～32767 % 10000(0～9999)
	//	int tmp = rand() % 10000;
	//	int idx = tmp / 1000;

	//	randRes[idx]++;
	//}
	////結果を出力
	//OutputDebugStringA("-----------------------------------------------\n");
	//for (int i=0;i<10 ;i++)
	//{
	//	std::stringstream ss;
	//	ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数:\t" << randRes[i] << "\n";
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());
	//}
	//OutputDebugStringA("-----------------------------------------------\n");

	///////////////////////////////////////////////////////////
	//メルセンヌツイスタ
	//for (int i = 0; i < 100000000; i++)
	//{
	//	//0～32767 % 10000(0～9999)
	//	int tmp =KdGetInt(0,9999);
	//	int idx = tmp / 1000;

	//	randRes[idx]++;
	//}
	////結果を出力
	//OutputDebugStringA("-----------------------------------------------\n");
	//for (int i = 0; i < 10; i++)
	//{
	//	std::stringstream ss;
	//	ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数:\t" << randRes[i] << "\n";
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());
	//}
	//OutputDebugStringA("-----------------------------------------------\n");

	///////////////////////////////////////
	//レッスンその１：ｃカードとｒカードをそれぞれ50％の確率で起動時に表示せよ
	//レッスンその2：ｃカードとｒカードをそれぞれ99.5％,0.5%の確率で起動時に表示せよ
	int tmp = KdGetInt(1, 1000);
	//結果を出力
	OutputDebugStringA("-----------------------------------------------\n");
	std::stringstream ss;
	if (tmp <= 950)
	{
		ss << "CカードGET！" << "\n";
	}
	else
	{
		ss << "RカードGET！" << "\n";
	}
	std::string str = ss.str();
	OutputDebugStringA(str.c_str());
	OutputDebugStringA("-----------------------------------------------\n");

}

void GameScene::Event()
{
}