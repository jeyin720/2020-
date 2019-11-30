#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>

#include "CEntity.h"
#include "CSprite.h"
#include "CTexture.h"

#include "GameObject.h"


GameObject::GameObject():m_pSpr(NULL),m_pTex(NULL),m_pEntity(NULL),m_bAlive(false)
{

}

GameObject::GameObject(LPDIRECT3DDEVICE9 pD3DDevice, const TCHAR * filename, D3DXVECTOR3 pos, D3DXVECTOR3 cen, D3DXVECTOR3 dir, float speed):m_bAlive(false)
{
	Create(pD3DDevice,filename,pos,cen,dir,speed);
}


GameObject::~GameObject()
{
	if (m_pSpr != NULL) delete m_pSpr;
	if (m_pTex != NULL) delete m_pTex;
	if (m_pEntity != NULL) delete m_pEntity;

	m_pSpr = NULL;
	m_pTex = NULL;
	m_pEntity = NULL;
}

bool GameObject::Create(LPDIRECT3DDEVICE9 pD3DDevice
	,const TCHAR* filename
	, D3DXVECTOR3 pos
	, D3DXVECTOR3 cen
	, D3DXVECTOR3 dir
	, float speed)
{
	m_pSpr = new CSprite(pD3DDevice);
	m_pTex = new CTexture(pD3DDevice, filename);
	m_pEntity = new CEntity(pos, cen, dir, speed);

	if (m_pSpr == NULL || m_pTex == NULL || m_pEntity == NULL) {
		return false;
	}
	return true;
}

void GameObject::Draw()
{
	if (m_pSpr == NULL || m_pTex == NULL || m_pEntity == NULL) //오브젝트만 만들어졌지만 Create가 안되었을 때를 방지
		return;
	if (m_bAlive == false) {
		return;
	}
	m_pSpr->DrawSprite(m_pTex->GetTexture()
		, m_pEntity->getCen()
		, m_pEntity->getPos());
}

