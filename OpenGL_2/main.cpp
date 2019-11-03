#include <math.h>
#include <time.h>
#include "header/Angel.h"
#include "Characters/mainrole.h"
#include "Characters/MainRole_Ring.h"
#include "Background/Cloud.h"
#include "Weapon/Bullet_Main.h"

#define SPACE_KEY 32

//螢幕大小define
#define SCREENWIDTH 360
#define SCREENHEIGHT 640
#define SCREENWIDTH_HALF (SCREENWIDTH/2.0)
#define SCREENHEIGHT_HALF (SCREENHEIGHT/2.0)



// 必須在 glewInit(); 執行完後,在執行物件實體的取得
MainRole *mainrole;	// 宣告 指標物件，結束時記得釋放
MainRole_Ring *mainrole_ring;	// 宣告 指標物件，結束時記得釋放
Cloud* cloud[6];
Bullet_Main* bullet_main;


// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;


// 函式的原型宣告
void IdleProcess();
void CreateGameObject();



//雲朵位置、大小陣列
float cloud_info[6][3] = {

	1.0f , 1.3f , 8.5f/10.0f,
	1.5f , 0.1f , 7.0f/10.0f,
	0.95f , -0.8f , 6.5f / 10.0f,
	-1.45f , 1.9f , 8.0f / 10.0f,
	-2.1f , 0.6f , 10.0f / 10.0f,
	-1.2f , -1.45f , 10.1f / 10.0f

};



void init( void )
{
	
	srand((unsigned)time(NULL));//設定亂數種子

    g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

	CreateGameObject();	//取得物件


    glClearColor( 0.9882, 0.6718, 0.6445, 1.0 ); // black background
}


//取得物件
void CreateGameObject() {

	mainrole = new MainRole;
	mainrole->SetShader(g_mxModelView, g_mxProjection);

	mainrole_ring = new MainRole_Ring;
	mainrole_ring->SetShader(g_mxModelView, g_mxProjection);

	
	
	for (int i = 0; i < 6; i++)
	{
		cloud[i] = new Cloud;
		cloud[i]->SetShader(g_mxModelView, g_mxProjection);
		cloud[i]->_x = cloud_info[i][0];
		cloud[i]->_y = cloud_info[i][1];
		cloud[i]->_scale = cloud_info[i][2];
		cloud[i]->SetXYScale(cloud[i]->_x, cloud[i]->_y, cloud[i]->_scale);

	}
	
	

	
}




void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	for (int i = 0; i < 6; i++)
	{
		cloud[i]->Draw();
	}

	mainrole->Draw();
	mainrole_ring->Draw();

	glutSwapBuffers();	// 交換 Frame Buffer
}


void CreateBullet_Main() { //你在寫這裡!!!!!

	bullet_main = new Bullet_Main;
	bullet_main->SetShader(g_mxModelView, g_mxProjection);
	bullet_main->Draw();

}

//----------------------------------------------------------------------------


float timer_autoRotate = 0; //rotation's timer

void onFrameMove(float delta)
{
	timer_autoRotate += delta;
	if (timer_autoRotate > 1.0 / 1000.0) { //每1/1000更新一次
		
		
		mainrole_ring->AutomaticRotation( mainrole->mxTran_Main );//星環自動選轉 傳入父層

		for (int i = 0; i < 6; i++)
		{
			cloud[i]->AutoTranslate_Background();
		}
		
		timer_autoRotate = 0;
	}
	
	GL_Display();
	
}


int bullet_count = 0; //發射子彈數
float timer_bullet = 0.0; //時間計時器
float BulletLaunchSecStart = 0.0; //紀錄子彈發射的時間 
bool canLaunchBullet = true; //是否允許發射子彈
bool clickLaunchBullet = false; //是否按下發射

bool mouse_down= GLUT_UP;
void onBulletLaunch(float delta) {
	
	//printf("目前發射了: %d\n 發子彈", bullet_count);

	timer_bullet += delta;
	if (clickLaunchBullet && canLaunchBullet) {
		
		//bullet_count++;
		CreateBullet_Main();
		canLaunchBullet = false;
		
		BulletLaunchSecStart = timer_bullet;
		 
	}

	if (timer_bullet - BulletLaunchSecStart > 0.6f ) { //每隔0.6秒可發射一發子彈
		
		canLaunchBullet = true;
		if(mouse_down == GLUT_UP){ 
			clickLaunchBullet = false; //從此處開始再次確認是否有點擊滑鼠

		}
		else if (mouse_down == GLUT_DOWN) { //長按
			clickLaunchBullet = true; //若為長按則連續發射
		}
		
		timer_bullet = BulletLaunchSecStart = 0.0f;
	}

}


//----------------------------------------------------------------------------
void reset()
{ 
	
	mainrole->SetTRSMatrix(g_mxModelView);
	glutPostRedisplay();
}
//----------------------------------------------------------------------------


float mouse_displacement = 2.0f; //滑鼠位移量

void win_PassiveMotion(int x , int y) { //用滑鼠操控船艦

	//計算位移量

	mainrole->_x = mouse_displacement * (x - SCREENWIDTH_HALF) / (SCREENWIDTH_HALF) ;
	mainrole->_y = -mouse_displacement * (y - SCREENHEIGHT_HALF) / (SCREENHEIGHT_HALF);
	
	//set main role matrix
	mainrole->mxTran_Main = Translate(mainrole->_x, mainrole->_y,0);
	mainrole->SetTRSMatrix(mainrole->mxTran_Main);

	//set ring matrix
	mainrole_ring->maTran_Ring = Translate(mainrole_ring->_x, mainrole_ring->_y , 0); //取得圓環的X、Y資訊 
	mainrole_ring->SetTRSMatrix(mainrole->mxTran_Main * mainrole_ring->maTran_Ring * mainrole_ring->mxAutoRotate_Ring ); //設定圓環的父子關係
	
}


void win_mousemotion( int x ,int y) {
	//計算位移量

	mainrole->_x = mouse_displacement * (x - SCREENWIDTH_HALF) / (SCREENWIDTH_HALF);
	mainrole->_y = -mouse_displacement * (y - SCREENHEIGHT_HALF) / (SCREENHEIGHT_HALF);

	//set main role matrix
	mainrole->mxTran_Main = Translate(mainrole->_x, mainrole->_y, 0);
	mainrole->SetTRSMatrix(mainrole->mxTran_Main);

	//set ring matrix
	mainrole_ring->maTran_Ring = Translate(mainrole_ring->_x, mainrole_ring->_y, 0); //取得圓環的X、Y資訊 
	mainrole_ring->SetTRSMatrix(mainrole->mxTran_Main * mainrole_ring->maTran_Ring * mainrole_ring->mxAutoRotate_Ring); //設定圓環的父子關係


}


//test _defenceBallNUM
void win_keyFunc(unsigned char key ,int x, int y) { 

	switch (key)
	{
	case 'a':
		mainrole_ring->_defenceBallNUM=0;
		break;
	case 'b':
		mainrole_ring->_defenceBallNUM = 1;
		break;
	case 'c':
		mainrole_ring->_defenceBallNUM = 2;
		break;
	case 'd':
		mainrole_ring->_defenceBallNUM = 3;
		break;

	}

}


//launch bullet
void win_mouse(int button , int state , int x , int y ) {

	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			

			if (state == GLUT_DOWN) {
				mouse_down = GLUT_DOWN;
				clickLaunchBullet = true;
			}
			else
				mouse_down = GLUT_UP;

				
			break;

		default:

			break;
	}
	

}





//----------------------------------------------------------------------------
void GL_Reshape(GLsizei w, GLsizei h)
{
	

	/*if (w/h > 0) {
		glViewport(0, 0, h, h);
	
	}

	else if (w/ h < 0) {
		glViewport(0, 0, w, w);
	
	}
	else if (w / h == 1) {*/
		glViewport(0, 0, w, h);
	//}
}

//----------------------------------------------------------------------------

float timer_test;

int main( int argc, char **argv )
{
    
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT );

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "Draw two triangles" );

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE; 
    glewInit();  

    init();

	
	glutKeyboardFunc(win_keyFunc);//test _defenceBallNUM
	
	glutMotionFunc(win_mousemotion);//滑鼠在按下按鍵時一樣操控船艦
	glutPassiveMotionFunc(win_PassiveMotion); //用滑鼠操控船艦

	glutMouseFunc(win_mouse); //發射子彈
	

	glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	

    glutMainLoop();
    return 0;
}
