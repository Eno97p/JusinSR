#include "stdafx.h"
#include "..\Header\Loading.h"
#include "Export_System.h"
#include "Export_Utility.h"

CLoading::CLoading(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
{
	m_pGraphicDev->AddRef();
	ZeroMemory(m_szLoading, sizeof(m_szLoading));
}

CLoading::~CLoading()
{
}

HRESULT CLoading::Ready_Loading(LOADINGID eID)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL,	// 디폴트 보안 속성
		0,										// 디폴트 스택 사이즈(1바이트)
		Thread_Main,							// 동작 시킬 쓰레드 함수 이름(__stdcall 규약)
		this,									// 쓰레드 함수의 매개 변수로 전달할 값
		0,										// 쓰레드 생성 및 실행을 조절하기 위한 FLAG
		NULL);									// 쓰레드 ID 반환..

	m_eID = eID;

	return S_OK;
}



_uint CLoading::Loading_ForStage()
{
	FAILED_CHECK_RETURN(Loading_UI_Texture(), E_FAIL);
	FAILED_CHECK_RETURN(Loading_Item_Texture(), E_FAIL);
	FAILED_CHECK_RETURN(Loading_Componment(), E_FAIL);
	FAILED_CHECK_RETURN(Loading_Player_Texture(), E_FAIL);
	FAILED_CHECK_RETURN(Loading_Beefalo_Texture(), E_FAIL);

	//Sound
	//Engine::Ready_Sound();

	//FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_TerrainTexture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain.png")), E_FAIL);
	//FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_HeightTerrainTexture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain0.png")), E_FAIL);
	FAILED_CHECK_RETURN(SaveLoadingTexture(L"Proto_TerrainTexture", TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain.png"), E_FAIL);
	FAILED_CHECK_RETURN(SaveLoadingTexture(L"Proto_HeightTerrainTexture", TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain0.png"), E_FAIL);


	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_PlayerTexture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player%d.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_EffectTexture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Explosion/Explosion%d.png", 90)), E_FAIL);


	Loading_Spider_Texture();
	Loading_Pig_Texture();
	/*Loading_Boss_Texture();*/
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_SkyBoxTexture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Bin/Resource/Texture/SkyBox/Ocean.dds")), E_FAIL);



	m_bFinish = true;
	lstrcpy(m_szLoading, L"Loading Complete");

	return S_OK;
}

HRESULT CLoading::Loading_Componment()
{
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_TriCol", CTriCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_RcCol", CRcCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_TerrainTex", CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_CubeTex", CCubeTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Transform", CTransform::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Calculator", CCalculator::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_3_3_1_Tex", CustomizeTex::Create(m_pGraphicDev, 3, 3, 1)), E_FAIL);

	return S_OK;
}

HRESULT CLoading::Loading_Player_Texture()
{
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_idle_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/idle_down/idle_down__%03d.png", 22)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_idle_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/idle_up/idle_up__%03d.png", 22)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_idle_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/idle_side/idle_side__%03d.png", 23)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_run_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/run_down/run_down__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_run_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/run_up/run_up__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_run_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/run_side/run_side__%03d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_build_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/build_down/build_down__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_build_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/build_up/build_up__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_build_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/build_side/build_side__%03d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_pickup_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/pickup_down/pickup_down__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_pickup_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/pickup_up/pickup_up__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_pickup_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/pickup_side/pickup_side__%03d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_hit_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/hit_std/hit_std__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_hit_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/hit_up/hit_up__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_hit_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/hit_side/hit_side__%03d.png", 7)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_punch_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/attack/punch_down/punch_down__%03d.png", 11)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_punch_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/attack/punch_up/punch_up__%03d.png", 11)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Unarmed_punch_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/attack/punch_side/punch_side__%03d.png", 11)), E_FAIL);


	//횃불
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Torch_idle_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Armed/torch/idle_down/torch_idle_down__%03d.png", 22)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Torch_idle_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL,   L"../Bin/Resource/Texture/Player/Armed/torch/idle_up/torch_idle_up__%03d.png", 22)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Torch_idle_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Armed/torch/idle_side/torch_idle_side__%03d.png", 22)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Torch_run_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Armed/torch/run_down/torch_run_down__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Torch_run_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL,   L"../Bin/Resource/Texture/Player/Armed/torch/run_up/torch_run_up__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_Torch_run_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Armed/torch/run_side/torch_run_side__%03d.png", 6)), E_FAIL);


	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_falldown", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/fall_down/fall_down__%03d.png", 8)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_wakeup", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/wake_up/wake_up__%03d.png", 32)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Player_eat", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/eat/eat__%03d.png", 36)), E_FAIL);

	return S_OK;
}

HRESULT CLoading::Loading_Beefalo_Texture()
{
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Object_Erase", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Erase/Die__%03d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_graze", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_graze/befalo_graze__%03d.png", 10)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_idle", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_idle/beefalo_idle__%03d.png", 16)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_walk_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_run/walk_down/down__%03d.png", 20)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_walk_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_run/walk_up/up__%03d.png", 20)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_walk_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_run/walk_side/side__%03d.png", 20)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_run_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_run/run_down/run_down__%03d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_run_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_run/run_up/run_up__%03d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_run_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_run/run_side/run_side__%03d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_atk_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_atk_down/atk_down__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_atk_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_atk_side/atk_side__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_atk_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_atk_up/atk_up__%03d.png", 7)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Beefalo_dead", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/beefalo/beefalo_dead/dead__%03d.png", 12)), E_FAIL);
	return 0;
}

HRESULT CLoading::Loading_Spider_Texture()
{
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Spider_walk_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/spider/move/walk_down/walk_down__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Spider_walk_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/spider/move/walk_up/walk_up__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Spider_walk_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/spider/move/walk_side/walk_side__%03d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Spider_atk_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/spider/atk/atk_down/atk_down__%03d.png", 11)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Spider_atk_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/spider/atk/atk_up/atk_up__%03d.png", 11)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Spider_atk_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/spider/atk/atk_side/atk_side__%03d.png", 11)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Spider_hit", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/spider/hit/hit__%03d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Spider_dead", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/spider/dead/dead__%03d.png", 9)), E_FAIL);


	return 0;
}

HRESULT CLoading::Loading_Pig_Texture()
{
	//Pig House
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_PigHouse_IDLE", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Resource/pig_house/idle/idle__%d.png", 3)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_PigHouse_hit_run_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Resource/pig_house/hit/run_down/run_hit__%03d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_PigHouse_hit_std", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Resource/pig_house/hit/std/std_hit__%03d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_PigHouse_dead", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Resource/pig_house/idle/rubble.png")), E_FAIL);


	//Pig
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_happy", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/idle_happy/happy__%03d.png", 17)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_angry", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/idle_angry/angry__%03d.png", 17)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_idle_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/idle_down/idle_down__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_idle_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/idle_up/idle_up__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_idle_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/idle_side/side__%03d.png", 7)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_walk_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/move/walk/down/walk_down__%03d.png", 8)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_walk_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL,   L"../Bin/Resource/Texture/Monster/pig/move/walk/up/walk_up__%03d.png", 8)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_walk_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/move/walk/side/walk_side__%03d.png", 8)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_run_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/move/run/down/run_down__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_run_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL,   L"../Bin/Resource/Texture/Monster/pig/move/run/up/run_up__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_run_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/move/run/side/run_side__%03d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_atk_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/attack/down/down__%03d.png", 10)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_atk_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL,   L"../Bin/Resource/Texture/Monster/pig/attack/up/up__%03d.png", 10)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_atk_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/attack/side/side__%03d.png", 10)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_dead", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/dead/dead__%03d.png", 11)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_hit", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/hit/hit__%03d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Pig_eat", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/pig/eat/eat__%03d.png", 16)), E_FAIL);
	return 0;
}

HRESULT CLoading::Loading_Boss_Texture()
{

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_Idle_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/idle/down/down__%03d.png", 19)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_Idle_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/idle/side/side__%03d.png", 19)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_Idle_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/idle/up/up__%03d.png", 19)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_walk_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/walk/down/walk_down_%d.png", 16)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_walk_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/walk/side/side__%03d.png", 16)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_walk_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/walk/up/up__%03d.png", 16)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_Atk_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/attack/down/non_effect/non__%03d.png", 20)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_Atk_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/attack/side/non_effect/non__%03d.png", 20)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_Atk_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/attack/up/non_effect/non__%03d.png", 20)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_hit_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/hit/down/down__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_hit_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/hit/side/side__%03d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_hit_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/hit/up/up__%03d.png", 7)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_taunt", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/taunt/taunt__%03d.png", 17)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Deer_dead", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/deerclops/dead/dead__%03d.png", 24)), E_FAIL);
	return S_OK;
}

HRESULT CLoading::Loading_UI_Texture()
{
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Left_Panel", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Left_Panel.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Item_Inven_Slot", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Item_Inven_Slot.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Equipment", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Equipment.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Cloth", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Cloth.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Alive", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Alive.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Light", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Light.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Weapon", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Weapon.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Armor_Panel", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Armor_Panel.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Left_Panel_Default", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Left_Panel_Default.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Left_Panel_Off", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Left_Panel_Off.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Left_Panel_On", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Left_Panel_On.png")), E_FAIL);


	//Right_Top UI
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_HP", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/HP/HP__%03d.png",20)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Hungry", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Hungry/Hunger__%03d.png",20)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Mental", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Mental/Sanity__%03d.png",20)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_World_1", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/World_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_World_2", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/World_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_World_10", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/World_10.png")), E_FAIL);



	//Pop_Up UI
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Linked_Panel", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Linked_Panel.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Item_Panel", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Item_Panel.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_UI_Explain_PopUp_Panel", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Hud/Explain_PopUp_Panel.png")), E_FAIL);
	return S_OK;
}

HRESULT CLoading::Loading_Item_Texture()
{
	//Objects Resource
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Obejct_Tree_Idle", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/Tree/idle/tree_idle__%03d.png", 27)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Obejct_Tree_Hit", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/Tree/chop/chop__%03d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Obejct_Tree_Left_Fall", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/Tree/fall_left/fall_left__%03d.png", 13)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Obejct_Tree_Right_Fall", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/Tree/fall_right/fall_right__%03d.png", 13)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Obejct_Tree_Final", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/Tree/stump__000.png")), E_FAIL);
	
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Nomal_Rock", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/Rock/Nomal_Rock/Nomal_Rock_%d.png", 3)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Obejct_Grass_idle", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/grass_new/idle/grass_idle__%03d.png", 28)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Obejct_Grass_dead", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/grass_new/picking/picking__%03d.png", 7)), E_FAIL);

	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Object_most_idle", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/berrybush/most/most_idle__000.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Object_most_pick", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/berrybush/most_picked/most_picked__%03d.png", 3)), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Object_empty_idle", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/berrybush/empty_idle/empty_idle__000.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Proto_Object_empty_pick", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Monster/Resource/berrybush/empty_picked/empty_picked__%03d.png", 5)), E_FAIL);
	
	//Item Object
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Log", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/Log.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Berries", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/Berries.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Cooked_berries", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/Cooked_berries.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Cooked_Meat_Monster", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/Cooked_Meat_Monster.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"CookedMeat", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/CookedMeat.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"CutGlass", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/CutGlass.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"CutStone", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/CutStone.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Meat_Monster", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/Meat_Monster.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"RawMeat", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/RawMeat.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Rocks_0", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/Rocks_0.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Rocks_1", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/Rocks_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Silk", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/Silk.png")), E_FAIL);
	FAILED_CHECK_RETURN(proto::Ready_Proto(L"Twigs", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../../Client/Bin/Resource/Texture/Item/Twigs.png")), E_FAIL);

	return S_OK;
}


HRESULT CLoading::SaveLoadingTexture(const _tchar* _key, TEXTUREID _textureTag, const _tchar* _path, int num)
{
	FAILED_CHECK_RETURN(proto::Ready_Proto(_key, CTexture::Create(m_pGraphicDev, _textureTag, _path)), E_FAIL);

	Save_TexturePath(L"Scene_STAGE",_key, _textureTag, _path, num);
	
	return S_OK;
}

unsigned int CLoading::Thread_Main(void* pArg)
{
	CLoading* pLoading = reinterpret_cast<CLoading*>(pArg);

	_uint iFlag(0);

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadingID())
	{
	case LOADING_STAGE:
		iFlag = pLoading->Loading_ForStage();
		break;

	case LOADING_BOSS:
		break;
	}

	LeaveCriticalSection(pLoading->Get_Crt());

	//_endthreadex(0);

	return iFlag;
}

CLoading* CLoading::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eID)
{
	CLoading* pInstance = new CLoading(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eID)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Loading Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLoading::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);
}
