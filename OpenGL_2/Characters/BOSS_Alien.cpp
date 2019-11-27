#include "Alien.h"

extern int PlayerTotalPoint_BAlien;
extern short BOSSMode;
extern bool Game_Over;
extern void CreateSmoke(float _x, float _y);
BOSS_Alien::~BOSS_Alien()
{


}


BOSS_Alien::BOSS_Alien()
{

	


	//bottom_middle
	for (int i = 0; i < BAlien_circle; i++)
	{
		_Points[i] = vec4(0.2f * cosf(2.0f * M_PI * i / BAlien_circle), 0.15 * sinf(2.0f * M_PI * i / BAlien_circle) - 0.35f, 0.0f, 1.0f);


	}

	for (int i = 0; i < BAlien_circle; i++)
	{
		_Colors[i] = vec4(0.8398, 0.1718, 0.1406, 1.0);
	}
	

	//bottom_left
	for (int i = BAlien_circle; i < BAlien_circle * 2; i++)
	{
		_Points[i] = vec4(0.15f * cosf(2.0f * M_PI * i / BAlien_circle) - 0.4f, 0.1 * sinf(2.0f * M_PI * i / BAlien_circle) - 0.32f, 0.0f, 1.0f);

	}

	for (int i = BAlien_circle; i < BAlien_circle * 2; i++)
	{
		_Colors[i] = vec4(0.8398, 0.1718, 0.1406, 1.0);
	}



	//bottom_right
	for (int i = BAlien_circle * 2; i < BAlien_circle * 3; i++)
	{
		_Points[i] = vec4(0.15f * cosf(2.0f * M_PI * i / BAlien_circle) + 0.4f, 0.1 * sinf(2.0f * M_PI * i / BAlien_circle) - 0.32f, 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 2; i < BAlien_circle * 3; i++)
	{
		_Colors[i] = vec4(0.8398, 0.1718, 0.1406, 1.0);
	}




	//rectangle_left
	_Points[BAlien_circle * 3 + 0] = vec4(-0.8f , 0.0f , 0.0f, 1.0f);
	_Points[BAlien_circle * 3 + 1] = vec4(-0.8f , -0.5f, 0.0f, 1.0f);
	_Points[BAlien_circle * 3 + 2] = vec4(-0.6f , -0.5f, 0.0f, 1.0f);
	_Points[BAlien_circle * 3 + 3] = vec4(-0.6f, 0.0f, 0.0f, 1.0f);

	for (size_t i = 0; i < BAlien_rectangle; i++)
	{
		_Colors[BAlien_circle * 3 + i] = vec4(0.3828f, 0.6132f, 0.6445f, 1.0);
	}


	//rectangle_right
	_Points[BAlien_circle * 3 + BAlien_rectangle + 0] = vec4(0.8f, 0.0f, 0.0f, 1.0f);
	_Points[BAlien_circle * 3 + BAlien_rectangle + 1] = vec4(0.8f, -0.5f, 0.0f, 1.0f);
	_Points[BAlien_circle * 3 + BAlien_rectangle + 2] = vec4(0.6f, -0.5f, 0.0f, 1.0f);
	_Points[BAlien_circle * 3 + BAlien_rectangle + 3] = vec4(0.6f, 0.0f, 0.0f, 1.0f);

	for (size_t i = 0; i < BAlien_rectangle; i++)
	{
		_Colors[BAlien_circle * 3 + BAlien_rectangle + i] = vec4(0.3828f, 0.6132f, 0.6445f, 1.0);
	}




	//body
	for (int i = BAlien_circle * 3 + (BAlien_rectangle * 2); i < BAlien_circle * 4 + (BAlien_rectangle * 2); i++)
	{
		_Points[i] = vec4(0.85f * cosf(2.0f * M_PI * i / BAlien_circle), 0.37 * sinf(2.0f * M_PI * i / BAlien_circle), 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 3 + (BAlien_rectangle * 2); i < BAlien_circle * 4 + (BAlien_rectangle * 2); i++)
	{
		_Colors[i] = vec4(0.9492, 0.9726, 0.5, 1.0);
	}


	//rocket_left
	for (int i = BAlien_circle * 4 + (BAlien_rectangle * 2); i < BAlien_circle * 5 + (BAlien_rectangle * 2); i++)
	{
		_Points[i] = vec4(0.1 * cosf(2.0f * M_PI * i / BAlien_circle) - 0.7f, 0.1 * sinf(2.0f * M_PI * i / BAlien_circle) - 0.5f, 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 4 + (BAlien_rectangle * 2); i < BAlien_circle * 5 + (BAlien_rectangle * 2); i++)
	{
		_Colors[i] = vec4(0.0f, 1.0f, 0.0f, 1.0);
	}


	//rocket_right
	for (int i = BAlien_circle * 5 + (BAlien_rectangle * 2); i < BAlien_circle * 6 + (BAlien_rectangle * 2); i++)
	{
		_Points[i] = vec4(0.1 * cosf(2.0f * M_PI * i / BAlien_circle) + 0.7f, 0.1 * sinf(2.0f * M_PI * i / BAlien_circle) - 0.5f, 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 5 + (BAlien_rectangle * 2); i < BAlien_circle * 6 + (BAlien_rectangle * 2); i++)
	{
		_Colors[i] = vec4(0.0f, 1.0f, 0.0f, 1.0);
	}


	//head
	for (int i = BAlien_circle * 6 + (BAlien_rectangle * 2); i < BAlien_circle * 7 + (BAlien_rectangle * 2); i++)
	{
		_Points[i] = vec4(0.43 * cosf(2.0f * M_PI * i / BAlien_circle) , 0.35 * sinf(2.0f * M_PI * i / BAlien_circle) + 0.3f , 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 6 + (BAlien_rectangle * 2); i < BAlien_circle * 7 + (BAlien_rectangle * 2); i++)
	{
		_Colors[i] = vec4(0.8398, 0.1718, 0.1406, 1.0);
	}


	//Blush_left
	for (int i = BAlien_circle * 7 + (BAlien_rectangle * 2); i < BAlien_circle * 8 + (BAlien_rectangle * 2); i++)
	{
		_Points[i] = vec4(0.1 * cosf(2.0f * M_PI * i / BAlien_circle) - 0.4f , 0.13 * sinf(2.0f * M_PI * i / BAlien_circle) + 0.3f, 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 7 + (BAlien_rectangle * 2); i < BAlien_circle * 8 + (BAlien_rectangle * 2); i++)
	{
		_Colors[i] = vec4(0.9960f, 0.6875f, 0.7812f, 1.0);
	}


	//Blush_right
	for (int i = BAlien_circle * 8 + (BAlien_rectangle * 2); i < BAlien_circle * 9 + (BAlien_rectangle * 2); i++)
	{
		_Points[i] = vec4(0.1 * cosf(2.0f * M_PI * i / BAlien_circle) + 0.4f, 0.13 * sinf(2.0f * M_PI * i / BAlien_circle) + 0.3f, 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 8 + (BAlien_rectangle * 2); i < BAlien_circle * 9 + (BAlien_rectangle * 2); i++)
	{
		_Colors[i] = vec4(0.9960f, 0.6875f, 0.7812f, 1.0);
	}


	//mouse
	for (int i = BAlien_circle * 9 + (BAlien_rectangle * 2); i < BAlien_circle * 10 + (BAlien_rectangle * 2); i++)
	{
		_Points[i] = vec4(0.13 * cosf(2.0f * M_PI * i / BAlien_circle) - 0.04f , 0.18 * sinf(2.0f * M_PI * i / BAlien_circle) + 0.2f, 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 9 + (BAlien_rectangle * 2); i < BAlien_circle * 10 + (BAlien_rectangle * 2); i++)
	{
		_Colors[i] = vec4(0.9726f, 0.9726f, 0.0f, 1.0);
	}

	//mouse_inside


	_Points[BAlien_circle * 10 + (BAlien_rectangle * 2) + 0] = vec4(-0.17f, 0.2f, 0.0f, 1.0f);
	_Points[BAlien_circle * 10 + (BAlien_rectangle * 2) + 1] = vec4(-0.05f, 0.37f, 0.0f, 1.0f);
	_Points[BAlien_circle * 10 + (BAlien_rectangle * 2) + 2] = vec4(0.07f, 0.2f, 0.0f, 1.0f);
	_Points[BAlien_circle * 10 + (BAlien_rectangle * 2) + 3] = vec4(-0.05f, 0.02f, 0.0f, 1.0f);

	for (int i = BAlien_circle * 10 + (BAlien_rectangle * 2); i < BAlien_circle * 10 + (BAlien_rectangle * 3); i++)
	{
		_Colors[i] = vec4(0.9453f, 0.1132f, 0.1132f, 1.0);
	}


	//eyes_left
	for (int i = BAlien_circle * 10 + (BAlien_rectangle * 3); i < BAlien_circle * 11 + (BAlien_rectangle * 3); i++)
	{

		float x = 0.08 * cosf(2.0f * M_PI * i / BAlien_circle) ;
		float y = 0.05 * sinf(2.0f * M_PI * i / BAlien_circle) ;

		_Points[i] = vec4(x * cosf(-0.25 * M_PI) - y * sinf(-0.25 * M_PI) -0.25f, x * sinf(-0.25 * M_PI) + y * cosf(-0.25 * M_PI) + 0.45f, 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 10 + (BAlien_rectangle * 3); i < BAlien_circle * 11 + (BAlien_rectangle * 3); i++)
	{
		_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0);
	}



	//eyes_right
	for (int i = BAlien_circle * 11 + (BAlien_rectangle * 3); i < BAlien_circle * 12 + (BAlien_rectangle * 3); i++)
	{

		float x = 0.1 * cosf(2.0f * M_PI * i / BAlien_circle);
		float y = 0.05 * sinf(2.0f * M_PI * i / BAlien_circle);

		_Points[i] = vec4(x * cosf(0.15 * M_PI) - y * sinf(0.15 * M_PI) + 0.2f, x * sinf(0.15 * M_PI) + y * cosf(0.15 * M_PI) + 0.45f, 0.0f, 1.0f);

	}

	for (int i = BAlien_circle * 11 + (BAlien_rectangle * 3); i < BAlien_circle * 12 + (BAlien_rectangle * 3); i++)
	{
		_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0);
	}


	//hair_middle



	_Points[BAlien_circle * 12 + (BAlien_rectangle * 3) + 0] = vec4(0.0f, 0.8f, 0.0f, 1.0f);
	_Points[BAlien_circle * 12 + (BAlien_rectangle * 3) + 1] = vec4(0.0f, 0.6f, 0.0f, 1.0f);
	_Points[BAlien_circle * 12 + (BAlien_rectangle * 3) + 2] = vec4(-0.05f, 0.6f, 0.0f, 1.0f);
	_Points[BAlien_circle * 12 + (BAlien_rectangle * 3) + 3] = vec4(-0.05f, 0.8f, 0.0f, 1.0f);


	for (int i = BAlien_circle * 12 + (BAlien_rectangle * 3); i < BAlien_circle * 12 + (BAlien_rectangle * 4); i++)
	{
		_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0);
	}


	_Points[BAlien_circle * 12 + (BAlien_rectangle * 4) + 0] = vec4(0.12f, 0.8f, 0.0f, 1.0f);
	_Points[BAlien_circle * 12 + (BAlien_rectangle * 4) + 1] = vec4(0.0f, 0.65f, 0.0f, 1.0f);
	_Points[BAlien_circle * 12 + (BAlien_rectangle * 4) + 2] = vec4(-0.05f, 0.65f, 0.0f, 1.0f);
	_Points[BAlien_circle * 12 + (BAlien_rectangle * 4) + 3] = vec4(0.07f, 0.8f, 0.0f, 1.0f);


	for (int i = BAlien_circle * 12 + (BAlien_rectangle * 4); i < BAlien_circle * 12 + (BAlien_rectangle * 5); i++)
	{
		_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0);
	}


	_Points[BAlien_circle * 12 + (BAlien_rectangle * 5) + 0] = vec4(-0.12f, 0.8f, 0.0f, 1.0f);
	_Points[BAlien_circle * 12 + (BAlien_rectangle * 5) + 1] = vec4(0.0f, 0.65f, 0.0f, 1.0f);
	_Points[BAlien_circle * 12 + (BAlien_rectangle * 5) + 2] = vec4(-0.05f, 0.65f, 0.0f, 1.0f);
	_Points[BAlien_circle * 12 + (BAlien_rectangle * 5) + 3] = vec4(-0.17f, 0.8f, 0.0f, 1.0f);


	for (int i = BAlien_circle * 12 + (BAlien_rectangle * 5); i < BAlien_circle * 12 + (BAlien_rectangle * 6); i++)
	{
		_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0);
	}



	





	//校正比例
	for (int i = 0; i < BAlien_Point_NUM; i++)
	{
		
		_Points[i].y = _Points[i].y * (360.0 / 640.0);

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


	glDrawArrays(GL_TRIANGLE_FAN, 0, BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle, BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 2, BAlien_circle);
	
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 3 , BAlien_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 3 + BAlien_rectangle, BAlien_rectangle);

	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 3 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 4 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 5 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 6 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 7 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 8 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 9 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 10 + (BAlien_rectangle * 2), BAlien_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 10 + (BAlien_rectangle * 3), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 11 + (BAlien_rectangle * 3), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 12 + (BAlien_rectangle * 3), BAlien_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 12 + (BAlien_rectangle * 4), BAlien_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 12 + (BAlien_rectangle * 5), BAlien_rectangle);
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
	glDrawArrays(GL_TRIANGLE_FAN, 0, BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle, BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 2, BAlien_circle);

	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 3, BAlien_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 3 + BAlien_rectangle, BAlien_rectangle);

	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 3 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 4 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 5 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 6 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 7 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 8 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 9 + (BAlien_rectangle * 2), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 10 + (BAlien_rectangle * 2), BAlien_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 10 + (BAlien_rectangle * 3), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 11 + (BAlien_rectangle * 3), BAlien_circle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 12 + (BAlien_rectangle * 3), BAlien_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 12 + (BAlien_rectangle * 4), BAlien_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, BAlien_circle * 12 + (BAlien_rectangle * 5), BAlien_rectangle);

	
}


void BOSS_Alien::AutomaticMotion(float timer) {
	readyToDraw = true;
	
	if (timer < 2.0f) //在螢幕外
	{
		_y = 3.0f;
	}

	else if (timer < 5.0f)//在螢幕外
	{
		if (_y > 1.3f)
		{
			_y -= 0.0015f;
		}

		
	}

	else if(timer > 5.0f)
	{
		if (first_direction_x) {
			_x -= 0.0015;
		}

		else
		{
			_x += 0.0015;
		}


		if (first_direction_y) {
			_y -= 0.0005;
		}

		else
		{
			_y += 0.0005;
		}


		if (_x > 1.3f || _x < -1.3f)
		{
			first_direction_x = !first_direction_x;
		}

		if (_y > 1.3f || _y < 1.0f)
		{
			first_direction_y = !first_direction_y;
		}

		//轉換攻擊模式
		/*switch (PlayerTotalPoint_BAlien)
		{

		case 10:
			BOSSMode = 3;
			break;

		case 20:
			BOSSMode = 2;
			break;


		default:
			break;
		}*/

		if (PlayerTotalPoint_BAlien > 20) {
		
			BOSSMode = 2;
		
		}

		else if (PlayerTotalPoint_BAlien > 10) {

			BOSSMode = 3;
		}
		





	}

	

	mxTran_Alien = Translate(_x, _y, 0.0);
	SetTRSMatrix(mxTran_Alien);

	

}


void BOSS_Alien::AutomaticFire(mat4 Alien_mxTran) {

}

void BOSS_Alien::AutoCheckHurtDie(GLfloat Bullet_x, GLfloat Bullet_y, float MAX_X, float MAX_Y, bool* HurtAlien) {

	if (_x - this->MAX_X <= (float)(Bullet_x - MAX_X) && _x + this->MAX_X >= (float)(Bullet_x + MAX_X) && _y + this->MAX_Y >= (float)(Bullet_y + MAX_Y) && _y - this->MAX_Y <= (float)(Bullet_y - MAX_Y)) { //判斷是否在中彈的範圍內

		*HurtAlien = true; //設定該子彈有打到Alien

		Blood--;
		PlayerTotalPoint_BAlien++;

	}



	if (Blood <= 0)
	{
		if (used) {
			CreateSmoke(this->_x, this->_y);

		}
		
		used = false;
		alife = false;
		Game_Over = true;
	}



}


void BOSS_Alien::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
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


void BOSS_Alien::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}


void BOSS_Alien::CreateBufferObject()
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
