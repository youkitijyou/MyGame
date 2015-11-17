#include "myDX.h"
#include "Shell.h"
#include "Player.h"

/////////////////////////////////////////////////////////////////////////
//  ’e‚Ì•`‰æ
/////////////////////////////////////////////////////////////////////////
void DrawShell(Shell &shell)
{
	D3DXMATRIX matAxis,matRot, matPos, mat,mat1;
	D3DXVECTOR3 axis(0.f, 0.f, 1.f);
	if (shell.active)
	{
		D3DXVec3TransformCoord(&axis, &axis, &shell.mat);
		D3DXMatrixRotationAxis(&matAxis, &axis, D3DXToRadian(shell.direction));
		D3DXMatrixTranslation(&matPos, shell.position.x, shell.position.y, shell.position.z);
		D3DXMatrixMultiply(&mat1, &matAxis, &shell.mat);
		D3DXMatrixMultiply(&mat, &mat1, &matPos);
		lpD3DDev->SetTransform(D3DTS_WORLD, &mat);
		DrawMyMesh(&shell.mesh);
	}
}

void DrawEmyShell(Shell &shell)
{
	D3DXMATRIX matRot, matPos, mat, mat1;
	if (shell.active)
	{
		D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(shell.direction), shell.pitch, shell.roll);
		D3DXMatrixTranslation(&matPos, shell.position.x, shell.position.y, shell.position.z);
		D3DXMatrixMultiply(&mat1, &matRot, &shell.mat);
		D3DXMatrixMultiply(&mat, &mat1, &matPos);
		lpD3DDev->SetTransform(D3DTS_WORLD, &mat);
		DrawMyMesh(&shell.mesh);
	}
}
/////////////////////////////////////////////////////////////////////////
//  ’e”­ŽË
/////////////////////////////////////////////////////////////////////////
void MoveShell(Shell &shell, Tank(&tank)[myTANKNUM], float speed, float cd)
{

	D3DXVECTOR3 vec;
	if (shell.fireOK == false)
	{
		if (shell.time < cd / FPS * 60.f)
		{
			shell.time += fpTimeDelta;
		}
		else
		{
			shell.fireOK = true;
			shell.time = cd / FPS * 60.f;
		}
	}
	if (shell.fireOK &&key&mLbtn)
	{
		shell.hitmax += 1;
		shell.active = true;
		shell.fireOK = false;
		shell.time = 0.f;
	}
	if (shell.active == false)
	{
		shell.position = tank[myGUN].position;
		shell.prePos = tank[myGUN].position;

		D3DXMatrixRotationYawPitchRoll(&shell.mat, D3DXToRadian(tank[myGUN].direction), tank[myGUN].pitch, tank[myGUN].roll);
		D3DXMatrixMultiply(&shell.mat, &shell.mat, &tank[myGUN].mat);
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.f, 0.f, 0.5f), &shell.mat);
		D3DXVec3Add(&shell.position, &tank[myGUN].position, &vec);
	}

	else if (shell.active)
	{
		shell.prePos = shell.position;
		D3DXVECTOR3 dist(0.0f, 0.0f, speed / 150.f);
		D3DXVec3TransformCoord(&dist, &dist, &shell.mat);
		D3DXVec3Add(&shell.position, &shell.position, &dist);

		if (D3DXVec3Length(D3DXVec3Subtract(&vec, &shell.position, &tank[myGUN].position)) > 600.f)
		{
			shell.active = false;
		}
	}
}

void MoveEmyShell(Shell &shell, Enemy(&enemy)[eTANKNUM], float speed, float cd)
{
	D3DXVECTOR3 vec;
	if (shell.fireOK == false)
	{
		if (shell.time < cd / FPS * 60.f)
		{
			shell.time += fpTimeDelta;
		}
		else
		{
			shell.fireOK = true;
		}
	}
	else if (shell.fireOK)
	{
		shell.active = true;
		shell.fireOK = false;
		shell.time = 0.f;
	}
	if (shell.active == false)
	{
		shell.position = enemy[eGUN].position;
		shell.prePos = enemy[eGUN].position;

		D3DXMatrixRotationYawPitchRoll(&shell.mat, D3DXToRadian(enemy[eGUN].direction), enemy[eGUN].pitch, enemy[eGUN].roll);
		D3DXMatrixMultiply(&shell.mat, &shell.mat, &enemy[eGUN].mat);
	}
	else if (shell.active)
	{
		shell.prePos = shell.position;
		D3DXVECTOR3 dist;
		dist = { 0.0f, 0.0f, speed / 150.f };
		D3DXVec3TransformCoord(&dist, &dist, &shell.mat);
		D3DXVec3Add(&shell.position, &shell.position, &dist);

		if (D3DXVec3Length(D3DXVec3Subtract(&vec, &shell.position, &enemy[eGUN].position)) > 600.f)
		{
			shell.active = false;
		}
	}
}
