#include <math.h>
#include <time.h>
#include "header/Angel.h"
#include "Characters/mainrole.h"
#include "Characters/MainRole_Ring.h"
#include "Background/Cloud.h"
#include "Characters/Alien.h"
#include "Weapon/Bullet_Main.h"


#define SPACE_KEY 32

//螢幕大小define
#define SCREENWIDTH 360
#define SCREENHEIGHT 640
#define SCREENWIDTH_HALF (SCREENWIDTH/2.0)
#define SCREENHEIGHT_HALF (SCREENHEIGHT/2.0)

//BOSS 子彈發射座標
 int boss_Mode1BulletCount = 0;
float boss_BulletCoordinate[3][2] = {

	0.75f , -0.6f,
   -0.75f , -0.6f,
    0.0f  , -0.2f

};



//玩家總分
int PlayerTotalPoint = 0;
bool isBossOut = false; //第二Alien狀態


// 必須在 glewInit(); 執行完後,在執行物件實體的取得
MainRole *mainrole;	// 宣告 指標物件，結束時記得釋放
MainRole_Ring *mainrole_ring;	// 宣告 指標物件，結束時記得釋放
Cloud* cloud[6];
Bullet_Main* bullet_main;
short small_alien = 3; //螢幕上small alien 出現的最大數量
short middle_alien = 1; //螢幕上middle alien 出現的最大數量
short BOSS_alien = 0; //螢幕上BOSS alien 出現的最大數量
short SAlien_space = 4;  // SAlien 空間個數
short MAlien_space = 2;  // MAlien 空間個數
short BAlien_space = 1;  // BOSS 空間個數

const short all_alien = 7; /* small_alien + middle_alien + BOSS_alien*/

Alien* alien[all_alien];

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;


// 函式的原型宣告
void IdleProcess();
void CreateGameObject();
void CheckBullet();

//子彈宣告
typedef struct Bullet_Node_struct {
	Bullet_Main *bullet_main;
	struct Bullet_Node_struct*link;

} Bullet_NODE , *Bullet_PNODE ;



//主角子彈設定
const short Bullet_space_NUM = 40; //畫面最多產生的子彈數量


Bullet_PNODE pHead_MainBullet_free = NULL;
Bullet_PNODE pTail_MainBullet_free = NULL;
Bullet_PNODE pGet_MainBullet_free;
Bullet_PNODE pHead_MainBullet_used = NULL;
Bullet_PNODE pTail_MainBullet_used = NULL;
Bullet_PNODE pGet_MainBullet_used;
Bullet_PNODE pGet_Draw_bullet;
Bullet_PNODE pGet_Move_bullet;
Bullet_PNODE pGet_Last_Draw_bullet = NULL;
Bullet_PNODE pGet_Check_bullet = NULL;
GLuint ShaderHandle_Bullet; //取得 Shader 的序號

int Bullet_Total_MainBullet_used = 0;
int Bullet_Total_MainBullet_free = 0;



//Small Alien 子彈型別宣告
typedef struct Bullet_Node_struct_SAlien {
	Bullet_SAlien* bullet_main;
	Bullet_MAlien* bullet_MAlien;
	// 用於判斷現在為SAlien or MAlien
	bool isSAlien_bullet = false;
	bool isMAlien_bullet = false;
	bool isBAlien_bullet = false;
	struct Bullet_Node_struct_SAlien* link;

} Bullet_NODE_SAlien, * Bullet_PNODE_SAlien;



//Small Alien 子彈設定
const short SAlienBullet_NUM = 30;//畫面最多產生的Small Alien彈數量
const short MAlienBullet_NUM = 30;//畫面最多產生的Small Alien彈數量
Bullet_PNODE_SAlien pHead_AlienBullet_free = NULL;
Bullet_PNODE_SAlien pTail_AlienBullet_free = NULL;
Bullet_PNODE_SAlien pGet_AlienBullet_free = NULL;
Bullet_PNODE_SAlien pHead_AlienBullet_used = NULL;
Bullet_PNODE_SAlien pTail_AlienBullet_used = NULL;
Bullet_PNODE_SAlien pGet_AlienBullet_used = NULL;
Bullet_PNODE_SAlien pGet_Draw_AlienBullet;
Bullet_PNODE_SAlien pGet_Check_AlienBullet;
Bullet_PNODE_SAlien pGet_Last_Draw_AlienBullet_used = NULL;
int Bullet_Total_Alien_used = 0;
int Bullet_Total_Alien_free = 0;




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

	GLuint ShaderHandle;

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

	
	for (int i = 0; i < all_alien; i++)
	{
		if(i < SAlien_space){ //設定small alien 空間
		
			if (i == 0) { //只須設定第一個Shader
				alien[i] = new Small_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection);
				ShaderHandle = alien[i]->GetShaderHandle();
			}

			else //沿用前面的Shader
			{
				alien[i] = new Small_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);

			}

		}

		else if( i < SAlien_space + MAlien_space)//設定middle alien
		{
			
			if (i == SAlien_space) //middle alien起始空間
			{
				alien[i] = new Middle_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection);
				ShaderHandle = alien[i]->GetShaderHandle();

			
				

			}

			else //沿用前面的Shader
			{
				alien[i] = new Middle_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);
			

			}

			

		}


		else if (i < SAlien_space + MAlien_space + BAlien_space)//設定BOSS alien
		{

				alien[i] = new BOSS_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection);
				alien[i]->_y = 1.5f; 
				alien[i]->SetTRSMatrix(Translate(alien[i]->_x, alien[i]->_y,0.0f));

		}


		

	}


	//存放子彈的儲存空間
	for (int i = 0; i < Bullet_space_NUM; i++)
	{
		if (i == 0) {

			if ((pHead_MainBullet_free = (Bullet_PNODE)malloc(sizeof(Bullet_NODE))) ==NULL) {
			
				printf("記憶體空間不足");
				exit(0);
			
			};

			pHead_MainBullet_free->bullet_main = new Bullet_Main;
			pHead_MainBullet_free->bullet_main->SetShader(g_mxModelView, g_mxProjection);
			ShaderHandle = pHead_MainBullet_free->bullet_main->GetShaderHandle();
			pHead_MainBullet_free->link = NULL;
			pTail_MainBullet_free = pHead_MainBullet_free;



		}


		else
		{
			if ((pGet_MainBullet_free = (Bullet_PNODE)malloc(sizeof(Bullet_NODE))) == NULL) {
				printf("記憶體空間不足");
				exit(0);
			}

			pGet_MainBullet_free->bullet_main = new Bullet_Main;
			pGet_MainBullet_free->bullet_main->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);
			pGet_MainBullet_free->link = NULL;
			pTail_MainBullet_free->link = pGet_MainBullet_free;
			pTail_MainBullet_free = pGet_MainBullet_free;
		}

		Bullet_Total_MainBullet_free++;

	
	}

	

	//Small + Middle Alien 存放子彈的空間
	for (int i = 0; i < SAlienBullet_NUM + MAlienBullet_NUM; i++)
	{
		if (i == 0) {

			if ((pHead_AlienBullet_free = (Bullet_PNODE_SAlien)malloc(sizeof(Bullet_NODE_SAlien))) == NULL) {

				printf("記憶體空間不足\n");
				exit(0);

			}

			pHead_AlienBullet_free->bullet_main = new Bullet_SAlien;
			pHead_AlienBullet_free->bullet_main->SetShader(g_mxModelView, g_mxProjection);

			pHead_AlienBullet_free->bullet_MAlien = new Bullet_MAlien;
			pHead_AlienBullet_free->bullet_MAlien->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);

			ShaderHandle = pHead_AlienBullet_free->bullet_main->GetShaderHandle();
			pHead_AlienBullet_free->link = NULL;
			pTail_AlienBullet_free = pHead_AlienBullet_free;
			

		}

		else if(i < SAlienBullet_NUM) //設定small alien bullet
		{
			if ((pGet_AlienBullet_free = (Bullet_PNODE_SAlien)malloc(sizeof(Bullet_NODE_SAlien))) == NULL) {

				printf("記憶體空間不足\n");
				exit(0);

			}

			pGet_AlienBullet_free->bullet_main = new Bullet_SAlien;
			pGet_AlienBullet_free->bullet_main->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);


			pGet_AlienBullet_free->bullet_MAlien = new Bullet_MAlien;
			pGet_AlienBullet_free->bullet_MAlien->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);

			pGet_AlienBullet_free->link = NULL;
			pTail_AlienBullet_free->link = pGet_AlienBullet_free;
			pTail_AlienBullet_free = pGet_AlienBullet_free;
			
		}


		else if (i < SAlienBullet_NUM + MAlienBullet_NUM) //設定middle alien bullet
		{
			if ((pGet_AlienBullet_free = (Bullet_PNODE_SAlien)malloc(sizeof(Bullet_NODE_SAlien))) == NULL) {

				printf("記憶體空間不足\n");
				exit(0);

			}



			pGet_AlienBullet_free->bullet_main = new Bullet_SAlien;
			pGet_AlienBullet_free->bullet_main->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);

			pGet_AlienBullet_free->bullet_MAlien = new Bullet_MAlien;
			pGet_AlienBullet_free->bullet_MAlien->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);

			pGet_AlienBullet_free->link = NULL;
			pTail_AlienBullet_free->link = pGet_AlienBullet_free;
			pTail_AlienBullet_free = pGet_AlienBullet_free;

		}

		Bullet_Total_Alien_free++; //可用子彈數增加一


	}
	
}


void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	
	
	for (int i = 0; i < 6; i++)
	{
		cloud[i]->Draw();
	}



	
	pGet_Draw_bullet = pHead_MainBullet_used;
	for (int i = 0; i < Bullet_Total_MainBullet_used; i++)
	{
		pGet_Draw_bullet->bullet_main->Draw();
		pGet_Draw_bullet = pGet_Draw_bullet->link;

	}



	//Draw Small Alien Bullet
	pGet_Draw_AlienBullet = pHead_AlienBullet_used;
	for (int i = 0; i < Bullet_Total_Alien_used; i++)
	{
		if (pGet_Draw_AlienBullet->isSAlien_bullet)
		{
			pGet_Draw_AlienBullet->bullet_main->Draw();
		}

		else if (pGet_Draw_AlienBullet->isMAlien_bullet)
		{
			pGet_Draw_AlienBullet->bullet_MAlien->Draw();
		}
		
		pGet_Draw_AlienBullet = pGet_Draw_AlienBullet->link;
	}


	//Draw Small Alien 
	if (small_alien > 0) {
		alien[0]->Draw();
	}
	
	for (int i = 1; i < small_alien ; i++)
		{
			if(alien[i]->alife){
				alien[i]->DrawW();
			}
		
		}



	//Draw Middle Alien 
	if(middle_alien > 0){  //若有中怪存在

		alien[SAlien_space]->Draw();

	}

	for (int i = SAlien_space + 1; i < SAlien_space + middle_alien; i++)
	{
		if (alien[i]->alife) {
			alien[i]->DrawW();
		}

	}


	for (int i = SAlien_space + MAlien_space; i < SAlien_space + MAlien_space + BOSS_alien; i++)
	{
		if (alien[i]->alife) {
			alien[i]->Draw();
		}

	}

	

	
	
	
	
	mainrole->Draw();
	mainrole_ring->Draw();

	glutSwapBuffers();	// 交換 Frame Buffer
}




void CreateBullet_Main() { 

	if (Bullet_Total_MainBullet_used == 0) {

		pHead_MainBullet_used = pHead_MainBullet_free; 
		pHead_MainBullet_free = pHead_MainBullet_free->link;

		pHead_MainBullet_used->bullet_main->_x = mainrole->_x;
		pHead_MainBullet_used->bullet_main->_y = mainrole->_y;

		pHead_MainBullet_used->bullet_main->SetTRSMatrix(Translate(pHead_MainBullet_used->bullet_main->_x, pHead_MainBullet_used->bullet_main->_y,0.0));

		pHead_MainBullet_used->link = NULL;
		pTail_MainBullet_used = pHead_MainBullet_used;

		Bullet_Total_MainBullet_free--;
		Bullet_Total_MainBullet_used++;


	}


	else if (Bullet_Total_MainBullet_used > 0) {

		pGet_MainBullet_used = pHead_MainBullet_free;
		pHead_MainBullet_free = pHead_MainBullet_free->link;

		pGet_MainBullet_used->bullet_main->_x = mainrole->_x;
		pGet_MainBullet_used->bullet_main->_y = mainrole->_y;

		pGet_MainBullet_used->bullet_main->SetTRSMatrix(Translate(pGet_MainBullet_used->bullet_main->_x, pGet_MainBullet_used->bullet_main->_y, 0.0));

		pTail_MainBullet_used->link = pGet_MainBullet_used; //結尾link指向新取得的頭
		pGet_MainBullet_used->link = NULL;//設定結尾為NULL
		pTail_MainBullet_used = pGet_MainBullet_used;//設定尾巴為PGet

		Bullet_Total_MainBullet_free--;
		Bullet_Total_MainBullet_used++;


	}
	
	
}


void CreateBullet_Alien(Alien *alien , char what_alien ) {

	
	switch (what_alien)
	{
	case 'B': //若為BOSS Alien 發射的子彈
		if (Bullet_Total_Alien_used == 0) { //第一個被使用的子彈

			pHead_AlienBullet_used = pHead_AlienBullet_free;  //從頭拿資源
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //將 free 的頭改成下一個節點


			pHead_AlienBullet_used->bullet_main->_x = alien->_x + boss_BulletCoordinate[boss_Mode1BulletCount][0];
			pHead_AlienBullet_used->bullet_main->_y = alien->_y + boss_BulletCoordinate[boss_Mode1BulletCount][1];
			pHead_AlienBullet_used->isSAlien_bullet = true; //設定子彈為B
			pHead_AlienBullet_used->isMAlien_bullet = false; //設定子彈為B
			pHead_AlienBullet_used->isBAlien_bullet = true; //設定子彈為B



			pHead_AlienBullet_used->bullet_main->SetTRSMatrix( Translate(pHead_AlienBullet_used->bullet_main->_x, pHead_AlienBullet_used->bullet_main->_y, 0.0) );


			pHead_AlienBullet_used->link = NULL; //設定結尾為NULL
			pTail_AlienBullet_used = pHead_AlienBullet_used; //設定尾巴為PHead


			Bullet_Total_Alien_used++; //已用空間數量加一
			Bullet_Total_Alien_free--;//未用空間數量減一



		}


		else if ((Bullet_Total_Alien_used < SAlienBullet_NUM + MAlienBullet_NUM))
		{
			pGet_AlienBullet_used = pHead_AlienBullet_free; //從頭拿資源
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //將 free 的頭改成下一個節點

			pGet_AlienBullet_used->bullet_main->_x = alien->_x + boss_BulletCoordinate[boss_Mode1BulletCount][0];
			pGet_AlienBullet_used->bullet_main->_y = alien->_y + boss_BulletCoordinate[boss_Mode1BulletCount][1];
			pGet_AlienBullet_used->isSAlien_bullet = true; //設定子彈為B
			pGet_AlienBullet_used->isMAlien_bullet = false; //設定子彈為B
			pGet_AlienBullet_used->isBAlien_bullet = true; //設定子彈為B



			pGet_AlienBullet_used->bullet_main->SetTRSMatrix( Translate(pGet_AlienBullet_used->bullet_main->_x, pGet_AlienBullet_used->bullet_main->_y, 0.0));

			pTail_AlienBullet_used->link = pGet_AlienBullet_used; //結尾link指向新取得的頭
			pGet_AlienBullet_used->link = NULL;//設定結尾為NULL
			pTail_AlienBullet_used = pGet_AlienBullet_used;//設定尾巴為PGet

			Bullet_Total_Alien_used++; //已用空間數量加一
			Bullet_Total_Alien_free--;//未用空間數量減一

		}


		break;
	case 'S'://若為Small Alien 發射的子彈

		if (Bullet_Total_Alien_used == 0) { //第一個被使用的子彈

			pHead_AlienBullet_used = pHead_AlienBullet_free;  //從頭拿資源
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //將 free 的頭改成下一個節點


			pHead_AlienBullet_used->bullet_main->_x = alien->_x;
			pHead_AlienBullet_used->bullet_main->_y = alien->_y;
			pHead_AlienBullet_used->isSAlien_bullet = true; //設定子彈為S
			pHead_AlienBullet_used->isMAlien_bullet = false; //設定子彈為S
			pHead_AlienBullet_used->isBAlien_bullet = false; //設定子彈為B
			


			pHead_AlienBullet_used->bullet_main->SetTRSMatrix(Translate(pHead_AlienBullet_used->bullet_main->_x, pHead_AlienBullet_used->bullet_main->_y, 0.0));


			pHead_AlienBullet_used->link = NULL; //設定結尾為NULL
			pTail_AlienBullet_used = pHead_AlienBullet_used; //設定尾巴為PHead


			Bullet_Total_Alien_used++; //已用空間數量加一
			Bullet_Total_Alien_free--;//未用空間數量減一



		}


		else if ((Bullet_Total_Alien_used < SAlienBullet_NUM + MAlienBullet_NUM))
		{
			pGet_AlienBullet_used = pHead_AlienBullet_free; //從頭拿資源
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //將 free 的頭改成下一個節點

			pGet_AlienBullet_used->bullet_main->_x = alien->_x;
			pGet_AlienBullet_used->bullet_main->_y = alien->_y;
			pGet_AlienBullet_used->isSAlien_bullet = true; //設定子彈為S
			pGet_AlienBullet_used->isMAlien_bullet = false; //設定子彈為S
			pGet_AlienBullet_used->isBAlien_bullet = false; //設定子彈為B

			

			pGet_AlienBullet_used->bullet_main->SetTRSMatrix(Translate(pGet_AlienBullet_used->bullet_main->_x, pGet_AlienBullet_used->bullet_main->_y, 0.0));

			pTail_AlienBullet_used->link = pGet_AlienBullet_used; //結尾link指向新取得的頭
			pGet_AlienBullet_used->link = NULL;//設定結尾為NULL
			pTail_AlienBullet_used = pGet_AlienBullet_used;//設定尾巴為PGet

			Bullet_Total_Alien_used++; //已用空間數量加一
			Bullet_Total_Alien_free--;//未用空間數量減一

		}



		break;

	case 'M': //若為Middle Alien 發射的子彈


		if (Bullet_Total_Alien_used == 0) { //第一個被使用的子彈

			pHead_AlienBullet_used = pHead_AlienBullet_free;  //從頭拿資源
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //將 free 的頭改成下一個節點

			pHead_AlienBullet_used->bullet_MAlien->_x = alien->_x;
			pHead_AlienBullet_used->bullet_MAlien->_y = alien->_y;
			pHead_AlienBullet_used->bullet_MAlien->MainRoleDis_x = alien->dis_x;
			pHead_AlienBullet_used->bullet_MAlien->MainRoleDis_y = alien->dis_y;
			


			pHead_AlienBullet_used->isSAlien_bullet = false; //設定子彈為M
			pHead_AlienBullet_used->isMAlien_bullet = true; //設定子彈為M
			pHead_AlienBullet_used->isBAlien_bullet = false; //設定子彈為B
			

			pHead_AlienBullet_used->bullet_MAlien->SetTRSMatrix(Translate(pHead_AlienBullet_used->bullet_MAlien->_x, pHead_AlienBullet_used->bullet_MAlien->_y, 0.0));


			pHead_AlienBullet_used->link = NULL; //設定結尾為NULL
			pTail_AlienBullet_used = pHead_AlienBullet_used; //設定尾巴為PHead


			Bullet_Total_Alien_used++; //已用空間數量加一
			Bullet_Total_Alien_free--;//未用空間數量減一



		}


		else if ((Bullet_Total_Alien_used < SAlienBullet_NUM + MAlienBullet_NUM))
		{
			pGet_AlienBullet_used = pHead_AlienBullet_free; //從頭拿資源
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //將 free 的頭改成下一個節點

			pGet_AlienBullet_used->bullet_MAlien->_x = alien->_x;
			pGet_AlienBullet_used->bullet_MAlien->_y = alien->_y;
			pGet_AlienBullet_used->bullet_MAlien->MainRoleDis_x = alien->dis_x;
			pGet_AlienBullet_used->bullet_MAlien->MainRoleDis_y = alien->dis_y;
		

			pGet_AlienBullet_used->isSAlien_bullet = false; //設定子彈為M
			pGet_AlienBullet_used->isMAlien_bullet = true; //設定子彈為M
			pGet_AlienBullet_used->isBAlien_bullet = false; //設定子彈為B

			
			pGet_AlienBullet_used->bullet_MAlien->SetTRSMatrix(Translate(pGet_AlienBullet_used->bullet_MAlien->_x, pGet_AlienBullet_used->bullet_MAlien->_y, 0.0));

			pTail_AlienBullet_used->link = pGet_AlienBullet_used; //結尾link指向新取得的頭
			pGet_AlienBullet_used->link = NULL;//設定結尾為NULL
			pTail_AlienBullet_used = pGet_AlienBullet_used;//設定尾巴為PGet

			Bullet_Total_Alien_used++; //已用空間數量加一
			Bullet_Total_Alien_free--;//未用空間數量減一

		}




		break;
	default:
		break;
	}




}

//----------------------------------------------------------------------------



//檢查子彈是否超過有效範圍, 若超過則連結好前後節點，並delete
void CheckBullet() {
	

	//printf("%d\n" , Bullet_Total_MainBullet_used);
	pGet_Check_bullet = pHead_MainBullet_used;

	for (int i = 0; i < Bullet_Total_MainBullet_used; i++)
	{

		
		
		if (pGet_Check_bullet->bullet_main->_y > 1.8 || pGet_Check_bullet->bullet_main->HurtAlien ) { //超過有效距離或有中彈   //有問題
			
			//若刪除的是第一個節點則更換 pHead的位置
			if (pGet_Check_bullet == pHead_MainBullet_used) {
				
				pTail_MainBullet_free->link = pGet_Check_bullet; //將位置與free的尾巴相連
				pTail_MainBullet_free = pGet_Check_bullet; //free 的尾巴為新增的節點
				pHead_MainBullet_used = pHead_MainBullet_used->link; //將used的頭指向下個節點
				pTail_MainBullet_free->bullet_main->HurtAlien = false; //reset子彈狀態
				pTail_MainBullet_free->link = NULL; //free 尾巴link為NULL
				
			}

			//若刪除的是最後一個節點則更換 pTail的位置
			else if (pGet_Check_bullet == pTail_MainBullet_used) {


				pTail_MainBullet_free->link = pGet_Check_bullet;
				pTail_MainBullet_free = pGet_Check_bullet;
				pGet_Last_Draw_bullet->link = NULL;
				pTail_MainBullet_used = pGet_Last_Draw_bullet; //設定used的新尾巴
				pTail_MainBullet_free->bullet_main->HurtAlien = false; //reset子彈狀態
				pTail_MainBullet_free->link = NULL;

			}

			//若不為頭也不為尾的節點則連接好頭尾位置
			else {
			
				
				pTail_MainBullet_free->link = pGet_Check_bullet;
				pTail_MainBullet_free = pGet_Check_bullet;
				pGet_Last_Draw_bullet->link = pGet_Check_bullet->link;
				pTail_MainBullet_free->bullet_main->HurtAlien = false; //reset子彈狀態
				pTail_MainBullet_free->link = NULL;
			}
			
			
			Bullet_Total_MainBullet_used--;
			Bullet_Total_MainBullet_free++;

			break; //若有刪除節點則跳出迴圈因為節點要重新計算
		
		}

		pGet_Last_Draw_bullet = pGet_Check_bullet; //獲取前一次的pGet 以便必要時收回空間
		pGet_Check_bullet = pGet_Check_bullet->link;


	}

	
}


//檢查Small Alien 子彈是否超過有效區
void CheckBullet_Alien(){


	


	pGet_Check_AlienBullet = pHead_AlienBullet_used;

	for (int i = 0; i <Bullet_Total_Alien_used; i++)
	{
		if(pGet_Check_AlienBullet->isSAlien_bullet){
		
			if (!(pGet_Check_AlienBullet->bullet_main->_y > -2.0) || pGet_Check_AlienBullet->bullet_main->HurtMainRole ) {

				if (pGet_Check_AlienBullet == pHead_AlienBullet_used) { //如果刪除的是第一個節點

					pTail_AlienBullet_free->link = pGet_Check_AlienBullet; //將位置與free的尾巴相連
					pTail_AlienBullet_free = pGet_Check_AlienBullet; //free 的尾巴為新增的節點
					pHead_AlienBullet_used = pHead_AlienBullet_used->link; //將used的頭指向下個節點
					pTail_AlienBullet_free->bullet_main->HurtMainRole = false; //reset子彈狀態
					pTail_AlienBullet_free->link = NULL; //free 尾巴link為NULL

				}

				else if (pGet_Check_AlienBullet == pTail_AlienBullet_used) { //如果刪除的是尾巴的部分

					pTail_AlienBullet_free->link = pGet_Check_AlienBullet;
					pTail_AlienBullet_free = pGet_Check_AlienBullet;
					pGet_Last_Draw_AlienBullet_used->link = NULL;
					pTail_AlienBullet_used = pGet_Last_Draw_AlienBullet_used; //設定used的新尾巴
					pTail_AlienBullet_free->bullet_main->HurtMainRole = false; //reset子彈狀態
					pTail_AlienBullet_free->link = NULL;
				}

				else { //刪除中間的部分//你在寫這裡
					pTail_AlienBullet_free->link = pGet_Check_AlienBullet;
					pTail_AlienBullet_free = pGet_Check_AlienBullet;
					pGet_Last_Draw_AlienBullet_used->link = pGet_Check_AlienBullet->link;
					pTail_AlienBullet_free->bullet_main->HurtMainRole = false; //reset子彈狀態
					pTail_AlienBullet_free->link = NULL;

				}

				Bullet_Total_Alien_used--; //已用空間數量減一
				Bullet_Total_Alien_free++;//未用空間數量加一
				break;

			}
		
		}
	
		else if (pGet_Check_AlienBullet->isMAlien_bullet) {

			if (!(pGet_Check_AlienBullet->bullet_MAlien->_x > -2.5f && pGet_Check_AlienBullet->bullet_MAlien->_x < 2.5f && pGet_Check_AlienBullet->bullet_MAlien->_y > -2.5f && pGet_Check_AlienBullet->bullet_MAlien->_y < 2.5f )|| pGet_Check_AlienBullet->bullet_MAlien->HurtMainRole) {

				if (pGet_Check_AlienBullet == pHead_AlienBullet_used) { //如果刪除的是第一個節點

					pTail_AlienBullet_free->link = pGet_Check_AlienBullet; //將位置與free的尾巴相連
					pTail_AlienBullet_free = pGet_Check_AlienBullet; //free 的尾巴為新增的節點
					pHead_AlienBullet_used = pHead_AlienBullet_used->link; //將used的頭指向下個節點
					pTail_AlienBullet_free->bullet_MAlien->HurtMainRole = false; //reset子彈狀態
					pTail_AlienBullet_free->link = NULL; //free 尾巴link為NULL

				}

				else if (pGet_Check_AlienBullet == pTail_AlienBullet_used) { //如果刪除的是尾巴的部分

					pTail_AlienBullet_free->link = pGet_Check_AlienBullet;
					pTail_AlienBullet_free = pGet_Check_AlienBullet;
					pGet_Last_Draw_AlienBullet_used->link = NULL;
					pTail_AlienBullet_used = pGet_Last_Draw_AlienBullet_used; //設定used的新尾巴
					pTail_AlienBullet_free->bullet_MAlien->HurtMainRole = false; //reset子彈狀態
					pTail_AlienBullet_free->link = NULL;
				}

				else { //刪除中間的部分//你在寫這裡
					pTail_AlienBullet_free->link = pGet_Check_AlienBullet;
					pTail_AlienBullet_free = pGet_Check_AlienBullet;
					pGet_Last_Draw_AlienBullet_used->link = pGet_Check_AlienBullet->link;
					pTail_AlienBullet_free->bullet_MAlien->HurtMainRole = false; //reset子彈狀態
					pTail_AlienBullet_free->link = NULL;

				}

				Bullet_Total_Alien_used--; //已用空間數量減一
				Bullet_Total_Alien_free++;//未用空間數量加一
				break;

			}

		}


		pGet_Last_Draw_AlienBullet_used = pGet_Check_AlienBullet;//獲取前一次的pGet 以便必要時收回空間
		pGet_Check_AlienBullet = pGet_Check_AlienBullet->link;

	}


}




float timer_onFrameMove = 0; //rotation's timer
float timer_canHurtMainRole = 0; //rotation's timer


void onFrameMove(float delta)
{
	timer_onFrameMove += delta;
	timer_canHurtMainRole += delta;

	if (timer_onFrameMove > 1.0 / 1500.0) { //每1/1000秒更新一次
		
	
		
		mainrole_ring->AutomaticRotation( mainrole->mxTran_Main );//星環自動選轉 傳入父層

		//更新雲朵位置
		for (int i = 0; i < 6; i++)
		{
			cloud[i]->AutoTranslate_Background();
		}

		
		//更新子彈路線 
		pGet_Move_bullet = pHead_MainBullet_used;
		for (int i = 0; i < Bullet_Total_MainBullet_used; i++)
		{
			pGet_Move_bullet->bullet_main->AutoTranslate_Bullet();

			//檢查是否有Alien被子彈打到
			for (int i = 0; i < SAlien_space + middle_alien ; i++)
			{
				
				alien[i]->AutoCheckHurtDie(pGet_Move_bullet->bullet_main->_x, pGet_Move_bullet->bullet_main->_y , pGet_Move_bullet->bullet_main->MAX_X, pGet_Move_bullet->bullet_main->MAX_Y, &pGet_Move_bullet->bullet_main->HurtAlien );
				
			}

			pGet_Move_bullet = pGet_Move_bullet->link;
		}

		//檢查是否有子彈超過有效區
		CheckBullet();

		//更新SAlien 位置
		for (int i = 0; i < small_alien; i++)
		{
			//若alien 死亡則玩家家一分
			if (alien[i]->alife == false) { //alien死亡
				PlayerTotalPoint++; //玩家一分
			}

			alien[i]->AutomaticMotion();
		}

		
		//更新small alien 子彈位置
		pGet_AlienBullet_used = pHead_AlienBullet_used;
		for (int i = 0; i < Bullet_Total_Alien_used; i++)
		{
			if (pGet_AlienBullet_used->isSAlien_bullet == true && pGet_AlienBullet_used->isMAlien_bullet == false) //為SAlien bullet
			{
				pGet_AlienBullet_used->bullet_main->AutoTranslate_Bullet();
				mainrole->AutoCheckHurt_MainRole(pGet_AlienBullet_used->bullet_main->_x, pGet_AlienBullet_used->bullet_main->_y, pGet_AlienBullet_used->bullet_main->MAX_X, pGet_AlienBullet_used->bullet_main->MAX_Y, &pGet_AlienBullet_used->bullet_main->HurtMainRole, &mainrole_ring->_defenceBallNUM);//偵測 main role是否被子彈打中			

				//被傷害後無敵狀態計算時間
				if (pGet_AlienBullet_used->bullet_main->HurtMainRole) {
					timer_canHurtMainRole = 0.0f;
					mainrole->SetAlpha(0.6); //無敵狀態為半透明
					mainrole_ring->SetAlpha(0.6); //無敵狀態為半透明
				}
			}
			else if (pGet_AlienBullet_used->isSAlien_bullet == false && pGet_AlienBullet_used->isMAlien_bullet == true) //為MAlien bullet
			{
				pGet_AlienBullet_used->bullet_MAlien->AutoTranslate_Bullet(); //要改
				mainrole->AutoCheckHurt_MainRole(pGet_AlienBullet_used->bullet_MAlien->_x, pGet_AlienBullet_used->bullet_MAlien->_y, pGet_AlienBullet_used->bullet_MAlien->MAX_X, pGet_AlienBullet_used->bullet_MAlien->MAX_Y, &pGet_AlienBullet_used->bullet_MAlien->HurtMainRole, &mainrole_ring->_defenceBallNUM);//偵測 main role是否被子彈打中			

				//被傷害後無敵狀態計算時間
				if (pGet_AlienBullet_used->bullet_MAlien->HurtMainRole) {
					timer_canHurtMainRole = 0.0f;
					mainrole->SetAlpha(0.6); //無敵狀態為半透明
					mainrole_ring->SetAlpha(0.6); //無敵狀態為半透明
				}
			}
			

			

			pGet_AlienBullet_used = pGet_AlienBullet_used->link;

		}
		//檢查Small Alien 子彈是否超過有效區
		CheckBullet_Alien();
		
		
		//更新middle Alien 位置
		for (int i = SAlien_space; i < SAlien_space + middle_alien; i++)
		{

			//若alien 死亡則玩家家一分
			if (alien[i]->alife == false) { //alien死亡
				PlayerTotalPoint++; //玩家一分
			}

			alien[i]->AutomaticMotion(mainrole->_x , mainrole->_y);
			
		}


		timer_onFrameMove = 0;
	}


	//更新保護機制
	if (timer_canHurtMainRole >4.0 && mainrole->can_change_hurtMain ==false) { //維持四秒無敵狀態
		
		mainrole->can_change_hurtMain = true; //可重新攻擊
		mainrole->SetAlpha(1.0);
		mainrole_ring->SetAlpha(1.0); 

	}
	


	//若總分到達十分則放出中怪
	if (PlayerTotalPoint == 3)
	{
		middle_alien = 1; //螢幕上middle alien 出現的最大數量
		
	}

	//若總分到達十分則放出BOSS
	//else if (PlayerTotalPoint == 5)
	//{
	//	isBossOut = true; //開啟第二個模式 test


	//}

	
	
	GL_Display();
	
}





float timer_bullet = 0.0; //時間計時器
float BulletLaunchSecStart = 0.0; //紀錄子彈發射的時間 
bool canLaunchBullet = true; //是否允許發射子彈
bool clickLaunchBullet = false; //是否按下發射

bool mouse_down= GLUT_UP;
void onBulletLaunch(float delta) {

	
	timer_bullet += delta;
	if (clickLaunchBullet && canLaunchBullet && Bullet_Total_MainBullet_free > 0) {
		
		
		CreateBullet_Main();
		canLaunchBullet = false;
		
		BulletLaunchSecStart = timer_bullet;
		 
	}

	if (timer_bullet - BulletLaunchSecStart > 0.2f ) { //每隔0.6秒可發射一發子彈
		
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


float timer_AlienBulletLaunch = 0.0f;

//Alien發射子彈
void onAlienBulletLaunch(float delta) {
	timer_AlienBulletLaunch += delta;

	if (timer_AlienBulletLaunch >= 1.0f && Bullet_Total_Alien_free >0) { //每隔一秒發射一顆子彈
	
		
		
		for (int i = 0; i < SAlien_space + middle_alien; i++) //每個小怪都建置一個子彈
		{
			if(i <  small_alien){ //SAlien 創造子彈
				if (alien[i]->_y > -2.5 && alien[i]->_y < 2.5) {
					CreateBullet_Alien(alien[i] , 'S');
				}
			}

			else if(i < SAlien_space + middle_alien){ //MAlien 創造子彈
				if (alien[i]->_y > -2.5 && alien[i]->_y < 2.5) {
				
					CreateBullet_Alien(alien[i], 'M');
				
				
				}
				
			}
			
		}

		//BOSS三重子彈
		for (boss_Mode1BulletCount = 0; boss_Mode1BulletCount < 3 && BOSS_alien > 0; boss_Mode1BulletCount++) //Boss存在則發射子彈
		{
			CreateBullet_Alien(alien[SAlien_space + MAlien_space] , 'B');
		}
		





		timer_AlienBulletLaunch = 0.0f;
	
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
		mainrole_ring->_defenceBallNUM = 0;
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

	case 033:
		
		for (int i = 0; i < Bullet_Total_Alien_free; i++)
		{
			pGet_Draw_AlienBullet = pHead_AlienBullet_free->link;
			free(pHead_AlienBullet_free);
			pHead_AlienBullet_free = pGet_Draw_AlienBullet;
		}


		for (int i = 0; i < Bullet_Total_Alien_used; i++)
		{
			pGet_Draw_AlienBullet = pHead_AlienBullet_used->link;
			free(pHead_AlienBullet_used);
			pHead_AlienBullet_used = pGet_Draw_AlienBullet;
		}


		for (int i = 0; i < Bullet_Total_MainBullet_free; i++)
		{
			pGet_Draw_bullet = pHead_MainBullet_free->link;
			free(pHead_MainBullet_free);
			pHead_MainBullet_free = pGet_Draw_bullet;
		}


		for (int i = 0; i < Bullet_Total_MainBullet_used; i++)
		{
			pGet_Draw_bullet = pHead_MainBullet_used->link;
			free(pHead_MainBullet_used);
			pHead_MainBullet_used = pGet_Draw_bullet;
		}

		exit(EXIT_SUCCESS);

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
	
	//允許透明度設定
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
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
