#pragma once

#include "Base.h"
#include "Engine_Define.h"
#include "Export_System.h"
#include "Export_Utility.h"

BEGIN(Engine)

class CGraphicDev;
class CManagement;

END

class CMainApp : public CBase
{
private:				// 생성자, 소멸자 선언
	explicit CMainApp();
	virtual ~CMainApp();

public:			//public 함수, 변수 -> protected 함수, 변수 -> private 함수, 변수
	HRESULT		Ready_MainApp();
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp();
	void		Render_MainApp();

private:
	HRESULT		Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement** ppManagement);
	HRESULT		SetUp_Setting(LPDIRECT3DDEVICE9* ppGraphicDev);

private:
	Engine::CGraphicDev*		m_pDeviceClass;
	Engine::CManagement*		m_pManagementClass;
	LPDIRECT3DDEVICE9			m_pGraphicDev;


public:
	static CMainApp*		Create();

private:
	virtual		void		Free();

};


// 엔진 헤더에 있는 파일들을 레퍼런스 헤더에 복사 붙여넣기
// 엔진 bin 폴더에 있는 dll과 lib 파일을 복사해서 레퍼런스 라이브러리에 클라이언트의 bin 복사 붙여넣기

//D3DXMatrixLookAtLH();
//D3DXMatrixPerspectiveFovLH();

//
//m_pGraphicDev->SetTransform(D3DTS_WORLD, ? );
//m_pGraphicDev->SetTransform(D3DTS_VIEW, ? );
//m_pGraphicDev->SetTransform(D3DTS_PROJECTION, ? );