#include "..\Include\stdafx.h"
#include "Monster.h"
#include "Export_System.h"
#include "Export_Utility.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CGameObject(pGraphicDev)
{
}

CMonster::CMonster(const CMonster& rhs)

{
}

CMonster::~CMonster()
{
}
