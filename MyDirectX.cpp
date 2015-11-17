/////////////////////////////////////////////////////////////////////////
// MyDirectX.cpp 
//  DirectX関連
//	Copyright(c) 2004 Hiroshi Ikuyama. All rights reserved.
/////////////////////////////////////////////////////////////////////////

#include "myDX.h"
#include <TCHAR.h>

LPDIRECT3D9				lpD3D;							//Direct3Dオブジェクト
LPDIRECT3DDEVICE9		lpD3DDev;						//Direct3DDeviceオブジェクト
LPD3DXSPRITE			lpSprite;						//スプライトオブジェクト
#ifdef	kUSEDXFONT
LPD3DXFONT				lpFont;							//フォントオブジェクト
#endif
#ifdef	kUSEDINPUT
//インプット用
LPDIRECTINPUT8			lpDInput;
LPDIRECTINPUTDEVICE8	lpDIDev[eIDEVNUM];
int						cntIDev;
int						nBtn[eIDEVNUM];
#endif
//音関係
#ifdef	kUSEDMUSIC
IDirectMusicPerformance8	*pPerformance;
#ifdef kUSEAUDIOPATH
IDirectMusicAudioPath8	*pAudioPath[eAPNUM];
#else
IDirectMusicAudioPath8	*pAudioPath;
#endif
IDirectMusicLoader8		*pLoader;
#endif


/////////////////////////////////////////////////////////////////////////
//  DirectX環境の生成
/////////////////////////////////////////////////////////////////////////
HRESULT CreateDXEnv(HWND hWnd)
{
	if(FAILED(CreateD3D(hWnd)))
		return E_FAIL;
#ifdef kFULLSCREEN
	if(FAILED(CreateD3DDevFull(hWnd)))
#else
	if(FAILED(CreateD3DDevWin(hWnd)))
#endif
		return E_FAIL;
	if(FAILED(CreateSprite()))
		return E_FAIL;
#ifdef kUSEDXFONT
	if(FAILED(CreateFont()))
		return E_FAIL;
#endif
#ifdef kUSEDINPUT
	if(FAILED(CreateDInput(hWnd)))
		return E_FAIL;
	if(FAILED(CreateDIDev(hWnd)))
		return E_FAIL;
	if(FAILED(SetupDI(hWnd)))
		return E_FAIL;
#endif
#ifdef kUSEDMUSIC
	if(FAILED(CreateDMusic(hWnd)))
		return E_FAIL;
#endif
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  DirectX環境オブジェクトのリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseDXEnv(void)
{
	//Env.
#ifdef kUSEDMUSIC
	ReleaseDMusic();
#endif
#ifdef kUSEDINPUT
	ReleaseDI();
#endif
#ifdef kUSEDXFONT
	ReleaseFont();
#endif
	ReleaseSprite();
	ReleaseD3D();
}

/////////////////////////////////////////////////////////////////////////
//  DX環境のNULLクリアー
/////////////////////////////////////////////////////////////////////////
void DoNULLClearDXEnv(void)
{
	lpD3D								=NULL;
	lpD3DDev							=NULL;
	lpSprite							=NULL;
#ifdef kUSEDXFONT
	lpFont								=NULL;
#endif
#ifdef	kUSEDINPUT
	lpDInput							=NULL;
	for(int cntDIDev=0;cntDIDev<1;cntDIDev++){
		lpDIDev[cntDIDev]				=NULL;
	}
	cntIDev								=0;
#endif
#ifdef kUSEDMUSIC
	pPerformance						=NULL;
#ifdef kUSEAUDIOPATH
	for(int i=0;i<eAPNUM;i++){
		pAudioPath[i]					=NULL;
	}
#else
	pAudioPath							=NULL;
#endif
	pLoader								=NULL;
#endif
}

/////////////////////////////////////////////////////////////////////////
//  Direct3Dの生成
/////////////////////////////////////////////////////////////////////////
HRESULT CreateD3D(HWND hWnd)
{
	if(((lpD3D)=Direct3DCreate9(D3D_SDK_VERSION))==NULL)	return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Direct3Dデバイスの生成(Windowモード)
/////////////////////////////////////////////////////////////////////////
HRESULT CreateD3DDevWin(HWND hWnd)
{
	D3DDISPLAYMODE			dispMode;
	D3DPRESENT_PARAMETERS	presentParam;

	lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&dispMode);
	ZeroMemory(&presentParam,sizeof(presentParam));
	presentParam.Windowed=TRUE;
	presentParam.BackBufferFormat = dispMode.Format;
	presentParam.BackBufferCount=1;
	presentParam.SwapEffect=D3DSWAPEFFECT_DISCARD;
	presentParam.EnableAutoDepthStencil=TRUE;
	presentParam.AutoDepthStencilFormat=D3DFMT_D16;
//	if(FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT/*,D3DDEVTYPE_HAL*/,D3DDEVTYPE_REF,
	if(FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,
			hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&presentParam,&lpD3DDev)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Direct3Dデバイスの生成(FullScreenモード)
/////////////////////////////////////////////////////////////////////////
HRESULT CreateD3DDevFull(HWND hWnd)
{
	D3DDISPLAYMODE			dispMode;
	D3DPRESENT_PARAMETERS	presentParam;

	lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&dispMode);
	ZeroMemory(&presentParam,sizeof(presentParam));
	presentParam.Windowed=FALSE;
	presentParam.BackBufferWidth=1920;
	presentParam.BackBufferHeight=1080;
	presentParam.BackBufferFormat=dispMode.Format;
	presentParam.BackBufferCount=1;
	presentParam.SwapEffect=D3DSWAPEFFECT_DISCARD;
	presentParam.FullScreen_RefreshRateInHz=D3DPRESENT_RATE_DEFAULT;
	presentParam.EnableAutoDepthStencil=TRUE;
	presentParam.AutoDepthStencilFormat=D3DFMT_D16;
//	if(FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT,/*D3DDEVTYPE_HAL,*/D3DDEVTYPE_REF,
	if(FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,
		hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&presentParam,&lpD3DDev)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Direct3D関連のリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseD3D(void)
{
	if(lpD3DDev!=NULL){
		lpD3DDev->Release();
		lpD3DDev=NULL;
	}
	if(lpD3D!=NULL){
		lpD3D->Release();
		lpD3D=NULL;
	}
}

/////////////////////////////////////////////////////////////////////////
//  3DMeshの描画
/////////////////////////////////////////////////////////////////////////
void Draw3DMesh(
	DWORD matCount,D3DMATERIAL9 *pMat,LPDIRECT3DTEXTURE9 *pTex,LPD3DXMESH lpMesh)
{
	for(DWORD cnt=0;cnt<matCount;cnt++){
		lpD3DDev->SetMaterial(&pMat[cnt]);
		if(pTex!=NULL)	lpD3DDev->SetTexture(0,pTex[cnt]);
		else			lpD3DDev->SetTexture(0,NULL);
		lpMesh->DrawSubset(cnt);
	}
}

/////////////////////////////////////////////////////////////////////////
//  MyMeshの描画
/////////////////////////////////////////////////////////////////////////
void DrawMyMesh(MyMesh *pMyMesh)
{
	for(DWORD cnt=0;cnt<pMyMesh->matCount;cnt++){
		if(pMyMesh->pMat!=NULL)	lpD3DDev->SetMaterial(&pMyMesh->pMat[cnt]);
//		else			lpD3DDev->SetMaterial(NULL);
		if(pMyMesh->pTex!=NULL)	lpD3DDev->SetTexture(0,pMyMesh->pTex[cnt]);
		else			lpD3DDev->SetTexture(0,NULL);
		pMyMesh->lpMesh->DrawSubset(cnt);
	}
}

/////////////////////////////////////////////////////////////////////////
//  3DModelの描画
/////////////////////////////////////////////////////////////////////////
void DrawModel(MyMesh *pMyMesh,
	float scaleX,	float scaleY,	float scaleZ,
	float yaw,		float pitch,	float roll,
	D3DXVECTOR3 pos)
{
	D3DXMATRIX		matScale,matRot,matPos,mat;

	D3DXMatrixScaling(&matScale,scaleX,scaleY,scaleZ);
	D3DXMatrixRotationYawPitchRoll(&matRot,yaw,pitch,roll);
	D3DXMatrixTranslation(&matPos,pos.x,pos.y,pos.z);
	D3DXMatrixMultiply(&mat,&matScale,&matRot);
	D3DXMatrixMultiply(&mat,&mat,&matPos);
	lpD3DDev->SetTransform(D3DTS_WORLD,&mat);
	DrawMyMesh(pMyMesh);
}

/////////////////////////////////////////////////////////////////////////
//  MyMesh型のNULLクリア
/////////////////////////////////////////////////////////////////////////
void DoNullClear(MyMesh *pMyMesh)
{
	pMyMesh->lpMesh				=NULL;
	pMyMesh->matCount			=0;
	pMyMesh->pMat				=NULL;
	pMyMesh->pTex				=NULL;
}
//以上Direct3D関連関数定義

//以下Sprite関連関数定義
/////////////////////////////////////////////////////////////////////////
//  Spriteの生成
/////////////////////////////////////////////////////////////////////////
HRESULT CreateSprite(void)
{
	if(FAILED(D3DXCreateSprite(lpD3DDev,&lpSprite)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Spriteのリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseSprite(void)
{
	if(lpSprite!=NULL){
		lpSprite->Release();
		lpSprite=NULL;
	}
}
//以上Sprite関連関数定義

/////////////////////////////////////////////////////////////////////////
//  Fontの生成
/////////////////////////////////////////////////////////////////////////
#ifdef	kUSEDXFONT
HRESULT CreateFont(void)
{
	if(FAILED(D3DXCreateFont(
		lpD3DDev,						//LPDIRECT3DDEVICE9	lpD3DDev,
		32,								//UINT				Height,
		0,								//UINT				Width,
		FW_NORMAL,						//UINT				Weight,
		D3DX_DEFAULT,					//UINT				MipLevels,
		FALSE,							//BOOL				Italic,
		SHIFTJIS_CHARSET,				//DWORD				CharSet,
		OUT_DEFAULT_PRECIS,				//DWORD				OutputPrecision,
		PROOF_QUALITY,					//DWORD				Quality,
		DEFAULT_PITCH | FF_DONTCARE,	//DWORD				PitchAndFamily,
		"ＭＳ ゴシック",					//LPCTSTR			pFacename,
		&lpFont							//LPD3DXFONT		*ppFont
	))){
		return E_FAIL;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Fontのリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseFont(void)
{
	if(lpFont!=NULL){
		lpFont->Release();
		lpFont=NULL;
	}
}
#endif

/////////////////////////////////////////////////////////////////////////
//  抜け色を指定したTextureのロード
/////////////////////////////////////////////////////////////////////////
HRESULT LoadTextureEx(LPCTSTR fName,LPDIRECT3DTEXTURE9 *pTex)
{
	if(FAILED(D3DXCreateTextureFromFileEx(
		lpD3DDev,				//LPDIRECT3DDEVICE9		pDevice,
		fName,					//LPCTSTR				pSrcFile,
		D3DX_DEFAULT,			//UINT					Width,
		D3DX_DEFAULT,			//UINT					Height,
		D3DX_DEFAULT,			//UINT					MipLevels,
		0,						//DWORD					Usage,
		D3DFMT_UNKNOWN,			//D3DFORMAT				Format,
		D3DPOOL_MANAGED,		//D3DPOOL				Pool,
		D3DX_DEFAULT,			//DWORD					Filter,
		D3DX_DEFAULT,			//DWORD					MipFilter,
//		0xFF000000,				//D3DCOLOR				ColorKey,	//抜け色を黒に設定
		0xFF00FF00,				//D3DCOLOR				ColorKey,	//抜け色を緑に設定
		NULL,					//D3DXIMAGE_INFO		*pSrcInfo,
		NULL,					//PALETTEENTRY			*pPalette,
		pTex					//LPDIRECT3DTEXTURE9	*ppTexture
		)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Textureのロード
/////////////////////////////////////////////////////////////////////////
HRESULT LoadTexture(LPCTSTR fName,LPDIRECT3DTEXTURE9 *pTex)
{
	if(FAILED(D3DXCreateTextureFromFile(lpD3DDev,fName,pTex)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Textureのリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseTexture(LPDIRECT3DTEXTURE9 *pTex)
{
	if(*pTex!=NULL){
		(*pTex)->Release();
		*pTex=NULL;
	}
}

/////////////////////////////////////////////////////////////////////////
//  Textureの描画
/////////////////////////////////////////////////////////////////////////
void DrawTexture(LPDIRECT3DTEXTURE9 lpTexture,
		int xPos,int yPos,
		float wScale,float hScale,
		RECT *pRect,
		float rotation,
		int offsetX,int offsetY,int offsetZ,
		DWORD color)
{
	D3DXMATRIX		mat,matID,matPos,matRot,matScale;

	//単位行列の作成
	D3DXMatrixIdentity(&matID);
	//位置行列の作成
	D3DXMatrixTranslation(&matPos,(float)xPos,(float)yPos,0.0f);
	//回転行列の作成
	D3DXMatrixRotationZ(&matRot,-rotation);
	//拡大縮小行列の作成
	D3DXMatrixScaling(&matScale,wScale,hScale,1.0f);
	//行列の合成
	D3DXMatrixMultiply(&mat,&matID,&matScale);
	D3DXMatrixMultiply(&mat,&mat,&matRot);
	D3DXMatrixMultiply(&mat,&mat,&matPos);
	//スプライトエンジンに行列を登録
	lpSprite->SetTransform(&mat);
	//描画
	lpSprite->Draw(lpTexture, pRect, &D3DXVECTOR3((float)offsetX, (float)offsetY, (float)offsetZ), NULL, color);
}

/////////////////////////////////////////////////////////////////////////
//  XFileのロード
/////////////////////////////////////////////////////////////////////////
//HRESULT LoadXFile(LPDIRECT3DDEVICE9 lpD3DDev,char *xfileName,MyMesh *pMyMesh,char path[])
HRESULT LoadXFile(char *xfileName,MyMesh *pMyMesh,char path[])
{
	LPD3DXBUFFER		lpD3DBuffer;
	D3DXMATERIAL		*d3dxMat;
	DWORD				i;
	char				str[256]="";
	_TCHAR				wstr[256]=_T("");

	strcat_s(str,path);
	strcat_s(str,xfileName);
	if(FAILED(D3DXLoadMeshFromX(str,D3DXMESH_SYSTEMMEM,lpD3DDev,
			NULL,&lpD3DBuffer,NULL,&pMyMesh->matCount,&pMyMesh->lpMesh))){
		return E_FAIL;
	}
	d3dxMat=(D3DXMATERIAL*)lpD3DBuffer->GetBufferPointer();
	pMyMesh->pMat=new D3DMATERIAL9[pMyMesh->matCount];
	pMyMesh->pTex=new LPDIRECT3DTEXTURE9[pMyMesh->matCount];
	for(i=0;i<pMyMesh->matCount;i++){
		pMyMesh->pMat[i]=d3dxMat[i].MatD3D;
		lstrcpy(wstr,_T(path));
		lstrcat(wstr,d3dxMat[i].pTextureFilename);
		if(FAILED(D3DXCreateTextureFromFile(lpD3DDev,wstr,&pMyMesh->pTex[i]))){
			pMyMesh->pTex[i]=NULL;
		}
	}
	lpD3DBuffer->Release();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  メッシュデータのリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseXMesh(MyMesh *pMyMesh)
{
	if(pMyMesh->pTex!=NULL){
		for(DWORD i=0;i<pMyMesh->matCount;i++){
			if(pMyMesh->pTex[i]!=NULL){
				pMyMesh->pTex[i]->Release();
				pMyMesh->pTex[i]=NULL;
			}
		}
		delete[] pMyMesh->pTex;
		pMyMesh->pTex=NULL;
	}
	if(pMyMesh->pMat!=NULL){
		delete[] pMyMesh->pMat;
		pMyMesh->pMat=NULL;
	}
	if(pMyMesh->lpMesh!=NULL){
		pMyMesh->lpMesh->Release();
		pMyMesh->lpMesh=NULL;
	}
}

/////////////////////////////////////////////////////////////////////////
//  ディレクショナルライトの設定
//	color[0] ===> Diffuse
//	color[1] ===> Specular
//	color[2] ===> Ambient
/////////////////////////////////////////////////////////////////////////
void SetupDirectionalLight(D3DCOLORVALUE color[],D3DXVECTOR3 vec,DWORD num)
{
	D3DLIGHT9		light;

	ZeroMemory(&light,sizeof(light));
	light.Type=D3DLIGHT_DIRECTIONAL;
	light.Diffuse=	color[0];
	light.Specular=	color[1];
	light.Ambient=	color[2];
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vec);
	lpD3DDev->SetLight(num,&light);
	lpD3DDev->LightEnable(num,TRUE);
}

/////////////////////////////////////////////////////////////////////////
//	スポットライトの設定
//	D3DCOLORVALUE		color[3];
//		color[0]	===> Diffuse
//		color[1]	===> Specular
//		color[2]	===> Ambient
//	D3DXVECTOR3			vec[2];
//		vec[0]		===> Direction
//		vec[1]		===> Position
//	float				val[7];
//		val[0]		===> Range
//		val[1]		===> Falloff
//		val[2]		===> Attenuation0
//		val[3]		===> Attenuation1
//		val[4]		===> Attenuation2
//		val[5]		===> Theta
//		val[6]		===> Phi
/////////////////////////////////////////////////////////////////////////
void SetupSpotLight(D3DCOLORVALUE color[],D3DXVECTOR3 vec[],float val[],DWORD num)
{
	D3DLIGHT9		light;

	ZeroMemory(&light,sizeof(light));
	light.Type=D3DLIGHT_SPOT;
	light.Diffuse		=color[0];
	light.Specular		=color[1];
	light.Ambient		=color[2];
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vec[0]);
	light.Position		=vec[1];
	light.Range			=val[0];
	light.Falloff		=val[1];
	light.Attenuation0	=val[2];
	light.Attenuation1	=val[3];
	light.Attenuation2	=val[4];
	light.Theta			=val[5];
	light.Phi			=val[6];
	lpD3DDev->SetLight(num,&light);
	lpD3DDev->LightEnable(num,TRUE);
}

/////////////////////////////////////////////////////////////////////////
//	ポイントライトの設定
//	D3DCOLORVALUE		color[3];
//		color[0]	===> Diffuse
//		color[1]	===> Specular
//		color[2]	===> Ambient
//	D3DXVECTOR3			vec;
//		vec			===> Position
//	float				val[4];
//		val[0]		===> Range
//		val[1]		===> Attenuation0
//		val[2]		===> Attenuation1
//		val[3]		===> Attenuation2
/////////////////////////////////////////////////////////////////////////
void SetupPointLight(D3DCOLORVALUE color[],D3DXVECTOR3 vec,float val[],DWORD num)
{
	D3DLIGHT9		light;

	ZeroMemory(&light,sizeof(light));
	light.Type=D3DLIGHT_POINT;
	light.Diffuse		=color[0];
	light.Specular		=color[1];
	light.Ambient		=color[2];
	light.Position		=vec;
	light.Range			=val[0];
	light.Attenuation0	=val[1];
	light.Attenuation1	=val[2];
	light.Attenuation2	=val[3];
	lpD3DDev->SetLight(num,&light);
	lpD3DDev->LightEnable(num,TRUE);
}

#ifdef	kUSEDINPUT
/////////////////////////////////////////////////////////////////////////
//  DirectInputの生成
/////////////////////////////////////////////////////////////////////////
HRESULT CreateDInput(HWND hWnd)
{
	if(FAILED(DirectInput8Create((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),
			DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&lpDInput,NULL))){
		return E_FAIL;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  DirectInputデバイスの生成
/////////////////////////////////////////////////////////////////////////
HRESULT CreateDIDev(HWND hWnd)
{
	if(FAILED(lpDInput->EnumDevices(DI8DEVCLASS_GAMECTRL,EnumJoyCallback,
			NULL,DIEDFL_ATTACHEDONLY))){
		return E_FAIL;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  DirectInputDeviceの列挙コールバック
/////////////////////////////////////////////////////////////////////////
BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* pdidInstance,VOID* pContext)
{
	DIDEVCAPS	diDevCaps;

	if(FAILED(lpDInput->CreateDevice(pdidInstance->guidInstance,
			&lpDIDev[cntIDev],NULL))){
		return DIENUM_CONTINUE;
	}
	diDevCaps.dwSize=sizeof(DIDEVCAPS);
	if(FAILED(lpDIDev[cntIDev]->GetCapabilities(&diDevCaps))){
		lpDIDev[cntIDev]->Release();
		lpDIDev[cntIDev]=NULL;
		return DIENUM_CONTINUE;
	}
	else{
		nBtn[cntIDev]=diDevCaps.dwButtons;
	}
	if(++cntIDev!=eIDEVNUM){
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}

/////////////////////////////////////////////////////////////////////////
//  DirectInput各種設定
/////////////////////////////////////////////////////////////////////////
HRESULT SetupDI(HWND hWnd)
{
	DIPROPDWORD		prop;
	int				i;

	for(i=0;i<eIDEVNUM;i++){
		if(lpDIDev[i]!=NULL){
			if(FAILED(lpDIDev[i]->SetDataFormat(&c_dfDIJoystick))){
				return E_FAIL;
			}
			if(FAILED(lpDIDev[i]->SetCooperativeLevel(hWnd,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))){
				return E_FAIL;
			}
			cntIDev=i;
			if(FAILED(lpDIDev[i]->EnumObjects(EnumAxisCallback,NULL,DIDFT_AXIS))){
				return E_FAIL;
			}
			prop.diph.dwSize		=sizeof(prop);
			prop.diph.dwHeaderSize	=sizeof(prop.diph);
			prop.diph.dwObj			=0;
			prop.diph.dwHow			=DIPH_DEVICE;
			prop.dwData				=DIPROPAXISMODE_ABS;
			if(FAILED(lpDIDev[i]->SetProperty(DIPROP_AXISMODE,&prop.diph))){
				return E_FAIL;
			}
			prop.dwData				=1000;
			if(FAILED(lpDIDev[i]->SetProperty(DIPROP_BUFFERSIZE,&prop.diph))){
				return E_FAIL;
			}
			lpDIDev[i]->Acquire();
		}
		else{
			return E_FAIL;
		}
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  JoyStickの軸を列挙するコールバック
/////////////////////////////////////////////////////////////////////////
BOOL CALLBACK EnumAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpInst,VOID *pRef)
{
	DIPROPRANGE		prg;

	ZeroMemory(&prg,sizeof(prg));
	prg.diph.dwSize=sizeof(prg);
	prg.diph.dwHeaderSize=sizeof(prg.diph);
	prg.diph.dwObj=lpInst->dwType;
	prg.diph.dwHow=DIPH_BYID;
	prg.lMin= -1000;
	prg.lMax= 1000;
	if(FAILED(lpDIDev[cntIDev]->SetProperty(DIPROP_RANGE,&prg.diph))){
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

/////////////////////////////////////////////////////////////////////////
//  DirectInput関連のリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseDI(void)
{
	for(int i=0;i<eIDEVNUM;i++){
		if(lpDIDev[i]!=NULL){
			lpDIDev[i]->Unacquire();
			lpDIDev[i]->Release();
			lpDIDev[i]=NULL;
		}
	}
	if(lpDInput!=NULL){
		lpDInput->Release();
		lpDInput=NULL;
	}
}
#endif

#ifdef kUSEDMUSIC
/////////////////////////////////////////////////////////////////////////
//  DirectMusicの生成
/////////////////////////////////////////////////////////////////////////
HRESULT CreateDMusic(HWND hWnd)
{
	//comの初期化
	if(FAILED(CoInitialize(NULL)))
		return E_FAIL;
	//パフォーマンスの生成
	if(FAILED(CoCreateInstance(CLSID_DirectMusicPerformance,NULL,
			CLSCTX_INPROC,IID_IDirectMusicPerformance8,
			(void**)&pPerformance)))
		return E_FAIL;
	//パフォーマンスの初期化
	if(FAILED(pPerformance->InitAudio(NULL,NULL,hWnd,
			DMUS_APATH_SHARED_STEREOPLUSREVERB,64,DMUS_AUDIOF_ALL,NULL)))
		return E_FAIL;
#ifdef kUSEAUDIOPATH	//オーディオパスの作成
	for(int i=0;i<eAPNUM;i++){
		if(FAILED(pPerformance->CreateStandardAudioPath(DMUS_APATH_DYNAMIC_STEREO,
				64,TRUE,&pAudioPath[i])))
			return E_FAIL;
	}
#else				//標準のオーディオパス
	if(FAILED(pPerformance->GetDefaultAudioPath(&pAudioPath)))
		return E_FAIL;
#endif
	//ローダーの作成
	if(FAILED(CoCreateInstance(CLSID_DirectMusicLoader,NULL,
			CLSCTX_INPROC,IID_IDirectMusicLoader8,(void**)&pLoader)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//	WAVEファイルからセグメントにロード
/////////////////////////////////////////////////////////////////////////
HRESULT LoadWaveFile(
	WCHAR						*fName,
	IDirectMusicSegment8		**ppSegment)
{
	if(FAILED(pLoader->LoadObjectFromFile(CLSID_DirectMusicSegment,
			IID_IDirectMusicSegment8,fName,(LPVOID*)ppSegment)))
		return E_FAIL;
	if(FAILED(SetupBand(ppSegment)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//	バンドのダウンロード
/////////////////////////////////////////////////////////////////////////
HRESULT SetupBand(
	IDirectMusicSegment8		**ppSegment)
{
	if(FAILED((*ppSegment)->Download(pPerformance)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//	WAVEリソースからセグメントにロード
/////////////////////////////////////////////////////////////////////////
HRESULT LoadWaveRes(DWORD resID,
	IDirectMusicSegment8 **ppSegment)
{
	HRSRC				hFound=FindResource(NULL,MAKEINTRESOURCE(resID),"WAVE");
	HGLOBAL				hRes=LoadResource(NULL,hFound);
	DMUS_OBJECTDESC		objDesc;

	objDesc.dwSize		=sizeof(DMUS_OBJECTDESC);
	objDesc.guidClass	=CLSID_DirectMusicSegment;
	objDesc.dwValidData	=DMUS_OBJ_CLASS | DMUS_OBJ_MEMORY;
	objDesc.pbMemData	=(BYTE*)LockResource(hRes);
	objDesc.llMemLength	=SizeofResource(NULL,hFound);
	if(FAILED(pLoader->GetObject(&objDesc,IID_IDirectMusicSegment8,
			(LPVOID*)ppSegment)))
		return E_FAIL;
	if(FAILED(SetupBand(ppSegment)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//	MIDIファイルからセグメントにロード
/////////////////////////////////////////////////////////////////////////
HRESULT LoadMIDIFile(WCHAR *fName,
	IDirectMusicSegment8 **ppSegment)
{
	if(FAILED(pLoader->LoadObjectFromFile(CLSID_DirectMusicSegment,
			IID_IDirectMusicSegment8,fName,(LPVOID*)ppSegment)))
		return E_FAIL;
	//スタンダードMIDIファイルをDirectMusic用に変換
	if(FAILED((*ppSegment)->SetParam(GUID_StandardMIDIFile,
			0xFFFFFFFF,0,0,NULL)))
		return E_FAIL;
	if(FAILED(SetupBand(ppSegment)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//	MIDIリソースからセグメントにロード
/////////////////////////////////////////////////////////////////////////
HRESULT LoadMIDIRes(DWORD resID,
	IDirectMusicSegment8 **ppSegment)
{
	HRSRC				hFound=FindResource(NULL,MAKEINTRESOURCE(resID),"WAVE");
	HGLOBAL				hRes=LoadResource(NULL,hFound);
	DMUS_OBJECTDESC		objDesc;

	objDesc.dwSize		=sizeof(DMUS_OBJECTDESC);
	objDesc.guidClass	=CLSID_DirectMusicSegment;
	objDesc.dwValidData	=DMUS_OBJ_CLASS | DMUS_OBJ_MEMORY;
	objDesc.pbMemData	=(BYTE*)LockResource(hRes);
	objDesc.llMemLength	=SizeofResource(NULL,hFound);
	if(FAILED(pLoader->GetObject(&objDesc,IID_IDirectMusicSegment8,
			(LPVOID*)ppSegment)))
		return E_FAIL;
	//スタンダードMIDIファイルをDirectMusic用に変換
	if(FAILED((*ppSegment)->SetParam(GUID_StandardMIDIFile,
			0xFFFFFFFF,0,0,NULL)))
		return E_FAIL;
	if(FAILED(SetupBand(ppSegment)))
		return E_FAIL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//	DirectXAudio関連のリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseDMusic(void)
{
	if(pPerformance!=NULL){
		pPerformance->Stop(NULL,NULL,0,0);
		Sleep(10);
		pPerformance->CloseDown();
	}
	if(pLoader!=NULL){
		pLoader->Release();
		pLoader=NULL;
	}
#ifdef kUSEAUDIOPATH
	for(int i=0;i<eAPNUM;i++){
		if(pAudioPath[i]!=NULL){
			pAudioPath[i]->Release();
			pAudioPath[i]=NULL;
		}
	}
#else
	if(pAudioPath!=NULL){
		pAudioPath->Release();
		pAudioPath=NULL;
	}
#endif
	if(pPerformance!=NULL){
		pPerformance->Release();
		pPerformance=NULL;
	}
	CoUninitialize();
}

/////////////////////////////////////////////////////////////////////////
//	セグメントのリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseSegment(IDirectMusicSegment8 **ppSegment)
{
	if(pPerformance!=NULL){
		pPerformance->StopEx(*ppSegment,0,0);
	}
	if(*ppSegment!=NULL){
		(*ppSegment)->Release();
		*ppSegment=NULL;
	}
}
#endif
