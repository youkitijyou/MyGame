#include "myDX.h"
#include "Obb.h"
#include "Player.h"
#include "Enemy.h"
#include "Shell.h"

/////////////////////////////////////////////////////////////////////////
//  BoundingBox‚Ìì¬
/////////////////////////////////////////////////////////////////////////
void CreateOBB(OBB *obb, Tank(&tank)[myTANKNUM])
{
	D3DXMATRIX matRot;

	D3DXVECTOR3 max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);

	VERTEX* vertexBuffer = NULL;
	tank[myBODY].mesh.lpMesh->LockVertexBuffer(0, (VOID**)&vertexBuffer);

	for (int i = 0; i < (int)tank[myBODY].mesh.lpMesh->GetNumVertices(); ++i)
	{
		D3DXVECTOR3 pos = vertexBuffer[i].position;
		if (pos.x < min.x)min.x = pos.x;
		if (pos.x > max.x)max.x = pos.x;
		if (pos.y < min.y)min.y = pos.y;
		if (pos.y > max.y)max.y = pos.y;
		if (pos.z < min.z)min.z = pos.z;
		if (pos.z > max.z)max.z = pos.z;
	}
	tank[myBODY].mesh.lpMesh->UnlockVertexBuffer();

	obb->c = (min + max) * 0.5f + tank[myBODY].position;

	D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(tank[myBODY].direction), tank[myBODY].pitch, tank[myBODY].roll);
	obb->u[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
	obb->u[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
	obb->u[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);

	obb->e.x = fabsf(max.x - min.x) * 0.5f;
	obb->e.y = fabsf(max.y - min.y) * 0.5f;
	obb->e.z = fabsf(max.z - min.z) * 0.5f;
}

void CreateHeadOBB(OBB *obb, Tank(&tank)[myTANKNUM])
{
	D3DXMATRIX matRot;

	D3DXVECTOR3 max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);

	VERTEX* vertexBuffer = NULL;
	tank[myHEAD].mesh.lpMesh->LockVertexBuffer(0, (VOID**)&vertexBuffer);

	for (int i = 0; i < (int)tank[myHEAD].mesh.lpMesh->GetNumVertices(); ++i)
	{
		D3DXVECTOR3 pos = vertexBuffer[i].position;
		if (pos.x < min.x)min.x = pos.x;
		if (pos.x > max.x)max.x = pos.x;
		if (pos.y < min.y)min.y = pos.y;
		if (pos.y > max.y)max.y = pos.y;
		if (pos.z < min.z)min.z = pos.z;
		if (pos.z > max.z)max.z = pos.z;
	}
	tank[myHEAD].mesh.lpMesh->UnlockVertexBuffer();

	obb->c = (min + max) * 0.5f + tank[myBODY].position;

	D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(tank[myHEAD].direction), tank[myHEAD].pitch, tank[myHEAD].roll);
	obb->u[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
	obb->u[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
	obb->u[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);

	obb->e.x = fabsf(max.x - min.x) * 0.5f;
	obb->e.y = fabsf(max.y - min.y) * 0.5f;
	obb->e.z = fabsf(max.z - min.z) * 0.5f;
}

void CreateEmyOBB(OBB *obb, Enemy(&enemy)[eTANKNUM])
{
	D3DXMATRIX matRot;

	D3DXVECTOR3 max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);

	VERTEX* vertexBuffer = NULL;

	enemy[eBODY].mesh.lpMesh->LockVertexBuffer(0, (VOID**)&vertexBuffer);

	for (int i = 0; i < (int)enemy[eBODY].mesh.lpMesh->GetNumVertices(); ++i)
	{
		D3DXVECTOR3 pos = vertexBuffer[i].position;
		if (pos.x < min.x)min.x = pos.x;
		if (pos.x > max.x)max.x = pos.x;
		if (pos.y < min.y)min.y = pos.y;
		if (pos.y > max.y)max.y = pos.y;
		if (pos.z < min.z)min.z = pos.z;
		if (pos.z > max.z)max.z = pos.z;
	}
	enemy[eBODY].mesh.lpMesh->UnlockVertexBuffer();

	obb->c = (min + max) * 0.5f + enemy[eBODY].position;

	D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(enemy[eBODY].direction), enemy[eBODY].pitch, enemy[eBODY].roll);
	obb->u[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
	obb->u[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
	obb->u[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);

	obb->e.x = fabsf(max.x - min.x) * 0.5f;
	obb->e.y = fabsf(max.y - min.y) * 0.5f;
	obb->e.z = fabsf(max.z - min.z) * 0.5f;
}

void CreateEmyHeadOBB(OBB *obb, Enemy(&enemy)[eTANKNUM])
{
	D3DXMATRIX matRot;

	D3DXVECTOR3 max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);

	VERTEX* vertexBuffer = NULL;

	enemy[eHEAD].mesh.lpMesh->LockVertexBuffer(0, (VOID**)&vertexBuffer);

	for (int i = 0; i < (int)enemy[eHEAD].mesh.lpMesh->GetNumVertices(); ++i)
	{
		D3DXVECTOR3 pos = vertexBuffer[i].position;
		if (pos.x < min.x)min.x = pos.x;
		if (pos.x > max.x)max.x = pos.x;
		if (pos.y < min.y)min.y = pos.y;
		if (pos.y > max.y)max.y = pos.y;
		if (pos.z < min.z)min.z = pos.z;
		if (pos.z > max.z)max.z = pos.z;
	}
	enemy[eHEAD].mesh.lpMesh->UnlockVertexBuffer();

	obb->c = (min + max) * 0.5f + enemy[eBODY].position;

	D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(enemy[eHEAD].direction), enemy[eHEAD].pitch, enemy[eHEAD].roll);
	obb->u[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
	obb->u[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
	obb->u[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);

	obb->e.x = fabsf(max.x - min.x) * 0.5f;
	obb->e.y = fabsf(max.y - min.y) * 0.5f;
	obb->e.z = fabsf(max.z - min.z) * 0.5f;
}

void CreateShellOBB(OBB *obb, Shell &shell, Tank(&tank)[myTANKNUM])
{
	D3DXMATRIX matRot;

	D3DXVECTOR3 max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);

	VERTEX* vertexBuffer = NULL;

	shell.mesh.lpMesh->LockVertexBuffer(0, (VOID**)&vertexBuffer);

	for (int i = 0; i < (int)shell.mesh.lpMesh->GetNumVertices(); ++i)
	{
		D3DXVECTOR3 pos = vertexBuffer[i].position;
		if (pos.x < min.x)min.x = pos.x;
		if (pos.x > max.x)max.x = pos.x;
		if (pos.y < min.y)min.y = pos.y;
		if (pos.y > max.y)max.y = pos.y;
		if (pos.z < min.z)min.z = pos.z;
		if (pos.z > max.z)max.z = pos.z;
	}
	shell.mesh.lpMesh->UnlockVertexBuffer();

	obb->c = (min + max) * 0.5f + shell.position;

	D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(shell.direction), shell.pitch, shell.roll);
	obb->u[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
	obb->u[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
	obb->u[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);

	obb->e.x = fabsf(max.x - min.x) * 0.5f;
	obb->e.y = fabsf(max.y - min.y) * 0.5f;
	obb->e.z = fabsf(max.z - min.z) * 0.5f;
}

void CreateEmyShellOBB(OBB *obb, Shell &shell, Enemy(&enemy)[eTANKNUM])
{
	D3DXMATRIX matRot;

	D3DXVECTOR3 max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);

	VERTEX* vertexBuffer = NULL;

	shell.mesh.lpMesh->LockVertexBuffer(0, (VOID**)&vertexBuffer);

	for (int i = 0; i < (int)shell.mesh.lpMesh->GetNumVertices(); ++i)
	{
		D3DXVECTOR3 pos = vertexBuffer[i].position;
		if (pos.x < min.x)min.x = pos.x;
		if (pos.x > max.x)max.x = pos.x;
		if (pos.y < min.y)min.y = pos.y;
		if (pos.y > max.y)max.y = pos.y;
		if (pos.z < min.z)min.z = pos.z;
		if (pos.z > max.z)max.z = pos.z;
	}
	shell.mesh.lpMesh->UnlockVertexBuffer();

	obb->c = (min + max) * 0.5f + shell.position;

	D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(shell.direction), shell.pitch, shell.roll);
	obb->u[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
	obb->u[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
	obb->u[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);

	obb->e.x = fabsf(max.x - min.x) * 0.5f;
	obb->e.y = fabsf(max.y - min.y) * 0.5f;
	obb->e.z = fabsf(max.z - min.z) * 0.5f;
}
/////////////////////////////////////////////////////////////////////////
//  OBB‚ÆOBB‚Ì”»’è
/////////////////////////////////////////////////////////////////////////
BOOL TestOBBOBB(OBB *a, OBB *b)
{
	const double EPSILON = 1.175494e-37;

	float R[3][3], AbsR[3][3];
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; j++)
		{
			R[i][j] = D3DXVec3Dot(&a->u[i], &b->u[j]);
			AbsR[i][j] = fabsf(R[i][j]) + (float)EPSILON;
		}
	}

	D3DXVECTOR3 t = b->c - a->c;
	t = D3DXVECTOR3(D3DXVec3Dot(&t, &a->u[0]), D3DXVec3Dot(&t, &a->u[1]), D3DXVec3Dot(&t, &a->u[2]));

	float ra, rb;

	for (int i = 0; i < 3; ++i)
	{
		ra = a->e[i];
		rb = b->e[0] * AbsR[i][0] + b->e[1] * AbsR[i][1] + b->e[2] * AbsR[i][2];
		if (fabsf(t[i]) > ra + rb) return false;
	}

	for (int i = 0; i < 3; ++i)
	{
		ra = a->e[0] * AbsR[0][i] + a->e[1] * AbsR[1][i] + a->e[2] * AbsR[2][i];
		rb = b->e[i];
		if (fabsf(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return false;
	}

	ra = a->e[1] * AbsR[2][0] + a->e[2] * AbsR[1][0];
	rb = b->e[1] * AbsR[0][2] + b->e[2] * AbsR[0][1];
	if (fabsf(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return false;

	ra = a->e[1] * AbsR[2][1] + a->e[2] * AbsR[1][1];
	rb = b->e[0] * AbsR[0][2] + b->e[2] * AbsR[0][0];
	if (fabsf(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return false;

	ra = a->e[1] * AbsR[2][2] + a->e[2] * AbsR[1][2];
	rb = b->e[0] * AbsR[0][1] + b->e[1] * AbsR[0][0];
	if (fabsf(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return false;

	ra = a->e[0] * AbsR[2][0] + a->e[2] * AbsR[0][0];
	rb = b->e[1] * AbsR[1][2] + b->e[2] * AbsR[1][1];
	if (fabsf(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return false;

	ra = a->e[0] * AbsR[2][1] + a->e[2] * AbsR[0][1];
	rb = b->e[0] * AbsR[1][2] + b->e[2] * AbsR[1][0];
	if (fabsf(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return false;

	ra = a->e[0] * AbsR[2][2] + a->e[2] * AbsR[0][2];
	rb = b->e[0] * AbsR[1][1] + b->e[1] * AbsR[1][0];
	if (fabsf(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return false;

	ra = a->e[0] * AbsR[1][0] + a->e[1] * AbsR[0][0];
	rb = b->e[1] * AbsR[2][2] + b->e[2] * AbsR[2][1];
	if (fabsf(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return false;

	ra = a->e[0] * AbsR[1][1] + a->e[1] * AbsR[0][1];
	rb = b->e[0] * AbsR[2][2] + b->e[2] * AbsR[2][0];
	if (fabsf(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return false;

	ra = a->e[0] * AbsR[1][2] + a->e[1] * AbsR[0][2];
	rb = b->e[0] * AbsR[2][1] + b->e[1] * AbsR[2][0];
	if (fabsf(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////
//  ‚ ‚½‚è”»’è(player_enemy)
/////////////////////////////////////////////////////////////////////////
void CheckAttack(Tank(&tank)[myTANKNUM], Enemy(&enemy)[eTANKNUM], OBB *Myobb, OBB *Emyobb)
{
	if (TestOBBOBB(Myobb, Emyobb))
	{
		tank[myBODY].flagobb = true;
		enemy[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Myobb, Emyobb))
	{
		tank[myBODY].flagobb = false;
		enemy[eBODY].Emyflagobb = false;
	}
}

void CheckAttack2(Tank(&tank)[myTANKNUM], Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], OBB *Myobb, OBB *Emyobb, OBB *Emyobb2)
{
	if (TestOBBOBB(Myobb, Emyobb) || TestOBBOBB(Myobb, Emyobb2))
	{
		tank[myBODY].flagobb = true;
	}
	else
	{
		tank[myBODY].flagobb = false;
	}
	if (TestOBBOBB(Emyobb, Myobb) || TestOBBOBB(Emyobb, Emyobb2))
	{
		enemy[eBODY].Emyflagobb = true;
	}
	else
	{
		enemy[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb2, Myobb) || TestOBBOBB(Emyobb2, Emyobb))
	{
		enemy2[eBODY].Emyflagobb = true;
	}
	else 
	{
		enemy2[eBODY].Emyflagobb = false;
	}
}

void CheckAttack3(Tank(&tank)[myTANKNUM], Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], 
	              OBB *Myobb, OBB *Emyobb, OBB *Emyobb2, OBB *Emyobb3)
{
	if (TestOBBOBB(Myobb, Emyobb) || TestOBBOBB(Myobb, Emyobb2) || TestOBBOBB(Myobb, Emyobb3))
	{
		tank[myBODY].flagobb = true;
	}
	else
	{
		tank[myBODY].flagobb = false;
	}
	if (TestOBBOBB(Emyobb, Myobb) || TestOBBOBB(Emyobb, Emyobb2) || TestOBBOBB(Emyobb, Emyobb3))
	{
		enemy[eBODY].Emyflagobb = true;
	}
	else
	{
		enemy[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb2, Myobb) || TestOBBOBB(Emyobb2, Emyobb) || TestOBBOBB(Emyobb2, Emyobb3))
	{
		enemy2[eBODY].Emyflagobb = true;
	}
	else
	{
		enemy2[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb3, Myobb) || TestOBBOBB(Emyobb3, Emyobb) || TestOBBOBB(Emyobb3, Emyobb2))
	{
		enemy3[eBODY].Emyflagobb = true;
	}
	else
	{
		enemy3[eBODY].Emyflagobb = false;
	}
}

void CheckAttack4(Tank(&tank)[myTANKNUM], Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Enemy(&enemy4)[eTANKNUM], 
	              OBB *Myobb, OBB *Emyobb, OBB *Emyobb2, OBB *Emyobb3, OBB *Emyobb4)
{
	if (TestOBBOBB(Myobb, Emyobb) || TestOBBOBB(Myobb, Emyobb2) || TestOBBOBB(Myobb, Emyobb3) || TestOBBOBB(Myobb, Emyobb4))
	{
		tank[myBODY].flagobb = true;
	}
	else
	{
		tank[myBODY].flagobb = false;
	}
	if (TestOBBOBB(Emyobb, Myobb) || TestOBBOBB(Emyobb, Emyobb2) || TestOBBOBB(Emyobb, Emyobb3) || TestOBBOBB(Emyobb, Emyobb4))
	{
		enemy[eBODY].Emyflagobb = true;
	}
	else
	{
		enemy[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb2, Myobb) || TestOBBOBB(Emyobb2, Emyobb) || TestOBBOBB(Emyobb2, Emyobb3) || TestOBBOBB(Emyobb2, Emyobb4))
	{
		enemy2[eBODY].Emyflagobb = true;
	}
	else
	{
		enemy2[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb3, Myobb) || TestOBBOBB(Emyobb3, Emyobb) || TestOBBOBB(Emyobb3, Emyobb2) || TestOBBOBB(Emyobb3, Emyobb4))
	{
		enemy3[eBODY].Emyflagobb = true;
	}
	else
	{
		enemy3[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb4, Myobb) || TestOBBOBB(Emyobb4, Emyobb) || TestOBBOBB(Emyobb4, Emyobb2) || TestOBBOBB(Emyobb4, Emyobb3))
	{
		enemy4[eBODY].Emyflagobb = true;
	}
	else
	{
		enemy4[eBODY].Emyflagobb = false;
	}
}

void CheckAttackEmy(Enemy(&enemy1)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], OBB *Emyobb1, OBB *Emyobb2)
{
	if (TestOBBOBB(Emyobb1, Emyobb2))
	{
		enemy1[eBODY].Emyflagobb = true;
		enemy2[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb1, Emyobb2))
	{
		enemy1[eBODY].Emyflagobb = false;
		enemy2[eBODY].Emyflagobb = false;
	}
}
/////////////////////////////////////////////////////////////////////////
//  ‚ ‚½‚è”»’è(playershell_enemy)
/////////////////////////////////////////////////////////////////////////
void CheckAttackShell(Shell &shell, Enemy(&enemy)[eTANKNUM], OBB *MyShellobb, OBB *Emyobb,OBB *EmyHeadobb)
{
	if (TestOBBOBB(MyShellobb, Emyobb) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy[eBODY].EmyDamage = true;

	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy[eHEAD].EmyDamage = true;
	}
}

void CheckAttackShell2(Shell &shell, Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], OBB *MyShellobb, OBB *Emyobb, 
	                   OBB *EmyHeadobb, OBB *Emyobb2, OBB *EmyHeadobb2)
{
	if (TestOBBOBB(MyShellobb, Emyobb) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy[eBODY].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy[eHEAD].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, Emyobb2) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy2[eBODY].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb2) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy2[eHEAD].EmyDamage = true;
	}
}

void CheckAttackShell3(Shell &shell, Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], OBB *MyShellobb, 
	                   OBB *Emyobb, OBB *EmyHeadobb, OBB *Emyobb2, OBB *EmyHeadobb2, OBB *Emyobb3, OBB *EmyHeadobb3)
{
	if (TestOBBOBB(MyShellobb, Emyobb) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy[eBODY].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy[eHEAD].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, Emyobb2) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy2[eBODY].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb2) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy2[eHEAD].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, Emyobb3) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy3[eBODY].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb3) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy3[eHEAD].EmyDamage = true;
	}
}

void CheckAttackShell4(Shell &shell, Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Enemy(&enemy4)[eTANKNUM], 
	                   OBB *MyShellobb, OBB *Emyobb, OBB *EmyHeadobb, OBB *Emyobb2, OBB *EmyHeadobb2, OBB *Emyobb3, OBB *EmyHeadobb3, 
					   OBB *Emyobb4, OBB *EmyHeadobb4)
{
	if (TestOBBOBB(MyShellobb, Emyobb) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy[eBODY].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy[eHEAD].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, Emyobb2) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy2[eBODY].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb2) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy2[eHEAD].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, Emyobb3) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy3[eBODY].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb3) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy3[eHEAD].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, Emyobb4) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy4[eBODY].EmyDamage = true;
	}
	if (TestOBBOBB(MyShellobb, EmyHeadobb4) && shell.active)
	{
		shell.active = false;
		shell.hit += 1;
		enemy4[eHEAD].EmyDamage = true;
	}
}
/////////////////////////////////////////////////////////////////////////
//  ‚ ‚½‚è”»’è(player_enemyshell)
/////////////////////////////////////////////////////////////////////////
void CheckAttackEmyShell(Shell &shell, Tank(&tank)[myTANKNUM], OBB *EnemyShellobb, OBB *Myobb, OBB *MyHeadobb)
{
	if (TestOBBOBB(EnemyShellobb, Myobb) && shell.active)
	{
		shell.active = false;
		tank[myBODY].Damage = true;
	}
	if (TestOBBOBB(EnemyShellobb, MyHeadobb) && shell.active)
	{
		shell.active = false;
		tank[myHEAD].Damage = true;
	}
}

void CheckAttackEmyShell2(Shell &shell, Shell &shell2, Tank(&tank)[myTANKNUM], OBB *EnemyShellobb, OBB *EnemyShellobb2, OBB *Myobb, OBB *MyHeadobb)
{
	if (TestOBBOBB(EnemyShellobb, Myobb) && shell.active)
	{
		shell.active = false;
		tank[myBODY].Damage = true;
	}
	if (TestOBBOBB(EnemyShellobb, MyHeadobb) && shell.active)
	{
		shell.active = false;
		tank[myHEAD].Damage = true;
	}
	if (TestOBBOBB(EnemyShellobb2, Myobb) && shell2.active)
	{
		shell2.active = false;
		tank[myBODY].Damage2 = true;
	}
	if (TestOBBOBB(EnemyShellobb2, MyHeadobb) && shell2.active)
	{
		shell2.active = false;
		tank[myHEAD].Damage2 = true;
	}
}

void CheckAttackEmyShell3(Shell &shell, Shell &shell2, Shell &shell3, Tank(&tank)[myTANKNUM], 
	                      OBB *EnemyShellobb, OBB *EnemyShellobb2, OBB *EnemyShellobb3, OBB *Myobb, OBB *MyHeadobb)
{
	if (TestOBBOBB(EnemyShellobb, Myobb) && shell.active)
	{
		shell.active = false;
		tank[myBODY].Damage = true;
	}
	if (TestOBBOBB(EnemyShellobb, MyHeadobb) && shell.active)
	{
		shell.active = false;
		tank[myHEAD].Damage = true;
	}
	if (TestOBBOBB(EnemyShellobb2, Myobb) && shell2.active)
	{
		shell2.active = false;
		tank[myBODY].Damage2 = true;
	}
	if (TestOBBOBB(EnemyShellobb2, MyHeadobb) && shell2.active)
	{
		shell2.active = false;
		tank[myHEAD].Damage2 = true;
	}
	if (TestOBBOBB(EnemyShellobb3, Myobb) && shell3.active)
	{
		shell3.active = false;
		tank[myBODY].Damage3 = true;
	}
	if (TestOBBOBB(EnemyShellobb3, MyHeadobb) && shell3.active)
	{
		shell3.active = false;
		tank[myHEAD].Damage3 = true;
	}
}

void CheckAttackEmyShell4(Shell &shell, Shell &shell2, Shell &shell3, Shell &shell4, Tank(&tank)[myTANKNUM], 
	                      OBB *EnemyShellobb, OBB *EnemyShellobb2, OBB *EnemyShellobb3, OBB *EnemyShellobb4, OBB *Myobb, OBB *MyHeadobb)
{
	if (TestOBBOBB(EnemyShellobb, Myobb) && shell.active)
	{
		shell.active = false;
		tank[myBODY].Damage = true;
	}
	if (TestOBBOBB(EnemyShellobb, MyHeadobb) && shell.active)
	{
		shell.active = false;
		tank[myHEAD].Damage = true;
	}
	if (TestOBBOBB(EnemyShellobb2, Myobb) && shell2.active)
	{
		shell2.active = false;
		tank[myBODY].Damage2 = true;
	}
	if (TestOBBOBB(EnemyShellobb2, MyHeadobb) && shell2.active)
	{
		shell2.active = false;
		tank[myHEAD].Damage2 = true;
	}
	if (TestOBBOBB(EnemyShellobb3, Myobb) && shell3.active)
	{
		shell3.active = false;
		tank[myBODY].Damage3 = true;
	}
	if (TestOBBOBB(EnemyShellobb3, MyHeadobb) && shell3.active)
	{
		shell3.active = false;
		tank[myHEAD].Damage3 = true;
	}
	if (TestOBBOBB(EnemyShellobb4, Myobb) && shell4.active)
	{
		shell4.active = false;
		tank[myBODY].Damage4 = true;
	}
	if (TestOBBOBB(EnemyShellobb4, MyHeadobb) && shell4.active)
	{
		shell4.active = false;
		tank[myHEAD].Damage4 = true;
	}
}

/////////////////////////////////////////////////////////////////////////
//  ‚ ‚½‚è”»’è(enemy_enemy)
/////////////////////////////////////////////////////////////////////////
void CheckAttackEmyEmy2(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], OBB *Emyobb, OBB *Emyobb2)
{
	if (TestOBBOBB(Emyobb, Emyobb2))
	{
		enemy[eBODY].Emyflagobb = true;
		enemy2[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb, Emyobb2))
	{
		enemy[eBODY].Emyflagobb = false;
		enemy2[eBODY].Emyflagobb = false;
	}
}

void CheckAttackEmyEmy3(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], OBB *Emyobb, OBB *Emyobb2, OBB *Emyobb3)
{
	if (TestOBBOBB(Emyobb, Emyobb2))
	{
		enemy[eBODY].Emyflagobb = true;
		enemy2[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb, Emyobb2))
	{
		enemy[eBODY].Emyflagobb = false;
		enemy2[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb, Emyobb3))
	{
		enemy[eBODY].Emyflagobb = true;
		enemy3[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb, Emyobb3))
	{
		enemy[eBODY].Emyflagobb = false;
		enemy3[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb2, Emyobb3))
	{
		enemy2[eBODY].Emyflagobb = true;
		enemy3[eBODY].Emyflagobb = true;
	}
	else if (TestOBBOBB(Emyobb2, Emyobb3))
	{
		enemy2[eBODY].Emyflagobb = false;
		enemy3[eBODY].Emyflagobb = false;
	}
}

void CheckAttackEmyEmy4(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Enemy(&enemy4)[eTANKNUM],
	                    OBB *Emyobb, OBB *Emyobb2, OBB *Emyobb3, OBB *Emyobb4)
{
	if (TestOBBOBB(Emyobb, Emyobb2))
	{
		enemy[eBODY].Emyflagobb = true;
		enemy2[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb, Emyobb2))
	{
		enemy[eBODY].Emyflagobb = false;
		enemy2[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb, Emyobb3))
	{
		enemy[eBODY].Emyflagobb = true;
		enemy3[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb, Emyobb3))
	{
		enemy[eBODY].Emyflagobb = false;
		enemy3[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb, Emyobb4))
	{
		enemy[eBODY].Emyflagobb = true;
		enemy4[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb, Emyobb4))
	{
		enemy[eBODY].Emyflagobb = false;
		enemy4[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb2, Emyobb3))
	{
		enemy2[eBODY].Emyflagobb = true;
		enemy3[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb2, Emyobb3))
	{
		enemy2[eBODY].Emyflagobb = false;
		enemy3[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb2, Emyobb4))
	{
		enemy2[eBODY].Emyflagobb = true;
		enemy4[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb2, Emyobb4))
	{
		enemy2[eBODY].Emyflagobb = false;
		enemy4[eBODY].Emyflagobb = false;
	}
	if (TestOBBOBB(Emyobb3, Emyobb4))
	{
		enemy3[eBODY].Emyflagobb = true;
		enemy4[eBODY].Emyflagobb = true;
	}
	else if (!TestOBBOBB(Emyobb3, Emyobb4))
	{
		enemy3[eBODY].Emyflagobb = false;
		enemy4[eBODY].Emyflagobb = false;
	}
}