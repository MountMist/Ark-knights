#pragma once
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include"bullet.h"

using namespace std;
enum EnemyStatus // 枚举类型，游戏角色所有的可能状态
{
	 enemyleft, enemyright
};
class Enemy
{
public:
	vector<IMAGE> im_enemy_frames_right; // 存放5张敌人图片的向量
	vector<IMAGE> im_enemy_frames_left; // 存放5张敌人图片的向量
		
	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;
	float x, y;
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // 速度
	int frameIndex;     // 当前动画帧的索引
	int frameDelay;     // 控制帧切换速度的计数器
	bool hurt ;
	//阿咬的晦明属性
	int huiming = 1;
	int enemy_hp;
	bool relieve;	//敌人死亡后为我方回复生命与法力
	
	void initialize(int px,int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/right/AY/enemy_L1_AY%d.png"),i);
			loadimage(&im_enemy_frames_right[i], filename); // 加载每张图片
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/left/AY/enemy_L1_AY%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // 加载每张图片
		}
		
		loadimage(&im_enemy_injured_right, _T("Enemy/level1/right/AY/enemy_L1_AY0_injured_right.png")); // 加载每张图片
		loadimage(&im_enemy_injured_left, _T("Enemy/level1/left/AY/enemy_L1_AY0_injured_left.png")); // 加载每张图片
		loadimage(&im_die, _T("EnemyDie/enemy_L1_AY_die.png"));
		// 使用第一张图片的尺寸作为敌人尺寸
		enemy_width = im_enemy_injured_right.getwidth();
		enemy_height = im_enemy_injured_right.getheight();
		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = enemyright;
		enemy_hp = 50;//阿咬的生命，应该可以被砍五下
		relieve = false;
	}

	void draw()
	{
		setfillcolor(BLACK);
		fillcircle(x + enemy_width / 2, y, 10);
		if (enemystatus == enemyright) {
			if (hurt == false) {
						if (frameDelay++ >= 3) { // 每5次调用切换一次图片
									frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
									frameDelay = 0;
								}
						putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
					}				
					if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // 每5次调用切换一次图片
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

		// 归一化方向并设置速度
		float vx = (dx / distance) * 2.0f;
		float vy = (dy / distance) * 2.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// 更新位置
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
	vector<IMAGE> im_enemy_frames_right; // 存放5张敌人图片的向量
	vector<IMAGE> im_enemy_frames_left; // 存放5张敌人图片的向量


	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;
	float x, y;
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // 速度
	int frameIndex;     // 当前动画帧的索引
	int frameDelay;     // 控制帧切换速度的计数器
	bool hurt;
	//小躁的晦明属性
	int huiming = -1;
	int enemy_hp;
	bool relieve;	//敌人死亡后为我方回复生命与法力

	void initialize(int px, int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/right/XZ/enemy_L1_XZ%d.png"), i);
			loadimage(&im_enemy_frames_right[i], filename); // 加载每张图片
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/left/XZ/enemy_L1_XZ%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // 加载每张图片
		}

		loadimage(&im_enemy_injured_right, _T("Enemy/level1/right/XZ/enemy_L1_XZ_injured_right.png")); // 加载每张图片
		loadimage(&im_enemy_injured_left, _T("Enemy/level1/left/XZ/enemy_L1_XZ_injured_left.png")); // 加载每张图片
		loadimage(&im_die, _T("EnemyDie/enemy_L1_XZ_die.png"));
		
		// 使用第一张图片的尺寸作为敌人尺寸
		enemy_width = im_enemy_injured_right.getwidth();
		enemy_height = im_enemy_injured_right.getheight();
		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = enemyright;
		enemy_hp = 30;//小躁的生命，应该可以被砍三下
		relieve = false;
	}

	void draw()
	{
		setfillcolor(LIGHTGRAY);
		fillcircle(x + enemy_width / 2, y, 10);
		if (enemystatus == enemyright) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // 每5次调用切换一次图片
					frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // 每5次调用切换一次图片
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

		// 归一化方向并设置速度
		float vx = (dx / distance) * 5.0f;
		float vy = (dy / distance) * 5.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// 更新位置
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
	vector<IMAGE> im_enemy_frames_right; // 存放5张敌人图片的向量
	vector<IMAGE> im_enemy_frames_left; // 存放5张敌人图片的向量


	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;

	float x, y;	//当前位置坐标
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // 速度
	int frameIndex;     // 当前动画帧的索引
	int frameDelay;     // 控制帧切换速度的计数器
	bool hurt;

	int enemy_hp;
	bool relieve;	//敌人死亡后为我方回复生命与法力

	Bullet bullet;
	void initialize(int px, int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/right/BX/enemy_L1_BX%d.png"), i);
			loadimage(&im_enemy_frames_right[i], filename); // 加载每张图片
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/left/BX/enemy_L1_BX%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // 加载每张图片
		}

		loadimage(&im_enemy_injured_right, _T("Enemy/level1/right/BX/enemy_L1_BX_injured_right.png")); // 加载每张图片
		loadimage(&im_enemy_injured_left, _T("Enemy/level1/right/BX/enemy_L1_BX_injured_left.png")); // 加载每张图片
		loadimage(&im_die, _T("EnemyDie/enemy_L1_BX_die.png"));

		//bullet.initialize();
		// 使用第一张图片的尺寸作为敌人尺寸
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
				if (frameDelay++ >= 3) { // 每5次调用切换一次图片
					frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // 每5次调用切换一次图片
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

		// 归一化方向并设置速度
		float vx = (dx / distance) * 1.0f;
		float vy = (dy / distance) * 1.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// 更新位置
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
	vector<IMAGE> im_enemy_frames_right; // 存放5张敌人图片的向量
	vector<IMAGE> im_enemy_frames_left; // 存放5张敌人图片的向量

	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;
	float x, y;
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // 速度
	int frameIndex;     // 当前动画帧的索引
	int frameDelay;     // 控制帧切换速度的计数器
	bool hurt;

	int enemy_hp;
	bool relieve;	//敌人死亡后为我方回复生命与法力
	int deathtime = 0;//死亡后计时，一段时间后会复活
	void initialize(int px, int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level2/right/CS_MOV/enemy_L2_CS%d.png"), i);
			loadimage(&im_enemy_frames_right[i], filename); // 加载每张图片
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level2/left/CS_MOV/enemy_L2_CS%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // 加载每张图片
		}

		loadimage(&im_enemy_injured_right, _T("Enemy/level2/right/CS_MOV/enemy_L2_CS_injured_right.png")); // 加载每张图片
		loadimage(&im_enemy_injured_left, _T("Enemy/level2/left/CS_MOV/enemy_L2_CS_injured_left.png")); // 加载每张图片
		loadimage(&im_die, _T("EnemyDie/enemy_L2_CS_die.png"));
		// 使用第一张图片的尺寸作为敌人尺寸
		enemy_width = im_enemy_injured_right.getwidth();
		enemy_height = im_enemy_injured_right.getheight();
		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = enemyright;
		enemy_hp = 80;//沉沙的生命，可以被砍8下
		relieve = false;
	}

	void draw()
	{
		if (enemystatus == enemyright) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // 每5次调用切换一次图片
					frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // 每5次调用切换一次图片
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

		// 归一化方向并设置速度
		float vx = (dx / distance) * 1.0f;
		float vy = (dy / distance) * 1.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// 更新位置
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
	vector<IMAGE> im_enemy_frames_right; // 存放5张敌人图片的向量
	vector<IMAGE> im_enemy_frames_left; // 存放5张敌人图片的向量

	IMAGE im_enemy;
	IMAGE im_enemy_injured_right;
	IMAGE im_enemy_injured_left;
	IMAGE im_show;
	IMAGE im_die;
	float x, y;
	float enemy_width, enemy_height;
	EnemyStatus enemystatus;
	float v;                                             // 速度
	int frameIndex;     // 当前动画帧的索引
	int frameDelay;     // 控制帧切换速度的计数器
	bool hurt;

	int enemy_hp;
	bool relieve;	//敌人死亡后为我方回复生命与法力
	int deathtime = 0;//死亡后的时间，当死亡后一段时间会复活
	void initialize(int px, int py)
	{
		im_enemy_frames_right.resize(4);
		im_enemy_frames_left.resize(4);
		TCHAR filename[50];
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level2/right/MP_MOV/enemy_L2_MP%d.png"), i);
			loadimage(&im_enemy_frames_right[i], filename); // 加载每张图片
		}
		for (int i = 0; i < 4; i++) {
			swprintf_s(filename, _T("Enemy/level1/left/MP_MOV/enemy_L2_MP%d.png"), i);
			loadimage(&im_enemy_frames_left[i], filename); // 加载每张图片
		}

		loadimage(&im_enemy_injured_right, _T("Enemy/level2/right/MP_MOV/enemy_L2_MP_injured_right.png")); // 加载每张图片
		loadimage(&im_enemy_injured_left, _T("Enemy/level2/left/MP_MOV/enemy_L2_MP_injured_left.png")); // 加载每张图片
		loadimage(&im_die, _T("EnemyDie/enemy_L2_MP_die.png"));
		// 使用第一张图片的尺寸作为敌人尺寸
		enemy_width = im_enemy_injured_right.getwidth();
		enemy_height = im_enemy_injured_right.getheight();
		im_show = im_enemy;
		frameIndex = 0;
		frameDelay = 0;
		hurt = false;
		x = px; y = py;
		enemystatus = enemyright;
		enemy_hp = 30;//磨磐的生命，可以被砍三下
		relieve = false;
	}

	void draw()
	{
		if (enemystatus == enemyright) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // 每5次调用切换一次图片
					frameIndex = (frameIndex + 1) % im_enemy_frames_right.size();
					frameDelay = 0;
				}
				putimagePng(x, y, &im_enemy_frames_right[frameIndex]);
			}
			if (hurt == true)	putimagePng(x, y, &im_enemy_injured_right);
		}
		if (enemystatus == enemyleft) {
			if (hurt == false) {
				if (frameDelay++ >= 3) { // 每5次调用切换一次图片
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

		// 归一化方向并设置速度
		float vx = (dx / distance) * 5.0f;
		float vy = (dy / distance) * 5.0f;
		if (dx < 0)enemystatus = enemyleft;
		else enemystatus = enemyright;
		// 更新位置
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