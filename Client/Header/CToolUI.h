#pragma once
#include "CUI.h"

class CSlideUI;
class CItemTool;
class CToolUI :public CUI
{
	//ItemTool�� ��ȣ�ۿ� �ϴ� ������ �����ϱ�


protected:
	explicit CToolUI(LPDIRECT3DDEVICE9 pGraphicDev, UI_STATE eUIState, const _tchar* _UI_Name);
	explicit CToolUI(const CToolUI& rhs);
	virtual ~CToolUI();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;





	virtual void Pop_SidePanel();
	void SetGameData(CItemTool* _ItemTool, eITEMTOOL_TYPE _ItemType);
	//virtual void UpdateItemTool(eITEMTOOL_TYPE _ItemToolState);


	virtual void Free() override;
protected:

	//���� ������ ���
	CItemTool* m_pToolData[ITEM_END];

};

