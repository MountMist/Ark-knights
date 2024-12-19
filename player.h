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
enum PlayerStatus // 枚举类型，游戏角色所有的可能状态
{
	standleft, standright, runleft, runright, runup, rundown, atkleft, atkright
};

class Player  // 玩家控制的游戏角色类
{
public:
	IMAGE im_show;  // 当前时刻要显示的图像
	IMAGE im_standright; // 向右站立图像
	IMAGE im_standleft; // 向左站立图像
	IMAGE littleZZ;	//小自在的图片
	vector <IMAGE> ims_runright; // 向右奔跑的图像序列
	vector <IMAGE> ims_runleft; // 向左奔跑的图像序列
	vector <IMAGE> ims_atkright; // 向右攻击的图像序列
	vector <IMAGE> ims_atkleft; // 向左攻击的图像序列
	vector <IMAGE> ims_skill3left;//向左技能的图像序列
	vector <IMAGE> ims_skill3right;//向右技能的图像序列
	vector <IMAGE> ims_skill2left;//向左技能的图像序列
	vector <IMAGE> ims_skill2right;//向右技能的图像序列

	int animId;  // 用于循环动画播放的id
	PlayerStatus playerStatus; // 当前的状态
	float x_left, y_bottom; // 左侧坐标与下部坐标
	
	float v; // 速度
	float width, height; // 图片的宽度、高度
	bool injured;//是否被攻击
	int health;//生命值
	int magic;//法力值
	float x_right;
	float y_top;
	int huiming = 1;
	bool isskill3 = false;
	int energy = 0;//反弹可以获得能量
	void draw()// 显示相关信息	
	{
		putimagePng(x_left, y_bottom - height, &im_show);  // 游戏中显示角色
	}

	void initialize() // 初始化
	{
		ims_runleft.clear(); // 先清空掉vector
		ims_runright.clear();
		ims_skill3left.clear();
		ims_skill3right.clear();
		ims_skill2left.clear();
		ims_skill2right.clear();
		loadimage(&im_standright, _T("Dusk_standright.png")); // 导入向右站立图片
		loadimage(&im_standleft, _T("Dusk_standleft.png")); // 导入向左站立图片
		loadimage(&littleZZ, _T("Dusk/小自在.png"));
		health = 100;
		magic = 50;
		injured = false;
		playerStatus = standright; // 初始为向右站立的游戏状态
		im_show = im_standright;  // 初始显示向右站立的图片
		width = im_standright.getwidth(); // 获得图像的宽、高，所有动画图片大小一样
		height = im_standright.getheight();

		TCHAR filename[80];
		for (int i = 0; i <= 7; i++) // 把向右奔跑的八张图片对象添加到ims_runright中
		{
			swprintf_s(filename, _T("Dusk/move_right/move_right%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_runright.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // 把向左奔跑的八张图片对象添加到ims_runleft中
		{
			swprintf_s(filename, _T("Dusk/move_left/move_left%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_runleft.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // 把向左攻击的12张图片对象添加到ims_atkleft中
		{
			swprintf_s(filename, _T("Dusk/ottack_left/otk_left%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_atkleft.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // 把向右攻击的12张图片对象添加到ims_atkright中
		{
			swprintf_s(filename, _T("Dusk/ottack_right/otk_right%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_atkright.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // 把向右攻击的12张图片对象添加到skill3_right中
		{
			swprintf_s(filename, _T("Dusk/skill2_right/skill2_right%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_skill3right.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // 把向右攻击的12张图片对象添加到skill3_left中
		{
			swprintf_s(filename, _T("Dusk/skill2_left/skill2_left%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_skill3left.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // 把向右攻击的12张图片对象添加到skill3_right中
		{
			swprintf_s(filename, _T("Dusk/skill3_right/skill3_right%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_skill2right.push_back(im);
		}
		for (int i = 0; i <= 7; i++) // 把向右攻击的12张图片对象添加到skill3_left中
		{
			swprintf_s(filename, _T("Dusk/skill3_left/skill3_left%d.png"), i);
			IMAGE im;
			loadimage(&im, filename);
			ims_skill2left.push_back(im);
		}
		animId = 0; // 动画id开始设为0
		v = 10;//初始移动速度为5
		updateXY(WIDTH / 2, HEIGHT / 2); // 开始将角色放在画面中间

	}

	void updateXY(float mx, float my) // 根据输入，更新玩家坐标
	{
		x_left = mx;
		y_bottom = my;
		
	}

	void runRight() // 游戏角色向右奔跑
	{
		x_left += v; // 横坐标增加，向右移动


		if (playerStatus != runright) // 如果之前角色状态不是向右奔跑
		{
			playerStatus = runright; // 切换为向右奔跑状态
			animId = 0; // 动画播放id初始化为0
		}
		else // 表示之前就是向右奔跑状态了
		{
			animId++; // 动画图片开始切换
			if (animId >= ims_runright.size()) // 循环切换
				animId = 0;
		}
		im_show = ims_runright[animId];	 // 设置要显示的对应图片	 

	}

	void runLeft() // 游戏角色向左奔跑
	{
		x_left -= v; // 横坐标减少，向左移动		

		if (playerStatus != runleft) // 如果之前角色状态不是向左奔跑
		{
			playerStatus = runleft; // 切换为向左奔跑状态
			animId = 0; // 动画播放id初始化为0
		}
		else // 之前就是向左奔跑状态了
		{
			animId++; // 动画图片开始切换
			if (animId >= ims_runleft.size()) // 循环切换
				animId = 0;
		}
		im_show = ims_runleft[animId];	 // 设置要显示的对应图片	

	}
	void runUp() // 游戏角色向上奔跑
	{
		y_bottom -= v; // 纵坐标减少，向上移动		

		if (playerStatus != runup) // 如果之前角色状态不是向上奔跑
		{
			playerStatus = runup; // 切换为向左奔跑状态
			animId = 0; // 动画播放id初始化为0
		}
		else // 之前就是向上奔跑状态了
		{
			animId++; // 动画图片开始切换
			if (animId >= ims_runleft.size()) // 循环切换
				animId = 0;
		}
		im_show = ims_runright[animId];	 // 设置要显示的对应图片，向上跑用向右代替	

	}
	void runDown() // 游戏角色向下奔跑
	{
		y_bottom += v; // 纵坐标增加，向下移动		

		if (playerStatus != rundown) // 如果之前角色状态不是向下奔跑
		{
			playerStatus = rundown; // 切换为向下奔跑状态
			animId = 0; // 动画播放id初始化为0
		}
		else // 之前就是向下奔跑状态了
		{
			animId++; // 动画图片开始切换
			if (animId >= ims_runleft.size()) // 循环切换
				animId = 0;
		}
		im_show = ims_runleft[animId];	 // 设置要显示的对应图片。向下跑用向左代替	

	}
int animspeed = 0;
	void atkLeft() // 游戏角色向左攻击
	{
		
			if (playerStatus != atkleft) // 如果之前角色状态不是向左攻击
					{
						playerStatus = atkleft; // 切换为向左攻击状态
						animId = 0; // 动画播放id初始化为0

					}
					else // 之前就是向左攻击状态了
					{
						animspeed++;
						if(animspeed%2==0)animId++; // 动画图片开始切换
			
						if (animId >= ims_atkleft.size()) {
							animId = 0;
					
						} // 循环切换
							
					}
		
					im_show = ims_atkleft[animId];	 // 设置要显示的对应图片
		
					if (animspeed % 9 == 0)	magic-=5;
					if (magic <= 0)magic = 0;
	}
	void skill3Left() // 游戏角色向左攻击
	{

		if (playerStatus != atkleft) // 如果之前角色状态不是向左攻击
		{
			playerStatus = atkleft; // 切换为向左攻击状态
			animId = 0; // 动画播放id初始化为0

		}
		else // 之前就是向左攻击状态了
		{
			animspeed++;
			if (animspeed % 2 == 0)animId++; // 动画图片开始切换

			if (animId >= ims_skill3left.size()) {
				animId = 0;

			} // 循环切换

		}

		im_show = ims_skill3left[animId];	 // 设置要显示的对应图片

		//if (animspeed % 9 == 0)	magic -= 5;
		if (magic <= 0)magic = 0;
	}
	void skill2Left() // 游戏角色向左攻击
	{

		if (playerStatus != atkleft) // 如果之前角色状态不是向左攻击
		{
			playerStatus = atkleft; // 切换为向左攻击状态
			animId = 0; // 动画播放id初始化为0

		}
		else // 之前就是向左攻击状态了
		{
			animspeed++;
			if (animspeed % 2 == 0)animId++; // 动画图片开始切换

			if (animId >= ims_skill2left.size()) {
				animId = 0;

			} // 循环切换

		}

		im_show = ims_skill2left[animId];	 // 设置要显示的对应图片

		if (animspeed % 9 == 0)	magic -= 10;
		if (magic <= 0)magic = 0;
	}
	void atkRight() // 游戏角色向右攻击
	{
		
			if (playerStatus != atkright) // 如果之前角色状态不是向右攻击
			{
				playerStatus = atkright; // 切换为向右攻击状态
				animId = 0; // 动画播放id初始化为0
			}
			else // 之前就是向右攻击状态了
			{
				if (animspeed % 2 == 0)animId++; // 动画图片开始切换
				animspeed++;
				if (animId >= ims_atkright.size()) // 循环切换
					animId = 0;
			}
			im_show = ims_atkright[animId];	 // 设置要显示的对应图片	
		
			if (animspeed % 9 == 0)	magic-=5;
			if (magic <= 0)magic = 0;
	}
	void skill3Right() // 游戏角色向右攻击
	{

		if (playerStatus != atkright) // 如果之前角色状态不是向右攻击
		{
			playerStatus = atkright; // 切换为向右攻击状态
			animId = 0; // 动画播放id初始化为0
		}
		else // 之前就是向右攻击状态了
		{
			if (animspeed % 2 == 0)animId++; // 动画图片开始切换
			animspeed++;
			if (animId >= ims_skill3right.size()) // 循环切换
				animId = 0;
		}
		im_show = ims_skill3right[animId];	 // 设置要显示的对应图片	

		//if (animspeed % 9 == 0)	magic -= 5;
		if (magic <= 0)magic = 0;
	}
	void skill2Right() // 游戏角色向右攻击
	{

		if (playerStatus != atkright) // 如果之前角色状态不是向右攻击
		{
			playerStatus = atkright; // 切换为向右攻击状态
			animId = 0; // 动画播放id初始化为0
		}
		else // 之前就是向右攻击状态了
		{
			if (animspeed % 2 == 0)animId++; // 动画图片开始切换
			animspeed++;
			if (animId >= ims_skill2right.size()) // 循环切换
				animId = 0;
		}
		im_show = ims_skill2right[animId];	 // 设置要显示的对应图片	

		if (animspeed % 9 == 0)	magic -= 10;
		if (magic <= 0)magic = 0;
	}
	void standStill() // 游戏角色默认为向左或向右静止站立
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
		float y_top_enemy = enemy.y - enemy.enemy_height; // 同样注意y轴方向
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
		float y_top_enemy = enemy.y - enemy.enemy_height; // 同样注意y轴方向
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
		float y_top_enemy = enemy.y - enemy.enemy_height; // 同样注意y轴方向
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
		float y_top_enemy = enemy.y - enemy.enemy_height; // 同样注意y轴方向
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
		
		// 获取子弹和玩家的半径）
		float bulletRadius = bullet.im_bullet.getwidth() / 2.0f - 5; // 如果图像宽度等于直径
		float playerRadius = this->width / 2.0f - 50; // 假设 width 是直径

		// 计算圆心之间的距离
		float dx = bullet.x + 0 - (this->x_left + playerRadius + 20); // 玩家圆心的 x 坐标是 x_left + 半径
		float dy = bullet.y + 10 - (this->y_bottom + playerRadius - 120); // 玩家圆心的 y 坐标是 y_bottom + 半径
		float distanceSquared = dx * dx + dy * dy;
		//setlinecolor(BLACK);
		//circle(this->x_left + playerRadius + 20, this->y_bottom + playerRadius - 120, playerRadius);
		//circle(bullet.x + 50, bullet.y + 10, bulletRadius);
		// 检查两个圆是否相交
		float radiiSum = bulletRadius + playerRadius;
		if ((distanceSquared <= radiiSum * radiiSum) && playerStatus != atkleft && playerStatus != atkright) {
			// 如果发生碰撞，减少玩家的生命值并标记子弹为不存在
			this->health -= 10;
			bullet.exisit = false;
		}
		if ((distanceSquared <= radiiSum * radiiSum) && (playerStatus == atkleft || playerStatus == atkright) && magic > 0) {
			// 成功反弹则标记为反弹
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