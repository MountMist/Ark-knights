#pragma once
#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include"player.h"
using namespace std;
class EP1 {
public:
	Player player;  // 定义玩家控制的游戏角色对象
	Scene scene;  // 定义场景全局对象
	Timer timer;  // 用于精确延时
	int  magicrelieve = 0;
	bool win1 = false;
	void initialize(Player p) {
		scene.initialize();  // 场景初始化
		player = p;
	}

	void fade_in() {
		TCHAR text[50] = _T("一更天，对镜烧烛展玉宣");
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
		TCHAR text[50] = _T("一更天，对镜烧烛展玉宣");
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

	void show()  // 显示
	{
		scene.draw();   // 显示场景相关信息
		scene.drawtext(player.health, player.magic);
		player.draw();  // 显示玩家相关信息
		//绘制晦明属性
		if (player.huiming == 1) {
			setfillcolor(BLACK);
			fillcircle(player.x_left + player.width / 2, player.y_bottom - player.height, 10);
		}
		else {
			setfillcolor(LIGHTGRAY);
			fillcircle(player.x_left + player.width / 2, player.y_bottom - player.height, 10);
		}
		if ((!scene.en1.is_alive()) && (!scene.en2.is_alive()) && (!scene.en3.is_alive()) && (!scene.en4.is_alive()) && (!scene.en5.is_alive())) {
			scene.DisplayGameWin();
			win1 = true;
			//exit(0);
		}

		FlushBatchDraw(); // 批量绘制
		timer.Sleep(50); // 暂停若干毫秒

	}
	void updateWithoutInput() // 和输入无关的更新
	{
		magicrelieve++;//自动回复法力
		if (magicrelieve == 100) {
			player.magic += 20;
			magicrelieve = 0;
		}
		if (player.health <= 0) {
			scene.DisplayGameOver();
			exit(0);
		}


		// 敌人自动更新位置
		if (scene.en1.is_alive())   scene.en1.update(player.x_left, player.y_bottom - player.height);
		if (scene.en2.is_alive())	scene.en2.update(player.x_left, player.y_bottom - player.height);
		if (scene.en3.is_alive())	scene.en3.update(player.x_left, player.y_bottom - player.height);
		if (scene.en4.is_alive()) {
			scene.en4.update(player.x_left, player.y_bottom - player.height);
		}
		if (scene.en5.is_alive()) {
			scene.en5.update(player.x_left, player.y_bottom - player.height);
		}
		//敌人死亡后为我方回复生命与法力
		if ((!scene.en1.is_alive()) && scene.en1.relieve == false) {
			scene.en1.relieve = true;
			player.health += 10;
			player.magic += 10;
			player.huiming = -player.huiming;
		}
		if ((!scene.en2.is_alive()) && scene.en2.relieve == false) {
			scene.en2.relieve = true;
			player.health += 10;
			player.magic += 10;
			player.huiming = -player.huiming;
		}
		if ((!scene.en3.is_alive()) && scene.en3.relieve == false) {
			scene.en3.relieve = true;
			player.health += 10;
			player.magic += 10;
			player.huiming = -player.huiming;
		}
		if ((player.isCollideEnemy(scene.en1) && scene.en1.is_alive()) || (player.isCollideEnemy(scene.en2) && scene.en2.is_alive()) || (player.isCollideEnemy(scene.en3) && scene.en3.is_alive())|| (player.isCollideEnemy(scene.en4) && scene.en4.is_alive())|| (player.isCollideEnemy(scene.en5) && scene.en5.is_alive()))
		{

			if (player.injured == false) {

				player.health -= 1;//敌人对角色造成伤害
				player.injured = true;
			}
			
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene.en1)) {
				if (scene.en1.hurt == false && player.magic > 0) {
					if (player.huiming == scene.en1.huiming)scene.en1.enemy_hp -= 5;//角色对敌人造成伤害，同属性减半，不同属性加倍
					else scene.en1.enemy_hp -= 10;
				}
				scene.en1.hurt = true;
			}
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene.en2)) {
				if (scene.en2.hurt == false && player.magic > 0) {
					if (player.huiming == scene.en2.huiming)scene.en2.enemy_hp -= 5;
					else scene.en2.enemy_hp -= 10;
				}
				scene.en2.hurt = true;
			}
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene.en3)) {
				if (scene.en3.hurt == false && player.magic > 0) {
					if (player.huiming == scene.en3.huiming)scene.en3.enemy_hp -= 5;
					else scene.en3.enemy_hp -= 10;
				}
				scene.en3.hurt = true;
			}
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene.en4)) {
				if (scene.en4.hurt == false && player.magic > 0) {
					if (player.huiming == scene.en4.huiming)scene.en4.enemy_hp -= 5;
					else scene.en4.enemy_hp -= 10;
				}
				scene.en4.hurt = true;
			}
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene.en5)) {
				if (scene.en5.hurt == false && player.magic > 0) {
					if (player.huiming == scene.en5.huiming)scene.en5.enemy_hp -= 5;
					else scene.en5.enemy_hp -= 10;
				}
				scene.en5.hurt = true;
			}
		}
		else {
			// 如果没有检测到新的碰撞，重置碰撞标志
			// if ((!player.isCollideEnemy(scene.en1))|| (!player.isCollideEnemy(scene.en2))) {
			if (!player.isCollideEnemy(scene.en1))scene.en1.hurt = false;
			if (!player.isCollideEnemy(scene.en2))scene.en2.hurt = false;
			if (!player.isCollideEnemy(scene.en3))scene.en3.hurt = false;
			if (!player.isCollideEnemy(scene.en4))scene.en4.hurt = false;
			if (!player.isCollideEnemy(scene.en5))scene.en5.hurt = false;
			player.injured = false;
		}


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
		}
	}
};