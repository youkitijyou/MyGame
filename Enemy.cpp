#include "myDX.h"
#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "Land.h"

/////////////////////////////////////////////////////////////////////////
//  êÌé‘ÇÃï`âÊ
/////////////////////////////////////////////////////////////////////////
void DrawEnemy(Enemy(&enemy)[eTANKNUM])
{
	D3DXMATRIX matID, matRot, matPos, mat1, mat;

	for (int i = 0; i < eTANKNUM; ++i)
	{
		D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(enemy[i].direction), enemy[i].pitch, enemy[i].roll);
		D3DXMatrixTranslation(&matPos, enemy[i].position.x, enemy[i].position.y, enemy[i].position.z);
		D3DXMatrixMultiply(&mat1, &matRot, &enemy[i].mat);
		D3DXMatrixMultiply(&mat, &mat1, &matPos);
		lpD3DDev->SetTransform(D3DTS_WORLD, &mat);
		Draw3DMesh(enemy[i].mesh.matCount, enemy[i].mesh.pMat, enemy[i].mesh.pTex, enemy[i].mesh.lpMesh);
	}
}
/////////////////////////////////////////////////////////////////////////
//  êÌé‘ÇÃà⁄ìÆ
/////////////////////////////////////////////////////////////////////////
void MoveChildEmy(Enemy(&enemy)[eTANKNUM])
{
	for (int i = eHEAD; i < eTANKNUM; ++i)
	{
		D3DXMatrixRotationYawPitchRoll(&enemy[i].mat, D3DXToRadian(enemy[i - 1].direction), enemy[i - 1].pitch, enemy[i - 1].roll);
		D3DXMatrixMultiply(&enemy[i].mat, &enemy[i].mat, &enemy[i - 1].mat);

		D3DXVec3TransformCoord(&enemy[i].position, &enemy[i].offsetEmy, &enemy[i].mat);
		D3DXVec3Add(&enemy[i].position, &enemy[i].position, &enemy[i - 1].position);
	}
}

void MoveEnemy(Enemy(&enemy)[eTANKNUM], float speedmax, float pitchmax, float acc1, float acc2, float turn)
{
	D3DXMATRIX mat;
	D3DXVECTOR3 vec;
	
	if (enemy[eBODY].hp > 0)
	{
		if (!enemy[eBODY].Emyflagobb&&!enemy[eBODY].Emyflagobb&&enemy[eBODY].e - enemy[eBODY].direction <= 3.f&&enemy[eBODY].e - enemy[eBODY].direction >= -3.f)
		{
			if (enemy[eBODY].pitch <= 0)
			{
				if ((enemy[eBODY].speed += (speedmax / 1000.f*5.0f / acc1 / 50.f)) >=
					speedmax / 1000.f*5.0f + (enemy[eBODY].pitch*(speedmax / 1000.f*5.0f / D3DXToRadian(pitchmax))))
					enemy[eBODY].speed = speedmax / 1000.f*5.0f + (enemy[eBODY].pitch*(speedmax / 1000.f*5.0f / D3DXToRadian(pitchmax)));
			}
			else if (enemy[eBODY].pitch > 0)
			{
				if ((enemy[eBODY].speed += (speedmax / 1000.f*5.0f / acc1 / 50.f)) >= speedmax / 1000.f*5.0f) enemy[eBODY].speed = speedmax / 1000.f*5.0f;
			}
			if (enemy[eBODY].Emypoint)
			{
				enemy[eBODY].speed -= 0.005f;
				if (enemy[eBODY].speed <= 0.f) enemy[eBODY].speed = 0.f;
			}
		}
		if (enemy[eBODY].Emyflagobb)
		{
			DWORD buf_time = timeGetTime();
			enemy[eBODY].speed = buf_time % 10 * (-0.01f);
		}
		D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(enemy[eBODY].direction), enemy[eBODY].pitch, enemy[eBODY].roll);
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 0.0f, enemy[eBODY].speed), &mat);
		D3DXVec3Add(&enemy[eBODY].position, &enemy[eBODY].position, &vec);

		if (enemy[eBODY].e - enemy[eBODY].direction >= 0.f&&enemy[eBODY].e - enemy[eBODY].direction <= 180.f)
		{
			if (!enemy[eBODY].Emyflagobb)
			{
				enemy[eBODY].turn += 0.03f;
				if (enemy[eBODY].turn >= 360.f / turn / 100.f) enemy[eBODY].turn = 360.f / turn / 100.f;
				enemy[eBODY].direction += enemy[eBODY].turn;
				if (enemy[eBODY].direction >= enemy[eBODY].e) enemy[eBODY].direction = enemy[eBODY].e;
			}
			if (enemy[eBODY].Emyflagobb)
			{
				DWORD buf_time = timeGetTime();
				enemy[eBODY].speed = buf_time % 10 * (-0.01f);
			}
		}
		else if (enemy[eBODY].e - enemy[eBODY].direction > 180.f&&enemy[eBODY].e - enemy[eBODY].direction < 360.f)
		{
			if (!enemy[eBODY].Emyflagobb)
			{
				enemy[eBODY].direction += 360.f;
				enemy[eBODY].turn += 0.03f;
				if (enemy[eBODY].turn >= 360.f / turn / 100.f) enemy[eBODY].turn = 360.f / turn / 100.f;
				enemy[eBODY].direction -= enemy[eBODY].turn;
				if (enemy[eBODY].direction <= enemy[eBODY].e) enemy[eBODY].direction = enemy[eBODY].e;
			}
			if (enemy[eBODY].Emyflagobb)
			{
				DWORD buf_time = timeGetTime();
				enemy[eBODY].speed = buf_time % 10 * (-0.01f);
			}
		}
		else if (enemy[eBODY].e - enemy[eBODY].direction < 0.f&&enemy[eBODY].e - enemy[eBODY].direction >= -180.f)
		{
			if (!enemy[eBODY].Emyflagobb)
			{
				enemy[eBODY].turn += 0.03f;
				if (enemy[eBODY].turn >= 360.f / turn / 100.f) enemy[eBODY].turn = 360.f / turn / 100.f;
				enemy[eBODY].direction -= enemy[eBODY].turn;
				if (enemy[eBODY].direction <= enemy[eBODY].e) enemy[eBODY].direction = enemy[eBODY].e;
			}
			if (enemy[eBODY].Emyflagobb)
			{
				DWORD buf_time = timeGetTime();
				enemy[eBODY].speed = buf_time % 10 * (-0.01f);
			}
		}
		else if (enemy[eBODY].e - enemy[eBODY].direction < -180.f&&enemy[eBODY].e - enemy[eBODY].direction >= -360.f)
		{
			if (!enemy[eBODY].Emyflagobb)
			{
				enemy[eBODY].direction -= 360.f;
				enemy[eBODY].turn += 0.03f;
				if (enemy[eBODY].turn >= 360.f / turn / 100.f) enemy[eBODY].turn = 360.f / turn / 100.f;
				enemy[eBODY].direction += enemy[eBODY].turn;
				if (enemy[eBODY].direction >= enemy[eBODY].e) enemy[eBODY].direction = enemy[eBODY].e;
			}
			if (enemy[eBODY].Emyflagobb)
			{
				DWORD buf_time = timeGetTime();
				enemy[eBODY].speed = buf_time % 10 * (-0.01f);
			}
		}
	}
	//É^ÉìÉNèàï™
	else if (enemy[eBODY].hp <= 0)
	{
		enemy[eBODY].position = { 0.f, 1000.f, 0.f };
		enemy[eHEAD].position = { 0.f, 1000.f, 0.f };
		enemy[eGUN].position = { 0.f, 1000.f, 0.f };
	}
}
/////////////////////////////////////////////////////////////////////////
//  HEADÇÃà⁄ìÆ
/////////////////////////////////////////////////////////////////////////
void MoveHeadEmy(Enemy(&enemy)[eTANKNUM], float turn)
{
	if (enemy[eHEAD].c - enemy[eHEAD].direction - enemy[eBODY].direction >= 0.f
		&&enemy[eHEAD].c - enemy[eHEAD].direction - enemy[eBODY].direction <= 180.f)
	{
		enemy[eHEAD].direction += turn / 60.f;
		if (enemy[eHEAD].direction >= enemy[eHEAD].c - enemy[eBODY].direction)
			enemy[eHEAD].direction = enemy[eHEAD].c - enemy[eBODY].direction;
	}
	else if (enemy[eHEAD].c - enemy[eHEAD].direction - enemy[eBODY].direction > 180.f&&
		enemy[eHEAD].c - enemy[eHEAD].direction - enemy[eBODY].direction < 360.f)
	{
		enemy[eHEAD].direction += 360.f;
		enemy[eHEAD].direction -= turn / 60.f;
		if (enemy[eHEAD].direction <= enemy[eHEAD].c - enemy[eBODY].direction)
			enemy[eHEAD].direction = enemy[eHEAD].c - enemy[eBODY].direction;
	}
	else if (enemy[eHEAD].c - enemy[eHEAD].direction - enemy[eBODY].direction < 0.f&&
		enemy[eHEAD].c - enemy[eHEAD].direction - enemy[eBODY].direction >= -180.f)
	{
		enemy[eHEAD].direction -= turn / 60.f;
		if (enemy[eHEAD].direction <= enemy[eHEAD].c - enemy[eBODY].direction)
			enemy[eHEAD].direction = enemy[eHEAD].c - enemy[eBODY].direction;
	}
	else if (enemy[eHEAD].c - enemy[eHEAD].direction - enemy[eBODY].direction < -180.f&&
		enemy[eHEAD].c - enemy[eHEAD].direction - enemy[eBODY].direction >= -360.f)
	{
		enemy[eHEAD].direction -= 360.f;
		enemy[eHEAD].direction += turn / 60.f;
		if (enemy[eHEAD].direction >= enemy[eHEAD].c - enemy[eBODY].direction)
			enemy[eHEAD].direction = enemy[eHEAD].c - enemy[eBODY].direction;
	}
}
/////////////////////////////////////////////////////////////////////////
//  GUNÇÃà⁄ìÆ
/////////////////////////////////////////////////////////////////////////
void MoveGunEmy(Enemy(&enemy)[eTANKNUM], float pitchmax, float pitchmin)
{
	if (enemy[eGUN].pitch >= D3DXToRadian(enemy[eGUN].d))
	{
		enemy[eGUN].pitch -= D3DXToRadian(0.1f);
		if (enemy[eGUN].pitch <= -D3DXToRadian(pitchmax)) enemy[eGUN].pitch = -D3DXToRadian(pitchmax);
	}
	else if (enemy[eGUN].pitch < D3DXToRadian(enemy[eGUN].d))
	{
		enemy[eGUN].pitch += D3DXToRadian(0.1f);
		if (enemy[eGUN].pitch >= D3DXToRadian(pitchmin)) enemy[eGUN].pitch = D3DXToRadian(pitchmin);
	}
}

/////////////////////////////////////////////////////////////////////////
//  DamageÇÃåvéZ
/////////////////////////////////////////////////////////////////////////
void EmyDamage(Enemy(&enemy)[eTANKNUM], Tank(&tank)[myTANKNUM], float dmg10, float dmg2000)
{
	D3DXVECTOR3 vec;
	float dist;
	float damage;

	dist = D3DXVec3Length(D3DXVec3Subtract(&vec, &enemy[eBODY].position, &tank[myBODY].position));
	if (dist <= 10.f) dist = 10.f;
	else if (dist >= 2000.f) dist = 2000.f;
	if (enemy[eHEAD].EmyDamage)
	{
		damage = (((dmg2000 - dmg10) / (2000.f - 10.f)*dist + dmg10 - 10.f*(dmg2000 - dmg10) / (2000.f - 10.f)) - enemy[eHEAD].armor)*5.f;
		if (damage <= 0) damage = 0;
		enemy[eBODY].hp -= (int)damage;
		if (enemy[eBODY].hp <= 0) enemy[eBODY].hp = 0;
		enemy[eHEAD].EmyDamage = false;
	}
	if (enemy[eBODY].EmyDamage)
	{
		damage = (((dmg2000 - dmg10) / (2000.f - 10.f)*dist + dmg10 - 10.f*(dmg2000 - dmg10) / (2000.f - 10.f)) - enemy[eBODY].armor)*5.f;
		if (damage <= 0) damage = 0;
		enemy[eBODY].hp -= (int)damage;
		if (enemy[eBODY].hp <= 0) enemy[eBODY].hp = 0;
		enemy[eBODY].EmyDamage = false;
	}
}