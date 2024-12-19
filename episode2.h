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
	Player player;  // ������ҿ��Ƶ���Ϸ��ɫ����
	Scene2 scene2;  // ���峡��ȫ�ֶ���
	int  magicrelieve = 0;
	bool win2 = false;
	Timer timer;  // ���ھ�ȷ��ʱ
	bool isskill2 = false;
	void initialize(Player p) {
		scene2.initialize();  // ������ʼ��
		player = p;
	}

	void fade_in() {
		TCHAR text[50] = _T("�����죬��ġ����δ��˼");
		LOGFONT font;
		//gettextstyle(&font);
		//settextstyle(20, 0, _T("��������"));
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
			settextstyle(80, 0, _T("�����п�"));
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

	// ���ֵ���
	void fade_out() {
		TCHAR text[50] = _T("�����죬��ġ����δ��˼");
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
			settextstyle(80, 0, _T("�����п�"));
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

	void show2()  // ��ʾ
	{
		scene2.draw();   // ��ʾ���������Ϣ
		scene2.drawtext(player.health, player.magic);
		player.draw();  // ��ʾ��������Ϣ
		if ((!scene2.en1.is_alive()) && (!scene2.en2.is_alive()) && (!scene2.en3.is_alive())) {
			scene2.DisplayGameWin();
			win2 = true;
			//exit(0);
		}
		FlushBatchDraw(); // ��������
		timer.Sleep(50); // ��ͣ���ɺ���
	}
	void updateWithoutInput2() // �������޹صĸ���
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


		// �����Զ�����λ��
		if (scene2.en1.is_alive())   scene2.en1.update(player.x_left, player.y_bottom - player.height);
		if (scene2.en2.is_alive())	scene2.en2.update(player.x_left, player.y_bottom - player.height);
		if (scene2.en3.is_alive())	scene2.en3.update(player.x_left, player.y_bottom - player.height);
		if (scene2.en4.is_alive()) {
			scene2.en4.update(player.x_left, player.y_bottom - player.height);
		
		}
		if (scene2.en5.is_alive()) {
			scene2.en5.update(player.x_left, player.y_bottom - player.height);
			
		}
		//����������Ϊ�ҷ��ظ������뷨��
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
			// ���û�м�⵽�µ���ײ��������ײ��־
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
	void updateWithInput() // �������йصĸ���
	{
		player.standStill(); // ��Ϸ��ɫĬ��Ϊ��������Ҿ�ֹվ��

		if (_kbhit()) // ������ʱ���л���ɫ��ʾͼƬ������λ��
		{
			if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))  // ����D�����ҷ����
			{
				player.runRight();
			}
			else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// ����A���������
			{
				player.runLeft();
			}
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))     // ����W�����Ϸ����
			{
				player.runUp();
			}
			if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))     // ����W�����Ϸ����
			{
				player.runDown();
			}
			if (GetAsyncKeyState('J') && (player.playerStatus == runleft || player.playerStatus == atkleft || player.playerStatus == rundown) && player.magic > 0)   // ���󹥻�
			{
				player.atkLeft();
				//player.magic--;
			}
			if (GetAsyncKeyState('J') && (player.playerStatus == runright || player.playerStatus == atkright || player.playerStatus == runup) && player.magic > 0)   // ���󹥻�
			{
				player.atkRight();
				//player.magic--;
			}
			if (GetAsyncKeyState('K') && (player.playerStatus == runleft || player.playerStatus == atkleft || player.playerStatus == rundown) && player.magic > 0)   // ���󹥻�
			{
				player.skill2Left();
				isskill2 = true;
				//player.magic--;
			}
			if (GetAsyncKeyState('K') && (player.playerStatus == runright || player.playerStatus == atkright || player.playerStatus == runup) && player.magic > 0)   // ���󹥻�
			{
				player.skill2Right();
				isskill2 = true;
				//player.magic--;
			}
		}
	}
};