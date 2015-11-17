/////////////////////////////////////////////////////////////////////////
// myDX.h        ver 1.0 ( '03.04.14 Hiroshi Ikuyama )
//  myDX�֘A�̃v���g�^�C�v�t�@�C��
//	Copyright(c) 2003 Hiroshi Ikuyama. All rights reserved.
/////////////////////////////////////////////////////////////////////////
#pragma once
#define _CRT_SECURE_NO_DEPRECATE
/////////////////////////////////////////////////////////////////////////
//	�e��X�C�b�`
/////////////////////////////////////////////////////////////////////////
//�t���X�N���[�����[�h�ƃE�B���h�E���[�h�̃X�C�b�`
//#define kFULLSCREEN			//00-001
//DirectInput�̎g�p/�s�g�p
//#define		kUSEDINPUT
//DirectXFont�̎g�p/�s�g�p
#define	kUSEDXFONT
//DirectMusic�̎g�p/�s�g�p
//#define			kUSEDMUSIC
//�I�[�f�B�I�p�X�����̎g�p/�s�g�p
//#define	kUSEAUDIOPATH
//DirectInput�o�[�W����
#define		DIRECTINPUT_VERSION		0x0800

//�Q�[���p�b�h�������񋓃f�[�^
#ifdef	kUSEDINPUT
//�ȉ��̓Q�[���p�b�h���P�̂Ƃ�
enum {eIDEV0,eIDEVNUM};
//�Q�[���p�b�h��ǉ�����Ƃ��ȉ��̂悤��eIDEVNUM�̑O��eIDEV?��ǉ�����B
//enum {eIDEV0,eIDEV1,eIDEV2,eIDEVNUM};
#endif
//�I�[�f�B�I�p�X�p�񋓃f�[�^�F�ȉ��̓I�[�f�B�I�p�X�������̂Ƃ�
#ifdef kUSEAUDIOPATH
	enum {eBGM,eBOMB,eENGIN,eAPNUM};
#endif

#include <d3dx9.h>
#include <dinput.h>
//#include <dmusici.h>

//���b�V��(3DModel)�p�f�[�^�̒�`
typedef struct tagMyMesh{
	LPD3DXMESH					lpMesh;
	DWORD						matCount;
	D3DMATERIAL9				*pMat;
	LPDIRECT3DTEXTURE9			*pTex;
}MyMesh;
	

//DX���f�[�^�̊O���錾
//�`��p
extern LPDIRECT3D9				lpD3D;							//Direct3D�I�u�W�F�N�g
extern LPDIRECT3DDEVICE9		lpD3DDev;						//Direct3DDevice�I�u�W�F�N�g
extern LPD3DXSPRITE				lpSprite;						//�X�v���C�g�I�u�W�F�N�g
#ifdef	kUSEDXFONT
extern LPD3DXFONT				lpFont;							//�t�H���g�I�u�W�F�N�g
#endif
//�C���v�b�g�p
#ifdef	kUSEDINPUT
extern LPDIRECTINPUT8			lpDInput;
extern LPDIRECTINPUTDEVICE8		lpDIDev[eIDEVNUM];
extern int						cntIDev;
extern int						nBtn[eIDEVNUM];
#endif
//���֌W
#ifdef	kUSEDMUSIC
extern IDirectMusicPerformance8	*pPerformance;
#ifdef kUSEAUDIOPATH
extern IDirectMusicAudioPath8	*pAudioPath[eAPNUM];
#else
extern IDirectMusicAudioPath8	*pAudioPath;
#endif
extern IDirectMusicLoader8		*pLoader;
#endif

/////////////////////////////////////////////////////////////////////////
//	DirectX�������֐��̃v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
extern HRESULT CreateDXEnv(HWND hWnd);
extern void ReleaseDXEnv(void);
extern void DoNULLClearDXEnv(void);

/////////////////////////////////////////////////////////////////////////
//	Direct3D�֘A�v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
extern HRESULT CreateD3D(HWND hWnd);
extern HRESULT CreateD3DDevWin(HWND hWnd);
extern HRESULT CreateD3DDevFull(HWND hWnd);
extern void ReleaseD3D(void);
extern void Draw3DMesh(
	DWORD						matCount,
	D3DMATERIAL9				*pMat,
	LPDIRECT3DTEXTURE9			*pTex,
	LPD3DXMESH					lpMesh);
extern void DrawMyMesh(MyMesh *pMyMesh);
extern void DrawModel(
	MyMesh						*pMyMesh,
	float						scaleX,
	float						scaleY,
	float						scaleZ,
	float						yaw,
	float						pitch,
	float						roll,
	D3DXVECTOR3					pos);
extern void DoNullClear(MyMesh *pMyMesh);

/////////////////////////////////////////////////////////////////////////
//	Sprite�֘A�v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
extern HRESULT CreateSprite(void);
extern void ReleaseSprite(void);

/////////////////////////////////////////////////////////////////////////
//  Font�֘A�v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
extern HRESULT CreateFont(void);
extern void ReleaseFont(void);

/////////////////////////////////////////////////////////////////////////
//  Texture�֘A�v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
extern HRESULT LoadTexture(
	LPCTSTR						fName,
	LPDIRECT3DTEXTURE9			*pTex);
extern HRESULT LoadTextureEx(
	LPCTSTR						fName,
	LPDIRECT3DTEXTURE9			*pTex);
extern void ReleaseTexture(LPDIRECT3DTEXTURE9 *pTex);
extern void DrawTexture(LPDIRECT3DTEXTURE9 lpTexture,
	int xPos,int yPos,
	float wScale,float hScale,
	RECT *pRect,
	float rotation,
	int offsetX,int offsetY,int offsetZ,
	DWORD color);

/////////////////////////////////////////////////////////////////////////
//  XFile�֘A�v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
extern HRESULT LoadXFile(
//	LPDIRECT3DDEVICE9			lpD3DDev,
	char						*xfileName,
	MyMesh						*pMyMesh,
	char						path[]);
extern void ReleaseXMesh(MyMesh *pMyMesh);

/////////////////////////////////////////////////////////////////////////
//  Light�֘A�v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
extern void SetupDirectionalLight(
	D3DCOLORVALUE				color[],
	D3DXVECTOR3					vec,
	DWORD						num);
extern void SetupSpotLight(
	D3DCOLORVALUE				color[],
	D3DXVECTOR3					vec[],
	float						val[],
	DWORD						num);
extern void SetupPointLight(
	D3DCOLORVALUE				color[],
	D3DXVECTOR3					vec,
	float						val[],
	DWORD						num);

/////////////////////////////////////////////////////////////////////////
//  DirectInput�֘A�v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
#ifdef kUSEDINPUT
extern HRESULT CreateDInput(HWND hWnd);
extern HRESULT CreateDIDev(HWND hWnd);
extern BOOL CALLBACK EnumJoyCallback(
	const DIDEVICEINSTANCE*		pdidInstance,
	VOID*						pContext);
extern HRESULT SetupDI(
	HWND						hWnd);
extern BOOL CALLBACK EnumAxisCallback(
	LPCDIDEVICEOBJECTINSTANCE	lpInst,
	VOID*						pRef);
extern void ReleaseDI(void);
#endif

/////////////////////////////////////////////////////////////////////////
//  DirectMusic�֘A�v���g�^�C�v�錾
/////////////////////////////////////////////////////////////////////////
#ifdef kUSEDMUSIC
extern HRESULT CreateDMusic(HWND hWnd);
extern HRESULT LoadWaveFile(
	WCHAR						*fName,
	IDirectMusicSegment8		**ppSegment);
extern HRESULT LoadWaveRes(
	DWORD						resID,
	IDirectMusicSegment8		**ppSegment);
extern HRESULT SetupBand(
	IDirectMusicSegment8		**ppSegment);
extern HRESULT LoadMIDIFile(
	WCHAR						*fName,
	IDirectMusicSegment8		**ppSegment);
extern HRESULT LoadMIDIRes(
	DWORD						resID,
	IDirectMusicSegment8		**ppSegment);
extern void ReleaseDMusic(void);
extern void ReleaseSegment(IDirectMusicSegment8 **ppSegment);
#endif
