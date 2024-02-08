#pragma once
#include "Export_Utility.h"
#include <CItem.h>

class CInvenBox :public CGameObject
{
protected:
	explicit CInvenBox(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, _uint iIndex, BOX_TYPE eType);
	explicit CInvenBox(const CInvenBox& rhs);
	virtual ~CInvenBox();

public:
	void Set_Item(CItem* pItem) { m_pItem = pItem; }
	
	CItem* Get_Item() { return m_pItem; }
	_float Get_fX() { return m_fX; }
	_float Get_fY() { return m_fY; }
	_float Get_SizeX() { return m_fSizeX; }
	_float Get_SizeY() { return m_fSizeY; }

public:
	virtual HRESULT Ready_GameObject()						 override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject()					 override;
	virtual void Render_GameObject()						 override;


	//virtual BOOL IsItemOn() { return m_bItemChek; }
	//virtual void SetItemOn(BOOL _ItemPut) { m_bItemChek = _ItemPut; }

public:
	//static CInvenBox* Create(LPDIRECT3DDEVICE9	pGraphicDev, UI_STATE _State, _vec3 _pos, _vec3 _size, const _tchar* _UI_Name, _uint _Index, float _Angle = 0.f);
	static CInvenBox* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, _uint iIndex, BOX_TYPE eType = INVEN);
	virtual HRESULT			Add_Component();
	virtual void Free();

private:
	Engine::CRcTex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;

	_vec2 m_vFontPos;

	_uint	m_iInvenIndex;
	_uint m_ItmeCount;

	_matrix				m_ViewMatrix, m_ProjMatrix;
	_float m_fX, m_fY, m_fSizeX, m_fSizeY;

	CItem* m_pItem; // 인벤토리일 경우 아이템을 넣어주지 않는다.

	BOX_TYPE m_eType; // 아이템 숫자 띄워줄지, 띄워주지 않을지 구분하는 용도
	
};

