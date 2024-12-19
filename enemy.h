#pragma once
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include"bullet.h"

using namespace std;
enum EnemyStatus // ö�����ͣ���Ϸ��ɫ���еĿ���״̬
{
	 enemyleft, enemyright
};
class Enemy
{
public:
	vector<IMAGE> im_enemy_frames_right; // ���5�ŵ���ͼƬ������
	vector<IMAGE> im_enemy_frames_left; // ���5�ŵ���ͼƬ������
		
	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;
	float x, y;
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // �ٶ�
	int frameIndex;     // ��ǰ����֡������
	int frameDelay;     // ����֡�л��ٶȵļ�����
	bool hurt ;
	//��ҧ�Ļ�������
	int huiming = 1;
	int enemy_hp;
	bool relieve;	//����������Ϊ�ҷ��ظ������뷨��
	
	void initialize(int px,int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/right/AY/enemy_L1_AY%d.png"),i);
			loadimage(&im_enemy_frames_right[i], filename); // ����ÿ��ͼƬ
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/left/AY/enemy_L1_AY%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // ����ÿ��ͼƬ
		}
		
		loadimage(&im_enemy_injured_right, _T("Enemy/level1/right/AY/enemy_L1_AY0_injured_right.png")); // ����ÿ��ͼƬ
		loadimage(&im_enemy_injured_left, _T("Enemy/level1/left/AY/enemy_L1_AY0_injured_left.png")); // ����ÿ��ͼƬ
		loadimage(&im_die, _T("EnemyDie/enemy_L1_AY_die.png"));
		// ʹ�õ�һ��ͼƬ�ĳߴ���Ϊ���˳ߴ�
		enemy_width = im_enemy_injured_right.getwidth();
		enemy_height = im_enemy_injured_right.getheight();
		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = enemyright;
		enemy_hp = 50;//��ҧ��������Ӧ�ÿ��Ա�������
		relieve = false;
	}

	void draw()
	{
		setfillcolor(BLACK);
		fillcircle(x + enemy_width / 2, y, 10);
		if (enemystatus == enemyright) {
			if (hurt == false) {
						if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
									frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
									frameDelay = 0;
								}
						putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
					}				
					if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
					frameIndex = (frameIndex + 1) % im_enemy_frames_left.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_left[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_left);
		}

	}
		
	void update(float targetX, float targetY) {
		float dx = targetX - x;
		float dy = targetY - y;
		float distance = sqrt(dx * dx + dy * dy);

		// ��һ�����������ٶ�
		float vx = (dx / distance) * 2.0f;
		float vy = (dy / distance) * 2.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// ����λ��
		x += vx;
		y += vy;
	}
	bool is_alive() {
		if (enemy_hp > 0) {
			
			return 1;
		}
		else {
			return 0;
		}
	}
	void drawdie() {
		putimagePng(x, y, &im_die);
	}
};
class EnemyXZ
{
public:
	vector<IMAGE> im_enemy_frames_right; // ���5�ŵ���ͼƬ������
	vector<IMAGE> im_enemy_frames_left; // ���5�ŵ���ͼƬ������


	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;
	float x, y;
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // �ٶ�
	int frameIndex;     // ��ǰ����֡������
	int frameDelay;     // ����֡�л��ٶȵļ�����
	bool hurt;
	//С��Ļ�������
	int huiming = -1;
	int enemy_hp;
	bool relieve;	//����������Ϊ�ҷ��ظ������뷨��

	void initialize(int px, int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/right/XZ/enemy_L1_XZ%d.png"), i);
			loadimage(&im_enemy_frames_right[i], filename); // ����ÿ��ͼƬ
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/left/XZ/enemy_L1_XZ%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // ����ÿ��ͼƬ
		}

		loadimage(&im_enemy_injured_right, _T("Enemy/level1/right/XZ/enemy_L1_XZ_injured_right.png")); // ����ÿ��ͼƬ
		loadimage(&im_enemy_injured_left, _T("Enemy/level1/left/XZ/enemy_L1_XZ_injured_left.png")); // ����ÿ��ͼƬ
		loadimage(&im_die, _T("EnemyDie/enemy_L1_XZ_die.png"));
		
		// ʹ�õ�һ��ͼƬ�ĳߴ���Ϊ���˳ߴ�
		enemy_width = im_enemy_injured_right.getwidth();
		enemy_height = im_enemy_injured_right.getheight();
		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = enemyright;
		enemy_hp = 30;//С���������Ӧ�ÿ��Ա�������
		relieve = false;
	}

	void draw()
	{
		setfillcolor(LIGHTGRAY);
		fillcircle(x + enemy_width / 2, y, 10);
		if (enemystatus == enemyright) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
					frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
					frameIndex = (frameIndex + 1) % im_enemy_frames_left.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_left[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_left);
		}

	}

	void update(float targetX, float targetY) {
		float dx = targetX - x;
		float dy = targetY - y;
		float distance = sqrt(dx * dx + dy * dy);

		// ��һ�����������ٶ�
		float vx = (dx / distance) * 5.0f;
		float vy = (dy / distance) * 5.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// ����λ��
		x += vx;
		y += vy;
	}
	bool is_alive() {
		if (enemy_hp > 0) {

			return 1;
		}
		else {
			return 0;
		}
	}
	void drawdie() {
		putimagePng(x, y, &im_die);
	}
};
class EnemyBX
{
public:
	vector<IMAGE> im_enemy_frames_right; // ���5�ŵ���ͼƬ������
	vector<IMAGE> im_enemy_frames_left; // ���5�ŵ���ͼƬ������


	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;

	float x, y;	//��ǰλ������
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // �ٶ�
	int frameIndex;     // ��ǰ����֡������
	int frameDelay;     // ����֡�л��ٶȵļ�����
	bool hurt;

	int enemy_hp;
	bool relieve;	//����������Ϊ�ҷ��ظ������뷨��

	Bullet bullet;
	void initialize(int px, int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/right/BX/enemy_L1_BX%d.png"), i);
			loadimage(&im_enemy_frames_right[i], filename); // ����ÿ��ͼƬ
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/left/BX/enemy_L1_BX%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // ����ÿ��ͼƬ
		}

		loadimage(&im_enemy_injured_right, _T("Enemy/level1/right/BX/enemy_L1_BX_injured_right.png")); // ����ÿ��ͼƬ
		loadimage(&im_enemy_injured_left, _T("Enemy/level1/right/BX/enemy_L1_BX_injured_left.png")); // ����ÿ��ͼƬ
		loadimage(&im_die, _T("EnemyDie/enemy_L1_BX_die.png"));

		//bullet.initialize();
		// ʹ�õ�һ��ͼƬ�ĳߴ���Ϊ���˳ߴ�
		enemy_width = im_enemy_injured_right.getwidth();
		enemy_height = im_enemy_injured_right.getheight();
		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = enemyright;
		enemy_hp = 3;
		relieve = false;
		v = 3;
	}

	void draw()
	{
		if (enemystatus == enemyright) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
					frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
					frameIndex = (frameIndex + 1) % im_enemy_frames_left.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_left[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_left);
		}

	}

	void update(float targetX, float targetY) {
		float dx = targetX - x;
		float dy = targetY - y;
		float distance = sqrt(dx * dx + dy * dy);

		// ��һ�����������ٶ�
		float vx = (dx / distance) * 1.0f;
		float vy = (dy / distance) * 1.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// ����λ��
		x += vx;
		y += vy;
	}
	void BXmove() {
		
		y += v;
		if (y < 100 || y>500)v = -v;
		if (x < 500)enemystatus = enemyright;
		if (x > 500)enemystatus = enemyleft;
	}
	bool is_alive() {
		if (enemy_hp > 0) {

			return 1;
		}
		else {
			return 0;
		}
	}
	void drawdie() {
		putimagePng(x, y, &im_die);
	}
	void BXshoot() {
		
		if (bullet.x < 0 || bullet.x>1000) {
			bullet.x = x;
			bullet.y = y;
		}
		
			//if (x < 500)bullet.updateleft(y);
			//if (x > 500)bullet.updateright(y);
		
			//bullet.draw();
	}
};
class EnemyCS
{
public:
	vector<IMAGE> im_enemy_frames_right; // ���5�ŵ���ͼƬ������
	vector<IMAGE> im_enemy_frames_left; // ���5�ŵ���ͼƬ������

	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;
	float x, y;
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // �ٶ�
	int frameIndex;     // ��ǰ����֡������
	int frameDelay;     // ����֡�л��ٶȵļ�����
	bool hurt;

	int enemy_hp;
	bool relieve;	//����������Ϊ�ҷ��ظ������뷨��
	int deathtime = 0;//�������ʱ��һ��ʱ���Ḵ��
	void initialize(int px, int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level2/right/CS_MOV/enemy_L2_CS%d.png"), i);
			loadimage(&im_enemy_frames_right[i], filename); // ����ÿ��ͼƬ
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level2/left/CS_MOV/enemy_L2_CS%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // ����ÿ��ͼƬ
		}

		loadimage(&im_enemy_injured_right, _T("Enemy/level2/right/CS_MOV/enemy_L2_CS_injured_right.png")); // ����ÿ��ͼƬ
		loadimage(&im_enemy_injured_left, _T("Enemy/level2/left/CS_MOV/enemy_L2_CS_injured_left.png")); // ����ÿ��ͼƬ
		loadimage(&im_die, _T("EnemyDie/enemy_L2_CS_die.png"));
		// ʹ�õ�һ��ͼƬ�ĳߴ���Ϊ���˳ߴ�
		enemy_width = im_enemy_injured_right.getwidth();
		enemy_height = im_enemy_injured_right.getheight();
		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = enemyright;
		enemy_hp = 80;//��ɳ�����������Ա���8��
		relieve = false;
	}

	void draw()
	{
		if (enemystatus == enemyright) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
					frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
					frameIndex = (frameIndex + 1) % im_enemy_frames_left.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_left[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_left);
		}

	}

	void update(float targetX, float targetY) {
		float dx = targetX - x;
		float dy = targetY - y;
		float distance = sqrt(dx * dx + dy * dy);

		// ��һ�����������ٶ�
		float vx = (dx / distance) * 1.0f;
		float vy = (dy / distance) * 1.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// ����λ��
		x += vx;
		y += vy;
	}
	bool is_alive() {
		if (enemy_hp > 0) {

			return 1;
		}
		else {
			return 0;
		}
	}
	void drawdie() {
		putimagePng(x, y, &im_die);
		deathtime++;
		if (deathtime == 100) {
			enemy_hp = 80;
			deathtime = 0;
		}
	}
};
class EnemyMP
{
public:
	vector<IMAGE> im_enemy_frames_right; // ���5�ŵ���ͼƬ������
	vector<IMAGE> im_enemy_frames_left; // ���5�ŵ���ͼƬ������

	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;
	float x, y;
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // �ٶ�
	int frameIndex;     // ��ǰ����֡������
	int frameDelay;     // ����֡�л��ٶȵļ�����
	bool hurt;

	int enemy_hp;
	bool relieve;	//����������Ϊ�ҷ��ظ������뷨��
	int deathtime = 0;//�������ʱ�䣬��������һ��ʱ��Ḵ��
	void initialize(int px, int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level2/right/MP_MOV/enemy_L2_MP%d.png"), i);
			loadimage(&im_enemy_frames_right[i], filename); // ����ÿ��ͼƬ
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/left/MP_MOV/enemy_L2_MP%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // ����ÿ��ͼƬ
		}

		loadimage(&im_enemy_injured_right, _T("Enemy/level2/right/MP_MOV/enemy_L2_MP_injured_right.png")); // ����ÿ��ͼƬ
		loadimage(&im_enemy_injured_left, _T("Enemy/level2/left/MP_MOV/enemy_L2_MP_injured_left.png")); // ����ÿ��ͼƬ
		loadimage(&im_die, _T("EnemyDie/enemy_L2_MP_die.png"));
		// ʹ�õ�һ��ͼƬ�ĳߴ���Ϊ���˳ߴ�
		enemy_width = im_enemy_injured_right.getwidth();
		enemy_height = im_enemy_injured_right.getheight();
		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = enemyright;
		enemy_hp = 30;//ĥ�͵����������Ա�������
		relieve = false;
	}

	void draw()
	{
		if (enemystatus == enemyright) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
					frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // ÿ5�ε����л�һ��ͼƬ
					frameIndex = (frameIndex + 1) % im_enemy_frames_left.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_left[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_left);
		}

	}

	void update(float targetX, float targetY) {
		float dx = targetX - x;
		float dy = targetY - y;
		float distance = sqrt(dx * dx + dy * dy);

		// ��һ�����������ٶ�
		float vx = (dx / distance) * 5.0f;
		float vy = (dy / distance) * 5.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// ����λ��
		x += vx;
		y += vy;
	}
	bool is_alive() {
		if (enemy_hp > 0) {

			return 1;
		}
		else {
			return 0;
		}
	}
	void drawdie() {
		putimagePng(x, y, &im_die);
		deathtime++;
		if (deathtime == 100) {
			enemy_hp = 30;
			deathtime = 0;
		}
	}
};