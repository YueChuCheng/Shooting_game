#include "Bullet_Main.h"


Bullet_SAlien::Bullet_SAlien() {

	for (int i = 0; i < Bullet_SAlien_Point_NUM; i++)
	{
		_Points[i] = vec4(0.2f * cosf(2.0f * M_PI * i / Bullet_SAlien_Point_NUM), 0.2f * sinf(2.0f * M_PI * i / Bullet_SAlien_Point_NUM), 0.0f, 1.0f);
	}

	for (int i = 0; i < Bullet_SAlien_Point_NUM; i++)
	{
		_Colors[i] = vec4(0.9960f, 0.5507f, 0.25f, 1.0f);
	}

	for (int i = 0; i < Bullet_SAlien_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (3.5 / 10.0);
		_Points[i].y = _Points[i].y * (360.0 / 640.0) * (3.5 / 10.0);

	}



	CreateBufferObject();

};
Bullet_SAlien::~Bullet_SAlien() {};


void Bullet_SAlien::AutoTranslate_Bullet() {

	
	
	switch (fire_style)
	{
	case NORMAL:
		_y -= 0.0035;
		BulletTrans = Translate(_x, _y, 0.0);
		SetTRSMatrix(BulletTrans);

		break;
	case LEFT_45:
		_x -= 0.0035 / 1.4;//pow(0.5)
		_y -= 0.0035 / 1.4;//pow(0.5)
		BulletTrans = Translate(_x, _y, 0.0);
		SetTRSMatrix(BulletTrans);

		break;
	case RIGHT_45:
		_x += 0.0035 / 1.4;//pow(0.5)
		_y -= 0.0035 / 1.4;//pow(0.5)
		BulletTrans = Translate(_x, _y, 0.0);
		SetTRSMatrix(BulletTrans);


		break;
	

	default:
		break;
	}




}


void Bullet_SAlien::CreateBufferObject()
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


void Bullet_SAlien::Draw()
{


	glUseProgram(_Program);
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


	glDrawArrays(GL_TRIANGLE_FAN, 0, Bullet_SAlien_Point_NUM);
	

}



void Bullet_SAlien::DrawW()
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
	glDrawArrays(GL_TRIANGLE_FAN, 0, Bullet_SAlien_Point_NUM);
}



void Bullet_SAlien::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) _Program = InitShader("vsBullet_Main.glsl", "fsBullet_Main.glsl");
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


void Bullet_SAlien::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}