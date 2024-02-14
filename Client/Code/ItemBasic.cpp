#include "ItemBasic.h"
#include "Export_Utility.h"
#include "stdafx.h"
#include "SlotMgr.h"
#include <Terrain.h>

CItemBasic::CItemBasic(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev), m_bChangeRander(false)
{
}

CItemBasic::CItemBasic(LPDIRECT3DDEVICE9 pGraphicDev, wstring _strObjName)
	: CItem(pGraphicDev, _strObjName)
{
}

CItemBasic::CItemBasic(const CItem& rhs)
	: CItem(rhs)
{
}

CItemBasic::~CItemBasic()
{
}

void CItemBasic::Pickup_Item(_vec3 vSlotPos)
{
	m_vPos = m_pTransForm->Get_Pos();
	m_pCalculatorCom->Change_OnObjectMatrix(g_hWnd, &m_vPos);
	m_bChangeRander = true;

	m_vSlotPos = vSlotPos;

	m_fX = m_vPos.x;
	m_fY = m_vPos.y;
	m_fSizeX = 15.f;
	m_fSizeY = 15.f;
	m_pTransForm->Set_Pos(_vec3(m_fX - WINCX * 0.5f, -m_fY + WINCY * 0.5f, 0.0f));
	m_pTransForm->Set_Scale(_vec3(m_fSizeX, m_fSizeY, 0.f));
	//m_pTransForm->Rotation(Engine::ROT_Z, D3DXToRadian(180.f));

	D3DXMatrixIdentity(&m_ViewMatrix);
	D3DXMatrixOrthoLH(&m_ProjMatrix, WINCX, WINCY, 0.0f, 1.f);
}

HRESULT CItemBasic::Ready_GameObject()
{
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	Set_ObjState();
	m_fDiffY = -4.f;

    return S_OK;
}

_int CItemBasic::Update_GameObject(const _float& fTimeDelta)
{

	CGameObject::Update_GameObject(fTimeDelta);

	if (m_bChangeRander)
	{
		if (m_vSlotPos.y - m_fY <= 0.5f)
		{
			_vec3 vSlotPos = {};
			CSlotMgr::GetInstance()->AddItem(m_pGraphicDev, m_strObjName, &vSlotPos);
			DeleteObject(this);
			//return 0x80000000;
		}
			
		// ������ �Ծ����� ���������� �̵�
		m_fX += (m_vSlotPos.x - m_fX) * 5.f * fTimeDelta;
		m_fY += (m_vSlotPos.y - m_fY) * 5.f * fTimeDelta;

		m_pTransForm->Set_Pos(_vec3(m_fX - WINCX * 0.5f, -m_fY + WINCY * 0.5f, 0.1f));
		m_pTransForm->Set_Scale(_vec3(m_fSizeX, m_fSizeY, 0.f));
	}
	else m_pTransForm->BillBoard();

	MousePicking();

	if (m_bIsCreateByObject)
	{
		DropMotion(fTimeDelta);
	}

	renderer::Add_RenderGroup(m_bChangeRander ? RENDER_UI : RENDER_ALPHA, this);

	return 0;
}

void CItemBasic::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();
	_vec3	vPos;
	m_pTransForm->Get_Info(INFO_POS, &vPos);
	__super::Compute_ViewZ(&vPos);
}

void CItemBasic::Render_GameObject()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransForm->Get_WorldMatrix());

	if (m_bChangeRander)
	{
		m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
		m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);
	}

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	if (!m_bChangeRander) m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	m_pTextureCom->Set_Texture(0);
	if (!m_bChangeRander) FAILED_CHECK_RETURN(SetUp_Material(), );
	m_pBufferCom->Render_Buffer();

	if (!m_bChangeRander) m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	scenemgr::Get_CurScene()->EndOrtho();
}

void CItemBasic::DropMotion(const _float& fTimeDelta)
{
	const float gravity = 9.8f;
	_vec3 vDirUp;
	_vec3 vDirRight;
	_vec3 vDirLook;
	_vec3 vOrigin;

	// �������� �ʱ� ��ġ �� ���� ���� ��������
	_float fSpeed = 20.f;

	m_pTransForm->Get_Info(INFO_POS, &vOrigin);
	
	m_pTransForm->Get_Info(INFO_UP, &vDirUp);
	m_pTransForm->Get_Info(INFO_RIGHT, &vDirRight);
	m_pTransForm->Get_Info(INFO_LOOK, &vDirLook);

	if (!bHowFar)
	{
		m_pTransForm->Move_Pos(&vDirUp, fSpeed, fTimeDelta);
		if (vOrigin.y > 0.8f)   // ������ �ö� ���ΰ�
		{
			bHowFar = true;
		}
	}
	else // �������� �Ʒ��� �������� ���� �߷��� ������ �޾� ������ �
	{
		if (vOrigin.y < 0.3f)   // ������ ������ ���ΰ�
		{
			m_pTransForm->Set_Pos(vOrigin.x+iPos, vOrigin.y, vOrigin.z+iPos);
			m_bIsCreateByObject = false;
			return;
		}

		// �������� �ӵ��� �߷� ���ӵ��� ���Ͽ� ������ � ����
		fItemSpeed += gravity * fTimeDelta;
		m_pTransForm->Move_Pos(&(-vDirUp * fItemSpeed), fSpeed, fTimeDelta);
	}

	// x������ �̵�
	//if(!m_bHowToDir)
	//	m_pTransForm->Move_Pos(&(vDirLook * m_iSign), fSpeed * 0.5f, fTimeDelta);
	//else{
	//	// z������ �̵�
	m_pTransForm->Move_Pos(&(vDirRight * m_iSign), fSpeed * 0.5f, fTimeDelta);//���⼭�� �ӵ��� �Ÿ���
	//}





	//_vec3	vDirUp;
	//_vec3	vDirRight;
	//_vec3	vDirLook;
	//_vec3   vOrigin;
	//

	//_float fSpeed = 10.f;


	//m_pTransForm->Get_Info(INFO_POS, &vOrigin);
	//m_pTransForm->Get_Info(INFO_UP, &vDirUp);
	//m_pTransForm->Get_Info(INFO_RIGHT, &vDirRight);
	//m_pTransForm->Get_Info(INFO_LOOK, &vDirLook);

	//

	//if (bHowFar)
	//{
	//	m_pTransForm->Move_Pos(&-vDirUp, fSpeed, fTimeDelta);
	//	if (vOrigin.y < 0.7f)	//������ ������ ���ΰ�
	//	{
	//		m_bIsCreateByObject = false;
	//	}
	//}
	//else if(!bHowFar)
	//{
	//	m_pTransForm->Move_Pos(&vDirUp, fSpeed, fTimeDelta);
	//	if (vOrigin.y > 1.0f)	//������ �ö� ���ΰ�
	//	{
	//		bHowFar = true;
	//	}
	//}

	//m_pTransForm->Move_Pos(&(vDirRight* m_iSign), fSpeed*0.5,  fTimeDelta);



	////m_pTransForm->Move_Pos(&(vDirLook* m_iSign), fSpeed,  fTimeDelta);
	//



	

	

}

void CItemBasic::CheckSign(int _iSign, int _Dir)
{
	{
		//��ȣ ����ó��
		if (_iSign > 1 || _iSign < -1 || _iSign == 0)
			return;
		//���� ����ó��
		if (_Dir > 1 || _Dir < 0)
			return;
		if (_iSign == 1)
			m_iSign = 1;
		else
			m_iSign = -1;

		if (_Dir == 0)
			m_bHowToDir = false;    //x���� ����
		else
			m_bHowToDir = true;	    //z���� ����



	}

}

CItem* CItemBasic::Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring _szName)
{
	CItem* pInstance = new CItemBasic(pGraphicDev, _szName);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

    return pInstance;
}

void CItemBasic::Free()
{
	__super::Free();
}
