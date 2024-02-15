#include "ResObject.h"
#include "ItemBasic.h"

CResObject::CResObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev),
	m_eCurState(RES_DEAD),
	m_ePreState(RES_DEAD),
	m_bHit(false),
	m_fFrame(0),
	m_fFrameEnd(0),
	m_ePlayerLook(LOOK_END)
{
}

CResObject::CResObject(const CResObject& rhs)
	: CGameObject(rhs.m_pGraphicDev),
	m_eCurState(rhs.m_eCurState),
	m_ePreState(rhs.m_ePreState),
	m_bHit(false),
	m_fFrame(rhs.m_fFrame),
	m_fFrameEnd(rhs.m_fFrameEnd),
	m_ePlayerLook(rhs.m_ePlayerLook)
{
}

CResObject::~CResObject()
{
}



HRESULT CResObject::Ready_GameObject()
{
	return S_OK;
}

_int CResObject::Update_GameObject(const _float& fTimeDelta)
{
	return 0;
}

void CResObject::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();
}

void CResObject::Render_GameObject()
{
}

void CResObject::Free()
{
	__super::Free();
}




void CResObject::CreateItem(const _tchar* _itemName, CGameObject* _Type, LPDIRECT3DDEVICE9 pGraphicDev)
{

	srand(static_cast<unsigned int>(time(nullptr)));
	int iItemCount = rand() % 1 + 3;	//������ ������
	for (int i = 0; i < iItemCount; ++i)
	{

		_vec3 vPos;
		_Type->GetTransForm()->Get_Info(INFO_POS, &vPos);//m_pTransForm->Get_Info(INFO_POS, &vPos);
		CGameObject* pGameObj = CItemBasic::Create(pGraphicDev, _itemName);
		dynamic_cast<CItemBasic*>(pGameObj)->SetCreateByObject();
		//������ ��ü�� �� ����� ���ư� ���� ������ �¾��.
		pGameObj->GetTransForm()->Set_Pos(vPos.x, 0.f, vPos.z);
		scenemgr::Get_CurScene()->AddGameObject(eLAYER_TYPE::GAME_LOGIC, eOBJECT_GROUPTYPE::ITEM, pGameObj);


	}


}

const tuple<_vec3, _vec3, _vec3> CResObject::Get_Info_vec()
{
	if(scenemgr::Get_CurScene()->GetPlayerObject() == nullptr)
		return make_tuple(_vec3(0,0,0), _vec3(0,0,0), _vec3(0,0,0));

	decltype(auto) pPlayer = scenemgr::Get_CurScene()->GetPlayerObject();
	
	Engine::CTransform* pPlayerTransformCom = pPlayer->GetTransForm();

	_vec3 PlayerPos;
	_vec3 thisLook;
	_vec3 thisUp;
	this->GetTransForm()->Get_Info(INFO_LOOK, &thisLook);
	this->GetTransForm()->Get_Info(INFO_UP, &thisUp);
	pPlayerTransformCom->Get_Info(INFO_POS, &PlayerPos);



	return make_tuple(PlayerPos, thisLook, thisUp);
}
