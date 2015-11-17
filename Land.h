#pragma once
#include "myDX.h"

typedef struct tagMyLand
{
	MyMesh mesh;
	D3DXVECTOR3 position;
	D3DXMATRIX mat;
	D3DXVECTOR3 offset;
}Land;

extern Land land1;
extern Land land2;
extern Land land3;
extern Land land4;
extern Land Point;

extern BOOL flag_point;
extern BOOL point_tank;
extern BOOL point_enemy;