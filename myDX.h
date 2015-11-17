/////////////////////////////////////////////////////////////////////////
// myDX.h        ver 1.0 ( '03.04.14 Hiroshi Ikuyama )
//  myDX関連のプロトタイプファイル
//	Copyright(c) 2003 Hiroshi Ikuyama. All rights reserved.
/////////////////////////////////////////////////////////////////////////
#pragma once
#define _CRT_SECURE_NO_DEPRECATE
/////////////////////////////////////////////////////////////////////////
//	各種スイッチ
/////////////////////////////////////////////////////////////////////////
//フルスクリーンモードとウィンドウモードのスイッチ
//#define kFULLSCREEN			//00-001
//DirectInputの使用/不使用
//#define		kUSEDINPUT
//DirectXFontの使用/不使用
#define	kUSEDXFONT
//DirectMusicの使用/不使用
//#define			kUSEDMUSIC
//オーディオパス複数個の使用/不使用
//#define	kUSEAUDIOPATH
//DirectInputバージョン
#define		DIRECTINPUT_VERSION		0x0800

//ゲームパッドを示す列挙データ
#ifdef	kUSEDINPUT
//以下はゲームパッドが１つのとき
enum {eIDEV0,eIDEVNUM};
//ゲームパッドを追加するとき以下のようにeIDEVNUMの前にeIDEV?を追加する。
//enum {eIDEV0,eIDEV1,eIDEV2,eIDEVNUM};
#endif
//オーディオパス用列挙データ：以下はオーディオパスが複数個のとき
#ifdef kUSEAUDIOPATH
	enum {eBGM,eBOMB,eENGIN,eAPNUM};
#endif

#include <d3dx9.h>
#include <dinput.h>
//#include <dmusici.h>

//メッシュ(3DModel)用データの定義
typedef struct tagMyMesh{
	LPD3DXMESH					lpMesh;
	DWORD						matCount;
	D3DMATERIAL9				*pMat;
	LPDIRECT3DTEXTURE9			*pTex;
}MyMesh;
	

//DX環境データの外部宣言
//描画用
extern LPDIRECT3D9				lpD3D;							//Direct3Dオブジェクト
extern LPDIRECT3DDEVICE9		lpD3DDev;						//Direct3DDeviceオブジェクト
extern LPD3DXSPRITE				lpSprite;						//スプライトオブジェクト
#ifdef	kUSEDXFONT
extern LPD3DXFONT				lpFont;							//フォントオブジェクト
#endif
//インプット用
#ifdef	kUSEDINPUT
extern LPDIRECTINPUT8			lpDInput;
extern LPDIRECTINPUTDEVICE8		lpDIDev[eIDEVNUM];
extern int						cntIDev;
extern int						nBtn[eIDEVNUM];
#endif
//音関係
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
//	DirectX環境生成関数のプロトタイプ宣言
/////////////////////////////////////////////////////////////////////////
extern HRESULT CreateDXEnv(HWND hWnd);
extern void ReleaseDXEnv(void);
extern void DoNULLClearDXEnv(void);

/////////////////////////////////////////////////////////////////////////
//	Direct3D関連プロトタイプ宣言
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
//	Sprite関連プロトタイプ宣言
/////////////////////////////////////////////////////////////////////////
extern HRESULT CreateSprite(void);
extern void ReleaseSprite(void);

/////////////////////////////////////////////////////////////////////////
//  Font関連プロトタイプ宣言
/////////////////////////////////////////////////////////////////////////
extern HRESULT CreateFont(void);
extern void ReleaseFont(void);

/////////////////////////////////////////////////////////////////////////
//  Texture関連プロトタイプ宣言
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
//  XFile関連プロトタイプ宣言
/////////////////////////////////////////////////////////////////////////
extern HRESULT LoadXFile(
//	LPDIRECT3DDEVICE9			lpD3DDev,
	char						*xfileName,
	MyMesh						*pMyMesh,
	char						path[]);
extern void ReleaseXMesh(MyMesh *pMyMesh);

/////////////////////////////////////////////////////////////////////////
//  Light関連プロトタイプ宣言
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
//  DirectInput関連プロトタイプ宣言
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
//  DirectMusic関連プロトタイプ宣言
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
