#pragma once
#include "CUI.h"
class CHpUI : public CUI
{
protected:
	explicit CHpUI(LPDIRECT3DDEVICE9 pGraphicDev, UI_STATE eUIState, const _tchar* _UI_Name);
	explicit CHpUI(const CHpUI& rhs);
	virtual ~CHpUI();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void Render_GameObject()						 override;


public:
	static CHpUI* Create(LPDIRECT3DDEVICE9	pGraphicDev, UI_STATE _State, _vec3 _pos, _vec3 _size, const _tchar* _UI_Name, float _Angle = 0.f);
	virtual void Free() override;




public:
	void SetCurntHp(float _CurentHp) { m_fCurentHp = _CurentHp; }
	void SetMaxHp(float _MaxHp) { m_fMaxHp = _MaxHp; }
	void AddCurntHp(const _int _value);
	void MinusCurntHp(const _int _value);
	

private:
	_float m_fCurentHp;
	_float m_fMaxHp;
	_float m_frame; //��µ� ���� �ε���
	_float m_frameEnd; //�������� ���۵ǰ��� �����̴� ��
	_float m_PreFrame;
	BOOL m_bFrameStop = true;
	BOOL m_bHpPiusMInus = true; //true ü���� ���� false�� ü���� ����



	_float m_fImageCount=0.f;
};

