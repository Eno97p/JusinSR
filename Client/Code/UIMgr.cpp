#include "stdafx.h"
#include "UIMgr.h"
#include"CItem.h"
#include "SlotMgr.h"
#include <ItemTool.h>

IMPLEMENT_SINGLETON(CUIMgr)

CUIMgr::CUIMgr()
{
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
	//m_pItemArr[0].
	//__super::Free();
}