#pragma once


class CSprite
{
protected:
	LPD3DXSPRITE m_Sprite;
public:

	CSprite();
	CSprite(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual ~CSprite();

	bool CreateSprite(LPDIRECT3DDEVICE9 pD3DDevice);
	void DrawSprite(LPDIRECT3DTEXTURE9 p_Texture, const D3DXVECTOR3 &center, const D3DXVECTOR3 &position);
	void ReleaseSprite();

	
};

