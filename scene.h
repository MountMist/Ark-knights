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
class Scene // ��Ϸ������
{
public:
	IMAGE im_bk;  // ����ͼ��	
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
			TCHAR s[20]; // �ַ���
			TCHAR TITLE[50];
			setbkmode(TRANSPARENT); // ����͸����ʾ
			swprintf_s(s, _T("����: %d "), hp); // ���������ַ���
			settextcolor(RED);  // ����������ɫ
			settextstyle(20, 0, _T("��������")); // �������ִ�С������
			outtextxy(50, 50, s); // �������
			swprintf_s(s, _T("����: %d "), ap); // ���������ַ���
			settextcolor(BLUE);  // ����������ɫ
			settextstyle(20, 0, _T("��������")); // �������ִ�С������
			outtextxy(50, 80, s); // �������
			settextcolor(BLACK);  // ����������ɫ
			settextstyle(20, 0, _T("��������")); // �������ִ�С������
			outtextxy(400, 100, _T("��һ�£�����ɽ"));
	}

	void initialize() // ��ʼ��
	{	

		loadimage(&im_bk, _T("background.png")); // ���뱳��ͼƬ
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
	//��ʾ��Ϸʧ��
	void DisplayGameOver() {
		//MessageBox(NULL, TEXT("Ϧ�ڻ�������ʧ�ˣ�����������"), TEXT("��Ϸʧ��"), MB_OK);
		while (1) {
			putimagePng(0, 0, &LOSE);
			if (_kbhit()) {
				if (GetAsyncKeyState(' '))break;
			}
		}
	}

	// ��ʾ��Ϸʤ��
	void DisplayGameWin() {
		//MessageBox(NULL, TEXT("You Win"), TEXT("Game Status"), MB_OK);
		settextcolor(BLACK);  // ����������ɫ
		settextstyle(40, 0, _T("�����п�")); // �������ִ�С������
		outtextxy(450, 300, _T("������ɡ���"));
		putimagePng(800, 400, &im_next);
	}
};
class Scene2 // ��Ϸ������
{
public:
	IMAGE im_bk;  // ����ͼ��	
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
		TCHAR s[20]; // �ַ���
		TCHAR TITLE[50];
		setbkmode(TRANSPARENT); // ����͸����ʾ
		swprintf_s(s, _T("����: %d "), hp); // ���������ַ���
		settextcolor(RED);  // ����������ɫ
		settextstyle(20, 0, _T("��������")); // �������ִ�С������
		outtextxy(50, 50, s); // �������
		swprintf_s(s, _T("����: %d "), ap); // ���������ַ���
		settextcolor(BLUE);  // ����������ɫ
		settextstyle(20, 0, _T("��������")); // �������ִ�С������
		outtextxy(50, 80, s); // �������
		settextcolor(BLACK);  // ����������ɫ
		settextstyle(20, 0, _T("��������")); // �������ִ�С������
		outtextxy(400, 100, _T("�ڶ��£��뽭��"));
	//	swprintf_s(s, _T("����ʱ��: %d "), en2.deathtime); // ���������ַ���
	//	outtextxy(400, 200,s);
	}

	void initialize() // ��ʼ��
	{
		//enemies.clear();
		//enemies.resize(3);
		loadimage(&im_bk, _T("background2.png")); // ���뱳��ͼƬ
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
	//��ʾ��Ϸʧ��
	void DisplayGameOver() {
		//MessageBox(NULL, TEXT("Ϧ�ڻ�������ʧ�ˣ�����������"), TEXT("��Ϸʧ��"), MB_OK);
		while (1) {
			putimagePng(0, 0, &LOSE);
			if (_kbhit()) {
				if (GetAsyncKeyState(' '))break;
			}
		}
	}

	// ��ʾ��Ϸʤ��
	void DisplayGameWin() {
		//MessageBox(NULL, TEXT("You Win"), TEXT("Game Status"), MB_OK);
		settextcolor(BLACK);  // ����������ɫ
		settextstyle(40, 0, _T("�����п�")); // �������ִ�С������
		outtextxy(450, 300, _T("������ɡ���"));
		putimagePng(800, 400, &im_next);
	}
};
class Scene3 // ��Ϸ������
{
public:
	IMAGE im_bk;  // ����ͼ��	
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
		TCHAR s[20]; // �ַ���
		TCHAR TITLE[50];
		setbkmode(TRANSPARENT); // ����͸����ʾ
		swprintf_s(s, _T("����: %d "), hp); // ���������ַ���
		settextcolor(RED);  // ����������ɫ
		settextstyle(20, 0, _T("��������")); // �������ִ�С������
		outtextxy(50, 50, s); // �������
		swprintf_s(s, _T("����: %d "), ap); // ���������ַ���
		settextcolor(BLUE);  // ����������ɫ
		settextstyle(20, 0, _T("��������")); // �������ִ�С������
		outtextxy(50, 80, s); // �������
		settextcolor(BLACK);  // ����������ɫ
		settextstyle(20, 0, _T("��������")); // �������ִ�С������
		outtextxy(400, 100, _T("�����£����Ź�"));
		
	}

	void initialize() // ��ʼ��
	{
		//enemies.clear();
		//enemies.resize(3);
		loadimage(&im_bk, _T("background3.png")); // ���뱳��ͼƬ
		loadimage(&im_next, _T("NEXT.png"));
		loadimage(&im_skill3, _T("Dusk/д��ʤ��.png"));
		loadimage(&im_energy_skill3, _T("Dusk/energy.png"));
		loadimage(&im_boss_die, _T("EnemyDie/enemy_L3_ZZ_die.png"));
		loadimage(&LOSE, _T("lose.png"));
	}
	//��ʾ��Ϸʧ��
	void DisplayGameOver() {
		//MessageBox(NULL, TEXT("Ϧ�ڻ�������ʧ�ˣ�����������"), TEXT("��Ϸʧ��"), MB_OK);
		while (1) { 
			putimagePng(0, 0, &LOSE);
			if (_kbhit()) {
				if (GetAsyncKeyState(' '))break;
			}
		}
	}

	// ��ʾ��Ϸʤ��
	void DisplayGameWin() {
		//MessageBox(NULL, TEXT("You Win"), TEXT("Game Status"), MB_OK);
		settextcolor(BLACK);  // ����������ɫ
		settextstyle(40, 0, _T("�����п�")); // �������ִ�С������
		outtextxy(450, 300, _T("������ɡ���"));
		putimagePng(800, 400, &im_next);
		putimagePng(600, 200, &im_boss_die);
	}
};