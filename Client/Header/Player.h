#pragma once

#include "Base.h"
#include "GameObject.h"

namespace Engine {

class CRcTex;
class CRvRcTex;
class CTexture;
class CTransform;
class CCalculator;
class CPlayerStatus;

}



class CPlayer :	public Engine::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev,wstring _strName);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer();

public:
	virtual HRESULT Ready_GameObject()						 override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject()					 override;
	virtual void Render_GameObject()						 override;

private:
	HRESULT			Add_Component();
	void			Key_Input(const _float& fTimeDelta);
	HRESULT			SetUp_Material();

	void			Height_OnTerrain();
	_vec3			Picking_OnTerrain();
	void			Check_State();
	void			Set_Scale();
	void			Set_Stat();

	void BillBoard();

private:
	Engine::CRcTex*		m_pBufferCom;
	Engine::CRvRcTex*	m_pReverseCom;
	Engine::CTexture*	m_pTextureCom[LOOKDIR::LOOK_END][PLAYERSTATE::STATE_END];
	Engine::CCalculator*	m_pCalculatorCom;

	_float				m_fFrame = 0.f;
	_float				m_fFrameEnd;

	PLAYERSTATE m_eCurState;
	PLAYERSTATE m_ePreState;

	LOOKDIR  m_ePlayerLookAt;
	_bool		m_Dirchange;
	_bool m_bAttack;
	OBJSTAT  m_Stat;
public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9	pGraphicDev,wstring _strName);
	static CPlayer*		Create(LPDIRECT3DDEVICE9	pGraphicDev);

private:
	virtual void Free() override;
};

