#pragma once
#include "myDX.h"
#include "Player.h"

extern LPDIRECT3DTEXTURE9 lpTitle;
extern LPDIRECT3DTEXTURE9 lpNewGame;
extern LPDIRECT3DTEXTURE9 lpResumeGame;
extern LPDIRECT3DTEXTURE9 lpQuit;

extern LPDIRECT3DTEXTURE9 lpisTank;
extern LPDIRECT3DTEXTURE9 lpMozdok;
extern LPDIRECT3DTEXTURE9 lpAllaman;
extern LPDIRECT3DTEXTURE9 lpKursk;
extern LPDIRECT3DTEXTURE9 lpArdennes;

extern LPDIRECT3DTEXTURE9 lpArrow;
extern LPDIRECT3DTEXTURE9 lpGermany;
extern LPDIRECT3DTEXTURE9 lpSoviet;
extern LPDIRECT3DTEXTURE9 lpAmerica;

extern LPDIRECT3DTEXTURE9 lpT44;
extern LPDIRECT3DTEXTURE9 lpT54;
extern LPDIRECT3DTEXTURE9 lpIS1;
extern LPDIRECT3DTEXTURE9 lpIS3;

extern LPDIRECT3DTEXTURE9 lpPantherG;
extern LPDIRECT3DTEXTURE9 lpPantherII;
extern LPDIRECT3DTEXTURE9 lpTiger;
extern LPDIRECT3DTEXTURE9 lpTigerII;

extern LPDIRECT3DTEXTURE9 lpM26;
extern LPDIRECT3DTEXTURE9 lpM46;
extern LPDIRECT3DTEXTURE9 lpT32;
extern LPDIRECT3DTEXTURE9 lpM103;

extern LPDIRECT3DTEXTURE9 lpT44data;
extern LPDIRECT3DTEXTURE9 lpT54data;
extern LPDIRECT3DTEXTURE9 lpIS1data;
extern LPDIRECT3DTEXTURE9 lpIS3data;

extern LPDIRECT3DTEXTURE9 lpPantherGdata;
extern LPDIRECT3DTEXTURE9 lpPantherIIdata;
extern LPDIRECT3DTEXTURE9 lpTigerdata;
extern LPDIRECT3DTEXTURE9 lpTigerIIdata;

extern LPDIRECT3DTEXTURE9 lpM26data;
extern LPDIRECT3DTEXTURE9 lpM46data;
extern LPDIRECT3DTEXTURE9 lpT32data;
extern LPDIRECT3DTEXTURE9 lpM103data;

extern LPDIRECT3DTEXTURE9 lpBack;
extern LPDIRECT3DTEXTURE9 lpStart;

extern int num_stage;
extern int num_tank;
extern int num_country;
extern BOOL TitleStart;
extern BOOL isTank;
extern BOOL GameStart;
extern BOOL Mozdok;
extern BOOL Allaman;
extern BOOL Kursk;
extern BOOL Ardennes;
extern int count;
extern BOOL ReStart;
extern float game_time;