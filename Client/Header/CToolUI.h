#pragma once
#include "CUI.h"

class CSlideUI;
class CItemTool;


class CToolUI :public CUI
{
	//�� ��ü�� �θ� ���� �����ǰ� ������ �����͸޴����� ���� �����ȴ�.
	//������ �Ŵ����� ���̾ �ִ� CUI�� ã�� Get�� ���� �ش� ��ü�� �����͸� �����Ѵ�.
	//�� ��ü�� �� �ǿ� ���� �����͸� �ѷ��ִ� ������ �Ѵ�.

protected:
	explicit CToolUI(LPDIRECT3DDEVICE9 pGraphicDev, UI_STATE eUIState, const _tchar* _UI_Name);
	explicit CToolUI(const CToolUI& rhs);
	virtual ~CToolUI();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;




	//�� �ڽĵ��� �� �Լ��� �������̵� �ؼ� ����Ѵ�.
	virtual void Pop_SidePanel();


	//���� �����͸� ���� �ϴ� �Ŵ����� ���� ������ , CUI���� 
	void SetGameData(CItemTool* _ItemTool, eITEMTOOL_TYPE _ItemType);
	//virtual void UpdateItemTool(eITEMTOOL_TYPE _ItemToolState);



	 static   CToolUI* Create(LPDIRECT3DDEVICE9	pGraphicDev, UI_STATE _State, _vec3 _pos, _vec3 _size, const _tchar* _UI_Name);

	virtual void Free() override;
protected:

	//���� ������ ���
	//�ڽĵ��� �� �����͸� ���� �ϰ� �ִ�
	CItemTool* m_pToolData[ITEM_END];

};

