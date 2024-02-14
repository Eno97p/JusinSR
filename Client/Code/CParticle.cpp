
#include "stdafx.h"
#include "CParticle.h"

#include "Export_Utility.h"


CParticle::CParticle(LPDIRECT3DDEVICE9 pGraphicDev, wstring _strObjName)
	:CGameObject(pGraphicDev, _strObjName)
	, m_pTextureCom(nullptr)
{
}

CParticle::CParticle(const CParticle& rhs)
	:CGameObject(rhs)
	, m_pTextureCom(nullptr)
{
	m_pVB->AddRef();
}

CParticle::~CParticle()
{
}

HRESULT CParticle::Ready_GameObject()
{

	m_dwFVF = FVF_PARTICLE;
	m_dwVtxSize = sizeof(VTXPARTICLE);

	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer
	(m_vbSize * m_dwVtxSize,	// ������ ���ؽ� ������ ũ��
		0,			// ���ؽ� ������ ����(0�� ��� ���� ����, d3dusage_dynamic�� ��� ���� ����)
		m_dwFVF,	// ���ؽ� �Ӽ� �ɼ�
		D3DPOOL_MANAGED, // ���� ������ managed
		&m_pVB,	// ������ ���ؽ� ���� �� ��ü
		NULL),	// ���� ����
		E_FAIL);


	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



	return S_OK;
}

_int CParticle::Update_GameObject(const _float& fTimeDelta)
{

	__super::Update_GameObject(fTimeDelta);
	renderer::Add_RenderGroup(RENDERID::RENDER_ALPHA, this);

	return 0;
}

void CParticle::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();


}

void CParticle::Render_GameObject()
{
	if (!m_ParticleList.empty())
	{
		preRender();

		m_pTextureCom->Set_Texture(0);
		m_pGraphicDev->SetFVF(m_dwFVF);
		m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);

		if (m_vbOffset >= m_vbSize)
			m_vbOffset = 0;

		VTXPARTICLE* v = 0;

		m_pVB->Lock(m_vbOffset * m_dwVtxSize,
			m_vbBatchSize * m_dwVtxSize,
			(void**)&v,
			m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);


		DWORD numParticlesInBatch = 0;

		std::list<Attribute>::iterator iter;

		for (iter = m_ParticleList.begin(); iter != m_ParticleList.end(); iter++)
		{
			if (iter->m_bAlive)
			{
				v->vPosition = iter->m_vPos;
				v->_color = iter->m_cColor;
				v++;
				numParticlesInBatch++;
				if (numParticlesInBatch == m_vbBatchSize)
				{
					m_pVB->Unlock();

					m_pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, m_vbOffset, m_vbBatchSize);

					m_vbOffset += m_vbBatchSize;
					if (m_vbOffset >= m_vbSize)
						m_vbOffset = 0;

					m_pVB->Lock(m_vbOffset * m_dwVtxSize,
						m_vbBatchSize * m_dwVtxSize,
						(void**)&v,
						m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0;
				}
			}

		}//end for

		m_pVB->Unlock();

		if (numParticlesInBatch)
		{
			m_pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, m_vbOffset, numParticlesInBatch);
		}

		m_vbOffset += m_vbBatchSize;


		FAILED_CHECK_RETURN(SetUp_Material(), );


	}



	postRender();
}


void CParticle::preRender()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, true);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE, FtoDw(m_fSize));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.f));

	//�Ÿ������� ��ƼŬ ũ�� ����
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.f));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.f));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.f));


}

void CParticle::postRender()
{

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, true);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void CParticle::Reset()
{

	list<Attribute>::iterator iter;
	for (iter = m_ParticleList.begin(); iter != m_ParticleList.end(); iter++)
	{
		resetParticle(&(*iter));
	}
}

float CParticle::GetRandomFloat(_float fLowBound, _float fHighBound)
{

	if (fLowBound >= fHighBound)
		return fLowBound;


	_float f = (rand() % 10000) * 0.0001f;
	return (f * (fHighBound - fLowBound) + fLowBound);
}


HRESULT CParticle::Add_Component()
{
	CComponent* pComponent = nullptr;

	//TEXTURE
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(proto::Clone_Proto(L"Rocks_0"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ GetObjName().c_str(), pComponent });

	return S_OK;
}

void CParticle::Free()
{
	Safe_Release(m_pVB);
	__super::Free();
}

