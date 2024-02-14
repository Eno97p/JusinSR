#include "stdafx.h"
#include "CObjectRock.h"
#include "Export_Utility.h"
#include "Component.h"
#include "ItemBasic.h"
CObjectRock::CObjectRock(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResObject(pGraphicDev)
{
}

CObjectRock::CObjectRock(const CObjectRock& rhs)
	: CResObject(rhs.m_pGraphicDev)
{
}

CObjectRock::~CObjectRock()
{
}

HRESULT CObjectRock::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	_vec3 vPos;
	m_pTransForm->Set_Scale(_vec3(2.f, 2.f,2.f));
	m_pTransForm->Get_Info(INFO_POS, &vPos);
	m_pTransForm->Set_Pos(vPos.x, 1.1f, vPos.z);

	Ready_Stat();
	m_eCurState = RES_IDLE;
	m_eObject_id = ROCK;
	m_fFrame = 0;
	m_fDiffY = 1.f;

	return S_OK;
}

_int CObjectRock::Update_GameObject(const _float& fTimeDelta)
{

	Change_Frame_Event();
	m_pTransForm->Get_Info(INFO_POS, &m_vOriginPos);
	CGameObject::Update_GameObject(fTimeDelta);


	renderer::Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}

void CObjectRock::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();
	m_pTransForm->BillBoard();
	_vec3	vPos;
	m_pTransForm->Get_Info(INFO_POS, &vPos);
	__super::Compute_ViewZ(&vPos);
}

void CObjectRock::Render_GameObject()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransForm->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);


	m_pTextureCom[m_eCurState]->Set_Texture(m_fFrame);
	FAILED_CHECK_RETURN(SetUp_Material(), );
	m_pBufferCom->Render_Buffer();



	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);


}

HRESULT CObjectRock::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(proto::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTex", pComponent });

	pComponent = m_pTextureCom[RES_IDLE] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Nomal_Rock"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Nomal_Rock", pComponent });

	pComponent = m_pTransForm = dynamic_cast<CTransform*>(proto::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_Transform", pComponent });


	return S_OK;
}

void CObjectRock::Change_Frame_Event()
{
	if (m_Stat.fHP <= 3.f && m_Stat.fHP != 0)
	{
		//m_pTransForm->Set_Scale(_vec3(1.f, 1.f, 1.f));
		m_fFrame = 1;
	}
	if (m_Stat.fHP <= 1)
	{
		//m_pTransForm->Set_Scale(_vec3(1.f, 1.f, 1.f));
		m_fFrame = 2;
	}

	if (m_Stat.fHP <= 0)
	{

		if (m_Stat.bDead == false)
		{
			CreateItem(L"Rocks_0",this, this->m_pGraphicDev);
			CreateItem(L"Rocks_1",this, this->m_pGraphicDev);


		}


		m_Stat.bDead = true;
		m_fFrame = 3;
	}
}

void CObjectRock::Check_FrameState()
{
	
}

void CObjectRock::Ready_Stat()
{
	m_Stat.strObjName = L"����";
	m_Stat.fHP = 6;
	m_Stat.fMxHP = 6;
	m_Stat.fSpeed = 1;
	m_Stat.bDead = false;
}

CResObject* CObjectRock::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CResObject* pInstance = new CObjectRock(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		return nullptr;
	}

	return pInstance;
}

void CObjectRock::Free()
{
	CGameObject::Free();
}

