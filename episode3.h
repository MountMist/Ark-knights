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
	Player player;  // ������ҿ��Ƶ���Ϸ��ɫ����
	Scene3 scene3;  // ���峡��ȫ�ֶ���
	int  magicrelieve = 0;
	int zzx;
	int skilldelay = 0;
	bool win3 = false;
	int xuli = 0;
	Timer timer;  // ���ھ�ȷ��ʱ
	BOSS ZZ;
	void initialize(Player p) {
		scene3.initialize();  // ������ʼ��
		ZZ.initialize(600,100);
		player = p;
	}

	void fade_in() {
		TCHAR text[50] = _T("�����죬�ʾ���Ƹ��Ѻ�");
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
		TCHAR text[50] = _T("�����죬�ʾ���Ƹ��Ѻ�");
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

	void show3()  // ��ʾ
	{
		
		scene3.draw(player.energy);   // ��ʾ���������Ϣ
		scene3.drawtext(player.health, player.magic);
		if (ZZ.boss_hp<=0) {
			ZZ.boss_hp = 0;
			scene3.DisplayGameWin();
			win3 = true;
			//exit(0);
		}
		player.draw();  // ��ʾ��������Ϣ
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
		FlushBatchDraw(); // ��������
		timer.Sleep(50); // ��ͣ���ɺ���
	}
	void updateWithInput() // �������йصĸ���
	{
		player.standStill(); // ��Ϸ��ɫĬ��Ϊ��������Ҿ�ֹվ��

		if (_kbhit()) // ������ʱ���л���ɫ��ʾͼƬ������λ��
		{
			if(!win3)if (player.x_left >= 500)player.x_left = 500;//ʤ��ͨ�غ���Լ��������ߣ������ܼ���������
			if (player.x_left <= 0)player.x_left = 0;
			if (player.y_bottom >= 600)player.y_bottom = 600;
		//	if (player.y_bottom <= 30)player.y_bottom = 30;
			if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))  // ����D�����ҷ����
			{
				player.runRight();
				//player.standStill();
			}
			else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// ����A���������
			{
				player.runLeft();
				//player.standStill();
			}
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))     // ����W�����Ϸ����
			{
				player.runUp();
				//player.standStill();
			}
			if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))     // ����W�����Ϸ����
			{
				player.runDown();
				//player.standStill();
			}
			if (GetAsyncKeyState('J') && (player.playerStatus == runleft || player.playerStatus == atkleft || player.playerStatus == rundown) && player.magic > 0)// ���󹥻�
			{
				player.atkLeft();
				player.standStill();
				//player.magic--;
			}
			if (GetAsyncKeyState('J') && (player.playerStatus == runright || player.playerStatus == atkright || player.playerStatus == runup) && player.magic > 0)   // ���󹥻�
			{
				player.atkRight();
				player.standStill();
				//player.magic--;
			}
			if (GetAsyncKeyState('K')&&(player.playerStatus == runleft || player.playerStatus == atkleft || player.playerStatus == rundown))     // ����K��ʹ�ü���
			{
				player.skill3Left();
				player.isskill3 = true;
				zzx = player.x_left;
			}
			if (GetAsyncKeyState('K') && (player.playerStatus == runright || player.playerStatus == atkright || player.playerStatus == runup)&&player.energy>=5)     // ����K��ʹ�ü���
			{
				player.skill3Right();
				player.isskill3 = true;
				xuli++;
				zzx = player.x_left;
				
			}
		}
	}
	void updateWithoutInput3() {
		magicrelieve++;//�Զ��ظ�����
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
	
