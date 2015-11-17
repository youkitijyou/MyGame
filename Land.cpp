#include "myDX.h"
#include "Land.h"
#include "Player.h"
#include "Enemy.h"

/////////////////////////////////////////////////////////////////////////
//  地面の描画
/////////////////////////////////////////////////////////////////////////
void DrawLand(Land &land)
{
	DrawModel(&land.mesh, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 0.f, land.position);
}

/////////////////////////////////////////////////////////////////////////
//  POINTの描画
/////////////////////////////////////////////////////////////////////////
void DrawPoint()
{
	if (flag_point)
	{
		DWORD buf_time = timeGetTime();
		Point.position = { (float)(buf_time % 300) - 150.f, -0.1f, (float)(buf_time * buf_time % 300) - 150.f };
		flag_point = false;
	}

	DrawModel(&Point.mesh, 1.f,1.f, 1.f, 0.f, 0.f, 0.f, Point.position);
}
/////////////////////////////////////////////////////////////////////////
//  POINTとTANKの距離
/////////////////////////////////////////////////////////////////////////
void PointToTank(Tank(&tank)[myTANKNUM])
{
	D3DXVECTOR3 dis;
	if (D3DXVec3Length(D3DXVec3Subtract(&dis, &Point.position, &tank[myBODY].position)) <= 10.f)
	{
		point_tank = true;
	}
	else if (D3DXVec3Length(D3DXVec3Subtract(&dis, &Point.position, &tank[myBODY].position)) > 10.f)
	{
		point_tank = false;
	}
}
/////////////////////////////////////////////////////////////////////////
//  POINTとENEMYの距離
/////////////////////////////////////////////////////////////////////////
void PointToEnemy(Enemy(&enemy)[eTANKNUM])
{
	D3DXVECTOR3 dis;

	if (D3DXVec3Length(D3DXVec3Subtract(&dis, &Point.position, &enemy[eBODY].position)) <= 10.f)
	{
		point_enemy = true;
		enemy[eBODY].Emypoint = true;
	}
	else 
	{
		point_enemy = false;
		enemy[eBODY].Emypoint = false;
	}
}

void PointToEnemy2(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM])
{
	D3DXVECTOR3 dis,dis2;

	if (D3DXVec3Length(D3DXVec3Subtract(&dis, &Point.position, &enemy[eBODY].position)) <= 10.f)
	{
		enemy[eBODY].Emypoint = true;
	}
	else
	{
		enemy[eBODY].Emypoint = false;
	}
	if (D3DXVec3Length(D3DXVec3Subtract(&dis2, &Point.position, &enemy2[eBODY].position)) <= 10.f)
	{
		enemy2[eBODY].Emypoint = true;
	}
	else
	{
		enemy2[eBODY].Emypoint = false;
	}
	if (D3DXVec3Length(D3DXVec3Subtract(&dis, &Point.position, &enemy[eBODY].position)) <= 10.f
		|| D3DXVec3Length(D3DXVec3Subtract(&dis2, &Point.position, &enemy2[eBODY].position)) <= 10.f)
	{
		point_enemy = true;
	}
	else
	{
		point_enemy = false;
	}
}

void PointToEnemy3(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM])
{
	D3DXVECTOR3 dis, dis2, dis3;

	if (D3DXVec3Length(D3DXVec3Subtract(&dis, &Point.position, &enemy[eBODY].position)) <= 10.f)
	{
		enemy[eBODY].Emypoint = true;
	}
	else
	{
		enemy[eBODY].Emypoint = false;
	}
	if (D3DXVec3Length(D3DXVec3Subtract(&dis2, &Point.position, &enemy2[eBODY].position)) <= 10.f)
	{
		enemy2[eBODY].Emypoint = true;
	}
	else
	{
		enemy2[eBODY].Emypoint = false;
	}
	if (D3DXVec3Length(D3DXVec3Subtract(&dis3, &Point.position, &enemy3[eBODY].position)) <= 10.f)
	{
		enemy3[eBODY].Emypoint = true;
	}
	else
	{
		enemy3[eBODY].Emypoint = false;
	}
	if (D3DXVec3Length(D3DXVec3Subtract(&dis, &Point.position, &enemy[eBODY].position)) <= 10.f
		|| D3DXVec3Length(D3DXVec3Subtract(&dis2, &Point.position, &enemy2[eBODY].position)) <= 10.f
		|| D3DXVec3Length(D3DXVec3Subtract(&dis3, &Point.position, &enemy3[eBODY].position)) <= 10.f)
	{
		point_enemy = true;
	}
	else
	{
		point_enemy = false;
	}
}

void PointToEnemy4(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Enemy(&enemy4)[eTANKNUM])
{
	D3DXVECTOR3 dis, dis2, dis3, dis4;

	if (D3DXVec3Length(D3DXVec3Subtract(&dis, &Point.position, &enemy[eBODY].position)) <= 10.f)
	{
		enemy[eBODY].Emypoint = true;
	}
	else
	{
		enemy[eBODY].Emypoint = false;
	}
	if (D3DXVec3Length(D3DXVec3Subtract(&dis2, &Point.position, &enemy2[eBODY].position)) <= 10.f)
	{
		enemy2[eBODY].Emypoint = true;
	}
	else
	{
		enemy2[eBODY].Emypoint = false;
	}
	if (D3DXVec3Length(D3DXVec3Subtract(&dis3, &Point.position, &enemy3[eBODY].position)) <= 10.f)
	{
		enemy3[eBODY].Emypoint = true;
	}
	else
	{
		enemy3[eBODY].Emypoint = false;
	}
	if (D3DXVec3Length(D3DXVec3Subtract(&dis4, &Point.position, &enemy4[eBODY].position)) <= 10.f)
	{
		enemy4[eBODY].Emypoint = true;
	}
	else
	{
		enemy4[eBODY].Emypoint = false;
	}
	if (D3DXVec3Length(D3DXVec3Subtract(&dis, &Point.position, &enemy[eBODY].position)) <= 10.f
		|| D3DXVec3Length(D3DXVec3Subtract(&dis2, &Point.position, &enemy2[eBODY].position)) <= 10.f
		|| D3DXVec3Length(D3DXVec3Subtract(&dis3, &Point.position, &enemy3[eBODY].position)) <= 10.f
		|| D3DXVec3Length(D3DXVec3Subtract(&dis4, &Point.position, &enemy4[eBODY].position)) <= 10.f)
	{
		point_enemy = true;
	}
	else
	{
		point_enemy = false;
	}
}
/////////////////////////////////////////////////////////////////////////
//  メッシュとベクトルの交差チェック
/////////////////////////////////////////////////////////////////////////
BOOL CheckIntersect(LPD3DXMESH lpMesh, D3DXVECTOR3 *rayPos, D3DXVECTOR3 *ray, float *pDist)
{
	BOOL isHit;
	DWORD faceCnt;
	float u, v;
	LPD3DXBUFFER xBuf;
	DWORD hitCnt;

	D3DXIntersect(lpMesh, rayPos, ray, &isHit, &faceCnt, &u, &v, pDist, &xBuf, &hitCnt);
	if (isHit) xBuf->Release();

	return isHit;
}
/////////////////////////////////////////////////////////////////////////
//  高さの判定
/////////////////////////////////////////////////////////////////////////
void CheckHeight(Tank(&tank)[myTANKNUM], Land &land)
{
	D3DXVECTOR3 rayPos;
	float dist;

	rayPos = tank[myBODY].position;
	rayPos.y += 1.0f;

	if (CheckIntersect(land.mesh.lpMesh, &rayPos, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist))
	{
		tank[myBODY].position.y = rayPos.y - dist;
	}
}
/////////////////////////////////////////////////////////////////////////
//  傾きの判定
/////////////////////////////////////////////////////////////////////////
void CheckLean(Tank(&tank)[myTANKNUM], Land &land)
{
	D3DXMATRIX mat;
	D3DXVECTOR3 vec;
	D3DXVECTOR3 rayPos1, rayPos2, rayPos3, rayPos4;
	BOOL isHit1, isHit2, isHit3, isHit4;
	float dist1, dist2, dist3, dist4;
	D3DXVECTOR3 vec1, vec2, vec3, vec4, vec0;
	float val;

	D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(tank[myBODY].direction), tank[myBODY].pitch, tank[myBODY].roll);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 1.0f, 3.5f), &mat);
	D3DXVec3Add(&rayPos1, &tank[myBODY].position, &vec);
	isHit1 = CheckIntersect(land.mesh.lpMesh, &rayPos1, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist1);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 1.0f, -3.5f), &mat);
	D3DXVec3Add(&rayPos2, &tank[myBODY].position, &vec);
	isHit2 = CheckIntersect(land.mesh.lpMesh, &rayPos2, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist2);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(2.0f, 1.0f, 0.0f), &mat);
	D3DXVec3Add(&rayPos3, &tank[myBODY].position, &vec);
	isHit3 = CheckIntersect(land.mesh.lpMesh, &rayPos3, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist3);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(-2.0f, 1.0f, 0.0f), &mat);
	D3DXVec3Add(&rayPos4, &tank[myBODY].position, &vec);
	isHit4 = CheckIntersect(land.mesh.lpMesh, &rayPos4, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist4);

	if (isHit1&&isHit2)
	{
		vec1 = rayPos1;
		vec1.y -= dist1;

		vec2 = rayPos2;
		vec2.y -= dist2;

		D3DXVec3Subtract(&vec, &vec1, &vec2);

		vec0 = vec;
		vec0.y = 0;

		D3DXVec3Normalize(&vec, &vec);
		D3DXVec3Normalize(&vec0, &vec0);

		val = D3DXVec3Dot(&vec, &vec0);
		if ((val >= -1) && (val <= 1))
		{
			if (vec1.y > vec2.y)
			{
				tank[myBODY].pitch -= 0.01f;
				if (tank[myBODY].pitch <= -(float)acos((double)val)) tank[myBODY].pitch = -(float)acos((double)val);
			}
			else
			{
				tank[myBODY].pitch += 0.01f;
				if (tank[myBODY].pitch >= (float)acos((double)val))  tank[myBODY].pitch = (float)acos((double)val);
			}
		}
	}

	if (isHit3&&isHit4)
	{
		vec3 = rayPos3;
		vec3.y -= dist3;

		vec4 = rayPos4;
		vec4.y -= dist4;

		D3DXVec3Subtract(&vec, &vec3, &vec4);

		vec0 = vec;
		vec0.y = 0;

		D3DXVec3Normalize(&vec, &vec);
		D3DXVec3Normalize(&vec0, &vec0);

		val = D3DXVec3Dot(&vec, &vec0);
		if ((val >= -1) && (val <= 1))
		{
			if (vec3.y < vec4.y)
			{
				tank[myBODY].roll -= 0.01f;
				if (tank[myBODY].roll <= -(float)acos((double)val)) tank[myBODY].roll = -(float)acos((double)val);
			}
			else
			{
				tank[myBODY].roll += 0.01f;
				if (tank[myBODY].roll >= (float)acos((double)val))  tank[myBODY].roll = (float)acos((double)val);
			}
		}
	}
}

void CheckEmyLean(Enemy(&enemy)[eTANKNUM], Land &land)
{
	D3DXMATRIX mat;
	D3DXVECTOR3 vec;
	D3DXVECTOR3 rayPos1, rayPos2, rayPos3, rayPos4;
	BOOL isHit1, isHit2, isHit3, isHit4;
	float dist1, dist2, dist3, dist4;
	D3DXVECTOR3 vec1, vec2, vec3, vec4, vec0;
	float val;

	D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(enemy[eBODY].direction), enemy[eBODY].pitch, enemy[eBODY].roll);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 1.0f, 3.5f), &mat);
	D3DXVec3Add(&rayPos1, &enemy[eBODY].position, &vec);
	isHit1 = CheckIntersect(land.mesh.lpMesh, &rayPos1, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist1);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 1.0f, -3.5f), &mat);
	D3DXVec3Add(&rayPos2, &enemy[eBODY].position, &vec);
	isHit2 = CheckIntersect(land.mesh.lpMesh, &rayPos2, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist2);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(2.0f, 1.0f, 0.0f), &mat);
	D3DXVec3Add(&rayPos3, &enemy[eBODY].position, &vec);
	isHit3 = CheckIntersect(land.mesh.lpMesh, &rayPos3, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist3);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(-2.0f, 1.0f, 0.0f), &mat);
	D3DXVec3Add(&rayPos4, &enemy[eBODY].position, &vec);
	isHit4 = CheckIntersect(land.mesh.lpMesh, &rayPos4, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist4);

	if (isHit1&&isHit2)
	{
		vec1 = rayPos1;
		vec1.y -= dist1;

		vec2 = rayPos2;
		vec2.y -= dist2;

		D3DXVec3Subtract(&vec, &vec1, &vec2);

		vec0 = vec;
		vec0.y = 0;

		D3DXVec3Normalize(&vec, &vec);
		D3DXVec3Normalize(&vec0, &vec0);

		val = D3DXVec3Dot(&vec, &vec0);
		if ((val >= -1) && (val <= 1))
		{
			if (vec1.y > vec2.y)
			{
				enemy[eBODY].pitch -= 0.01f;
				if (enemy[eBODY].pitch <= -(float)acos((double)val)) enemy[eBODY].pitch = -(float)acos((double)val);
			}
			else
			{
				enemy[eBODY].pitch += 0.01f;
				if (enemy[eBODY].pitch >= (float)acos((double)val))  enemy[eBODY].pitch = (float)acos((double)val);
			}
		}
	}

	if (isHit3&&isHit4)
	{
		vec3 = rayPos3;
		vec3.y -= dist3;

		vec4 = rayPos4;
		vec4.y -= dist4;

		D3DXVec3Subtract(&vec, &vec3, &vec4);

		vec0 = vec;
		vec0.y = 0;

		D3DXVec3Normalize(&vec, &vec);
		D3DXVec3Normalize(&vec0, &vec0);

		val = D3DXVec3Dot(&vec, &vec0);
		if ((val >= -1) && (val <= 1))
		{
			if (vec3.y < vec4.y)
			{
				enemy[eBODY].roll -= 0.01f;
				if (enemy[eBODY].roll <= -(float)acos((double)val)) enemy[eBODY].roll = -(float)acos((double)val);
			}
			else
			{
				enemy[eBODY].roll += 0.01f;
				if (enemy[eBODY].roll >= (float)acos((double)val))  enemy[eBODY].roll = (float)acos((double)val);
			}
		}
	}
}

void CheckEmyHeight(Enemy(&enemy)[eTANKNUM], Land &land)
{
	D3DXVECTOR3 rayPos;
	float dist;

	rayPos = enemy[eBODY].position;
	rayPos.y += 1.0f;

	if (CheckIntersect(land.mesh.lpMesh, &rayPos, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &dist))
	{
		enemy[eBODY].position.y = rayPos.y - dist;
	}
}