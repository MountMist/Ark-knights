#pragma once
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include"player.h"
#include <vector>
using namespace std;
//class Player;
class Bullet {
public:
    IMAGE im_bullet; // 子弹图像
    float x, y;      // 子弹位置
    float vx;    // 子弹速度
    float startx;
    bool exisit;
    bool reverse = false;
    void initialize(int px,int py,int pVx) {
        loadimage(&im_bullet, _T("Enemy/lightening.png"));
        x = px; y = py; vx = pVx;
        startx = px;
    }

    void updateleft() {
        x += vx;

    }
    void updateright() {
        x -= vx;

    }
    void renew(int a, int b,int c) {
        x = a;
        y = b;
        vx = c;
    }
    void draw() {
        putimagePng(x, y, &im_bullet);
    }
    void check() {
        if (x <= 0)x = startx;
    }
    void update(float targetX, float targetY) {
        float dx = targetX - x;
        float dy = targetY - y;
        float distance = sqrt(dx * dx + dy * dy);

        // 归一化方向并设置速度
        float dvx = (dx / distance) * vx;
        float dvy = (dy / distance) * vx;

        // 更新位置
        x += dvx;
        y += dvy;
    }
  void updateRe() {
       x += vx;
        if (x > 650)exisit = false;
   }
};