#pragma once
#include "myDX.h"

typedef struct tagCamera
{
	POINT m_oldpt, m_curpt;
	D3DXMATRIX matRola;
	D3DXMATRIX	m_view;
	D3DXMATRIX	m_proj;
	D3DXVECTOR3 vdelt;
	D3DXVECTOR3	m_vDelt;
	D3DXVECTOR3	m_lookat;
	D3DXVECTOR3	m_pos;
	D3DXVECTOR3	m_up;
	float m_rolaX;
	float m_rolaY;
	BOOL m_Rbtn = false;
	BOOL key_E = false;
}Camera;

extern Camera camera;

extern LPDIRECT3DTEXTURE9 lpCenter;
extern LPDIRECT3DTEXTURE9 lpTarget;
extern LPDIRECT3DTEXTURE9 lpSight;
extern LPDIRECT3DTEXTURE9 lpSky;