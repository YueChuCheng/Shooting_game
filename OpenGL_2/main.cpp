#include <math.h>
#include <time.h>
#include "header/Angel.h"
#include "Characters/mainrole.h"
#include "Characters/MainRole_Ring.h"
#include "Background/Cloud.h"
#include "Characters/Alien.h"
#include "Weapon/Bullet_Main.h"
#include"Deco/Explo.h"
#include"Bonus/SuperCub.h"

#define SPACE_KEY 32

//螢幕大小define
#define SCREENWIDTH 360
#define SCREENHEIGHT 640
#define SCREENWIDTH_HALF (SCREENWIDTH/2.0)
#define SCREENHEIGHT_HALF (SCREENHEIGHT/2.0)

//Bonus
SuperCube* superCube;
bool touch_superCube = false;

SuperCube* superCube_twoGun;
bool touch_twoGunStar = false;

//Deco
Explo* explo_alien[5];

//BOSS 子彈發射座標
enum Mode
{
	None =0, One , Two,Three
};
 int boss_Mode1BulletNUM = 0;
 int boss_Mode3BulletNUM = 0;
 short BOSSMode = One;
float boss_BulletCoordinate[3][2] = {

	0.75f , -0.3f,
   -0.75f , -0.3f,
    0.0f  , -0.1f

};
const short boss_Mode2BulletCount = 4;

Bullet_BAlien *Bmode2_bullet[boss_Mode2BulletCount]; //BOSS第二模式攻擊子彈



//玩家總分
float SMAlien_speed = 0.0015f;//中怪小怪速度
int PlayerTotalPoint_SAlien = 0; //打小怪
int PlayerTotalPoint_MAlien = 0; //打中怪
int PlayerTotalPoint_BAlien = 0; //打BOSS
bool Game_Over = false; //遊戲結束

bool isBossOut = false; //放出BOSS
bool isSMAlienClear = true; //SMAlien是否都已經消失於畫面

// 必須在 glewInit(); 執行完後,在執行物件實體的取得
MainRole *mainrole;	// 宣告 指標物件，結束時記得釋放
MainRole_Ring *mainrole_ring;	// 宣告 指標物件，結束時記得釋放
Cloud* cloud[6];
Bullet_Main* bullet_main;
short small_alien = 3; //螢幕上small alien 出現的最大數量
short middle_alien = 0; //螢幕上middle alien 出現的最大數量
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
void GameProcessUpdate();

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

			if (i < small_alien) { //空間是否被利用

				alien[i]->used = true;

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

			
			if (i < SAlien_space + middle_alien) { //空間是否被利用

				alien[i]->used = true;

			}
		}


		else if (i < SAlien_space + MAlien_space + BAlien_space)//設定BOSS alien
		{

			

				alien[i] = new BOSS_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection);
				
				if (i < SAlien_space + MAlien_space + BOSS_alien) { //空間是否被利用

					alien[i]->used = true;

				}

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
	
	//設定BOSS 子彈
	for (int i = 0; i < boss_Mode2BulletCount; i++)
	{
		Bmode2_bullet[i] = new Bullet_BAlien;
		Bmode2_bullet[i]->SetShader(g_mxModelView, g_mxProjection);
		
		//設定初始方向
		if ((i+1)%2)
		{
			Bmode2_bullet[i]->first_direction_x = LEFT;
			Bmode2_bullet[i]->_x = -3.0f;

		}
		else
		{
			Bmode2_bullet[i]->first_direction_x = RIGHT;

			Bmode2_bullet[i]->_x = 3.0f;
		}

		Bmode2_bullet[i]->first_direction_y = BOTTOM;

		Bmode2_bullet[i]->_y = -0.5f * i + 3.0f;

		Bmode2_bullet[i]->BulletTrans = Translate(Bmode2_bullet[i]->_x , Bmode2_bullet[i]->_y , 0.0f);
		
		Bmode2_bullet[i]->SetTRSMatrix(Bmode2_bullet[i]->BulletTrans);
	}
	

	// explo
	/*explo_alien = new Explo;
	explo_alien->SetShader(g_mxModelView, g_mxProjection);*/

	for (int i = 0; i < 5; i++)
	{
		explo_alien[i] = new Explo;
		explo_alien[i]->SetShader(g_mxModelView, g_mxProjection);


	}


	//test bonus cube;
	superCube = new SuperCube;
	superCube->SetShader(g_mxModelView, g_mxProjection);
	superCube->cubeStyle = 0; //設定cube樣式

	//test two gun
	superCube_twoGun = new SuperCube;
	superCube_twoGun->SetShader(g_mxModelView, g_mxProjection);
	superCube_twoGun->cubeStyle = 1; //設定cube樣式
	superCube_twoGun->SetColor(1.0f, 1.0f, 0.0f);
}


void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	int i; //for count
	
	for ( i= 0; i < 6; i++)
	{
		cloud[i]->Draw();
	}



	
	pGet_Draw_bullet = pHead_MainBullet_used;
	for ( i = 0; i < Bullet_Total_MainBullet_used; i++)
	{
		pGet_Draw_bullet->bullet_main->Draw();
		pGet_Draw_bullet = pGet_Draw_bullet->link;

	}



	//Draw Small + Middle Alien Bullet
	pGet_Draw_AlienBullet = pHead_AlienBullet_used;
	for ( i = 0; i < Bullet_Total_Alien_used; i++)
	{
		if (pGet_Draw_AlienBullet->isSAlien_bullet)
		{
			pGet_Draw_AlienBullet->bullet_main->Draw();
		}
		else// if (pGet_Draw_AlienBullet->isMAlien_bullet)
		{
			pGet_Draw_AlienBullet->bullet_MAlien->Draw();
		}
		
		pGet_Draw_AlienBullet = pGet_Draw_AlienBullet->link;
	}


	//Draw Alien
	for ( i = 0; i < SAlien_space + MAlien_space + BAlien_space; i++)
	{

		if (alien[i]->used && alien[i]->alife) { //有使用到的alien空間 且 為存活Alien

			alien[i]->Draw();

		}

	}



	// Boss mode 2 attack
	for ( i = 0; i < boss_Mode2BulletCount && BOSSMode == Two; i++)
	{
		Bmode2_bullet[i]->Draw();
	}
	
	//Draw Alien smoke
	for ( i = 0; i < 5; i++)
	{
		if (explo_alien[i]->used) {

			explo_alien[i]->Draw();
		}

	}


	//test bouns
	if (superCube->used)
	{
		superCube->Draw();
	}


	//test two gun
	if (superCube_twoGun->used)
	{
		superCube_twoGun->Draw();
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


//test雙槍管

enum Gun_Main
{
	LEFT_GUNMAIN = 0 , RIGHT_GUNMAIN = 1
};

int gunSide = LEFT_GUNMAIN; //子彈出口

void CreateTwoGunBullet_Main() {

	if (gunSide == LEFT_GUNMAIN) //左邊槍口
	{
		if (Bullet_Total_MainBullet_used == 0) {

		pHead_MainBullet_used = pHead_MainBullet_free;
		pHead_MainBullet_free = pHead_MainBullet_free->link;

		pHead_MainBullet_used->bullet_main->_x = mainrole->_x - 0.2f;
		pHead_MainBullet_used->bullet_main->_y = mainrole->_y - 0.2f;

		pHead_MainBullet_used->bullet_main->SetTRSMatrix(Translate(pHead_MainBullet_used->bullet_main->_x, pHead_MainBullet_used->bullet_main->_y, 0.0));

		pHead_MainBullet_used->link = NULL;
		pTail_MainBullet_used = pHead_MainBullet_used;

		Bullet_Total_MainBullet_free--;
		Bullet_Total_MainBullet_used++;


	}


	else if (Bullet_Total_MainBullet_used > 0) {

		pGet_MainBullet_used = pHead_MainBullet_free;
		pHead_MainBullet_free = pHead_MainBullet_free->link;

		pGet_MainBullet_used->bullet_main->_x = mainrole->_x - 0.2f;
		pGet_MainBullet_used->bullet_main->_y = mainrole->_y - 0.2f;

		pGet_MainBullet_used->bullet_main->SetTRSMatrix(Translate(pGet_MainBullet_used->bullet_main->_x, pGet_MainBullet_used->bullet_main->_y, 0.0));

		pTail_MainBullet_used->link = pGet_MainBullet_used; //結尾link指向新取得的頭
		pGet_MainBullet_used->link = NULL;//設定結尾為NULL
		pTail_MainBullet_used = pGet_MainBullet_used;//設定尾巴為PGet

		Bullet_Total_MainBullet_free--;
		Bullet_Total_MainBullet_used++;


	}
		gunSide = RIGHT_GUNMAIN;

	}
	

	else {


		if (Bullet_Total_MainBullet_used == 0) {

			pHead_MainBullet_used = pHead_MainBullet_free;
			pHead_MainBullet_free = pHead_MainBullet_free->link;

			pHead_MainBullet_used->bullet_main->_x = mainrole->_x + 0.2f;
			pHead_MainBullet_used->bullet_main->_y = mainrole->_y - 0.2f;

			pHead_MainBullet_used->bullet_main->SetTRSMatrix(Translate(pHead_MainBullet_used->bullet_main->_x, pHead_MainBullet_used->bullet_main->_y, 0.0));

			pHead_MainBullet_used->link = NULL;
			pTail_MainBullet_used = pHead_MainBullet_used;

			Bullet_Total_MainBullet_free--;
			Bullet_Total_MainBullet_used++;


		}


		else if (Bullet_Total_MainBullet_used > 0) {

			pGet_MainBullet_used = pHead_MainBullet_free;
			pHead_MainBullet_free = pHead_MainBullet_free->link;

			pGet_MainBullet_used->bullet_main->_x = mainrole->_x + 0.2f;
			pGet_MainBullet_used->bullet_main->_y = mainrole->_y - 0.2f;

			pGet_MainBullet_used->bullet_main->SetTRSMatrix(Translate(pGet_MainBullet_used->bullet_main->_x, pGet_MainBullet_used->bullet_main->_y, 0.0));

			pTail_MainBullet_used->link = pGet_MainBullet_used; //結尾link指向新取得的頭
			pGet_MainBullet_used->link = NULL;//設定結尾為NULL
			pTail_MainBullet_used = pGet_MainBullet_used;//設定尾巴為PGet

			Bullet_Total_MainBullet_free--;
			Bullet_Total_MainBullet_used++;


		}
		gunSide = LEFT_GUNMAIN;

	}



}



void CreateBullet_Alien(Alien *alien , char what_alien ) {

	
	switch (what_alien)
	{
	case 'B': //若為BOSS Alien 發射的子彈
		if (Bullet_Total_Alien_used == 0) { //第一個被使用的子彈

			pHead_AlienBullet_used = pHead_AlienBullet_free;  //從頭拿資源
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //將 free 的頭改成下一個節點


			pHead_AlienBullet_used->bullet_main->_x = alien->_x + boss_BulletCoordinate[boss_Mode1BulletNUM][0];
			pHead_AlienBullet_used->bullet_main->_y = alien->_y + boss_BulletCoordinate[boss_Mode1BulletNUM][1];
			if (BOSSMode == One) //第一攻擊模式
			{
				pHead_AlienBullet_used->bullet_main->fire_style = NORMAL;

			}

			else if (BOSSMode == Three) {

				if (boss_Mode3BulletNUM % 3 ==1)
				{
					pHead_AlienBullet_used->bullet_main->fire_style = LEFT_45;
				}
				else if (boss_Mode3BulletNUM % 3 == 2) {

					pHead_AlienBullet_used->bullet_main->fire_style = NORMAL;
				}
				
				else if (boss_Mode3BulletNUM % 3 == 0) {

					pHead_AlienBullet_used->bullet_main->fire_style = RIGHT_45;

				}

			}
			else
			{
				pHead_AlienBullet_used->bullet_main->fire_style = NORMAL;
			}



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

			pGet_AlienBullet_used->bullet_main->_x = alien->_x + boss_BulletCoordinate[boss_Mode1BulletNUM][0];
			pGet_AlienBullet_used->bullet_main->_y = alien->_y + boss_BulletCoordinate[boss_Mode1BulletNUM][1];
			

			if (BOSSMode == One) //第一攻擊模式
			{
				pGet_AlienBullet_used->bullet_main->fire_style = NORMAL;

			}
			else if (BOSSMode == Three) {//第二攻擊模式

				if (boss_Mode3BulletNUM % 3 == 1)
				{
					pGet_AlienBullet_used->bullet_main->fire_style = LEFT_45;
				}
				else if (boss_Mode3BulletNUM % 3 == 2) {

					pGet_AlienBullet_used->bullet_main->fire_style = NORMAL;
				}

				else if (boss_Mode3BulletNUM % 3 == 0) {

					pGet_AlienBullet_used->bullet_main->fire_style = RIGHT_45;

				}

			}
			else
			{
				pGet_AlienBullet_used->bullet_main->fire_style = NORMAL;
			}



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
			pHead_AlienBullet_used->bullet_main->fire_style = NORMAL;
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
			pGet_AlienBullet_used->bullet_main->fire_style = NORMAL;
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


//產生煙霧
void CreateSmoke( float _x , float _y ) {

	for (int i = 0; i < 5  && !Game_Over; i++)
	{
		if (explo_alien[i]->used == false) {
			
			explo_alien[i]->used=true;
			explo_alien[i]->_x = _x;
			explo_alien[i]->_y = _y;
			explo_alien[i]->mxTran_Smoke = Translate(explo_alien[i]->_x, explo_alien[i]->_y, 0.0f);
			explo_alien[i]->SetTRSMatrix(explo_alien[i]->mxTran_Smoke);
			break;
		}


	}


}





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
		
			if (!(pGet_Check_AlienBullet->bullet_main->_x > -2.5f && pGet_Check_AlienBullet->bullet_main->_x < 2.5f && pGet_Check_AlienBullet->bullet_main->_y > -2.5f && pGet_Check_AlienBullet->bullet_main->_y < 2.5f) || pGet_Check_AlienBullet->bullet_main->HurtMainRole ) {

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
float timer_BAlien = 0;

void onFrameMove(float delta)
{
	timer_onFrameMove += delta;
	timer_canHurtMainRole += delta;
	timer_BAlien += delta;

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
			for (int i = 0; i < SAlien_space + MAlien_space + BAlien_space   ; i++) // *注意 alien的空間須被使用
			{
				if(alien[i]->used)
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
				PlayerTotalPoint_SAlien++; //玩家一分
			}

			alien[i]->AutomaticMotion();
		}

		
		//更新 alien 子彈位置
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
				pGet_AlienBullet_used->bullet_MAlien->AutoTranslate_Bullet(); 
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
				PlayerTotalPoint_MAlien++; //玩家一分
			}

			alien[i]->AutomaticMotion(mainrole->_x , mainrole->_y);
			
		}


		//更新BOSS alien 位置
		for (int i = SAlien_space + MAlien_space; i < SAlien_space + MAlien_space + BOSS_alien; i++)
		{
			//若alien 死亡則玩家家一分
			if (alien[i]->alife == false) { //alien死亡
				PlayerTotalPoint_MAlien++; //玩家一分
			}

			alien[i]->AutomaticMotion(timer_BAlien);

		}

		// boss mode2 bullet
		for (int i = 0; i < boss_Mode2BulletCount && BOSSMode == Two; i++)
		{
			Bmode2_bullet[i]->AutoTranslate_Bullet();
			mainrole->AutoCheckHurt_MainRole(Bmode2_bullet[i]->_x, Bmode2_bullet[i]->_y, Bmode2_bullet[i]->MAX_X, Bmode2_bullet[i]->MAX_Y, &Bmode2_bullet[i]->HurtMainRole, &mainrole_ring->_defenceBallNUM);//偵測 main role是否被子彈打中			
			//被傷害後無敵狀態計算時間
			if (Bmode2_bullet[i]->HurtMainRole) {
				timer_canHurtMainRole = 0.0f;
				mainrole->SetAlpha(0.6); //無敵狀態為半透明
				mainrole_ring->SetAlpha(0.6); //無敵狀態為半透明
			}

			Bmode2_bullet[i]->HurtMainRole = false; //reset 狀態

			if ((Bmode2_bullet[i]->_x >3.0f || Bmode2_bullet[i]->_x < -3.0f) && Game_Over) //若超過距離且game over則不需再新增mode2的x y位置
			{
				BOSSMode = None;
			}


		}

		//更新smoke
		for (int i = 0; i < 5 ; i++)
		{
			if (explo_alien[i]->used) {
				explo_alien[i]->AutomaticMotion(delta);
				
			}
			
		}

		//更新Super Cube
		
		if(superCube->used){ //Super有被使用
			superCube->AutomaticMotion(mainrole->_x , mainrole->_y);
			if (!touch_superCube) {

				superCube->CheackMainRole(mainrole->_x, mainrole->_y, mainrole->MAX_X, mainrole->MAX_Y );

				if (touch_superCube) { //若更新為true 則mainrole 回復原來狀態 且不得攻擊
					mainrole->can_change_hurtMain = false;
					mainrole->SetAlpha(1.0);
					mainrole_ring->SetAlpha(1.0);
				}
			}

			else //更新super 是否有打到alien
			{

				//檢查是否有Alien被main role打到
				for (int i = 0; i < SAlien_space + MAlien_space ; i++) // *注意 alien的空間須被使用
				{
					
					if (alien[i]->used)
						alien[i]->CheckSuperHurt(superCube->_x, superCube->_y, superCube->MAX_X, superCube->MAX_Y);

				}


			}

		}


		//test two gun 
		if (superCube_twoGun->used) {

			superCube_twoGun->AutomaticMotion(mainrole->_x, mainrole->_y);
			superCube_twoGun->CheackMainRole(mainrole->_x, mainrole->_y, mainrole->MAX_X, mainrole->MAX_Y);

		}

		
		
		


		//更新遊戲流程
		GameProcessUpdate();

		timer_onFrameMove = 0;
	}


	//更新保護機制
	if (timer_canHurtMainRole >4.0 && mainrole->can_change_hurtMain ==false && !touch_superCube) { //維持四秒無敵狀態 且不為無敵狀態
		
		mainrole->can_change_hurtMain = true; //可重新攻擊
		mainrole->SetAlpha(1.0);
		mainrole_ring->SetAlpha(1.0); 


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
	if (clickLaunchBullet && canLaunchBullet && Bullet_Total_MainBullet_free > 0) {
		
		if (touch_twoGunStar) { //兩槍管
			CreateTwoGunBullet_Main();
			CreateTwoGunBullet_Main();
		}
		
		else//一般狀態
		{
			CreateBullet_Main();
		}

		
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
				if (alien[i]->_y > -2.5 && alien[i]->_y < 2.5  && alien[i]->alife) {  //Alien 需再存活狀態
					CreateBullet_Alien(alien[i] , 'S');
					
				}
			}

			else if(i < SAlien_space + middle_alien){ //MAlien 創造子彈
				if (alien[i]->_y > -2.5 && alien[i]->_y < 2.5 && alien[i]->alife) { //Alien 需再存活狀態
				
					CreateBullet_Alien(alien[i], 'M');
				
				
				}
				
			}
			
		}

		//BOSS三重子彈
		for (boss_Mode1BulletNUM = 0; boss_Mode1BulletNUM < 3 && BOSS_alien > 0 && BOSSMode == One && timer_BAlien > 5.0f; boss_Mode1BulletNUM++) //Boss存在則發射子彈 且模式為Mode1
		{
			CreateBullet_Alien(alien[SAlien_space + MAlien_space] , 'B');
		}



		//BOSS 兩邊三重子彈
		for ( boss_Mode1BulletNUM = 0; boss_Mode1BulletNUM < 2; boss_Mode1BulletNUM++) //兩個出彈口
		{
			for (boss_Mode3BulletNUM = 0; boss_Mode3BulletNUM < 3 && BOSS_alien > 0 && BOSSMode == Three; boss_Mode3BulletNUM++) //Boss存在則發射子彈 且模式為Mode3
			{

				CreateBullet_Alien(alien[SAlien_space + MAlien_space], 'B');

			}
		}
		
		




		timer_AlienBulletLaunch = 0.0f;
	
	}


}



bool super_twoGunFlag = false;
bool superCubeFlag = false;
float superCube_timer = 0.0f;
//依據流程跟新怪設狀態
void GameProcessUpdate() {
	//若總分到達十分則放出中怪
	if (PlayerTotalPoint_SAlien == 3)
	{
		middle_alien = 1; //放出一隻中怪
		
		alien[SAlien_space]->used = true;

		if (!superCubeFlag) { //放出superCube
			superCube->used = true;
			superCube->if_first_cube = true;
			touch_superCube = false;
			superCubeFlag = true;
			superCube_timer = 0.0f;
		}

	}

	
	else if(PlayerTotalPoint_SAlien >= 7 && PlayerTotalPoint_MAlien >= 3)
	{
		isBossOut = true; //放出BOSS

		isSMAlienClear = true; //關閉flag
		for (int i = 0; i < SAlien_space + MAlien_space + BAlien_space; i++)
		{
			if (alien[i]->used == true) //有一Alien 存在於畫面
			{
				isSMAlienClear = false; //開啟flag
				break;
			}
			
		}
		

		if (isSMAlienClear)
		{
			BOSS_alien = 1; //放出一隻BOSS
			alien[SAlien_space + MAlien_space]->used = true;
			timer_BAlien = 0.0f;

			if (!super_twoGunFlag ) { //放出superCube
				superCube_twoGun->used = true;
				superCube_twoGun->if_first_cube = true;
				touch_twoGunStar = false;
				super_twoGunFlag = true;
				superCube_timer = 0.0f;
			}



		}
		
		

	}


	if ((superCubeFlag == true || super_twoGunFlag==true) && superCube_timer > 10.0f) {
		
		superCube->used = false; //SuperCube 消失
		
		touch_twoGunStar = false; //停止雙槍射擊

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
	case't': //雙槍管
		superCube_twoGun->used = true;
		superCube_twoGun->if_first_cube = true;
		touch_twoGunStar = false;
		superCube_timer = 0.0f;
		break;

	case'x': //test super cube
		superCube->used = true;
		superCube->if_first_cube = true;
		touch_superCube = false;
		superCube_timer = 0.0f;
		break;
	case '1':
		BOSSMode = One; //BOSS改變成第一型態test
		break;
	case '2':
		BOSSMode = Two; //BOSS改變成第二型態test

		break;
	case '3':
		BOSSMode = Three; //BOSS改變成第二型態test
		break;
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
			delete pHead_AlienBullet_free;
			pHead_AlienBullet_free = pGet_Draw_AlienBullet;
		}


		for (int i = 0; i < Bullet_Total_Alien_used; i++)
		{
			pGet_Draw_AlienBullet = pHead_AlienBullet_used->link;
			delete pHead_AlienBullet_used;
			pHead_AlienBullet_used = pGet_Draw_AlienBullet;
		}


		for (int i = 0; i < Bullet_Total_MainBullet_free; i++)
		{
			pGet_Draw_bullet = pHead_MainBullet_free->link;
			delete pHead_MainBullet_free;
			pHead_MainBullet_free = pGet_Draw_bullet;
		}


		for (int i = 0; i < Bullet_Total_MainBullet_used; i++)
		{
			pGet_Draw_bullet = pHead_MainBullet_used->link;
			delete pHead_MainBullet_used;
			pHead_MainBullet_used = pGet_Draw_bullet;
		}

		delete mainrole;
		delete mainrole_ring;
		
		for (int i = 0; i < 6; i++)
		{
			delete cloud[i];
		}


		for (int i = 0; i < 7; i++)
		{
			delete alien[i];
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


    glutCreateWindow( "Shooting Game" );

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE; 
	
	//允許透明度設定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

	glewInit();  
    init();

	

	
	glutKeyboardFunc(win_keyFunc);
	
	glutMotionFunc(win_mousemotion);//滑鼠在按下按鍵時一樣操控船艦
	glutPassiveMotionFunc(win_PassiveMotion); //用滑鼠操控船艦

	glutMouseFunc(win_mouse); //發射子彈
	

	glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	

    glutMainLoop();
    return 0;
}
