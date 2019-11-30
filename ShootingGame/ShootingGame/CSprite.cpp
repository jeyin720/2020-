#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>

#include "CSprite.h"



CSprite::CSprite():m_Sprite(NULL)
{
	
}

CSprite::CSprite(LPDIRECT3DDEVICE9 pD3DDevice)
{
	CreateSprite(pD3DDevice);
}


CSprite::~CSprite()
{
	ReleaseSprite();
}

bool CSprite::CreateSprite(LPDIRECT3DDEVICE9 pD3DDevice) {
	
	auto hr = D3DXCreateSprite(pD3DDevice, &m_Sprite);
	if (FAILED(hr))
		return false;
	return true;
}
void CSprite::DrawSprite( LPDIRECT3DTEXTURE9 p_Texture,const D3DXVECTOR3 &center, const D3DXVECTOR3 &position) {
	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_Sprite->Draw(p_Texture, NULL, &center, &position, D3DCOLOR_XRGB(255, 255, 255));
	m_Sprite->End();
}
void CSprite::ReleaseSprite() {
	if (m_Sprite != NULL)
	{
		m_Sprite->Release();
		m_Sprite = NULL;
	}
}
