#pragma once
#include "CUI.h"

class CSlideUI;

class CItemTool;
class CSlideUI;
class CLightUI;
class CScienceUI;
class CClothUI;
class CWeaponUI;
class CAliveUI;
class CEquiment;


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

	const CAliveUI* GetAliveUI() { return m_pAliveUI; }
	const CEquiment* GetEquimentI() { return m_pEquimentUI; }
	const CLightUI* GetLightUI() { return m_pLightUI; }
	const CScienceUI* GetScienceUI() { return m_pScienceUI; }
	const CClothUI* GetClothUI() { return m_pClothUI; }
	const CWeaponUI* GetWeaponUI() { return m_pWeaponUI; }




	 static   CToolUI* Create(LPDIRECT3DDEVICE9	pGraphicDev, const _tchar* _UI_Name);


	virtual void Free() override;
protected:

	//���� ������ ���
	//�ڽĵ��� �� �����͸� ���� �ϰ� �ִ�
	CItemTool* m_pToolData[ITEM_END];


	BOOL m_bSlideState;
private:
	static  CAliveUI* m_pAliveUI;
	static  CEquiment* m_pEquimentUI;
	static  CLightUI* m_pLightUI;
	static  CScienceUI* m_pScienceUI;
	static  CClothUI* m_pClothUI;
	static  CWeaponUI* m_pWeaponUI;

	static CSlideUI* m_pSlideUI[5];
};

