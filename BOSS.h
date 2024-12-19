#pragma once

#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include "EasyXPng.h"
#include "Timer.h"
#include"bullet.h"
#include"player.h"
using namespace std;

class BOSS
{
public:

	IMAGE im_enemy_frames_left[10]; // ���5�ŵ���ͼƬ������
	IMAGE im_enemy_frames_atk[10];
	IMAGE im_enemy;
	IMAGE im_show;
	IMAGE im_die;
	Bullet lightning[5];
	float x, y;
	float enemy_width, enemy_height;
	int enemystatus;//0��idle��1��attack
	float v;                                             // �ٶ�
	int frameIndex;     // ��ǰ����֡������
	int frameDelay;     // ����֡�л��ٶȵļ�����
	bool hurt;
	Timer timer;
	int boss_hp;
	bool relieve;	//����������Ϊ�ҷ��ظ������뷨��
	bool boss_alive;
	void initialize(int px, int py)
	{

		//im_enemy_frames_left.resize(4);
		//im_enemy_frames_atk.resize(4);
		TCHAR filename[50];

		for (int i = 0; i < 6; i++) {
			swprintf_s(filename, _T("Enemy/level3/ZZ-LOOP/enemy_L3_ZZ%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // ����ÿ��ͼƬ
		}
		for (int i = 0; i < 9; i++) {
			swprintf_s(filename, _T("Enemy/level3/ZZ-ATK/enemy_L3_ZZ%d.png"), i);
			loadimage(&im_enemy_frames_atk[i], filename); // ����ÿ��ͼƬ
		}

		loadimage(&im_die, _T("EnemyDie/enemy_L3_ZZ_die.png"));
		
		
		for (int i = 0; i < 5; i++) {
			int randnum = rand() % 6;
			lightning[i].initialize(800, 100 + 80 * i, 10 + randnum * 8);
		}

		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = 0;
		boss_hp = 1000;
		relieve = false;
		boss_alive = true;
	}

	void draw() {
		if (boss_hp <= 0) {
			putimagePng(x, y+500, &im_die);
			boss_alive=false;
		}
		else {
			if (enemystatus == 0) {
						if (frameDelay++ >= 5) { // ÿ5�ε����л�һ��ͼƬ
							frameIndex++;
							if (frameIndex == 6)frameIndex = 0;
							frameDelay = 0;
						}
			
							putimagePng(x, y, &im_enemy_frames_left[frameIndex]);
							timer.Sleep(50);

					}
					if (enemystatus == 1) {
						if (frameDelay++ >= 5) { // ÿ5�ε����л�һ��ͼƬ
							frameIndex++;
							if (frameIndex == 6)frameIndex = 0;
							frameDelay = 0;
						}
						putimagePng(x, y, &im_enemy_frames_atk[frameIndex]);
			

					}
		}
		
		TCHAR s[50];
		setbkmode(TRANSPARENT); // ����͸����ʾ
		swprintf_s(s, _T("��������: %d "), boss_hp); // ���������ַ���
		settextcolor(BLACK);  // ����������ɫ
		settextstyle(20, 0, _T("����")); // �������ִ�С������
		outtextxy(700, 100, s);
	}
	void atking(int playerx,int playery,Player &player)
	{
		
		if (enemystatus == 1) {
				//putimagePng(x, y, &im_enemy_frames_atk[0]);
			
				for (int i = 0; i < 5; i++) {
					if (lightning[i].exisit) {
							lightning[i].draw();		
							if(!lightning[i].reverse)lightning[i].update(playerx, playery);
							if (lightning[i].reverse) { 
								lightning[i].updateRe(); 
								if (lightning[i].x > 600)boss_hp -= 10;
							}
							lightning[i].check();
							player.CollideBullet(lightning[i]);
							
						}
						
								
				}
				
		}
		if (enemystatus == 0) {
			//putimagePng(x, y, &im_enemy_frames_left[0]);
			
			for (int i = 0; i < 5; i++) {
				lightning[i].renew(800, 100 + 80 * i, lightning[i].vx);
				lightning[i].reverse = false;
				lightning[i].exisit = true;
				
			}
		}
		
	}

	
	bool is_alive() {
		if (boss_hp > 0) {

			return 1;
		}
		else {
			return 0;
		}
	}
	void drawdie() {
		putimagePng(x, y, &im_die);
	}
	void bullet_reinitial() {
		for (int i = 0; i < 5; i++) {
			int randnum = rand() % 6;
			lightning[i].initialize(800, 100 + 80 * i, 10 + randnum * 8);
		}
	}
};