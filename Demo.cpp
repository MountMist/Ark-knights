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

// һЩȫ�ֱ���
Player player;  // ������ҿ��Ƶ���Ϸ��ɫ����
Scene scene;  // ���峡��ȫ�ֶ���
Scene2 scene2;
Timer timer;  // ���ھ�ȷ��ʱ
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
void startup()  // ��ʼ��
{
	srand(time(0)); // ��ʼ�����������
	player.initialize(); // ��ҽ�ɫ��ʼ��
	initgraph(WIDTH, HEIGHT); // �¿�һ������
	
	ep1.initialize(player);
	ep2.initialize(player);
	ep3.initialize(player);
	loadimage(&poster, _T("Guide/poster.png"));
	loadimage(&guide1, _T("Guide/guide1.png"));
	loadimage(&guide2, _T("Guide/guide2.png"));
	loadimage(&guide3, _T("Guide/guide3.png"));
	loadimage(&WIN, _T("victory.png"));
	
	mciSendString(_T("open JBL.mp3 alias bkmusic"), NULL, 0, NULL);//��������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
	//�����볡CG
	while (1) {		
		 putimage(0, 0, &poster);
		if (_kbhit()) {
			if (GetAsyncKeyState(' '))break;
		}
	}
	BeginBatchDraw(); // ��ʼ��������
	
}



int main() // ������
{
	
	startup();  	// ��ʼ��

	
	
	while (1)       // ���һ��
	{
		if (text1) {
			ep1.fade_in();
			ep1.fade_out();
			text1 = false;
		}
		
		if (!start1) {
			//cleardevice();
			
			putimage(0, 0, &guide1);//��һ�عؿ�����
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
			ep1.show();  // ��ʾ
			ep1.updateWithoutInput(); // �������޹صĸ���
			ep1.updateWithInput();    // �������йصĸ���
			if (ep1.win1 == true && ep1.player.x_left > 900 && ep1.player.y_bottom > 500)break;//�����ʤ�����봫�����������һ��
		}
		
		
		
	}
	
		//(_T("close bkmusic"), NULL, 0, NULL);//ֹͣ����
		//mciSendString(_T("open ZFC.mp3 alias bkmusic"), NULL, 0, NULL);//��������
		//mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
		while (1) {	//��ڶ���

			if (text2) {
				ep2.fade_in();
				ep2.fade_out();
				text2 = false;
			}

			if (!start2) {
				putimage(0, 0, &guide2);//�ڶ��عؿ�����
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
				ep2.updateWithInput();    // �������йصĸ���
				if (ep2.win2 == true && ep2.player.x_left > 900 && ep2.player.y_bottom > 500)break;//�����ʤ�����봫�����������һ��
			}
			
		}
	
		//mciSendString(_T("close bkmusic"), NULL, 0, NULL);//ֹͣ����
		//mciSendString(_T("open DFB.mp3 alias bkmusic"), NULL, 0, NULL);//��������
		//mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
		while (1) {		//�������

			if (text3) {
				ep3.fade_in();
				ep3.fade_out();
				text3 = false;
			}

			if (!start3) {
				putimage(0, 0, &guide3);//�����عؿ�����
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
				ep3.updateWithInput();    // �������йصĸ���
				if (ep3.win3 == true && ep3.player.x_left > 900 && ep3.player.y_bottom > 500)break;//�����ʤ�����봫�����������һ��
			}
				
		}
		while (1) {
			//MessageBox(NULL, TEXT("Ϧͻ�������ҵ��������������鼫��"), TEXT("��Ϸʤ��"), MB_OK);
			putimagePng(0, 0, &WIN);
			if (_kbhit()) {
				if (GetAsyncKeyState(' '))break;
			}
		}
			return 0;
}
	