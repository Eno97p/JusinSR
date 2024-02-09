#include "stdafx.h"
#include "CBonfire.h"

#include "Export_System.h"
#include "Export_Utility.h"





#include "CFire.h"

CBonfire::CBonfire(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResObject(pGraphicDev)

{
}

CBonfire::CBonfire(const CBonfire& rhs)
	: CResObject(rhs.m_pGraphicDev)
	, m_pFire(rhs.m_pFire)

{

}

CBonfire::~CBonfire()
{
}

HRESULT CBonfire::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_eObject_id = BON_FIRE;
	m_eBonfireCurState = BONFIRE_IDLE;
	m_fFrame = 0.0f;
	m_pTransForm->Set_Scale(_vec3(1.0f, 1.0f, 1.0f));

	return S_OK;
}

_int CBonfire::Update_GameObject(const _float& fTimeDelta)
{
	if (GetAsyncKeyState('T')) // 횃불
	{
		Set_DropBonfire();

	}
	if (GetAsyncKeyState('1')) // 횃불
	{

		AddFIre(1);
	}
	if (GetAsyncKeyState('2')) // 횃불
	{

		AddFIre(2);
	}
	if (GetAsyncKeyState('3')) // 횃불
	{

		AddFIre(3);
	}
	if (GetAsyncKeyState('4')) // 횃불
	{

		AddFIre(4);
	}
	if (GetAsyncKeyState('5')) // 횃불
	{

	}

	
	//
	if (m_eBonfireCurState == BONFIRE_DROP)
		{
			if (!m_bIsDropEnd)
			{
				m_fFrame += m_fFrameEnd * fTimeDelta;
				if (m_fFrame >= m_fFrameEnd)
				{
					m_fFrame = m_fFrameEnd;
					m_bIsDropEnd = true;
				
				}
			}
		}
	
	if (m_bIsDrop)
	{
		m_eBonfireCurState = BONFIRE_DROP;

	}

	if (m_pFire)
	{
		//불이 꺼지면 장작도 IDLE상태로
		if (m_pFire->Get_IsOff())
		{
			m_eBonfireCurState = BONFIRE_IDLE;
	
		}

	}
	//드롭이 끝나면 해당 이미지idle로 변경
	if (m_bIsDropEnd)
	{
		m_eBonfireCurState = BONFIRE_IDLE;
	}


	Check_FrameState();

	CGameObject::Update_GameObject(fTimeDelta);
	renderer::Add_RenderGroup(RENDER_ALPHA, this);


	//드롭이 끝나면 해당 위치에 불 업데이트
	if (m_bIsDropEnd)
	{
		
		if (m_pFire)
		{
			_vec3	vPos;
			m_pTransForm->Get_Info(INFO_POS, &vPos);
			m_pFire->Set_Pos(vPos);
			m_pFire->Update_GameObject(fTimeDelta);

		}


	}


	return 0;
}

void CBonfire::LateUpdate_GameObject()
{



	_vec3	vPos;
	m_pTransForm->BillBoard();
	m_pTransForm->Get_Info(INFO_POS, &vPos);
	Compute_ViewZ(&vPos);

	__super::LateUpdate_GameObject();

	if (m_pFire)
	{
		m_pFire->LateUpdate_GameObject();
	}

}

void CBonfire::Render_GameObject()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransForm->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);


	m_pBonfireTexCom[m_eBonfireCurState]->Set_Texture((_uint)m_fFrame);
	FAILED_CHECK_RETURN(SetUp_Material(), );
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	if (m_pFire)
	{
		m_pFire->Render_GameObject();
	}
}

void CBonfire::AddFIre(int _Value)
{
	if (m_pFire)
	{

		m_pFire->Set_FireLevel(_Value);

	}

}


HRESULT CBonfire::Add_Component()
{
	CComponent* pComponent = nullptr;
	_vec3 vPos;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(proto::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTex", pComponent });

	pComponent = m_pBonfireTexCom[BONFIRE_DROP] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Object_BonFIre_Drop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Object_BonFIre_Drop", pComponent });


	pComponent = m_pBonfireTexCom[BONFIRE_IDLE] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Object_Bonfire_Idle"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Object_Bonfire_Idle", pComponent });

	pComponent = m_pTransForm = dynamic_cast<CTransform*>(proto::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_Transform", pComponent });



	m_pTransForm->Get_Info(INFO_POS, &vPos);
	m_pTransForm->Set_Pos(vPos.x, 1.0f, vPos.z);

	return S_OK;
}

void CBonfire::Check_FrameState()
{


	if (m_eBonfireCurState != m_eBonfirerPrevState)
	{

		switch (m_eBonfireCurState)
		{
		case CBonfire::BONFIRE_IDLE:
		{
			m_pTransForm->Set_Scale(_vec3(1.0f, 1.0f, 1.0f));
			m_fFrameEnd = 0.0f;
			break;
		}
		case CBonfire::BONFIRE_DROP:
		{
			m_pTransForm->Set_Scale(_vec3(1.0f, 1.0f, 1.0f));
			m_fFrameEnd = 6.0f;
			m_pFire = CFire::Create(m_pGraphicDev);


			break;
		}
		default:
			break;
		}

		m_eBonfirerPrevState = m_eBonfireCurState;
		m_fFrame = 0.0f;
	}


}



CResObject* CBonfire::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CResObject* pInstance = new CBonfire(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBonfire::Free()
{
	Safe_Release(m_pFire);
	CGameObject::Free();
}


