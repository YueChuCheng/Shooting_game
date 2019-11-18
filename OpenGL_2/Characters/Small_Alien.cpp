#include "Alien.h"

extern bool isBossOut;
extern float SMAlien_speed;


Small_Alien::~Small_Alien()
{

	
}


Small_Alien::Small_Alien()
{

	for (int i = 0; i < SAlien_circle; i++)
	{
		float x = 0.2f * cosf(2.0f * M_PI * i / SAlien_circle);
		float y = 0.35f * sinf(2.0f * M_PI * i / SAlien_circle);

		_Points[i] = vec4(x * cosf(-0.125 * M_PI) - y * sinf(-0.125 * M_PI) + 0.38f, x * sinf(-0.125 * M_PI) + y * cosf(-0.125 * M_PI) + 0.65f, 0.0f, 1.0f);


	}


	for (int i = 0; i < SAlien_circle; i++)
	{
		_Colors[i] = vec4(0.4179, 0.6953, 0.7812, 1.0);
	}
	


	for (int i = SAlien_circle; i < (SAlien_circle * 2 ); i++)
	{
		float x = 0.2f * cosf(2.0f * M_PI * i / SAlien_circle);
		float y = 0.35f * sinf(2.0f * M_PI * i / SAlien_circle);

		_Points[i] = vec4(x * cosf(0.125 * M_PI) - y * sinf(0.125 * M_PI) - 0.38f, x * sinf(0.125 * M_PI) + y * cosf(0.125 * M_PI) + 0.65f, 0.0f, 1.0f);

	}

	for (int i = SAlien_circle; i < (SAlien_circle * 2); i++)
	{
		_Colors[i] = vec4(0.4179, 0.6953, 0.7812, 1.0);
	}




	for (int i = (SAlien_circle * 2); i < (SAlien_circle * 3); i++)
	{
		_Points[i] = vec4(0.75f * cosf(2.0f * M_PI * i / SAlien_circle), 0.67f * sinf(2.0f * M_PI * i / SAlien_circle), 0.0f, 1.0f);

	}

	for (int i = (SAlien_circle * 2); i < (SAlien_circle * 3); i++)
	{
		_Colors[i] = vec4(0.5234, 0.7773, 0.8554, 1.0);
	}


	for (int i = (SAlien_circle * 3); i < (SAlien_circle * 4); i++)
	{
		_Points[i] = vec4(0.4f * cosf(2.0f * M_PI * i / SAlien_circle), 0.4f * sinf(2.0f * M_PI * i / SAlien_circle) + 0.07f, 0.0f, 1.0f);

	}

	for (int i = (SAlien_circle * 3); i < (SAlien_circle * 4); i++)
	{
		_Colors[i] = vec4(0.9960, 0.9531, 0.8828, 1.0);
	}




	for (int i = (SAlien_circle * 4); i < (SAlien_circle * 5); i++)
	{
		_Points[i] = vec4(0.2f * cosf(2.0f * M_PI * i / SAlien_circle), 0.2f * sinf(2.0f * M_PI * i / SAlien_circle) + 0.07f, 0.0f, 1.0f);

	}

	for (int i = (SAlien_circle * 4); i < (SAlien_circle * 5); i++)
	{
		_Colors[i] = vec4(0.8867, 0.2929, 0.5156, 1.0);
	}





	for (int i = (SAlien_circle * 5); i < (SAlien_circle * 6); i++)
	{

		_Points[i] = vec4(0.1f * cosf(2.0f * M_PI * i / SAlien_circle), 0.1f * sinf(2.0f * M_PI * i / SAlien_circle) + 0.07f, 0.0f, 1.0f);

	}

	for (int i = (SAlien_circle * 5); i < (SAlien_circle * 6); i++)
	{
		_Colors[i] = vec4(0.4062, 0.2460, 0.3085, 1.0);
	}
	






	for (int i = (SAlien_circle * 6); i < (SAlien_circle * 7); i++)
	{

		_Points[i] = vec4(0.25f * cosf(2.0f * M_PI * i / SAlien_circle), 0.2f * sinf(2.0f * M_PI * i / SAlien_circle) - 0.4f, 0.0f, 1.0f);


	}

	for (int i = (SAlien_circle * 6); i < (SAlien_circle * 7); i++)
	{
		_Colors[i] = vec4(0.9687, 0.8203, 0.4960, 1.0);
	}


	//校正比例
	for (int i = 0; i < SAlien_Point_NUM; i++)
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


	glDrawArrays(GL_TRIANGLE_FAN, 0 , SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 2, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 3, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 4, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 5, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 6, SAlien_circle);
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
	glDrawArrays(GL_TRIANGLE_FAN, 0, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 2, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 3, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 4, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 5, SAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, SAlien_circle * 6, SAlien_circle);
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

		
		_y -= SMAlien_speed;
		
		mxTran_Alien = Translate(_x, _y, 0.0);
		SetTRSMatrix(mxTran_Alien);

		if (_y < -2.0 ) { //若超過顯示範圍 且 大BOSS未出來則重頭顯示
		
			if (!isBossOut)
			{
				if_first_alien = true;
				Blood = Blood_original; //血量重新計算

			}
			

			else if (isBossOut)
			{
				used = false;
				if_first_alien = false;
				alife = false;
			}

		}
		
	
	}

	if (alife==false ) //若此Alien已死亡 且 大BOSS未出來
	{
		if(!isBossOut){
		
			if_first_alien = true;
			Blood = Blood_original; //血量重新計算
			alife = true;//重生

		}
		
		else if (isBossOut)
		{
			used = false;
			if_first_alien = false;
			alife = false;
		}
		
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


void Small_Alien::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) _Program = InitShader("vsMainRole.glsl", "fsMainRole.glsl");
	else _Program = uiShaderHandle;

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(_Program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(_Program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(_Points)));

	_ModelView = glGetUniformLocation(_Program, "ModelView");
	_mxView = mxView;
	glUniformMatrix4fv(_ModelView, 1, GL_TRUE, _mxView);

	_Projection = glGetUniformLocation(_Program, "Projection");
	_mxProjection = mxProjection;
	glUniformMatrix4fv(_Projection, 1, GL_TRUE, _mxProjection);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Small_Alien::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}


void Small_Alien::CreateBufferObject()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// Create and initialize a buffer object

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_Points) + sizeof(_Colors), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_Points), _Points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
}