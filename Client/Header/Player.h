#pragma once

#include "Base.h"
#include "GameObject.h"
#include "ResObject.h"

namespace Engine
{
	class CRcTex;
	class CRvRcTex;
	class CTexture;
	class CTransform;
	class CCalculator;
	class CPlayerStatus;
}

class CPlayer : public Engine::CGameObject
{
	
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev, wstring _strName);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer();

public:
	virtual HRESULT Ready_GameObject()						 override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject()					 override;
	virtual void Render_GameObject()						 override;
	void			Set_Attack(int _Atk);			//���ݴ����� �� ȣ��Ǵ� �Լ�
private:
	HRESULT			Add_Component();
	void			Key_Input(const _float& fTimeDelta);
	void			Ket_Input_Road(const _float& fTimeDelta);
	HRESULT			SetUp_Material();
	void			Check_State();				//���� ����� �Լ�
	void			Set_Scale();				//�ൿ�� ���� �������� �����ϱ� ���� �Լ�
	void			Set_Stat();					
	void			Weapon_Change();			//���� ���濡 ���� ��ȭ�� ���� �Լ�
	void			Look_Change();				//�ٶ󺸴� ������ �ٲٱ� ���� �Լ�
	void			ResObj_Mining(RESOBJID _ObjID , CGameObject* _Obj);	//Res������Ʈ���� ä���� �� ����ϴ� �Լ�


	HRESULT Ready_Light();	//����
	void Fire_Light();
	

	CGameObject* Find_NeerObject(float _fRange, eOBJECT_GROUPTYPE _findTarget);

	void BillBoard();

private:
	Engine::CRcTex* m_pBufferCom;
	Engine::CRvRcTex* m_pReverseCom;
	Engine::CTexture* m_pTextureCom[LOOKDIR::LOOK_END][PLAYERSTATE::STATE_END];
	Engine::CCalculator* m_pCalculatorCom;

	_float				m_fFrame = 0.f;
	_float				m_fFrameEnd;

	PLAYERSTATE			m_eCurState;
	PLAYERSTATE			m_ePreState;

	WEAPON				m_eCurWeapon;			//���� �����ϰ� �ִ� ����
	WEAPON				m_ePreWeapon;			// ���Ŀ� ���� ����Ī�Ҷ� �޼ҵ带 ���� �����ص�

	LOOKDIR				m_eCurLook;
	LOOKDIR				m_ePreLook;
	_bool				m_Dirchange;			//Look
	_bool				m_bAttack;
	OBJSTAT				m_Stat;
	_bool				m_KeyLock;				//Key Input �Լ��� ���� �뵵	true �� ����
	_bool				m_bFrameLock;			//������ ������ ���� �뵵 true �� ����


	_vec3				m_vTargetPos;			//������Ʈ ����� ��ġ����
	_vec3				m_vTargetDir;			//�̵��ϴ� ����
	_bool				m_vPlayerActing;		//������Ʈ�� ��ȣ�ۿ� �� �� true

	RESOBJID			m_TargetObject;			//Res������Ʈ�� ������ �Ǻ�
	_bool				m_bIsRoadScene;			//Road ���̸� true (�ӽ�)

public:
	static CPlayer* Create(LPDIRECT3DDEVICE9	pGraphicDev, wstring _strName);
	static CPlayer* Create(LPDIRECT3DDEVICE9	pGraphicDev);

private:
	virtual void Free() override;
};

