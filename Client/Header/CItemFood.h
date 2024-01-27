#pragma once

#include "../Header/CItem.h"

BEGIN(Engine)
class CRcTex;
class CTexture;
class CTransform;
END

class CItemFood :
	public CItem
{
public:
	explicit CItemFood(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* _key,_vec3 _vPos);
	virtual ~CItemFood();

public:
	virtual _bool UseItem() override;
	virtual _bool DropItem() override;
};

