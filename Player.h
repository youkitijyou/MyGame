#pragma once
#include "myDX.h"

#define		kKEYENTER		0x0001
#define		kKEYW			0x0002
#define		kKEYS			0x0004
#define		kKEYA			0x0008
#define		kKEYD			0x0010
#define		kKEYE			0x0020
#define     mLbtn           0x0040

extern short key;

enum { myBODY, myHEAD, myGUN, myTANKNUM };

typedef struct tagMyTank
{
	MyMesh mesh;
	D3DXVECTOR3 position;
	float direction;
	float pitch;
	float roll;
	D3DXMATRIX mat;
	D3DXVECTOR3 offset;
	float speed;
	float backspeed;
	float turn;
	BOOL choose;
	BOOL flagobb;
	BOOL Damage,Damage2,Damage3,Damage4;
	float a, b;
	int hp;
	int hpmax;
	float armor;
}Tank;

extern Tank T44[myTANKNUM];
extern Tank IS1[myTANKNUM];
extern Tank T54[myTANKNUM];
extern Tank IS3[myTANKNUM];
extern Tank PantherG[myTANKNUM];
extern Tank Tiger[myTANKNUM];
extern Tank PantherII[myTANKNUM];
extern Tank TigerII[myTANKNUM];
extern Tank M26[myTANKNUM];
extern Tank T32[myTANKNUM];
extern Tank M46[myTANKNUM];
extern Tank M103[myTANKNUM];

extern D3DXVECTOR3 HitPoint;
extern BOOL isHit;
extern float dist;
extern float fpTimeDelta;
extern BOOL tank_hpup,tank_hpdown;
extern BOOL outofmap;