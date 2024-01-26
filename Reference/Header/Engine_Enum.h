#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum WINMODE { MODE_FULL, MODE_WIN };

	// Dynamic 컴포넌트 경우 매 프레임마다 갱신해야하는 컴포넌트 집단
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };

	enum INFO {	INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };

	enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };

	enum RENDERID { RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END };

	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
	enum MOUSEMOVESTATE {	DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	enum PLAYERWEAPONSTATE { AXE, PICK, HAMMER, SPEAR, STAT_END }; //플레이어 무기 상태
	//enum PLAYERSTATE {
	//	IDLE, MOVE_DOWN, MOVE_UP, MOVE_RIGHT, MOVE_LEFT,  //플레이어 행동상태
	//	ATTACK, USINGTOOL, DIALOG, SLEEP, HIT, DEAD, STATE_END
	//};
	/*enum PLAYERSTATE {
		IDLE_DOWN,IDLE_UP,IDLE_SIDE, MOVE_DOWN, MOVE_UP, MOVE_SIDE,
		BUILD_DOWN, BUILD_UP, BUILD_SIDE,PICKUP_UP, PICKUP_DOWN, PICKUP_SIDE,
		HIT_DOWN,HIT_UP, HIT_SIDE, ATTACK_DOWN, ATTACK_UP, ATTACK_SIDE,
		FALLDOWN,WAKEUP,EAT,
		 STATE_END
	};*/

	enum PLAYERSTATE {
		IDLE, MOVE, BUILD, PICKUP,HIT,ATTACK,FALLDOWN,WAKEUP,EAT,STATE_END
	};
	enum PLAYERLOOK { LOOK_DOWN, LOOK_RIGHT,LOOK_LEFT, LOOK_UP, LOOK_END };
}
#endif // Engine_Enum_h__
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_idle_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/idle_down/idle_down__%03d.png", 22)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_idle_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/idle_up/idle_up__%03d.png", 22)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_idle_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/idle_side/idle_side__%03d.png", 23)), E_FAIL);
//
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_run_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/run_down/run_down__%03d.png", 6)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_run_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/run_up/run_up__%03d.png", 6)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_run_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/run_side/run_side__%03d.png", 6)), E_FAIL);
//
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_build_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/build_down/build_down__%03d.png", 6)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_build_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/build_up/build_up__%03d.png", 6)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_build_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/build_side/build_side__%03d.png", 6)), E_FAIL);
//
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_pickup_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/pickup_down/pickup_down__%03d.png", 6)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_pickup_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/pickup_up/pickup_up__%03d.png", 6)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_pickup_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/pickup_side/pickup_side__%03d.png", 6)), E_FAIL);
//
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_hit_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/hit_std/hit_std__%03d.png", 7)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_hit_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/hit_up/hit_up__%03d.png", 7)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_hit_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/hit_side/hit_side__%03d.png", 7)), E_FAIL);
//
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_punch_down", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/attack/punch_down/punch_down__%03d.png", 11)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_punch_up", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/attack/punch_up/punch_up__%03d.png", 11)), E_FAIL);
//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Player_Unarmed_punch_side", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/UnArmed/attack/punch_side/punch_side__%03d.png", 11)), E_FAIL);
