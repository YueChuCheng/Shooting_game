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
void CheckBullet();

//子彈宣告
int Bullet_Total = 0;
typedef struct Bullet_Node_struct {
	Bullet_Main *bullet_main;
	struct Bullet_Node_struct*link;

} Bullet_NODE , *Bullet_PNODE ;

Bullet_PNODE pHead_bullet = NULL;
Bullet_PNODE pTail_bullet = NULL;
Bullet_PNODE pGet_bullet;
Bullet_PNODE pGet_Draw_bullet;
Bullet_PNODE pGet_Last_Draw_bullet = NULL;
Bullet_PNODE pGet_Check_bullet = NULL;


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

	pGet_Draw_bullet = pHead_bullet;
	
		for (int i = 0; i < Bullet_Total; i++)
		{
			pGet_Draw_bullet->bullet_main->Draw();
			pGet_Draw_bullet = pGet_Draw_bullet->link;


		}
	


	mainrole->Draw();
	mainrole_ring->Draw();

	glutSwapBuffers();	// 交換 Frame Buffer
}




void CreateBullet_Main() { 

	if( Bullet_Total == 0){ //若第一顆子彈
		
		if ((pHead_bullet = (Bullet_PNODE)malloc(sizeof(Bullet_NODE))) == NULL) { //成功取得空間
			printf("記憶體空間不足\n");
			exit(0);
		
		}
		

		//設定Bullet 內容

		pHead_bullet->bullet_main = new Bullet_Main;
		pHead_bullet->bullet_main->SetShader(g_mxModelView, g_mxProjection);
		
		//複製mainrole 的資訊
		pHead_bullet->bullet_main ->_x = mainrole->_x;
		pHead_bullet->bullet_main->_y = mainrole->_y;
		
		pHead_bullet->bullet_main->BulletTrans = Translate(pHead_bullet->bullet_main->_x, pHead_bullet->bullet_main->_y, 0.0);

		pHead_bullet->bullet_main->SetTRSMatrix(pHead_bullet->bullet_main->BulletTrans);

		pHead_bullet->link = NULL;
		pTail_bullet = pHead_bullet;

		Bullet_Total++;

	}

	else if (Bullet_Total>0) { //若不為第一顆子彈

		if ((pGet_bullet = (Bullet_PNODE)malloc(sizeof(Bullet_NODE))) == NULL) { //成功取得空間
			printf("記憶體空間不足\n");
			exit(0);

		}

	
		//設定Bullet內容

		pGet_bullet->bullet_main = new Bullet_Main;
		pGet_bullet->bullet_main->SetShader(g_mxModelView, g_mxProjection);

		//複製mainrole 的資訊
		pGet_bullet->bullet_main->_x = mainrole->_x;
		pGet_bullet->bullet_main->_y = mainrole->_y;


		pGet_bullet->bullet_main->BulletTrans = Translate(pGet_bullet->bullet_main->_x, pGet_bullet->bullet_main->_y, 0.0);

		pGet_bullet->bullet_main->SetTRSMatrix(pGet_bullet->bullet_main->BulletTrans);
		pGet_bullet->link = NULL;

		pGet_bullet->bullet_main->Draw();


		pTail_bullet->link = pGet_bullet; //將前一個節點與新的節點連接
		pTail_bullet = pGet_bullet; //設定尾巴節點為新拿的空間
		
		Bullet_Total++;
	}

	

}

//----------------------------------------------------------------------------

float bullet_main_y;
Bullet_PNODE one, two, three;

//檢查子彈是否超過有效範圍, 若超過則連結好前後節點，並delete
void CheckBullet() {
	
	pGet_Check_bullet = pHead_bullet;

	

	for (int i = 0; i < Bullet_Total; i++)
	{

		bullet_main_y = pGet_Check_bullet->bullet_main->_y;

		if (bullet_main_y > 2.0) {
			
			//若刪除的是第一個節點則更換 pHead的位置
			if (pGet_Check_bullet == pHead_bullet) {
				pHead_bullet = pHead_bullet->link;
				
			}

			//若刪除的是最後一個節點則更換 pTail的位置
			else if (pGet_Check_bullet == pTail_bullet) {

				pTail_bullet = pGet_Last_Draw_bullet;
				pTail_bullet->link = NULL;

			}

			//若不為頭也不為尾的節點則連接好頭尾位置
			else {
			
				pGet_Last_Draw_bullet->link = pGet_Check_bullet->link; //前一次的link，連接到下一個節點的起頭
			}
			
			

			
			
			free(pGet_Check_bullet); //刪除節點
			
			Bullet_Total--;

			break; //若有刪除節點則跳出迴圈因為節點要重新計算
		
		}

		pGet_Last_Draw_bullet = pGet_Check_bullet; //獲取前一次的pGet 以便必要時收回空間
		pGet_Check_bullet = pGet_Check_bullet->link;


	}

	/*while (pGet_Check_bullet!=NULL)
	{

		bullet_main_y = pGet_Check_bullet->bullet_main->_y;

		if (bullet_main_y > 2.0) {

			//若刪除的是第一個節點則更換 pHead的位置
			if (pHead_bullet == pGet_Check_bullet) {
				pHead_bullet = pHead_bullet->link;

			}

			//若刪除的是最後一個節點則更換 pTail的位置
			else if (pTail_bullet == pGet_Check_bullet) {

				pTail_bullet = pGet_Last_Draw_bullet;
				pTail_bullet->link = NULL;

			}



			pGet_Last_Draw_bullet->link = pGet_Check_bullet->link; //前一次的link，連接到下一個節點的起頭



			free(pGet_Check_bullet); //刪除節點

			Bullet_Total--;

			break; //若有刪除節點則跳出迴圈因為節點要重新計算

		}

		pGet_Last_Draw_bullet = pGet_Check_bullet; //獲取前一次的pGet 以便必要時收回空間
		pGet_Check_bullet = pGet_Check_bullet->link;


	}
	*/


	
}


//float test_i = 0; //測試是否有確實回收記憶體

float timer_onFrameMove = 0; //rotation's timer

void onFrameMove(float delta)
{

	

	timer_onFrameMove += delta;
	if (timer_onFrameMove > 1.0 / 1000.0) { //每1/1000更新一次
		
		//test 是否有回收記憶體
		/*if (pHead_bullet == NULL) {
			printf("%f\n", test_i);
			test_i++;
		}*/
		
		mainrole_ring->AutomaticRotation( mainrole->mxTran_Main );//星環自動選轉 傳入父層

		for (int i = 0; i < 6; i++)
		{
			cloud[i]->AutoTranslate_Background();
		}

		
		//更新子彈路線 
		pGet_Draw_bullet = pHead_bullet;
		for (int i = 0; i < Bullet_Total; i++)
		{
			pGet_Draw_bullet->bullet_main->AutoTranslate_Bullet();
			pGet_Draw_bullet = pGet_Draw_bullet->link;


		}

		//檢查是否有子彈超過有效區
		CheckBullet();
		
		timer_onFrameMove = 0;
	}
	
	GL_Display();
	
}


float timer_bullet = 0.0; //時間計時器
float BulletLaunchSecStart = 0.0; //紀錄子彈發射的時間 
bool canLaunchBullet = true; //是否允許發射子彈
bool clickLaunchBullet = false; //是否按下發射

bool mouse_down= GLUT_UP;
void onBulletLaunch(float delta) {

	timer_bullet += delta;
	if (clickLaunchBullet && canLaunchBullet) {
		
		CreateBullet_Main();
		canLaunchBullet = false;
		
		BulletLaunchSecStart = timer_bullet;
		 
	}

	if (timer_bullet - BulletLaunchSecStart > 0.1f ) { //每隔0.6秒可發射一發子彈
		
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
	mainrole_ring->mxTran_Ring = Translate(mainrole_ring->_x, mainrole_ring->_y , 0); //取得圓環的X、Y資訊 
	mainrole_ring->SetTRSMatrix(mainrole->mxTran_Main * mainrole_ring->mxTran_Ring * mainrole_ring->mxAutoRotate_Ring ); //設定圓環的父子關係
	
}


void win_mousemotion( int x ,int y) {
	//計算位移量

	mainrole->_x = mouse_displacement * (x - SCREENWIDTH_HALF) / (SCREENWIDTH_HALF);
	mainrole->_y = -mouse_displacement * (y - SCREENHEIGHT_HALF) / (SCREENHEIGHT_HALF);

	//set main role matrix
	mainrole->mxTran_Main = Translate(mainrole->_x, mainrole->_y, 0);
	mainrole->SetTRSMatrix(mainrole->mxTran_Main);

	//set ring matrix
	mainrole_ring->mxTran_Ring = Translate(mainrole_ring->_x, mainrole_ring->_y, 0); //取得圓環的X、Y資訊 
	mainrole_ring->SetTRSMatrix(mainrole->mxTran_Main * mainrole_ring->mxTran_Ring * mainrole_ring->mxAutoRotate_Ring); //設定圓環的父子關係


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
