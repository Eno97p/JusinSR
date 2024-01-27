#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CRcTex;
class CTexture;
class CTransform;
END

struct ItemInfo
{
	_uint ItemCount;//�����۰��� or ����� ��������
	_uint HP;
	_uint Hungry;
	_uint Mental;
	_uint Demage;
};

class CItem :
	public CGameObject
{
protected:
	explicit CItem(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* _key,_vec3 _vPos);
	explicit CItem(const CItem& rhs);
	virtual ~CItem();

public:
	const wstring& GetItemKey() const { return m_strItemKey; }
	void AddItemCount(_uint _num) { m_tItemInfo.ItemCount += _num; }
	void MinusItemCount(_uint _num)
	{
		if (m_tItemInfo.ItemCount > _num)
			m_tItemInfo.ItemCount -= _num;
	}

	void SetPos(const _vec3& _vPos);

	const ItemInfo& GetItemInfo() { return m_tItemInfo; }
	void SetItemInfo(const ItemInfo& _itemInfo) { m_tItemInfo = _itemInfo; }
public:
	//���������Լ�
	virtual _bool UseItem() { return false; }
	virtual _bool DropItem() { return false; }

public:
	virtual HRESULT Ready_GameObject()						 override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void		LateUpdate_GameObject()override;
	virtual void		Render_GameObject()override;

	static CItem* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* _key, _vec3 _vPos);

private:
	HRESULT			Add_Component();
	virtual void MousePicking();
	void Billboard();

private:
	virtual void Free();

protected:
	Engine::CRcTex* m_pBufferCom;
	Engine::CTransform* m_pTransformCom;
	Engine::CTexture* m_pTextureCom;

private:
	wstring	m_strItemKey;//�ؽ�ó Ű�� �� ������ Ű��
	ItemInfo	m_tItemInfo;	//�����۰���
};

