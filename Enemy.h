#pragma once
#include "myDX.h"

enum { eBODY, eHEAD, eGUN, eTANKNUM };

typedef struct tagEnemyTank
{
	MyMesh mesh;
	D3DXVECTOR3 position;
	float direction;
	float pitch;
	float roll;
	D3DXMATRIX mat;
	D3DXVECTOR3 offsetEmy;
	float speed;
	BOOL Emyflagobb;
	BOOL EmyDamage;
	float c, d, e;
	int hp;
	int hpmax;
	float armor;
	float turn;
	BOOL Emypoint;
}Enemy;

extern Enemy EmyT44[eTANKNUM];
extern Enemy EmyIS1[eTANKNUM];
extern Enemy EmyT54[eTANKNUM];
extern Enemy EmyIS3[eTANKNUM];
extern Enemy EmyPantherG[eTANKNUM];
extern Enemy EmyTiger[eTANKNUM];
extern Enemy EmyPantherII[eTANKNUM];
extern Enemy EmyTigerII[eTANKNUM];
extern Enemy EmyM26[eTANKNUM];
extern Enemy EmyT32[eTANKNUM];
extern Enemy EmyM46[eTANKNUM];
extern Enemy EmyM103[eTANKNUM];