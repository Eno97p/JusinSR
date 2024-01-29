#pragma once

#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer : public CBase
{
private:
	explicit CLayer();
	virtual ~CLayer();

public:
	unordered_multimap<const _tchar*, CGameObject*> Get_MapObject() { return m_mapObject; } // Tool ���


	vector<CGameObject*> findObject(const _tchar* _pObjTagName,CGameObject* _ObjType);
public:
	CComponent*		Get_Component(COMPONENTID eID, const _tchar* pObjTag, const _tchar* pComponentTag);

public:
	HRESULT		Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObject);

public:
	HRESULT		Ready_Layer();
	_int		Update_Layer(const _float& fTimeDelta);
	void		LateUpdate_Layer();

private:
	unordered_multimap<const _tchar*, CGameObject*>		m_mapObject;

	
public:
	static		CLayer*		Create();

private:
	virtual		void		Free();

};

END