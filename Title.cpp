#include "myDX.h"
#include "Title.h"
#include "End.h"

/////////////////////////////////////////////////////////////////////////
//  描画（オープニング）
/////////////////////////////////////////////////////////////////////////
void DrawOpen(void)
{
	lpD3DDev->BeginScene();
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//以下描画処理
	if (TitleStart)
	{
		D3DXMATRIX mat1;
		float chosen1, chosen2, chosen3;
		POINT cursorpt;
		GetCursorPos(&cursorpt);

		D3DXMatrixScaling(&mat1, 1920.0f / 2048.0f, 1080.0f / 1024.0f, 1.0f);
		lpSprite->SetTransform(&mat1);
		lpSprite->Draw(lpTitle, NULL, NULL, NULL, 0xFFFFFFFF);

		chosen1 = chosen2 = chosen3 = 1.f;
		if (cursorpt.x >= 1920 / 2 - 316 / 2 && cursorpt.x <= 1920 / 2 + 316 / 2 && cursorpt.y >= 750 && cursorpt.y <= 750 + 55)
		{
			chosen1 = 1.1f;
			if (key&mLbtn&&isTank == false)
			{
				if (ReStart == false)
				{
					TitleStart = false;
					isTank = true;
				}
				if (ReStart)
				{
					TitleStart = true;
					isTank = false;
					Mozdok = true;
					Allaman = false;
					Kursk = false;
					Ardennes = false;
					ReStart = false;
					num_stage = 0;
					num_tank = 0;
					num_country = 0;
				}
			}
		}
		else if (cursorpt.x >= 1920 / 2 - 434 / 2 && cursorpt.x <= 1920 / 2 + 434 / 2 && cursorpt.y >= 850 && cursorpt.y <= 850 + 55)
		{
			chosen2 = 1.1f;
			if (key&mLbtn)
			{
				if (ReStart)
				{
					TitleStart = false;
					isTank = true;
				}
			}
		}
		else if (cursorpt.x >= 1920 / 2 - 152 / 2 && cursorpt.x <= 1920 / 2 + 152 / 2 && cursorpt.y >= 950 && cursorpt.y <= 950 + 62)
		{
			chosen3 = 1.1f;
			if (key&mLbtn)
			{
				PostQuitMessage(0);
			}
		}
		DrawTexture(lpNewGame, 1920 / 2 - 316 / 2, 750, 316.0f / 512.0f*chosen1, 55.0f / 64.0f*chosen1, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpResumeGame, 1920 / 2 - 434 / 2, 850, 434.0f / 512.0f*chosen2, 55.0f / 64.0f*chosen2, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
		DrawTexture(lpQuit, 1920 / 2 - 152 / 2, 950, 152.0f / 256.0f*chosen3, 62.0f / 64.0f*chosen3, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);
	}

	else if (isTank)
	{
		DWORD c1, c2, c3, c4, c5, c6, c7, c8, c9;
		DWORD c11, c12, c13, c14, c21, c22, c23, c24, c31, c32, c33, c34;
		DWORD c11d, c12d, c13d, c14d, c21d, c22d, c23d, c24d, c31d, c32d, c33d, c34d;
		POINT cursorpt2;
		GetCursorPos(&cursorpt2);
		c1 = c2 = c3 = c4 = 0x00FFFFFF;
		c5 = c6 = c7 = c8 = c9 = 0x66FFFFFF;
		c11 = c12 = c13 = c14 = c21 = c22 = c23 = c24 = c31 = c32 = c33 = c34 = 0x00FFFFFF;
		c11d = c12d = c13d = c14d = c21d = c22d = c23d = c24d = c31d = c32d = c33d = c34d = 0x00FFFFFF;

		if (Mozdok)
		{
			c1 = 0x66FFFFFF;
			c11 = c21 = c31 = 0x66FFFFFF;
			if (cursorpt2.x >= 100 && cursorpt2.x <= 100 + 322 && cursorpt2.y >= 100 && cursorpt2.y <= 100 + 133 || num_stage == 1)
			{
				c1 = 0xFFFFFFFF;
				if (key&mLbtn) num_stage = 1;
			}
		}
		if (Allaman)
		{
			c2 = 0x66FFFFFF;
			c12 = c22 = c32 = 0x66FFFFFF;
			if (cursorpt2.x >= 100 && cursorpt2.x <= 100 + 356 && cursorpt2.y >= 300 && cursorpt2.y <= 300 + 145 || num_stage == 2)
			{
				c2 = 0xFFFFFFFF;
				if (key&mLbtn) num_stage = 2;
			}
		}
		if (Kursk)
		{
			c3 = 0x66FFFFFF;
			c13 = c23 = c33 = 0x66FFFFFF;
			if (cursorpt2.x >= 100 && cursorpt2.x <= 100 + 322 && cursorpt2.y >= 500 && cursorpt2.y <= 500 + 144 || num_stage == 3)
			{
				c3 = 0xFFFFFFFF;
				if (key&mLbtn) num_stage = 3;
			}
		}
		if (Ardennes)
		{
			c4 = 0x66FFFFFF;
			c14 = c24 = c34 = 0x66FFFFFF;
			if (cursorpt2.x >= 100 && cursorpt2.x <= 100 + 345 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 139 || num_stage == 4)
			{
				c4 = 0xFFFFFFFF;
				if (key&mLbtn) num_stage = 4;
			}
		}

		switch (num_stage)
		{
		case 1:
			c5 = c6 = 0xFFFFFFFF;
			break;
		case 2:
			c6 = c7 = 0xFFFFFFFF;
			break;
		case 3:
			c5 = c6 = 0xFFFFFFFF;
			break;
		case 4:
			c6 = 0xFFFFFFFF;
			break;
		}

		if ((cursorpt2.x >= 490 && cursorpt2.x <= 490 + 230 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 || 
			num_tank == 11) && c5 == 0xFFFFFFFF && c11 == 0x66FFFFFF)
		{
			c11 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 11;
		}
		if ((cursorpt2.x >= 720 && cursorpt2.x <= 710 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 || 
			num_tank == 12) && c5 == 0xFFFFFFFF && c12 == 0x66FFFFFF)
		{
			c12 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 12;
		}
		if ((cursorpt2.x >= 490 && cursorpt2.x <= 490 + 230 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 || 
			num_tank == 13) && c5 == 0xFFFFFFFF && c13 == 0x66FFFFFF)
		{
			c13 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 13;
		}
		if ((cursorpt2.x >= 720 && cursorpt2.x <= 710 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 || 
			num_tank == 14) && c5 == 0xFFFFFFFF && c14 == 0x66FFFFFF)
		{
			c14 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 14;
		}
		if ((cursorpt2.x >= 950 && cursorpt2.x <= 940 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 || 
			num_tank == 21) && c6 == 0xFFFFFFFF && c21 == 0x66FFFFFF)
		{
			c21 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 21;
		}
		if ((cursorpt2.x >= 1180 && cursorpt2.x <= 1180 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 || 
			num_tank == 22) && c6 == 0xFFFFFFFF && c22 == 0x66FFFFFF)
		{
			c22 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 22;
		}
		if ((cursorpt2.x >= 950 && cursorpt2.x <= 940 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 || 
			num_tank == 23) && c6 == 0xFFFFFFFF && c23 == 0x66FFFFFF)
		{
			c23 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 23;
		}
		if ((cursorpt2.x >= 1180 && cursorpt2.x <= 1180 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 || 
			num_tank == 24) && c6 == 0xFFFFFFFF && c24 == 0x66FFFFFF)
		{
			c24 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 24;
		}
		if ((cursorpt2.x >= 1420 && cursorpt2.x <= 1410 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 || 
			num_tank == 31) && c7 == 0xFFFFFFFF && c31 == 0x66FFFFFF)
		{
			c31 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 31;
		}
		if ((cursorpt2.x >= 1650 && cursorpt2.x <= 1650 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 || 
			num_tank == 32) && c7 == 0xFFFFFFFF && c32 == 0x66FFFFFF)
		{
			c32 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 32;
		}
		if ((cursorpt2.x >= 1420 && cursorpt2.x <= 1410 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 || 
			num_tank == 33) && c7 == 0xFFFFFFFF && c33 == 0x66FFFFFF)
		{
			c33 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 33;
		}
		if ((cursorpt2.x >= 1650 && cursorpt2.x <= 1650 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 || 
			num_tank == 34) && c7 == 0xFFFFFFFF && c34 == 0x66FFFFFF)
		{
			c34 = 0xFFFFFFFF;
			if (key&mLbtn) num_tank = 34;
		}

		if (num_tank / 10 == 1) num_country = 1;
		if (num_tank / 10 == 2) num_country = 2;
		if (num_tank / 10 == 3) num_country = 3;

		if (cursorpt2.x >= 490 && cursorpt2.x <= 490 + 230 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 && c5 == 0xFFFFFFFF && c11 != 0x00FFFFFF)
		{
			c11d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 720 && cursorpt2.x <= 710 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 && c5 == 0xFFFFFFFF && c12 != 0x00FFFFFF)
		{
			c12d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 490 && cursorpt2.x <= 490 + 230 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 && c5 == 0xFFFFFFFF && c13 != 0x00FFFFFF)
		{
			c13d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 720 && cursorpt2.x <= 710 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 && c5 == 0xFFFFFFFF && c14 != 0x00FFFFFF)
		{
			c14d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 950 && cursorpt2.x <= 940 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 && c6 == 0xFFFFFFFF && c21 != 0x00FFFFFF)
		{
			c21d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 1180 && cursorpt2.x <= 1180 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 && c6 == 0xFFFFFFFF && c22 != 0x00FFFFFF)
		{
			c22d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 950 && cursorpt2.x <= 940 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 && c6 == 0xFFFFFFFF && c23 != 0x00FFFFFF)
		{
			c23d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 1180 && cursorpt2.x <= 1180 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 && c6 == 0xFFFFFFFF && c24 != 0x00FFFFFF)
		{
			c24d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 1420 && cursorpt2.x <= 1410 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 && c7 == 0xFFFFFFFF && c31 != 0x00FFFFFF)
		{
			c31d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 1650 && cursorpt2.x <= 1650 + 240 && cursorpt2.y >= 400 && cursorpt2.y <= 400 + 150 && c7 == 0xFFFFFFFF && c32 != 0x00FFFFFF)
		{
			c32d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 1420 && cursorpt2.x <= 1410 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 && c7 == 0xFFFFFFFF && c33 != 0x00FFFFFF)
		{
			c33d = 0xFFFFFFFF;
		}
		if (cursorpt2.x >= 1650 && cursorpt2.x <= 1650 + 240 && cursorpt2.y >= 700 && cursorpt2.y <= 700 + 150 && c7 == 0xFFFFFFFF && c34 != 0x00FFFFFF)
		{
			c34d = 0xFFFFFFFF;
		}


		if (cursorpt2.x >= 1500 && cursorpt2.x <= 1500 + 97 && cursorpt2.y >= 1000 && cursorpt2.y <= 1000 + 32)
		{
			c8 = 0xFFFFFFFF;
			if (key&mLbtn&&TitleStart == false)
			{
				TitleStart = true;
				isTank = false;
				if (EndStart)
				{
					ReStart = true;
				}
			}
		}
		if (cursorpt2.x >= 1750 && cursorpt2.x <= 1750 + 95 && cursorpt2.y >= 1000 && cursorpt2.y <= 1000 + 32)
		{
			c9 = 0xFFFFFFFF;
			if (key&mLbtn&&num_stage != 0 && num_tank != 0)
			{
				GameStart = true;
				TitleStart = false;
				isTank = false;
			}
		}

		DrawTexture(lpisTank, 0, 0, 1920.0f / 2048.0f, 1080.0f / 1024.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);

		DrawTexture(lpMozdok, 100, 100, 322.0f / 256.0f, 133.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c1);
		DrawTexture(lpAllaman, 100, 300, 356.0f / 256.0f, 145.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c2);
		DrawTexture(lpKursk, 100, 500, 322.0f / 256.0f, 144.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c3);
		DrawTexture(lpArdennes, 100, 700, 345.0f / 256.0f, 139.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c4);

		DrawTexture(lpArrow, 600, 300, 1200.0f / 1024.0f, 358.0f / 512.0f, NULL, 0.0f, 0, 0, 0, 0xFFFFFFFF);

		DrawTexture(lpSoviet, 580, 85, 300.0f / 512.0f, 200.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c5);
		DrawTexture(lpGermany, 1060, 85, 300.0f / 512.0f, 200.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c6);
		DrawTexture(lpAmerica, 1530, 85, 300.0f / 512.0f, 200.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c7);

		DrawTexture(lpT44, 490, 400, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c11);
		DrawTexture(lpIS1, 710, 400, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c12);
		DrawTexture(lpPantherG, 940, 400, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c21);
		DrawTexture(lpTiger, 1180, 400, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c22);
		DrawTexture(lpM26, 1410, 400, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c31);
		DrawTexture(lpT32, 1650, 400, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c32);

		DrawTexture(lpT54, 490, 700, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c13);
		DrawTexture(lpIS3, 710, 700, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c14);
		DrawTexture(lpPantherII, 940, 700, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c23);
		DrawTexture(lpTigerII, 1180, 700, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c24);
		DrawTexture(lpM46, 1410, 700, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c33);
		DrawTexture(lpM103, 1650, 700, 240.0f / 256.0f, 150.0f / 128.0f, NULL, 0.0f, 0, 0, 0, c34);

		DrawTexture(lpBack, 1500, 1000, 97.0f / 128.0f, 32.0f / 32.0f, NULL, 0.0f, 0, 0, 0, c8);
		DrawTexture(lpStart, 1750, 1000, 95.0f / 128.0f, 32.0f / 32.0f, NULL, 0.0f, 0, 0, 0, c9);

		DrawTexture(lpT44data, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c11d);
		DrawTexture(lpIS1data, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c12d);
		DrawTexture(lpT54data, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c13d);
		DrawTexture(lpIS3data, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c14d);

		DrawTexture(lpPantherGdata, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c21d);
		DrawTexture(lpTigerdata, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c22d);
		DrawTexture(lpPantherIIdata, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c23d);
		DrawTexture(lpTigerIIdata, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c24d);

		DrawTexture(lpM26data, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c31d);
		DrawTexture(lpT32data, cursorpt2.x - 411, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c32d);
		DrawTexture(lpM46data, cursorpt2.x, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c33d);
		DrawTexture(lpM103data, cursorpt2.x - 411, cursorpt2.y, 411.0f / 512.0f, 293.0f / 256.0f, NULL, 0.0f, 0, 0, 0, c34d);
	}
	//描画処理終了
	lpSprite->End();
	lpD3DDev->EndScene();
	lpD3DDev->Present(NULL, NULL, NULL, NULL);
}