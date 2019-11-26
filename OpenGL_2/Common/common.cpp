#include <iostream>
#include <cmath>
#include <ctime>
#include "Timer.h"
#include <string.h>
#include <gl\glut.h>

#define ORTHO_WIDTH 0

char g_strFPS[9] = "FPS:0000";
//IdleProcess
int g_ifps;
int g_icount = 0;
double g_ckStart = -1;
double g_felapse;
double g_fprev;
Timer g_Timer;

//CallBackDelta 
int callback_ifps;
int callback_icount = 0;
double callback_ckStart = -1;
double callback_felapse;
double callback_fprev;
Timer callback_Timer;


extern float superCube_timer;
extern bool super_twoGunFlag;
extern bool superCubeFlag;

extern void onFrameMove(float delta);
extern void onBulletLaunch(float delta);
extern void onAlienBulletLaunch(float delta);
void DisplayFSP(int ifps);
void DrawText(float x, float y, char *string);



void IdleProcess()
{
	float delta;
	double ckNow; 
	g_icount++;
	if( g_ckStart == -1 ) {
		g_fprev = g_ckStart = g_Timer.getElapsedTimeInMilliSec(); //clock(); //開始計時
		onFrameMove(0);
	}
	else {
		ckNow = g_Timer.getElapsedTimeInMilliSec();
		//計時一秒計時器
		/*g_felapse = (ckNow - g_ckStart);
		if( g_felapse >= 1000.0 ) {
			g_ifps = g_icount;
			g_icount = 0;
			g_ckStart += g_felapse;
		}*/
		delta = (float)((ckNow - g_fprev)/1000); // 計算間隔的時間
		g_fprev = ckNow; // 記錄這次的時間，當成前一次的時間
		onFrameMove(delta);
		onBulletLaunch(delta);
		onAlienBulletLaunch(delta);
		if (superCubeFlag || super_twoGunFlag) {
			superCube_timer += delta;
		}
		
				
	}
	glutPostRedisplay(); // 呼叫 Rendering 更新螢幕
}




//--------------------------------------------------------------------------------
// 以下沒有用到，無須理會
void DrawText(float x, float y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);  // GLUT_BITMAP_TIMES_ROMAN_24
	}
}

void DisplayFSP(int ifps)
{
	int i;
	
	glColor3f(1.0, 1.0, 1.0);
	i = ifps/1000;
	g_strFPS[4] = i+48;
	ifps = ifps - i*1000;
	i = ifps/100;
	g_strFPS[5] = i+48;
	ifps = ifps - i*100;
	g_strFPS[6] = ifps/10+48;
	g_strFPS[7] = ifps%10+48;
	glColor3f(0.5, 0.8, 0.5);
	DrawText(0, ORTHO_WIDTH, g_strFPS);	// 在指定的位置處，顯示指定的字串內容
}

//--------------------------------------------------------------------------------