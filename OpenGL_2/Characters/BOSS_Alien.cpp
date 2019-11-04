#include "Alien.h"

BOSS_Alien::~BOSS_Alien()
{


}


BOSS_Alien::BOSS_Alien()
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





	//校正比例
	for (int i = 0; i < Alien_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (6.5 / 10.0);
		_Points[i].y = _Points[i].y * (360.0 / 640.0) * (6.5 / 10.0) -1.0f ;

	}


	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}





void BOSS_Alien::Draw()
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



void BOSS_Alien::DrawW()
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


void BOSS_Alien::AutomaticMotion() {

}


void BOSS_Alien::AutomaticFire(mat4 Alien_mxTran) {

}

void BOSS_Alien::AutoCheckHurtDie() {

}