#pragma once

#include "GameObject.h"

namespace Engine
{
	class CRcTex;
	class CTexture;
}

class CUI
	: public Engine::CGameObject
{
protected:
	explicit CUI(LPDIRECT3DDEVICE9 pGraphicDev, UI_STATE eUIState, const _tchar* _UI_Name);
	explicit CUI(const CUI& rhs);
	virtual ~CUI();

public:
	virtual HRESULT Ready_GameObject(_vec3 _pos, _vec3 _size, float _Angle = 0);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject()					 override;
	virtual void Render_GameObject()						 override;



	virtual BOOL UI_Collision();
	virtual BOOL IsItemOn() { return m_bItemChek; }
	virtual void SetItemOn(BOOL _ItemPut) { m_bItemChek = _ItemPut; }
	virtual HRESULT			Add_Component();
protected:
	Engine::CTexture* m_pTextureCom;
	Engine::CRcTex* m_pBufferCom;
	UI_STATE		m_eUIState;
protected:
	_float m_fX;
	_float m_fY;
	_float m_fSizeX;
	_float m_fSizeY;
	_float m_fAngle;

	POINT m_MousePoint;
	BOOL m_bItemChek;
public:
	static CUI* Create(LPDIRECT3DDEVICE9	pGraphicDev, UI_STATE _State, _vec3 _pos, _vec3 _size, const _tchar* _UI_Name, float _Angle = 0.f);

public:
	virtual void Free() override;
};

