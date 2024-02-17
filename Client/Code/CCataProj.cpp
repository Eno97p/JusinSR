#include "stdafx.h"
#include "CCataProj.h"
#include "Export_Utility.h"
#include "Player.h"

CCataProj::CCataProj(LPDIRECT3DDEVICE9 pGraphicDev, wstring _strObjName)
	:CTrap(pGraphicDev, _strObjName)
	, m_fSpeed(6.f)
{
}

CCataProj::CCataProj(const CCataProj& rhs)
	:CTrap(rhs)
{
}

CCataProj::~CCataProj()
{
}

HRESULT CCataProj::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransForm->Set_Scale(_vec3(0.3f, 0.3f, 0.3f));
	return S_OK;
}

_int CCataProj::Update_GameObject(const _float& fTimeDelta)
{

	if (m_eCurState == eTRAP_STATE::MOVE)//�����̴»��¸� �÷��̾�üũ
	{
		if (PlayerHit(0.3f))//�÷��̾� �¾������
		{
			m_eCurState = eTRAP_STATE::DEAD;
			dynamic_cast<CPlayer*>(scenemgr::Get_CurScene()->GetPlayerObject())->Set_Attack(1);
			m_pAnimCom->ChangeAnimation(L"HIT");
			m_pAnimCom->SetLoopAnimator(false);
		}
		else//�ƴϸ��̵�
		{
			MovePos(fTimeDelta);
		}
	}

	if (m_eCurState == eTRAP_STATE::DEAD)//��������ϰ�� ����ִϸ��̼� �ٳ����� ����
	{
		if (m_pAnimCom->IsFinish(L"HIT"))
		{
			DeleteObject(this);
		}
	}


	return __super::Update_GameObject(fTimeDelta);
}

void CCataProj::Render_GameObject()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransForm->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	m_pAnimCom->SetAnimTexture();
	FAILED_CHECK_RETURN(SetUp_Material(), );

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

CCataProj* CCataProj::Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring _strObjName, _vec3 vPos)
{
	CCataProj* pInstance = new CCataProj(pGraphicDev, _strObjName);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	pInstance->GetTransForm()->Set_Pos(vPos);

	return pInstance;
}

void CCataProj::MovePos(const _float& fTimeDelta)
{

	_vec3 vPos(-1.f, 0.f, 0.f);


	m_pTransForm->Move_Pos(&vPos, m_fSpeed, fTimeDelta);

}

HRESULT CCataProj::Add_Component()
{
	CComponent* pComponent = nullptr;
	_vec3 vPos;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(proto::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTex", pComponent });


	pComponent = m_pReverseCom = dynamic_cast<CRvRcTex*>(proto::Clone_Proto(L"Proto_RvRcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RvRcTex", pComponent });

	pComponent = m_pTransForm = dynamic_cast<CTransform*>(proto::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_Transform", pComponent });

	pComponent = m_pAnimCom = dynamic_cast<CAnimator*>(proto::Clone_Proto(L"Proto_Anim"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_Anim", pComponent });


	m_pAnimCom->AddAnimation(L"AIR", proto::Clone_ProtoAnim(L"PROJ_CATAPULT_AIR"));//�Ʒ�

	m_pAnimCom->AddAnimation(L"HIT", proto::Clone_ProtoAnim(L"PROJ_CATAPULT_HIT"));


	m_pAnimCom->SetCurAnimation(L"AIR");
	m_pAnimCom->SetLoopAnimator(true);
	m_eCurState = eTRAP_STATE::MOVE;


	return S_OK;
}
