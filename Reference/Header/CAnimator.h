#pragma once
#include "Component.h"
#include "CAnimation.h"

namespace Engine
{
	class ENGINE_DLL CAnimator :
		public CComponent
	{
	public:
		void SetCurAnimation(const _tchar* _strAnimKey);
		void SetCurAnimationFrame(const _tchar* _strAnimKey,_uint _iFrame);
		_bool GetAnimFinish(const _tchar* _strAnimKey) { return Find_Animation(_strAnimKey)->m_bFinish; }
		void SetAnimTexture();

		//Ư�� �ִϸ��̼��϶��� ������ ������ //�ȴ»����϶��� Ư������������������
		_int	GetAnimFrame(const _tchar* _strAnimKey) { return Find_Animation(_strAnimKey)->m_iCurFrm; }
		_int	GetAnimMaxFrame(const _tchar* _strAnimKey) { return Find_Animation(_strAnimKey)->m_iMaxFrameCount-1; }

		//���� ������Ʈ���� �ִϸ��̼� ������
		//���� �̵����϶� ������������ ȸ���������� 
		//�ٽ� ������ �����Ӱ����� ������ ȸ���ִϸ��̼ǿ� �����ų������
		// ex) �������� �ȴ� �������� 15������ ī�޶��̵��� �������� ���� 0�����Ӻ��ʹٽ� �ȴ°Ծƴ�
		//		15�������� �����ʾִϸ��̼ǿ� 15���������� �����ϵ���
		_int	GetCurAnimFrame() { return m_pCurAnimation->m_iCurFrm; }

		void AddAnimation(const _tchar* _strAnimKey, Engine::CAnimation* _pAnimation) { m_mapAnimation.insert({ _strAnimKey, _pAnimation }); }
		void SetLoopAnimator(_bool _bLoop) { m_bLoop = _bLoop; }
		_bool IsLoop() { return m_bLoop; }

	public:
		virtual HRESULT		Ready_Animation();
		virtual _int		Update_Component(const _float& fTimeDelta);
		virtual void		LateUpdate_Component();
		virtual CComponent* Clone()override;

		static CAnimator* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	protected:
		explicit CAnimator() = delete;
		explicit CAnimator(LPDIRECT3DDEVICE9 pGraphicDev);
		explicit CAnimator(const CAnimator& rhs);
		virtual ~CAnimator();

	protected:
		virtual void		Free();
	private:
		CAnimation* Find_Animation(const _tchar* _key);

	private:
		map<const _tchar*, Engine::CAnimation*>	m_mapAnimation;
		Engine::CAnimation* m_pCurAnimation;
		_bool		m_bLoop;//����ִϸ��̼� ��������

	};

}