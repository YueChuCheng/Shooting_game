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
	

	


	//校正比例
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

	//沒有一直轉換視角則不須判斷Proj是否改變
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

		if (_y < -2.0 ) { //若超過顯示範圍則重頭顯示
		
			if_first_alien = true;

		}
		
	
	}

	if (alife==false) //若此Alien已死亡
	{
		if_first_alien = true;
		Blood = Blood_original; //血量重新計算
		alife = true;//重生
		
	}

	 


}


void Small_Alien::AutomaticFire(mat4 Alien_mxTran) {
	
}



void Small_Alien::AutoCheckHurtDie(GLfloat Bullet_x , GLfloat Bullet_y, float MAX_X, float MAX_Y ,  bool *HurtAlien) {

		
		if (_x- this->MAX_X <= Bullet_x- MAX_X && _x + this->MAX_X >= Bullet_x + MAX_X && _y + this->MAX_Y >= Bullet_y + MAX_Y && _y - this->MAX_Y <= Bullet_y - MAX_Y)  { //判斷是否在中彈的範圍內

			*HurtAlien = true; //設定該子彈有打到Alien
			Blood--;
			

		}

	

		if (Blood<=0)
		{
			alife = false;
		}

}