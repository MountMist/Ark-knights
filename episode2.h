#pragma once
#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include"player.h"
using namespace std;
class EP2 {
public:
	Player player;  // 定义玩家控制的游戏角色对象
	Scene2 scene2;  // 定义场景全局对象
	int  magicrelieve = 0;
	bool win2 = false;
	Timer timer;  // 用于精确延时
	bool isskill2 = false;
	void initialize(Player p) {
		scene2.initialize();  // 场景初始化
		player = p;
	}

	void fade_in() {
		TCHAR text[50] = _T("二更天，欲摹心事未有思");
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
		TCHAR text[50] = _T("二更天，欲摹心事未有思");
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

	void show2()  // 显示
	{
		scene2.draw();   // 显示场景相关信息
		scene2.drawtext(player.health, player.magic);
		player.draw();  // 显示玩家相关信息
		if ((!scene2.en1.is_alive()) && (!scene2.en2.is_alive()) && (!scene2.en3.is_alive())) {
			scene2.DisplayGameWin();
			win2 = true;
			//exit(0);
		}
		FlushBatchDraw(); // 批量绘制
		timer.Sleep(50); // 暂停若干毫秒
	}
	void updateWithoutInput2() // 和输入无关的更新
	{
		magicrelieve++;
		if (magicrelieve == 100) {
			player.magic += 20;
			magicrelieve = 0;
		}
		if (player.health <= 0) {
			scene2.DisplayGameOver();
			exit(0);
		}


		// 敌人自动更新位置
		if (scene2.en1.is_alive())   scene2.en1.update(player.x_left, player.y_bottom - player.height);
		if (scene2.en2.is_alive())	scene2.en2.update(player.x_left, player.y_bottom - player.height);
		if (scene2.en3.is_alive())	scene2.en3.update(player.x_left, player.y_bottom - player.height);
		if (scene2.en4.is_alive()) {
			scene2.en4.update(player.x_left, player.y_bottom - player.height);
		
		}
		if (scene2.en5.is_alive()) {
			scene2.en5.update(player.x_left, player.y_bottom - player.height);
			
		}
		//敌人死亡后为我方回复生命与法力
		if ((!scene2.en1.is_alive()) && scene2.en1.relieve == false) {
			scene2.en1.relieve = true;
			player.health += 10;
			player.magic += 10;
		}
		if ((!scene2.en2.is_alive()) && scene2.en2.relieve == false) {
			scene2.en2.relieve = true;
			player.health += 10;
			player.magic += 10;
		}
		if ((!scene2.en3.is_alive()) && scene2.en3.relieve == false) {
			scene2.en3.relieve = true;
			player.health += 10;
			player.magic += 10;
		}
		if ((player.isCollideEnemy(scene2.en1) && scene2.en1.is_alive()) ||( player.isCollideEnemy(scene2.en2) && scene2.en2.is_alive()) ||( player.isCollideEnemy(scene2.en3) && scene2.en3.is_alive())||(player.isCollideEnemy(scene2.en4) && scene2.en4.is_alive())||(player.isCollideEnemy(scene2.en5) && scene2.en5.is_alive()))
		{

			if (player.injured == false) {

				player.health -= 1;
				player.injured = true;
			}
			
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene2.en1)) {
				if (scene2.en1.hurt == false && player.magic > 0)scene2.en1.enemy_hp-=10;
				scene2.en1.hurt = true;
			}
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene2.en2)) {
				if (scene2.en2.hurt == false && player.magic > 0)scene2.en2.enemy_hp-=10;
				scene2.en2.hurt = true;
			}
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene2.en3)) {
				if (scene2.en3.hurt == false && player.magic > 0)scene2.en3.enemy_hp-=10;
				scene2.en3.hurt = true;
			}
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene2.en4)) {
				if (scene2.en4.hurt == false && player.magic > 0)scene2.en4.enemy_hp -= 10;
				scene2.en4.hurt = true;
			}
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene2.en5)) {
				if (scene2.en5.hurt == false && player.magic > 0)scene2.en5.enemy_hp -= 10;
				scene2.en5.hurt = true;
			}

		}
		else {
			// 如果没有检测到新的碰撞，重置碰撞标志
			// if ((!player.isCollideEnemy(scene.en1))|| (!player.isCollideEnemy(scene.en2))) {
			if (!player.isCollideEnemy(scene2.en1))scene2.en1.hurt = false;
			if (!player.isCollideEnemy(scene2.en2))scene2.en2.hurt = false;
			if (!player.isCollideEnemy(scene2.en3))scene2.en3.hurt = false;
			if (!player.isCollideEnemy(scene2.en4))scene2.en4.hurt = false;
			if (!player.isCollideEnemy(scene2.en5))scene2.en5.hurt = false;
			player.injured = false;
		}
		if (isskill2 == true) {
			scene2.en1.hurt = true;
			scene2.en1.enemy_hp -= 5;
			scene2.en2.hurt = true;
			scene2.en2.enemy_hp -= 5;
			scene2.en3.hurt = true;
			scene2.en3.enemy_hp -= 5;
			scene2.en4.hurt = true;
			scene2.en4.enemy_hp -= 5;
			scene2.en5.hurt = true;
			scene2.en5.enemy_hp -= 5;
			isskill2 = false;
		}
		/*if (isskill2 == false) {
			scene2.en1.hurt = false;
			scene2.en2.hurt = false;
			scene2.en3.hurt = false;
			scene2.en4.hurt = false;
			scene2.en5.hurt = false;
		}*/

	}
	void updateWithInput() // 和输入有关的更新
	{
		player.standStill(); // 游戏角色默认为向左或向右静止站立

		if (_kbhit()) // 当按键时，切换角色显示图片，更改位置
		{
			if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))  // 按下D键或右方向键
			{
				player.runRight();
			}
			else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// 按下A键或左方向键
			{
				player.runLeft();
			}
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))     // 按下W键或上方向键
			{
				player.runUp();
			}
			if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))     // 按下W键或上方向键
			{
				player.runDown();
			}
			if (GetAsyncKeyState('J') && (player.playerStatus == runleft || player.playerStatus == atkleft || player.playerStatus == rundown) && player.magic > 0)   // 向左攻击
			{
				player.atkLeft();
				//player.magic--;
			}
			if (GetAsyncKeyState('J') && (player.playerStatus == runright || player.playerStatus == atkright || player.playerStatus == runup) && player.magic > 0)   // 向左攻击
			{
				player.atkRight();
				//player.magic--;
			}
			if (GetAsyncKeyState('K') && (player.playerStatus == runleft || player.playerStatus == atkleft || player.playerStatus == rundown) && player.magic > 0)   // 向左攻击
			{
				player.skill2Left();
				isskill2 = true;
				//player.magic--;
			}
			if (GetAsyncKeyState('K') && (player.playerStatus == runright || player.playerStatus == atkright || player.playerStatus == runup) && player.magic > 0)   // 向左攻击
			{
				player.skill2Right();
				isskill2 = true;
				//player.magic--;
			}
		}
	}
};