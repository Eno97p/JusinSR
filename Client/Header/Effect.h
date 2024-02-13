#pragma once

#include "Base.h"
#include "GameObject.h"

class CEffect :	public Engine::CGameObject
{
protected:
	explicit CEffect(LPDIRECT3DDEVICE9 pGraphicDev,_vec3 vPos);
	explicit CEffect(const CEffect& rhs);
	virtual ~CEffect();

protected:
	virtual void	State_Change()	PURE;
	virtual void	Look_Change();
	void Check_Collision();
protected:
	_vec3 m_vPos;

	LOOKDIR		m_eCurLook;			//���� �ٶ󺸴� ����
	LOOKDIR		m_ePreLook;
	//������
	_float				m_fFrame = 0.f;
	_float				m_fFrameEnd;
	_float				m_fAcctime;				//�ð� ������ ����
	_int				m_fFrameChange = 0;		//�������� �ٲ��� �ϴ� ��쿡 �����.
	_bool				m_bFrameStop;			//�������� ����� �� �� true�� �ٲ���

	_bool				m_Dirchange;

	_float				m_fDamage;
protected:
	virtual void Free() override;


};

