#include "myDX.h"
#include "Player.h"
#include "Camera.h"
#include "Land.h"
#include "Shell.h"
#include "Obb.h"

D3DXVECTOR3 HitPoint;
BOOL isHit;
float dist;
/////////////////////////////////////////////////////////////////////////
//  êÌé‘ÇÃï`âÊ
/////////////////////////////////////////////////////////////////////////
void DrawTank(Tank(&tank)[myTANKNUM])
{
	D3DXMATRIX matID, matRot, matPos, mat1, mat;

	for (int i = 0; i < myTANKNUM; ++i)
	{
		D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(tank[i].direction), tank[i].pitch, tank[i].roll);
		D3DXMatrixTranslation(&matPos, tank[i].position.x, tank[i].position.y, tank[i].position.z);
		D3DXMatrixMultiply(&mat1, &matRot, &tank[i].mat);
		D3DXMatrixMultiply(&mat, &mat1, &matPos);
		lpD3DDev->SetTransform(D3DTS_WORLD, &mat);
		Draw3DMesh(tank[i].mesh.matCount, tank[i].mesh.pMat, tank[i].mesh.pTex, tank[i].mesh.lpMesh);
	}
}
/////////////////////////////////////////////////////////////////////////
//  êÌé‘ÇÃà⁄ìÆ
/////////////////////////////////////////////////////////////////////////
void MoveTank(Tank(&tank)[myTANKNUM], float speedmax, float pitchmax, float acc1, float acc2, float back, float turn)
{
	D3DXMATRIX mat;
	D3DXVECTOR3 vec,dis;
	D3DXVECTOR3 xyz = { 0.f, 0.f, 0.f };

	if (D3DXVec3Length(D3DXVec3Subtract(&dis, &tank[myBODY].position, &xyz)) >= 450.f) outofmap = true;
	else outofmap = false;

	if (key&kKEYW)
	{
		if (!tank[myBODY].flagobb)
		{
			if (!outofmap)
			{
				if (tank[myBODY].pitch <= 0)
				{
					if ((tank[myBODY].speed += (speedmax / 1000.f*5.0f / acc1 / 50.f)) >=
						speedmax / 1000.f*5.0f + (tank[myBODY].pitch*(speedmax / 1000.f*5.0f / D3DXToRadian(pitchmax))))
						tank[myBODY].speed = speedmax / 1000.f*5.0f + (tank[myBODY].pitch*(speedmax / 1000.f*5.0f / D3DXToRadian(pitchmax)));
				}
				else if (tank[myBODY].pitch > 0)
				{
					if ((tank[myBODY].speed += (speedmax / 1000.f*5.0f / acc1 / 50.f)) >= speedmax / 1000.f*5.0f) tank[myBODY].speed = speedmax / 1000.f*5.0f;
				}
			}
			else if (outofmap)
			{
				tank[myBODY].speed = -0.05f;
			}
		}
		else if (tank[myBODY].flagobb)
		{
			tank[myBODY].speed = -0.01f;
		}
		D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(tank[myBODY].direction), tank[myBODY].pitch, tank[myBODY].roll);
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 0.0f, tank[myBODY].speed), &mat);
		D3DXVec3Add(&tank[myBODY].position, &tank[myBODY].position, &vec);
	}
	else if (tank[myBODY].speed > 0.f)
	{
		if (!tank[myBODY].flagobb)
		{
			if (!outofmap)
			{
				if ((tank[myBODY].speed -= (speedmax / 1000.f*5.0f / acc2 / 50.f)) <= 0.0f) tank[myBODY].speed = 0.0f;
			}
			else if (outofmap)
			{
				tank[myBODY].speed = -0.05f;
			}
		}
		else if (tank[myBODY].flagobb)
		{
			tank[myBODY].speed = -0.03f;
		}
		D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(tank[myBODY].direction), tank[myBODY].pitch, tank[myBODY].roll);
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 0.0f, tank[myBODY].speed), &mat);
		D3DXVec3Add(&tank[myBODY].position, &tank[myBODY].position, &vec);
	}
	if (key&kKEYS)
	{
		if (!tank[myBODY].flagobb)
		{
			if (!outofmap)
			{
				tank[myBODY].backspeed += 0.0001f;
				if (tank[myBODY].backspeed >= back / 200.f) tank[myBODY].backspeed = back / 200.f;
			}
			else if (outofmap)
			{
				tank[myBODY].backspeed = -0.01f;
			}
		}
		else if (tank[myBODY].flagobb)
		{
			tank[myBODY].backspeed = -0.05f;
		}
		D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(tank[myBODY].direction), tank[myBODY].pitch, tank[myBODY].roll);
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 0.0f, -tank[myBODY].backspeed), &mat);
		D3DXVec3Add(&tank[myBODY].position, &tank[myBODY].position, &vec);
	}
	else if (tank[myBODY].backspeed > 0.f)
	{
		if (!tank[myBODY].flagobb)
		{
			tank[myBODY].backspeed -= 0.0005f;
			if (tank[myBODY].backspeed <= 0.f) tank[myBODY].backspeed = 0.f;
		}
		else if (tank[myBODY].flagobb)
		{
			tank[myBODY].backspeed = -0.005f;
		}
		D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(tank[myBODY].direction), tank[myBODY].pitch, tank[myBODY].roll);
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 0.0f, -tank[myBODY].backspeed), &mat);
		D3DXVec3Add(&tank[myBODY].position, &tank[myBODY].position, &vec);
	}
	if (key&kKEYD)
	{
		if (!tank[myBODY].flagobb)
		{
			tank[myBODY].turn += 0.03f;
			if (tank[myBODY].turn >= 360.f / turn / 100.f) tank[myBODY].turn = 360.f / turn / 100.f;
			if ((tank[myBODY].direction += (tank[myBODY].turn)) >= 360.f) tank[myBODY].direction -= 360.f;
		}
		else if (tank[myBODY].flagobb)
		{
			tank[myBODY].direction -= 2.f;
		}
	}
	if (key&kKEYA)
	{
		if (!tank[myBODY].flagobb)
		{
			tank[myBODY].turn += 0.03f;
			if (tank[myBODY].turn >= 360.f / turn / 100.f) tank[myBODY].turn = 360.f / turn / 100.f;
			if ((tank[myBODY].direction -= (360.f / turn / 100.f)) <= -360.f) tank[myBODY].direction += 360.f;
		}
		else if (tank[myBODY].flagobb)
		{
			tank[myBODY].direction += 2.f;
		}
	}
}

void MoveChild(Tank(&tank)[myTANKNUM])
{
	for (int i = myHEAD; i < myTANKNUM; ++i)
	{
		D3DXMatrixRotationYawPitchRoll(&tank[i].mat, D3DXToRadian(tank[i - 1].direction), tank[i - 1].pitch, tank[i - 1].roll);
		D3DXMatrixMultiply(&tank[i].mat, &tank[i].mat, &tank[i - 1].mat);

		D3DXVec3TransformCoord(&tank[i].position, &tank[i].offset, &tank[i].mat);
		D3DXVec3Add(&tank[i].position, &tank[i].position, &tank[i - 1].position);
	}
}
/////////////////////////////////////////////////////////////////////////
//  HEADÇÃà⁄ìÆ
/////////////////////////////////////////////////////////////////////////
void MoveHead(Tank(&tank)[myTANKNUM], float turn)
{
	if (isHit)
	{
		if (HitPoint.x <= 1920 / 2 - (int)(dist / 20.f + 5.f))
		{
			tank[myHEAD].direction += turn / 60.f;
			if (HitPoint.x >= 1920 / 2 - (int)(dist / 20.f + 5.f)) HitPoint.x = 1920 / 2;
		}
		else if (HitPoint.x > 1920 / 2 + (int)(dist / 20.f + 5.f))
		{
			tank[myHEAD].direction -= turn / 60.f;
			if (HitPoint.x <= 1920 / 2 + (int)(dist / 20.f + 5.f)) HitPoint.x = 1920 / 2;
		}
	}
	else if (!isHit)
	{
		if (tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction >= 0.f&&tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction <= 180.f)
		{
			tank[myHEAD].direction += turn / 60.f;
			if (tank[myHEAD].direction >= tank[myHEAD].a - tank[myBODY].direction) tank[myHEAD].direction = tank[myHEAD].a - tank[myBODY].direction;
		}
		else if (tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction > 180.f&&tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction < 360.f)
		{
			tank[myHEAD].direction += 360.f;
			tank[myHEAD].direction -= turn / 60.f;
			if (tank[myHEAD].direction <= tank[myHEAD].a - tank[myBODY].direction) tank[myHEAD].direction = tank[myHEAD].a - tank[myBODY].direction;
		}
		else if (tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction < 0.f&&tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction >= -180.f)
		{
			tank[myHEAD].direction -= turn / 60.f;
			if (tank[myHEAD].direction <= tank[myHEAD].a - tank[myBODY].direction) tank[myHEAD].direction = tank[myHEAD].a - tank[myBODY].direction;
		}
		else if (tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction < -180.f&&tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction > -360.f)
		{
			tank[myHEAD].direction -= 360.f;
			tank[myHEAD].direction += turn / 60.f;
			if (tank[myHEAD].direction >= tank[myHEAD].a - tank[myBODY].direction) tank[myHEAD].direction = tank[myHEAD].a - tank[myBODY].direction;
		}
	}
}

void MoveHeadFar(Tank(&tank)[myTANKNUM], float turn)
{
	if (isHit)
	{
		if (HitPoint.x <= 1920 / 2 - (int)(dist / 20.f + 5.f))
		{
			tank[myHEAD].direction += turn / 60.f;
			if (HitPoint.x >= 1920 / 2 - (int)(dist / 20.f + 5.f)) HitPoint.x = 1920 / 2;
		}
		else if (HitPoint.x > 1920 / 2 + (int)(dist / 20.f + 5.f))
		{
			tank[myHEAD].direction -= turn / 60.f;
			if (HitPoint.x <= 1920 / 2 + (int)(dist / 20.f + 5.f)) HitPoint.x = 1920 / 2;
		}
	}
	else if (!isHit)
	{
		if (tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction >= 0.f&&tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction <= 180.f)
		{
			tank[myHEAD].direction += turn / 60.f;
			if (tank[myHEAD].direction >= tank[myHEAD].a - tank[myBODY].direction) tank[myHEAD].direction = tank[myHEAD].a - tank[myBODY].direction;
		}
		else if (tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction > 180.f&&tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction < 360.f)
		{
			tank[myHEAD].direction += 360.f;
			tank[myHEAD].direction -= turn / 60.f;
			if (tank[myHEAD].direction <= tank[myHEAD].a - tank[myBODY].direction) tank[myHEAD].direction = tank[myHEAD].a - tank[myBODY].direction;
		}
		else if (tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction < 0.f&&tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction >= -180.f)
		{
			tank[myHEAD].direction -= turn / 60.f;
			if (tank[myHEAD].direction <= tank[myHEAD].a - tank[myBODY].direction) tank[myHEAD].direction = tank[myHEAD].a - tank[myBODY].direction;
		}
		else if (tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction < -180.f&&tank[myHEAD].a - tank[myHEAD].direction - tank[myBODY].direction > -360.f)
		{
			tank[myHEAD].direction -= 360.f;
			tank[myHEAD].direction += turn / 60.f;
			if (tank[myHEAD].direction >= tank[myHEAD].a - tank[myBODY].direction) tank[myHEAD].direction = tank[myHEAD].a - tank[myBODY].direction;
		}
	}
}
/////////////////////////////////////////////////////////////////////////
//  GUNÇÃà⁄ìÆ
/////////////////////////////////////////////////////////////////////////
void MoveGun(Tank(&tank)[myTANKNUM], float pitchmax, float pitchmin)
{
	if (isHit)
	{
		if (HitPoint.y <= 400 - (int)(dist / 30.f + 3.f) && tank[myGUN].pitch <= D3DXToRadian(pitchmin))
		{
			tank[myGUN].pitch += D3DXToRadian(0.1f);
			if (HitPoint.y >= 400 - (int)(dist / 30.f + 3.f)) HitPoint.y = 400;
			if (tank[myGUN].pitch <= -D3DXToRadian(pitchmax)) tank[myGUN].pitch = -D3DXToRadian(pitchmax);
		}
		else if (HitPoint.y > 400 + (int)(dist / 30.f + 3.f) && tank[myGUN].pitch >= -D3DXToRadian(pitchmax))
		{
			tank[myGUN].pitch -= D3DXToRadian(0.1f);
			if (HitPoint.y <= 400 + (int)(dist / 30.f + 3.f)) HitPoint.y = 400;
			if (tank[myGUN].pitch >= D3DXToRadian(pitchmin)) tank[myGUN].pitch = D3DXToRadian(pitchmin);
		}
	}
	else if (!isHit)
	{
		if (tank[myGUN].pitch >= D3DXToRadian(tank[myGUN].b))
		{
			tank[myGUN].pitch -= D3DXToRadian(0.1f);
			if (tank[myGUN].pitch <= -D3DXToRadian(pitchmax)) tank[myGUN].pitch = -D3DXToRadian(pitchmax);
		}
		else if (tank[myGUN].pitch < D3DXToRadian(tank[myGUN].b))
		{
			tank[myGUN].pitch += D3DXToRadian(0.1f);
			if (tank[myGUN].pitch >= D3DXToRadian(pitchmin)) tank[myGUN].pitch = D3DXToRadian(pitchmin);
		}
	}
}

void MoveGunFar(Tank(&tank)[myTANKNUM], float pitchmax, float pitchmin)
{
	if (isHit)
	{
		if (HitPoint.y <= 1080 / 2 - (int)(dist / 30.f + 1.f) && tank[myGUN].pitch <= D3DXToRadian(pitchmin))
		{
			tank[myGUN].pitch += D3DXToRadian(0.1f);
			if (HitPoint.y >= 1080 / 2 - (int)(dist / 30.f + 1.f)) HitPoint.y = 1080 / 2;
			if (tank[myGUN].pitch <= -D3DXToRadian(pitchmax)) tank[myGUN].pitch = -D3DXToRadian(pitchmax);
		}
		else if (HitPoint.y > 1080 / 2 + (int)(dist / 30.f + 1.f) && tank[myGUN].pitch >= -D3DXToRadian(pitchmax))
		{
			tank[myGUN].pitch -= D3DXToRadian(0.1f);
			if (HitPoint.y <= 1080 / 2 + (int)(dist / 30.f + 1.f)) HitPoint.y = 1080 / 2;
			if (tank[myGUN].pitch >= D3DXToRadian(pitchmin)) tank[myGUN].pitch = D3DXToRadian(pitchmin);
		}
	}
	else if (!isHit)
	{
		if (tank[myGUN].pitch >= D3DXToRadian(tank[myGUN].b))
		{
			tank[myGUN].pitch -= D3DXToRadian(0.1f);
			if (tank[myGUN].pitch <= -D3DXToRadian(pitchmax)) tank[myGUN].pitch = -D3DXToRadian(pitchmax);
		}
		else if (tank[myGUN].pitch < D3DXToRadian(tank[myGUN].b))
		{
			tank[myGUN].pitch += D3DXToRadian(0.1f);
			if (tank[myGUN].pitch >= D3DXToRadian(pitchmin)) tank[myGUN].pitch = D3DXToRadian(pitchmin);
		}
	}
}

/////////////////////////////////////////////////////////////////////////
//  HitPointÇÃåvéZ
/////////////////////////////////////////////////////////////////////////
void CalcHitPoint(Tank(&tank)[myTANKNUM], Shell &shell, Land &land)
{
	DWORD faceCnt;
	float u, v;
	LPD3DXBUFFER xBuf;
	DWORD hitCnt;
	D3DXVECTOR3 ray;

	IDirect3DIndexBuffer9* IndexBuf;
	IDirect3DVertexBuffer9* VertexBuf;
	WORD* pIndices;
	BYTE* pVertices;
	D3DXVECTOR3 v0, v1, v2;
	DWORD fvfSize;

	ray = shell.position - tank[myGUN].position;
	D3DXVec3Normalize(&ray, &ray);

	D3DXIntersect(land.mesh.lpMesh, &tank[myGUN].position, &ray, &isHit, &faceCnt, &u, &v, &dist, &xBuf, &hitCnt);

	land.mesh.lpMesh->GetIndexBuffer(&IndexBuf);
	land.mesh.lpMesh->GetVertexBuffer(&VertexBuf);

	if (isHit)
	{
		IndexBuf->Lock(3 * sizeof(WORD)*faceCnt, 3 * sizeof(WORD), (VOID**)&pIndices, D3DLOCK_READONLY);
		VertexBuf->Lock(0, 0, (VOID**)&pVertices, D3DLOCK_READONLY);

		fvfSize = D3DXGetFVFVertexSize(land.mesh.lpMesh->GetFVF());

		v0 = *(D3DXVECTOR3*)(pVertices + fvfSize*pIndices[0]);
		v1 = *(D3DXVECTOR3*)(pVertices + fvfSize*pIndices[1]);
		v2 = *(D3DXVECTOR3*)(pVertices + fvfSize*pIndices[2]);

		IndexBuf->Unlock();
		VertexBuf->Unlock();
		IndexBuf->Release();
		VertexBuf->Release();

		HitPoint = (1 - u - v)*v0 + u*v1 + v*v2;

		D3DXMatrixLookAtLH(&camera.m_view, &camera.m_pos, &camera.m_lookat, &camera.m_up);
		lpD3DDev->SetTransform(D3DTS_VIEW, &camera.m_view);
		D3DXVec3TransformCoord(&HitPoint, &HitPoint, &camera.m_view);
		D3DXMatrixPerspectiveFovLH(&camera.m_proj, D3DXToRadian(32.0f), 16.0f / 9.0f, 0.1f, 500.0f);
		lpD3DDev->SetTransform(D3DTS_PROJECTION, &camera.m_proj);
		D3DXVec3TransformCoord(&HitPoint, &HitPoint, &camera.m_proj);
		HitPoint = { (HitPoint.x + 1.f)*1920.f / 2.f, 1080.f - (HitPoint.y + 1.f)*1080.f / 2.f, HitPoint.z };
	}
}

/////////////////////////////////////////////////////////////////////////
//  DamageÇÃåvéZ
/////////////////////////////////////////////////////////////////////////
void Damage(Enemy(&enemy)[eTANKNUM], Tank(&tank)[myTANKNUM], float emydmg10, float emydmg2000)
{
	D3DXVECTOR3 vec;
	float dist;
	float damage;

	dist = D3DXVec3Length(D3DXVec3Subtract(&vec, &enemy[eBODY].position, &tank[myBODY].position));
	if (dist <= 10.f) dist = 10.f;
	else if (dist >= 2000.f) dist = 2000.f;
	if (tank[myHEAD].Damage)
	{
		damage = (((emydmg2000 - emydmg10) / (2000.f - 10.f)*dist + emydmg10 - 10.f*(emydmg2000 - emydmg10) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage <= 0) damage = 0;
		tank[myBODY].hp -= (int)damage;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage = false;
	}
	if (tank[myBODY].Damage)
	{
		damage = (((emydmg2000 - emydmg10) / (2000.f - 10.f)*dist + emydmg10 - 10.f*(emydmg2000 - emydmg10) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage <= 0) damage = 0;
		tank[myBODY].hp -= (int)damage;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage = false;
	}
}

void Damage2(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Tank(&tank)[myTANKNUM], float emydmg10, float emydmg2000, float emydmg10_2, float emydmg2000_2)
{
	D3DXVECTOR3 vec, vec2;
	float dist, dist2;
	float damage, damage2;

	dist = D3DXVec3Length(D3DXVec3Subtract(&vec, &enemy[eBODY].position, &tank[myBODY].position));
	dist2 = D3DXVec3Length(D3DXVec3Subtract(&vec2, &enemy2[eBODY].position, &tank[myBODY].position));
	if (dist <= 10.f) dist = 10.f;
	else if (dist >= 2000.f) dist = 2000.f;
	if (dist2 <= 10.f) dist2 = 10.f;
	else if (dist2 >= 2000.f) dist2 = 2000.f;
	if (tank[myHEAD].Damage)
	{
		damage = (((emydmg2000 - emydmg10) / (2000.f - 10.f)*dist + emydmg10 - 10.f*(emydmg2000 - emydmg10) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage <= 0) damage = 0;
		tank[myBODY].hp -= (int)damage;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage = false;
	}
	if (tank[myBODY].Damage)
	{
		damage = (((emydmg2000 - emydmg10) / (2000.f - 10.f)*dist + emydmg10 - 10.f*(emydmg2000 - emydmg10) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage <= 0) damage = 0;
		tank[myBODY].hp -= (int)damage;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage = false;
	}
	if (tank[myHEAD].Damage2)
	{
		damage2 = (((emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)*dist2 + emydmg10_2 - 10.f*(emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage2 <= 0) damage2 = 0;
		tank[myBODY].hp -= (int)damage2;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage2 = false;
	}
	if (tank[myBODY].Damage2)
	{
		damage2 = (((emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)*dist2 + emydmg10_2 - 10.f*(emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage2 <= 0) damage2 = 0;
		tank[myBODY].hp -= (int)damage2;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage2 = false;
	}
}

void Damage3(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Tank(&tank)[myTANKNUM], 
	         float emydmg10, float emydmg2000, float emydmg10_2, float emydmg2000_2, float emydmg10_3, float emydmg2000_3)
{
	D3DXVECTOR3 vec, vec2,vec3;
	float dist, dist2,dist3;
	float damage, damage2,damage3;

	dist = D3DXVec3Length(D3DXVec3Subtract(&vec, &enemy[eBODY].position, &tank[myBODY].position));
	dist2 = D3DXVec3Length(D3DXVec3Subtract(&vec2, &enemy2[eBODY].position, &tank[myBODY].position));
	dist3 = D3DXVec3Length(D3DXVec3Subtract(&vec3, &enemy3[eBODY].position, &tank[myBODY].position));
	if (dist <= 10.f) dist = 10.f;
	else if (dist >= 2000.f) dist = 2000.f;
	if (dist2 <= 10.f) dist2 = 10.f;
	else if (dist2 >= 2000.f) dist2 = 2000.f;
	if (dist3 <= 10.f) dist3 = 10.f;
	else if (dist3 >= 2000.f) dist3 = 2000.f;
	if (tank[myHEAD].Damage)
	{
		damage = (((emydmg2000 - emydmg10) / (2000.f - 10.f)*dist + emydmg10 - 10.f*(emydmg2000 - emydmg10) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage <= 0) damage = 0;
		tank[myBODY].hp -= (int)damage;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage = false;
	}
	if (tank[myBODY].Damage)
	{
		damage = (((emydmg2000 - emydmg10) / (2000.f - 10.f)*dist + emydmg10 - 10.f*(emydmg2000 - emydmg10) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage <= 0) damage = 0;
		tank[myBODY].hp -= (int)damage;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage = false;
	}
	if (tank[myHEAD].Damage2)
	{
		damage2 = (((emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)*dist2 + emydmg10_2 - 10.f*(emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage2 <= 0) damage2 = 0;
		tank[myBODY].hp -= (int)damage2;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage2 = false;
	}
	if (tank[myBODY].Damage2)
	{
		damage2 = (((emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)*dist2 + emydmg10_2 - 10.f*(emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage2 <= 0) damage2 = 0;
		tank[myBODY].hp -= (int)damage2;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage2 = false;
	}
	if (tank[myHEAD].Damage3)
	{
		damage3 = (((emydmg2000_3 - emydmg10_3) / (2000.f - 10.f)*dist3 + emydmg10_3 - 10.f*(emydmg2000_3 - emydmg10_3) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage3 <= 0) damage3 = 0;
		tank[myBODY].hp -= (int)damage3;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage3 = false;
	}
	if (tank[myBODY].Damage3)
	{
		damage3 = (((emydmg2000_3 - emydmg10_3) / (2000.f - 10.f)*dist3 + emydmg10_3 - 10.f*(emydmg2000_3 - emydmg10_3) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage3 <= 0) damage3= 0;
		tank[myBODY].hp -= (int)damage3;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage3 = false;
	}
}

void Damage4(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Enemy(&enemy4)[eTANKNUM], 
	         Tank(&tank)[myTANKNUM],float emydmg10, float emydmg2000, float emydmg10_2, float emydmg2000_2, 
			 float emydmg10_3, float emydmg2000_3, float emydmg10_4, float emydmg2000_4)
{
	D3DXVECTOR3 vec, vec2, vec3,vec4;
	float dist, dist2, dist3,dist4;
	float damage, damage2, damage3,damage4;

	dist = D3DXVec3Length(D3DXVec3Subtract(&vec, &enemy[eBODY].position, &tank[myBODY].position));
	dist2 = D3DXVec3Length(D3DXVec3Subtract(&vec2, &enemy2[eBODY].position, &tank[myBODY].position));
	dist3 = D3DXVec3Length(D3DXVec3Subtract(&vec3, &enemy3[eBODY].position, &tank[myBODY].position));
	dist4 = D3DXVec3Length(D3DXVec3Subtract(&vec4, &enemy4[eBODY].position, &tank[myBODY].position));
	if (dist <= 10.f) dist = 10.f;
	else if (dist >= 2000.f) dist = 2000.f;
	if (dist2 <= 10.f) dist2 = 10.f;
	else if (dist2 >= 2000.f) dist2 = 2000.f;
	if (dist3 <= 10.f) dist3 = 10.f;
	else if (dist3 >= 2000.f) dist3 = 2000.f;
	if (dist4 <= 10.f) dist4 = 10.f;
	else if (dist4 >= 2000.f) dist4 = 2000.f;
	if (tank[myHEAD].Damage)
	{
		damage = (((emydmg2000 - emydmg10) / (2000.f - 10.f)*dist + emydmg10 - 10.f*(emydmg2000 - emydmg10) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage <= 0) damage = 0;
		tank[myBODY].hp -= (int)damage;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage = false;
	}
	if (tank[myBODY].Damage)
	{
		damage = (((emydmg2000 - emydmg10) / (2000.f - 10.f)*dist + emydmg10 - 10.f*(emydmg2000 - emydmg10) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage <= 0) damage = 0;
		tank[myBODY].hp -= (int)damage;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage = false;
	}
	if (tank[myHEAD].Damage2)
	{
		damage2 = (((emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)*dist2 + emydmg10_2 - 10.f*(emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage2 <= 0) damage2 = 0;
		tank[myBODY].hp -= (int)damage2;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage2 = false;
	}
	if (tank[myBODY].Damage2)
	{
		damage2 = (((emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)*dist2 + emydmg10_2 - 10.f*(emydmg2000_2 - emydmg10_2) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage2 <= 0) damage2 = 0;
		tank[myBODY].hp -= (int)damage2;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage2 = false;
	}
	if (tank[myHEAD].Damage3)
	{
		damage3 = (((emydmg2000_3 - emydmg10_3) / (2000.f - 10.f)*dist3 + emydmg10_3 - 10.f*(emydmg2000_3 - emydmg10_3) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage3 <= 0) damage3 = 0;
		tank[myBODY].hp -= (int)damage3;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage3 = false;
	}
	if (tank[myBODY].Damage3)
	{
		damage3 = (((emydmg2000_3 - emydmg10_3) / (2000.f - 10.f)*dist3 + emydmg10_3 - 10.f*(emydmg2000_3 - emydmg10_3) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage3 <= 0) damage3 = 0;
		tank[myBODY].hp -= (int)damage3;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage3 = false;
	}
	if (tank[myHEAD].Damage4)
	{
		damage4 = (((emydmg2000_4 - emydmg10_4) / (2000.f - 10.f)*dist4 + emydmg10_4 - 10.f*(emydmg2000_4 - emydmg10_4) / (2000.f - 10.f)) - tank[myHEAD].armor)*0.5f;
		if (damage4 <= 0) damage4 = 0;
		tank[myBODY].hp -= (int)damage4;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myHEAD].Damage4 = false;
	}
	if (tank[myBODY].Damage4)
	{
		damage4 = (((emydmg2000_4 - emydmg10_4) / (2000.f - 10.f)*dist4 + emydmg10_4 - 10.f*(emydmg2000_4 - emydmg10_4) / (2000.f - 10.f)) - tank[myBODY].armor)*0.5f;
		if (damage4 <= 0) damage4 = 0;
		tank[myBODY].hp -= (int)damage4;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank[myBODY].Damage4 = false;
	}
}
/////////////////////////////////////////////////////////////////////////
//  HPÇÃåvéZ(POINT)
/////////////////////////////////////////////////////////////////////////
void HpUpDown(Tank(&tank)[myTANKNUM])
{
	if (tank_hpup)
	{
		tank[myBODY].hp += 300;
		if (tank[myBODY].hp >= tank[myBODY].hpmax) tank[myBODY].hp = tank[myBODY].hpmax;
		tank_hpup = false;
	}
	else if (tank_hpdown)
	{
		tank[myBODY].hp -= 50;
		if (tank[myBODY].hp <= 0) tank[myBODY].hp = 0;
		tank_hpdown = false;
	}
}