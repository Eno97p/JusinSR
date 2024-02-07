#include "stdafx.h"
#include "UIMgr.h"
#include"CItem.h"
#include "InvenBoxMgr.h"
#include <ItemTool.h>

IMPLEMENT_SINGLETON(CUIMgr)

CUIMgr::CUIMgr()
{
	for (int i = 0; i < 15; i++)
	{
		m_pItemArr[i] = nullptr;
	}
}

CUIMgr::~CUIMgr()
{
	Free();
}

CREATEINFO CUIMgr::Get_CreateInfo(wstring pKey)
{
	for (auto& iter : m_vecCreateInfo)
	{
		if (iter.strKeyName == pKey)
			return iter;
	}

	return CREATEINFO();
}

//������ ������н� false��ȯ
_bool CUIMgr::AddItem(LPDIRECT3DDEVICE9 pGraphicDev, wstring strItemKey)
{
	//int i = 0;

	//for (auto& itemBox : m_pItemArr)
	//{
	//	if (nullptr == itemBox && _pItem->IsEquipment())// ������ĭ�� ����� ���������� �����������
	//	{
	//		itemBox = _pItem;
	//		return true;
	//	}

	//	if (nullptr != itemBox && (!_pItem->IsEquipment()))//���������ְ� �Ҹ�ǰ�������������
	//	{
	//		if (itemBox->GetObjName()== _pItem->GetObjName())//�ش�ĭ�� �̸��� ���� ���������������
	//		{
	//			itemBox->AddItemCount(_pItem->GetItemInfo().ItemCount);
	//			return true;
	//		}
	//	}
	//}

	//for (auto& itemBox : m_pItemArr)
	//{
	//	if (itemBox == nullptr)
	//	{
	//		itemBox = _pItem;
	//		return true;
	//	}
	//}
	vector<CInvenBox*> vecBox = CInvenBoxMgr::GetInstance()->Get_BoxList(INVEN);

	for (auto& box : vecBox) // �κ��丮 ��ĭ �ִ��� ������ üũ
	{
		if (box->Get_Item() == nullptr) // �������� ���ٸ� �κ��� ������ ����
		{
			_vec3 vPos;
			vPos.x = box->Get_fX();
			vPos.y = box->Get_fY();

			CItem* pItem = CItemTool::Create(pGraphicDev, strItemKey, vPos, UI_ITEM_INVEN);
			box->Set_Item(pItem);
			return true;
		}

		if (box->Get_Item()->GetObjName() == strItemKey) // ���� �������� �ִٸ� ������ ī��Ʈ ����
		{
			box->Get_Item()->AddItemCount(1);
			return true;
		}
	}

	return false;
}

CItem* CUIMgr::GetItemBox(_uint _uint)

{
	if (nullptr != m_pItemArr[_uint])
	{
		return m_pItemArr[_uint];
	}
	else
	{
		return nullptr;
	}
}

void CUIMgr::Ready_CreateInfo()
{
	CREATEINFO tInfo;

	ZeroMemory(&tInfo, sizeof(tInfo));

	// ��Ȱ��ǰ
	tInfo.strKeyName = L"Ax";
	tInfo.strName = L"����";
	tInfo.strInfo = L"������ �� �� �ִ�.";
	tInfo.tItemInfo[0].strItemName = L"Twigs";
	tInfo.tItemInfo[0].iCount = 1;
	tInfo.tItemInfo[1].strItemName = L"FireSton";
	tInfo.tItemInfo[1].iCount = 5;
	m_vecCreateInfo.push_back(tInfo);

	tInfo.strKeyName = L"Pickaxe";
	tInfo.strName = L"���";
	tInfo.strInfo = L"������ Ķ �� �ִ�.";
	tInfo.tItemInfo[0].strItemName = L"Twigs";
	tInfo.tItemInfo[0].iCount = 1;
	tInfo.tItemInfo[1].strItemName = L"FireSton";
	tInfo.tItemInfo[1].iCount = 5;
	m_vecCreateInfo.push_back(tInfo);

	tInfo.strKeyName = L"Hammer";
	tInfo.strName = L"��ġ";
	tInfo.strInfo = L"�����̵� �μ� �� �ִ�.";
	tInfo.tItemInfo[0].strItemName = L"Twigs";
	tInfo.tItemInfo[0].iCount = 1;
	tInfo.tItemInfo[1].strItemName = L"Rocks_0";
	tInfo.tItemInfo[1].iCount = 2;
	m_vecCreateInfo.push_back(tInfo);

	//���� ��ǰ
	tInfo.strKeyName = L"Torch";
	tInfo.strName = L"ȶ��";
	tInfo.strInfo = L"��������� �ֺ��� �����ش�.";
	tInfo.tItemInfo[0].strItemName = L"Twigs";
	tInfo.tItemInfo[0].iCount = 2;
	tInfo.tItemInfo[1].strItemName = L"CutGlass";
	tInfo.tItemInfo[1].iCount = 2;
	m_vecCreateInfo.push_back(tInfo);

	tInfo.strKeyName = L"BonFire";
	tInfo.strName = L"��ں�";
	tInfo.strInfo = L"��ġ�ϸ� �ֺ��� ȯ�ϰ� �����ش�.";
	tInfo.tItemInfo[0].strItemName = L"Log";
	tInfo.tItemInfo[0].iCount = 2;
	tInfo.tItemInfo[1].strItemName = L"CutGlass";
	tInfo.tItemInfo[1].iCount = 3;
	m_vecCreateInfo.push_back(tInfo);

	//������ǰ
	tInfo.strKeyName = L"Lance";
	tInfo.strName = L"����â";
	tInfo.strInfo = L"��� �����Ѵٸ� ���� ��ų �� �ִ�.";
	tInfo.tItemInfo[0].strItemName = L"Twigs";
	tInfo.tItemInfo[0].iCount = 2;
	tInfo.tItemInfo[1].strItemName = L"FireSton";
	tInfo.tItemInfo[1].iCount = 1;
	m_vecCreateInfo.push_back(tInfo);
}

void CUIMgr::Free()
{
	for (auto iter : m_pItemArr)
	{
		
	}
	//m_pItemArr[0].
	//__super::Free();
}