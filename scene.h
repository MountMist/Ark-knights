#pragma once
#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include"enemy.h"
#define  WIDTH 800  
#define  HEIGHT 600
using namespace std;
class Scene // 游戏场景类
{
public:
	IMAGE im_bk;  // 背景图像	
	IMAGE im_next;
	IMAGE guide1;
	Timer timer;
	IMAGE LOSE;
	Enemy en1, en2,en4;
	EnemyXZ en3,en5;
	
	int enemynum = 3;
	bool start1 = false;
	


	void draw()
	{
		
		putimage(0, 0, &im_bk);      

		if (en1.enemy_hp > 0)en1.draw();
		else en1.drawdie();
		if (en2.enemy_hp > 0)en2.draw();
		else en2.drawdie();
		if (en3.enemy_hp > 0)en3.draw();
		else en3.drawdie();
		if (en4.enemy_hp > 0)en4.draw();
		else en4.drawdie();
		if (en5.enemy_hp > 0)en5.draw();
		else en5.drawdie();
			
			
	}
	void drawtext(int hp, int ap) {
			TCHAR s[20]; // 字符串
			TCHAR TITLE[50];
			setbkmode(TRANSPARENT); // 文字透明显示
			swprintf_s(s, _T("生命: %d "), hp); // 生成文字字符串
			settextcolor(RED);  // 设置文字颜色
			settextstyle(20, 0, _T("华文隶书")); // 设置文字大小、字体
			outtextxy(50, 50, s); // 输出文字
			swprintf_s(s, _T("法力: %d "), ap); // 生成文字字符串
			settextcolor(BLUE);  // 设置文字颜色
			settextstyle(20, 0, _T("华文隶书")); // 设置文字大小、字体
			outtextxy(50, 80, s); // 输出文字
			settextcolor(BLACK);  // 设置文字颜色
			settextstyle(20, 0, _T("华文隶书")); // 设置文字大小、字体
			outtextxy(400, 100, _T("第一章：灰齐山"));
	}

	void initialize() // 初始化
	{	

		loadimage(&im_bk, _T("background.png")); // 导入背景图片
		loadimage(&im_next, _T("NEXT.png"));
		loadimage(&guide1, _T("guide1.png"));
		loadimage(&LOSE, _T("lose.png"));
		int Xmax = 1200, Xmin = -30;
		int Ymax = 900, Ymin = -30;
			en1.initialize((rand() % (Xmax - Xmin + 1)) + Xmin, (rand() % (Ymax - Ymin + 1)) + Ymin);
			en2.initialize((rand() % (Xmax - Xmin + 1)) + Xmin, (rand() % (Ymax - Ymin + 1)) + Ymin);
			en3.initialize((rand() % (Xmax - Xmin + 1)) + Xmin, (rand() % (Ymax - Ymin + 1)) + Ymin);
			en4.initialize((rand() % (Xmax - Xmin + 1)) + Xmin, (rand() % (Ymax - Ymin + 1)) + Ymin);
			en5.initialize((rand() % (Xmax - Xmin + 1)) + Xmin, (rand() % (Ymax - Ymin + 1)) + Ymin);
		
		
	}
	//显示游戏失败
	void DisplayGameOver() {
		//MessageBox(NULL, TEXT("夕在画境中迷失了，重新来过吧"), TEXT("游戏失败"), MB_OK);
		while (1) {
			putimagePng(0, 0, &LOSE);
			if (_kbhit()) {
				if (GetAsyncKeyState(' '))break;
			}
		}
	}

	// 显示游戏胜利
	void DisplayGameWin() {
		//MessageBox(NULL, TEXT("You Win"), TEXT("Game Status"), MB_OK);
		settextcolor(BLACK);  // 设置文字颜色
		settextstyle(40, 0, _T("华文行楷")); // 设置文字大小、字体
		outtextxy(450, 300, _T("——完成——"));
		putimagePng(800, 400, &im_next);
	}
};
class Scene2 // 游戏场景类
{
public:
	IMAGE im_bk;  // 背景图像	
	IMAGE im_next;
	IMAGE LOSE;
	//vector<Enemy> enemies;

	EnemyMP en1,en4,en5;
	EnemyCS en2, en3;

	int enemynum = 3;


	void draw()
	{
		putimage(0, 0, &im_bk);

		if (en1.enemy_hp > 0)en1.draw();
		else en1.drawdie();
		if (en2.enemy_hp > 0)en2.draw();
		else en2.drawdie();
		if (en3.enemy_hp > 0)en3.draw();
		else en3.drawdie();
		if (en4.enemy_hp > 0)en4.draw();
		else en4.drawdie();
		if (en5.enemy_hp > 0)en5.draw();
		else en5.drawdie();


	}
	void drawtext(int hp, int ap) {
		TCHAR s[20]; // 字符串
		TCHAR TITLE[50];
		setbkmode(TRANSPARENT); // 文字透明显示
		swprintf_s(s, _T("生命: %d "), hp); // 生成文字字符串
		settextcolor(RED);  // 设置文字颜色
		settextstyle(20, 0, _T("华文隶书")); // 设置文字大小、字体
		outtextxy(50, 50, s); // 输出文字
		swprintf_s(s, _T("法力: %d "), ap); // 生成文字字符串
		settextcolor(BLUE);  // 设置文字颜色
		settextstyle(20, 0, _T("华文隶书")); // 设置文字大小、字体
		outtextxy(50, 80, s); // 输出文字
		settextcolor(BLACK);  // 设置文字颜色
		settextstyle(20, 0, _T("华文隶书")); // 设置文字大小、字体
		outtextxy(400, 100, _T("第二章：纂江峰"));
	//	swprintf_s(s, _T("死亡时间: %d "), en2.deathtime); // 生成文字字符串
	//	outtextxy(400, 200,s);
	}

	void initialize() // 初始化
	{
		//enemies.clear();
		//enemies.resize(3);
		loadimage(&im_bk, _T("background2.png")); // 导入背景图片
		loadimage(&im_next, _T("NEXT.png"));
		loadimage(&LOSE, _T("lose.png"));
		//Enemy en;
		en1.initialize(50, 20);
		//enemies.push_back(en);
		//Enemy en2;
		en2.initialize(500, 400);
		//enemies.push_back(en2);
		en3.initialize(700, 300);
		en4.initialize(850, 100);
		en5.initialize(60, 500);


	}
	//显示游戏失败
	void DisplayGameOver() {
		//MessageBox(NULL, TEXT("夕在画境中迷失了，重新来过吧"), TEXT("游戏失败"), MB_OK);
		while (1) {
			putimagePng(0, 0, &LOSE);
			if (_kbhit()) {
				if (GetAsyncKeyState(' '))break;
			}
		}
	}

	// 显示游戏胜利
	void DisplayGameWin() {
		//MessageBox(NULL, TEXT("You Win"), TEXT("Game Status"), MB_OK);
		settextcolor(BLACK);  // 设置文字颜色
		settextstyle(40, 0, _T("华文行楷")); // 设置文字大小、字体
		outtextxy(450, 300, _T("——完成——"));
		putimagePng(800, 400, &im_next);
	}
};
class Scene3 // 游戏场景类
{
public:
	IMAGE im_bk;  // 背景图像	
	IMAGE im_next;
	IMAGE im_skill3;
	IMAGE im_energy_skill3;
	IMAGE im_boss_die;
	IMAGE LOSE;
	void draw(int energynum)
	{
		putimage(0, 0, &im_bk);
		//setfillcolor(GREEN);
		for (int i = 1; i <= energynum; i++) {
			//fillcircle(20 + i * 50, 500, 20);
			if (i != 5)putimagePng(-10 + i * 70, 500, &im_energy_skill3);
			if (i == 5)putimagePng(i * 70 - 10, 500, &im_skill3);
		}
	}
	void drawtext(int hp, int ap) {
		TCHAR s[20]; // 字符串
		TCHAR TITLE[50];
		setbkmode(TRANSPARENT); // 文字透明显示
		swprintf_s(s, _T("生命: %d "), hp); // 生成文字字符串
		settextcolor(RED);  // 设置文字颜色
		settextstyle(20, 0, _T("华文隶书")); // 设置文字大小、字体
		outtextxy(50, 50, s); // 输出文字
		swprintf_s(s, _T("法力: %d "), ap); // 生成文字字符串
		settextcolor(BLUE);  // 设置文字颜色
		settextstyle(20, 0, _T("华文隶书")); // 设置文字大小、字体
		outtextxy(50, 80, s); // 输出文字
		settextcolor(BLACK);  // 设置文字颜色
		settextstyle(20, 0, _T("华文隶书")); // 设置文字大小、字体
		outtextxy(400, 100, _T("第三章：玉门关"));
		
	}

	void initialize() // 初始化
	{
		//enemies.clear();
		//enemies.resize(3);
		loadimage(&im_bk, _T("background3.png")); // 导入背景图片
		loadimage(&im_next, _T("NEXT.png"));
		loadimage(&im_skill3, _T("Dusk/写意胜形.png"));
		loadimage(&im_energy_skill3, _T("Dusk/energy.png"));
		loadimage(&im_boss_die, _T("EnemyDie/enemy_L3_ZZ_die.png"));
		loadimage(&LOSE, _T("lose.png"));
	}
	//显示游戏失败
	void DisplayGameOver() {
		//MessageBox(NULL, TEXT("夕在画境中迷失了，重新来过吧"), TEXT("游戏失败"), MB_OK);
		while (1) { 
			putimagePng(0, 0, &LOSE);
			if (_kbhit()) {
				if (GetAsyncKeyState(' '))break;
			}
		}
	}

	// 显示游戏胜利
	void DisplayGameWin() {
		//MessageBox(NULL, TEXT("You Win"), TEXT("Game Status"), MB_OK);
		settextcolor(BLACK);  // 设置文字颜色
		settextstyle(40, 0, _T("华文行楷")); // 设置文字大小、字体
		outtextxy(450, 300, _T("——完成——"));
		putimagePng(800, 400, &im_next);
		putimagePng(600, 200, &im_boss_die);
	}
};