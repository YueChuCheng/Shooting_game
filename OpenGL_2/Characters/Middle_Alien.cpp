#include "Alien.h"
extern bool isBossOut;
extern float SMAlien_speed;
extern void CreateSmoke(float _x, float _y);

Middle_Alien::~Middle_Alien()
{


}


Middle_Alien::Middle_Alien()
{
	for (int i = (MAlien_circle * 0); i < (MAlien_circle * 1); i++)
	{
		float x = 0.18f * cosf(2.0f * M_PI * i / MAlien_circle);
		float y = 0.45f * sinf(2.0f * M_PI * i / MAlien_circle); 

		_Points[i] = vec4(x * cosf(0.125 * M_PI) - y * sinf(0.125 * M_PI) + 0.76f, x * sinf(0.125 * M_PI) + y * cosf(0.125 * M_PI) - 0.25f, 0.0f, 1.0f);

		
	}

	for (int i = (MAlien_circle * 0); i < (MAlien_circle * 1); i++)
	{
		_Colors[i] = vec4(0.5625, 0.6953, 0.2656, 1.0);
	}




	for (int i = (MAlien_circle * 1); i < (MAlien_circle * 2); i++)
	{
		float x = 0.18f * cosf(2.0f * M_PI * i / MAlien_circle);
		float y = 0.45f * sinf(2.0f * M_PI * i / MAlien_circle);

		_Points[i] = vec4(x * cosf( -0.125 * M_PI) - y * sinf( -0.125 * M_PI) - 0.76f, x * sinf( -0.125 * M_PI) + y * cosf( -0.125 * M_PI) - 0.25f, 0.0f, 1.0f);


	}

	for (int i = (MAlien_circle * 1); i < (MAlien_circle * 2); i++)
	{
		_Colors[i] = vec4(0.5625, 0.6953, 0.2656, 1.0);
	}





	for (int i = (MAlien_circle * 2); i < (MAlien_circle * 3); i++)
	{
		_Points[i] = vec4(0.75f * cosf(2.0f * M_PI * i / MAlien_circle), 0.67f * sinf(2.0f * M_PI * i / MAlien_circle), 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 2); i < (MAlien_circle * 3); i++)
	{
		_Colors[i] = vec4(0.6679, 0.8046, 0.3046, 1.0);
	}




	for (int i = (MAlien_circle * 3); i < (MAlien_circle * 4); i++)
	{
		_Points[i] = vec4(0.28f * cosf(2.0f * M_PI * i / MAlien_circle), 0.28f * sinf(2.0f * M_PI * i / MAlien_circle) + 0.2f, 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 3); i < (MAlien_circle * 4); i++)
	{
		_Colors[i] = vec4(0.99f, 0.99f, 0.99f, 1.0);
	}




	for (int i = (MAlien_circle * 4); i < (MAlien_circle * 5); i++)
	{
		_Points[i] = vec4(0.2f * cosf(2.0f * M_PI * i / MAlien_circle) - 0.28f, 0.2f * sinf(2.0f * M_PI * i / MAlien_circle) - 0.3f, 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 4); i < (MAlien_circle * 5); i++)
	{
		_Colors[i] = vec4(0.99f, 0.99f, 0.99f, 1.0);
	}


	for (int i = (MAlien_circle * 5); i < (MAlien_circle * 6); i++)
	{
		_Points[i] = vec4(0.2f * cosf(2.0f * M_PI * i / MAlien_circle) + 0.28f, 0.2f * sinf(2.0f * M_PI * i / MAlien_circle) - 0.3f, 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 5); i < (MAlien_circle * 6); i++)
	{
		_Colors[i] = vec4(0.99f, 0.99f, 0.99f, 1.0);
	}

	for (int i = (MAlien_circle * 6); i < (MAlien_circle * 7); i++)
	{
		_Points[i] = vec4(0.12f * cosf(2.0f * M_PI * i / MAlien_circle) + 0.28f, 0.12f * sinf(2.0f * M_PI * i / MAlien_circle) - 0.3f, 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 6); i < (MAlien_circle * 7); i++)
	{
		_Colors[i] = vec4(0.5742, 0.3593f, 0.5234f, 1.0);
	}




	for (int i = (MAlien_circle * 7); i < (MAlien_circle * 8); i++)
	{
		_Points[i] = vec4(0.05f * cosf(2.0f * M_PI * i / MAlien_circle) + 0.28f, 0.05f * sinf(2.0f * M_PI * i / MAlien_circle) - 0.3f, 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 7); i < (MAlien_circle * 8); i++)
	{
		_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0);
	}



	for (int i = (MAlien_circle * 8); i < (MAlien_circle * 9); i++)
	{
		_Points[i] = vec4(0.12f * cosf(2.0f * M_PI * i / MAlien_circle) - 0.28f, 0.12f * sinf(2.0f * M_PI * i / MAlien_circle) - 0.3f, 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 8); i < (MAlien_circle * 9); i++)
	{
		_Colors[i] = vec4(0.5742, 0.3593f, 0.5234f, 1.0);
	}




	for (int i = (MAlien_circle * 9); i < (MAlien_circle * 10); i++)
	{
		_Points[i] = vec4(0.05f * cosf(2.0f * M_PI * i / MAlien_circle) - 0.28f, 0.05f * sinf(2.0f * M_PI * i / MAlien_circle) - 0.3f, 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 9); i < (MAlien_circle * 10); i++)
	{
		_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0);
	}



	for (int i = (MAlien_circle * 10); i < (MAlien_circle * 11); i++)
	{
		_Points[i] = vec4(0.13f * cosf(2.0f * M_PI * i / MAlien_circle) , 0.13f * sinf(2.0f * M_PI * i / MAlien_circle) + 0.15f, 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 10); i < (MAlien_circle * 11); i++)
	{
		_Colors[i] = vec4(0.5742, 0.3593f, 0.5234f, 1.0);
	}




	for (int i = (MAlien_circle * 11); i < (MAlien_circle * 12); i++)
	{
		_Points[i] = vec4(0.08f * cosf(2.0f * M_PI * i / MAlien_circle) , 0.08f * sinf(2.0f * M_PI * i / MAlien_circle) + 0.15f, 0.0f, 1.0f);

	}

	for (int i = (MAlien_circle * 11); i < (MAlien_circle * 12); i++)
	{
		_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0);
	}




	//test
	/*for (int i = 0; i < MAlien_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (4.5 / 10.0);
		_Points[i].y = _Points[i].y * (360.0 / 640.0) * (4.5 / 10.0);

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


	glDrawArrays(GL_TRIANGLE_FAN, 0, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 2, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 3, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 4, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 5, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 6, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 7, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 8, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 9, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 10, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 11, MAlien_circle);
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
	glDrawArrays(GL_TRIANGLE_FAN, 0, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 2, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 3, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 4, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 5, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 6, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 7, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 8, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 9, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 10, MAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, MAlien_circle * 11, MAlien_circle);
}


void Middle_Alien::AutomaticMotion(GLfloat MainRole_x, GLfloat MainRole_y) {

	readyToDraw = true;
	if (alife == false) //若此Alien已死亡
	{
		if (used) {
			CreateSmoke(this->_x, this->_y);

		}

		if (!isBossOut) {

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



	float rotate ;  //旋轉角度
	float fix_angle = 0; //修正角度

	dis_x =MainRole_x  - _x;
	dis_y =MainRole_y  - _y;
	
	if ((dis_x > 0.0 && dis_y >= 0.0)  || (dis_x > 0.0 && dis_y <= 0.0)) { //第一、四象限
		fix_angle = 90.0f;
	}
	else if ((dis_x <= 0.0 && dis_y < 0.0) || (dis_x < 0.0 && dis_y >= 0.0))  //第三、二象限
	{
		fix_angle = 270.0f;
	}



	rotate = atan(dis_y / dis_x) * 180 / M_PI + fix_angle;
	

	mxRotate_Alien =  RotateZ(rotate  );

	


	mxRotate_Alien._m[0] *= (4.8 / 10.0);
	mxRotate_Alien._m[1] *= (360.0 / 640.0) * (4.8 / 10.0);

	SetTRSMatrix(mxTran_Alien * mxRotate_Alien );

	
	if (if_first_alien) {

		_x = (double)(rand() % 4000 - 2000.0) / 1000.0;
		_y = (double)(rand() % 2000 + 2000.0) / 1000.0;
		mxTran_Alien = Translate(_x, _y, 0.0);
		SetTRSMatrix(mxTran_Alien * mxRotate_Alien);

		if_first_alien = false;


	}

	else {
		_y -= SMAlien_speed;
		mxTran_Alien = Translate(_x, _y, 0.0);
		SetTRSMatrix(mxTran_Alien * mxRotate_Alien);

		if (_y < -2.0) { //若超過顯示範圍則重頭顯示

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

	
	
};



void Middle_Alien::AutomaticFire(mat4 Alien_mxTran) {

}

void Middle_Alien::AutoCheckHurtDie(GLfloat Bullet_x, GLfloat Bullet_y, float MAX_X, float MAX_Y, bool* HurtAlien) {
	

	if (_x - this->MAX_X <= Bullet_x - MAX_X && _x + this->MAX_X >= Bullet_x + MAX_X && _y + this->MAX_Y >= Bullet_y + MAX_Y && _y - this->MAX_Y <= Bullet_y - MAX_Y) { //判斷是否在中彈的範圍內

			*HurtAlien = true; //設定該子彈有打到Alien
			
			Blood--;


		}



		if (Blood <= 0)
		{
			alife = false;
		}

	
}


void Middle_Alien::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
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

void Middle_Alien::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}


void Middle_Alien::CreateBufferObject()
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



//偵測super 攻擊
void Middle_Alien::CheckSuperHurt(GLfloat Super_x, GLfloat Super_y, float MAX_X, float MAX_Y) {

	if (_x - this->MAX_X + 0.3f >= Super_x - MAX_X  && _x + this->MAX_X - 0.3f <= Super_x + MAX_X && _y + this->MAX_Y  <= Super_y + MAX_Y  && _y - this->MAX_Y  >= Super_y - MAX_Y )//偵測是否位於攻擊範圍 且是否為可攻擊狀態
	{

		alife = false;

	}


}