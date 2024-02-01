#pragma once

#include "Engine_Define.h"
#include "Base.h"

class CItem;

class CInventoryMgr :
	public CBase
{
	DECLARE_SINGLETON(CInventoryMgr)
public:
	_bool	AddItem(CItem* _pItem);	//��ȯ����False�� �����۽������(�����۲���)
	CItem*	GetItemBox(_uint _uint);
	virtual void Free() override;

private:
	explicit CInventoryMgr();
	virtual ~CInventoryMgr();

private:
	CItem* m_pItemArr[15]; // �κ��丮


};

