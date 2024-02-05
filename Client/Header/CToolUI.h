#pragma once
#include "CUI.h"

class CSlideUI;
class CItemTool;
class CSlideUI;
class CLightUI;
class CScienceUI;
class CClothUI;
class CWeaponUI;


class CToolUI :public CUI
{
	//�� ��ü�� �θ� ���� �����ǰ� ������ �����͸޴����� ���� �����ȴ�.
	//������ �Ŵ����� ���̾ �ִ� CUI�� ã�� Get�� ���� �ش� ��ü�� �����͸� �����Ѵ�.
	//�� ��ü�� �� �ǿ� ���� �����͸� �ѷ��ִ� ������ �Ѵ�.

protected:
	explicit CToolUI(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* _UI_Name);
	explicit CToolUI(const CToolUI& rhs);
	virtual ~CToolUI();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	//�� �ڽĵ��� �� �Լ��� �������̵� �ؼ� ����Ѵ�.
	virtual void Pop_SidePanel();

	//���� �����͸� ���� �ϴ� �Ŵ����� ���� ������ , CUI���� 
	void SetGameData(CItemTool* _ItemTool, eITEMTOOL_TYPE _ItemType);
	//virtual void UpdateItemTool(eITEMTOOL_TYPE _ItemToolState);

	const CUI* GetAliveUI() { return m_pAliveUI; }
	const CUI* GetEquimentI() { return m_pEquimentUI; }
	const CUI* GetLightUI() { return m_pLightUI; }
	const CUI* GetScienceUI() { return m_pScienceUI; }
	const CUI* GetClothUI() { return m_pClothUI; }
	const CUI* GetWeaponUI() { return m_pWeaponUI; }




	 static   CToolUI* Create(LPDIRECT3DDEVICE9	pGraphicDev, const _tchar* _UI_Name);


	virtual void Free() override;
protected:

	//���� ������ ���
	//�ڽĵ��� �� �����͸� ���� �ϰ� �ִ�
	CItemTool* m_pToolData[ITEM_END];


	BOOL m_bSlideState;
private:
	static  CUI* m_pAliveUI;
	static  CUI* m_pEquimentUI;
	static  CUI* m_pLightUI;
	static  CUI* m_pScienceUI;
	static  CUI* m_pClothUI;
	static  CUI* m_pWeaponUI;

	static CUI* m_pSlideUI[5];
};

