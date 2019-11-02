// Model-View matrix and Projection matrix
// Orthogonal or Orthographic projection
// Windows Events - Keyboard & Mouse
// Rotate Rectangle

#include "header/Angel.h"
#include "Characters/mainrole.h"
#include "Characters/MainRole_Ring.h"


#define SPACE_KEY 32

//�ù��j�pdefine
#define SCREENWIDTH 360
#define SCREENHEIGHT 640
#define SCREENWIDTH_HALF (SCREENWIDTH/2.0)
#define SCREENHEIGHT_HALF (SCREENHEIGHT/2.0)



// �����b glewInit(); ���槹��,�b���檫����骺���o
MainRole *mainrole;	// �ŧi ���Ъ���A�����ɰO�o����
MainRole_Ring *mainrole_ring;	// �ŧi ���Ъ���A�����ɰO�o����


// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;


//�x�}
mat4 mxAutoRotate_Ring;
mat4 mxTran_Main;
mat4 maTran_Ring;

// �禡���쫬�ŧi
void IdleProcess();
void CreateGameObject();



void init( void )
{

    g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

	CreateGameObject();


    glClearColor( 0.9882, 0.6718, 0.6445, 1.0 ); // black background
}



void CreateGameObject() {

	mainrole = new MainRole;
	mainrole->SetShader(g_mxModelView, g_mxProjection);

	mainrole_ring = new MainRole_Ring;
	mainrole_ring->SetShader(g_mxModelView, g_mxProjection);
}




void GL_Display( void )
{
    glClear( GL_COLOR_BUFFER_BIT ); // clear the window
	mainrole->Draw();
	mainrole_ring->Draw();

	glutSwapBuffers();	// �洫 Frame Buffer
}

//----------------------------------------------------------------------------

//�۰ʱ���



void AutomaticRotation() {

	//����׷���
	if (mainrole_ring->_rotate>360) {
		mainrole_ring->_rotate -= 360;  
	}
	
	
	mxAutoRotate_Ring = RotateZ(mainrole_ring->_rotate+=0.1);
	
	//rotate �ݭn���ե� 
	mxAutoRotate_Ring._m[0] *=  (6.5 / 10.0);
	mxAutoRotate_Ring._m[1] *= (360.0 / 640.0) * (6.5 / 10.0);

	mainrole_ring->SetTRSMatrix(mxTran_Main * maTran_Ring * mxAutoRotate_Ring);

}



float timer_autoRotate = 0; //rotation's timer
void onFrameMove(float delta)
{
	timer_autoRotate += delta;
	if (timer_autoRotate >1.0/3000.0) { //�C1/5000��s�@��
		AutomaticRotation();
		timer_autoRotate = 0;
	}
	
	GL_Display();
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
	mxTran_Main = Translate(mainrole->_x, mainrole->_y,0);
	mainrole->SetTRSMatrix(mxTran_Main);

	//set ring matrix
	maTran_Ring = Translate(mainrole_ring->_x, mainrole_ring->_y , 0); //���o������X�BY��T 
	mainrole_ring->SetTRSMatrix(mxTran_Main * maTran_Ring * mxAutoRotate_Ring ); //�]�w���������l���Y

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

	//test _defenceBallNUM
	glutKeyboardFunc(win_keyFunc);
	
	
	glutPassiveMotionFunc(win_PassiveMotion); //�ηƹ��ޱ���ĥ
	glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	
    glutMainLoop();
    return 0;
}
