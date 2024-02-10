#pragma once
#include "CItem.h"
class CItemBasic : // �⺻ ������. ����� �����ϴ� ������
    public CItem
{
private:
    explicit CItemBasic(LPDIRECT3DDEVICE9 pGraphicDev);
    explicit CItemBasic(LPDIRECT3DDEVICE9 pGraphicDev, wstring _strObjName);
    explicit CItemBasic(const CItem& rhs);
    virtual ~CItemBasic();

public:
    void Pickup_Item(_vec3 vSlotPos);

public:
    HRESULT Ready_GameObject() override;
    _int Update_GameObject(const _float& fTimeDelta) override;
    void LateUpdate_GameObject() override;
    void Render_GameObject() override;
    

    //������Ʈ�� ���� ������ ��ü�鸸 ����� ��
    void SetCreateByObject( ) { m_bIsCreateByObject = true; }
    void DropMotion(const _float& fTimeDelta);

public:
    static CItem* Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring _szName);

private:
    virtual void Free();


    BOOL m_bIsCreateByObject = false;


private:
    _bool m_bChangeRander;

    _vec3 m_vPos = {};
    _vec3 m_vSlotPos = {};
};

