#include "Alien.h"

Middle_Alien::~Middle_Alien()
{


}


Middle_Alien::Middle_Alien()
{

	_Points[0] = vec4(-0.5, 0.5, 0.0, 1.0);
	_Points[1] = vec4(-0.5, -0.5, 0.0, 1.0);
	_Points[2] = vec4(0.5, -0.5, 0.0, 1.0);
	_Points[3] = vec4(-0.5, 0.5, 0.0, 1.0);
	_Points[4] = vec4(0.5, -0.5, 0.0, 1.0);
	_Points[5] = vec4(0.5, 0.5, 0.0, 1.0);


	for (int i = 0; i < Alien_Point_NUM; i++)
	{
		_Colors[i] = vec4(1.0, 0.0, 0.0, 1.0);
	}





	//校正比例 於跟隨Main Role 時一同做旋轉
	/*for (int i = 0; i < Alien_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (4.5 / 10.0);
		_Points[i].y = _Points[i].y * (360.0 / 640.0) * (4.5 / 10.0) ;

	}*/


	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}





void Middle_Alien::Draw()
{
	glUseProgram(_Program);
	glBindVertexArray(_VAO);
	if (_bUpdateMV) {
		_mxMVFinal = _mxView * _mxTRS;
		_bUpdateMV = false;
	}
	glUniformMatrix4fv(_ModelView, 1, GL_TRUE, _mxMVFinal);

	//沒有一直轉換視角則不須判斷Proj是否改變
	/*if (_bUpdateProj) {
		glUniformMatrix4fv(_Projection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}*/


	glDrawArrays(GL_TRIANGLES, 0, Alien_Point_NUM);

}




//mainrole Update



void Middle_Alien::DrawW()
{
	glBindVertexArray(_VAO);

	if (_bUpdateMV) {
		_mxMVFinal = _mxView * _mxTRS;
		_bUpdateMV = false;
	}

	glUniformMatrix4fv(_ModelView, 1, GL_TRUE, _mxMVFinal);
	if (_bUpdateProj) {
		glUniformMatrix4fv(_Projection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, Alien_Point_NUM);
}


void Middle_Alien::AutomaticMotion(GLfloat MainRole_x, GLfloat MainRole_y) {

	float dis_x = 0; //相差多少寬
	float dis_y = 0; //相差多少高
	
	dis_x =MainRole_x  - _x;
	dis_y =MainRole_y  - _y;

	//printf("%f\n" , atan(dis_y / dis_x));

	mxRotate_Alien =  RotateZ(atan(dis_x /dis_y) * -50.0f);


	mxRotate_Alien._m[0] *= (4.5 / 10.0);
	mxRotate_Alien._m[1] *= (360.0 / 640.0) * (4.5 / 10.0);

	SetTRSMatrix(mxTran_Alien * mxRotate_Alien );
	
};



void Middle_Alien::AutomaticFire(mat4 Alien_mxTran) {

}

void Middle_Alien::AutoCheckHurtDie(GLfloat Bullet_x, GLfloat Bullet_y, float MAX_X, float MAX_Y, bool* HurtAlien) {

}