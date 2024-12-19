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
	Player player;  // ������ҿ��Ƶ���Ϸ��ɫ����
	Scene scene;  // ���峡��ȫ�ֶ���
	Timer timer;  // ���ھ�ȷ��ʱ
	int  magicrelieve = 0;
	bool win1 = false;
	void initialize(Player p) {
		scene.initialize();  // ������ʼ��
		player = p;
	}

	void fade_in() {
		TCHAR text[50] = _T("һ���죬�Ծ�����չ����");
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
		TCHAR text[50] = _T("һ���죬�Ծ�����չ����");
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

	void show()  // ��ʾ
	{
		scene.draw();   // ��ʾ���������Ϣ
		scene.drawtext(player.health, player.magic);
		player.draw();  // ��ʾ��������Ϣ
		//���ƻ�������
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

		FlushBatchDraw(); // ��������
		timer.Sleep(50); // ��ͣ���ɺ���

	}
	void updateWithoutInput() // �������޹صĸ���
	{
		magicrelieve++;//�Զ��ظ�����
		if (magicrelieve == 100) {
			player.magic += 20;
			magicrelieve = 0;
		}
		if (player.health <= 0) {
			scene.DisplayGameOver();
			exit(0);
		}


		// �����Զ�����λ��
		if (scene.en1.is_alive())   scene.en1.update(player.x_left, player.y_bottom - player.height);
		if (scene.en2.is_alive())	scene.en2.update(player.x_left, player.y_bottom - player.height);
		if (scene.en3.is_alive())	scene.en3.update(player.x_left, player.y_bottom - player.height);
		if (scene.en4.is_alive()) {
			scene.en4.update(player.x_left, player.y_bottom - player.height);
		}
		if (scene.en5.is_alive()) {
			scene.en5.update(player.x_left, player.y_bottom - player.height);
		}
		//����������Ϊ�ҷ��ظ������뷨��
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

				player.health -= 1;//���˶Խ�ɫ����˺�
				player.injured = true;
			}
			
			if ((player.playerStatus == atkleft || player.playerStatus == atkright) && player.isCollideEnemy(scene.en1)) {
				if (scene.en1.hurt == false && player.magic > 0) {
					if (player.huiming == scene.en1.huiming)scene.en1.enemy_hp -= 5;//��ɫ�Ե�������˺���ͬ���Լ��룬��ͬ���Լӱ�
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
			// ���û�м�⵽�µ���ײ��������ײ��־
			// if ((!player.isCollideEnemy(scene.en1))|| (!player.isCollideEnemy(scene.en2))) {
			if (!player.isCollideEnemy(scene.en1))scene.en1.hurt = false;
			if (!player.isCollideEnemy(scene.en2))scene.en2.hurt = false;
			if (!player.isCollideEnemy(scene.en3))scene.en3.hurt = false;
			if (!player.isCollideEnemy(scene.en4))scene.en4.hurt = false;
			if (!player.isCollideEnemy(scene.en5))scene.en5.hurt = false;
			player.injured = false;
		}


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
		}
	}
};