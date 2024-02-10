#include "stdafx.h"
#include "CTent.h"

#include "Export_System.h"
#include "Export_Utility.h"
#include <Mouse.h>
#include "SlotMgr.h"

CTent::CTent(LPDIRECT3DDEVICE9 pGraphicDev, _bool bInstall)
	: CResObject(pGraphicDev), m_bInstall(bInstall)
{
}

CTent::CTent(const CTent& rhs)
	: CResObject(rhs.m_pGraphicDev)
{

}

CTent::~CTent()
{
}

HRESULT CTent::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_eObject_id = TENT;
	m_eTentCurState = CTENT_DEFAULT;

	m_fDiffY = 1.f;
	m_fFrame = 0.0f;
	return S_OK;
}

_int CTent::Update_GameObject(const _float& fTimeDelta)
{

	Install_Obj();

	//���� �ڵ�
	if (GetAsyncKeyState('T')) // ȶ��
	{

		Set_Drop();
	}
	if (GetAsyncKeyState('1')) // ȶ��
	{

		Set_Enter();
	}
	if (GetAsyncKeyState('2')) // ȶ��
	{

		Set_Hit();
	}
	if (GetAsyncKeyState('3')) // ȶ��
	{
		Set_Destroy();

	}
	if (GetAsyncKeyState('4')) // ȶ��
	{
		Set_Destroy();

	}
	if (GetAsyncKeyState('5')) // ȶ��
	{
		Set_Burnt();
	}


	if (!m_bIsFrameStop)
		m_fFrame += m_fFrameEnd * fTimeDelta;









	Change_Frame_Event();

	CGameObject::Update_GameObject(fTimeDelta);
	renderer::Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CTent::LateUpdate_GameObject()
{



	Check_FrameState();




	_vec3	vPos;
	m_pTransForm->BillBoard();
	m_pTransForm->Get_Info(INFO_POS, &vPos);
	Compute_ViewZ(&vPos);

	__super::LateUpdate_GameObject();
}

void CTent::Render_GameObject()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransForm->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);



	m_pTentTexCom[m_eTentCurState]->Set_Texture((_uint)m_fFrame);
	FAILED_CHECK_RETURN(SetUp_Material(), );
	m_pBufferCom->Render_Buffer();



	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
}




HRESULT CTent::Add_Component()
{
	CComponent* pComponent = nullptr;
	_vec3 vPos;



	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(proto::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTex", pComponent });

	pComponent = m_pTentTexCom[CTENT_IDLE] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Object_Tent_Idle"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Object_Tent_Idle", pComponent });


	pComponent = m_pTentTexCom[CTENT_HIT] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Object_Tent_Hit"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Object_Tent_Hit", pComponent });

	pComponent = m_pTentTexCom[CTENT_ENTER] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Object_Tent_Enter"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Object_Tent_Enter", pComponent });

	pComponent = m_pTentTexCom[CTENT_DESTROY] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Object_Tent_Destroy"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Object_Tent_Destroy", pComponent });

	pComponent = m_pTentTexCom[CTENT_BURNT] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Object_Tent_Burnt"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Object_Tent_Burnt", pComponent });


	pComponent = m_pTentTexCom[CTENT_DEFAULT] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Object_Tent_Defalut_Idle"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Object_Tent_Defalut_Idle", pComponent });

	pComponent = m_pTentTexCom[CTENT_PLACE] = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Proto_Object_Tent_Place"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Object_Tent_Place", pComponent });


	pComponent = m_pTransForm = dynamic_cast<CTransform*>(proto::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_Transform", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(proto::Clone_Proto(L"Proto_Calculator"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Calculator", pComponent });






	m_pTransForm->Set_Scale(_vec3(4.5f, 4.5f, 4.5f));

	if (!m_bInstall)
	{
		m_pTransForm->Get_Info(INFO_POS, &vPos);
		m_pTransForm->Set_Pos(vPos.x, 1.7f, vPos.z);
	}

	return S_OK;
}

void CTent::Check_FrameState()
{
	if (m_eTentCurState != m_eTentPrevState)
	{
		switch (m_eTentCurState)
		{
		case CTent::CTENT_IDLE:
			m_fFrameEnd = 18.0f;
			break;
		case CTent::CTENT_HIT:
			m_fFrameEnd = 3.0f;
			break;
		case CTent::CTENT_ENTER:
			m_fFrameEnd = 7.0f;
			break;
		case CTent::CTENT_DESTROY:
			m_fFrameEnd = 16.0f;
			break;
		case CTent::CTENT_BURNT:
			m_fFrameEnd = 0.0f;
			break;
		case CTent::CTENT_PLACE:
			m_fFrameEnd = 7.0f;
			break;
		case CTent::CTENT_DEFAULT:
			m_fFrameEnd = 0.0f;
			break;
		default:
			break;
		}
		m_eTentPrevState = m_eTentCurState;
		m_fFrame = 0.0f;
	}



}

void CTent::Change_Frame_Event()
{
	if (m_bIsDrop)
	{
		if (m_eTentCurState == CTENT_DEFAULT)
		{
			m_eTentCurState = CTENT_PLACE;
		}

		if (m_bIsBurnt && !m_bIsDestroy)	//�ı����� ���� ���¿����� Ż �� ����
		{
			m_eTentCurState = CTENT_BURNT;
			return;
		}

		if (m_bIsDestroy)
		{
			m_eTentCurState = CTENT_DESTROY;
			if (m_fFrame > m_fFrameEnd)
			{

				m_bIsFrameStop = true;
				//ȸ���� �ٽô� �� ����
				return;
			}
		}

		if (m_eTentCurState == CTENT_PLACE && m_fFrame > m_fFrameEnd)
		{
			m_bIsFrameStop = true;
			m_eTentCurState = CTENT_IDLE;
		}

		else if (m_eTentCurState == CTENT_IDLE)
		{
			m_bIsFrameStop = false;
			if (m_fFrame > m_fFrameEnd)
			{
				m_fFrame = 0.0f;
			}
		}

		if (m_bIsEnter)
		{
			m_eTentCurState = CTENT_ENTER;
			if (m_fFrame > m_fFrameEnd)
			{
				m_eTentCurState = CTENT_IDLE;
				m_bIsEnter = false;
				m_fFrame = 0.0f;
			}
		}
		if (m_bIsHit)
		{

			m_eTentCurState = CTENT_HIT;
			if (m_fFrame > m_fFrameEnd)
			{
				m_eTentCurState = CTENT_IDLE;
				m_bIsHit = false;
				m_fFrame = 0.0f;
			}
		}





	}




}
void CTent::Install_Obj()
{
	if (!m_bInstall) return;

	auto& vecTerrain = scenemgr::Get_CurScene()->GetGroupObject(eLAYER_TYPE::GAME_LOGIC, eOBJECT_GROUPTYPE::TILE)[0];
	CTerrainTex* pTerrainBufferCom = dynamic_cast<CTerrainTex*>(scenemgr::Get_CurScene()->GetTerrainObject()->Find_Component(ID_STATIC, L"Proto_TerrainTex"));
	_vec3 vPos = m_pCalculatorCom->Picking_OnTerrain(g_hWnd, pTerrainBufferCom, vecTerrain->GetTransForm());

	vPos.y = 1.f;
	m_pTransForm->Set_Pos(vPos);

	if (Engine::GetMouseState(DIM_LB) == eKEY_STATE::TAP) // ��ġ �Ϸ�
	{
		m_bInstall = false;

		auto& vecMouse = scenemgr::Get_CurScene()->GetGroupObject(eLAYER_TYPE::ENVIRONMENT, eOBJECT_GROUPTYPE::MOUSE)[0];
		CMouse* pMouse = dynamic_cast<CMouse*>(vecMouse);
		pMouse->Set_Install(false);

		CSlotMgr::GetInstance()->Remove_InvenItem(m_iSlotNum);
	}
}

CTent* CTent::Create(LPDIRECT3DDEVICE9 pGraphicDev, _bool bInstall)
{
	CTent* pInstance = new CTent(pGraphicDev, bInstall);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTent::Free()
{
	CGameObject::Free();
}


