#include "myDX.h"
#include "Camera.h"
#include "Enemy.h"
#include "Player.h"
#include "Title.h"
#include "Land.h"

/////////////////////////////////////////////////////////////////////////
//  カメラの設定
/////////////////////////////////////////////////////////////////////////
void SetCursorPos(const POINT& curpt, Tank(&tank)[myTANKNUM])
{
	//照準合わせる
	if (curpt.x <= 0)			SetCursorPos(1884, curpt.y);
	else if (curpt.x >= 1884)	SetCursorPos(0, curpt.y);

	//pitchの制限
	if (tank[myBODY].pitch < 0.f)
	{
		if (curpt.y >= 900 - (int)(tank[myBODY].pitch*400.f))	SetCursorPos(curpt.x, 900 - (int)(tank[myBODY].pitch*400.f));
		else if (curpt.y <= 550 + (int)(tank[myBODY].pitch*400.f))	SetCursorPos(curpt.x, 550 + (int)(tank[myBODY].pitch*400.f));
	}
	else if (tank[myBODY].pitch >= 0.f)
	{
		if (curpt.y >= 900 - (int)(tank[myBODY].pitch*200.f))	SetCursorPos(curpt.x, 900 - (int)(tank[myBODY].pitch*200.f));
		else if (curpt.y <= 550 + (int)(tank[myBODY].pitch*200.f))	SetCursorPos(curpt.x, 550 + (int)(tank[myBODY].pitch*200.f));
	}
}

void SetCursorPos2(const POINT& curpt, Tank(&tank)[myTANKNUM])
{
	//照準合わせる2
	if (curpt.x <= 0)			SetCursorPos(1884, curpt.y);
	else if (curpt.x >= 1884)	SetCursorPos(0, curpt.y);

	if (curpt.y >= 800)			SetCursorPos(curpt.x, 800);
	else if (curpt.y <= 400)	SetCursorPos(curpt.x, 400);
}

//カメラ1
void SetupCamera(D3DXVECTOR3 *position)
{
	camera.m_oldpt.x = 1920 / 2;
	camera.m_oldpt.y = 1080 / 2;
	camera.m_curpt.x = 0;
	camera.m_curpt.y = 1080 - camera.m_curpt.y;
	GetCursorPos(&camera.m_curpt);	//マウス座標取得
	camera.m_rolaX = 0.0f;
	camera.m_rolaY = 0.0f;

	camera.m_rolaY = (camera.m_curpt.x - camera.m_oldpt.x) / 300.f;
	camera.m_rolaX = (camera.m_curpt.y - camera.m_oldpt.y) / 300.f;
	if (camera.key_E == false)	camera.m_vDelt = D3DXVECTOR3(0.0f, 0.0f, 20.0f);	//E離す
	if (camera.key_E)			camera.m_vDelt = D3DXVECTOR3(0.0f, 0.0f, 100.0f);	//E押す

	camera.m_lookat = *position + D3DXVECTOR3(0.f, 3.f, 0.f);
	camera.m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	camera.m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	camera.m_oldpt = camera.m_curpt;

	//座標変換
	D3DXMatrixRotationYawPitchRoll(&camera.matRola, camera.m_rolaY, camera.m_rolaX, 0.0f);
	D3DXVec3TransformCoord(&camera.vdelt, &camera.m_vDelt, &camera.matRola);
	camera.m_pos = camera.m_lookat - camera.vdelt;
	D3DXMatrixLookAtLH(&camera.m_view, &camera.m_pos, &camera.m_lookat, &camera.m_up);
	lpD3DDev->SetTransform(D3DTS_VIEW, &camera.m_view);
	D3DXMatrixPerspectiveFovLH(&camera.m_proj, D3DXToRadian(32.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
	lpD3DDev->SetTransform(D3DTS_PROJECTION, &camera.m_proj);

	if (count < 0)
	{
		//タンク種類取得
		switch (num_tank)
		{
		case 11:
			SetCursorPos(camera.m_curpt, T44);
			break;
		case 12:
			SetCursorPos(camera.m_curpt, IS1);
			break;
		case 13:
			SetCursorPos(camera.m_curpt, T54);
			break;
		case 14:
			SetCursorPos(camera.m_curpt, IS3);
			break;
		case 21:
			SetCursorPos(camera.m_curpt, PantherG);
			break;
		case 22:
			SetCursorPos(camera.m_curpt, Tiger);
			break;
		case 23:
			SetCursorPos(camera.m_curpt, PantherII);
			break;
		case 24:
			SetCursorPos(camera.m_curpt, TigerII);
			break;
		case 31:
			SetCursorPos(camera.m_curpt, M26);
			break;
		case 32:
			SetCursorPos(camera.m_curpt, T32);
			break;
		case 33:
			SetCursorPos(camera.m_curpt, M46);
			break;
		case 34:
			SetCursorPos(camera.m_curpt, M103);
			break;
		}
	}
}

//カメラ2
void Camera_Far(D3DXVECTOR3 *position)
{
	camera.m_oldpt.x = 1920 / 2;
	camera.m_oldpt.y = 1080 / 2;
	camera.m_curpt.x = 0;
	camera.m_curpt.y = 0;
	GetCursorPos(&camera.m_curpt);
	camera.m_rolaX = 0.0f;
	camera.m_rolaY = 0.0f;

	camera.m_rolaY = (camera.m_curpt.x - camera.m_oldpt.x) / 300.f;
	camera.m_rolaX = (camera.m_curpt.y - camera.m_oldpt.y - 200) / 300.f;

	camera.m_pos = *position + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	camera.m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	camera.m_oldpt = camera.m_curpt;
	camera.m_vDelt = D3DXVECTOR3(0.0f, -15.0f, 22.0f);

	D3DXMatrixRotationYawPitchRoll(&camera.matRola, camera.m_rolaY, camera.m_rolaX, 0.0f);
	D3DXVec3TransformCoord(&camera.vdelt, &camera.m_vDelt, &camera.matRola);
	camera.m_lookat = camera.m_pos + camera.vdelt;
	D3DXMatrixLookAtLH(&camera.m_view, &camera.m_pos, &camera.m_lookat, &camera.m_up);
	lpD3DDev->SetTransform(D3DTS_VIEW, &camera.m_view);
	D3DXMatrixPerspectiveFovLH(&camera.m_proj, D3DXToRadian(10.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
	lpD3DDev->SetTransform(D3DTS_PROJECTION, &camera.m_proj);

	if (count < 0)
	{
		switch (num_tank)
		{
		case 11:
			SetCursorPos2(camera.m_curpt, T44);
			break;
		case 12:
			SetCursorPos2(camera.m_curpt, IS1);
			break;
		case 13:
			SetCursorPos2(camera.m_curpt, T54);
			break;
		case 14:
			SetCursorPos2(camera.m_curpt, IS3);
			break;
		case 21:
			SetCursorPos2(camera.m_curpt, PantherG);
			break;
		case 22:
			SetCursorPos2(camera.m_curpt, Tiger);
			break;
		case 23:
			SetCursorPos2(camera.m_curpt, PantherII);
			break;
		case 24:
			SetCursorPos2(camera.m_curpt, TigerII);
			break;
		case 31:
			SetCursorPos2(camera.m_curpt, M26);
			break;
		case 32:
			SetCursorPos2(camera.m_curpt, T32);
			break;
		case 33:
			SetCursorPos2(camera.m_curpt, M46);
			break;
		case 34:
			SetCursorPos2(camera.m_curpt, M103);
			break;
		}
	}
}

//タンク頭と照準の角度（左右）
void For_a(Tank(&tank)[myTANKNUM])
{
	D3DXVECTOR3 m_vec;
	D3DXVECTOR3 m_head;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_lookat;
	float m_val;

	m_pos = { camera.m_pos.x, 0.f, camera.m_pos.z };
	m_lookat = { camera.m_lookat.x, 0.f, camera.m_lookat.z };
	m_head = { 0.f, 0.f, 1.f };
	D3DXVec3Subtract(&m_vec, &m_pos, &m_lookat);
	D3DXVec3Normalize(&m_vec, &m_vec);
	D3DXVec3Normalize(&m_head, &m_head);
	m_val = D3DXVec3Dot(&m_vec, &m_head);
	if (camera.m_curpt.x >= 960 && camera.m_curpt.x <= 1884)	tank[myHEAD].a = 180.f - D3DXToDegree(acos(m_val));
	else if (camera.m_curpt.x >= 0 && camera.m_curpt.x < 960)	tank[myHEAD].a = -180.f + D3DXToDegree(acos(m_val));
	if (tank[myHEAD].a >= 360.f)	tank[myHEAD].a -= 360.f;
	if (tank[myHEAD].a <= -360.f) tank[myHEAD].a += 360.f;
}

//タンク頭と照準の角度（上下）
void For_b(Tank(&tank)[myTANKNUM], float pitchmax, float pitchmin)
{
	D3DXVECTOR3 m_vec;
	D3DXVECTOR3 m_gun;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_lookat;
	float m_val;

	D3DXVec3Subtract(&m_vec, &camera.m_pos, &camera.m_lookat);
	m_pos = { camera.m_pos.x, 0.f, camera.m_pos.z };
	m_lookat = { camera.m_lookat.x, 0.f, camera.m_lookat.z };
	D3DXVec3Subtract(&m_gun, &m_pos, &m_lookat);
	D3DXVec3Normalize(&m_vec, &m_vec);
	D3DXVec3Normalize(&m_gun, &m_gun);
	m_val = D3DXVec3Dot(&m_vec, &m_gun);
	if (camera.m_pos.y < tank[myBODY].position.y)
	{
		tank[myGUN].b = -D3DXToDegree(acos(m_val));
		if (tank[myGUN].b <= -pitchmax) tank[myGUN].b = -pitchmax;
	}
	else if (camera.m_pos.y >= tank[myBODY].position.y)
	{
		tank[myGUN].b = D3DXToDegree(acos(m_val));
		if (tank[myGUN].b >= pitchmin) tank[myGUN].b = pitchmin;
	}
}

//敵頭とタンクの角度（左右）
void For_c(Enemy(&enemy)[eTANKNUM], Tank(&tank)[myTANKNUM])
{
	D3DXVECTOR3 emy_ply;
	D3DXVECTOR3 emy_z;
	float e_val;

	emy_ply = enemy[eBODY].position - tank[myBODY].position;
	emy_z = { 0.f, 0.f, 1.f };
	D3DXVec3Normalize(&emy_ply, &emy_ply);
	D3DXVec3Normalize(&emy_z, &emy_z);
	e_val = D3DXVec3Dot(&emy_ply, &emy_z);
	if (enemy[eBODY].position.x <= tank[myBODY].position.x)     enemy[eHEAD].c = 180.f - D3DXToDegree(acos(e_val));
	else if (enemy[eBODY].position.x > tank[myBODY].position.x) enemy[eHEAD].c = -180.f + D3DXToDegree(acos(e_val));
	if (enemy[eHEAD].c >= 360.f)	enemy[eHEAD].c -= 360.f;
	if (enemy[eHEAD].c <= -360.f) enemy[eHEAD].c += 360.f;
}

//敵頭とタンクの角度（上下）
void For_d(Enemy(&enemy)[eTANKNUM], Tank(&tank)[myTANKNUM], float pitchmax, float pitchmin)
{
	D3DXVECTOR3 emy_ply;
	D3DXVECTOR3 emy_y0;
	D3DXVECTOR3 x;
	float e_val;
	x = { 0.f, 2.f, 0.f };

	emy_ply = enemy[eBODY].position - (tank[myBODY].position - x);
	emy_y0 = { emy_ply.x, 0.f, emy_ply.z };
	D3DXVec3Normalize(&emy_ply, &emy_ply);
	D3DXVec3Normalize(&emy_y0, &emy_y0);
	e_val = D3DXVec3Dot(&emy_ply, &emy_y0);

	if (enemy[eBODY].position.y <= (tank[myBODY].position.y - 2.f))
	{
		enemy[eGUN].d = -D3DXToDegree(acos(e_val)) / 3.f;
		if (enemy[eGUN].d <= -pitchmax) enemy[eGUN].d = -pitchmax;
	}
	else if (enemy[eBODY].position.y > (tank[myBODY].position.y - 2.f))
	{
		enemy[eGUN].d = D3DXToDegree(acos(e_val)) / 3.f;
		if (enemy[eGUN].d >= pitchmin) enemy[eGUN].d = pitchmin;
	}
}

//敵頭と敵タンクの角度（左右）
void For_e(Enemy(&enemy)[eTANKNUM])
{
	D3DXVECTOR3 emy_pot;
	D3DXVECTOR3 x0;
	float p_val;

	emy_pot = enemy[eBODY].position - Point.position;
	x0 = { 0.f, 0.f, 1.f };
	D3DXVec3Normalize(&emy_pot, &emy_pot);
	p_val = D3DXVec3Dot(&emy_pot, &x0);

	if (enemy[eBODY].position.x <= Point.position.x)     enemy[eBODY].e = 180.f - D3DXToDegree(acos(p_val));
	else if (enemy[eBODY].position.x > Point.position.x) enemy[eBODY].e = -180.f + D3DXToDegree(acos(p_val));
	if (enemy[eBODY].e >= 360.f)	enemy[eBODY].e -= 360.f;
	if (enemy[eBODY].e <= -360.f) enemy[eBODY].e += 360.f;
}