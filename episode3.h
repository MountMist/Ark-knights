#pragma once
#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include"player.h"
#include"BOSS.h"
using namespace std;
class EP3 {
public:
	Player player;  // 定义玩家控制的游戏角色对象
	Scene3 scene3;  // 定义场景全局对象
	int  magicrelieve = 0;
	int zzx;
	int skilldelay = 0;
	bool win3 = false;
	int xuli = 0;
	Timer timer;  // 用于精确延时
	BOSS ZZ;
	void initialize(Player p) {
		scene3.initialize();  // 场景初始化
		ZZ.initialize(600,100);
		player = p;
	}

	void fade_in() {
		TCHAR text[50] = _T("三更天，彩卷洇破复难合");
		LOGFONT font;
		//gettextstyle(&font);
		//settextstyle(20, 0, _T("华文隶书"));
		COLORREF bk_color = getbkcolor();
		COLORREF text_color = WHITE;
		int bk_color_arr[3] = { GetRValue(bk_color), GetGValue(bk_color), GetBValue(bk_color) };
		int text_color_arr[3] = { GetRValue(text_color), GetGValue(text_color), GetBValue(text_color) };

		int times = 80,
			r_incr = (text_color_arr[0] - bk_color_arr[0]) / times,
			g_incr = (text_color_arr[1] - bk_color_arr[1]) / times,
			b_incr = (text_color_arr[2] - bk_color_arr[2]) / times;

		BeginBatchDraw();
		for (int i = 0; i < times; i++) {
			//font.lfHeight = 80;
			//settextstyle(&font);
			settextstyle(80, 0, _T("华文行楷"));
			int text_width = textwidth(text),
				text_height = textheight(text);
			cleardevice();
			//putimage(0, 0, &win_image);
			settextcolor(RGB(bk_color_arr[0] + r_incr * i, bk_color_arr[1] + g_incr * i, bk_color_arr[2] + b_incr * i));
			outtextxy((WIDTH - text_width) / 2, (HEIGHT - text_height) / 2, text);
			FlushBatchDraw();
			Sleep(15);
		}
		EndBatchDraw();
	}

	// 文字淡出
	void fade_out() {
		TCHAR text[50] = _T("三更天，彩卷洇破复难合");
		LOGFONT font;
		//gettextstyle(&font);

		COLORREF bk_color = getbkcolor();
		COLORREF text_color = WHITE;
		int bk_color_arr[3] = { GetRValue(bk_color), GetGValue(bk_color), GetBValue(bk_color) };
		int text_color_arr[3] = { GetRValue(text_color), GetGValue(text_color), GetBValue(text_color) };

		int times = 80,
			r_incr = (bk_color_arr[0] - text_color_arr[0]) / times,
			g_incr = (bk_color_arr[1] - text_color_arr[1]) / times,
			b_incr = (bk_color_arr[2] - text_color_arr[2]) / times;

		BeginBatchDraw();
		for (int i = 0; i < times; i++) {
			//font.lfHeight = 80;
			//settextstyle(&font);
			settextstyle(80, 0, _T("华文行楷"));
			int text_width = textwidth(text),
				text_height = textheight(text);
			cleardevice();
			//putimage(0, 0, &win_image);
			settextcolor(RGB(text_color_arr[0] + r_incr * i, text_color_arr[1] + g_incr * i, text_color_arr[2] + b_incr * i));
			outtextxy((WIDTH - text_width) / 2, (HEIGHT - text_height) / 2, text);
			FlushBatchDraw();
			Sleep(15);
		}
		//putimage(0, 0, &win_image);
		EndBatchDraw();
	}

	void show3()  // 显示
	{
		
		scene3.draw(player.energy);   // 显示场景相关信息
		scene3.drawtext(player.health, player.magic);
		if (ZZ.boss_hp<=0) {
			ZZ.boss_hp = 0;
			scene3.DisplayGameWin();
			win3 = true;
			//exit(0);
		}
		player.draw();  // 显示玩家相关信息
		ZZ.draw();
		ZZ.atking(player.x_left+player.width/2,player.y_bottom-player.height/2,player);
		if (player.isskill3 == true) {
			
			zzx+=20;
			player.skill3(zzx);
			if (zzx > 700) {
				zzx = player.x_left;
				ZZ.boss_hp -= 10 + xuli * 10;
				player.isskill3 = false;
				xuli = 0;
				player.energy -= 5;
			}
		}
		FlushBatchDraw(); // 批量绘制
		timer.Sleep(50); // 暂停若干毫秒
	}
	void updateWithInput() // 和输入有关的更新
	{
		player.standStill(); // 游戏角色默认为向左或向右静止站立

		if (_kbhit()) // 当按键时，切换角色显示图片，更改位置
		{
			if(!win3)if (player.x_left >= 500)player.x_left = 500;//胜利通关后可以继续往右走，否则不能继续往右走
			if (player.x_left <= 0)player.x_left = 0;
			if (player.y_bottom >= 600)player.y_bottom = 600;
		//	if (player.y_bottom <= 30)player.y_bottom = 30;
			if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))  // 按下D键或右方向键
			{
				player.runRight();
				//player.standStill();
			}
			else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// 按下A键或左方向键
			{
				player.runLeft();
				//player.standStill();
			}
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))     // 按下W键或上方向键
			{
				player.runUp();
				//player.standStill();
			}
			if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))     // 按下W键或上方向键
			{
				player.runDown();
				//player.standStill();
			}
			if (GetAsyncKeyState('J') && (player.playerStatus == runleft || player.playerStatus == atkleft || player.playerStatus == rundown) && player.magic > 0)// 向左攻击
			{
				player.atkLeft();
				player.standStill();
				//player.magic--;
			}
			if (GetAsyncKeyState('J') && (player.playerStatus == runright || player.playerStatus == atkright || player.playerStatus == runup) && player.magic > 0)   // 向左攻击
			{
				player.atkRight();
				player.standStill();
				//player.magic--;
			}
			if (GetAsyncKeyState('K')&&(player.playerStatus == runleft || player.playerStatus == atkleft || player.playerStatus == rundown))     // 按下K键使用技能
			{
				player.skill3Left();
				player.isskill3 = true;
				zzx = player.x_left;
			}
			if (GetAsyncKeyState('K') && (player.playerStatus == runright || player.playerStatus == atkright || player.playerStatus == runup)&&player.energy>=5)     // 按下K键使用技能
			{
				player.skill3Right();
				player.isskill3 = true;
				xuli++;
				zzx = player.x_left;
				
			}
		}
	}
	void updateWithoutInput3() {
		magicrelieve++;//自动回复法力
		if (magicrelieve == 100) {
			player.magic += 20;
			magicrelieve = 0;
		}
		if (player.health <= 0) {
			scene3.DisplayGameOver();
			exit(0);
		}
		if (ZZ.boss_hp > 0) {
			skilldelay++;
					if (skilldelay == 50) {
						ZZ.enemystatus = 1;
						ZZ.bullet_reinitial();
					}
					if (skilldelay == 150) {
						ZZ.enemystatus = 0;
						skilldelay = 0;
						ZZ.bullet_reinitial();
					}
		}
		
	}
};
	
