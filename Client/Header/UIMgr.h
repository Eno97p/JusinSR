#pragma once

#include "Engine_Define.h"
#include "Base.h"

class CItem;

class CUIMgr :
	public CBase
{
	DECLARE_SINGLETON(CUIMgr)

private:
	explicit CUIMgr();
	virtual ~CUIMgr();

public:
	CREATEINFO Get_CreateInfo(wstring pKey);

public:
	_bool	AddItem(LPDIRECT3DDEVICE9 pGraphicDev ,wstring strItemKey);	//��ȯ����False�� �����۽������(�����۲���)
	CItem*	GetItemBox(_uint _uint);

	void Ready_CreateInfo();

private:
	virtual void Free();

private:
	CItem* m_pItemArr[15]; // �κ��丮

	// �����
	vector<CREATEINFO> m_vecCreateInfo;


};

