#include <math.h>
#include <time.h>
#include "header/Angel.h"
#include "Characters/mainrole.h"
#include "Characters/MainRole_Ring.h"
#include "Background/Cloud.h"
#include "Characters/Alien.h"
#include "Weapon/Bullet_Main.h"


#define SPACE_KEY 32

//�ù��j�pdefine
#define SCREENWIDTH 360
#define SCREENHEIGHT 640
#define SCREENWIDTH_HALF (SCREENWIDTH/2.0)
#define SCREENHEIGHT_HALF (SCREENHEIGHT/2.0)

//BOSS �l�u�o�g�y��
 int boss_Mode1BulletCount = 0;
float boss_BulletCoordinate[3][2] = {

	0.75f , -0.6f,
   -0.75f , -0.6f,
    0.0f  , -0.2f

};



//���a�`��
int PlayerTotalPoint = 0;
bool isBossOut = false; //�ĤGAlien���A


// �����b glewInit(); ���槹��,�b���檫����骺���o
MainRole *mainrole;	// �ŧi ���Ъ���A�����ɰO�o����
MainRole_Ring *mainrole_ring;	// �ŧi ���Ъ���A�����ɰO�o����
Cloud* cloud[6];
Bullet_Main* bullet_main;
short small_alien = 3; //�ù��Wsmall alien �X�{���̤j�ƶq
short middle_alien = 1; //�ù��Wmiddle alien �X�{���̤j�ƶq
short BOSS_alien = 0; //�ù��WBOSS alien �X�{���̤j�ƶq
short SAlien_space = 4;  // SAlien �Ŷ��Ӽ�
short MAlien_space = 2;  // MAlien �Ŷ��Ӽ�
short BAlien_space = 1;  // BOSS �Ŷ��Ӽ�

const short all_alien = 7; /* small_alien + middle_alien + BOSS_alien*/

Alien* alien[all_alien];

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;


// �禡���쫬�ŧi
void IdleProcess();
void CreateGameObject();
void CheckBullet();

//�l�u�ŧi
typedef struct Bullet_Node_struct {
	Bullet_Main *bullet_main;
	struct Bullet_Node_struct*link;

} Bullet_NODE , *Bullet_PNODE ;



//�D���l�u�]�w
const short Bullet_space_NUM = 40; //�e���̦h���ͪ��l�u�ƶq


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
GLuint ShaderHandle_Bullet; //���o Shader ���Ǹ�

int Bullet_Total_MainBullet_used = 0;
int Bullet_Total_MainBullet_free = 0;



//Small Alien �l�u���O�ŧi
typedef struct Bullet_Node_struct_SAlien {
	Bullet_SAlien* bullet_main;
	Bullet_MAlien* bullet_MAlien;
	// �Ω�P�_�{�b��SAlien or MAlien
	bool isSAlien_bullet = false;
	bool isMAlien_bullet = false;
	bool isBAlien_bullet = false;
	struct Bullet_Node_struct_SAlien* link;

} Bullet_NODE_SAlien, * Bullet_PNODE_SAlien;



//Small Alien �l�u�]�w
const short SAlienBullet_NUM = 30;//�e���̦h���ͪ�Small Alien�u�ƶq
const short MAlienBullet_NUM = 30;//�e���̦h���ͪ�Small Alien�u�ƶq
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




//������m�B�j�p�}�C
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
	
	srand((unsigned)time(NULL));//�]�w�üƺؤl

    g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

	CreateGameObject();	//���o����


    glClearColor( 0.9882, 0.6718, 0.6445, 1.0 ); // black background
}


//���o����
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
		if(i < SAlien_space){ //�]�wsmall alien �Ŷ�
		
			if (i == 0) { //�u���]�w�Ĥ@��Shader
				alien[i] = new Small_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection);
				ShaderHandle = alien[i]->GetShaderHandle();
			}

			else //�u�Ϋe����Shader
			{
				alien[i] = new Small_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);

			}

		}

		else if( i < SAlien_space + MAlien_space)//�]�wmiddle alien
		{
			
			if (i == SAlien_space) //middle alien�_�l�Ŷ�
			{
				alien[i] = new Middle_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection);
				ShaderHandle = alien[i]->GetShaderHandle();

			
				

			}

			else //�u�Ϋe����Shader
			{
				alien[i] = new Middle_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection, ShaderHandle);
			

			}

			

		}


		else if (i < SAlien_space + MAlien_space + BAlien_space)//�]�wBOSS alien
		{

				alien[i] = new BOSS_Alien;
				alien[i]->SetShader(g_mxModelView, g_mxProjection);
				alien[i]->_y = 1.5f; 
				alien[i]->SetTRSMatrix(Translate(alien[i]->_x, alien[i]->_y,0.0f));

		}


		

	}


	//�s��l�u���x�s�Ŷ�
	for (int i = 0; i < Bullet_space_NUM; i++)
	{
		if (i == 0) {

			if ((pHead_MainBullet_free = (Bullet_PNODE)malloc(sizeof(Bullet_NODE))) ==NULL) {
			
				printf("�O����Ŷ�����");
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
				printf("�O����Ŷ�����");
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

	

	//Small + Middle Alien �s��l�u���Ŷ�
	for (int i = 0; i < SAlienBullet_NUM + MAlienBullet_NUM; i++)
	{
		if (i == 0) {

			if ((pHead_AlienBullet_free = (Bullet_PNODE_SAlien)malloc(sizeof(Bullet_NODE_SAlien))) == NULL) {

				printf("�O����Ŷ�����\n");
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

		else if(i < SAlienBullet_NUM) //�]�wsmall alien bullet
		{
			if ((pGet_AlienBullet_free = (Bullet_PNODE_SAlien)malloc(sizeof(Bullet_NODE_SAlien))) == NULL) {

				printf("�O����Ŷ�����\n");
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


		else if (i < SAlienBullet_NUM + MAlienBullet_NUM) //�]�wmiddle alien bullet
		{
			if ((pGet_AlienBullet_free = (Bullet_PNODE_SAlien)malloc(sizeof(Bullet_NODE_SAlien))) == NULL) {

				printf("�O����Ŷ�����\n");
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

		Bullet_Total_Alien_free++; //�i�Τl�u�ƼW�[�@


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
	if(middle_alien > 0){  //�Y�����Ǧs�b

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

	glutSwapBuffers();	// �洫 Frame Buffer
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

		pTail_MainBullet_used->link = pGet_MainBullet_used; //����link���V�s���o���Y
		pGet_MainBullet_used->link = NULL;//�]�w������NULL
		pTail_MainBullet_used = pGet_MainBullet_used;//�]�w���ڬ�PGet

		Bullet_Total_MainBullet_free--;
		Bullet_Total_MainBullet_used++;


	}
	
	
}


void CreateBullet_Alien(Alien *alien , char what_alien ) {

	
	switch (what_alien)
	{
	case 'B': //�Y��BOSS Alien �o�g���l�u
		if (Bullet_Total_Alien_used == 0) { //�Ĥ@�ӳQ�ϥΪ��l�u

			pHead_AlienBullet_used = pHead_AlienBullet_free;  //�q�Y���귽
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //�N free ���Y�令�U�@�Ӹ`�I


			pHead_AlienBullet_used->bullet_main->_x = alien->_x + boss_BulletCoordinate[boss_Mode1BulletCount][0];
			pHead_AlienBullet_used->bullet_main->_y = alien->_y + boss_BulletCoordinate[boss_Mode1BulletCount][1];
			pHead_AlienBullet_used->isSAlien_bullet = true; //�]�w�l�u��B
			pHead_AlienBullet_used->isMAlien_bullet = false; //�]�w�l�u��B
			pHead_AlienBullet_used->isBAlien_bullet = true; //�]�w�l�u��B



			pHead_AlienBullet_used->bullet_main->SetTRSMatrix( Translate(pHead_AlienBullet_used->bullet_main->_x, pHead_AlienBullet_used->bullet_main->_y, 0.0) );


			pHead_AlienBullet_used->link = NULL; //�]�w������NULL
			pTail_AlienBullet_used = pHead_AlienBullet_used; //�]�w���ڬ�PHead


			Bullet_Total_Alien_used++; //�w�ΪŶ��ƶq�[�@
			Bullet_Total_Alien_free--;//���ΪŶ��ƶq��@



		}


		else if ((Bullet_Total_Alien_used < SAlienBullet_NUM + MAlienBullet_NUM))
		{
			pGet_AlienBullet_used = pHead_AlienBullet_free; //�q�Y���귽
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //�N free ���Y�令�U�@�Ӹ`�I

			pGet_AlienBullet_used->bullet_main->_x = alien->_x + boss_BulletCoordinate[boss_Mode1BulletCount][0];
			pGet_AlienBullet_used->bullet_main->_y = alien->_y + boss_BulletCoordinate[boss_Mode1BulletCount][1];
			pGet_AlienBullet_used->isSAlien_bullet = true; //�]�w�l�u��B
			pGet_AlienBullet_used->isMAlien_bullet = false; //�]�w�l�u��B
			pGet_AlienBullet_used->isBAlien_bullet = true; //�]�w�l�u��B



			pGet_AlienBullet_used->bullet_main->SetTRSMatrix( Translate(pGet_AlienBullet_used->bullet_main->_x, pGet_AlienBullet_used->bullet_main->_y, 0.0));

			pTail_AlienBullet_used->link = pGet_AlienBullet_used; //����link���V�s���o���Y
			pGet_AlienBullet_used->link = NULL;//�]�w������NULL
			pTail_AlienBullet_used = pGet_AlienBullet_used;//�]�w���ڬ�PGet

			Bullet_Total_Alien_used++; //�w�ΪŶ��ƶq�[�@
			Bullet_Total_Alien_free--;//���ΪŶ��ƶq��@

		}


		break;
	case 'S'://�Y��Small Alien �o�g���l�u

		if (Bullet_Total_Alien_used == 0) { //�Ĥ@�ӳQ�ϥΪ��l�u

			pHead_AlienBullet_used = pHead_AlienBullet_free;  //�q�Y���귽
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //�N free ���Y�令�U�@�Ӹ`�I


			pHead_AlienBullet_used->bullet_main->_x = alien->_x;
			pHead_AlienBullet_used->bullet_main->_y = alien->_y;
			pHead_AlienBullet_used->isSAlien_bullet = true; //�]�w�l�u��S
			pHead_AlienBullet_used->isMAlien_bullet = false; //�]�w�l�u��S
			pHead_AlienBullet_used->isBAlien_bullet = false; //�]�w�l�u��B
			


			pHead_AlienBullet_used->bullet_main->SetTRSMatrix(Translate(pHead_AlienBullet_used->bullet_main->_x, pHead_AlienBullet_used->bullet_main->_y, 0.0));


			pHead_AlienBullet_used->link = NULL; //�]�w������NULL
			pTail_AlienBullet_used = pHead_AlienBullet_used; //�]�w���ڬ�PHead


			Bullet_Total_Alien_used++; //�w�ΪŶ��ƶq�[�@
			Bullet_Total_Alien_free--;//���ΪŶ��ƶq��@



		}


		else if ((Bullet_Total_Alien_used < SAlienBullet_NUM + MAlienBullet_NUM))
		{
			pGet_AlienBullet_used = pHead_AlienBullet_free; //�q�Y���귽
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //�N free ���Y�令�U�@�Ӹ`�I

			pGet_AlienBullet_used->bullet_main->_x = alien->_x;
			pGet_AlienBullet_used->bullet_main->_y = alien->_y;
			pGet_AlienBullet_used->isSAlien_bullet = true; //�]�w�l�u��S
			pGet_AlienBullet_used->isMAlien_bullet = false; //�]�w�l�u��S
			pGet_AlienBullet_used->isBAlien_bullet = false; //�]�w�l�u��B

			

			pGet_AlienBullet_used->bullet_main->SetTRSMatrix(Translate(pGet_AlienBullet_used->bullet_main->_x, pGet_AlienBullet_used->bullet_main->_y, 0.0));

			pTail_AlienBullet_used->link = pGet_AlienBullet_used; //����link���V�s���o���Y
			pGet_AlienBullet_used->link = NULL;//�]�w������NULL
			pTail_AlienBullet_used = pGet_AlienBullet_used;//�]�w���ڬ�PGet

			Bullet_Total_Alien_used++; //�w�ΪŶ��ƶq�[�@
			Bullet_Total_Alien_free--;//���ΪŶ��ƶq��@

		}



		break;

	case 'M': //�Y��Middle Alien �o�g���l�u


		if (Bullet_Total_Alien_used == 0) { //�Ĥ@�ӳQ�ϥΪ��l�u

			pHead_AlienBullet_used = pHead_AlienBullet_free;  //�q�Y���귽
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //�N free ���Y�令�U�@�Ӹ`�I

			pHead_AlienBullet_used->bullet_MAlien->_x = alien->_x;
			pHead_AlienBullet_used->bullet_MAlien->_y = alien->_y;
			pHead_AlienBullet_used->bullet_MAlien->MainRoleDis_x = alien->dis_x;
			pHead_AlienBullet_used->bullet_MAlien->MainRoleDis_y = alien->dis_y;
			


			pHead_AlienBullet_used->isSAlien_bullet = false; //�]�w�l�u��M
			pHead_AlienBullet_used->isMAlien_bullet = true; //�]�w�l�u��M
			pHead_AlienBullet_used->isBAlien_bullet = false; //�]�w�l�u��B
			

			pHead_AlienBullet_used->bullet_MAlien->SetTRSMatrix(Translate(pHead_AlienBullet_used->bullet_MAlien->_x, pHead_AlienBullet_used->bullet_MAlien->_y, 0.0));


			pHead_AlienBullet_used->link = NULL; //�]�w������NULL
			pTail_AlienBullet_used = pHead_AlienBullet_used; //�]�w���ڬ�PHead


			Bullet_Total_Alien_used++; //�w�ΪŶ��ƶq�[�@
			Bullet_Total_Alien_free--;//���ΪŶ��ƶq��@



		}


		else if ((Bullet_Total_Alien_used < SAlienBullet_NUM + MAlienBullet_NUM))
		{
			pGet_AlienBullet_used = pHead_AlienBullet_free; //�q�Y���귽
			pHead_AlienBullet_free = pHead_AlienBullet_free->link;  //�N free ���Y�令�U�@�Ӹ`�I

			pGet_AlienBullet_used->bullet_MAlien->_x = alien->_x;
			pGet_AlienBullet_used->bullet_MAlien->_y = alien->_y;
			pGet_AlienBullet_used->bullet_MAlien->MainRoleDis_x = alien->dis_x;
			pGet_AlienBullet_used->bullet_MAlien->MainRoleDis_y = alien->dis_y;
		

			pGet_AlienBullet_used->isSAlien_bullet = false; //�]�w�l�u��M
			pGet_AlienBullet_used->isMAlien_bullet = true; //�]�w�l�u��M
			pGet_AlienBullet_used->isBAlien_bullet = false; //�]�w�l�u��B

			
			pGet_AlienBullet_used->bullet_MAlien->SetTRSMatrix(Translate(pGet_AlienBullet_used->bullet_MAlien->_x, pGet_AlienBullet_used->bullet_MAlien->_y, 0.0));

			pTail_AlienBullet_used->link = pGet_AlienBullet_used; //����link���V�s���o���Y
			pGet_AlienBullet_used->link = NULL;//�]�w������NULL
			pTail_AlienBullet_used = pGet_AlienBullet_used;//�]�w���ڬ�PGet

			Bullet_Total_Alien_used++; //�w�ΪŶ��ƶq�[�@
			Bullet_Total_Alien_free--;//���ΪŶ��ƶq��@

		}




		break;
	default:
		break;
	}




}

//----------------------------------------------------------------------------



//�ˬd�l�u�O�_�W�L���Ľd��, �Y�W�L�h�s���n�e��`�I�A��delete
void CheckBullet() {
	

	//printf("%d\n" , Bullet_Total_MainBullet_used);
	pGet_Check_bullet = pHead_MainBullet_used;

	for (int i = 0; i < Bullet_Total_MainBullet_used; i++)
	{

		
		
		if (pGet_Check_bullet->bullet_main->_y > 1.8 || pGet_Check_bullet->bullet_main->HurtAlien ) { //�W�L���ĶZ���Φ����u   //�����D
			
			//�Y�R�����O�Ĥ@�Ӹ`�I�h�� pHead����m
			if (pGet_Check_bullet == pHead_MainBullet_used) {
				
				pTail_MainBullet_free->link = pGet_Check_bullet; //�N��m�Pfree�����ڬ۳s
				pTail_MainBullet_free = pGet_Check_bullet; //free �����ڬ��s�W���`�I
				pHead_MainBullet_used = pHead_MainBullet_used->link; //�Nused���Y���V�U�Ӹ`�I
				pTail_MainBullet_free->bullet_main->HurtAlien = false; //reset�l�u���A
				pTail_MainBullet_free->link = NULL; //free ����link��NULL
				
			}

			//�Y�R�����O�̫�@�Ӹ`�I�h�� pTail����m
			else if (pGet_Check_bullet == pTail_MainBullet_used) {


				pTail_MainBullet_free->link = pGet_Check_bullet;
				pTail_MainBullet_free = pGet_Check_bullet;
				pGet_Last_Draw_bullet->link = NULL;
				pTail_MainBullet_used = pGet_Last_Draw_bullet; //�]�wused���s����
				pTail_MainBullet_free->bullet_main->HurtAlien = false; //reset�l�u���A
				pTail_MainBullet_free->link = NULL;

			}

			//�Y�����Y�]���������`�I�h�s���n�Y����m
			else {
			
				
				pTail_MainBullet_free->link = pGet_Check_bullet;
				pTail_MainBullet_free = pGet_Check_bullet;
				pGet_Last_Draw_bullet->link = pGet_Check_bullet->link;
				pTail_MainBullet_free->bullet_main->HurtAlien = false; //reset�l�u���A
				pTail_MainBullet_free->link = NULL;
			}
			
			
			Bullet_Total_MainBullet_used--;
			Bullet_Total_MainBullet_free++;

			break; //�Y���R���`�I�h���X�j��]���`�I�n���s�p��
		
		}

		pGet_Last_Draw_bullet = pGet_Check_bullet; //����e�@����pGet �H�K���n�ɦ��^�Ŷ�
		pGet_Check_bullet = pGet_Check_bullet->link;


	}

	
}


//�ˬdSmall Alien �l�u�O�_�W�L���İ�
void CheckBullet_Alien(){


	


	pGet_Check_AlienBullet = pHead_AlienBullet_used;

	for (int i = 0; i <Bullet_Total_Alien_used; i++)
	{
		if(pGet_Check_AlienBullet->isSAlien_bullet){
		
			if (!(pGet_Check_AlienBullet->bullet_main->_y > -2.0) || pGet_Check_AlienBullet->bullet_main->HurtMainRole ) {

				if (pGet_Check_AlienBullet == pHead_AlienBullet_used) { //�p�G�R�����O�Ĥ@�Ӹ`�I

					pTail_AlienBullet_free->link = pGet_Check_AlienBullet; //�N��m�Pfree�����ڬ۳s
					pTail_AlienBullet_free = pGet_Check_AlienBullet; //free �����ڬ��s�W���`�I
					pHead_AlienBullet_used = pHead_AlienBullet_used->link; //�Nused���Y���V�U�Ӹ`�I
					pTail_AlienBullet_free->bullet_main->HurtMainRole = false; //reset�l�u���A
					pTail_AlienBullet_free->link = NULL; //free ����link��NULL

				}

				else if (pGet_Check_AlienBullet == pTail_AlienBullet_used) { //�p�G�R�����O���ڪ�����

					pTail_AlienBullet_free->link = pGet_Check_AlienBullet;
					pTail_AlienBullet_free = pGet_Check_AlienBullet;
					pGet_Last_Draw_AlienBullet_used->link = NULL;
					pTail_AlienBullet_used = pGet_Last_Draw_AlienBullet_used; //�]�wused���s����
					pTail_AlienBullet_free->bullet_main->HurtMainRole = false; //reset�l�u���A
					pTail_AlienBullet_free->link = NULL;
				}

				else { //�R������������//�A�b�g�o��
					pTail_AlienBullet_free->link = pGet_Check_AlienBullet;
					pTail_AlienBullet_free = pGet_Check_AlienBullet;
					pGet_Last_Draw_AlienBullet_used->link = pGet_Check_AlienBullet->link;
					pTail_AlienBullet_free->bullet_main->HurtMainRole = false; //reset�l�u���A
					pTail_AlienBullet_free->link = NULL;

				}

				Bullet_Total_Alien_used--; //�w�ΪŶ��ƶq��@
				Bullet_Total_Alien_free++;//���ΪŶ��ƶq�[�@
				break;

			}
		
		}
	
		else if (pGet_Check_AlienBullet->isMAlien_bullet) {

			if (!(pGet_Check_AlienBullet->bullet_MAlien->_x > -2.5f && pGet_Check_AlienBullet->bullet_MAlien->_x < 2.5f && pGet_Check_AlienBullet->bullet_MAlien->_y > -2.5f && pGet_Check_AlienBullet->bullet_MAlien->_y < 2.5f )|| pGet_Check_AlienBullet->bullet_MAlien->HurtMainRole) {

				if (pGet_Check_AlienBullet == pHead_AlienBullet_used) { //�p�G�R�����O�Ĥ@�Ӹ`�I

					pTail_AlienBullet_free->link = pGet_Check_AlienBullet; //�N��m�Pfree�����ڬ۳s
					pTail_AlienBullet_free = pGet_Check_AlienBullet; //free �����ڬ��s�W���`�I
					pHead_AlienBullet_used = pHead_AlienBullet_used->link; //�Nused���Y���V�U�Ӹ`�I
					pTail_AlienBullet_free->bullet_MAlien->HurtMainRole = false; //reset�l�u���A
					pTail_AlienBullet_free->link = NULL; //free ����link��NULL

				}

				else if (pGet_Check_AlienBullet == pTail_AlienBullet_used) { //�p�G�R�����O���ڪ�����

					pTail_AlienBullet_free->link = pGet_Check_AlienBullet;
					pTail_AlienBullet_free = pGet_Check_AlienBullet;
					pGet_Last_Draw_AlienBullet_used->link = NULL;
					pTail_AlienBullet_used = pGet_Last_Draw_AlienBullet_used; //�]�wused���s����
					pTail_AlienBullet_free->bullet_MAlien->HurtMainRole = false; //reset�l�u���A
					pTail_AlienBullet_free->link = NULL;
				}

				else { //�R������������//�A�b�g�o��
					pTail_AlienBullet_free->link = pGet_Check_AlienBullet;
					pTail_AlienBullet_free = pGet_Check_AlienBullet;
					pGet_Last_Draw_AlienBullet_used->link = pGet_Check_AlienBullet->link;
					pTail_AlienBullet_free->bullet_MAlien->HurtMainRole = false; //reset�l�u���A
					pTail_AlienBullet_free->link = NULL;

				}

				Bullet_Total_Alien_used--; //�w�ΪŶ��ƶq��@
				Bullet_Total_Alien_free++;//���ΪŶ��ƶq�[�@
				break;

			}

		}


		pGet_Last_Draw_AlienBullet_used = pGet_Check_AlienBullet;//����e�@����pGet �H�K���n�ɦ��^�Ŷ�
		pGet_Check_AlienBullet = pGet_Check_AlienBullet->link;

	}


}




float timer_onFrameMove = 0; //rotation's timer
float timer_canHurtMainRole = 0; //rotation's timer


void onFrameMove(float delta)
{
	timer_onFrameMove += delta;
	timer_canHurtMainRole += delta;

	if (timer_onFrameMove > 1.0 / 1500.0) { //�C1/1000���s�@��
		
	
		
		mainrole_ring->AutomaticRotation( mainrole->mxTran_Main );//�P���۰ʿ��� �ǤJ���h

		//��s������m
		for (int i = 0; i < 6; i++)
		{
			cloud[i]->AutoTranslate_Background();
		}

		
		//��s�l�u���u 
		pGet_Move_bullet = pHead_MainBullet_used;
		for (int i = 0; i < Bullet_Total_MainBullet_used; i++)
		{
			pGet_Move_bullet->bullet_main->AutoTranslate_Bullet();

			//�ˬd�O�_��Alien�Q�l�u����
			for (int i = 0; i < SAlien_space + middle_alien ; i++)
			{
				
				alien[i]->AutoCheckHurtDie(pGet_Move_bullet->bullet_main->_x, pGet_Move_bullet->bullet_main->_y , pGet_Move_bullet->bullet_main->MAX_X, pGet_Move_bullet->bullet_main->MAX_Y, &pGet_Move_bullet->bullet_main->HurtAlien );
				
			}

			pGet_Move_bullet = pGet_Move_bullet->link;
		}

		//�ˬd�O�_���l�u�W�L���İ�
		CheckBullet();

		//��sSAlien ��m
		for (int i = 0; i < small_alien; i++)
		{
			//�Yalien ���`�h���a�a�@��
			if (alien[i]->alife == false) { //alien���`
				PlayerTotalPoint++; //���a�@��
			}

			alien[i]->AutomaticMotion();
		}

		
		//��ssmall alien �l�u��m
		pGet_AlienBullet_used = pHead_AlienBullet_used;
		for (int i = 0; i < Bullet_Total_Alien_used; i++)
		{
			if (pGet_AlienBullet_used->isSAlien_bullet == true && pGet_AlienBullet_used->isMAlien_bullet == false) //��SAlien bullet
			{
				pGet_AlienBullet_used->bullet_main->AutoTranslate_Bullet();
				mainrole->AutoCheckHurt_MainRole(pGet_AlienBullet_used->bullet_main->_x, pGet_AlienBullet_used->bullet_main->_y, pGet_AlienBullet_used->bullet_main->MAX_X, pGet_AlienBullet_used->bullet_main->MAX_Y, &pGet_AlienBullet_used->bullet_main->HurtMainRole, &mainrole_ring->_defenceBallNUM);//���� main role�O�_�Q�l�u����			

				//�Q�ˮ`��L�Ī��A�p��ɶ�
				if (pGet_AlienBullet_used->bullet_main->HurtMainRole) {
					timer_canHurtMainRole = 0.0f;
					mainrole->SetAlpha(0.6); //�L�Ī��A���b�z��
					mainrole_ring->SetAlpha(0.6); //�L�Ī��A���b�z��
				}
			}
			else if (pGet_AlienBullet_used->isSAlien_bullet == false && pGet_AlienBullet_used->isMAlien_bullet == true) //��MAlien bullet
			{
				pGet_AlienBullet_used->bullet_MAlien->AutoTranslate_Bullet(); //�n��
				mainrole->AutoCheckHurt_MainRole(pGet_AlienBullet_used->bullet_MAlien->_x, pGet_AlienBullet_used->bullet_MAlien->_y, pGet_AlienBullet_used->bullet_MAlien->MAX_X, pGet_AlienBullet_used->bullet_MAlien->MAX_Y, &pGet_AlienBullet_used->bullet_MAlien->HurtMainRole, &mainrole_ring->_defenceBallNUM);//���� main role�O�_�Q�l�u����			

				//�Q�ˮ`��L�Ī��A�p��ɶ�
				if (pGet_AlienBullet_used->bullet_MAlien->HurtMainRole) {
					timer_canHurtMainRole = 0.0f;
					mainrole->SetAlpha(0.6); //�L�Ī��A���b�z��
					mainrole_ring->SetAlpha(0.6); //�L�Ī��A���b�z��
				}
			}
			

			

			pGet_AlienBullet_used = pGet_AlienBullet_used->link;

		}
		//�ˬdSmall Alien �l�u�O�_�W�L���İ�
		CheckBullet_Alien();
		
		
		//��smiddle Alien ��m
		for (int i = SAlien_space; i < SAlien_space + middle_alien; i++)
		{

			//�Yalien ���`�h���a�a�@��
			if (alien[i]->alife == false) { //alien���`
				PlayerTotalPoint++; //���a�@��
			}

			alien[i]->AutomaticMotion(mainrole->_x , mainrole->_y);
			
		}


		timer_onFrameMove = 0;
	}


	//��s�O�@����
	if (timer_canHurtMainRole >4.0 && mainrole->can_change_hurtMain ==false) { //�����|��L�Ī��A
		
		mainrole->can_change_hurtMain = true; //�i���s����
		mainrole->SetAlpha(1.0);
		mainrole_ring->SetAlpha(1.0); 

	}
	


	//�Y�`����F�Q���h��X����
	if (PlayerTotalPoint == 3)
	{
		middle_alien = 1; //�ù��Wmiddle alien �X�{���̤j�ƶq
		
	}

	//�Y�`����F�Q���h��XBOSS
	//else if (PlayerTotalPoint == 5)
	//{
	//	isBossOut = true; //�}�ҲĤG�ӼҦ� test


	//}

	
	
	GL_Display();
	
}





float timer_bullet = 0.0; //�ɶ��p�ɾ�
float BulletLaunchSecStart = 0.0; //�����l�u�o�g���ɶ� 
bool canLaunchBullet = true; //�O�_���\�o�g�l�u
bool clickLaunchBullet = false; //�O�_���U�o�g

bool mouse_down= GLUT_UP;
void onBulletLaunch(float delta) {

	
	timer_bullet += delta;
	if (clickLaunchBullet && canLaunchBullet && Bullet_Total_MainBullet_free > 0) {
		
		
		CreateBullet_Main();
		canLaunchBullet = false;
		
		BulletLaunchSecStart = timer_bullet;
		 
	}

	if (timer_bullet - BulletLaunchSecStart > 0.2f ) { //�C�j0.6��i�o�g�@�o�l�u
		
		canLaunchBullet = true;
		if(mouse_down == GLUT_UP){ 
			clickLaunchBullet = false; //�q���B�}�l�A���T�{�O�_���I���ƹ�

		}
		else if (mouse_down == GLUT_DOWN) { //����
			clickLaunchBullet = true; //�Y�������h�s��o�g
		}
		
		timer_bullet = BulletLaunchSecStart = 0.0f;
	}

}


float timer_AlienBulletLaunch = 0.0f;

//Alien�o�g�l�u
void onAlienBulletLaunch(float delta) {
	timer_AlienBulletLaunch += delta;

	if (timer_AlienBulletLaunch >= 1.0f && Bullet_Total_Alien_free >0) { //�C�j�@��o�g�@���l�u
	
		
		
		for (int i = 0; i < SAlien_space + middle_alien; i++) //�C�Ӥp�ǳ��ظm�@�Ӥl�u
		{
			if(i <  small_alien){ //SAlien �гy�l�u
				if (alien[i]->_y > -2.5 && alien[i]->_y < 2.5) {
					CreateBullet_Alien(alien[i] , 'S');
				}
			}

			else if(i < SAlien_space + middle_alien){ //MAlien �гy�l�u
				if (alien[i]->_y > -2.5 && alien[i]->_y < 2.5) {
				
					CreateBullet_Alien(alien[i], 'M');
				
				
				}
				
			}
			
		}

		//BOSS�T���l�u
		for (boss_Mode1BulletCount = 0; boss_Mode1BulletCount < 3 && BOSS_alien > 0; boss_Mode1BulletCount++) //Boss�s�b�h�o�g�l�u
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


float mouse_displacement = 2.0f; //�ƹ��첾�q

void win_PassiveMotion(int x , int y) { //�ηƹ��ޱ���ĥ

	//�p��첾�q

	mainrole->_x = mouse_displacement * (x - SCREENWIDTH_HALF) / (SCREENWIDTH_HALF) ;
	mainrole->_y = -mouse_displacement * (y - SCREENHEIGHT_HALF) / (SCREENHEIGHT_HALF);
	
	//set main role matrix
	mainrole->mxTran_Main = Translate(mainrole->_x, mainrole->_y,0);
	mainrole->SetTRSMatrix(mainrole->mxTran_Main);

	//set ring matrix
	mainrole_ring->mxTran_Ring = Translate(mainrole_ring->_x, mainrole_ring->_y , 0); //���o������X�BY��T 
	mainrole_ring->SetTRSMatrix(mainrole->mxTran_Main * mainrole_ring->mxTran_Ring * mainrole_ring->mxAutoRotate_Ring ); //�]�w���������l���Y
	
}


void win_mousemotion( int x ,int y) {
	//�p��첾�q

	mainrole->_x = mouse_displacement * (x - SCREENWIDTH_HALF) / (SCREENWIDTH_HALF);
	mainrole->_y = -mouse_displacement * (y - SCREENHEIGHT_HALF) / (SCREENHEIGHT_HALF);

	//set main role matrix
	mainrole->mxTran_Main = Translate(mainrole->_x, mainrole->_y, 0);
	mainrole->SetTRSMatrix(mainrole->mxTran_Main);

	//set ring matrix
	mainrole_ring->mxTran_Ring = Translate(mainrole_ring->_x, mainrole_ring->_y, 0); //���o������X�BY��T 
	mainrole_ring->SetTRSMatrix(mainrole->mxTran_Main * mainrole_ring->mxTran_Ring * mainrole_ring->mxAutoRotate_Ring); //�]�w���������l���Y


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
	
	//���\�z���׳]�w
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	glewInit();  
    init();

	

	
	glutKeyboardFunc(win_keyFunc);//test _defenceBallNUM
	
	glutMotionFunc(win_mousemotion);//�ƹ��b���U����ɤ@�˾ޱ���ĥ
	glutPassiveMotionFunc(win_PassiveMotion); //�ηƹ��ޱ���ĥ

	glutMouseFunc(win_mouse); //�o�g�l�u
	

	glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	

    glutMainLoop();
    return 0;
}
