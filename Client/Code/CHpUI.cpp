
#include "CHpUI.h"



#include "Export_Utility.h"
#include "Export_System.h"

#include "Scene.h"
#include <Player.h>

CHpUI::CHpUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CStateUI(pGraphicDev)
{
}

CHpUI::CHpUI(const CHpUI& rhs)
	: CStateUI(rhs)
{
}

CHpUI::~CHpUI()
{
}

HRESULT CHpUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_fX = 680.f;
	m_fY = 110.f;

	m_fSizeX = 30.f;
	m_fSizeY = 30.f;

	__super::Ready_GameObject();

	m_frameEnd = 20.f;

	return S_OK;
}

_int CHpUI::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CHpUI::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();
	Check_State();
}

void CHpUI::Render_GameObject()
{
	__super::Render_GameObject();
}

HRESULT CHpUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(proto::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTex", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_UI_HP"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_UI_HP", pComponent });

	pComponent = m_pTransForm = dynamic_cast<CTransform*>(proto::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_Transform", pComponent });

	return S_OK;
}

void CHpUI::Check_State()
{
	CGameObject* pP = scenemgr::Get_CurScene()->GetGroupObject(eLAYER_TYPE::GAME_LOGIC, eOBJECT_GROUPTYPE::PLAYER)[0];
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pP);

	_float fHp = pPlayer->Get_PlayerHp();
	_float fMaxHp = pPlayer->Get_PlayerMaxHp();

	_float fFrame = (fMaxHp - fHp) / 10.f;
	
	if (fFrame < m_frameEnd)
		m_frame = fFrame;
}

CHpUI* CHpUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHpUI* pInstance = new CHpUI(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		MSG_BOX("UI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHpUI::Free()
{
	__super::Free();
}
