#include "myDX.h"
#include "End.h"
#include "Title.h"
#include "Shell.h"
#include "stdio.h"
#include "Player.h"

/////////////////////////////////////////////////////////////////////////
//  描画（エンディング）
/////////////////////////////////////////////////////////////////////////
void DrawResult(LPCTSTR pString, LPRECT rect)
{
	D3DXMATRIX nameMat;
	D3DXMatrixScaling(&nameMat, 1.0f, 1.0f, 1.0f);
	lpSprite->SetTransform(&nameMat);
	lpFont->DrawText(lpSprite, pString, -1, rect, DT_LEFT, 0xFFFFFFFF);
}

//タンク残HP取得
float GetTankHP(void)
{
	//タンク種類取得
	switch (num_tank)
	{
	case 11:
		return (float)T44[myBODY].hp / (float)T44[myBODY].hpmax*100.f;
		break;
	case 12:
		return (float)IS1[myBODY].hp / (float)IS1[myBODY].hpmax*100.f;
		break;
	case 13:
		return (float)T54[myBODY].hp / (float)T54[myBODY].hpmax*100.f;
		break;
	case 14:
		return (float)IS3[myBODY].hp / (float)IS3[myBODY].hpmax*100.f;
		break;
	case 21:
		return (float)PantherG[myBODY].hp / (float)PantherG[myBODY].hpmax*100.f;
		break;
	case 22:
		return (float)Tiger[myBODY].hp / (float)Tiger[myBODY].hpmax*100.f;
		break;
	case 23:
		return (float)PantherII[myBODY].hp / (float)PantherII[myBODY].hpmax*100.f;
		break;
	case 24:
		return (float)TigerII[myBODY].hp / (float)TigerII[myBODY].hpmax*100.f;
		break;
	case 31:
		return (float)M26[myBODY].hp / (float)M26[myBODY].hpmax*100.f;
		break;
	case 32:
		return (float)T32[myBODY].hp / (float)T32[myBODY].hpmax*100.f;
		break;
	case 33:
		return (float)M46[myBODY].hp / (float)M46[myBODY].hpmax*100.f;
		break;
	case 34:
		return (float)M103[myBODY].hp / (float)M103[myBODY].hpmax*100.f;
		break;
	}
}

//タンク命中率取得
float GetTankHitRate(void)
{
	//タンク種類取得
	switch (num_tank)
	{
	case 11:
		if (T44_shell.hitmax == 0) T44_shell.hitmax = 1;
		return (float)T44_shell.hit / (float)T44_shell.hitmax*100.f;
		break;
	case 12:
		if (IS1_shell.hitmax == 0) IS1_shell.hitmax = 1;
		return (float)IS1_shell.hit / (float)IS1_shell.hitmax*100.f;
		break;
	case 13:
		if (T54_shell.hitmax == 0) T54_shell.hitmax = 1;
		return (float)T54_shell.hit / (float)T54_shell.hitmax*100.f;
		break;
	case 14:
		if (IS3_shell.hitmax == 0) IS3_shell.hitmax = 1;
		return (float)IS3_shell.hit / (float)IS3_shell.hitmax*100.f;
		break;
	case 21:
		if (PantherG_shell.hitmax == 0) PantherG_shell.hitmax = 1;
		return (float)PantherG_shell.hit / (float)PantherG_shell.hitmax*100.f;
		break;
	case 22:
		if (Tiger_shell.hitmax == 0) Tiger_shell.hitmax = 1;
		return (float)Tiger_shell.hit / (float)Tiger_shell.hitmax*100.f;
		break;
	case 23:
		if (PantherII_shell.hitmax == 0) PantherII_shell.hitmax = 1;
		return (float)PantherII_shell.hit / (float)PantherII_shell.hitmax*100.f;
		break;
	case 24:
		if (TigerII_shell.hitmax == 0) TigerII_shell.hitmax = 1;
		return (float)TigerII_shell.hit / (float)TigerII_shell.hitmax*100.f;
		break;
	case 31:
		if (M26_shell.hitmax == 0) M26_shell.hitmax = 1;
		return (float)M26_shell.hit / (float)M26_shell.hitmax*100.f;
		break;
	case 32:
		if (T32_shell.hitmax == 0) T32_shell.hitmax = 1;
		return (float)T32_shell.hit / (float)T32_shell.hitmax*100.f;
		break;
	case 33:
		if (M46_shell.hitmax == 0) M46_shell.hitmax = 1;
		return (float)M46_shell.hit / (float)M46_shell.hitmax*100.f;
		break;
	case 34:
		if (M103_shell.hitmax == 0) M103_shell.hitmax = 1;
		return (float)M103_shell.hit / (float)M103_shell.hitmax*100.f;
		break;
	}
}

//時間取得
float GetTimeScore(void)
{
	//ステージナンバー取得
	switch (num_stage)
	{
	case 1:
		if (100.f / (game_time / FPS * 60.f)*10000.f >= 10000.f) return 10000.f;
		else return 100.f / (game_time / FPS * 60.f)*10000.f;
		break;
	case 2:
		if (150.f / (game_time / FPS * 60.f)*10000.f >= 10000.f) return 10000.f;
		else return 150.f / (game_time / FPS * 60.f)*10000.f;
		break;
	case 3:
		if (300.f / (game_time / FPS * 60.f)*10000.f >= 10000.f) return 10000.f;
		else return 300.f / (game_time / FPS * 60.f)*10000.f;
		break;
	case 4:
		if (300.f / (game_time / FPS * 60.f)*10000.f >= 10000.f) return 10000.f;
		else return 300.f / (game_time / FPS * 60.f)*10000.f;
		break;
	}
}

void DrawEnd(void)
{
	lpD3DDev->BeginScene();
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//以下描画処理
	D3DXMATRIX mat;
	POINT cursorpt;
	GetCursorPos(&cursorpt);

	D3DXMatrixScaling(&mat, 1920.0f / 2048.0f, 1080.0f / 1024.0f, 1.0f);
	lpSprite->SetTransform(&mat);
	lpSprite->Draw(lpEnd, NULL, NULL, NULL, 0xFFFFFFFF);

	DWORD c1;
	c1 = 0x66FFFFFF;

	if (cursorpt.x >= 1920 / 2 - 89 / 2 && cursorpt.x <= 1920 / 2 - 89 / 2 + 89 && cursorpt.y >= 900 && cursorpt.y <= 900 + 39)
	{
		c1 = 0xFFFFFFFF;
		if (key&mLbtn&&EndStart == false)
		{
			EndStart = true;
		}
	}
	DrawTexture(lpOK, 1920 / 2 - 89 / 2, 900, 89.0f / 128.0f, 39.0f / 32.0f, NULL, 0.0f, 0, 0, 0, c1);
	if (flag_win) DrawTexture(lpYouWin, 1920 / 2 - 512 / 2, 100, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
	if (flag_lose) DrawTexture(lpYouLose, 1920 / 2 - 512 / 2, 100, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);

	RECT rect_time,time_score,sin_time_score,rect_hitRate,hitRate_score,sin_hitRate_score,rect_hp,hp_score,sin_hp_score,rect_point,rect_rank,score;
	char buffer_time[20],buffer_time_score[20], buffer_hitRate[20],buffer_hitRate_score[20], buffer_hp[20],buffer_hp_score[20],buffer_score[20];
	int fin_score = (int)GetTimeScore() + (int)(GetTankHitRate()*100.f) + (int)(GetTankHP()*100.f);
	sprintf((LPTSTR)(buffer_time), "%.2f", game_time / FPS * 60.f);
	sprintf((LPTSTR)(buffer_hitRate), "%.2f", GetTankHitRate());
	sprintf((LPTSTR)(buffer_hp), "%.2f", GetTankHP());

	sprintf((LPTSTR)(buffer_time_score), "%d", (int)GetTimeScore());
	sprintf((LPTSTR)(buffer_hitRate_score), "%d", (int)(GetTankHitRate()*100.f));
	sprintf((LPTSTR)(buffer_hp_score), "%d", (int)(GetTankHP()*100.f));
	sprintf((LPTSTR)(buffer_score), "%d", fin_score);

	//ランクを計算する
	if (fin_score >= 27000) DrawTexture(lpRankS, 1300, 590, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
	else if (fin_score >= 24000 && fin_score < 27000) DrawTexture(lpRankA, 1300, 590, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
	else if (fin_score >= 21000 && fin_score < 24000) DrawTexture(lpRankB, 1300, 590, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
	else if (fin_score >= 18000 && fin_score < 21000) DrawTexture(lpRankC, 1300, 590, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
	else if (fin_score >= 15000 && fin_score < 18000) DrawTexture(lpRankD, 1300, 590, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
	else if (fin_score < 15000) DrawTexture(lpRankE, 1300, 590, 1.f, 1.f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);

	rect_time.left = 500;
	rect_time.top = 400;
	rect_time.right = 500+256;
	rect_time.bottom = 400+36;

	time_score.left = 600;
	time_score.top = 400;
	time_score.right = 600 + 256;
	time_score.bottom = 400 + 36;

	sin_time_score.left = 900;
	sin_time_score.top = 400;
	sin_time_score.right = 900 + 256;
	sin_time_score.bottom = 400 + 36;

	rect_hitRate.left = 500;
	rect_hitRate.top = 500;
	rect_hitRate.right = 500 + 256;
	rect_hitRate.bottom = 500 + 36;

	hitRate_score.left = 600;
	hitRate_score.top = 500;
	hitRate_score.right = 600 + 256;
	hitRate_score.bottom = 500 + 36;

	sin_hitRate_score.left = 900;
	sin_hitRate_score.top = 500;
	sin_hitRate_score.right = 900 + 256;
	sin_hitRate_score.bottom = 500 + 36;

	rect_hp.left = 500;
	rect_hp.top = 600;
	rect_hp.right = 500 + 256;
	rect_hp.bottom = 600 + 36;

	hp_score.left = 600;
	hp_score.top = 600;
	hp_score.right = 600 + 256;
	hp_score.bottom = 600 + 36;

	sin_hp_score.left = 900;
	sin_hp_score.top = 600;
	sin_hp_score.right = 900 + 256;
	sin_hp_score.bottom = 600 + 36;

	rect_point.left = 500;
	rect_point.top = 700;
	rect_point.right = 500 + 256;
	rect_point.bottom = 700 + 36;

	score.left = 900;
	score.top = 700;
	score.right = 900 + 256;
	score.bottom = 700 + 36;
	
	rect_rank.left = 1200;
	rect_rank.top = 700;
	rect_rank.right = 1200 + 256;
	rect_rank.bottom = 700 + 36;

	DrawResult("時間:         s", &rect_time);
	DrawResult(buffer_time, &time_score);
	DrawResult(buffer_time_score, &sin_time_score);
	DrawResult("命中:         %", &rect_hitRate);
	DrawResult(buffer_hitRate, &hitRate_score);
	DrawResult(buffer_hitRate_score, &sin_hitRate_score);
	DrawResult("残HP:         %", &rect_hp);
	DrawResult(buffer_hp, &hp_score);
	DrawResult(buffer_hp_score, &sin_hp_score);
	DrawResult("得点:", &rect_point);
	DrawResult(buffer_score, &score);
	DrawResult("ランク:", &rect_rank);
	//描画処理終了
	lpSprite->End();
	lpD3DDev->EndScene();
	lpD3DDev->Present(NULL, NULL, NULL, NULL);
}

