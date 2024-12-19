#pragma once
#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include"scene.h"
#include"enemy.h"
//#include"BOSS.h"
using namespace std;
#define  WIDTH 1000  
#define  HEIGHT 600
enum PlayerStatus // ö�����ͣ���Ϸ��ɫ���еĿ���״̬
{
	standleft, standright, runleft, runright, runup, rundown, atkleft, atkright
};

class Player  // ��ҿ��Ƶ���Ϸ��ɫ��
{
public:
	IMAGE im_show;  // ��ǰʱ��Ҫ��ʾ��ͼ��
	IMAGE im_standright; // ����վ��ͼ��
	IMAGE im_standleft; // ����վ��ͼ��
	IMAGE littleZZ;	//С���ڵ�ͼƬ
	vector <IMAGE> ims_runright; // ���ұ��ܵ�ͼ������
	vector <IMAGE> ims_runleft; // �����ܵ�ͼ������
	vector <IMAGE> ims_atkright; // ���ҹ�����ͼ������
	vector <IMAGE> ims_atkleft; // ���󹥻���ͼ������
	vector <IMAGE> ims_skill3left;//�����ܵ�ͼ������
	vector <IMAGE> ims_skill3right;//���Ҽ��ܵ�ͼ������
	vector <IMAGE> ims_skill2left;//�����ܵ�ͼ������
	vector <IMAGE> ims_skill2right;//���Ҽ��ܵ�ͼ������

	int animId;  // ����ѭ���������ŵ�id
	PlayerStatus playerStatus; // ��ǰ��״̬
	float x_left, y_bottom; // ����������²�����
	
	float v; // �ٶ�
	float width, height; // ͼƬ�Ŀ�ȡ��߶�
	bool injured;//�Ƿ񱻹���
	int health;//����ֵ
	int magic;//����ֵ
	float x_right;
	float y_top;
	int huiming = 1;
	bool isskill3 = false;
	int energy = 0;//�������Ի������
	void draw()// ��ʾ�����Ϣ	
	{
		putimagePng(x_left, y_bottom - height, &im_show);  // ��Ϸ����ʾ��ɫ
	}

	void initialize() // ��ʼ��
	{
		ims_runleft.clear(); // ����յ�vector
		ims_runright.clear();
		ims_skill3left.clear();
		ims_skill3right.clear();
		ims_skill2left.clear();
		ims_skill2right.clear();
		loadimage(&im_standright, _T("Dusk_standright.png")); // ��������վ��ͼƬ
		loadimage(&im_standleft, _T("Dusk_standleft.png")); // ��������վ��ͼƬ
		loadimage(&littleZZ, _T("Dusk/С����.png"));
		health = 100;
		magic = 50;
		injured = false;
		playerStatus = standright; // ��ʼΪ����վ������Ϸ״̬
		im_show = im_standright;  // ��ʼ��ʾ����վ����ͼƬ
		width = im_standright.getwidth(); // ���ͼ��Ŀ��ߣ����ж���ͼƬ��Сһ��
		height = im_standright.getheight();

		TCHAR filename[80];
		for (int i = 0; i <= 7; i++) // �����ұ��ܵİ���ͼƬ������ӵ�ims_runright��
		{
			swprintf_s(filename, _T("Dusk/move_right/move_right%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_runright.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // �������ܵİ���ͼƬ������ӵ�ims_runleft��
		{
			swprintf_s(filename, _T("Dusk/move_left/move_left%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_runleft.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // �����󹥻���12��ͼƬ������ӵ�ims_atkleft��
		{
			swprintf_s(filename, _T("Dusk/ottack_left/otk_left%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_atkleft.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // �����ҹ�����12��ͼƬ������ӵ�ims_atkright��
		{
			swprintf_s(filename, _T("Dusk/ottack_right/otk_right%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_atkright.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // �����ҹ�����12��ͼƬ������ӵ�skill3_right��
		{
			swprintf_s(filename, _T("Dusk/skill2_right/skill2_right%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_skill3right.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // �����ҹ�����12��ͼƬ������ӵ�skill3_left��
		{
			swprintf_s(filename, _T("Dusk/skill2_left/skill2_left%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_skill3left.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // �����ҹ�����12��ͼƬ������ӵ�skill3_right��
		{
			swprintf_s(filename, _T("Dusk/skill3_right/skill3_right%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_skill2right.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // �����ҹ�����12��ͼƬ������ӵ�skill3_left��
		{
			swprintf_s(filename, _T("Dusk/skill3_left/skill3_left%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_skill2left.push_back(im);
		}
		animId = 0; // ����id��ʼ��Ϊ0
		v = 10;//��ʼ�ƶ��ٶ�Ϊ5
		updateXY(WIDTH / 2, HEIGHT / 2); // ��ʼ����ɫ���ڻ����м�

	}

	void updateXY(float mx, float my) // �������룬�����������
	{
		x_left = mx;
		y_bottom = my;
		
	}

	void runRight() // ��Ϸ��ɫ���ұ���
	{
		x_left += v; // ���������ӣ������ƶ�


		if (playerStatus != runright) // ���֮ǰ��ɫ״̬�������ұ���
		{
			playerStatus = runright; // �л�Ϊ���ұ���״̬
			animId = 0; // ��������id��ʼ��Ϊ0
		}
		else // ��ʾ֮ǰ�������ұ���״̬��
		{
			animId++; // ����ͼƬ��ʼ�л�
			if (animId >= ims_runright.size()) // ѭ���л�
				animId = 0;
		}
		im_show = ims_runright[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	 

	}

	void runLeft() // ��Ϸ��ɫ������
	{
		x_left -= v; // ��������٣������ƶ�		

		if (playerStatus != runleft) // ���֮ǰ��ɫ״̬����������
		{
			playerStatus = runleft; // �л�Ϊ������״̬
			animId = 0; // ��������id��ʼ��Ϊ0
		}
		else // ֮ǰ����������״̬��
		{
			animId++; // ����ͼƬ��ʼ�л�
			if (animId >= ims_runleft.size()) // ѭ���л�
				animId = 0;
		}
		im_show = ims_runleft[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	

	}
	void runUp() // ��Ϸ��ɫ���ϱ���
	{
		y_bottom -= v; // ��������٣������ƶ�		

		if (playerStatus != runup) // ���֮ǰ��ɫ״̬�������ϱ���
		{
			playerStatus = runup; // �л�Ϊ������״̬
			animId = 0; // ��������id��ʼ��Ϊ0
		}
		else // ֮ǰ�������ϱ���״̬��
		{
			animId++; // ����ͼƬ��ʼ�л�
			if (animId >= ims_runleft.size()) // ѭ���л�
				animId = 0;
		}
		im_show = ims_runright[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ�������������Ҵ���	

	}
	void runDown() // ��Ϸ��ɫ���±���
	{
		y_bottom += v; // ���������ӣ������ƶ�		

		if (playerStatus != rundown) // ���֮ǰ��ɫ״̬�������±���
		{
			playerStatus = rundown; // �л�Ϊ���±���״̬
			animId = 0; // ��������id��ʼ��Ϊ0
		}
		else // ֮ǰ�������±���״̬��
		{
			animId++; // ����ͼƬ��ʼ�л�
			if (animId >= ims_runleft.size()) // ѭ���л�
				animId = 0;
		}
		im_show = ims_runleft[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ�����������������	

	}
int animspeed = 0;
	void atkLeft() // ��Ϸ��ɫ���󹥻�
	{
		
			if (playerStatus != atkleft) // ���֮ǰ��ɫ״̬�������󹥻�
					{
						playerStatus = atkleft; // �л�Ϊ���󹥻�״̬
						animId = 0; // ��������id��ʼ��Ϊ0

					}
					else // ֮ǰ�������󹥻�״̬��
					{
						animspeed++;
						if(animspeed%2==0)animId++; // ����ͼƬ��ʼ�л�
			
						if (animId >= ims_atkleft.size()) {
							animId = 0;
					
						} // ѭ���л�
							
					}
		
					im_show = ims_atkleft[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ
		
					if (animspeed % 9 == 0)	magic-=5;
					if (magic <= 0)magic = 0;
	}
	void skill3Left() // ��Ϸ��ɫ���󹥻�
	{

		if (playerStatus != atkleft) // ���֮ǰ��ɫ״̬�������󹥻�
		{
			playerStatus = atkleft; // �л�Ϊ���󹥻�״̬
			animId = 0; // ��������id��ʼ��Ϊ0

		}
		else // ֮ǰ�������󹥻�״̬��
		{
			animspeed++;
			if (animspeed % 2 == 0)animId++; // ����ͼƬ��ʼ�л�

			if (animId >= ims_skill3left.size()) {
				animId = 0;

			} // ѭ���л�

		}

		im_show = ims_skill3left[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ

		//if (animspeed % 9 == 0)	magic -= 5;
		if (magic <= 0)magic = 0;
	}
	void skill2Left() // ��Ϸ��ɫ���󹥻�
	{

		if (playerStatus != atkleft) // ���֮ǰ��ɫ״̬�������󹥻�
		{
			playerStatus = atkleft; // �л�Ϊ���󹥻�״̬
			animId = 0; // ��������id��ʼ��Ϊ0

		}
		else // ֮ǰ�������󹥻�״̬��
		{
			animspeed++;
			if (animspeed % 2 == 0)animId++; // ����ͼƬ��ʼ�л�

			if (animId >= ims_skill2left.size()) {
				animId = 0;

			} // ѭ���л�

		}

		im_show = ims_skill2left[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ

		if (animspeed % 9 == 0)	magic -= 10;
		if (magic <= 0)magic = 0;
	}
	void atkRight() // ��Ϸ��ɫ���ҹ���
	{
		
			if (playerStatus != atkright) // ���֮ǰ��ɫ״̬�������ҹ���
			{
				playerStatus = atkright; // �л�Ϊ���ҹ���״̬
				animId = 0; // ��������id��ʼ��Ϊ0
			}
			else // ֮ǰ�������ҹ���״̬��
			{
				if (animspeed % 2 == 0)animId++; // ����ͼƬ��ʼ�л�
				animspeed++;
				if (animId >= ims_atkright.size()) // ѭ���л�
					animId = 0;
			}
			im_show = ims_atkright[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	
		
			if (animspeed % 9 == 0)	magic-=5;
			if (magic <= 0)magic = 0;
	}
	void skill3Right() // ��Ϸ��ɫ���ҹ���
	{

		if (playerStatus != atkright) // ���֮ǰ��ɫ״̬�������ҹ���
		{
			playerStatus = atkright; // �л�Ϊ���ҹ���״̬
			animId = 0; // ��������id��ʼ��Ϊ0
		}
		else // ֮ǰ�������ҹ���״̬��
		{
			if (animspeed % 2 == 0)animId++; // ����ͼƬ��ʼ�л�
			animspeed++;
			if (animId >= ims_skill3right.size()) // ѭ���л�
				animId = 0;
		}
		im_show = ims_skill3right[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	

		//if (animspeed % 9 == 0)	magic -= 5;
		if (magic <= 0)magic = 0;
	}
	void skill2Right() // ��Ϸ��ɫ���ҹ���
	{

		if (playerStatus != atkright) // ���֮ǰ��ɫ״̬�������ҹ���
		{
			playerStatus = atkright; // �л�Ϊ���ҹ���״̬
			animId = 0; // ��������id��ʼ��Ϊ0
		}
		else // ֮ǰ�������ҹ���״̬��
		{
			if (animspeed % 2 == 0)animId++; // ����ͼƬ��ʼ�л�
			animspeed++;
			if (animId >= ims_skill2right.size()) // ѭ���л�
				animId = 0;
		}
		im_show = ims_skill2right[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	

		if (animspeed % 9 == 0)	magic -= 10;
		if (magic <= 0)magic = 0;
	}
	void standStill() // ��Ϸ��ɫĬ��Ϊ��������Ҿ�ֹվ��
	{
		if (playerStatus == runleft || playerStatus == standleft)
		{
			im_show = im_standleft;
		}
		else if (playerStatus == runright || playerStatus == standright)
		{
			im_show = im_standright;
		}
	}

	int isCollideEnemy(Enemy& enemy)
	{
		x_right = x_left + width;
		y_top = y_bottom - height;
		float x_right_enemy = enemy.x + enemy.enemy_width;
		float y_top_enemy = enemy.y - enemy.enemy_height; // ͬ��ע��y�᷽��
		float x_left_enemy = enemy.x;
		float y_bottom_enemy = enemy.y;
		
		if (x_left< x_right_enemy && x_right > x_left_enemy &&
			y_bottom > y_top_enemy && y_top < y_bottom_enemy)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	int isCollideEnemy(EnemyXZ& enemy)
	{
		x_right = x_left + width;
		y_top = y_bottom - height;
		float x_right_enemy = enemy.x + enemy.enemy_width;
		float y_top_enemy = enemy.y - enemy.enemy_height; // ͬ��ע��y�᷽��
		float x_left_enemy = enemy.x;
		float y_bottom_enemy = enemy.y;

		if (x_left< x_right_enemy && x_right > x_left_enemy &&
			y_bottom > y_top_enemy && y_top < y_bottom_enemy)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	int isCollideEnemy(EnemyCS& enemy)
	{
		x_right = x_left + width;
		y_top = y_bottom - height;
		float x_right_enemy = enemy.x + enemy.enemy_width;
		float y_top_enemy = enemy.y - enemy.enemy_height; // ͬ��ע��y�᷽��
		float x_left_enemy = enemy.x;
		float y_bottom_enemy = enemy.y;

		if (x_left< x_right_enemy && x_right > x_left_enemy &&
			y_bottom > y_top_enemy && y_top < y_bottom_enemy)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	int isCollideEnemy(EnemyMP& enemy)
	{
		x_right = x_left + width;
		y_top = y_bottom - height;
		float x_right_enemy = enemy.x + enemy.enemy_width;
		float y_top_enemy = enemy.y - enemy.enemy_height; // ͬ��ע��y�᷽��
		float x_left_enemy = enemy.x;
		float y_bottom_enemy = enemy.y;

		if (x_left< x_right_enemy && x_right > x_left_enemy &&
			y_bottom > y_top_enemy && y_top < y_bottom_enemy)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	void CollideBullet(Bullet& bullet) {
		
		// ��ȡ�ӵ�����ҵİ뾶��
		float bulletRadius = bullet.im_bullet.getwidth() / 2.0f - 5; // ���ͼ���ȵ���ֱ��
		float playerRadius = this->width / 2.0f - 50; // ���� width ��ֱ��

		// ����Բ��֮��ľ���
		float dx = bullet.x + 0 - (this->x_left + playerRadius + 20); // ���Բ�ĵ� x ������ x_left + �뾶
		float dy = bullet.y + 10 - (this->y_bottom + playerRadius - 120); // ���Բ�ĵ� y ������ y_bottom + �뾶
		float distanceSquared = dx * dx + dy * dy;
		//setlinecolor(BLACK);
		//circle(this->x_left + playerRadius + 20, this->y_bottom + playerRadius - 120, playerRadius);
		//circle(bullet.x + 50, bullet.y + 10, bulletRadius);
		// �������Բ�Ƿ��ཻ
		float radiiSum = bulletRadius + playerRadius;
		if ((distanceSquared <= radiiSum * radiiSum) && playerStatus != atkleft && playerStatus != atkright) {
			// ���������ײ��������ҵ�����ֵ������ӵ�Ϊ������
			this->health -= 10;
			bullet.exisit = false;
		}
		if ((distanceSquared <= radiiSum * radiiSum) && (playerStatus == atkleft || playerStatus == atkright) && magic > 0) {
			// �ɹ���������Ϊ����
			this->energy++;
			if (energy >= 8)energy = 8;
			bullet.reverse = true;
			
		}
	}
	void skill2() {

	}
	void skill3(int ZZx) {
		
		putimagePng(ZZx, y_bottom - 100, &littleZZ);
		
	}
};