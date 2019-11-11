#include "Alien.h"

Small_Alien::~Small_Alien()
{

	
}


Small_Alien::Small_Alien()
{

	_Points[0] = vec4(-0.5, 0.5, 0.0, 1.0);
	_Points[1] = vec4(-0.5, -0.5, 0.0, 1.0);
	_Points[2] = vec4(0.5,-0.5, 0.0, 1.0);
	_Points[3] = vec4(-0.5, 0.5, 0.0, 1.0);
	_Points[4] = vec4(0.5, -0.5, 0.0, 1.0);
	_Points[5] = vec4(0.5, 0.5, 0.0, 1.0);


	for (int i = 0; i < Alien_Point_NUM; i++)
	{
		_Colors[i] = vec4(1.0, 0.0, 0.0, alphea);
	}
	

	


	//�ե����
	for (int i = 0; i < Alien_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (3.5 / 10.0);
		_Points[i].y = _Points[i].y * (360.0 / 640.0) * (3.5 / 10.0);

	}


	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}





void Small_Alien::Draw()
{
	glUseProgram(_Program);
	glBindVertexArray(_VAO);
	if (_bUpdateMV) {
		_mxMVFinal = _mxView * _mxTRS;
		_bUpdateMV = false;
	}
	glUniformMatrix4fv(_ModelView, 1, GL_TRUE, _mxMVFinal);

	//�S���@���ഫ�����h�����P�_Proj�O�_����
	/*if (_bUpdateProj) {
		glUniformMatrix4fv(_Projection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}*/


	glDrawArrays(GL_TRIANGLES, 0 , Alien_Point_NUM);

}




//mainrole Update



void Small_Alien::DrawW()
{
	glBindVertexArray( _VAO );

	if( _bUpdateMV ) {
		_mxMVFinal = _mxView*_mxTRS;
		_bUpdateMV = false;
	}

	glUniformMatrix4fv( _ModelView, 1, GL_TRUE, _mxMVFinal );
	if( _bUpdateProj ) {
		glUniformMatrix4fv( _Projection, 1, GL_TRUE, _mxProjection );
		_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, Alien_Point_NUM);
}



void Small_Alien::AutomaticMotion() {

	if (if_first_alien) {
		
		_x = (double)(rand() % 4000 - 2000.0) / 1000.0;
		_y = (double)(rand() % 2000 + 2000.0) / 1000.0;
		mxTran_Alien = Translate(_x, _y, 0.0);
		SetTRSMatrix(mxTran_Alien);

		if_first_alien = false;


	}

	else {
		_y -= 0.0025f;
		mxTran_Alien = Translate(_x, _y, 0.0);
		SetTRSMatrix(mxTran_Alien);

		if (_y < -2.0 ) { //�Y�W�L��ܽd��h���Y���
		
			if_first_alien = true;

		}
		
	
	}

	if (alife==false) //�Y��Alien�w���`
	{
		if_first_alien = true;
		Blood = Blood_original; //��q���s�p��
		alife = true;//����
		
	}

	 


}


void Small_Alien::AutomaticFire(mat4 Alien_mxTran) {
	
}



void Small_Alien::AutoCheckHurtDie(GLfloat Bullet_x , GLfloat Bullet_y, bool *HurtAlien) {

		
		if (_x- MAX_X <= Bullet_x- 0.1 && _x + MAX_X >= Bullet_x + 0.1 && _y + MAX_Y >= Bullet_y + 0.1 && _y - MAX_Y <= Bullet_y - 0.2)  { //�P�_�O�_�b���u���d��

			*HurtAlien = true; //�]�w�Ӥl�u������Alien
			Blood--;
			

		}

	

		if (Blood<=0)
		{
			alife = false;
		}

}