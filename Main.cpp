/////////////////////////////////////////////////////////////////////////
//	ヘッダーファイル
/////////////////////////////////////////////////////////////////////////
#include "myDX.h"
#include "stdio.h"
#include "Title.h"
#include "Player.h"
#include "Camera.h"
#include "Land.h"
#include "Enemy.h"
#include "Shell.h"
#include "Obb.h"
#include "End.h"

#define kFULLSCREEN
/////////////////////////////////////////////////////////////////////////
//	列挙データ
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//	定数の定義
/////////////////////////////////////////////////////////////////////////
//キーフラグ用定数
#define		kKEYENTER		0x0001
#define		kKEYW			0x0002
#define		kKEYS			0x0004
#define		kKEYA			0x0008
#define		kKEYD			0x0010
#define		kKEYE			0x0020
#define     mLbtn           0x0040

/////////////////////////////////////////////////////////////////////////
//	ゲーム用データの構造体定義
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//	ゲーム用データ変数の宣言
/////////////////////////////////////////////////////////////////////////
//全体データの宣言
short key;
HRESULT	(*func)(void);

DWORD FrameCnt;
float TimeElapsed;
float fpTimeDelta;
float time;
float FPS;
//InGame
Tank T44[myTANKNUM];
Tank IS1[myTANKNUM];
Tank T54[myTANKNUM];
Tank IS3[myTANKNUM];
Tank PantherG[myTANKNUM];
Tank Tiger[myTANKNUM];
Tank PantherII[myTANKNUM];
Tank TigerII[myTANKNUM];
Tank M26[myTANKNUM];
Tank T32[myTANKNUM];
Tank M46[myTANKNUM];
Tank M103[myTANKNUM];

Land land1;
Land land2;
Land land3;
Land land4;
Land Point;
BOOL flag_point;
BOOL point_tank;
BOOL point_enemy;

Camera camera;

Enemy EmyT44[eTANKNUM];
Enemy EmyIS1[eTANKNUM];
Enemy EmyT54[eTANKNUM];
Enemy EmyIS3[eTANKNUM];
Enemy EmyPantherG[eTANKNUM];
Enemy EmyTiger[eTANKNUM];
Enemy EmyPantherII[eTANKNUM];
Enemy EmyTigerII[eTANKNUM];
Enemy EmyM26[eTANKNUM];
Enemy EmyT32[eTANKNUM];
Enemy EmyM46[eTANKNUM];
Enemy EmyM103[eTANKNUM];

Shell T44_shell;
Shell IS1_shell;
Shell T54_shell;
Shell IS3_shell;
Shell PantherG_shell;
Shell Tiger_shell;
Shell PantherII_shell;
Shell TigerII_shell;
Shell M26_shell;
Shell T32_shell;
Shell M46_shell;
Shell M103_shell;

Shell EmyT44_shell;
Shell EmyIS1_shell;
Shell EmyT54_shell;
Shell EmyIS3_shell;
Shell EmyPantherG_shell;
Shell EmyTiger_shell;
Shell EmyPantherII_shell;
Shell EmyTigerII_shell;
Shell EmyM26_shell;
Shell EmyT32_shell;
Shell EmyM46_shell;
Shell EmyM103_shell;

BOOL fire_OK;

OBB T44obb;
OBB IS1obb;
OBB T54obb;
OBB IS3obb;
OBB PantherGobb;
OBB Tigerobb;
OBB PantherIIobb;
OBB TigerIIobb;
OBB M26obb;
OBB T32obb;
OBB M46obb;
OBB M103obb;

OBB T44headobb;
OBB IS1headobb;
OBB T54headobb;
OBB IS3headobb;
OBB PantherGheadobb;
OBB Tigerheadobb;
OBB PantherIIheadobb;
OBB TigerIIheadobb;
OBB M26headobb;
OBB T32headobb;
OBB M46headobb;
OBB M103headobb;

OBB T44Emyobb;
OBB IS1Emyobb;
OBB T54Emyobb;
OBB IS3Emyobb;
OBB PantherGEmyobb;
OBB TigerEmyobb;
OBB PantherIIEmyobb;
OBB TigerIIEmyobb;
OBB M26Emyobb;
OBB T32Emyobb;
OBB M46Emyobb;
OBB M103Emyobb;

OBB T44Emyheadobb;
OBB IS1Emyheadobb;
OBB T54Emyheadobb;
OBB IS3Emyheadobb;
OBB PantherGEmyheadobb;
OBB TigerEmyheadobb;
OBB PantherIIEmyheadobb;
OBB TigerIIEmyheadobb;
OBB M26Emyheadobb;
OBB T32Emyheadobb;
OBB M46Emyheadobb;
OBB M103Emyheadobb;

OBB T44Shellobb;
OBB IS1Shellobb;
OBB T54Shellobb;
OBB IS3Shellobb;
OBB PantherGShellobb;
OBB TigerShellobb;
OBB PantherIIShellobb;
OBB TigerIIShellobb;
OBB M26Shellobb;
OBB T32Shellobb;
OBB M46Shellobb;
OBB M103Shellobb;

OBB T44EmyShellobb;
OBB IS1EmyShellobb;
OBB T54EmyShellobb;
OBB IS3EmyShellobb;
OBB PantherGEmyShellobb;
OBB TigerEmyShellobb;
OBB PantherIIEmyShellobb;
OBB TigerIIEmyShellobb;
OBB M26EmyShellobb;
OBB T32EmyShellobb;
OBB M46EmyShellobb;
OBB M103EmyShellobb;

LPDIRECT3DTEXTURE9 lpTitle;
LPDIRECT3DTEXTURE9 lpNewGame;
LPDIRECT3DTEXTURE9 lpResumeGame;
LPDIRECT3DTEXTURE9 lpQuit;
LPDIRECT3DTEXTURE9 lpisTank;
LPDIRECT3DTEXTURE9 lpMozdok;
LPDIRECT3DTEXTURE9 lpAllaman;
LPDIRECT3DTEXTURE9 lpKursk;
LPDIRECT3DTEXTURE9 lpArdennes;
LPDIRECT3DTEXTURE9 lpArrow;
LPDIRECT3DTEXTURE9 lpGermany;
LPDIRECT3DTEXTURE9 lpSoviet;
LPDIRECT3DTEXTURE9 lpAmerica;
LPDIRECT3DTEXTURE9 lpT44;
LPDIRECT3DTEXTURE9 lpT54;
LPDIRECT3DTEXTURE9 lpIS1;
LPDIRECT3DTEXTURE9 lpIS3;
LPDIRECT3DTEXTURE9 lpPantherG;
LPDIRECT3DTEXTURE9 lpPantherII;
LPDIRECT3DTEXTURE9 lpTiger;
LPDIRECT3DTEXTURE9 lpTigerII;
LPDIRECT3DTEXTURE9 lpM26;
LPDIRECT3DTEXTURE9 lpM46;
LPDIRECT3DTEXTURE9 lpT32;
LPDIRECT3DTEXTURE9 lpM103;
LPDIRECT3DTEXTURE9 lpT44data;
LPDIRECT3DTEXTURE9 lpT54data;
LPDIRECT3DTEXTURE9 lpIS1data;
LPDIRECT3DTEXTURE9 lpIS3data;
LPDIRECT3DTEXTURE9 lpPantherGdata;
LPDIRECT3DTEXTURE9 lpPantherIIdata;
LPDIRECT3DTEXTURE9 lpTigerdata;
LPDIRECT3DTEXTURE9 lpTigerIIdata;
LPDIRECT3DTEXTURE9 lpM26data;
LPDIRECT3DTEXTURE9 lpM46data;
LPDIRECT3DTEXTURE9 lpT32data;
LPDIRECT3DTEXTURE9 lpM103data;
LPDIRECT3DTEXTURE9 lpBack;
LPDIRECT3DTEXTURE9 lpStart;
LPDIRECT3DTEXTURE9 lpCenter;
LPDIRECT3DTEXTURE9 lpTarget;
LPDIRECT3DTEXTURE9 lpSight;
LPDIRECT3DTEXTURE9 lpSky;
LPDIRECT3DTEXTURE9 lpHp;
LPDIRECT3DTEXTURE9 lpHp0;
LPDIRECT3DTEXTURE9 lpShell;
LPDIRECT3DTEXTURE9 lpShell0;
LPDIRECT3DTEXTURE9 lpPoint;
LPDIRECT3DTEXTURE9 lpPoint0;

int num_stage;
int num_tank;
int num_country;
BOOL TitleStart;
BOOL isTank;
BOOL GameStart;
BOOL Mozdok;
BOOL Allaman;
BOOL Kursk;
BOOL Ardennes;

LPDIRECT3DTEXTURE9 lpEnd;
LPDIRECT3DTEXTURE9 lpOK;
LPDIRECT3DTEXTURE9 lpYouWin;
LPDIRECT3DTEXTURE9 lpYouLose;
LPDIRECT3DTEXTURE9 lpRankS;
LPDIRECT3DTEXTURE9 lpRankA;
LPDIRECT3DTEXTURE9 lpRankB;
LPDIRECT3DTEXTURE9 lpRankC;
LPDIRECT3DTEXTURE9 lpRankD;
LPDIRECT3DTEXTURE9 lpRankE;
BOOL EndStart;
BOOL ReStart;
BOOL flag_win;
BOOL flag_lose;
int count;
float game_time;
float point_tank_time;
float point_enemy_time;
BOOL tank_hpup;
BOOL tank_hpdown;
BOOL outofmap;
/////////////////////////////////////////////////////////////////////////
//	プロトタイプ宣言
/////////////////////////////////////////////////////////////////////////
//  Windowsプログラム（ゲームプログラム）における標準的なプロトタイプ宣言
LRESULT WINAPI WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
HRESULT GameLoop(HWND hWnd);
//  ゲームデータ関係のプロトタイプ宣言
HRESULT CheckKey(void);
void InitMyData(void);
HRESULT SetupMyData(HWND hWnd);
void ReleaseAll(void);
void DrawFPS(LPCTSTR pString, LPRECT rect);
void CalcFPS(float timeDelta);
int CalcHpBar(int *hp, int *hpmax);
float CalcShellBar(float *time, float cd);
BOOL ChechEnd(void);
float CalcPointBar(void);
//  オープニング関係のプロトタイプ宣言
HRESULT InitOpen(void);
HRESULT DoOpen(void);
    void DrawOpen(void);
HRESULT DisposeOpen(void);
//  インゲーム(3D)関係のプロトタイプ宣言
HRESULT InitInGame(void);
HRESULT SetupInGame(void);
HRESULT DoInGame(void);
    void MoveTank(Tank(&tank)[myTANKNUM], float speedmax, float pitchmax, float acc1, float acc2, float back, float turn);
	void MoveChild(Tank(&tank)[myTANKNUM]);
	void MoveChildEmy(Enemy(&enemy)[eTANKNUM]);
	void MoveHead(Tank(&tank)[myTANKNUM], float turn);
	void MoveHeadFar(Tank(&tank)[myTANKNUM], float turn);
	void MoveGun(Tank(&tank)[myTANKNUM], float pitchmax, float pitchmin);
	void MoveGunFar(Tank(&tank)[myTANKNUM], float pitchmax, float pitchmin);
	void CalcHitPoint(Tank(&tank)[myTANKNUM], Shell &shell, Land &land);
	void CheckHeight(Tank(&tank)[myTANKNUM], Land &land);
	void CheckEmyHeight(Enemy(&enemy)[eTANKNUM], Land &land);
	BOOL CheckIntersect(LPD3DXMESH lpMesh, D3DXVECTOR3 *rayPos, D3DXVECTOR3 *ray, float *pDist);
	void CheckLean(Tank(&tank)[myTANKNUM], Land &land);
	void CheckEmyLean(Enemy(&enemy)[eTANKNUM], Land &land);
	void MoveHeadEmy(Enemy(&enemy)[eTANKNUM], float turn);
	void MoveGunEmy(Enemy(&enemy)[eTANKNUM], float pitchmax, float pitchmin);
	void MoveShell(Shell &shell, Tank(&tank)[myTANKNUM], float speed, float cd);
	void MoveEmyShell(Shell &shell, Enemy(&enemy)[eTANKNUM], float speed, float cd);
	void CreateOBB(OBB *obb, Tank(&tank)[myTANKNUM]);
	void CreateHeadOBB(OBB *obb, Tank(&tank)[myTANKNUM]);
	void CreateEmyOBB(OBB *obb, Enemy(&enemy)[eTANKNUM]);
	void CreateEmyHeadOBB(OBB *obb, Enemy(&enemy)[eTANKNUM]);
	void CreateShellOBB(OBB *obb, Shell &shell, Tank(&tank)[myTANKNUM]);
	void CreateEmyShellOBB(OBB *obb, Shell &shell, Enemy(&enemy)[eTANKNUM]);
	BOOL TestOBBOBB(OBB *a, OBB *b);
	void CheckAttack(Tank(&tank)[myTANKNUM], Enemy(&enemy)[eTANKNUM], OBB *Myobb, OBB *Emyobb);
	void CheckAttack2(Tank(&tank)[myTANKNUM], Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], OBB *Myobb, OBB *Emyobb, OBB *Emyobb2);
	void CheckAttack3(Tank(&tank)[myTANKNUM], Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], 
		                          OBB *Myobb, OBB *Emyobb, OBB *Emyobb2, OBB *Emyobb3);
	void CheckAttack4(Tank(&tank)[myTANKNUM], Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], 
		                          Enemy(&enemy4)[eTANKNUM], OBB *Myobb, OBB *Emyobb, OBB *Emyobb2, OBB *Emyobb3, OBB *Emyobb4);
	void CheckAttackEmy(Enemy(&enemy1)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], OBB *Emyobb1, OBB *Emyobb2);
	void CheckAttackShell(Shell &shell, Enemy(&enemy)[eTANKNUM], OBB *MyShellobb, OBB *Emyobb, OBB *EmyHeadobb);
	void CheckAttackShell2(Shell &shell, Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], OBB *MyShellobb, OBB *Emyobb, 
		                   OBB *EmyHeadobb, OBB *Emyobb2, OBB *EmyHeadobb2);
	void CheckAttackShell3(Shell &shell, Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], 
		                   OBB *MyShellobb, OBB *Emyobb, OBB *EmyHeadobb, OBB *Emyobb2, OBB *EmyHeadobb2, OBB *Emyobb3, OBB *EmyHeadobb3);
	void CheckAttackShell4(Shell &shell, Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], 
		                   Enemy(&enemy4)[eTANKNUM], OBB *MyShellobb, OBB *Emyobb, OBB *EmyHeadobb, OBB *Emyobb2, OBB *EmyHeadobb2, 
						   OBB *Emyobb3, OBB *EmyHeadobb3, OBB *Emyobb4, OBB *EmyHeadobb4);
	void EmyDamage(Enemy(&enemy)[eTANKNUM], Tank(&tank)[myTANKNUM], float dmg10, float dmg2000);
	void CheckAttackEmyShell(Shell &shell, Tank(&tank)[myTANKNUM], OBB *EnemyShellobb, OBB *Myobb, OBB *MyHeadobb);
	void CheckAttackEmyShell2(Shell &shell, Shell &shell2, Tank(&tank)[myTANKNUM], OBB *EnemyShellobb,
		                      OBB *EnemyShellobb2, OBB *Myobb, OBB *MyHeadobb);
	void CheckAttackEmyShell3(Shell &shell, Shell &shell2, Shell &shell3, Tank(&tank)[myTANKNUM], OBB *EnemyShellobb, OBB *EnemyShellobb2, 
		                      OBB *EnemyShellobb3, OBB *Myobb, OBB *MyHeadobb);
	void CheckAttackEmyShell4(Shell &shell, Shell &shell2, Shell &shell3, Shell &shell4, Tank(&tank)[myTANKNUM],
		                      OBB *EnemyShellobb, OBB *EnemyShellobb2, OBB *EnemyShellobb3, OBB *EnemyShellobb4, OBB *Myobb, OBB *MyHeadobb);
	void Damage(Enemy(&enemy)[eTANKNUM], Tank(&tank)[myTANKNUM], float dmg10, float dmg2000);
	void Damage2(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Tank(&tank)[myTANKNUM], float emydmg10, float emydmg2000, float emydmg10_2, float emydmg2000_2);
	void Damage3(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Tank(&tank)[myTANKNUM], 
		         float emydmg10, float emydmg2000, float emydmg10_2, float emydmg2000_2, float emydmg10_3, float emydmg2000_3);
	void Damage4(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Enemy(&enemy4)[eTANKNUM],
		         Tank(&tank)[myTANKNUM], float emydmg10, float emydmg2000, float emydmg10_2, float emydmg2000_2,
		         float emydmg10_3, float emydmg2000_3, float emydmg10_4, float emydmg2000_4);
	void PointToTank(Tank(&tank)[myTANKNUM]);
	void HpUpDown(Tank(&tank)[myTANKNUM]);
	void CheckAttackEmyEmy2(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], OBB *Emyobb, OBB *Emyobb2);
	void CheckAttackEmyEmy3(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], OBB *Emyobb, OBB *Emyobb2, OBB *Emyobb3);
	void CheckAttackEmyEmy4(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Enemy(&enemy4)[eTANKNUM],
		                    OBB *Emyobb, OBB *Emyobb2, OBB *Emyobb3, OBB *Emyobb4);
	void MoveEnemy(Enemy(&enemy)[eTANKNUM], float speedmax, float pitchmax, float acc1, float acc2, float turn);
	void PointToEnemy(Enemy(&enemy)[eTANKNUM]);
	void PointToEnemy2(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM]);
	void PointToEnemy3(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM]);
	void PointToEnemy4(Enemy(&enemy)[eTANKNUM], Enemy(&enemy2)[eTANKNUM], Enemy(&enemy3)[eTANKNUM], Enemy(&enemy4)[eTANKNUM]);
void DrawInGame(void);
void Draw2DFrontInGame(void);
void Draw3DInGame(void);
	void Setup3DEnv(void);
	void SetupLight(void);
	void SetupCamera(D3DXVECTOR3 *position);
	void Camera_Far(D3DXVECTOR3 *position);
	void For_a(Tank(&tank)[myTANKNUM]);
	void For_b(Tank(&tank)[myTANKNUM], float pitchmax, float pitchmin);
	void For_c(Enemy(&enemy)[eTANKNUM], Tank(&tank)[myTANKNUM]);
	void For_d(Enemy(&enemy)[eTANKNUM], Tank(&tank)[myTANKNUM], float pitchmax, float pitchmin);
	void For_e(Enemy(&enemy)[eTANKNUM]);
	void DrawTank(Tank(&tank)[myTANKNUM]);
	void DrawLand(Land &land);
	void DrawEnemy(Enemy(&enemy)[eTANKNUM]);
	void DrawShell(Shell &shell);
	void DrawEmyShell(Shell(&shell));
	void DrawPoint();
void Draw2DBackInGame(void);
HRESULT DisposeInGame(void);
//  エンディング関係のプロトタイプ宣言
HRESULT InitEnd(void);
HRESULT DoEnd(void);
    void DrawEnd(void);
HRESULT DisposeEnd(void);

/////////////////////////////////////////////////////////////////////////
//  InGameを準備
/////////////////////////////////////////////////////////////////////////
HRESULT InitInGame(void)
{
	if (FAILED(SetupInGame())) return E_FAIL;
	//InGameの基本準備
	func = DoInGame;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  InGameのデータを準備
/////////////////////////////////////////////////////////////////////////
HRESULT SetupInGame(void)
{
	//以下、InGameの準備を記述
	char path[] = "X\\";

	char *T44FileName[] = { "T44body.x", "T44head.x", "T44gun.x" };
	char *IS1FileName[] = { "IS1body.x", "IS1head.x", "IS1gun.x" };
	char *T54FileName[] = { "T54body.x", "T54head.x", "T54gun.x" };
	char *IS3FileName[] = { "IS3body.x", "IS3head.x", "IS3gun.x" };
	char *PantherGFileName[] = { "PantherGbody.x", "PantherGhead.x", "PantherGgun.x" };
	char *TigerFileName[] = { "Tigerbody.x", "Tigerhead.x", "Tigergun.x" };
	char *PantherIIFileName[] = { "PantherIIbody.x", "PantherIIhead.x", "PantherIIgun.x" };
	char *TigerIIFileName[] = { "TigerIIbody.x", "TigerIIhead.x", "TigerIIgun.x" };
	char *M26FileName[] = { "M26body.x", "M26head.x", "M26gun.x" };
	char *T32FileName[] = { "T32body.x", "T32head.x", "T32gun.x" };
	char *M46FileName[] = { "M46body.x", "M46head.x", "M46gun.x" };
	char *M103FileName[] = { "M103body.x", "M103head.x", "M103gun.x" };

	char *land1FileName = "ground.x";
	char *land2FileName = "ground2.x";
	char *land3FileName = "ground3.x";
	char *land4FileName = "ground4.x";
	char *PointFileName = "Point.x";

	char *EmyT44FileName[] = { "T44body.x", "T44head.x", "T44gun.x" };
	char *EmyIS1FileName[] = { "IS1body.x", "IS1head.x", "IS1gun.x" };
	char *EmyT54FileName[] = { "T54body.x", "T54head.x", "T54gun.x" };
	char *EmyIS3FileName[] = { "IS3body.x", "IS3head.x", "IS3gun.x" };
	char *EmyPantherGFileName[] = { "PantherGbody.x", "PantherGhead.x", "PantherGgun.x" };
	char *EmyTigerFileName[] = { "Tigerbody.x", "Tigerhead.x", "Tigergun.x" };
	char *EmyPantherIIFileName[] = { "PantherIIbody.x", "PantherIIhead.x", "PantherIIgun.x" };
	char *EmyTigerIIFileName[] = { "TigerIIbody.x", "TigerIIhead.x", "TigerIIgun.x" };
	char *EmyM26FileName[] = { "M26body.x", "M26head.x", "M26gun.x" };
	char *EmyT32FileName[] = { "T32body.x", "T32head.x", "T32gun.x" };
	char *EmyM46FileName[] = { "M46body.x", "M46head.x", "M46gun.x" };
	char *EmyM103FileName[] = { "M103body.x", "M103head.x", "M103gun.x" };

	char *T44shellFileName = "T44shell.x";
	char *IS1shellFileName = "IS1shell.x";
	char *T54shellFileName = "T54shell.x";
	char *IS3shellFileName = "IS3shell.x";
	char *PantherGshellFileName = "PantherGshell.x";
	char *TigershellFileName = "Tigershell.x";
	char *PantherIIshellFileName = "PantherIIshell.x";
	char *TigerIIshellFileName = "TigerIIshell.x";
	char *M26shellFileName = "M26shell.x";
	char *T32shellFileName = "T32shell.x";
	char *M46shellFileName = "M46shell.x";
	char *M103shellFileName = "M103shell.x";

	char *EmyT44shellFileName = "T44shell.x";
	char *EmyIS1shellFileName = "IS1shell.x";
	char *EmyT54shellFileName = "T54shell.x";
	char *EmyIS3shellFileName = "IS3shell.x";
	char *EmyPantherGshellFileName = "PantherGshell.x";
	char *EmyTigershellFileName = "Tigershell.x";
	char *EmyPantherIIshellFileName = "PantherIIshell.x";
	char *EmyTigerIIshellFileName = "TigerIIshell.x";
	char *EmyM26shellFileName = "M26shell.x";
	char *EmyT32shellFileName = "T32shell.x";
	char *EmyM46shellFileName = "M46shell.x";
	char *EmyM103shellFileName = "M103shell.x";

	char Center[] = "BMP\\center.png";
	char Target[] = "BMP\\target.png";
	char Sight[] = "BMP\\gunsight.png";
	char Sky[] = "BMP\\sky.png";
	char Hp[] = "BMP\\hp.png";
	char Hp0[] = "BMP\\hp0.png";
	char Shellx[] = "BMP\\hp.png";
	char Shellx0[] = "BMP\\hp0.png";
	char Pointx[] = "BMP\\hp.png";
	char Pointx0[] = "BMP\\hp0.png";

	char T44x[] = "BMP\\T44.png";
	char T54x[] = "BMP\\T54.png";
	char IS1x[] = "BMP\\IS1.png";
	char IS3x[] = "BMP\\IS3.png";

	char PantherGx[] = "BMP\\PantherG.png";
	char PantherIIx[] = "BMP\\PantherII.png";
	char Tigerx[] = "BMP\\Tiger.png";
	char TigerIIx[] = "BMP\\TigerII.png";

	char M26x[] = "BMP\\M26.png";
	char M46x[] = "BMP\\M46.png";
	char T32x[] = "BMP\\T32.png";
	char M103x[] = "BMP\\M103.png";
	//  tank   //////////////////////////////////////////////////////////
	D3DXVECTOR3 offsetT44[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.08f, 2.3f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		T44[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		T44[i].direction = 0.0f;
		T44[i].pitch = 0.0f;
		T44[i].roll = 0.0f;
		D3DXMatrixIdentity(&T44[i].mat);
		T44[i].offset = offsetT44[i];
		T44[i].speed = 0.0f;
		T44[i].backspeed = 0.0f;
		T44[i].turn = 0.0f;
		T44[i].hp = 1200;
		T44[i].hpmax = 1200;
		T44[myHEAD].armor = 95.f;
		T44[myBODY].armor = 70.f;
		if (FAILED(LoadXFile(T44FileName[i], &T44[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetIS1[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.7f, 2.0f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		IS1[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		IS1[i].direction = 0.0f;
		IS1[i].pitch = 0.0f;
		IS1[i].roll = 0.0f;
		D3DXMatrixIdentity(&IS1[i].mat);
		IS1[i].offset = offsetIS1[i];
		IS1[i].speed = 0.0f;
		IS1[i].backspeed = 0.0f;
		IS1[i].turn = 0.0f;
		IS1[i].hp = 1130;
		IS1[i].hpmax = 1130;
		IS1[myHEAD].armor = 100.f;
		IS1[myBODY].armor = 90.f;
		if (FAILED(LoadXFile(IS1FileName[i], &IS1[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetT54[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.3f, 2.4f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		T54[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		T54[i].direction = 0.0f;
		T54[i].pitch = 0.0f;
		T54[i].roll = 0.0f;
		D3DXMatrixIdentity(&T54[i].mat);
		T54[i].offset = offsetT54[i];
		T54[i].speed = 0.0f;
		T54[i].backspeed = 0.0f;
		T54[i].turn = 0.0f;
		T54[i].hp = 1550;
		T54[i].hpmax = 1550;
		T54[myHEAD].armor = 125.f;
		T54[myBODY].armor = 81.7f;
		if (FAILED(LoadXFile(T54FileName[i], &T54[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetIS3[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.3f, 2.2f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		IS3[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		IS3[i].direction = 0.0f;
		IS3[i].pitch = 0.0f;
		IS3[i].roll = 0.0f;
		D3DXMatrixIdentity(&IS3[i].mat);
		IS3[i].offset = offsetIS3[i];
		IS3[i].speed = 0.0f;
		IS3[i].backspeed = 0.0f;
		IS3[i].turn = 0.0f;
		IS3[i].hp = 1450;
		IS3[i].hpmax = 1450;
		IS3[myHEAD].armor = 150.f;
		IS3[myBODY].armor = 86.7f;
		if (FAILED(LoadXFile(IS3FileName[i], &IS3[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetPantherG[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.8f, 1.7f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		PantherG[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		PantherG[i].direction = 0.0f;
		PantherG[i].pitch = 0.0f;
		PantherG[i].roll = 0.0f;
		D3DXMatrixIdentity(&PantherG[i].mat);
		PantherG[i].offset = offsetPantherG[i];
		PantherG[i].speed = 0.0f;
		PantherG[i].backspeed = 0.0f;
		PantherG[i].turn = 0.0f;
		PantherG[i].hp = 1200;
		PantherG[i].hpmax = 1200;
		PantherG[myHEAD].armor = 63.3f;
		PantherG[myBODY].armor = 56.7f;
		if (FAILED(LoadXFile(PantherGFileName[i], &PantherG[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetTiger[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.4f, 1.95f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		Tiger[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		Tiger[i].direction = 0.0f;
		Tiger[i].pitch = 0.0f;
		Tiger[i].roll = 0.0f;
		D3DXMatrixIdentity(&Tiger[i].mat);
		Tiger[i].offset = offsetTiger[i];
		Tiger[i].speed = 0.0f;
		Tiger[i].backspeed = 0.0f;
		Tiger[i].turn = 0.0f;
		Tiger[i].hp = 1400;
		Tiger[i].hpmax = 1400;
		Tiger[myHEAD].armor = 70.7f;
		Tiger[myBODY].armor = 88.7f;
		if (FAILED(LoadXFile(TigerFileName[i], &Tiger[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetPantherII[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.65f, 1.37f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		PantherII[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		PantherII[i].direction = 0.0f;
		PantherII[i].pitch = 0.0f;
		PantherII[i].roll = 0.0f;
		D3DXMatrixIdentity(&PantherII[i].mat);
		PantherII[i].offset = offsetPantherII[i];
		PantherII[i].speed = 0.0f;
		PantherII[i].backspeed = 0.0f;
		PantherII[i].turn = 0.0f;
		PantherII[i].hp = 1400;
		PantherII[i].hpmax = 1400;
		PantherII[myHEAD].armor = 90.f;
		PantherII[myBODY].armor = 86.7f;
		if (FAILED(LoadXFile(PantherIIFileName[i], &PantherII[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetTigerII[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.48f, 1.95f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		TigerII[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		TigerII[i].direction = 0.0f;
		TigerII[i].pitch = 0.0f;
		TigerII[i].roll = 0.0f;
		D3DXMatrixIdentity(&TigerII[i].mat);
		TigerII[i].offset = offsetTigerII[i];
		TigerII[i].speed = 0.0f;
		TigerII[i].backspeed = 0.0f;
		TigerII[i].turn = 0.0f;
		TigerII[i].hp = 1500;
		TigerII[i].hpmax = 1500;
		TigerII[myHEAD].armor = 113.3f;
		TigerII[myBODY].armor = 103.3f;
		if (FAILED(LoadXFile(TigerIIFileName[i], &TigerII[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetM26[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 1.8f, 1.8f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		M26[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		M26[i].direction = 0.0f;
		M26[i].pitch = 0.0f;
		M26[i].roll = 0.0f;
		D3DXMatrixIdentity(&M26[i].mat);
		M26[i].offset = offsetM26[i];
		M26[i].speed = 0.0f;
		M26[i].backspeed = 0.0f;
		M26[i].turn = 0.0f;
		M26[i].hp = 1350;
		M26[i].hpmax = 1350;
		M26[myHEAD].armor = 84.3f;
		M26[myBODY].armor = 76.f;
		if (FAILED(LoadXFile(M26FileName[i], &M26[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetT32[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.0f, 1.75f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		T32[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		T32[i].direction = 0.0f;
		T32[i].pitch = 0.0f;
		T32[i].roll = 0.0f;
		D3DXMatrixIdentity(&T32[i].mat);
		T32[i].offset = offsetT32[i];
		T32[i].speed = 0.0f;
		T32[i].backspeed = 0.0f;
		T32[i].turn = 0.0f;
		T32[i].hp = 1400;
		T32[i].hpmax = 1400;
		T32[myHEAD].armor = 100.7f;
		T32[myBODY].armor = 84.3f;
		if (FAILED(LoadXFile(T32FileName[i], &T32[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetM46[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 1.8f, 1.8f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		M46[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		M46[i].direction = 0.0f;
		M46[i].pitch = 0.0f;
		M46[i].roll = 0.0f;
		D3DXMatrixIdentity(&M46[i].mat);
		M46[i].offset = offsetM46[i];
		M46[i].speed = 0.0f;
		M46[i].backspeed = 0.0f;
		M46[i].turn = 0.0f;
		M46[i].hp = 1600;
		M46[i].hpmax = 1600;
		M46[myHEAD].armor = 84.3f;
		M46[myBODY].armor = 76.f;
		if (FAILED(LoadXFile(M46FileName[i], &M46[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetM103[myTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 1.72f, 2.3f),
	};
	for (int i = 0; i < myTANKNUM; ++i)
	{
		M103[i].position = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
		M103[i].direction = 0.0f;
		M103[i].pitch = 0.0f;
		M103[i].roll = 0.0f;
		D3DXMatrixIdentity(&M103[i].mat);
		M103[i].offset = offsetM103[i];
		M103[i].speed = 0.0f;
		M103[i].backspeed = 0.0f;
		M103[i].turn = 0.0f;
		M103[i].hp = 1750;
		M103[i].hpmax = 1750;
		M103[myHEAD].armor = 101.7f;
		M103[myBODY].armor = 72.f;
		if (FAILED(LoadXFile(M103FileName[i], &M103[i].mesh, path)))
			return E_FAIL;
	}

	tank_hpup = false;
	tank_hpdown = false;
	outofmap = false;
	//  land  ///////////////////////////////////////////////////////////
	land1.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (FAILED(LoadXFile(land1FileName, &land1.mesh, path)))
		return E_FAIL;
	land2.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (FAILED(LoadXFile(land2FileName, &land2.mesh, path)))
		return E_FAIL;
	land3.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (FAILED(LoadXFile(land3FileName, &land3.mesh, path)))
		return E_FAIL;
	land4.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (FAILED(LoadXFile(land4FileName, &land4.mesh, path)))
		return E_FAIL;
	Point.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (FAILED(LoadXFile(PointFileName, &Point.mesh, path)))
		return E_FAIL;

	flag_point = true;
	point_tank = false;
	point_enemy = false;
	//  enemy  ///////////////////////////////////////////////////////////
	D3DXVECTOR3 offsetEmyT44[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.08f, 2.3f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyT44[i].position = D3DXVECTOR3(0.f, 0.f, 150.0f);
		EmyT44[i].direction = 0.0f;
		EmyT44[i].pitch = 0.0f;
		EmyT44[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyT44[i].mat);
		EmyT44[i].offsetEmy = offsetEmyT44[i];
		EmyT44[i].speed = 0.0f;
		EmyT44[i].hp = 1200;
		EmyT44[i].hpmax = 1200;
		EmyT44[eHEAD].armor = 95.f;
		EmyT44[eBODY].armor = 70.f;
		EmyT44[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyT44FileName[i], &EmyT44[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyIS1[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.7f, 2.0f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyIS1[i].position = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);
		EmyIS1[i].direction = 0.0f;
		EmyIS1[i].pitch = 0.0f;
		EmyIS1[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyIS1[i].mat);
		EmyIS1[i].offsetEmy = offsetEmyIS1[i];
		EmyIS1[i].speed = 0.0f;
		EmyIS1[i].hp = 1130;
		EmyIS1[i].hpmax = 1130;
		EmyIS1[eHEAD].armor = 100.f;
		EmyIS1[eBODY].armor = 90.f;
		EmyIS1[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyIS1FileName[i], &EmyIS1[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyT54[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.3f, 2.4f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyT54[i].position = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
		EmyT54[i].direction = 0.0f;
		EmyT54[i].pitch = 0.0f;
		EmyT54[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyT54[i].mat);
		EmyT54[i].offsetEmy = offsetEmyT54[i];
		EmyT54[i].speed = 0.0f;
		EmyT54[i].hp = 1550;
		EmyT54[i].hpmax = 1550;
		EmyT54[eHEAD].armor = 125.f;
		EmyT54[eBODY].armor = 81.7f;
		EmyT54[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyT54FileName[i], &EmyT54[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyIS3[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.3f, 2.2f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyIS3[i].position = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);
		EmyIS3[i].direction = 0.0f;
		EmyIS3[i].pitch = 0.0f;
		EmyIS3[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyIS3[i].mat);
		EmyIS3[i].offsetEmy = offsetEmyIS3[i];
		EmyIS3[i].speed = 0.0f;
		EmyIS3[i].hp = 1450;
		EmyIS3[i].hpmax = 1450;
		EmyIS3[eHEAD].armor = 150.f;
		EmyIS3[eBODY].armor = 86.7f;
		EmyIS3[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyIS3FileName[i], &EmyIS3[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyPantherG[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.8f, 1.7f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyPantherG[i].position = D3DXVECTOR3(0.f, 0.f, 150.0f);
		EmyPantherG[i].direction = 0.0f;
		EmyPantherG[i].pitch = 0.0f;
		EmyPantherG[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyPantherG[i].mat);
		EmyPantherG[i].offsetEmy = offsetEmyPantherG[i];
		EmyPantherG[i].speed = 0.0f;
		EmyPantherG[i].hp = 1200;
		EmyPantherG[i].hpmax = 1200;
		EmyPantherG[eHEAD].armor = 63.3f;
		EmyPantherG[eBODY].armor = 56.7f;
		EmyPantherG[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyPantherGFileName[i], &EmyPantherG[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyTiger[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.4f, 1.95f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyTiger[i].position = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);
		EmyTiger[i].direction = 0.0f;
		EmyTiger[i].pitch = 0.0f;
		EmyTiger[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyTiger[i].mat);
		EmyTiger[i].offsetEmy = offsetEmyTiger[i];
		EmyTiger[i].speed = 0.0f;
		EmyTiger[i].hp = 1400;
		EmyTiger[i].hpmax = 1400;
		EmyTiger[eHEAD].armor = 70.7f;
		EmyTiger[eBODY].armor = 88.7f;
		EmyTiger[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyTigerFileName[i], &EmyTiger[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyPantherII[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.65f, 1.37f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyPantherII[i].position = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
		EmyPantherII[i].direction = 0.0f;
		EmyPantherII[i].pitch = 0.0f;
		EmyPantherII[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyPantherII[i].mat);
		EmyPantherII[i].offsetEmy = offsetEmyPantherII[i];
		EmyPantherII[i].speed = 0.0f;
		EmyPantherII[i].hp = 1400;
		EmyPantherII[i].hpmax = 1400;
		EmyPantherII[eHEAD].armor = 90.f;
		EmyPantherII[eBODY].armor = 86.7f;
		EmyPantherII[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyPantherIIFileName[i], &EmyPantherII[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyTigerII[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.48f, 1.95f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyTigerII[i].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		EmyTigerII[i].direction = 0.0f;
		EmyTigerII[i].pitch = 0.0f;
		EmyTigerII[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyTigerII[i].mat);
		EmyTigerII[i].offsetEmy = offsetEmyTigerII[i];
		EmyTigerII[i].speed = 0.0f;
		EmyTigerII[i].hp = 1500;
		EmyTigerII[i].hpmax = 1500;
		EmyTigerII[eHEAD].armor = 113.3f;
		EmyTigerII[eBODY].armor = 103.3f;
		EmyTigerII[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyTigerIIFileName[i], &EmyTigerII[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyM26[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 1.8f, 1.8f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyM26[i].position = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
		EmyM26[i].direction = 0.0f;
		EmyM26[i].pitch = 0.0f;
		EmyM26[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyM26[i].mat);
		EmyM26[i].offsetEmy = offsetEmyM26[i];
		EmyM26[i].speed = 0.0f;
		EmyM26[i].hp = 1350;
		EmyM26[i].hpmax = 1350;
		EmyM26[eHEAD].armor = 84.3f;
		EmyM26[eBODY].armor = 76.f;
		EmyM26[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyM26FileName[i], &EmyM26[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyT32[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.0f, 1.75f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyT32[i].position = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);
		EmyT32[i].direction = 0.0f;
		EmyT32[i].pitch = 0.0f;
		EmyT32[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyT32[i].mat);
		EmyT32[i].offsetEmy = offsetEmyT32[i];
		EmyT32[i].speed = 0.0f;
		EmyT32[i].hp = 1400;
		EmyT32[i].hpmax = 1400;
		EmyT32[eHEAD].armor = 100.7f;
		EmyT32[eBODY].armor = 84.3f;
		EmyT32[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyT32FileName[i], &EmyT32[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyM46[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 1.8f, 1.8f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyM46[i].position = D3DXVECTOR3(10.0f, 0.0f, 140.0f);
		EmyM46[i].direction = 0.0f;
		EmyM46[i].pitch = 0.0f;
		EmyM46[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyM46[i].mat);
		EmyM46[i].offsetEmy = offsetEmyM46[i];
		EmyM46[i].speed = 0.0f;
		EmyM46[i].hp = 1600;
		EmyM46[i].hpmax = 1600;
		EmyM46[eHEAD].armor = 84.3f;
		EmyM46[eBODY].armor = 76.f;
		EmyM46[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyM46FileName[i], &EmyM46[i].mesh, path)))
			return E_FAIL;
	}

	D3DXVECTOR3 offsetEmyM103[eTANKNUM] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 1.72f, 2.3f),
	};
	for (int i = 0; i < eTANKNUM; ++i)
	{
		EmyM103[i].position = D3DXVECTOR3(-10.0f, 0.0f, 140.0f);
		EmyM103[i].direction = 0.0f;
		EmyM103[i].pitch = 0.0f;
		EmyM103[i].roll = 0.0f;
		D3DXMatrixIdentity(&EmyM103[i].mat);
		EmyM103[i].offsetEmy = offsetEmyM103[i];
		EmyM103[i].speed = 0.0f;
		EmyM103[i].hp = 1750;
		EmyM103[i].hpmax = 1750;
		EmyM103[eHEAD].armor = 101.7f;
		EmyM103[eBODY].armor = 72.f;
		EmyM103[i].turn = 0.f;
		if (FAILED(LoadXFile(EmyM103FileName[i], &EmyM103[i].mesh, path)))
			return E_FAIL;
	}

	//  shell  ///////////////////////////////////////////////////////////
	T44_shell.fireOK = false;
	T44_shell.active = false;
	T44_shell.time = 0.f;
	T44_shell.hit = 0;
	T44_shell.hitmax = 0;
	if (FAILED(LoadXFile(T44shellFileName, &T44_shell.mesh, path)))
		return E_FAIL;
	IS1_shell.fireOK = false;
	IS1_shell.active = false;
	IS1_shell.time = 0.f;
	IS1_shell.hit = 0;
	IS1_shell.hitmax = 0;
	if (FAILED(LoadXFile(IS1shellFileName, &IS1_shell.mesh, path)))
		return E_FAIL;
	T54_shell.fireOK = false;
	T54_shell.active = false;
	T54_shell.time = 0.f;
	T54_shell.hit = 0;
	T54_shell.hitmax = 0;
	if (FAILED(LoadXFile(T54shellFileName, &T54_shell.mesh, path)))
		return E_FAIL;
	IS3_shell.fireOK = false;
	IS3_shell.active = false;
	IS3_shell.time = 0.f;
	IS3_shell.hit = 0;
	IS3_shell.hitmax = 0;
	if (FAILED(LoadXFile(IS3shellFileName, &IS3_shell.mesh, path)))
		return E_FAIL;
	PantherG_shell.fireOK = false;
	PantherG_shell.active = false;
	PantherG_shell.time = 0.f;
	PantherG_shell.hit = 0;
	PantherG_shell.hitmax = 0;
	if (FAILED(LoadXFile(PantherGshellFileName, &PantherG_shell.mesh, path)))
		return E_FAIL;
	Tiger_shell.fireOK = false;
	Tiger_shell.active = false;
	Tiger_shell.time = 0.f;
	Tiger_shell.hit = 0;
	Tiger_shell.hitmax = 0;
	if (FAILED(LoadXFile(TigershellFileName, &Tiger_shell.mesh, path)))
		return E_FAIL;
	PantherII_shell.fireOK = false;
	PantherII_shell.active = false;
	PantherII_shell.time = 0.f;
	PantherII_shell.hit = 0;
	PantherII_shell.hitmax = 0;
	if (FAILED(LoadXFile(PantherIIshellFileName, &PantherII_shell.mesh, path)))
		return E_FAIL;
	TigerII_shell.fireOK = false;
	TigerII_shell.active = false;
	TigerII_shell.time = 0.f;
	TigerII_shell.hit = 0;
	TigerII_shell.hitmax = 0;
	if (FAILED(LoadXFile(TigerIIshellFileName, &TigerII_shell.mesh, path)))
		return E_FAIL;
	M26_shell.fireOK = false;
	M26_shell.active = false;
	M26_shell.time = 0.f;
	M26_shell.hit = 0;
	M26_shell.hitmax = 0;
	if (FAILED(LoadXFile(M26shellFileName, &M26_shell.mesh, path)))
		return E_FAIL;
	T32_shell.fireOK = false;
	T32_shell.active = false;
	T32_shell.time = 0.f;
	T32_shell.hit = 0;
	T32_shell.hitmax = 0;
	if (FAILED(LoadXFile(T32shellFileName, &T32_shell.mesh, path)))
		return E_FAIL;
	M46_shell.fireOK = false;
	M46_shell.active = false;
	M46_shell.time = 0.f;
	M46_shell.hit = 0;
	M46_shell.hitmax = 0;
	if (FAILED(LoadXFile(M46shellFileName, &M46_shell.mesh, path)))
		return E_FAIL;
	M103_shell.fireOK = false;
	M103_shell.active = false;
	M103_shell.time = 0.f;
	M103_shell.hit = 0;
	M103_shell.hitmax = 0;
	if (FAILED(LoadXFile(M103shellFileName, &M103_shell.mesh, path)))
		return E_FAIL;

	EmyT44_shell.active = false;
	EmyT44_shell.fireOK = false;
	EmyT44_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyT44shellFileName, &EmyT44_shell.mesh, path)))
		return E_FAIL;
	EmyIS1_shell.active = false;
	EmyIS1_shell.fireOK = false;
	EmyIS1_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyIS1shellFileName, &EmyIS1_shell.mesh, path)))
		return E_FAIL;
	EmyT54_shell.active = false;
	EmyT54_shell.fireOK = false;
	EmyT54_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyT54shellFileName, &EmyT54_shell.mesh, path)))
		return E_FAIL;
	EmyIS3_shell.active = false;
	EmyIS3_shell.fireOK = false;
	EmyIS3_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyIS3shellFileName, &EmyIS3_shell.mesh, path)))
		return E_FAIL;
	EmyPantherG_shell.active = false;
	EmyPantherG_shell.fireOK = false;
	EmyPantherG_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyPantherGshellFileName, &EmyPantherG_shell.mesh, path)))
		return E_FAIL;
	EmyTiger_shell.active = false;
	EmyTiger_shell.fireOK = false;
	EmyTiger_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyTigershellFileName, &EmyTiger_shell.mesh, path)))
		return E_FAIL;
	EmyPantherII_shell.active = false;
	EmyPantherII_shell.fireOK = false;
	EmyPantherII_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyPantherIIshellFileName, &EmyPantherII_shell.mesh, path)))
		return E_FAIL;
	EmyTigerII_shell.active = false;
	EmyTigerII_shell.fireOK = false;
	EmyTigerII_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyTigerIIshellFileName, &EmyTigerII_shell.mesh, path)))
		return E_FAIL;
	EmyM26_shell.active = false;
	EmyM26_shell.fireOK = false;
	EmyM26_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyM26shellFileName, &EmyM26_shell.mesh, path)))
		return E_FAIL;
	EmyT32_shell.active = false;
	EmyT32_shell.fireOK = false;
	EmyT32_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyT32shellFileName, &EmyT32_shell.mesh, path)))
		return E_FAIL;
	EmyM46_shell.active = false;
	EmyM46_shell.fireOK = false;
	EmyM46_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyM46shellFileName, &EmyM46_shell.mesh, path)))
		return E_FAIL;
	EmyM103_shell.active = false;
	EmyM103_shell.fireOK = false;
	EmyM103_shell.time = 0.f;
	if (FAILED(LoadXFile(EmyM103shellFileName, &EmyM103_shell.mesh, path)))
		return E_FAIL;
	// 前景  ////////////////////////////////////////////////////////////
	if (FAILED(LoadTexture(Center, &lpCenter))) return E_FAIL;
	if (FAILED(LoadTexture(Target, &lpTarget))) return E_FAIL;
	if (FAILED(LoadTexture(Sight, &lpSight))) return E_FAIL;
	if (FAILED(LoadTexture(Hp, &lpHp))) return E_FAIL;
	if (FAILED(LoadTexture(Hp0, &lpHp0))) return E_FAIL;
	if (FAILED(LoadTexture(Shellx, &lpShell))) return E_FAIL;
	if (FAILED(LoadTexture(Shellx0, &lpShell0))) return E_FAIL;
	if (FAILED(LoadTexture(Pointx, &lpPoint))) return E_FAIL;
	if (FAILED(LoadTexture(Pointx0, &lpPoint0))) return E_FAIL;

	if (FAILED(LoadTexture(T44x, &lpT44))) return E_FAIL;
	if (FAILED(LoadTexture(IS1x, &lpIS1))) return E_FAIL;
	if (FAILED(LoadTexture(T54x, &lpT54))) return E_FAIL;
	if (FAILED(LoadTexture(IS3x, &lpIS3))) return E_FAIL;
	if (FAILED(LoadTexture(PantherGx, &lpPantherG))) return E_FAIL;
	if (FAILED(LoadTexture(Tigerx, &lpTiger))) return E_FAIL;
	if (FAILED(LoadTexture(PantherIIx, &lpPantherII))) return E_FAIL;
	if (FAILED(LoadTexture(TigerIIx, &lpTigerII))) return E_FAIL;
	if (FAILED(LoadTexture(M26x, &lpM26))) return E_FAIL;
	if (FAILED(LoadTexture(T32x, &lpT32))) return E_FAIL;
	if (FAILED(LoadTexture(M46x, &lpM46))) return E_FAIL;
	if (FAILED(LoadTexture(M103x, &lpM103))) return E_FAIL;
	// 背景  ////////////////////////////////////////////////////////////
	if (FAILED(LoadTexture(Sky, &lpSky))) return E_FAIL;
	//以上、InGameの準備を記述
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  InGameを実行
/////////////////////////////////////////////////////////////////////////
HRESULT DoInGame(void)
{
	DWORD fpLastTime = timeGetTime();
	while(count>=0)
	{
		ShowCursor(FALSE);
		count -= 1;
	}
	switch (num_tank)
	{
	case 11:
		MoveChild(T44);
		MoveTank(T44, 49.f, 36.f, 11.42f, 7.46f, 7.f, 15.22f);
		if (camera.m_Rbtn == false) MoveHead(T44, 15.f);
		if (camera.m_Rbtn) MoveHeadFar(T44, 15.f);
		if (camera.m_Rbtn == false) MoveGun(T44, 28.f, 5.f);
		if (camera.m_Rbtn) MoveGunFar(T44, 28.f, 5.f);
		MoveShell(T44_shell, T44, 792.f,8.5f);
		CreateOBB(&T44obb, T44);
		CreateHeadOBB(&T44headobb, T44);
		CreateShellOBB(&T44Shellobb, T44_shell, T44);
		switch (num_stage)
		{
		case 1:
			CheckHeight(T44,land1);
			CheckLean(T44,land1);
			CalcHitPoint(T44, T44_shell, land1);
			break;
		case 2:
			CheckHeight(T44, land2);
			CheckLean(T44, land2);
			CalcHitPoint(T44, T44_shell, land2);
			break;
		case 3:
			CheckHeight(T44, land3);
			CheckLean(T44, land3);
			CalcHitPoint(T44, T44_shell, land3);
			break;
		case 4:
			CheckHeight(T44, land4);
			CheckLean(T44, land4);
			CalcHitPoint(T44, T44_shell, land4);
			break;
		}
		break;
	case 12:
		MoveChild(IS1);
		MoveTank(IS1, 38.f, 41.f, 13.39f, 5.33f, 14.f, 38.04f);
		if (camera.m_Rbtn == false) MoveHead(IS1, 14.f);
		if (camera.m_Rbtn) MoveHeadFar(IS1, 14.f);
		if (camera.m_Rbtn == false) MoveGun(IS1, 25.f, 5.f);
		if (camera.m_Rbtn) MoveGunFar(IS1, 25.f, 5.f);
		MoveShell(IS1_shell, IS1, 792.f,9.6f);
		CreateOBB(&IS1obb, IS1);
		CreateHeadOBB(&IS1headobb, IS1);
		CreateShellOBB(&IS1Shellobb, IS1_shell, IS1);
		switch (num_stage)
		{
		case 1:
			CheckHeight(IS1, land1);
			CheckLean(IS1, land1);
			CalcHitPoint(IS1, IS1_shell, land1);
			break;
		case 2:
			CheckHeight(IS1, land2);
			CheckLean(IS1, land2);
			CalcHitPoint(IS1, IS1_shell, land2);
			break;
		case 3:
			CheckHeight(IS1, land3);
			CheckLean(IS1, land3);
			CalcHitPoint(IS1, IS1_shell, land3);
			break;
		case 4:
			CheckHeight(IS1, land4);
			CheckLean(IS1, land4);
			CalcHitPoint(IS1, IS1_shell, land4);
			break;
		}
		break;
	case 13:
		MoveChild(T54);
		MoveTank(T54, 45.f, 36.f, 10.65f, 5.74f, 6.f, 18.2f);
		if (camera.m_Rbtn == false) MoveHead(T54, 10.f);
		if (camera.m_Rbtn) MoveHeadFar( T54, 10.f);
		if (camera.m_Rbtn == false) MoveGun(T54, 17.f, 4.f);
		if (camera.m_Rbtn) MoveGunFar( T54, 17.f, 4.f);
		MoveShell(T54_shell, T54, 887.f,16.3f);
		CreateOBB(&T54obb, T54);
		CreateHeadOBB(&T54headobb, T54);
		CreateShellOBB(&T54Shellobb, T54_shell, T54);
		switch (num_stage)
		{
		case 1:
			CheckHeight(T54, land1);
			CheckLean(T54, land1);
			CalcHitPoint(T54, T54_shell, land1);
			break;
		case 2:
			CheckHeight(T54, land2);
			CheckLean(T54, land2);
			CalcHitPoint(T54, T54_shell, land2);
			break;
		case 3:
			CheckHeight(T54, land3);
			CheckLean(T54, land3);
			CalcHitPoint(T54, T54_shell, land3);
			break;
		case 4:
			CheckHeight(T54, land4);
			CheckLean(T54, land4);
			CalcHitPoint(T54, T54_shell, land4);
			break;
		}
		break;
	case 14:
		MoveChild(IS3);
		MoveTank(IS3, 38.f, 41.f, 15.81f, 5.53f, 14.f, 38.07f);
		if (camera.m_Rbtn == false) MoveHead(IS3, 12.f);
		if (camera.m_Rbtn) MoveHeadFar( IS3, 12.f);
		if (camera.m_Rbtn == false) MoveGun( IS3, 19.f, 2.f);
		if (camera.m_Rbtn) MoveGunFar(IS3, 19.f, 2.f);
		MoveShell(IS3_shell, IS3, 800.f,27.1f);
		CreateOBB(&IS3obb, IS3);
		CreateHeadOBB(&IS3headobb, IS3);
		CreateShellOBB(&IS3Shellobb, IS3_shell, IS3);
		switch (num_stage)
		{
		case 1:
			CheckHeight(IS3, land1);
			CheckLean(IS3, land1);
			CalcHitPoint(IS3, IS3_shell, land1);
			break;
		case 2:
			CheckHeight(IS3, land2);
			CheckLean(IS3, land2);
			CalcHitPoint(IS3, IS3_shell, land2);
			break;
		case 3:
			CheckHeight(IS3, land3);
			CheckLean(IS3, land3);
			CalcHitPoint(IS3, IS3_shell, land3);
			break;
		case 4:
			CheckHeight(IS3, land4);
			CheckLean(IS3, land4);
			CalcHitPoint(IS3, IS3_shell, land4);
			break;
		}
		break;
	case 21:
		MoveChild(PantherG);
		MoveTank(PantherG, 46.f, 41.f, 15.47f, 8.25f, 4.f, 28.57f);
		if (camera.m_Rbtn == false) MoveHead(PantherG, 15.f);
		if (camera.m_Rbtn) MoveHeadFar(PantherG, 15.f);
		if (camera.m_Rbtn == false) MoveGun(PantherG, 20.f, 8.f);
		if (camera.m_Rbtn) MoveGunFar( PantherG, 20.f, 8.f);
		MoveShell(PantherG_shell, PantherG, 935.f,11.2f);
		CreateOBB(&PantherGobb, PantherG);
		CreateHeadOBB(&PantherGheadobb, PantherG);
		CreateShellOBB(&PantherGShellobb, PantherG_shell, PantherG);
		switch (num_stage)
		{
		case 1:
			CheckHeight(PantherG, land1);
			CheckLean(PantherG, land1);
			CalcHitPoint(PantherG, PantherG_shell, land1);
			break;
		case 2:
			CheckHeight(PantherG, land2);
			CheckLean(PantherG, land2);
			CalcHitPoint(PantherG, PantherG_shell, land2);
			break;
		case 3:
			CheckHeight(PantherG, land3);
			CheckLean(PantherG, land3);
			CalcHitPoint(PantherG, PantherG_shell, land3);
			break;
		case 4:
			CheckHeight(PantherG, land4);
			CheckLean(PantherG, land4);
			CalcHitPoint(PantherG, PantherG_shell, land4);
			break;
		}
		break;
	case 22:
		MoveChild(Tiger);
		MoveTank(Tiger, 45.f, 41.f, 21.38f, 5.9f, 8.f, 37.78f);
		if (camera.m_Rbtn == false) MoveHead(Tiger, 7.5f);
		if (camera.m_Rbtn) MoveHeadFar( Tiger, 7.5f);
		if (camera.m_Rbtn == false) MoveGun( Tiger, 16.f, 8.f);
		if (camera.m_Rbtn) MoveGunFar(Tiger, 16.f, 8.f);
		MoveShell(Tiger_shell, Tiger, 773.f,10.8f);
		CreateOBB(&Tigerobb, Tiger);
		CreateHeadOBB(&Tigerheadobb, Tiger);
		CreateShellOBB(&TigerShellobb, Tiger_shell, Tiger);
		switch (num_stage)
		{
		case 1:
			CheckHeight(Tiger, land1);
			CheckLean(Tiger, land1);
			CalcHitPoint(Tiger, Tiger_shell, land1);
			break;
		case 2:
			CheckHeight(Tiger, land2);
			CheckLean(Tiger, land2);
			CalcHitPoint(Tiger, Tiger_shell, land2);
			break;
		case 3:
			CheckHeight(Tiger, land3);
			CheckLean(Tiger, land3);
			CalcHitPoint(Tiger, Tiger_shell, land3);
			break;
		case 4:
			CheckHeight(Tiger, land4);
			CheckLean(Tiger, land4);
			CalcHitPoint(Tiger, Tiger_shell, land4);
			break;
		}
		break;
	case 23:
		MoveChild(PantherII);
		MoveTank(PantherII, 54.f, 41.f, 14.49f, 8.3f, 4.f, 28.85f);
		if (camera.m_Rbtn == false) MoveHead(PantherII, 12.f);
		if (camera.m_Rbtn) MoveHeadFar( PantherII, 12.f);
		if (camera.m_Rbtn == false) MoveGun( PantherII, 15.f, 8.f);
		if (camera.m_Rbtn) MoveGunFar( PantherII, 15.f, 8.f);
		MoveShell(PantherII_shell, PantherII, 1000.f,13.f);
		CreateOBB(&PantherIIobb, PantherII);
		CreateHeadOBB(&PantherIIheadobb, PantherII);
		CreateShellOBB(&PantherIIShellobb, PantherII_shell, PantherII);
		switch (num_stage)
		{
		case 1:
			CheckHeight(PantherII, land1);
			CheckLean(PantherII, land1);
			CalcHitPoint(PantherII, PantherII_shell, land1);
			break;
		case 2:
			CheckHeight(PantherII, land2);
			CheckLean(PantherII, land2);
			CalcHitPoint(PantherII, PantherII_shell, land2);
			break;
		case 3:
			CheckHeight(PantherII, land3);
			CheckLean(PantherII, land3);
			CalcHitPoint(PantherII, PantherII_shell, land3);
			break;
		case 4:
			CheckHeight(PantherII, land4);
			CheckLean(PantherII, land4);
			CalcHitPoint(PantherII, PantherII_shell, land4);
			break;
		}
		break;
	case 24:
		MoveChild(TigerII);
		MoveTank(TigerII, 42.f, 41.f, 19.47f, 5.54f, 11.f, 52.38f);
		if (camera.m_Rbtn == false) MoveHead(TigerII, 18.5f);
		if (camera.m_Rbtn) MoveHeadFar(TigerII, 18.5f);
		if (camera.m_Rbtn == false) MoveGun( TigerII, 15.f, 8.f);
		if (camera.m_Rbtn) MoveGunFar(TigerII, 15.f, 8.f);
		MoveShell(TigerII_shell, TigerII, 1005.f,20.f);
		CreateOBB(&TigerIIobb, TigerII);
		CreateHeadOBB(&TigerIIheadobb, TigerII);
		CreateShellOBB(&TigerIIShellobb, TigerII_shell, TigerII);
		switch (num_stage)
		{
		case 1:
			CheckHeight(TigerII, land1);
			CheckLean(TigerII, land1);
			CalcHitPoint(TigerII, TigerII_shell, land1);
			break;
		case 2:
			CheckHeight(TigerII, land2);
			CheckLean(TigerII, land2);
			CalcHitPoint(TigerII, TigerII_shell, land2);
			break;
		case 3:
			CheckHeight(TigerII, land3);
			CheckLean(TigerII, land3);
			CalcHitPoint(TigerII, TigerII_shell, land3);
			break;
		case 4:
			CheckHeight(TigerII, land4);
			CheckLean(TigerII, land4);
			CalcHitPoint(TigerII, TigerII_shell, land4);
			break;
		}
		break;
	case 31:
		MoveChild(M26);
		MoveTank(M26, 46.f, 31.f, 18.46f, 6.08f, 11.f, 20.72f);
		if (camera.m_Rbtn == false) MoveHead(M26, 24.f);
		if (camera.m_Rbtn) MoveHeadFar( M26, 24.f);
		if (camera.m_Rbtn == false) MoveGun (M26, 20.f, 10.f);
		if (camera.m_Rbtn) MoveGunFar( M26, 20.f, 10.f);
		MoveShell(M26_shell, M26, 853.f,11.8f);
		CreateOBB(&M26obb, M26);
		CreateHeadOBB(&M26headobb, M26);
		CreateShellOBB(&M26Shellobb, M26_shell, M26);
		switch (num_stage)
		{
		case 1:
			CheckHeight(M26, land1);
			CheckLean(M26, land1);
			CalcHitPoint(M26, M26_shell, land1);
			break;
		case 2:
			CheckHeight(M26, land2);
			CheckLean(M26, land2);
			CalcHitPoint(M26, M26_shell, land2);
			break;
		case 3:
			CheckHeight(M26, land3);
			CheckLean(M26, land3);
			CalcHitPoint(M26, M26_shell, land3);
			break;
		case 4:
			CheckHeight(M26, land4);
			CheckLean(M26, land4);
			CalcHitPoint(M26, M26_shell, land4);
			break;
		}
		break;
	case 32:
		MoveChild(T32);
		MoveTank(T32, 35.f, 41.f, 9.01f, 5.25f, 5.f, 30.91f);
		if (camera.m_Rbtn == false) MoveHead( T32, 24.f);
		if (camera.m_Rbtn) MoveHeadFar(T32, 24.f);
		if (camera.m_Rbtn == false) MoveGun( T32, 20.f, 10.f);
		if (camera.m_Rbtn) MoveGunFar( T32, 20.f, 10.f);
		MoveShell(T32_shell, T32, 975.f,18.8f);
		CreateOBB(&T32obb, T32);
		CreateHeadOBB(&T32headobb, T32);
		CreateShellOBB(&T32Shellobb, T32_shell, T32);
		switch (num_stage)
		{
		case 1:
			CheckHeight(T32, land1);
			CheckLean(T32, land1);
			CalcHitPoint(T32, T32_shell, land1);
			break;
		case 2:
			CheckHeight(T32, land2);
			CheckLean(T32, land2);
			CalcHitPoint(T32, T32_shell, land2);
			break;
		case 3:
			CheckHeight(T32, land3);
			CheckLean(T32, land3);
			CalcHitPoint(T32, T32_shell, land3);
			break;
		case 4:
			CheckHeight(T32, land4);
			CheckLean(T32, land4);
			CalcHitPoint(T32, T32_shell, land4);
			break;
		}
		break;
	case 33:
		MoveChild(M46);
		MoveTank(M46, 47.f, 26.f, 12.5f, 7.96f, 11.f, 23.59f);
		if (camera.m_Rbtn == false) MoveHead( M46, 24.f);
		if (camera.m_Rbtn) MoveHeadFar( M46, 24.f);
		if (camera.m_Rbtn == false) MoveGun( M46, 20.f, 10.f);
		if (camera.m_Rbtn) MoveGunFar( M46, 20.f, 10.f);
		MoveShell(M46_shell, M46, 853.f,11.8f);
		CreateOBB(&M46obb, M46);
		CreateHeadOBB(&M46headobb, M46);
		CreateShellOBB(&M46Shellobb, M46_shell, M46);
		switch (num_stage)
		{
		case 1:
			CheckHeight(M46, land1);
			CheckLean(M46, land1);
			CalcHitPoint(M46, M46_shell, land1);
			break;
		case 2:
			CheckHeight(M46, land2);
			CheckLean(M46, land2);
			CalcHitPoint(M46, M46_shell, land2);
			break;
		case 3:
			CheckHeight(M46,land3);
			CheckLean(M46, land3);
			CalcHitPoint(M46, M46_shell, land3);
			break;
		case 4:
			CheckHeight(M46, land4);
			CheckLean(M46, land4);
			CalcHitPoint(M46, M46_shell, land4);
			break;
		}
		break;
	case 34:
		MoveChild(M103);
		MoveTank(M103, 33.f, 41.f, 8.94f, 5.08f, 5.f, 34.03f);
		if (camera.m_Rbtn == false) MoveHead(M103, 18.f);
		if (camera.m_Rbtn) MoveHeadFar( M103, 18.f);
		if (camera.m_Rbtn == false) MoveGun(M103, 15.f, 8.f);
		if (camera.m_Rbtn) MoveGunFar( M103, 15.f, 8.f);
		MoveShell(M103_shell, M103, 1067.f,26.5f);
		CreateOBB(&M103obb, M103);
		CreateHeadOBB(&M103headobb, M103);
		CreateShellOBB(&M103Shellobb, M103_shell, M103);
		switch (num_stage)
		{
		case 1:
			CheckHeight(M103, land1);
			CheckLean(M103, land1);
			CalcHitPoint(M103, M103_shell, land1);
			break;
		case 2:
			CheckHeight(M103, land2);
			CheckLean(M103, land2);
			CalcHitPoint(M103, M103_shell, land2);
			break;
		case 3:
			CheckHeight(M103, land3);
			CheckLean(M103, land3);
			CalcHitPoint(M103, M103_shell, land3);
			break;
		case 4:
			CheckHeight(M103, land4);
			CheckLean(M103, land4);
			CalcHitPoint(M103, M103_shell, land4);
			break;
		}
		break;
	}


	switch (num_stage)
	{
	case 1:
		switch (num_country)
		{
		case 1:
			MoveHeadEmy(EmyPantherG, 15.f);
			MoveGunEmy(EmyPantherG, 20.f, 8.f);
			CheckEmyHeight(EmyPantherG, land1);
			CheckEmyLean(EmyPantherG, land1);
			MoveChildEmy(EmyPantherG);
			MoveEnemy(EmyPantherG, 46.f, 41.f, 15.47f, 8.25f, 28.57f);
			PointToEnemy(EmyPantherG);
			break;
		case 2:
			MoveHeadEmy(EmyT44, 15.f);
			MoveGunEmy(EmyT44, 28.f, 5.f);
			CheckEmyHeight(EmyT44, land1);
			CheckEmyLean(EmyT44, land1);
			MoveChildEmy(EmyT44);
			MoveEnemy(EmyT44, 49.f, 36.f, 11.42f, 7.46f, 15.22f);
			PointToEnemy(EmyT44);
			break;
		}
		break;
	case 2:
		switch (num_country)
		{
		case 2:
			MoveHeadEmy(EmyM26, 24.f);
			MoveGunEmy(EmyM26, 20.f, 10.f);
			CheckEmyHeight(EmyM26, land2);
			CheckEmyLean(EmyM26, land2);
			MoveChildEmy(EmyM26);
			MoveEnemy(EmyM26, 46.f, 31.f, 18.46f, 6.08f, 20.72f);

			MoveHeadEmy(EmyT32, 24.f);
			MoveGunEmy(EmyT32, 20.f, 10.f);
			CheckEmyHeight(EmyT32, land2);
			CheckEmyLean(EmyT32, land2);
			MoveChildEmy(EmyT32);
			MoveEnemy(EmyT32, 35.f, 41.f, 9.01f, 5.25f, 30.91f);
			CheckAttackEmyEmy2(EmyM26, EmyT32, &M26Emyobb, &T32Emyobb);
			PointToEnemy2(EmyM26, EmyT32);
			break;
		case 3:
			MoveHeadEmy(EmyPantherG, 15.f);
			MoveGunEmy(EmyPantherG, 20.f, 8.f);
			CheckEmyHeight(EmyPantherG, land2);
			CheckEmyLean(EmyPantherG, land2);
			MoveChildEmy(EmyPantherG);
			MoveEnemy(EmyPantherG, 46.f, 41.f, 15.47f, 8.25f, 28.57f);

			MoveHeadEmy(EmyTiger, 7.5f);
			MoveGunEmy(EmyTiger, 16.f, 8.f);
			CheckEmyHeight(EmyTiger, land2);
			CheckEmyLean(EmyTiger, land2);
			MoveChildEmy(EmyTiger);
			MoveEnemy(EmyTiger, 45.f, 41.f, 21.38f, 5.9f, 37.78f);
			CheckAttackEmyEmy2(EmyPantherG, EmyTiger, &PantherGEmyobb, &TigerEmyobb);
			PointToEnemy2(EmyPantherG, EmyTiger);
			break;
		}
		break;
	case 3:
		switch (num_country)
		{
		case 1:
			MoveHeadEmy(EmyPantherII, 12.f);
			MoveGunEmy(EmyPantherII, 15.f, 8.f);
			CheckEmyHeight(EmyPantherII, land3);
			CheckEmyLean(EmyPantherII, land3);
			MoveChildEmy(EmyPantherII);
			MoveEnemy(EmyPantherII, 54.f, 41.f, 14.49f, 8.3f, 28.85f);

			MoveHeadEmy(EmyTiger, 7.5f);
			MoveGunEmy(EmyTiger, 16.f, 8.f);
			CheckEmyHeight(EmyTiger, land3);
			CheckEmyLean(EmyTiger, land3);
			MoveChildEmy(EmyTiger);
			MoveEnemy(EmyTiger, 45.f, 41.f, 21.38f, 5.9f, 37.78f);

			MoveHeadEmy(EmyPantherG, 15.f);
			MoveGunEmy(EmyPantherG, 20.f, 8.f);
			CheckEmyHeight(EmyPantherG, land3);
			CheckEmyLean(EmyPantherG, land3);
			MoveChildEmy(EmyPantherG);
			MoveEnemy(EmyPantherG, 46.f, 41.f, 15.47f, 8.25f, 28.57f);
			CheckAttackEmyEmy3(EmyPantherII, EmyTiger, EmyPantherG, &PantherIIEmyobb, &TigerEmyobb, &PantherGEmyobb);
			PointToEnemy3(EmyPantherII, EmyTiger, EmyPantherG);
			break;
		case 2:
			MoveHeadEmy(EmyT54, 10.f);
			MoveGunEmy(EmyT54, 17.f, 4.f);
			CheckEmyHeight(EmyT54, land3);
			CheckEmyLean(EmyT54, land3);
			MoveChildEmy(EmyT54);
			MoveEnemy(EmyT54, 45.f, 36.f, 10.65f, 5.74f, 18.2f);

			MoveHeadEmy(EmyIS1, 14.f);
			MoveGunEmy(EmyIS1, 25.f, 5.f);
			CheckEmyHeight(EmyIS1, land3);
			CheckEmyLean(EmyIS1, land3);
			MoveChildEmy(EmyIS1);
			MoveEnemy(EmyIS1, 38.f, 41.f, 13.39f, 5.33f, 38.04f);

			MoveHeadEmy(EmyT44, 15.f);
			MoveGunEmy(EmyT44, 28.f, 5.f);
			CheckEmyHeight(EmyT44, land3);
			CheckEmyLean(EmyT44, land3);
			MoveChildEmy(EmyT44);
			MoveEnemy(EmyT44, 49.f, 36.f, 11.42f, 7.46f, 15.22f);
			CheckAttackEmyEmy3(EmyT54, EmyIS1, EmyT44, &T54Emyobb, &IS1Emyobb, &T44Emyobb);
			PointToEnemy3(EmyT54, EmyIS1, EmyT44);
			break;
		}
		break;
	case 4:
		MoveHeadEmy(EmyIS3, 12.f);
		MoveGunEmy(EmyIS3, 19.f, 2.f);
		CheckEmyHeight(EmyIS3, land4);
		CheckEmyLean(EmyIS3, land4);
		MoveChildEmy(EmyIS3);
		MoveEnemy(EmyIS3, 38.f, 41.f, 15.81f, 5.53f, 38.07f);

		MoveHeadEmy(EmyT54, 10.f);
		MoveGunEmy(EmyT54, 17.f, 4.f);
		CheckEmyHeight(EmyT54, land4);
		CheckEmyLean(EmyT54, land4);
		MoveChildEmy(EmyT54);
		MoveEnemy(EmyT54, 45.f, 36.f, 10.65f, 5.74f, 18.2f);

		MoveHeadEmy(EmyM103, 18.f);
		MoveGunEmy(EmyM103, 15.f, 8.f);
		CheckEmyHeight(EmyM103, land4);
		CheckEmyLean(EmyM103, land4);
		MoveChildEmy(EmyM103);
		MoveEnemy(EmyM103, 33.f, 41.f, 8.94f, 5.08f, 34.03f);

		MoveHeadEmy(EmyM46, 24.f);
		MoveGunEmy(EmyM46, 20.f, 10.f);
		CheckEmyHeight(EmyM46, land4);
		CheckEmyLean(EmyM46, land4);
		MoveChildEmy(EmyM46);
		MoveEnemy(EmyM46, 47.f, 26.f, 12.5f, 7.96f, 23.59f);
		CheckAttackEmyEmy4(EmyIS3, EmyT54, EmyM103, EmyM46, &IS3Emyobb, &T54Emyobb, &M103Emyobb, &M46Emyobb);
		PointToEnemy4(EmyIS3, EmyT54, EmyM103, EmyM46);
		break;
	}

	DrawInGame();

	DWORD fpCurrTime = timeGetTime();
	fpTimeDelta = (float)(fpCurrTime - fpLastTime)*0.001f;
	CalcFPS(fpTimeDelta);

	if (ChechEnd()==false) game_time += fpTimeDelta;
	if (ChechEnd())
	{
		time += fpTimeDelta;
		if (time >= 3.f / FPS * 60.f)
		{
			DisposeInGame();
			time = 0.f;
		}
	}

	fpLastTime = fpCurrTime;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  描画
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
//  描画（前景）
/////////////////////////////////////////////////////////////////////////
void Draw2DFrontInGame(void)
{
	//描画処理開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//以下前景描画
	if (isHit) DrawTexture(lpTarget, (int)HitPoint.x - 32 / 2, (int)HitPoint.y - 32 / 2, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 256;
	rect.bottom = 36;
	char buf[20];
	sprintf((LPTSTR)(buf), "%.3f", FPS);
	DrawFPS(buf, &rect);

	if (camera.m_Rbtn == false) DrawTexture(lpCenter, 1920 / 2 - 64 / 2, 400 - 64 / 2, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
	if (camera.m_Rbtn) DrawTexture(lpSight, 0, 0, 1920.0f / 2048.0f, 1080.0f / 1024.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);

	switch (num_stage)
	{
	case 1:
		switch (num_tank / 10)
		{
		case 1:
			DrawTexture(lpPantherG, 1560, 20, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 35,1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 35, (float)EmyPantherG[eBODY].hp / (float)EmyPantherG[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyPantherG[eBODY].hp, &EmyPantherG[eBODY].hpmax));
			switch (num_tank % 10)
			{
			case 1:
				DrawTexture(lpT44, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)T44[myBODY].hp / (float)T44[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&T44[myBODY].hp, &T44[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&T44_shell.time, 8.5f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 2:
				DrawTexture(lpIS1, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)IS1[myBODY].hp / (float)IS1[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&IS1[myBODY].hp, &IS1[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&IS1_shell.time, 9.6f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 3:
				DrawTexture(lpT54, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)T54[myBODY].hp / (float)T54[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&T54[myBODY].hp, &T54[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&T54_shell.time, 16.3f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 4:
				DrawTexture(lpIS3, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)IS3[myBODY].hp / (float)IS3[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&IS3[myBODY].hp, &IS3[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&IS3_shell.time, 27.1f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			}
			break;
		case 2:
			DrawTexture(lpT44, 1560, 20, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 35, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 35, (float)EmyT44[eBODY].hp / (float)EmyT44[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyT44[eBODY].hp, &EmyT44[eBODY].hpmax));
			switch (num_tank % 10)
			{
			case 1:
				DrawTexture(lpPantherG, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)PantherG[myBODY].hp / (float)PantherG[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&PantherG[myBODY].hp, &PantherG[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&PantherG_shell.time, 11.2f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 2:
				DrawTexture(lpTiger, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)Tiger[myBODY].hp / (float)Tiger[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&Tiger[myBODY].hp, &Tiger[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&Tiger_shell.time, 10.8f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 3:
				DrawTexture(lpPantherII, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)PantherII[myBODY].hp / (float)PantherII[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&PantherII[myBODY].hp, &PantherII[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&PantherII_shell.time, 13.f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 4:
				DrawTexture(lpTigerII, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)TigerII[myBODY].hp / (float)TigerII[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&TigerII[myBODY].hp, &TigerII[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&TigerII_shell.time, 20.f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			}
			break;
		}
		break;
	case 2:
		switch (num_tank / 10)
		{
		case 2:
			DrawTexture(lpT32, 1560, 20, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 35, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 35, (float)EmyT32[eBODY].hp / (float)EmyT32[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyT32[eBODY].hp, &EmyT32[eBODY].hpmax));
			DrawTexture(lpM26, 1560, 90, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 105, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 105, (float)EmyM26[eBODY].hp / (float)EmyM26[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyM26[eBODY].hp, &EmyM26[eBODY].hpmax));
			switch (num_tank % 10)
			{
			case 1:
				DrawTexture(lpPantherG, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)PantherG[myBODY].hp / (float)PantherG[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&PantherG[myBODY].hp, &PantherG[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&PantherG_shell.time, 11.2f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 2:
				DrawTexture(lpTiger, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)Tiger[myBODY].hp / (float)Tiger[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&Tiger[myBODY].hp, &Tiger[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&Tiger_shell.time, 10.8f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 3:
				DrawTexture(lpPantherII, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)PantherII[myBODY].hp / (float)PantherII[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&PantherII[myBODY].hp, &PantherII[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&PantherII_shell.time, 13.f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 4:
				DrawTexture(lpTigerII, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)TigerII[myBODY].hp / (float)TigerII[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&TigerII[myBODY].hp, &TigerII[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&TigerII_shell.time, 20.f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			}
			break;
		case 3:
			DrawTexture(lpTiger, 1560, 20, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 35, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 35, (float)EmyTiger[eBODY].hp / (float)EmyTiger[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyTiger[eBODY].hp, &EmyTiger[eBODY].hpmax));
			DrawTexture(lpPantherG, 1560, 90, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 105, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 105, (float)EmyPantherG[eBODY].hp / (float)EmyPantherG[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyPantherG[eBODY].hp, &EmyPantherG[eBODY].hpmax));
			switch (num_tank % 10)
			{
			case 1:
				DrawTexture(lpM26, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)M26[myBODY].hp / (float)M26[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&M26[myBODY].hp, &M26[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&M26_shell.time, 11.8f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 2:
				DrawTexture(lpT32, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)T32[myBODY].hp / (float)T32[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&T32[myBODY].hp, &T32[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&T32_shell.time, 18.8f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 3:
				DrawTexture(lpM46, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)M46[myBODY].hp / (float)M46[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&M46[myBODY].hp, &M46[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&M46_shell.time, 11.8f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 4:
				DrawTexture(lpM103, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)M103[myBODY].hp / (float)M103[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&M103[myBODY].hp, &M103[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&M103_shell.time, 26.5f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			}
			break;
		}
		break;
	case 3:
		switch (num_tank / 10)
		{
		case 1:
			DrawTexture(lpPantherII, 1560, 20, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 35, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 35, (float)EmyPantherII[eBODY].hp / (float)EmyPantherII[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyPantherII[eBODY].hp, &EmyPantherII[eBODY].hpmax));
			DrawTexture(lpTiger, 1560, 90, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 105, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 105, (float)EmyTiger[eBODY].hp / (float)EmyTiger[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyTiger[eBODY].hp, &EmyTiger[eBODY].hpmax));
			DrawTexture(lpPantherG, 1560, 160, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 175, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 175, (float)EmyPantherG[eBODY].hp / (float)EmyPantherG[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyPantherG[eBODY].hp, &EmyPantherG[eBODY].hpmax));
			switch (num_tank % 10)
			{
			case 1:
				DrawTexture(lpT44, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)T44[myBODY].hp / (float)T44[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&T44[myBODY].hp, &T44[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&T44_shell.time, 8.5f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 2:
				DrawTexture(lpIS1, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)IS1[myBODY].hp / (float)IS1[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&IS1[myBODY].hp, &IS1[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&IS1_shell.time, 9.6f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 3:
				DrawTexture(lpT54, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)T54[myBODY].hp / (float)T54[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&T54[myBODY].hp, &T54[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&T54_shell.time, 16.3f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 4:
				DrawTexture(lpIS3, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)IS3[myBODY].hp / (float)IS3[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&IS3[myBODY].hp, &IS3[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&IS3_shell.time, 27.1f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			}
			break;
		case 2:
			DrawTexture(lpT54, 1560, 20, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 35, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 35, (float)EmyT54[eBODY].hp / (float)EmyT54[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyT54[eBODY].hp, &EmyT54[eBODY].hpmax));
			DrawTexture(lpIS1, 1560, 90, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 105, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 105, (float)EmyIS1[eBODY].hp / (float)EmyIS1[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyIS1[eBODY].hp, &EmyIS1[eBODY].hpmax));
			DrawTexture(lpT44, 1560, 160, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 1650, 175, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 1650, 175, (float)EmyT44[eBODY].hp / (float)EmyT44[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&EmyT44[eBODY].hp, &EmyT44[eBODY].hpmax));
			switch (num_tank % 10)
			{
			case 1:
				DrawTexture(lpPantherG, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)PantherG[myBODY].hp / (float)PantherG[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&PantherG[myBODY].hp, &PantherG[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&PantherG_shell.time, 11.2f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 2:
				DrawTexture(lpTiger, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)Tiger[myBODY].hp / (float)Tiger[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&Tiger[myBODY].hp, &Tiger[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&Tiger_shell.time, 10.8f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 3:
				DrawTexture(lpPantherII, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)PantherII[myBODY].hp / (float)PantherII[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&PantherII[myBODY].hp, &PantherII[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&PantherII_shell.time, 13.f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			case 4:
				DrawTexture(lpTigerII, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpHp, 180, 980, (float)TigerII[myBODY].hp / (float)TigerII[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
					        CalcHpBar(&TigerII[myBODY].hp, &TigerII[myBODY].hpmax));
				DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				DrawTexture(lpShell, 180, 1020, CalcShellBar(&TigerII_shell.time, 20.f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
				break;
			}
			break;
		}
		break;
	case 4:
		DrawTexture(lpIS3, 1560, 20, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpHp0, 1650, 35, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpHp, 1650, 35, (float)EmyIS3[eBODY].hp / (float)EmyIS3[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
			        CalcHpBar(&EmyIS3[eBODY].hp, &EmyIS3[eBODY].hpmax));
		DrawTexture(lpT54, 1560, 90, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpHp0, 1650, 105, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpHp, 1650, 105, (float)EmyT54[eBODY].hp / (float)EmyT54[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
			        CalcHpBar(&EmyT54[eBODY].hp, &EmyT54[eBODY].hpmax));
		DrawTexture(lpM103, 1560, 160, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpHp0, 1650, 175, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpHp, 1650, 175, (float)EmyM103[eBODY].hp / (float)EmyM103[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
			        CalcHpBar(&EmyM103[eBODY].hp, &EmyM103[eBODY].hpmax));
		DrawTexture(lpM46, 1560, 230, 80.0f / 256.0f, 50.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpHp0, 1650, 245, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpHp, 1650, 245, (float)EmyM46[eBODY].hp / (float)EmyM46[eBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
			        CalcHpBar(&EmyM46[eBODY].hp, &EmyM46[eBODY].hpmax));
		switch (num_tank % 10)
		{
		case 1:
			DrawTexture(lpPantherG, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 180, 980, (float)PantherG[myBODY].hp / (float)PantherG[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&PantherG[myBODY].hp, &PantherG[myBODY].hpmax));
			DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpShell, 180, 1020, CalcShellBar(&PantherG_shell.time, 11.2f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			break;
		case 2:
			DrawTexture(lpTiger, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 180, 980, (float)Tiger[myBODY].hp / (float)Tiger[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&Tiger[myBODY].hp, &Tiger[myBODY].hpmax));
			DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpShell, 180, 1020, CalcShellBar(&Tiger_shell.time, 10.8f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			break;
		case 3:
			DrawTexture(lpPantherII, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 180, 980, (float)PantherII[myBODY].hp / (float)PantherII[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&PantherII[myBODY].hp, &PantherII[myBODY].hpmax));
			DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpShell, 180, 1020, CalcShellBar(&PantherII_shell.time, 13.f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			break;
		case 4:
			DrawTexture(lpTigerII, 20, 950, 160.0f / 256.0f, 100.0f / 128.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp0, 180, 980, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpHp, 180, 980, (float)TigerII[myBODY].hp / (float)TigerII[myBODY].hpmax, 1.f, NULL, 0.0f, 0, 0, 0, 
				        CalcHpBar(&TigerII[myBODY].hp, &TigerII[myBODY].hpmax));
			DrawTexture(lpShell0, 180, 1020, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			DrawTexture(lpShell, 180, 1020, CalcShellBar(&TigerII_shell.time, 20.f), 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
			break;
		}
		break;
	}

	DrawTexture(lpPoint0, 1920 / 2 - 256, 35, 2.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
	DrawTexture(lpPoint, 1920 / 2 - 256, 35, CalcPointBar()*2.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFE1A67F);

	//以上前景描画
	//描画処理終了
	lpSprite->End();
}

/////////////////////////////////////////////////////////////////////////
//  描画（3D）
/////////////////////////////////////////////////////////////////////////
void Draw3DInGame(void)
{
	//以下に3D 描画
	Setup3DEnv();
	SetupLight();

	switch (num_tank)
	{
	case 11:
		For_a(T44);
		For_b(T44, 28.f, 5.f);
		if (camera.m_Rbtn) Camera_Far(&T44[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&T44[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(T44);
		DrawShell(T44_shell);
		PointToTank(T44);
		HpUpDown(T44);
		break;
	case 12:
		For_a(IS1);
		For_b(IS1, 25.f, 5.f);
		if (camera.m_Rbtn) Camera_Far(&IS1[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&IS1[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(IS1);
		DrawShell(IS1_shell);
		PointToTank(IS1);
		HpUpDown(IS1);
		break;
	case 13:
		For_a(T54);
		For_b(T54, 17.f, 4.f);
		if (camera.m_Rbtn) Camera_Far(&T54[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&T54[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(T54);
		DrawShell(T54_shell);
		PointToTank(T54);
		HpUpDown(T54);
		break;
	case 14:
		For_a(IS3);
		For_b(IS3, 19.f, 2.f);
		if (camera.m_Rbtn) Camera_Far(&IS3[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&IS3[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(IS3);
		DrawShell(IS3_shell);
		PointToTank(IS3);
		HpUpDown(IS3);
		break;
	case 21:
		For_a(PantherG);
		For_b(PantherG, 20.f, 8.f);
		if (camera.m_Rbtn) Camera_Far(&PantherG[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&PantherG[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(PantherG);
		DrawShell(PantherG_shell);
		PointToTank(PantherG);
		HpUpDown(PantherG);
		break;
	case 22:
		For_a(Tiger);
		For_b(Tiger, 16.f, 8.f);
		if (camera.m_Rbtn) Camera_Far(&Tiger[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&Tiger[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(Tiger);
		DrawShell(Tiger_shell);
		PointToTank(Tiger);
		HpUpDown(Tiger);
		break;
	case 23:
		For_a(PantherII);
		For_b(PantherII, 15.f, 8.f);
		if (camera.m_Rbtn) Camera_Far(&PantherII[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&PantherII[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(PantherII);
		DrawShell(PantherII_shell);
		PointToTank(PantherII);
		HpUpDown(PantherII);
		break;
	case 24:
		For_a(TigerII);
		For_b(TigerII, 15.f, 8.f);
		if (camera.m_Rbtn) Camera_Far(&TigerII[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&TigerII[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(TigerII);
		DrawShell(TigerII_shell);
		PointToTank(TigerII);
		HpUpDown(TigerII);
		break;
	case 31:
		For_a(M26);
		For_b(M26, 20.f, 10.f);
		if (camera.m_Rbtn) Camera_Far(&M26[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&M26[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(M26);
		DrawShell(M26_shell);
		PointToTank(M26);
		HpUpDown(M26);
		break;
	case 32:
		For_a(T32);
		For_b(T32, 20.f, 10.f);
		if (camera.m_Rbtn) Camera_Far(&T32[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&T32[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(T32);
		DrawShell(T32_shell);
		PointToTank(T32);
		HpUpDown(T32);
		break;
	case 33:
		For_a(M46);
		For_b(M46, 20.f, 10.f);
		if (camera.m_Rbtn) Camera_Far(&M46[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&M46[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(M46);
		DrawShell(M46_shell);
		PointToTank(M46);
		HpUpDown(M46);
		break;
	case 34:
		For_a(M103);
		For_b(M103, 15.f, 8.f);
		if (camera.m_Rbtn) Camera_Far(&M103[myHEAD].position);
		if (camera.m_Rbtn == false) SetupCamera(&M103[myHEAD].position);
		if (camera.m_Rbtn == false) DrawTank(M103);
		DrawShell(M103_shell);
		PointToTank(M103);
		HpUpDown(M103);
		break;
	}

	switch (num_stage)
	{
	case 1:
		DrawLand(land1);
		switch (num_tank/10)
		{
		case 1:
			DrawEnemy(EmyPantherG);
			DrawEmyShell(EmyPantherG_shell);
			MoveEmyShell(EmyPantherG_shell, EmyPantherG, 935.f, 11.2f);
			CreateEmyOBB(&PantherGEmyobb, EmyPantherG);
			CreateEmyHeadOBB(&PantherGEmyheadobb, EmyPantherG);
			CreateEmyShellOBB(&PantherGEmyShellobb, EmyPantherG_shell, EmyPantherG);
			switch (num_tank % 10)
			{
			case 1:
				For_c(EmyPantherG, T44);
				For_d(EmyPantherG, T44, 20.f, 8.f);
				For_e(EmyPantherG);
				CheckAttack(T44, EmyPantherG, &T44obb, &PantherGEmyobb);
				CheckAttackShell(T44_shell, EmyPantherG, &T44Shellobb, &PantherGEmyobb, &PantherGEmyheadobb);
				EmyDamage(EmyPantherG, T44, 132.f, 67.f);
				CheckAttackEmyShell(EmyPantherG_shell, T44, &PantherGEmyShellobb, &T44obb, &T44headobb);
				Damage(EmyPantherG, T44, 160.f, 97.f);
				break;
			case 2:
				For_c(EmyPantherG, IS1);
				For_d(EmyPantherG, IS1, 20.f, 8.f);
				For_e(EmyPantherG);
				CheckAttack(IS1, EmyPantherG, &IS1obb, &PantherGEmyobb);
				CheckAttackShell(IS1_shell, EmyPantherG, &IS1Shellobb, &PantherGEmyobb, &PantherGEmyheadobb);
				EmyDamage(EmyPantherG, IS1, 155.f, 104.f);
				CheckAttackEmyShell(EmyPantherG_shell, IS1, &PantherGEmyShellobb, &IS1obb, &IS1headobb);
				Damage(EmyPantherG, IS1, 160.f, 97.f);
				break;
			case 3:
				For_c(EmyPantherG, T54);
				For_d(EmyPantherG, T54, 20.f, 8.f);
				For_e(EmyPantherG);
				CheckAttack(T54, EmyPantherG, &T54obb,& PantherGEmyobb);
				CheckAttackShell(T54_shell, EmyPantherG, &T54Shellobb, &PantherGEmyobb, &PantherGEmyheadobb);
				EmyDamage(EmyPantherG, T54, 195.f, 144.f);
				CheckAttackEmyShell(EmyPantherG_shell, T54, &PantherGEmyShellobb, &T54obb, &T54headobb);
				Damage(EmyPantherG, T54, 160.f, 97.f);
				break;
			case 4:
				For_c(EmyPantherG, IS3);
				For_d(EmyPantherG, IS3, 20.f, 8.f);
				For_e(EmyPantherG);
				CheckAttack(IS3, EmyPantherG, &IS3obb, &PantherGEmyobb);
				CheckAttackShell(IS3_shell, EmyPantherG, &IS3Shellobb, &PantherGEmyobb, &PantherGEmyheadobb);
				EmyDamage(EmyPantherG, IS3, 207.f, 135.f);
				CheckAttackEmyShell(EmyPantherG_shell, IS3, &PantherGEmyShellobb, &IS3obb, &IS3headobb);
				Damage(EmyPantherG, IS3, 160.f, 97.f);
				break;
			}
			break;
		case 2:
			DrawEnemy(EmyT44);
			DrawEmyShell(EmyT44_shell);
			MoveEmyShell(EmyT44_shell, EmyT44, 792.f, 8.5f);
			CreateEmyOBB(&T44Emyobb, EmyT44);
			CreateEmyHeadOBB(&T44Emyheadobb, EmyT44);
			CreateEmyShellOBB(&T44EmyShellobb, EmyT44_shell, EmyT44);
			switch (num_tank % 10)
			{
			case 1:
				For_c(EmyT44, PantherG);
				For_d(EmyT44, PantherG, 28.f, 5.f);
				For_e(EmyT44);
				CheckAttack(PantherG, EmyT44, &PantherGobb, &T44Emyobb);
				CheckAttackShell(PantherG_shell, EmyT44, &PantherGShellobb, &T44Emyobb, &T44Emyheadobb);
				EmyDamage(EmyT44, PantherG, 160.f, 97.f);
				CheckAttackEmyShell(EmyT44_shell, PantherG, &T44EmyShellobb, &PantherGobb, &PantherGheadobb);
				Damage(EmyT44, PantherG, 132.f, 67.f);
				break;
			case 2:
				For_c(EmyT44, Tiger);
				For_d(EmyT44, Tiger, 28.f, 5.f);
				For_e(EmyT44);
				CheckAttack(Tiger, EmyT44, &Tigerobb, &T44Emyobb);
				CheckAttackShell(Tiger_shell, EmyT44, &TigerShellobb, &T44Emyobb, &T44Emyheadobb);
				EmyDamage(EmyT44, Tiger, 170.f, 110.f);
				CheckAttackEmyShell(EmyT44_shell, Tiger, &T44EmyShellobb, &Tigerobb, &Tigerheadobb);
				Damage(EmyT44, Tiger, 132.f, 67.f);
				break;
			case 3:
				For_c(EmyT44, PantherII);
				For_d(EmyT44, PantherII, 28.f, 5.f);
				For_e(EmyT44);
				CheckAttack(PantherII, EmyT44, &PantherIIobb, &T44Emyobb);
				CheckAttackShell(PantherII_shell, EmyT44, &PantherIIShellobb, &T44Emyobb, &T44Emyheadobb);
				EmyDamage(EmyT44, PantherII, 225.f, 150.f);
				CheckAttackEmyShell(EmyT44_shell, PantherII, &T44EmyShellobb, &PantherIIobb, &PantherIIheadobb);
				Damage(EmyT44, PantherII, 132.f, 67.f);
				break;
			case 4:
				For_c(EmyT44, TigerII);
				For_d(EmyT44, TigerII, 28.f, 5.f);
				For_e(EmyT44);
				CheckAttack(TigerII, EmyT44, &TigerIIobb, &T44Emyobb);
				CheckAttackShell(TigerII_shell, EmyT44, &TigerIIShellobb, &T44Emyobb, &T44Emyheadobb);
				EmyDamage(EmyT44, TigerII, 240.f, 167.f);
				CheckAttackEmyShell(EmyT44_shell, TigerII, &T44EmyShellobb, &TigerIIobb, &TigerIIheadobb);
				Damage(EmyT44, TigerII, 132.f, 67.f);
				break;
			}
			break;
		}
		break;
	case 2:
		DrawLand(land2);
		switch (num_tank/10)
		{
		case 2:
			DrawEnemy(EmyT32);
			DrawEmyShell(EmyT32_shell);
			MoveEmyShell(EmyT32_shell, EmyT32, 975.f, 18.8f);
			CreateEmyOBB(&T32Emyobb, EmyT32);
			CreateEmyHeadOBB(&T32Emyheadobb, EmyT32);
			CreateEmyShellOBB(&T32EmyShellobb, EmyT32_shell, EmyT32);

			DrawEnemy(EmyM26);
			DrawEmyShell(EmyM26_shell);
			MoveEmyShell(EmyM26_shell, EmyM26, 853.f, 11.8f);
			CreateEmyOBB(&M26Emyobb, EmyM26);
			CreateEmyHeadOBB(&M26Emyheadobb, EmyM26);
			CreateEmyShellOBB(&M26EmyShellobb, EmyM26_shell, EmyM26);
			switch (num_tank % 10)
			{
			case 1:
				For_c(EmyT32, PantherG);
				For_d(EmyT32, PantherG, 20.f, 10.f);
				For_e(EmyT32);
				EmyDamage(EmyT32, PantherG, 160.f, 97.f);

				For_c(EmyM26, PantherG);
				For_d(EmyM26, PantherG, 20.f, 10.f);
				For_e(EmyM26);
				EmyDamage(EmyM26, PantherG, 157.f, 122.f);
				CheckAttack2(PantherG, EmyM26, EmyT32, &PantherGobb, &M26Emyobb, &T32Emyobb);
				CheckAttackShell2(PantherG_shell, EmyT32, EmyM26, &PantherGShellobb, &T32Emyobb, &T32Emyheadobb, &M26Emyobb, &M26Emyheadobb);
				CheckAttackEmyShell2(EmyT32_shell, EmyM26_shell, PantherG, &T32EmyShellobb, &M26EmyShellobb, &PantherGobb, &PantherGheadobb);
				Damage2(EmyT32, EmyM26, PantherG, 183.f, 143.f, 157.f, 122.f);
				break;
			case 2:
				For_c(EmyT32, Tiger);
				For_d(EmyT32, Tiger, 20.f, 10.f);
				For_e(EmyT32);
				EmyDamage(EmyT32, Tiger, 170.f, 110.f);

				For_c(EmyM26, Tiger);
				For_d(EmyM26, Tiger, 20.f, 10.f);
				For_e(EmyM26);
				EmyDamage(EmyM26, Tiger, 170.f, 110.f);
				CheckAttack2(Tiger, EmyM26, EmyT32, &Tigerobb, &M26Emyobb, &T32Emyobb);
				CheckAttackShell2(Tiger_shell, EmyT32, EmyM26, &TigerShellobb, &T32Emyobb, &T32Emyheadobb, &M26Emyobb, &M26Emyheadobb);
				CheckAttackEmyShell2(EmyT32_shell, EmyM26_shell, Tiger, &T32EmyShellobb, &M26EmyShellobb, &Tigerobb, &Tigerheadobb);
				Damage2(EmyT32, EmyM26, Tiger, 183.f, 143.f, 157.f, 122.f);
				break;
			case 3:
				For_c(EmyT32, PantherII);
				For_d(EmyT32, PantherII, 20.f, 10.f);
				For_e(EmyT32);
				EmyDamage(EmyT32, PantherII, 225.f, 150.f);

				For_c(EmyM26, PantherII);
				For_d(EmyM26, PantherII, 20.f, 10.f);
				For_e(EmyM26);
				EmyDamage(EmyM26, PantherII, 225.f, 150.f);
				CheckAttack2(PantherII, EmyM26, EmyT32, &PantherIIobb, &M26Emyobb, &T32Emyobb);
				CheckAttackShell2(PantherII_shell, EmyT32, EmyM26, &PantherIIShellobb, &T32Emyobb, &T32Emyheadobb, &M26Emyobb, &M26Emyheadobb);
				CheckAttackEmyShell2(EmyT32_shell, EmyM26_shell, PantherII, &T32EmyShellobb, &M26EmyShellobb, &PantherIIobb, &PantherIIheadobb);
				Damage2(EmyT32, EmyM26, PantherII, 183.f, 143.f, 157.f, 122.f);
				break;
			case 4:
				For_c(EmyT32, TigerII);
				For_d(EmyT32, TigerII, 20.f, 10.f);
				For_e(EmyT32);
				EmyDamage(EmyT32, TigerII, 240.f, 167.f);

				For_c(EmyM26, TigerII);
				For_d(EmyM26, TigerII, 20.f, 10.f);
				For_e(EmyM26);
				EmyDamage(EmyM26, TigerII, 240.f, 167.f);
				CheckAttack2(TigerII, EmyM26, EmyT32, &TigerIIobb, &M26Emyobb, &T32Emyobb);
				CheckAttackShell2(TigerII_shell, EmyT32, EmyM26, &TigerIIShellobb, &T32Emyobb, &T32Emyheadobb, &M26Emyobb, &M26Emyheadobb);
				CheckAttackEmyShell2(EmyT32_shell, EmyM26_shell, TigerII, &T32EmyShellobb, &M26EmyShellobb, &TigerIIobb, &TigerIIheadobb);
				Damage2(EmyT32, EmyM26, TigerII, 183.f, 143.f, 157.f, 122.f);
				break;
			}
			break;
		case 3:
			DrawEnemy(EmyTiger);
			DrawEmyShell(EmyTiger_shell);
			MoveEmyShell(EmyTiger_shell, EmyTiger, 773.f, 10.8f);
			CreateEmyOBB(&TigerEmyobb, EmyTiger);
			CreateEmyHeadOBB(&TigerEmyheadobb, EmyTiger);
			CreateEmyShellOBB(&TigerEmyShellobb, EmyTiger_shell, EmyTiger);

			DrawEnemy(EmyPantherG);
			DrawEmyShell(EmyPantherG_shell);
			MoveEmyShell(EmyPantherG_shell, EmyPantherG, 935.f, 11.2f);
			CreateEmyOBB(&PantherGEmyobb, EmyPantherG);
			CreateEmyHeadOBB(&PantherGEmyheadobb, EmyPantherG);
			CreateEmyShellOBB(&PantherGEmyShellobb, EmyPantherG_shell, EmyPantherG);
			switch (num_tank % 10)
			{
			case 1:
				For_c(EmyTiger, M26);
				For_d(EmyTiger, M26, 16.f, 8.f);
				For_e(EmyTiger);
				EmyDamage(EmyTiger, M26, 157.f, 122.f);

				For_c(EmyPantherG, M26);
				For_d(EmyPantherG, M26, 20.f, 8.f);
				For_e(EmyPantherG);
				EmyDamage(EmyPantherG, M26, 157.f, 122.f);
				CheckAttack2(M26, EmyTiger, EmyPantherG, &M26obb, &TigerEmyobb, &PantherGEmyobb);
				CheckAttackShell2(M26_shell, EmyTiger, EmyPantherG, &M26Shellobb, &TigerEmyobb, &TigerEmyheadobb, 
					              &PantherGEmyobb, &PantherGEmyheadobb);
				CheckAttackEmyShell2(EmyTiger_shell, EmyPantherG_shell, M26, &TigerEmyShellobb, &PantherGEmyShellobb, &M26obb, &M26headobb);
				Damage2(EmyTiger, EmyPantherG, M26, 170.f, 110.f, 160.f, 97.f);
				break;
			case 2:
				For_c(EmyTiger, T32);
				For_d(EmyTiger, T32, 16.f, 8.f);
				For_e(EmyTiger);
				EmyDamage(EmyTiger, T32, 183.f, 143.f);

				For_c(EmyPantherG, T32);
				For_d(EmyPantherG, T32, 20.f, 8.f);
				For_e(EmyPantherG);
				EmyDamage(EmyPantherG, T32, 183.f, 143.f);
				CheckAttack2(T32, EmyTiger, EmyPantherG, &T32obb, &TigerEmyobb, &PantherGEmyobb);
				CheckAttackShell2(T32_shell, EmyTiger, EmyPantherG, &T32Shellobb, &TigerEmyobb, &TigerEmyheadobb, 
					              &PantherGEmyobb, &PantherGEmyheadobb);
				CheckAttackEmyShell2(EmyTiger_shell, EmyPantherG_shell, T32, &TigerEmyShellobb, &PantherGEmyShellobb, &T32obb, &T32headobb);
				Damage2(EmyTiger, EmyPantherG, T32, 170.f, 110.f, 160.f, 97.f);
				break;
			case 3:
				For_c(EmyTiger, M46);
				For_d(EmyTiger, M46, 16.f, 8.f);
				For_e(EmyTiger);
				EmyDamage(EmyTiger, M46, 157.f, 122.f);

				For_c(EmyPantherG, M46);
				For_d(EmyPantherG, M46, 20.f, 8.f);
				For_e(EmyPantherG);
				EmyDamage(EmyPantherG, M46, 157.f, 122.f);
				CheckAttack2(M46, EmyTiger, EmyPantherG, &M46obb, &TigerEmyobb, &PantherGEmyobb);
				CheckAttackShell2(M46_shell, EmyTiger, EmyPantherG, &M46Shellobb, &TigerEmyobb, &TigerEmyheadobb, 
					              &PantherGEmyobb, &PantherGEmyheadobb);
				CheckAttackEmyShell2(EmyTiger_shell, EmyPantherG_shell, M46, &TigerEmyShellobb, &PantherGEmyShellobb, &M46obb, &M46headobb);
				Damage2(EmyTiger, EmyPantherG, M46, 170.f, 110.f, 160.f, 97.f);
				break;
			case 4:
				For_c(EmyTiger, M103);
				For_d(EmyTiger, M103, 16.f, 8.f);
				For_e(EmyTiger);
				EmyDamage(EmyTiger, M103, 269.f, 217.f);

				For_c(EmyPantherG, M103);
				For_d(EmyPantherG, M103, 20.f, 8.f);
				For_e(EmyPantherG);
				EmyDamage(EmyPantherG, M103, 269.f, 217.f);
				CheckAttack2(M103, EmyTiger, EmyPantherG, &M103obb, &TigerEmyobb, &PantherGEmyobb);
				CheckAttackShell2(M103_shell, EmyTiger, EmyPantherG, &M103Shellobb, &TigerEmyobb, &TigerEmyheadobb, 
					              &PantherGEmyobb, &PantherGEmyheadobb);
				CheckAttackEmyShell2(EmyTiger_shell, EmyPantherG_shell, M103, &TigerEmyShellobb, &PantherGEmyShellobb, &M103obb, &M103headobb);
				Damage2(EmyTiger, EmyPantherG, M103, 170.f, 110.f, 160.f, 97.f);
				break;
			}
			break;
		}
		break;
	case 3:
		DrawLand(land3);
		switch (num_tank/10)
		{
		case 1:
			DrawEnemy(EmyPantherII);
			DrawEmyShell(EmyPantherII_shell);
			MoveEmyShell(EmyPantherII_shell, EmyPantherII, 1000.f, 13.f);
			CreateEmyOBB(&PantherIIEmyobb, EmyPantherII);
			CreateEmyHeadOBB(&PantherIIEmyheadobb, EmyPantherII);
			CreateEmyShellOBB(&PantherIIEmyShellobb, EmyPantherII_shell, EmyPantherII);

			DrawEnemy(EmyTiger);
			DrawEmyShell(EmyTiger_shell);
			MoveEmyShell(EmyTiger_shell, EmyTiger, 773.f, 10.8f);
			CreateEmyOBB(&TigerEmyobb, EmyTiger);
			CreateEmyHeadOBB(&TigerEmyheadobb, EmyTiger);
			CreateEmyShellOBB(&TigerEmyShellobb, EmyTiger_shell, EmyTiger);

			DrawEnemy(EmyPantherG);
			DrawEmyShell(EmyPantherG_shell);
			MoveEmyShell(EmyPantherG_shell, EmyPantherG, 935.f, 11.2f);
			CreateEmyOBB(&PantherGEmyobb, EmyPantherG);
			CreateEmyHeadOBB(&PantherGEmyheadobb, EmyPantherG);
			CreateEmyShellOBB(&PantherGEmyShellobb, EmyPantherG_shell, EmyPantherG);
			switch (num_tank % 10)
			{
			case 1:
				For_c(EmyPantherII, T44);
				For_d(EmyPantherII, T44, 15.f, 8.f);
				For_e(EmyPantherII);
				EmyDamage(EmyPantherII, T44, 132.f, 67.f);

				For_c(EmyTiger, T44);
				For_d(EmyTiger, T44, 16.f, 8.f);
				For_e(EmyTiger);
				EmyDamage(EmyTiger, T44, 132.f, 67.f);

				For_c(EmyPantherG, T44);
				For_d(EmyPantherG, T44, 20.f, 8.f);
				For_e(EmyPantherG);
				EmyDamage(EmyPantherG, T44, 132.f, 67.f);
				CheckAttack3(T44, EmyPantherII, EmyTiger, EmyPantherG, &T44obb, &PantherIIEmyobb, &TigerEmyobb, &PantherGEmyobb);
				CheckAttackShell3(T44_shell, EmyPantherII, EmyTiger, EmyPantherG, &T44Shellobb, &PantherIIEmyobb, &PantherIIEmyheadobb, 
					              &TigerEmyobb, &TigerEmyheadobb, &PantherGEmyobb, &PantherGEmyheadobb);
				CheckAttackEmyShell3(EmyPantherII_shell, EmyTiger_shell, EmyPantherG_shell, T44, &PantherIIEmyShellobb,
					&TigerEmyShellobb, &PantherGEmyShellobb, &T44obb, &T44headobb);
				Damage3(EmyPantherII, EmyTiger, EmyPantherG, T44, 225.f, 150.f, 170.f, 110.f, 160.f, 97.f);
				break;
			case 2:
				For_c(EmyPantherII, IS1);
				For_d(EmyPantherII, IS1, 15.f, 8.f);
				For_e(EmyPantherII);
				EmyDamage(EmyPantherII, IS1, 155.f, 104.f);

				For_c(EmyTiger, IS1);
				For_d(EmyTiger, IS1, 16.f, 8.f);
				For_e(EmyTiger);
				EmyDamage(EmyTiger, IS1, 155.f, 104.f);

				For_c(EmyPantherG, IS1);
				For_d(EmyPantherG, IS1, 20.f, 8.f);
				For_e(EmyPantherG);
				EmyDamage(EmyPantherG, IS1, 155.f, 104.f);
				CheckAttack3(IS1, EmyPantherII, EmyTiger, EmyPantherG, &IS1obb, &PantherIIEmyobb, &TigerEmyobb, &PantherGEmyobb);
				CheckAttackShell3(IS1_shell, EmyPantherII, EmyTiger, EmyPantherG, &IS1Shellobb, &PantherIIEmyobb, &PantherIIEmyheadobb, 
					              &TigerEmyobb, &TigerEmyheadobb, &PantherGEmyobb, &PantherGEmyheadobb);
				CheckAttackEmyShell3(EmyPantherII_shell, EmyTiger_shell, EmyPantherG_shell, IS1, &PantherIIEmyShellobb,
					                 &TigerEmyShellobb, &PantherGEmyShellobb, &IS1obb, &IS1headobb);
				Damage3(EmyPantherII, EmyTiger, EmyPantherG, IS1, 225.f, 150.f, 170.f, 110.f, 160.f, 97.f);
				break;
			case 3:
				For_c(EmyPantherII, T54);
				For_d(EmyPantherII, T54, 15.f, 8.f);
				For_e(EmyPantherII);
				EmyDamage(EmyPantherII, T54, 215.f, 144.f);

				For_c(EmyTiger, T54);
				For_d(EmyTiger, T54, 16.f, 8.f);
				For_e(EmyTiger);
				EmyDamage(EmyTiger, T54, 215.f, 144.f);

				For_c(EmyPantherG, T54);
				For_d(EmyPantherG, T54, 20.f, 8.f);
				For_e(EmyPantherG);
				EmyDamage(EmyPantherG, T54, 215.f, 144.f);
				CheckAttack3(T54, EmyPantherII, EmyTiger, EmyPantherG, &T54obb, &PantherIIEmyobb, &TigerEmyobb, &PantherGEmyobb);
				CheckAttackShell3(T54_shell, EmyPantherII, EmyTiger, EmyPantherG, &T54Shellobb, &PantherIIEmyobb, &PantherIIEmyheadobb, 
					              &TigerEmyobb, &TigerEmyheadobb, &PantherGEmyobb, &PantherGEmyheadobb);
				CheckAttackEmyShell3(EmyPantherII_shell, EmyTiger_shell, EmyPantherG_shell, T54, &PantherIIEmyShellobb,
					                 &TigerEmyShellobb, &PantherGEmyShellobb, &T54obb, &T54headobb);
				Damage3(EmyPantherII, EmyTiger, EmyPantherG, T54, 225.f, 150.f, 170.f, 110.f, 160.f, 97.f);
				break;
			case 4:
				For_c(EmyPantherII, IS3);
				For_d(EmyPantherII, IS3, 15.f, 8.f);
				For_e(EmyPantherII);
				EmyDamage(EmyPantherII, IS3, 207.f, 135.f);

				For_c(EmyTiger, IS3);
				For_d(EmyTiger, IS3, 16.f, 8.f);
				For_e(EmyTiger);
				EmyDamage(EmyTiger, IS3, 207.f, 135.f);

				For_c(EmyPantherG, IS3);
				For_d(EmyPantherG, IS3, 20.f, 8.f);
				For_e(EmyPantherG);
				EmyDamage(EmyPantherG, IS3, 207.f, 135.f);
				CheckAttack3(IS3, EmyPantherII, EmyTiger, EmyPantherG, &IS3obb, &PantherIIEmyobb, &TigerEmyobb, &PantherGEmyobb);
				CheckAttackShell3(IS3_shell, EmyPantherII, EmyTiger, EmyPantherG, &IS3Shellobb, &PantherIIEmyobb, &PantherIIEmyheadobb, 
					              &TigerEmyobb, &TigerEmyheadobb, &PantherGEmyobb, &PantherGEmyheadobb);
				CheckAttackEmyShell3(EmyPantherII_shell, EmyTiger_shell, EmyPantherG_shell, IS3, &PantherIIEmyShellobb,
					                 &TigerEmyShellobb, &PantherGEmyShellobb, &IS3obb, &IS3headobb);
				Damage3(EmyPantherII, EmyTiger, EmyPantherG, IS3, 225.f, 150.f, 170.f, 110.f, 160.f, 97.f);
				break;
			}
			break;
		case 2:
			DrawEnemy(EmyT54);
			DrawEmyShell(EmyT54_shell);
			MoveEmyShell(EmyT54_shell, EmyT54, 887.f, 16.3f);
			CreateEmyOBB(&T54Emyobb, EmyT54);
			CreateEmyHeadOBB(&T54Emyheadobb, EmyT54);
			CreateEmyShellOBB(&T54EmyShellobb, EmyT54_shell, EmyT54);

			DrawEnemy(EmyIS1);
			DrawEmyShell(EmyIS1_shell);
			MoveEmyShell(EmyIS1_shell, EmyIS1, 792.f, 9.6f);
			CreateEmyOBB(&IS1Emyobb, EmyIS1);
			CreateEmyHeadOBB(&IS1Emyheadobb, EmyIS1);
			CreateEmyShellOBB(&IS1EmyShellobb, EmyIS1_shell, EmyIS1);

			DrawEnemy(EmyT44);
			DrawEmyShell(EmyT44_shell);
			MoveEmyShell(EmyT44_shell, EmyT44, 792.f, 8.5f);
			CreateEmyOBB(&T44Emyobb, EmyT44);
			CreateEmyHeadOBB(&T44Emyheadobb, EmyT44);
			CreateEmyShellOBB(&T44EmyShellobb, EmyT44_shell, EmyT44);
			switch (num_tank % 10)
			{
			case 1:
				For_c(EmyT54, PantherG);
				For_d(EmyT54, PantherG, 17.f, 4.f);
				For_e(EmyT54);
				EmyDamage(EmyT54, PantherG, 160.f, 97.f);

				For_c(EmyIS1, PantherG);
				For_d(EmyIS1, PantherG, 25.f, 5.f);
				For_e(EmyIS1);
				EmyDamage(EmyIS1, PantherG, 160.f, 97.f);

				For_c(EmyT44, PantherG);
				For_d(EmyT44, PantherG, 28.f, 5.f);
				EmyDamage(EmyT44, PantherG, 160.f, 97.f);
				CheckAttack3(PantherG, EmyT54, EmyIS1, EmyT44, &PantherGobb, &T54Emyobb, &IS1Emyobb, &T44Emyobb);
				CheckAttackShell3(PantherG_shell, EmyT54, EmyIS1, EmyT44, &PantherGShellobb, &T54Emyobb, &T54Emyheadobb, &IS1Emyobb, 
					              &IS1Emyheadobb, &T44Emyobb, &T44Emyheadobb);
				CheckAttackEmyShell3(EmyT54_shell, EmyIS1_shell, EmyT44_shell, PantherG, &T54EmyShellobb,
					                 &IS1EmyShellobb, &T44EmyShellobb, &PantherGobb, &PantherGheadobb);
				Damage3(EmyT54, EmyIS1, EmyT44, PantherG, 215.f, 144.f, 155.f, 104.f, 132.f, 67.f);
				break;
			case 2:
				For_c(EmyT54, Tiger);
				For_d(EmyT54, Tiger, 17.f, 4.f);
				For_e(EmyT54);
				EmyDamage(EmyT54, Tiger, 130.f, 70.f);

				For_c(EmyIS1, Tiger);
				For_d(EmyIS1, Tiger, 25.f, 5.f);
				For_e(EmyIS1);
				EmyDamage(EmyIS1, Tiger, 130.f, 70.f);

				For_c(EmyT44, Tiger);
				For_d(EmyT44, Tiger, 28.f, 5.f);
				For_e(EmyT44);
				EmyDamage(EmyT44, Tiger, 130.f, 70.f);
				CheckAttack3(Tiger, EmyT54, EmyIS1, EmyT44, &Tigerobb, &T54Emyobb, &IS1Emyobb, &T44Emyobb);
				CheckAttackShell3(Tiger_shell, EmyT54, EmyIS1, EmyT44, &TigerShellobb, &T54Emyobb, &T54Emyheadobb, &IS1Emyobb, 
					              &IS1Emyheadobb, &T44Emyobb, &T44Emyheadobb);
				CheckAttackEmyShell3(EmyT54_shell, EmyIS1_shell, EmyT44_shell, Tiger, &T54EmyShellobb,
					                 &IS1EmyShellobb, &T44EmyShellobb, &Tigerobb, &Tigerheadobb);
				Damage3(EmyT54, EmyIS1, EmyT44, Tiger, 215.f, 144.f, 155.f, 104.f, 132.f, 67.f);
				break;
			case 3:
				For_c(EmyT54, PantherII);
				For_d(EmyT54, PantherII, 17.f, 4.f);
				For_e(EmyT54);
				EmyDamage(EmyT54, PantherII, 225.f, 150.f);

				For_c(EmyIS1, PantherII);
				For_d(EmyIS1, PantherII, 25.f, 5.f);
				For_e(EmyIS1);
				EmyDamage(EmyIS1, PantherII, 225.f, 150.f);

				For_c(EmyT44, PantherII);
				For_d(EmyT44, PantherII, 28.f, 5.f);
				For_e(EmyT44);
				EmyDamage(EmyT44, PantherII, 225.f, 150.f);
				CheckAttack3(PantherII, EmyT54, EmyIS1, EmyT44, &PantherIIobb, &T54Emyobb, &IS1Emyobb, &T44Emyobb);
				CheckAttackShell3(PantherII_shell, EmyT54, EmyIS1, EmyT44, &PantherIIShellobb, &T54Emyobb, &T54Emyheadobb, &IS1Emyobb, 
					              &IS1Emyheadobb, &T44Emyobb, &T44Emyheadobb);
				CheckAttackEmyShell3(EmyT54_shell, EmyIS1_shell, EmyT44_shell, PantherII, &T54EmyShellobb,
					                 &IS1EmyShellobb, &T44EmyShellobb, &PantherIIobb, &PantherIIheadobb);
				Damage3(EmyT54, EmyIS1, EmyT44, PantherII, 215.f, 144.f, 155.f, 104.f, 132.f, 67.f);
				break;
			case 4:
				For_c(EmyT54, TigerII);
				For_d(EmyT54, TigerII, 17.f, 4.f);
				For_e(EmyT54);
				EmyDamage(EmyT54, TigerII, 240.f, 167.f);

				For_c(EmyIS1, TigerII);
				For_d(EmyIS1, TigerII, 25.f, 5.f);
				For_e(EmyIS1);
				EmyDamage(EmyIS1, TigerII, 240.f, 167.f);

				For_c(EmyT44, TigerII);
				For_d(EmyT44, TigerII, 28.f, 5.f);
				For_e(EmyT44);
				EmyDamage(EmyT44, TigerII, 240.f, 167.f);
				CheckAttack3(TigerII, EmyT54, EmyIS1, EmyT44, &TigerIIobb, &T54Emyobb, &IS1Emyobb, &T44Emyobb);
				CheckAttackShell3(TigerII_shell, EmyT54, EmyIS1, EmyT44, &TigerIIShellobb, &T54Emyobb, &T54Emyheadobb, &IS1Emyobb, 
					              &IS1Emyheadobb, &T44Emyobb, &T44Emyheadobb);
				CheckAttackEmyShell3(EmyT54_shell, EmyIS1_shell, EmyT44_shell, TigerII, &T54EmyShellobb,
					                 &IS1EmyShellobb, &T44EmyShellobb, &TigerIIobb, &TigerIIheadobb);
				Damage3(EmyT54, EmyIS1, EmyT44, TigerII, 215.f, 144.f, 155.f, 104.f, 132.f, 67.f);
				break;
			}
			break;
		}
		break;
	case 4:
		DrawLand(land4);

		DrawEnemy(EmyIS3);
		DrawEmyShell(EmyIS3_shell);
		MoveEmyShell(EmyIS3_shell, EmyIS3, 800.f, 27.1f);
		CreateEmyOBB(&IS3Emyobb, EmyIS3);
		CreateEmyHeadOBB(&IS3Emyheadobb, EmyIS3);
		CreateEmyShellOBB(&IS3EmyShellobb, EmyIS3_shell, EmyIS3);

		DrawEnemy(EmyT54);
		DrawEmyShell(EmyT54_shell);
		MoveEmyShell(EmyT54_shell, EmyT54, 887.f, 16.3f);
		CreateEmyOBB(&T54Emyobb, EmyT54);
		CreateEmyHeadOBB(&T54Emyheadobb, EmyT54);
		CreateEmyShellOBB(&T54EmyShellobb, EmyT54_shell, EmyT54);

		DrawEnemy(EmyM103);
		DrawEmyShell(EmyM103_shell);
		MoveEmyShell(EmyM103_shell, EmyM103, 1067.f, 26.5f);
		CreateEmyOBB(&M103Emyobb, EmyM103);
		CreateEmyHeadOBB(&M103Emyheadobb, EmyM103);
		CreateEmyShellOBB(&M103EmyShellobb, EmyM103_shell, EmyM103);

		DrawEnemy(EmyM46);
		DrawEmyShell(EmyM46_shell);
		MoveEmyShell(EmyM46_shell, EmyM46, 853.f, 11.8f);
		CreateEmyOBB(&M46Emyobb, EmyM46);
		CreateEmyHeadOBB(&M46Emyheadobb, EmyM46);
		CreateEmyShellOBB(&M46EmyShellobb, EmyM46_shell, EmyM46);

		switch (num_tank%10)
		{
		case 1:
			For_c(EmyIS3, PantherG);
			For_d(EmyIS3, PantherG, 19.f, 2.f);
			For_e(EmyIS3);
			EmyDamage(EmyIS3, PantherG, 160.f, 97.f);

			For_c(EmyT54, PantherG);
			For_d(EmyT54, PantherG, 17.f, 4.f);
			For_e(EmyT54);
			EmyDamage(EmyT54, PantherG, 160.f, 97.f);

			For_c(EmyM103, PantherG);
			For_d(EmyM103, PantherG, 15.f, 8.f);
			For_e(EmyM103);
			EmyDamage(EmyM103, PantherG, 160.f, 97.f);

			For_c(EmyM46, PantherG);
			For_d(EmyM46, PantherG, 20.f, 10.f);
			For_e(EmyM46);
			EmyDamage(EmyM46, PantherG, 160.f, 97.f);
			CheckAttack4(PantherG, EmyIS3, EmyT54, EmyM103, EmyM46, &PantherGobb, &IS3Emyobb, &T54Emyobb, &M103Emyobb, &M46Emyobb);
			CheckAttackShell4(PantherG_shell, EmyIS3, EmyT54, EmyM103, EmyM46, &PantherGShellobb, &IS3Emyobb, &IS3Emyheadobb, &T54Emyobb, 
				              &T54Emyheadobb, &M103Emyobb, &M103Emyheadobb, &M46Emyobb, &M46Emyheadobb);
			CheckAttackEmyShell4(EmyIS3_shell, EmyT54_shell, EmyM103_shell, EmyM46_shell, PantherG, &IS3EmyShellobb,
				                 &T54EmyShellobb, &M103EmyShellobb, &M46EmyShellobb, &PantherGobb, &PantherGheadobb);
			Damage4(EmyIS3, EmyT54, EmyM103, EmyM46, PantherG, 207.f, 135.f, 215.f, 144.f, 269.f, 217.f, 157.f, 122.f);
			break;
		case 2:
			For_c(EmyIS3, Tiger);
			For_d(EmyIS3, Tiger, 19.f, 2.f);
			For_e(EmyIS3);
			EmyDamage(EmyIS3, Tiger, 170.f, 110.f);

			For_c(EmyT54, Tiger);
			For_d(EmyT54, Tiger, 17.f, 4.f);
			For_e(EmyT54);
			EmyDamage(EmyT54, Tiger, 170.f, 110.f);

			For_c(EmyM103, Tiger);
			For_d(EmyM103, Tiger, 15.f, 8.f);
			For_e(EmyM103);
			EmyDamage(EmyM103, Tiger, 170.f, 110.f);

			For_c(EmyM46, Tiger);
			For_d(EmyM46, Tiger, 20.f, 10.f);
			For_e(EmyM46);
			EmyDamage(EmyM46, Tiger, 170.f, 110.f);
			CheckAttack4(Tiger, EmyIS3, EmyT54, EmyM103, EmyM46, &Tigerobb, &IS3Emyobb, &T54Emyobb, &M103Emyobb, &M46Emyobb);
			CheckAttackShell4(Tiger_shell, EmyIS3, EmyT54, EmyM103, EmyM46, &TigerShellobb, &IS3Emyobb, &IS3Emyheadobb, &T54Emyobb, 
				              &T54Emyheadobb, &M103Emyobb, &M103Emyheadobb, &M46Emyobb, &M46Emyheadobb);
			CheckAttackEmyShell4(EmyIS3_shell, EmyT54_shell, EmyM103_shell, EmyM46_shell, Tiger, &IS3EmyShellobb,
				                 &T54EmyShellobb, &M103EmyShellobb, &M46EmyShellobb, &Tigerobb, &Tigerheadobb);
			Damage4(EmyIS3, EmyT54, EmyM103, EmyM46, Tiger, 207.f, 135.f, 215.f, 144.f, 269.f, 217.f, 157.f, 122.f);
			break;
		case 3:
			For_c(EmyIS3, PantherII);
			For_d(EmyIS3, PantherII, 19.f, 2.f);
			For_e(EmyIS3);
			EmyDamage(EmyIS3, PantherII, 225.f, 150.f);

			For_c(EmyT54, PantherII);
			For_d(EmyT54, PantherII, 17.f, 4.f);
			For_e(EmyT54);
			EmyDamage(EmyT54, PantherII, 225.f, 150.f);

			For_c(EmyM103, PantherII);
			For_d(EmyM103, PantherII, 15.f, 8.f);
			For_e(EmyM103);
			EmyDamage(EmyM103, PantherII, 225.f, 150.f);

			For_c(EmyM46, PantherII);
			For_d(EmyM46, PantherII, 20.f, 10.f);
			For_e(EmyM46);
			EmyDamage(EmyM46, PantherII, 225.f, 150.f);
			CheckAttack4(PantherII, EmyIS3, EmyT54, EmyM103, EmyM46, &PantherIIobb, &IS3Emyobb, &T54Emyobb, &M103Emyobb, &M46Emyobb);
			CheckAttackShell4(PantherII_shell, EmyIS3, EmyT54, EmyM103, EmyM46, &PantherIIShellobb, &IS3Emyobb, &IS3Emyheadobb, &T54Emyobb, 
				              &T54Emyheadobb, &M103Emyobb, &M103Emyheadobb, &M46Emyobb, &M46Emyheadobb);
			CheckAttackEmyShell4(EmyIS3_shell, EmyT54_shell, EmyM103_shell, EmyM46_shell, PantherII, &IS3EmyShellobb,
				                 &T54EmyShellobb, &M103EmyShellobb, &M46EmyShellobb, &PantherIIobb, &PantherIIheadobb);
			Damage4(EmyIS3, EmyT54, EmyM103, EmyM46, PantherII, 207.f, 135.f, 215.f, 144.f, 269.f, 217.f, 157.f, 122.f);
			break;
		case 4:
			For_c(EmyIS3, TigerII);
			For_d(EmyIS3, TigerII, 19.f, 2.f);
			For_e(EmyIS3);
			EmyDamage(EmyIS3, TigerII, 240.f, 167.f);

			For_c(EmyT54, TigerII);
			For_d(EmyT54, TigerII, 17.f, 4.f);
			For_e(EmyT54);
			EmyDamage(EmyT54, TigerII, 240.f, 167.f);

			For_c(EmyM103, TigerII);
			For_d(EmyM103, TigerII, 15.f, 8.f);
			For_e(EmyM103);
			EmyDamage(EmyM103, TigerII, 240.f, 167.f);

			For_c(EmyM46, TigerII);
			For_d(EmyM46, TigerII, 20.f, 10.f);
			For_e(EmyM46);
			EmyDamage(EmyM46, TigerII, 240.f, 167.f);
			CheckAttack4(TigerII, EmyIS3, EmyT54, EmyM103, EmyM46, &TigerIIobb, &IS3Emyobb, &T54Emyobb, &M103Emyobb, &M46Emyobb);
			CheckAttackShell4(TigerII_shell, EmyIS3, EmyT54, EmyM103, EmyM46, &TigerIIShellobb, &IS3Emyobb, &IS3Emyheadobb, &T54Emyobb, 
				              &T54Emyheadobb, &M103Emyobb, &M103Emyheadobb, &M46Emyobb, &M46Emyheadobb);
			CheckAttackEmyShell4(EmyIS3_shell, EmyT54_shell, EmyM103_shell, EmyM46_shell, TigerII, &IS3EmyShellobb,
				                 &T54EmyShellobb, &M103EmyShellobb, &M46EmyShellobb, &TigerIIobb, &TigerIIheadobb);
			Damage4(EmyIS3, EmyT54, EmyM103, EmyM46, TigerII, 207.f, 135.f, 215.f, 144.f, 269.f, 217.f, 157.f, 122.f);
			break;
		}
		break;
	}

	DrawPoint();
	//以上に3D 描画
}

/////////////////////////////////////////////////////////////////////////
//  描画（2D背景）
/////////////////////////////////////////////////////////////////////////
void Draw2DBackInGame(void)
{
	//描画処理開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//以下背景描画
	DrawTexture(lpSky, 0, 0, 1920.0f / 2048.0f, 1080.0f / 1024.0f, NULL, 0.0f, 0, 0, -1, 0xFFFFFFFF);
	//以上背景描画
	//描画処理終了
	lpSprite->End();
}

/////////////////////////////////////////////////////////////////////////
//  InGameを後始末
/////////////////////////////////////////////////////////////////////////
HRESULT DisposeInGame(void)
{
	//以下にInGameデータのリリース
	for (int i = 0; i < myTANKNUM; ++i)
	{
		ReleaseXMesh(&T44[i].mesh);
		ReleaseXMesh(&IS1[i].mesh);
		ReleaseXMesh(&T54[i].mesh);
		ReleaseXMesh(&IS3[i].mesh);
		ReleaseXMesh(&PantherG[i].mesh);
		ReleaseXMesh(&Tiger[i].mesh);
		ReleaseXMesh(&PantherII[i].mesh);
		ReleaseXMesh(&TigerII[i].mesh);
		ReleaseXMesh(&M26[i].mesh);
		ReleaseXMesh(&T32[i].mesh);
		ReleaseXMesh(&M46[i].mesh);
		ReleaseXMesh(&M103[i].mesh);
	}
	ReleaseXMesh(&land1.mesh);
	ReleaseXMesh(&land2.mesh);
	ReleaseXMesh(&land3.mesh);
	ReleaseXMesh(&land4.mesh);
	ReleaseXMesh(&Point.mesh);

	ReleaseXMesh(&EmyT44_shell.mesh);
	ReleaseXMesh(&EmyIS1_shell.mesh);
	ReleaseXMesh(&EmyT54_shell.mesh);
	ReleaseXMesh(&EmyIS3_shell.mesh);
	ReleaseXMesh(&EmyPantherG_shell.mesh);
	ReleaseXMesh(&EmyTiger_shell.mesh);
	ReleaseXMesh(&EmyPantherII_shell.mesh);
	ReleaseXMesh(&EmyTigerII_shell.mesh);
	ReleaseXMesh(&EmyM26_shell.mesh);
	ReleaseXMesh(&EmyT32_shell.mesh);
	ReleaseXMesh(&EmyM46_shell.mesh);
	ReleaseXMesh(&EmyM103_shell.mesh);
	for (int i = 0; i < eTANKNUM; ++i)
	{
		ReleaseXMesh(&EmyT44[i].mesh);
		ReleaseXMesh(&EmyIS1[i].mesh);
		ReleaseXMesh(&EmyT54[i].mesh);
		ReleaseXMesh(&EmyIS3[i].mesh);
		ReleaseXMesh(&EmyPantherG[i].mesh);
		ReleaseXMesh(&EmyTiger[i].mesh);
		ReleaseXMesh(&EmyPantherII[i].mesh);
		ReleaseXMesh(&EmyTigerII[i].mesh);
		ReleaseXMesh(&EmyM26[i].mesh);
		ReleaseXMesh(&EmyT32[i].mesh);
		ReleaseXMesh(&EmyM46[i].mesh);
		ReleaseXMesh(&EmyM103[i].mesh);
	}
	ReleaseXMesh(&T44_shell.mesh);
	ReleaseXMesh(&IS1_shell.mesh);
	ReleaseXMesh(&T54_shell.mesh);
	ReleaseXMesh(&IS3_shell.mesh);
	ReleaseXMesh(&PantherG_shell.mesh);
	ReleaseXMesh(&Tiger_shell.mesh);
	ReleaseXMesh(&PantherII_shell.mesh);
	ReleaseXMesh(&TigerII_shell.mesh);
	ReleaseXMesh(&M26_shell.mesh);
	ReleaseXMesh(&T32_shell.mesh);
	ReleaseXMesh(&M46_shell.mesh);
	ReleaseXMesh(&M103_shell.mesh);

	ReleaseTexture(&lpCenter);
	ReleaseTexture(&lpTarget);
	ReleaseTexture(&lpSight);
	ReleaseTexture(&lpHp);
	ReleaseTexture(&lpHp0);
	ReleaseTexture(&lpShell);
	ReleaseTexture(&lpShell0);
	ReleaseTexture(&lpPoint);
	ReleaseTexture(&lpPoint0);

	ReleaseTexture(&lpSky);
	//以上にInGameデータのリリース
	func = InitEnd;
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////
//  3D描画環境の設定
/////////////////////////////////////////////////////////////////////////
void Setup3DEnv(void)
{
	lpD3DDev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	lpD3DDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	lpD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	lpD3DDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	float start = 800.0f, end = 1000.0f;
	lpD3DDev->SetRenderState(D3DRS_FOGENABLE, TRUE);
	lpD3DDev->SetRenderState(D3DRS_FOGCOLOR, 0xffcccccc);
	lpD3DDev->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	lpD3DDev->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&start));
	lpD3DDev->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&end));
}
/////////////////////////////////////////////////////////////////////////
//  ライトの設定
/////////////////////////////////////////////////////////////////////////
void SetupLight(void)
{
	D3DCOLORVALUE color[2][3] =
	{
		{ { 1.0f, 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f } },
		{ { 0.5f, 0.5f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f } }
	};

	SetupDirectionalLight(color[0], D3DXVECTOR3(0.0f, -1.0f, 1.0f), 0);
	SetupDirectionalLight(color[1], D3DXVECTOR3(0.0f, -1.0f, -1.0f), 1);
	SetupDirectionalLight(color[0], D3DXVECTOR3(1.0f, -1.0f, 0.0f), 2);
	SetupDirectionalLight(color[1], D3DXVECTOR3(-1.0f, -1.0f, 0.0f), 3);
	lpD3DDev->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

/////////////////////////////////////////////////////////////////////////
//  Openを準備
/////////////////////////////////////////////////////////////////////////
HRESULT InitOpen(void)
{
	char TitleOpen[] = "BMP\\title.bmp";
	char NewGameOpen[] = "BMP\\NewGame.png";
	char ResumeGameOpen[] = "BMP\\ResumeGame.png";
	char QuitOpen[] = "BMP\\Quit.png";

	char isTankOpen[] = "BMP\\isTank.bmp";
	char MozdokOpen[] = "BMP\\Mozdok.png";
	char AllamanOpen[] = "BMP\\Allaman.png";
	char KurskOpen[] = "BMP\\Kursk.png";
	char ArdennesOpen[] = "BMP\\Ardennes.png";

	char ArrowOpen[] = "BMP\\Arrow.png";
	char GermanyOpen[] = "BMP\\Germany.bmp";
	char SovietOpen[] = "BMP\\Soviet.bmp";
	char AmericaOpen[] = "BMP\\America.bmp";

	char T44Open[] = "BMP\\T44.png";
	char T54Open[] = "BMP\\T54.png";
	char IS1Open[] = "BMP\\IS1.png";
	char IS3Open[] = "BMP\\IS3.png";

	char PantherGOpen[] = "BMP\\PantherG.png";
	char PantherIIOpen[] = "BMP\\PantherII.png";
	char TigerOpen[] = "BMP\\Tiger.png";
	char TigerIIOpen[] = "BMP\\TigerII.png";

	char M26Open[] = "BMP\\M26.png";
	char M46Open[] = "BMP\\M46.png";
	char T32Open[] = "BMP\\T32.png";
	char M103Open[] = "BMP\\M103.png";

	char T44dataOpen[] = "BMP\\T44data.png";
	char T54dataOpen[] = "BMP\\T54data.png";
	char IS1dataOpen[] = "BMP\\IS1data.png";
	char IS3dataOpen[] = "BMP\\IS3data.png";

	char PantherGdataOpen[] = "BMP\\PantherGdata.png";
	char PantherIIdataOpen[] = "BMP\\PantherIIdata.png";
	char TigerdataOpen[] = "BMP\\Tigerdata.png";
	char TigerIIdataOpen[] = "BMP\\TigerIIdata.png";

	char M26dataOpen[] = "BMP\\M26data.png";
	char M46dataOpen[] = "BMP\\M46data.png";
	char T32dataOpen[] = "BMP\\T32data.png";
	char M103dataOpen[] = "BMP\\M103data.png";

	char BackOpen[] = "BMP\\Back.png"; 
	char StartOpen[] = "BMP\\Start.png";
	//Openの基本準備
	if (EndStart == false)
	{
		TitleStart = true;
		isTank = false;
		Mozdok = true;
		Allaman = false;
		Kursk = false;
		Ardennes = false;  /////////123456
		ReStart = false;
		num_stage = 0;
		num_tank = 0;
		num_country = 0;
	}
	else if (EndStart)
	{
		TitleStart = false;
		isTank = true;
		switch (num_stage)
		{
		case 1:
			Allaman = true;
			break;
		case 2:
			Kursk = true;
			break;
		case 3:
			Ardennes = true;
			break;
		}
		num_stage = 0;
		num_tank = 0;
		num_country = 0;
	}
	GameStart = false;
	count = 0;
	fire_OK = false;
	flag_win = false;
	flag_lose = false;
	time = 0.f;
	game_time = 0.f;
	point_tank_time = 0.f;
	point_enemy_time = 0.f;

	func = DoOpen;
	//以下、Openの準備を記述
	if (FAILED(LoadTexture(TitleOpen, &lpTitle))) return E_FAIL;
	if (FAILED(LoadTexture(NewGameOpen, &lpNewGame))) return E_FAIL;
	if (FAILED(LoadTexture(ResumeGameOpen, &lpResumeGame))) return E_FAIL;
	if (FAILED(LoadTexture(QuitOpen, &lpQuit))) return E_FAIL;

	if (FAILED(LoadTexture(isTankOpen, &lpisTank))) return E_FAIL;
	if (FAILED(LoadTexture(MozdokOpen, &lpMozdok))) return E_FAIL;
	if (FAILED(LoadTexture(AllamanOpen, &lpAllaman))) return E_FAIL;
	if (FAILED(LoadTexture(KurskOpen, &lpKursk))) return E_FAIL;
	if (FAILED(LoadTexture(ArdennesOpen, &lpArdennes))) return E_FAIL;

	if (FAILED(LoadTexture(ArrowOpen, &lpArrow))) return E_FAIL;
	if (FAILED(LoadTexture(GermanyOpen, &lpGermany))) return E_FAIL;
	if (FAILED(LoadTexture(SovietOpen, &lpSoviet))) return E_FAIL;
	if (FAILED(LoadTexture(AmericaOpen, &lpAmerica))) return E_FAIL;

	if (FAILED(LoadTexture(T44Open, &lpT44))) return E_FAIL;
	if (FAILED(LoadTexture(T54Open, &lpT54))) return E_FAIL;
	if (FAILED(LoadTexture(IS1Open, &lpIS1))) return E_FAIL;
	if (FAILED(LoadTexture(IS3Open, &lpIS3))) return E_FAIL;

	if (FAILED(LoadTexture(PantherGOpen, &lpPantherG))) return E_FAIL;
	if (FAILED(LoadTexture(PantherIIOpen, &lpPantherII))) return E_FAIL;
	if (FAILED(LoadTexture(TigerOpen, &lpTiger))) return E_FAIL;
	if (FAILED(LoadTexture(TigerIIOpen, &lpTigerII))) return E_FAIL;

	if (FAILED(LoadTexture(M26Open, &lpM26))) return E_FAIL;
	if (FAILED(LoadTexture(M46Open, &lpM46))) return E_FAIL;
	if (FAILED(LoadTexture(T32Open, &lpT32))) return E_FAIL;
	if (FAILED(LoadTexture(M103Open, &lpM103))) return E_FAIL;

	if (FAILED(LoadTexture(T44dataOpen, &lpT44data))) return E_FAIL;
	if (FAILED(LoadTexture(T54dataOpen, &lpT54data))) return E_FAIL;
	if (FAILED(LoadTexture(IS1dataOpen, &lpIS1data))) return E_FAIL;
	if (FAILED(LoadTexture(IS3dataOpen, &lpIS3data))) return E_FAIL;

	if (FAILED(LoadTexture(PantherGdataOpen, &lpPantherGdata))) return E_FAIL;
	if (FAILED(LoadTexture(PantherIIdataOpen, &lpPantherIIdata))) return E_FAIL;
	if (FAILED(LoadTexture(TigerdataOpen, &lpTigerdata))) return E_FAIL;
	if (FAILED(LoadTexture(TigerIIdataOpen, &lpTigerIIdata))) return E_FAIL;

	if (FAILED(LoadTexture(M26dataOpen, &lpM26data))) return E_FAIL;
	if (FAILED(LoadTexture(M46dataOpen, &lpM46data))) return E_FAIL;
	if (FAILED(LoadTexture(T32dataOpen, &lpT32data))) return E_FAIL;
	if (FAILED(LoadTexture(M103dataOpen, &lpM103data))) return E_FAIL;

	if (FAILED(LoadTexture(BackOpen, &lpBack))) return E_FAIL;
	if (FAILED(LoadTexture(StartOpen, &lpStart))) return E_FAIL;
	//以上、Openの準備を記述
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Openを実行
/////////////////////////////////////////////////////////////////////////
HRESULT DoOpen(void)
{
	DrawOpen();
	if (GameStart)
	{
		EndStart = false;
		func = DisposeOpen;
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Openを後始末
/////////////////////////////////////////////////////////////////////////
HRESULT DisposeOpen(void)
{
	ReleaseTexture(&lpTitle);
	ReleaseTexture(&lpNewGame);
	ReleaseTexture(&lpResumeGame);
	ReleaseTexture(&lpQuit);

	ReleaseTexture(&lpisTank);
	ReleaseTexture(&lpMozdok);
	ReleaseTexture(&lpAllaman);
	ReleaseTexture(&lpKursk);
	ReleaseTexture(&lpArdennes);

	ReleaseTexture(&lpArrow);
	ReleaseTexture(&lpGermany);
	ReleaseTexture(&lpSoviet);
	ReleaseTexture(&lpAmerica);

	ReleaseTexture(&lpT44);
	ReleaseTexture(&lpT54);
	ReleaseTexture(&lpIS1);
	ReleaseTexture(&lpIS3);

	ReleaseTexture(&lpPantherG);
	ReleaseTexture(&lpPantherII);
	ReleaseTexture(&lpTiger);
	ReleaseTexture(&lpTigerII);

	ReleaseTexture(&lpM26);
	ReleaseTexture(&lpM46);
	ReleaseTexture(&lpT32);
	ReleaseTexture(&lpM103);

	ReleaseTexture(&lpT44data);
	ReleaseTexture(&lpT54data);
	ReleaseTexture(&lpIS1data);
	ReleaseTexture(&lpIS3data);

	ReleaseTexture(&lpPantherGdata);
	ReleaseTexture(&lpPantherIIdata);
	ReleaseTexture(&lpTigerdata);
	ReleaseTexture(&lpTigerIIdata);

	ReleaseTexture(&lpM26data);
	ReleaseTexture(&lpM46data);
	ReleaseTexture(&lpT32data);
	ReleaseTexture(&lpM103data);

	ReleaseTexture(&lpBack);
	ReleaseTexture(&lpStart);
	func = InitInGame;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Endを準備
/////////////////////////////////////////////////////////////////////////
HRESULT InitEnd(void)
{
	char End[] = "BMP\\isTank.bmp";
	char OK[] = "BMP\\OK.png";
	char Win[] = "BMP\\win.png";
	char Lose[] = "BMP\\lose.png";
	char S[] = "BMP\\s.png";
	char A[] = "BMP\\a.png";
	char B[] = "BMP\\b.png";
	char C[] = "BMP\\c.png";
	char D[] = "BMP\\d.png";
	char E[] = "BMP\\e.png";
	//Endの基本準備
	EndStart = false;

	func = DoEnd;
	//以下、Endの準備を記述
	if (FAILED(LoadTexture(End, &lpEnd))) return E_FAIL;
	if (FAILED(LoadTexture(OK, &lpOK))) return E_FAIL;
	if (FAILED(LoadTexture(Win, &lpYouWin))) return E_FAIL;
	if (FAILED(LoadTexture(Lose, &lpYouLose))) return E_FAIL;
	if (FAILED(LoadTexture(S, &lpRankS))) return E_FAIL;
	if (FAILED(LoadTexture(A, &lpRankA))) return E_FAIL;
	if (FAILED(LoadTexture(B, &lpRankB))) return E_FAIL;
	if (FAILED(LoadTexture(C, &lpRankC))) return E_FAIL;
	if (FAILED(LoadTexture(D, &lpRankD))) return E_FAIL;
	if (FAILED(LoadTexture(E, &lpRankE))) return E_FAIL;
	//以上、Endの準備を記述
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Endを実行
/////////////////////////////////////////////////////////////////////////
HRESULT DoEnd(void)
{
	while (count<0)
	{

		ShowCursor(TRUE);
		count += 1;
	}
	DrawEnd();
	if (EndStart)
	{
		func = DisposeEnd;
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  Endを後始末
/////////////////////////////////////////////////////////////////////////
HRESULT DisposeEnd(void)
{
	ReleaseTexture(&lpEnd);
	ReleaseTexture(&lpOK);
	ReleaseTexture(&lpYouWin);
	ReleaseTexture(&lpYouLose);
	ReleaseTexture(&lpRankS);
	ReleaseTexture(&lpRankA);
	ReleaseTexture(&lpRankB);
	ReleaseTexture(&lpRankC);
	ReleaseTexture(&lpRankD);
	ReleaseTexture(&lpRankE);

	func = InitOpen;
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////
//  FPSを描画
/////////////////////////////////////////////////////////////////////////
void DrawFPS(LPCTSTR pString, LPRECT rect)
{
	D3DXMATRIX nameMat;
	D3DXMatrixScaling(&nameMat, 1.0f, 1.0f, 1.0f);
	lpSprite->SetTransform(&nameMat);
	lpFont->DrawText(lpSprite, pString, -1, rect, DT_LEFT, 0xff000000);
}

void CalcFPS(float timeDelta)
{ 
	FrameCnt++; 
	TimeElapsed += timeDelta; 
	if (TimeElapsed >= 1.0f) 
	{ 
		FPS = (float)FrameCnt / TimeElapsed;
		TimeElapsed = 0.0f; 
		FrameCnt = 0; 
	} 
}

/////////////////////////////////////////////////////////////////////////
//  HPBARを描画
/////////////////////////////////////////////////////////////////////////
int CalcHpBar(int *hp,int *hpmax)
{
	DWORD c1, c2;
	c1 = 0x00;
	c2 = 0xC8;

	if (*hp >= (*hpmax / 2))
	{
		c1 = (int)((1.f - (float)*hp / (float)*hpmax)*400.f);
		if (c1 >= 0xC8) c1 = 0xC8;
	}
	if (*hp < (*hpmax / 2))
	{
		c1 = 0xC8;
		c2 = (int)((float)*hp / (float)*hpmax*400.f);
		if (c2 <= 0) c2 = 0;
	}
	return ((c1 * 0x010000) + (c2 * 0x0100) + 0xFF000000);
}

/////////////////////////////////////////////////////////////////////////
//  SHELLBARを描画
/////////////////////////////////////////////////////////////////////////
float CalcShellBar(float *time,float cd)
{
	return (*time / (cd / FPS * 60.f));
}
/////////////////////////////////////////////////////////////////////////
//  POINTBARを描画
/////////////////////////////////////////////////////////////////////////
float CalcPointBar(void)
{
	if (point_enemy == false)
	{
		if (point_tank)
		{
			if (point_enemy_time > 0.f)
			{
				point_enemy_time -= fpTimeDelta;
				if (point_enemy_time <= 0.f) point_enemy_time = 0.f;
			}
			else if (point_enemy_time <= 0.f)
			{
				point_tank_time += fpTimeDelta;
				if (point_tank_time >= 10.f)
				{
					point_tank_time = 0.f;
					flag_point = true;
					tank_hpup = true;
				}
			}
		}
		else if (point_tank == false)
		{
			point_tank_time -= fpTimeDelta;
			if (point_tank_time <= 0.f) point_tank_time = 0.f;
		}
	}
	if (point_tank == false)
	{
		if (point_enemy)
		{
			if (point_tank_time > 0.f)
			{
				point_tank_time -= fpTimeDelta;
				if (point_tank_time <= 0.f) point_tank_time = 0.f;
			}
			else if (point_tank_time <= 0.f)
			{
				point_enemy_time += fpTimeDelta;
				if (point_enemy_time >= 10.f)
				{
					point_enemy_time = 0.f;
					flag_point = true;
					tank_hpdown = true;
				}
			}
		}
		else if (point_enemy == false)
		{
			point_enemy_time -= fpTimeDelta;
			if (point_enemy_time <= 0.f) point_enemy_time = 0.f;
		}
	}
	if (point_enemy&&point_tank)
	{
		if (point_tank_time > 0.f)
		{
			point_tank_time -= fpTimeDelta;
			if (point_tank_time <= 0.f) point_tank_time = 0.f;
		}
		else if (point_enemy_time > 0.f)
		{
			point_enemy_time -= fpTimeDelta;
			if (point_enemy_time <= 0.f) point_enemy_time = 0.f;
		}
	}
	if (point_tank_time>0.f) return (point_tank_time / (10.f / FPS*60.f));
	if (point_enemy_time>0.f) return (point_enemy_time / (10.f / FPS*60.f));
}
/////////////////////////////////////////////////////////////////////////
//  CHECK END
/////////////////////////////////////////////////////////////////////////
BOOL ChechEnd(void)
{
	switch (num_stage)
	{
	case 1:
		switch (num_tank / 10)
		{
		case 1:
			if (EmyPantherG[eBODY].hp == 0)
			{
				flag_win = true;
				return true;
			}
			break;
		case 2:
			if (EmyT44[eBODY].hp == 0) 
			{
				flag_win = true;
				return true;
			}
			break;
		}
		break;
	case 2:
		switch (num_tank / 10)
		{
		case 2:
			if (EmyM26[eBODY].hp == 0 && EmyT32[eBODY].hp == 0) 
			{
				flag_win = true;
				return true;
			}
			break;
		case 3:
			if (EmyPantherG[eBODY].hp == 0 && EmyTiger[eBODY].hp == 0) 
			{
				flag_win = true;
				return true;
			}
			break;
		}
		break;
	case 3:
		switch (num_tank / 10)
		{
		case 1:
			if (EmyPantherG[eBODY].hp == 0 && EmyTiger[eBODY].hp == 0 && EmyPantherII[eBODY].hp == 0)
			{
				flag_win = true;
				return true;
			}
			break;
		case 2:
			if (EmyT44[eBODY].hp == 0 && EmyIS1[eBODY].hp == 0 && EmyT54[eBODY].hp == 0) 
			{
				flag_win = true;
				return true;
			}
			break;
		}
		break;
	case 4:
		if (EmyT54[eBODY].hp == 0 && EmyIS3[eBODY].hp == 0 && EmyM46[eBODY].hp == 0 && EmyM103[eBODY].hp == 0) 
		{
			flag_win = true;
			return true;
		}
		break;
	}
	if (T44[myBODY].hp == 0 || T54[myBODY].hp == 0 || IS1[myBODY].hp == 0 || IS3[myBODY].hp == 0 ||
		PantherG[myBODY].hp == 0 || Tiger[myBODY].hp == 0 || PantherII[myBODY].hp == 0 || TigerII[myBODY].hp == 0 ||
		M26[myBODY].hp == 0 || T32[myBODY].hp == 0 || M46[myBODY].hp == 0 || M103[myBODY].hp == 0)
	{
		flag_lose = true;
		return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////
//  MyDataの初期化
/////////////////////////////////////////////////////////////////////////
void InitMyData(void)
{
	//環境
	DoNULLClearDXEnv();
	//DirectXスケルトンデータ
	func = InitOpen;
	//以下、追加するデータのNULLクリア
	lpTitle = NULL;
	lpNewGame = NULL;
	lpResumeGame = NULL;
	lpQuit = NULL;

	lpisTank = NULL;
	lpMozdok = NULL;
	lpAllaman = NULL;
	lpKursk = NULL;
	lpArdennes = NULL;

	lpArrow = NULL;
	lpGermany = NULL;
	lpSoviet = NULL;
	lpAmerica = NULL;

	lpT44 = NULL;
	lpT54 = NULL;
	lpIS1 = NULL;
	lpIS3 = NULL;

	lpPantherG = NULL;
	lpPantherII = NULL;
	lpTiger = NULL;
	lpTigerII = NULL;

	lpM26 = NULL;
	lpM46 = NULL;
	lpT32 = NULL;
	lpM103 = NULL;

	lpT44data = NULL;
	lpT54data = NULL;
	lpIS1data = NULL;
	lpIS3data = NULL;

	lpPantherGdata = NULL;
	lpPantherIIdata = NULL;
	lpTigerdata = NULL;
	lpTigerIIdata = NULL;

	lpM26data = NULL;
	lpM46data = NULL;
	lpT32data = NULL;
	lpM103data = NULL;

	lpBack = NULL;
	lpStart = NULL;

	lpCenter = NULL;
	lpTarget = NULL;
	lpSight = NULL;
	lpHp = NULL;
	lpHp0 = NULL;
	lpShell = NULL;
	lpShell0 = NULL;
	lpPoint = NULL;
	lpPoint0 = NULL;

	lpSky = NULL;

	lpEnd = NULL;
	lpOK = NULL;
	lpYouWin = NULL;
	lpYouLose = NULL;
	lpRankS = NULL;
	lpRankA = NULL;
	lpRankB = NULL;
	lpRankC = NULL;
	lpRankD = NULL;
	lpRankE = NULL;
	//InGame
	for (int i = 0; i < myTANKNUM; ++i)
	{
		DoNullClear(&T44[i].mesh);
		DoNullClear(&IS1[i].mesh);
		DoNullClear(&T54[i].mesh);
		DoNullClear(&IS3[i].mesh);
		DoNullClear(&PantherG[i].mesh);
		DoNullClear(&Tiger[i].mesh);
		DoNullClear(&PantherII[i].mesh);
		DoNullClear(&TigerII[i].mesh);
		DoNullClear(&M26[i].mesh);
		DoNullClear(&T32[i].mesh);
		DoNullClear(&M46[i].mesh);
		DoNullClear(&M103[i].mesh);
	}
	DoNullClear(&land1.mesh);
	DoNullClear(&land2.mesh);
	DoNullClear(&land3.mesh);
	DoNullClear(&land4.mesh);
	DoNullClear(&Point.mesh);

	DoNullClear(&EmyT44_shell.mesh);
	DoNullClear(&EmyIS1_shell.mesh);
	DoNullClear(&EmyT54_shell.mesh);
	DoNullClear(&EmyIS3_shell.mesh);
	DoNullClear(&EmyPantherG_shell.mesh);
	DoNullClear(&EmyTiger_shell.mesh);
	DoNullClear(&EmyPantherII_shell.mesh);
	DoNullClear(&EmyTigerII_shell.mesh);
	DoNullClear(&EmyM26_shell.mesh);
	DoNullClear(&EmyT32_shell.mesh);
	DoNullClear(&EmyM46_shell.mesh);
	DoNullClear(&EmyM103_shell.mesh);
	for (int i = 0; i < eTANKNUM; ++i)
	{
		DoNullClear(&EmyT44[i].mesh);
		DoNullClear(&EmyIS1[i].mesh);
		DoNullClear(&EmyT54[i].mesh);
		DoNullClear(&EmyIS3[i].mesh);
		DoNullClear(&EmyPantherG[i].mesh);
		DoNullClear(&EmyTiger[i].mesh);
		DoNullClear(&EmyPantherII[i].mesh);
		DoNullClear(&EmyTigerII[i].mesh);
		DoNullClear(&EmyM26[i].mesh);
		DoNullClear(&EmyT32[i].mesh);
		DoNullClear(&EmyM46[i].mesh);
		DoNullClear(&EmyM103[i].mesh);
	}
	DoNullClear(&T44_shell.mesh);
	DoNullClear(&IS1_shell.mesh);
	DoNullClear(&T54_shell.mesh);
	DoNullClear(&IS3_shell.mesh);
	DoNullClear(&PantherG_shell.mesh);
	DoNullClear(&Tiger_shell.mesh);
	DoNullClear(&PantherII_shell.mesh);
	DoNullClear(&TigerII_shell.mesh);
	DoNullClear(&M26_shell.mesh);
	DoNullClear(&T32_shell.mesh);
	DoNullClear(&M46_shell.mesh);
	DoNullClear(&M103_shell.mesh);
}

/////////////////////////////////////////////////////////////////////////
//  MyDataの設定
/////////////////////////////////////////////////////////////////////////
HRESULT SetupMyData(HWND hWnd)
{
	//環境
	if (FAILED(CreateDXEnv(hWnd))) return E_FAIL;
	//以下に追加データ（全体で使うデータ）の値を設定する処理を記述する

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  オブジェクト全体のリリース
/////////////////////////////////////////////////////////////////////////
void ReleaseAll(void)
{
	//以下にロードデータのリリースを追加
	ReleaseTexture(&lpTitle);
	ReleaseTexture(&lpNewGame);
	ReleaseTexture(&lpResumeGame);
	ReleaseTexture(&lpQuit);

	ReleaseTexture(&lpisTank);
	ReleaseTexture(&lpMozdok);
	ReleaseTexture(&lpAllaman);
	ReleaseTexture(&lpKursk);
	ReleaseTexture(&lpArdennes);

	ReleaseTexture(&lpArrow);
	ReleaseTexture(&lpGermany);
	ReleaseTexture(&lpSoviet);
	ReleaseTexture(&lpAmerica);

	ReleaseTexture(&lpT44);
	ReleaseTexture(&lpT54);
	ReleaseTexture(&lpIS1);
	ReleaseTexture(&lpIS3);

	ReleaseTexture(&lpPantherG);
	ReleaseTexture(&lpPantherII);
	ReleaseTexture(&lpTiger);
	ReleaseTexture(&lpTigerII);

	ReleaseTexture(&lpM26);
	ReleaseTexture(&lpM46);
	ReleaseTexture(&lpT32);
	ReleaseTexture(&lpM103);

	ReleaseTexture(&lpT44data);
	ReleaseTexture(&lpT54data);
	ReleaseTexture(&lpIS1data);
	ReleaseTexture(&lpIS3data);

	ReleaseTexture(&lpPantherGdata);
	ReleaseTexture(&lpPantherIIdata);
	ReleaseTexture(&lpTigerdata);
	ReleaseTexture(&lpTigerIIdata);

	ReleaseTexture(&lpM26data);
	ReleaseTexture(&lpM46data);
	ReleaseTexture(&lpT32data);
	ReleaseTexture(&lpM103data);

	ReleaseTexture(&lpBack);
	ReleaseTexture(&lpStart);

	ReleaseTexture(&lpCenter);
	ReleaseTexture(&lpTarget);
	ReleaseTexture(&lpSight);
	ReleaseTexture(&lpHp);
	ReleaseTexture(&lpHp0);
	ReleaseTexture(&lpShell);
	ReleaseTexture(&lpShell0);
	ReleaseTexture(&lpPoint);
	ReleaseTexture(&lpPoint0);

	ReleaseTexture(&lpSky);
	for (int i = 0; i < myTANKNUM; ++i)
	{
		ReleaseXMesh(&T44[i].mesh);
		ReleaseXMesh(&IS1[i].mesh);
		ReleaseXMesh(&T54[i].mesh);
		ReleaseXMesh(&IS3[i].mesh);
		ReleaseXMesh(&PantherG[i].mesh);
		ReleaseXMesh(&Tiger[i].mesh);
		ReleaseXMesh(&PantherII[i].mesh);
		ReleaseXMesh(&TigerII[i].mesh);
		ReleaseXMesh(&M26[i].mesh);
		ReleaseXMesh(&T32[i].mesh);
		ReleaseXMesh(&M46[i].mesh);
		ReleaseXMesh(&M103[i].mesh);
	}
	ReleaseXMesh(&land1.mesh); 
	ReleaseXMesh(&land2.mesh);
	ReleaseXMesh(&land3.mesh);
	ReleaseXMesh(&land4.mesh);
	ReleaseXMesh(&Point.mesh);

	ReleaseXMesh(&EmyT44_shell.mesh);
	ReleaseXMesh(&EmyIS1_shell.mesh);
	ReleaseXMesh(&EmyT54_shell.mesh);
	ReleaseXMesh(&EmyIS3_shell.mesh);
	ReleaseXMesh(&EmyPantherG_shell.mesh);
	ReleaseXMesh(&EmyTiger_shell.mesh);
	ReleaseXMesh(&EmyPantherII_shell.mesh);
	ReleaseXMesh(&EmyTigerII_shell.mesh);
	ReleaseXMesh(&EmyM26_shell.mesh);
	ReleaseXMesh(&EmyT32_shell.mesh);
	ReleaseXMesh(&EmyM46_shell.mesh);
	ReleaseXMesh(&EmyM103_shell.mesh);
	for (int i = 0; i < eTANKNUM; ++i)
	{
		ReleaseXMesh(&EmyT44[i].mesh);
		ReleaseXMesh(&EmyIS1[i].mesh);
		ReleaseXMesh(&EmyT54[i].mesh);
		ReleaseXMesh(&EmyIS3[i].mesh);
		ReleaseXMesh(&EmyPantherG[i].mesh);
		ReleaseXMesh(&EmyTiger[i].mesh);
		ReleaseXMesh(&EmyPantherII[i].mesh);
		ReleaseXMesh(&EmyTigerII[i].mesh);
		ReleaseXMesh(&EmyM26[i].mesh);
		ReleaseXMesh(&EmyT32[i].mesh);
		ReleaseXMesh(&EmyM46[i].mesh);
		ReleaseXMesh(&EmyM103[i].mesh);
	}
	ReleaseXMesh(&T44_shell.mesh);
	ReleaseXMesh(&IS1_shell.mesh);
	ReleaseXMesh(&T54_shell.mesh);
	ReleaseXMesh(&IS3_shell.mesh);
	ReleaseXMesh(&PantherG_shell.mesh);
	ReleaseXMesh(&Tiger_shell.mesh);
	ReleaseXMesh(&PantherII_shell.mesh);
	ReleaseXMesh(&TigerII_shell.mesh);
	ReleaseXMesh(&T32_shell.mesh);
	ReleaseXMesh(&M46_shell.mesh);
	ReleaseXMesh(&M103_shell.mesh);
	//以上にロードデータのリリースを追加
	//DirectX環境のリリース
	ReleaseDXEnv();
}

/////////////////////////////////////////////////////////////////////////
//  キー入力のチェック
/////////////////////////////////////////////////////////////////////////
HRESULT CheckKey(void)
{
	//キーフラグのクリア
	key=0;
	//以下、キー入力のチェックとキーフラグのセット
	//ESCキーで終了へ
	if(HIBYTE(GetKeyState(VK_ESCAPE)))       	return E_FAIL;
	//F2キーでステージ移行へ
	if(HIBYTE(GetKeyState(VK_RETURN)))			key|=kKEYENTER;
	//矢印キー
	if(HIBYTE(GetKeyState('W')))				key|=kKEYW;
	if(HIBYTE(GetKeyState('S')))				key|=kKEYS;				
	if(HIBYTE(GetKeyState('A')))				key|=kKEYA;				
	if(HIBYTE(GetKeyState('D')))				key|=kKEYD;	

	if(HIBYTE(GetKeyState('E')))				key|=kKEYE;		

	if(HIBYTE(GetKeyState(VK_LBUTTON)))         key|=mLbtn;
#ifdef	kUSEDINPUT
	//以下、ゲームパッドによる入力のチェックとキーフラグのセット
	HRESULT		hr;
	DIJOYSTATE	dijs;
	//入力状態の取得
	if(FAILED(lpDIDev[eIDEV0]->Poll()))
	{
		hr=lpDIDev[eIDEV0]->Acquire();
		while(hr==DIERR_INPUTLOST)
			hr=lpDIDev[eIDEV0]->Acquire();
		return S_OK;
	}
	if(FAILED(lpDIDev[eIDEV0]->GetDeviceState(sizeof(DIJOYSTATE),&dijs)))
		return S_OK;
	//以下、ボタンのチェック
	//終了へ
	if(dijs.rgbButtons[nBtn[eIDEV0]-2] & 0x80)	//8
		return E_FAIL;
	//ステージ移行
	if(dijs.rgbButtons[nBtn[eIDEV0]-1] & 0x80)	//9
		key|=kKEYF2;
/*
	//Aボタン
	if(dijs.rgbButtons[0] & 0x80)		key|=kKEYSPACE;
	//Bボタン
	if(dijs.rgbButtons[1] & 0x80)		key|=kKEYD;
	//Yボタン
	if(dijs.rgbButtons[4] & 0x80)		key|=kKEYU;
	//軸
	if(dijs.lX>900)						key|=kKEYRIGHT;
	if(dijs.lX<-900)					key|=kKEYLEFT;
	if(dijs.lY>900)						key|=kKEYDOWN;
	if(dijs.lY<-900)					key|=kKEYUP;
*/
#endif

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  ゲームループ
/////////////////////////////////////////////////////////////////////////
HRESULT GameLoop(HWND hWnd)
{
	if (FAILED(CheckKey()))	return E_FAIL;
	if (FAILED((*func)()))	return E_FAIL;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
//  ウィンドウプロシージャ
/////////////////////////////////////////////////////////////////////////
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT			ps;
	static MMRESULT		mmRes;
	//メッセージの判別
	switch (msg)
	{
	case WM_CREATE:
		mmRes = timeBeginPeriod(1);
		break;
	case WM_PAINT://再描画要求
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY://ウィンドウの終了処理
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
//  メイン
/////////////////////////////////////////////////////////////////////////
INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,	LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASSEX		wc;
	HWND			hWnd;
	MSG				msg;

	//ウィンドウの形式
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
	//ウィンドウの登録
	RegisterClassEx(&wc);
	//ウィンドウの生成
	hWnd=CreateWindowEx(WS_EX_APPWINDOW,"DirectXAPP","Tank",WS_POPUP,0,0,1920,1080,
					NULL,NULL,hInstance,NULL);
	//ウィンドウの表示
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//Cursorを隠す
	
	//MyDataの初期化
	InitMyData();
	//MyDataのセットアップ
	if (FAILED(SetupMyData(hWnd)))
	{
		ReleaseAll();
		return 0;
	}
	//メッセージループ
	ZeroMemory(&msg,sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//ウィンドウメッセージの処理
		if (PeekMessage(&msg, NULL, 0L, 0L, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//ゲームループ
			if (FAILED(GameLoop(hWnd)))
			{
				DestroyWindow(hWnd);
			}
		}
	}
	ReleaseAll();
	return 0;
}
