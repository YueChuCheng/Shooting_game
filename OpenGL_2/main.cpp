// Model-View matrix and Projection matrix
// Orthogonal or Orthographic projection
// Windows Events - Keyboard & Mouse
// Rotate Rectangle

#include "header/Angel.h"
#include "Characters/mainrole.h"
#include "Characters/MainRole_Ring.h"


#define SPACE_KEY 32

//螢幕大小define
#define SCREENWIDTH 360
#define SCREENHEIGHT 640
#define SCREENWIDTH_HALF (SCREENWIDTH/2.0)
#define SCREENHEIGHT_HALF (SCREENHEIGHT/2.0)



// 必須在 glewInit(); 執行完後,在執行物件實體的取得
MainRole *mainrole;	// 宣告 指標物件，結束時記得釋放
MainRole_Ring *mainrole_ring;	// 宣告 指標物件，結束時記得釋放


// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;


//矩陣
mat4 mxAutoRotate_ring;
mat4 mxTran;
mat4 maTran_Ring;

// 函式的原型宣告
void IdleProcess();
void CreateGameObject();



void init( void )
{

    g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

	CreateGameObject();


    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
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

	glutSwapBuffers();	// 交換 Frame Buffer
}

//----------------------------------------------------------------------------

//自動旋轉



void AutomaticRotation() {

	mxAutoRotate_ring = RotateZ(mainrole_ring->_rotate+=0.1);
	
	//rotate 需要做校正 
	mxAutoRotate_ring._m[0] *=  (6.5 / 10.0);
	mxAutoRotate_ring._m[1] *= (360.0 / 640.0) * (6.5 / 10.0);

	mainrole_ring->SetTRSMatrix(mxTran * mxAutoRotate_ring * maTran_Ring);

}



void onFrameMove(float delta)
{
	/*if( _bAutoRotation ) AutomaticRotation();
	GL_Display();*/
	AutomaticRotation();
	GL_Display();
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
	mxTran = Translate(mainrole->_x, mainrole->_y,0);

	maTran_Ring = Translate(mainrole_ring->_x, mainrole_ring->_y, 0); //取得圓環的X、Y資訊
	
	mainrole->SetTRSMatrix(mxTran);

	mxTran = Translate(mainrole->_x, mainrole->_y-0.05, 0);
	mainrole_ring->SetTRSMatrix(mxTran * mxAutoRotate_ring * maTran_Ring); //設定圓環的父子關係

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

	
	glutPassiveMotionFunc(win_PassiveMotion); //用滑鼠操控船艦

	glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	
    glutMainLoop();
    return 0;
}
