/////////////////////////////////////////////////////////////////////////
// MyGame.cpp        ver 1.0 ( '05.04.01 Hiroshi Ikuyama )
//	�Q�[���̃v���O�����t�@�C��
//	Copyright(c) 2005 Hiroshi Ikuyama. All rights reserved.
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//	�w�b�_�[�t�@�C��
/////////////////////////////////////////////////////////////////////////
#include "myDX.h"
#include "Camera.h"
#include "Land.h"
//#define kFULLSCREEN
/////////////////////////////////////////////////////////////////////////
//	�񋓃f�[�^
/////////////////////////////////////////////////////////////////////////
enum { eBODY, eHEAD, eGUN, eTANKNUM };
/////////////////////////////////////////////////////////////////////////
//	�萔�̒�`
/////////////////////////////////////////////////////////////////////////
//�L�[�t���O�p�萔
#define		kKEYENTER		0x0001
#define		kKEYW			0x0002
#define		kKEYS			0x0004									
#define		kKEYA			0x0008									
#define		kKEYD			0x0010									
#define		kKEYE			0x0020									

/////////////////////////////////////////////////////////////////////////
//	�Q�[���p�f�[�^�̍\���̒�`
/////////////////////////////////////////////////////////////////////////
typedef struct tagMyTank
{
	MyMesh mesh;
	D3DXVECTOR3 position;
	float direction;
	float pitch;
	float roll;
	D3DXVECTOR3 vecMin, vecMax;
	D3DXMATRIX mat;
	D3DXVECTOR3 offset;

	float speed;
}MyTank;
/////////////////////////////////////////////////////////////////////////
//	�Q�[���p�f�[�^�ϐ��̐錾
/////////////////////////////////////////////////////////////////////////
//�S�̃f�[�^�̐錾
short						key;								//���̓L�[�Ǘ��p
HRESULT						(*func)(void);						//�Q�[���p�֐�
DWORD						startTime;							//�X�e�[�W�̃X�^�[�g�^�C��
LPDIRECT3DTEXTURE9 lpTitle;
//InGame
MyTank T44[eTANKNUM];
MyLand myLand;
Camera camera;
/////////////////////////////////////////////////////////////////////////
//	�v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
//  Windows�v���O�����i�Q�[���v���O�����j�ɂ�����W���I�ȃv���g�^�C�v�錾
LRESULT WINAPI WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
HRESULT GameLoop(HWND hWnd);
//  �Q�[���f�[�^�֌W�̃v���g�^�C�v�錾
HRESULT CheckKey(void);
void InitMyData(void);
HRESULT SetupMyData(HWND hWnd);
void ReleaseAll(void);
void DrawStageName(LPCTSTR pString,RECT rect);
//  �I�[�v�j���O�֌W�̃v���g�^�C�v�錾
HRESULT InitOpen(void);
HRESULT DoOpen(void);
void DrawOpen(void);
HRESULT DisposeOpen(void);
//  �C���Q�[��(3D)�֌W�̃v���g�^�C�v�錾
HRESULT InitInGame(void);
HRESULT SetupInGame(void);
HRESULT DoInGame(void);
	void MoveTank(void);
	void MoveChild(MyTank *pChild, MyTank *pParent);
	void MoveHead(float *a, float *yaw);
	void MoveGun(float *b, float *pitch);
	void CheckHeight(D3DXVECTOR3 *pVec);
	BOOL CheckIntersect(LPD3DXMESH lpMesh, D3DXVECTOR3 *rayPos, D3DXVECTOR3 *ray, float *pDist);
	void CheckLean(D3DXVECTOR3 *pPos, float yaw, float *pitch, float *roll);
void DrawInGame(void);
void Draw2DFrontInGame(void);
void Draw3DInGame(void);
	void Setup3DEnv(void);
	void SetupLight(void);
	void SetupCamera(D3DXVECTOR3 *position);
	void Camera_Far(D3DXVECTOR3 *position);
	void For_a(void);
	void For_b(float *pitch);
	void DrawTank(void);
	void DrawLand(void);
void Draw2DBackInGame(void);
HRESULT DisposeInGame(void);
/////////////////////////////////////////////////////////////////////////
//  InGame������
/////////////////////////////////////////////////////////////////////////
HRESULT InitInGame(void)
{
	if(FAILED(SetupInGame()))		return E_FAIL;
	//InGame�̊�{����
	func		=DoInGame;
	startTime	=timeGetTime();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  InGame�̃f�[�^������
/////////////////////////////////////////////////////////////////////////
HRESULT SetupInGame(void)
{
	//�ȉ��AInGame�̏������L�q
	char path[] = "X\\";
	char *tankFileName[] = { "T44body.x", "T44head.x", "T44gun.x" };
	char *fNameLand = "ground.x";

	D3DXVECTOR3 offset[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				//???
		D3DXVECTOR3(0.0f, -0.05f, -0.6f),			//???
		D3DXVECTOR3(0.1f, 2.1f, 2.6f),				//???
	};

	for (int i = 0; i < eTANKNUM; ++i)
	{
		T44[i].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		T44[i].direction = 0.0f;
		T44[i].pitch = 0.0f;
		T44[i].roll = 0.0f;
		D3DXMatrixIdentity(&T44[i].mat);
		T44[i].offset = offset[i];
		T44[i].speed = 0.0f;
		if (FAILED(LoadXFile(tankFileName[i], &T44[i].mesh, path)))
			return E_FAIL;
	}

	if (FAILED(LoadXFile(fNameLand, &myLand.mesh, path)))
		return E_FAIL;
	myLand.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�ȏ�AInGame�̏������L�q
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  InGame�����s
/////////////////////////////////////////////////////////////////////////
HRESULT DoInGame(void)
{
	MoveTank();
	MoveHead(&camera.a, &T44[eHEAD].direction);
	MoveGun(&camera.b, &T44[eGUN].pitch);
	CheckHeight(&T44[eBODY].position);
	CheckLean(&T44[eBODY].position, D3DXToRadian(T44[eBODY].direction), &T44[eBODY].pitch, &T44[eBODY].roll);
	for (int i = eHEAD; i<eTANKNUM; ++i) MoveChild(&T44[i], &T44[i - 1]);

	DrawInGame();
	if (timeGetTime() - startTime > 1000)
	{
		if (key&kKEYENTER)
		{
			func = DisposeInGame;
		}
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  �`��
/////////////////////////////////////////////////////////////////////////
void DrawInGame(void)
{
	lpD3DDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 255), 1.0, 0);
	lpD3DDev->BeginScene();
	Draw2DBackInGame();
	Draw3DInGame();
	Draw2DFrontInGame();
	lpD3DDev->EndScene();
	lpD3DDev->Present(NULL, NULL, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////
//  �`��i�O�i�j
/////////////////////////////////////////////////////////////////////////
void Draw2DFrontInGame(void)
{
	//�`�揈���J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//�ȉ��O�i�`��
	//�ȏ�O�i�`��
	//�ȉ��X�e�[�W���\��

	//�`�揈���I��
	lpSprite->End();
}

/////////////////////////////////////////////////////////////////////////
//  �`��i3D�j
/////////////////////////////////////////////////////////////////////////
void Draw3DInGame(void)
{
	//�ȉ���3D �`��
	Setup3DEnv();
	SetupLight();
	if (camera.m_Rbtn==false)	SetupCamera(&T44[eHEAD].position);
	if (camera.m_Rbtn)			Camera_Far(&T44[eHEAD].position);
	For_a();
	For_b(&T44[eBODY].pitch);
	DrawTank();
	DrawLand();
	//�ȏ��3D �`��
}

/////////////////////////////////////////////////////////////////////////
//  �`��i2D�w�i�j
/////////////////////////////////////////////////////////////////////////
void Draw2DBackInGame(void)
{
	//�`�揈���J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//�ȉ��w�i�`��
	//�ȏ�w�i�`��
	//�`�揈���I��
	lpSprite->End();
}

/////////////////////////////////////////////////////////////////////////
//  InGame����n��
/////////////////////////////////////////////////////////////////////////
HRESULT DisposeInGame(void)
{
	//�ȉ���InGame�f�[�^�̃����[�X
	for (int i = 0; i < eTANKNUM; ++i) ReleaseXMesh(&T44[i].mesh);
	//�ȏ��InGame�f�[�^�̃����[�X
	func = InitOpen;
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////
//  3D�`����̐ݒ�
/////////////////////////////////////////////////////////////////////////
void Setup3DEnv(void)
{
	lpD3DDev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	lpD3DDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	lpD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	lpD3DDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	float start = 40.0f, end = 100.0f;
	lpD3DDev->SetRenderState(D3DRS_FOGENABLE, TRUE);
	lpD3DDev->SetRenderState(D3DRS_FOGCOLOR, 0xffcccccc);
	lpD3DDev->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	lpD3DDev->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&start));
	lpD3DDev->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&end));
}
/////////////////////////////////////////////////////////////////////////
//  ���C�g�̐ݒ�
/////////////////////////////////////////////////////////////////////////
void SetupLight(void)
{
	D3DCOLORVALUE color[2][3] =
	{
		{ { 1.0f, 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f } },
		{ { 0.5f, 0.5f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f } }
	};

	SetupDirectionalLight(color[0], D3DXVECTOR3(0.0f, -1.0f, 1.0f), 0);
	SetupDirectionalLight(color[1], D3DXVECTOR3(0.0f, 1.0f, 1.0f), 1);
	lpD3DDev->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}
/////////////////////////////////////////////////////////////////////////
//  ��Ԃ̕`��
/////////////////////////////////////////////////////////////////////////
void DrawTank(void)
{
	D3DXMATRIX matID, matRot, matPos, mat1, mat;

	for (int i = 0; i < eTANKNUM; ++i)
	{
		D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(T44[i].direction), T44[i].pitch, T44[i].roll);
		D3DXMatrixTranslation(&matPos, T44[i].position.x, T44[i].position.y, T44[i].position.z);
		D3DXMatrixMultiply(&mat1, &matRot, &T44[i].mat);
		D3DXMatrixMultiply(&mat, &mat1, &matPos);
		lpD3DDev->SetTransform(D3DTS_WORLD, &mat);
		Draw3DMesh(T44[i].mesh.matCount, T44[i].mesh.pMat, T44[i].mesh.pTex, T44[i].mesh.lpMesh);
	}
}
/////////////////////////////////////////////////////////////////////////
//  ��Ԃ̈ړ�
/////////////////////////////////////////////////////////////////////////
void MoveTank(void)
{
	D3DXMATRIX mat;
	D3DXVECTOR3 vec;

	if (key&kKEYW)
	{
		if (T44[eBODY].pitch <= 0)
		{
			if ((T44[eBODY].speed += 0.001f) >= 0.049f*2.0f + (T44[eBODY].pitch*0.156f)) T44[eBODY].speed = 0.049f*2.0f + (T44[eBODY].pitch*0.156f);
		}
		else
		{
			if ((T44[eBODY].speed += 0.001f) >= 0.049f*2.0f) T44[eBODY].speed = 0.049f*2.0f;
		}
		D3DXMatrixRotationYawPitchRoll(&mat,D3DXToRadian(T44[eBODY].direction),T44[eBODY].pitch,T44[eBODY].roll);
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 0.0f, T44[eBODY].speed), &mat);
		D3DXVec3Add(&T44[eBODY].position, &T44[eBODY].position, &vec);
	}
	else
	{
		if ((T44[eBODY].speed -= 0.0005f) <= 0.0f) T44[eBODY].speed = 0.0f;
		D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(T44[eBODY].direction), T44[eBODY].pitch, T44[eBODY].roll);
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 0.0f, T44[eBODY].speed), &mat);
		D3DXVec3Add(&T44[eBODY].position, &T44[eBODY].position, &vec);
	}
	if (key&kKEYS)
	{
		D3DXMatrixRotationYawPitchRoll(&mat,D3DXToRadian(T44[eBODY].direction),T44[eBODY].pitch,T44[eBODY].roll);
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0.0f, 0.0f, -0.03f), &mat);
		D3DXVec3Add(&T44[eBODY].position, &T44[eBODY].position, &vec);
	}
	if (key&kKEYD)
	{
		if ((T44[eBODY].direction += 0.25f) >= 360.f) T44[eBODY].direction -= 360.f;
	}
	if (key&kKEYA)
	{
		if ((T44[eBODY].direction -= 0.25f) <= -360.f) T44[eBODY].direction += 360.f;
	}
}

void MoveChild(MyTank *pChild, MyTank *pParent)
{
	D3DXMATRIX mat;

	D3DXMatrixRotationYawPitchRoll(&pChild->mat, D3DXToRadian(pParent->direction), pParent->pitch, pParent->roll);
	D3DXMatrixMultiply(&pChild->mat, &pChild->mat, &pParent->mat);

	D3DXVec3TransformCoord(&pChild->position, &pChild->offset, &pChild->mat);
	D3DXVec3Add(&pChild->position, &pChild->position, &pParent->position);
}

void MoveHead(float *a,float *yaw)
{
	if (*a - *yaw - T44[eBODY].direction >= 0.f&&*a - *yaw - T44[eBODY].direction <= 180.f)
	{
		*yaw += 0.4f;
		if (*yaw >= *a - T44[eBODY].direction) *yaw = *a - T44[eBODY].direction;
	}
	else if (*a - *yaw - T44[eBODY].direction > 180.f&&*a - *yaw - T44[eBODY].direction < 360.f)
	{
		*yaw += 360.f;
		*yaw -= 0.4f;
		if (*yaw <= *a - T44[eBODY].direction) *yaw = *a - T44[eBODY].direction;
	}
	else if (*a - *yaw - T44[eBODY].direction < 0.f&&*a - *yaw - T44[eBODY].direction >= -180.f)
	{
		*yaw -= 0.4f;
		if (*yaw <= *a - T44[eBODY].direction) *yaw = *a - T44[eBODY].direction;
	}
	else if (*a - *yaw - T44[eBODY].direction < -180.f&&*a - *yaw - T44[eBODY].direction > -360.f)
	{
		*yaw -= 360.f;
		*yaw += 0.4f;
		if (*yaw >= *a - T44[eBODY].direction) *yaw = *a - T44[eBODY].direction;
	}
}

void MoveGun(float *b,float *pitch)
{
	if (camera.m_curpt.y >= 527 + T44[eBODY].pitch*100.f)
	{
		if (*pitch - T44[eBODY].pitch >= *b&&*pitch - T44[eBODY].pitch >= -D3DXToRadian(28.f))
		{
			*pitch -= D3DXToRadian(0.2f);
			if (*pitch - T44[eBODY].pitch <= *b&&*b>= -D3DXToRadian(28.f))
			{
				*pitch = *b + T44[eBODY].pitch;
			}
			else if (*pitch - T44[eBODY].pitch <= *b&&*b  <= -D3DXToRadian(28.f))
			{
				*pitch = -D3DXToRadian(28.f) + T44[eBODY].pitch;
			}
		}
		else if (*pitch - T44[eBODY].pitch < *b)
		{
			*pitch += D3DXToRadian(0.2f);
			if (*pitch - T44[eBODY].pitch >= *b)
			{
				*pitch = *b + T44[eBODY].pitch;
			}
		}
	}
	else if (camera.m_curpt.y < 527 + T44[eBODY].pitch*100.f)
	{
		if (*pitch - T44[eBODY].pitch <= *b&&*pitch - T44[eBODY].pitch <= D3DXToRadian(5.f))
		{
			*pitch += D3DXToRadian(0.2f);
			if (*pitch - T44[eBODY].pitch >= *b&&*b <= D3DXToRadian(5.f))
			{
				*pitch = *b + T44[eBODY].pitch;
			}
			else if (*pitch - T44[eBODY].pitch >= *b&&*b >= D3DXToRadian(5.f))
			{
				*pitch = D3DXToRadian(5.f) + T44[eBODY].pitch;
			}
		}
		else if (*pitch - T44[eBODY].pitch> *b)
		{
			*pitch -= D3DXToRadian(0.2f);
			if (*pitch - T44[eBODY].pitch <= *b)
			{
				*pitch = *b + T44[eBODY].pitch;
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////
//  Open������
/////////////////////////////////////////////////////////////////////////
HRESULT InitOpen(void)
{
	char fNameOpen[] = "BMP\\title.bmp";
	//Open�̊�{����
	func = DoOpen;
	startTime = timeGetTime();
	//�ȉ��AOpen�̏������L�q
	if (FAILED(LoadTexture(fNameOpen, &lpTitle))) return E_FAIL;
	//�ȏ�AOpen�̏������L�q
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Open�����s
/////////////////////////////////////////////////////////////////////////
HRESULT DoOpen(void)
{
	DrawOpen();
	if (timeGetTime() - startTime > 1000)
	{
		if (key&kKEYENTER)
		{
			func = DisposeOpen;
		}
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  �`��i�I�[�v�j���O�j
/////////////////////////////////////////////////////////////////////////
void DrawOpen(void)
{
	lpD3DDev->BeginScene();
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//�ȉ��`�揈��
	D3DXMATRIX mat;
	D3DXMatrixScaling(&mat, 1920.0f / 2048.0f, 1080.0f / 1024.0f, 1.0f);
	lpSprite->SetTransform(&mat);
	lpSprite->Draw(lpTitle, NULL, NULL, NULL, 0xFFFFFFFF);
	////�ȉ��X�e�[�W���\��

	//�`�揈���I��
	lpSprite->End();
	lpD3DDev->EndScene();
	lpD3DDev->Present(NULL, NULL, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////
//  Open����n��
/////////////////////////////////////////////////////////////////////////
HRESULT DisposeOpen(void)
{
	ReleaseTexture(&lpTitle);
	func = InitInGame;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  �X�e�[�W����`��
/////////////////////////////////////////////////////////////////////////
void DrawStageName(LPCTSTR pString,RECT rect)
{
#ifdef	kUSEDXFONT
	D3DXMATRIX		nameMat;
	D3DXMatrixScaling(&nameMat, 1.0f, 1.0f, 1.0f);
	lpSprite->SetTransform(&nameMat);
	lpFont->DrawText(
		lpSprite,			//LPD3DXSPRITE pSprite,
		pString,			//LPCTSTR pString,
		-1,					//INT Count,
		NULL,				//LPRECT pRect,
		DT_LEFT,			//DWORD Format,
		0xff000000			//D3DCOLOR Color
		);
#endif
}

/////////////////////////////////////////////////////////////////////////
//  MyData�̏�����
/////////////////////////////////////////////////////////////////////////
void InitMyData(void)
{
	//��
	DoNULLClearDXEnv();
	//DirectX�X�P���g���f�[�^
	func = InitOpen;
	startTime = timeGetTime();
	//�ȉ��A�ǉ�����f�[�^��NULL�N���A
	lpTitle = NULL;
	//InGame
	for (int i = 0; i < eTANKNUM; ++i) DoNullClear(&T44[i].mesh);
	DoNullClear(&myLand.mesh);
}

/////////////////////////////////////////////////////////////////////////
//  MyData�̐ݒ�
/////////////////////////////////////////////////////////////////////////
HRESULT SetupMyData(HWND hWnd)
{
	//��
	if (FAILED(CreateDXEnv(hWnd))) return E_FAIL;
	//�ȉ��ɒǉ��f�[�^�i�S�̂Ŏg���f�[�^�j�̒l��ݒ肷�鏈�����L�q����

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  �I�u�W�F�N�g�S�̂̃����[�X
/////////////////////////////////////////////////////////////////////////
void ReleaseAll(void)
{
	//�ȉ��Ƀ��[�h�f�[�^�̃����[�X��ǉ�
	ReleaseTexture(&lpTitle);
	for (int i = 0; i < eTANKNUM; ++i) ReleaseXMesh(&T44[i].mesh);
	ReleaseXMesh(&myLand.mesh);
	//�ȏ�Ƀ��[�h�f�[�^�̃����[�X��ǉ�
	//DirectX���̃����[�X
	ReleaseDXEnv();
}

/////////////////////////////////////////////////////////////////////////
//  �L�[���͂̃`�F�b�N
/////////////////////////////////////////////////////////////////////////
HRESULT CheckKey(void)
{
	//�L�[�t���O�̃N���A
	key=0;
	//�ȉ��A�L�[���͂̃`�F�b�N�ƃL�[�t���O�̃Z�b�g
	//ESC�L�[�ŏI����
	if(HIBYTE(GetKeyState(VK_ESCAPE)))	return E_FAIL;
	//F2�L�[�ŃX�e�[�W�ڍs��
	if(HIBYTE(GetKeyState(VK_RETURN)))			key|=kKEYENTER;
	//���L�[
	if(HIBYTE(GetKeyState('W')))				key|=kKEYW;
	if(HIBYTE(GetKeyState('S')))				key|=kKEYS;				
	if(HIBYTE(GetKeyState('A')))				key|=kKEYA;				
	if(HIBYTE(GetKeyState('D')))				key|=kKEYD;	

	if(HIBYTE(GetKeyState('E')))				key|=kKEYE;		


#ifdef	kUSEDINPUT
	//�ȉ��A�Q�[���p�b�h�ɂ����͂̃`�F�b�N�ƃL�[�t���O�̃Z�b�g
	HRESULT		hr;
	DIJOYSTATE	dijs;
	//���͏�Ԃ̎擾
	if(FAILED(lpDIDev[eIDEV0]->Poll())){
		hr=lpDIDev[eIDEV0]->Acquire();
		while(hr==DIERR_INPUTLOST)
			hr=lpDIDev[eIDEV0]->Acquire();
		return S_OK;
	}
	if(FAILED(lpDIDev[eIDEV0]->GetDeviceState(sizeof(DIJOYSTATE),&dijs)))
		return S_OK;
	//�ȉ��A�{�^���̃`�F�b�N
	//�I����
	if(dijs.rgbButtons[nBtn[eIDEV0]-2] & 0x80)	//8
		return E_FAIL;
	//�X�e�[�W�ڍs
	if(dijs.rgbButtons[nBtn[eIDEV0]-1] & 0x80)	//9
		key|=kKEYF2;
/*
	//A�{�^��
	if(dijs.rgbButtons[0] & 0x80)		key|=kKEYSPACE;
	//B�{�^��
	if(dijs.rgbButtons[1] & 0x80)		key|=kKEYD;
	//Y�{�^��
	if(dijs.rgbButtons[4] & 0x80)		key|=kKEYU;
	//��
	if(dijs.lX>900)						key|=kKEYRIGHT;
	if(dijs.lX<-900)					key|=kKEYLEFT;
	if(dijs.lY>900)						key|=kKEYDOWN;
	if(dijs.lY<-900)					key|=kKEYUP;
*/
#endif

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  �Q�[�����[�v
/////////////////////////////////////////////////////////////////////////
HRESULT GameLoop(HWND hWnd)
{
	static DWORD	loopTime = timeGetTime();
	if ((timeGetTime() - loopTime) > 10)
	{
		if (FAILED(CheckKey()))	return E_FAIL;
		if (FAILED((*func)()))	return E_FAIL;
		loopTime = timeGetTime();
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  �E�B���h�E�v���V�[�W��
/////////////////////////////////////////////////////////////////////////
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT			ps;
	static MMRESULT		mmRes;
	//���b�Z�[�W�̔���
	switch (msg)
	{
	case WM_CREATE:
		mmRes = timeBeginPeriod(1);
		break;
	case WM_PAINT://�ĕ`��v��
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY://�E�B���h�E�̏I������
		mmRes = timeEndPeriod(mmRes);
		PostQuitMessage(0);
		break;
	case WM_RBUTTONDOWN:
		if (camera.m_Rbtn == false) 	camera.m_pos = camera.m_lookat;
		else if (camera.m_Rbtn)			camera.m_lookat = camera.m_pos;
		camera.m_Rbtn = !camera.m_Rbtn;
		break;
	case WM_KEYDOWN:
	{
					   switch (wParam)
					   {
					   case 'e':
					   case 'E':
					   {
								   camera.key_E = !camera.key_E;
					   }
						   break;
					   }
	}
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0L;
}

/////////////////////////////////////////////////////////////////////////
//  ���C��
/////////////////////////////////////////////////////////////////////////
INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,	LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASSEX		wc;
	HWND			hWnd;
	MSG				msg;

	//�E�B���h�E�̌`��
	wc.hInstance		=hInstance;
	wc.lpszClassName	="DirectXAPP";
	wc.lpfnWndProc		=WndProc;
	wc.style			=CS_CLASSDC;
	wc.cbSize			=sizeof(WNDCLASSEX);
	wc.lpszMenuName		=NULL;
	wc.hIcon			=NULL;
	wc.hIconSm			=NULL;
	wc.hCursor			=LoadCursor(NULL,IDC_ARROW);
	wc.cbClsExtra		=0L;
	wc.cbWndExtra		=0L;
	wc.hbrBackground	=(HBRUSH)GetStockObject(WHITE_BRUSH);
	//�E�B���h�E�̓o�^
	RegisterClassEx(&wc);
	//�E�B���h�E�̐���
	hWnd=CreateWindowEx(WS_EX_APPWINDOW,"DirectXAPP","Tank",WS_POPUP,0,0,1920,1080,
					NULL,NULL,hInstance,NULL);
	//�E�B���h�E�̕\��
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	//MyData�̏�����
	InitMyData();
	//MyData�̃Z�b�g�A�b�v
	if (FAILED(SetupMyData(hWnd)))
	{
		ReleaseAll();
		return 0;
	}
	//���b�Z�[�W���[�v
	ZeroMemory(&msg,sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//�E�B���h�E���b�Z�[�W�̏���
		if (PeekMessage(&msg, NULL, 0L, 0L, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//�Q�[�����[�v
			if (FAILED(GameLoop(hWnd)))
			{
				DestroyWindow(hWnd);
			}
		}
	}
	ReleaseAll();
	return 0;
}
