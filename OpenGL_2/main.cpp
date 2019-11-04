#include <math.h>
#include <time.h>
#include "header/Angel.h"
#include "Characters/mainrole.h"
#include "Characters/MainRole_Ring.h"
#include "Background/Cloud.h"
#include "Weapon/Bullet_Main.h"

#define SPACE_KEY 32

//�ù��j�pdefine
#define SCREENWIDTH 360
#define SCREENHEIGHT 640
#define SCREENWIDTH_HALF (SCREENWIDTH/2.0)
#define SCREENHEIGHT_HALF (SCREENHEIGHT/2.0)



// �����b glewInit(); ���槹��,�b���檫����骺���o
MainRole *mainrole;	// �ŧi ���Ъ���A�����ɰO�o����
MainRole_Ring *mainrole_ring;	// �ŧi ���Ъ���A�����ɰO�o����
Cloud* cloud[6];
Bullet_Main* bullet_main;


// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;


// �禡���쫬�ŧi
void IdleProcess();
void CreateGameObject();
void CheckBullet();

//�l�u�ŧi
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

	glutSwapBuffers();	// �洫 Frame Buffer
}




void CreateBullet_Main() { 

	if( Bullet_Total == 0){ //�Y�Ĥ@���l�u
		
		if ((pHead_bullet = (Bullet_PNODE)malloc(sizeof(Bullet_NODE))) == NULL) { //���\���o�Ŷ�
			printf("�O����Ŷ�����\n");
			exit(0);
		
		}
		

		//�]�wBullet ���e

		pHead_bullet->bullet_main = new Bullet_Main;
		pHead_bullet->bullet_main->SetShader(g_mxModelView, g_mxProjection);
		
		//�ƻsmainrole ����T
		pHead_bullet->bullet_main ->_x = mainrole->_x;
		pHead_bullet->bullet_main->_y = mainrole->_y;
		
		pHead_bullet->bullet_main->BulletTrans = Translate(pHead_bullet->bullet_main->_x, pHead_bullet->bullet_main->_y, 0.0);

		pHead_bullet->bullet_main->SetTRSMatrix(pHead_bullet->bullet_main->BulletTrans);

		pHead_bullet->link = NULL;
		pTail_bullet = pHead_bullet;

		Bullet_Total++;

	}

	else if (Bullet_Total>0) { //�Y�����Ĥ@���l�u

		if ((pGet_bullet = (Bullet_PNODE)malloc(sizeof(Bullet_NODE))) == NULL) { //���\���o�Ŷ�
			printf("�O����Ŷ�����\n");
			exit(0);

		}

	
		//�]�wBullet���e

		pGet_bullet->bullet_main = new Bullet_Main;
		pGet_bullet->bullet_main->SetShader(g_mxModelView, g_mxProjection);

		//�ƻsmainrole ����T
		pGet_bullet->bullet_main->_x = mainrole->_x;
		pGet_bullet->bullet_main->_y = mainrole->_y;


		pGet_bullet->bullet_main->BulletTrans = Translate(pGet_bullet->bullet_main->_x, pGet_bullet->bullet_main->_y, 0.0);

		pGet_bullet->bullet_main->SetTRSMatrix(pGet_bullet->bullet_main->BulletTrans);
		pGet_bullet->link = NULL;

		pGet_bullet->bullet_main->Draw();


		pTail_bullet->link = pGet_bullet; //�N�e�@�Ӹ`�I�P�s���`�I�s��
		pTail_bullet = pGet_bullet; //�]�w���ڸ`�I���s�����Ŷ�
		
		Bullet_Total++;
	}

	

}

//----------------------------------------------------------------------------

float bullet_main_y;
Bullet_PNODE one, two, three;

//�ˬd�l�u�O�_�W�L���Ľd��, �Y�W�L�h�s���n�e��`�I�A��delete
void CheckBullet() {
	
	pGet_Check_bullet = pHead_bullet;

	

	for (int i = 0; i < Bullet_Total; i++)
	{

		bullet_main_y = pGet_Check_bullet->bullet_main->_y;

		if (bullet_main_y > 2.0) {
			
			//�Y�R�����O�Ĥ@�Ӹ`�I�h�� pHead����m
			if (pGet_Check_bullet == pHead_bullet) {
				pHead_bullet = pHead_bullet->link;
				
			}

			//�Y�R�����O�̫�@�Ӹ`�I�h�� pTail����m
			else if (pGet_Check_bullet == pTail_bullet) {

				pTail_bullet = pGet_Last_Draw_bullet;
				pTail_bullet->link = NULL;

			}

			//�Y�����Y�]���������`�I�h�s���n�Y����m
			else {
			
				pGet_Last_Draw_bullet->link = pGet_Check_bullet->link; //�e�@����link�A�s����U�@�Ӹ`�I���_�Y
			}
			
			

			
			
			free(pGet_Check_bullet); //�R���`�I
			
			Bullet_Total--;

			break; //�Y���R���`�I�h���X�j��]���`�I�n���s�p��
		
		}

		pGet_Last_Draw_bullet = pGet_Check_bullet; //����e�@����pGet �H�K���n�ɦ��^�Ŷ�
		pGet_Check_bullet = pGet_Check_bullet->link;


	}

	/*while (pGet_Check_bullet!=NULL)
	{

		bullet_main_y = pGet_Check_bullet->bullet_main->_y;

		if (bullet_main_y > 2.0) {

			//�Y�R�����O�Ĥ@�Ӹ`�I�h�� pHead����m
			if (pHead_bullet == pGet_Check_bullet) {
				pHead_bullet = pHead_bullet->link;

			}

			//�Y�R�����O�̫�@�Ӹ`�I�h�� pTail����m
			else if (pTail_bullet == pGet_Check_bullet) {

				pTail_bullet = pGet_Last_Draw_bullet;
				pTail_bullet->link = NULL;

			}



			pGet_Last_Draw_bullet->link = pGet_Check_bullet->link; //�e�@����link�A�s����U�@�Ӹ`�I���_�Y



			free(pGet_Check_bullet); //�R���`�I

			Bullet_Total--;

			break; //�Y���R���`�I�h���X�j��]���`�I�n���s�p��

		}

		pGet_Last_Draw_bullet = pGet_Check_bullet; //����e�@����pGet �H�K���n�ɦ��^�Ŷ�
		pGet_Check_bullet = pGet_Check_bullet->link;


	}
	*/


	
}


//float test_i = 0; //���լO�_���T��^���O����

float timer_onFrameMove = 0; //rotation's timer

void onFrameMove(float delta)
{

	

	timer_onFrameMove += delta;
	if (timer_onFrameMove > 1.0 / 1000.0) { //�C1/1000��s�@��
		
		//test �O�_���^���O����
		/*if (pHead_bullet == NULL) {
			printf("%f\n", test_i);
			test_i++;
		}*/
		
		mainrole_ring->AutomaticRotation( mainrole->mxTran_Main );//�P���۰ʿ��� �ǤJ���h

		for (int i = 0; i < 6; i++)
		{
			cloud[i]->AutoTranslate_Background();
		}

		
		//��s�l�u���u 
		pGet_Draw_bullet = pHead_bullet;
		for (int i = 0; i < Bullet_Total; i++)
		{
			pGet_Draw_bullet->bullet_main->AutoTranslate_Bullet();
			pGet_Draw_bullet = pGet_Draw_bullet->link;


		}

		//�ˬd�O�_���l�u�W�L���İ�
		CheckBullet();
		
		timer_onFrameMove = 0;
	}
	
	GL_Display();
	
}


float timer_bullet = 0.0; //�ɶ��p�ɾ�
float BulletLaunchSecStart = 0.0; //�����l�u�o�g���ɶ� 
bool canLaunchBullet = true; //�O�_���\�o�g�l�u
bool clickLaunchBullet = false; //�O�_���U�o�g

bool mouse_down= GLUT_UP;
void onBulletLaunch(float delta) {

	timer_bullet += delta;
	if (clickLaunchBullet && canLaunchBullet) {
		
		CreateBullet_Main();
		canLaunchBullet = false;
		
		BulletLaunchSecStart = timer_bullet;
		 
	}

	if (timer_bullet - BulletLaunchSecStart > 0.1f ) { //�C�j0.6��i�o�g�@�o�l�u
		
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
	
	glutMotionFunc(win_mousemotion);//�ƹ��b���U����ɤ@�˾ޱ���ĥ
	glutPassiveMotionFunc(win_PassiveMotion); //�ηƹ��ޱ���ĥ

	glutMouseFunc(win_mouse); //�o�g�l�u
	

	glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	

    glutMainLoop();
    return 0;
}
