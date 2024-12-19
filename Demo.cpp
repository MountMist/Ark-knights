#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include"player.h"
#include"episode1.h"
#include"episode2.h"
#include"episode3.h"
#pragma comment(lib,"Winmm.lib")
using namespace std;

#define  WIDTH 1000  
#define  HEIGHT 600

// 一些全局变量
Player player;  // 定义玩家控制的游戏角色对象
Scene scene;  // 定义场景全局对象
Scene2 scene2;
Timer timer;  // 用于精确延时
EP1 ep1;
EP2 ep2;
EP3 ep3;
IMAGE poster;
IMAGE guide1;
IMAGE guide2;
IMAGE guide3;
IMAGE WIN;
int  magicrelieve = 0;
bool win1 = false;
bool win2 = false;
bool start1 = false;
bool start2 = false;
bool start3 = false;
bool text1 = true;
bool text2 = true;
bool text3 = true;
float brightcount = 0;
void startup()  // 初始化
{
	srand(time(0)); // 初始化随机数种子
	player.initialize(); // 玩家角色初始化
	initgraph(WIDTH, HEIGHT); // 新开一个画面
	
	ep1.initialize(player);
	ep2.initialize(player);
	ep3.initialize(player);
	loadimage(&poster, _T("Guide/poster.png"));
	loadimage(&guide1, _T("Guide/guide1.png"));
	loadimage(&guide2, _T("Guide/guide2.png"));
	loadimage(&guide3, _T("Guide/guide3.png"));
	loadimage(&WIN, _T("victory.png"));
	
	mciSendString(_T("open JBL.mp3 alias bkmusic"), NULL, 0, NULL);//播放音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环播放
	//播放入场CG
	while (1) {		
		 putimage(0, 0, &poster);
		if (_kbhit()) {
			if (GetAsyncKeyState(' '))break;
		}
	}
	BeginBatchDraw(); // 开始批量绘制
	
}



int main() // 主函数
{
	
	startup();  	// 初始化

	
	
	while (1)       // 玩第一关
	{
		if (text1) {
			ep1.fade_in();
			ep1.fade_out();
			text1 = false;
		}
		
		if (!start1) {
			//cleardevice();
			
			putimage(0, 0, &guide1);//第一关关卡介绍
			FlushBatchDraw();
			//printf("AAA");
			if (_kbhit()) {
				if (GetAsyncKeyState('F')) { 
					start1 = true;
					//break;
				}
			}
		}
		else {
			ep1.show();  // 显示
			ep1.updateWithoutInput(); // 与输入无关的更新
			ep1.updateWithInput();    // 与输入有关的更新
			if (ep1.win1 == true && ep1.player.x_left > 900 && ep1.player.y_bottom > 500)break;//如果获胜且走入传送门则进入下一关
		}
		
		
		
	}
	
		//(_T("close bkmusic"), NULL, 0, NULL);//停止播放
		//mciSendString(_T("open ZFC.mp3 alias bkmusic"), NULL, 0, NULL);//播放音乐
		//mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环播放
		while (1) {	//玩第二关

			if (text2) {
				ep2.fade_in();
				ep2.fade_out();
				text2 = false;
			}

			if (!start2) {
				putimage(0, 0, &guide2);//第二关关卡介绍
				FlushBatchDraw();
				//printf("AAA");
				if (_kbhit()) {
					if (GetAsyncKeyState('F')) {
						start2 = true;
						//break;
					}
				}
			}
			
			else {
				ep2.show2();
				ep2.updateWithoutInput2();
				ep2.updateWithInput();    // 与输入有关的更新
				if (ep2.win2 == true && ep2.player.x_left > 900 && ep2.player.y_bottom > 500)break;//如果获胜且走入传送门则进入下一关
			}
			
		}
	
		//mciSendString(_T("close bkmusic"), NULL, 0, NULL);//停止播放
		//mciSendString(_T("open DFB.mp3 alias bkmusic"), NULL, 0, NULL);//播放音乐
		//mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环播放
		while (1) {		//玩第三关

			if (text3) {
				ep3.fade_in();
				ep3.fade_out();
				text3 = false;
			}

			if (!start3) {
				putimage(0, 0, &guide3);//第三关关卡介绍
				FlushBatchDraw();
				//printf("AAA");
				if (_kbhit()) {
					if (GetAsyncKeyState('F')) {
						start3 = true;
						//break;
					}
				}
			}
			else {
				ep3.show3();
				ep3.updateWithoutInput3();
				ep3.updateWithInput();    // 与输入有关的更新
				if (ep3.win3 == true && ep3.player.x_left > 900 && ep3.player.y_bottom > 500)break;//如果获胜且走入传送门则进入下一关
			}
				
		}
		while (1) {
			//MessageBox(NULL, TEXT("夕突破了自我的桎梏，画境更臻极致"), TEXT("游戏胜利"), MB_OK);
			putimagePng(0, 0, &WIN);
			if (_kbhit()) {
				if (GetAsyncKeyState(' '))break;
			}
		}
			return 0;
}
	