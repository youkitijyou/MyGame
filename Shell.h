#pragma once
#include "myDX.h"
#include "Enemy.h"

typedef struct tagMyShell
{
	MyMesh mesh;
	D3DXVECTOR3 position;
	float direction;
	float pitch;
	float roll;
	D3DXMATRIX mat;
	BOOL active;
	D3DXVECTOR3 prePos;
	BOOL fireOK;
	float time;
	int hit;
	int hitmax;
}Shell;

extern Shell T44_shell;
extern Shell IS1_shell;
extern Shell T54_shell;
extern Shell IS3_shell;
extern Shell PantherG_shell;
extern Shell Tiger_shell;
extern Shell PantherII_shell;
extern Shell TigerII_shell;
extern Shell M26_shell;
extern Shell T32_shell;
extern Shell M46_shell;
extern Shell M103_shell;

extern Shell EmyT44_shell;
extern Shell EmyIS1_shell;
extern Shell EmyT54_shell;
extern Shell EmyIS3_shell;
extern Shell EmyPantherG_shell;
extern Shell EmyTiger_shell;
extern Shell EmyPantherII_shell;
extern Shell EmyTigerII_shell;
extern Shell EmyM26_shell;
extern Shell EmyT32_shell;
extern Shell EmyM46_shell;
extern Shell EmyM103_shell;

extern float FPS;