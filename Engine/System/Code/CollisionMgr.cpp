#include "CollisionMgr.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
	Free();
}

//_bool CCollisionMgr::Collision_Monster(
//	_vec3* pPlayerVTXPos,
//	_vec3* pMonsterVTXPos,
//	_vec3 pPlayerPos,
//	_vec3 vPlayerRight, 
//	_vec3 vPlayerUp,
//	_vec3 vMonsterPos,
//	_vec3 vMonsterRight,
//	_vec3 vMonsterUp)
//{
//	_bool bCollisionCheck[3] = {};
//	//obb
//	D3DXVec3Normalize(&vPlayerRight, &vPlayerRight);
//	D3DXVec3Normalize(&vMonsterUp, &vMonsterUp);
//
//	//1. �÷��̾� right �� �������� ���� 
//	_vec3 vPlayerVTX = pPlayerVTXPos[0] - pPlayerPos; // ���� ���� �߽��� ���� ����
//	_float fPlayerRightDot1 = D3DXVec3Dot(&vPlayerRight, &vPlayerVTX); // 3
//
//	_vec3 vPlayer1 = vPlayerUp * fPlayerRightDot1;
//
//	_vec3 vMonsterVTX = pMonsterVTXPos[0] - vMonsterPos; 
//	_float fMonsterDot = D3DXVec3Dot(&vMonsterUp, &vMonsterVTX); //���� ���� ���� ����
//
//	_vec3 vMonster1 = vMonsterUp * fMonsterDot; //�����Ͽ� ���� ���� ���� ���͸� �־��༭ ���ϱ�
//	_float fPlayerRightDot2 = D3DXVec3Dot(&vPlayerRight, &vMonster1);
//
//	_float fMonsterRightDot = D3DXVec3Dot(&vMonsterRight, &pMonsterVTXPos[0]);
//	_vec3 vMonster2 = vMonsterRight * fMonsterRightDot;
//	_float fPlayerRightDot3 = D3DXVec3Dot(&vPlayerRight, &vMonster2);
//
//	// �� �ڽ��� �Ÿ���
//	_vec3 vPlayerLookToMonster = vMonsterPos - pPlayerPos;
//	_float fPlayerLookToMonster = D3DXVec3Dot(&vPlayerRight, &vPlayerLookToMonster);
//
//	if (fPlayerRightDot1 + fPlayerRightDot2 + fPlayerRightDot3 > fPlayerLookToMonster)
//		bCollisionCheck[0] = true;
//
//	//2. �÷��̾� up���� �������� ����
//	_float fPlayerUpDot1 = D3DXVec3Dot(&vPlayerUp, &vPlayerVTX);
//	_float fPlayerUpDot2 = D3DXVec3Dot(&vPlayerUp, &vMonster1);
//	_float fPlayerUpDot3 = D3DXVec3Dot(&vPlayerUp, &vMonster2);
//	fPlayerLookToMonster = D3DXVec3Dot(&vPlayerUp, &vPlayerLookToMonster);
//
//	if (fPlayerUpDot1 + fPlayerUpDot2 + fPlayerUpDot3 > fPlayerLookToMonster)
//		bCollisionCheck[1] = true;
//	
//	//3. ���� right���� �������� ����
//	_float fMonsterRightDot1 = D3DXVec3Dot(&vMonsterRight, &vMonsterVTX);
//	_float fMonsterRightDot2 = D3DXVec3Dot(&vMonsterRight, &vPlayer1);
//	_float fMonsterRightDot3 = D3DXVec3Dot(&vMonsterRight, &vPlayer2);
//	//3. ���� up���� �������� ����
//
//
//
//	return _bool();
//}

_bool CCollisionMgr::Collision_Item(_vec3 pPlayerPos, _vec3 pItemPos, _vec3 vPlayerScale, _vec3 vItemScale)
{
	_float iDistanceX = fabs(pPlayerPos.x - pItemPos.x);
	_float fRadCX = vPlayerScale.x * 0.5f + vItemScale.x * 0.5f;

	_float fDistanceZ = fabs(pPlayerPos.z - pItemPos.z);
	_float fRadCY = vPlayerScale.y * 0.5f + vItemScale.y * 0.5f;

	if (fDistanceZ > fRadCY || iDistanceX > fRadCX)
		return false;

	return true;
}

void CCollisionMgr::Free()
{
}
