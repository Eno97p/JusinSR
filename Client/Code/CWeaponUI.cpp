#include"CWeaponUI.h"
#include "Export_Utility.h"
#include "Export_System.h"





CWeaponUI::CWeaponUI(LPDIRECT3DDEVICE9 pGraphicDev, UI_STATE eUIState, const _tchar* _UI_Name)
	:CToolUI(pGraphicDev, _UI_Name)

{
	m_eUIState = eUIState;
}

CWeaponUI::CWeaponUI(const CWeaponUI& rhs)
	: CToolUI(rhs)
{
}

CWeaponUI::~CWeaponUI()
{
}

_int CWeaponUI::Update_GameObject(const _float& fTimeDelta)
{

	__super::Update_GameObject(fTimeDelta);
	if (UI_Collision() && Engine::Get_DIMouseState(DIM_LB) & 0x80)
	{
		Pop_SidePanel(true);

	}
	return 0;
}

CWeaponUI* CWeaponUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, UI_STATE _State, _vec3 _pos, _vec3 _size, const _tchar* _UI_Name, float _Angle)
{
	CWeaponUI* pInstance = new CWeaponUI(pGraphicDev, _State, _UI_Name);
	if (FAILED(pInstance->Ready_GameObject(_pos, _size, _Angle)))
	{
		Safe_Release(pInstance);
		MSG_BOX("UI Create Failed");
		return nullptr;
	}

	return pInstance;
}
void CWeaponUI::Free()
{
	//���� ������Ʈ ����, ���� ������� ����Ǹ� �ش� ������ �ʿ� ����
	this->m_pBufferCom->Release();
	this->m_pTextureCom->Release();
	this->m_pTransForm->Release();
	__super::Free();
}
