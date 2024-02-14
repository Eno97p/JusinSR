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
    _bool Get_ChangeRender() { return m_bChangeRander; }

public:
    HRESULT Ready_GameObject() override;
    _int Update_GameObject(const _float& fTimeDelta) override;
    void LateUpdate_GameObject() override;
    void Render_GameObject() override;

    //������Ʈ�� ���� ������ ��ü�鸸 ����� ��
    void SetCreateByObject(_int _randomNum ) 
    {
        iPos= _randomNum;
        m_bIsCreateByObject = true;
    }
    void DropMotion(const _float& fTimeDelta);
    void CheckSign(int _iSign, int _Dir);
   

public:
    static CItem* Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring _szName);

private:
    virtual void Free();


    //������Ʈ�� ���� ������ ��ü�鸸 ����� ��
    BOOL m_bIsCreateByObject = false;
    BOOL m_bHowToDir = false;
    _int m_iSign = 0;
    _float fItemSpeed = 0.0f;
    bool bHowFar = false;
    int iPos = 0;
   
private:
    _bool m_bChangeRander;

    _vec3 m_vPos = {};
    _vec3 m_vSlotPos = {};
};

