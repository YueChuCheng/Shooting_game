#include "Alien.h"




BOSS_Alien::~BOSS_Alien()
{


}


BOSS_Alien::BOSS_Alien()
{

	_Points[0] = vec4(-0.75, 0.4, 0.0, 1.0);
	_Points[1] = vec4(-0.75, -0.4, 0.0, 1.0);
	_Points[2] = vec4(0.75, -0.4, 0.0, 1.0);
	_Points[3] = vec4(-0.75, 0.4, 0.0, 1.0);
	_Points[4] = vec4(0.75, -0.4, 0.0, 1.0);
	_Points[5] = vec4(0.75, 0.4, 0.0, 1.0);


	_Points[rectangle_BAlien+0] = vec4(-0.9, 0.0, 0.0, 1.0);
	_Points[rectangle_BAlien+1] = vec4(-0.9, -0.8, 0.0, 1.0);
	_Points[rectangle_BAlien+2] = vec4(-0.6, -0.8, 0.0, 1.0);
	_Points[rectangle_BAlien+3] = vec4(-0.9, 0.0, 0.0, 1.0);
	_Points[rectangle_BAlien+4] = vec4(-0.6, -0.8, 0.0, 1.0);
	_Points[rectangle_BAlien+5] = vec4(-0.6, 0.0, 0.0, 1.0);

	_Points[(rectangle_BAlien * 2) + 0] = vec4(0.9, 0.0, 0.0, 1.0);
	_Points[(rectangle_BAlien * 2) + 1] = vec4(0.9, -0.8, 0.0, 1.0);
	_Points[(rectangle_BAlien * 2) + 2] = vec4(0.6, -0.8, 0.0, 1.0);
	_Points[(rectangle_BAlien * 2) + 3] = vec4(0.9, 0.0, 0.0, 1.0);
	_Points[(rectangle_BAlien * 2) + 4] = vec4(0.6, -0.8, 0.0, 1.0);
	_Points[(rectangle_BAlien * 2) + 5] = vec4(0.6, 0.0, 0.0, 1.0);

	_Points[(rectangle_BAlien * 3) + 0] = vec4(0.9, -0.7, 0.0, 1.0);
	_Points[(rectangle_BAlien * 3) + 1] = vec4(0.9, -0.8, 0.0, 1.0);
	_Points[(rectangle_BAlien * 3) + 2] = vec4(0.6, -0.8, 0.0, 1.0);
	_Points[(rectangle_BAlien * 3) + 3] = vec4(0.9, -0.7, 0.0, 1.0);
	_Points[(rectangle_BAlien * 3) + 4] = vec4(0.6, -0.8, 0.0, 1.0);
	_Points[(rectangle_BAlien * 3) + 5] = vec4(0.6, -0.7, 0.0, 1.0);


	_Points[(rectangle_BAlien * 4) + 0] = vec4(-0.9, -0.7, 0.0, 1.0);
	_Points[(rectangle_BAlien * 4) + 1] = vec4(-0.9, -0.8, 0.0, 1.0);
	_Points[(rectangle_BAlien * 4) + 2] = vec4(-0.6, -0.8, 0.0, 1.0);
	_Points[(rectangle_BAlien * 4) + 3] = vec4(-0.9, -0.7, 0.0, 1.0);
	_Points[(rectangle_BAlien * 4) + 4] = vec4(-0.6, -0.8, 0.0, 1.0);
	_Points[(rectangle_BAlien * 4) + 5] = vec4(-0.6, -0.7, 0.0, 1.0);


	

	//color
	for (int i = 0; i < rectangle_BAlien; i++)
	{
		_Colors[i] = vec4(0.0, 0.0, 1.0, 1.0);
	}


	for (int i = rectangle_BAlien; i < rectangle_BAlien * 3; i++)
	{
		_Colors[i] = vec4(1.0, 1.0, 1.0, 1.0);
	}


	

	for (int i = (rectangle_BAlien * 3); i < (rectangle_BAlien * 4); i++)
	{
		_Colors[i] = vec4(1.0, 1.0, 0.0, 1.0);
	}


	for (int i = (rectangle_BAlien * 4); i < (rectangle_BAlien * 5); i++)
	{
		_Colors[i] = vec4(1.0, 1.0, 0.0, 1.0);
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


	glDrawArrays(GL_TRIANGLES, 0, rectangle_BAlien);
	glDrawArrays(GL_TRIANGLES, rectangle_BAlien, rectangle_BAlien );
	glDrawArrays(GL_TRIANGLES, rectangle_BAlien * 2, rectangle_BAlien );
	glDrawArrays(GL_TRIANGLES, rectangle_BAlien * 3, rectangle_BAlien );
	glDrawArrays(GL_TRIANGLES, rectangle_BAlien * 4, rectangle_BAlien );


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
	glDrawArrays(GL_TRIANGLES, 0, rectangle_BAlien);
	glDrawArrays(GL_TRIANGLES, rectangle_BAlien, rectangle_BAlien);
	glDrawArrays(GL_TRIANGLES, rectangle_BAlien * 2, rectangle_BAlien);
	glDrawArrays(GL_TRIANGLES, rectangle_BAlien * 3, rectangle_BAlien);
	glDrawArrays(GL_TRIANGLES, rectangle_BAlien * 4, rectangle_BAlien);
}


void BOSS_Alien::AutomaticMotion() {

	if(first_direction_x){
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

	if (_y > 1.5f || _y < 1.2f)
	{
		first_direction_y = !first_direction_y;
	}


	mxTran_Alien = Translate(_x, _y, 0.0);
	SetTRSMatrix(mxTran_Alien);


}


void BOSS_Alien::AutomaticFire(mat4 Alien_mxTran) {

}

void BOSS_Alien::AutoCheckHurtDie(GLfloat Bullet_x, GLfloat Bullet_y, float MAX_X, float MAX_Y, bool* HurtAlien) {

	if (_x - this->MAX_X <= Bullet_x - MAX_X && _x + this->MAX_X >= Bullet_x + MAX_X && _y + this->MAX_Y >= Bullet_y + MAX_Y && _y - this->MAX_Y <= Bullet_y - MAX_Y) { //判斷是否在中彈的範圍內

		*HurtAlien = true; //設定該子彈有打到Alien

		//Blood--;


	}



	if (Blood <= 0)
	{
		alife = false;
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
