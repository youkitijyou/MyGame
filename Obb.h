#pragma once
#include "myDX.h"
#include "Enemy.h"

struct OBB{
	D3DXVECTOR3 c;     
	D3DXVECTOR3 u[3];  
	D3DXVECTOR3 e;   
};

struct VERTEX
{
	D3DXVECTOR3 position, normal;
	float tu, tv;
};

extern OBB T44obb;
extern OBB IS1obb;
extern OBB T54obb;
extern OBB IS3obb;
extern OBB PantherGobb;
extern OBB Tigerobb;
extern OBB PantherIIobb;
extern OBB TigerIIobb;
extern OBB M26obb;
extern OBB T32obb;
extern OBB M46obb;
extern OBB M103obb;

extern OBB T44headobb;
extern OBB IS1headobb;
extern OBB T54headobb;
extern OBB IS3headobb;
extern OBB PantherGheadobb;
extern OBB Tigerheadobb;
extern OBB PantherIIheadobb;
extern OBB TigerIIheadobb;
extern OBB M26headobb;
extern OBB T32headobb;
extern OBB M46headobb;
extern OBB M103headobb;

extern OBB T44Emyobb;
extern OBB IS1Emyobb;
extern OBB T54Emyobb;
extern OBB IS3Emyobb;
extern OBB PantherGEmyobb;
extern OBB TigerEmyobb;
extern OBB PantherIIEmyobb;
extern OBB TigerIIEmyobb;
extern OBB M26Emyobb;
extern OBB T32Emyobb;
extern OBB M46Emyobb;
extern OBB M103Emyobb;

extern OBB T44Emyheadobb;
extern OBB IS1Emyheadobb;
extern OBB T54Emyheadobb;
extern OBB IS3Emyheadobb;
extern OBB PantherGEmyheadobb;
extern OBB TigerEmyheadobb;
extern OBB PantherIIEmyheadobb;
extern OBB TigerIIEmyheadobb;
extern OBB M26Emyheadobb;
extern OBB T32Emyheadobb;
extern OBB M46Emyheadobb;
extern OBB M103Emyheadobb;

extern OBB T44Shellobb;
extern OBB IS1Shellobb;
extern OBB T54Shellobb;
extern OBB IS3Shellobb;
extern OBB PantherGShellobb;
extern OBB TigerShellobb;
extern OBB PantherIIShellobb;
extern OBB TigerIIShellobb;
extern OBB M26Shellobb;
extern OBB T32Shellobb;
extern OBB M46Shellobb;
extern OBB M103Shellobb;

extern OBB T44EmyShellobb;
extern OBB IS1EmyShellobb;
extern OBB T54EmyShellobb;
extern OBB IS3EmyShellobb;
extern OBB PantherGEmyShellobb;
extern OBB TigerEmyShellobb;
extern OBB PantherIIEmyShellobb;
extern OBB TigerIIEmyShellobb;
extern OBB M26EmyShellobb;
extern OBB T32EmyShellobb;
extern OBB M46EmyShellobb;
extern OBB M103EmyShellobb;