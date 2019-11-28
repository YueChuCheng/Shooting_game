#include"Smoke_BOSS.h"


Smoke::Smoke()
{

	for (int i = 0; i < Smoke_circle; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 3.5f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle), 0.0f, 1.0f);

	}


	for (int i = 0; i < Smoke_circle; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Smoke_circle; i < Smoke_circle * 2; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) , 0.0f, 1.0f);

	}


	for (int i = Smoke_circle; i < Smoke_circle * 2; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Smoke_circle * 2; i < Smoke_circle * 3; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) , 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 2; i < Smoke_circle * 3; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}



	for (int i = Smoke_circle * 3; i < Smoke_circle * 4; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) , 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 3; i < Smoke_circle * 4; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}



	for (int i = Smoke_circle * 4; i < Smoke_circle * 5; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) , 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 4; i < Smoke_circle * 5; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}


	for (int i = Smoke_circle * 5; i < Smoke_circle * 6; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) , 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 5; i < Smoke_circle * 6; i++)
	{
		_Colors[i] = vec4(0.5664f, 0.5820f, 0.5234f, 1.0f);

	}


	for (int i = Smoke_circle * 6; i < Smoke_circle * 7; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) , 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 6; i < Smoke_circle * 7; i++)
	{
		_Colors[i] = vec4(0.5664f, 0.5820f, 0.5234f, 1.0f);

	}


	for (int i = Smoke_circle * 7; i < Smoke_circle * 8; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) , 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 7; i < Smoke_circle * 8; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Smoke_circle * 8; i < Smoke_circle * 9; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) , 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 8; i < Smoke_circle * 9; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}


	for (int i = Smoke_circle * 9; i < Smoke_circle * 10; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) , 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 9; i < Smoke_circle * 10; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}


	for (int i = Smoke_circle * 10; i < Smoke_circle * 11; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) - 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.2f, 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 10; i < Smoke_circle * 11; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Smoke_circle * 11; i < Smoke_circle * 12; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) - 2.8f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) + 0.2f, 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 11; i < Smoke_circle * 12; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}



	for (int i = Smoke_circle * 12; i < Smoke_circle * 13; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 1.77f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.8f, 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 12; i < Smoke_circle * 13; i++)
	{
		_Colors[i] = vec4(0.5f, 0.5078f, 0.4726f, 1.0f);

	}


	for (int i = Smoke_circle * 13; i < Smoke_circle * 14; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 1.7f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.65f, 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 13; i < Smoke_circle * 14; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Smoke_circle * 14; i < Smoke_circle * 15; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.2f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.8f, 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 14; i < Smoke_circle * 15; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}


	for (int i = Smoke_circle * 15; i < Smoke_circle * 16; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.15f, 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.7f, 0.0f, 1.0f);

	}


	for (int i = Smoke_circle * 15; i < Smoke_circle * 16; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}


	//タゑㄒ
	for (int i = 0; i < Smoke_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (2.0 / 10.0);
		_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

	}


	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}


void Smoke::CreateBufferObject()
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

void Smoke::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) _Program = InitShader("vsSmoke.glsl", "fsSmoke.glsl");
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

void Smoke::SetViewMatrix(mat4& mat)
{
	_mxView = mat;
	_bUpdateMV = true;
}

void Smoke::SetProjectionMatrix(mat4& mat)
{
	_mxProjection = mat;
	_bUpdateProj = true;
}

void Smoke::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}

void Smoke::SetAlpha(GLfloat alpha)
{
	for (int i = 0; i < Smoke_Point_NUM; i++) {
		_Colors[i].w = alpha;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
}

void Smoke::SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[])
{
	_Colors[0].x = vLFColor[0];
	_Colors[0].y = vLFColor[1];
	_Colors[0].z = vLFColor[2];
	_Colors[0].w = vLFColor[3];
	_Colors[3] = _Colors[0];

	_Colors[1].x = vLRColor[0];
	_Colors[1].y = vLRColor[1];
	_Colors[1].z = vLRColor[2];
	_Colors[1].w = vLRColor[3];

	_Colors[2].x = vTRColor[0];
	_Colors[2].y = vTRColor[1];
	_Colors[2].z = vTRColor[2];
	_Colors[2].w = vTRColor[3];
	_Colors[4] = _Colors[2];

	_Colors[5].x = vTLColor[0];
	_Colors[5].y = vTLColor[1];
	_Colors[5].z = vTLColor[2];
	_Colors[5].w = vTLColor[3];

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
}

void Smoke::Draw()
{

	glUseProgram(_Program);
	glBindVertexArray(_VAO);
	if (_bUpdateMV) {
		_mxMVFinal = _mxView * _mxTRS;
		_bUpdateMV = false;
	}
	glUniformMatrix4fv(_ModelView, 1, GL_TRUE, _mxMVFinal);

	//⊿Τ锣传跌à玥ぃ斗耞Proj琌э跑
	/*if (_bUpdateProj) {
		glUniformMatrix4fv(_Projection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}*/


	glDrawArrays(GL_TRIANGLE_FAN, 0, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 1, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 2, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 3, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 4, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 5, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 6, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 7, Smoke_circle);
	/*glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 8, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 9, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 10, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 11, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 12, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 13, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 14, Smoke_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Smoke_circle * 15, Smoke_circle);*/



}
bool touch_top = false; //翴琌计笷程よ

void Smoke::AutomaticMotion(float boss_x, float boss_y, float delta) {

	 

	//翴1.
	for (int i = 0; i < Smoke_circle; i++)
	{
			_Points[i].x += (0.18f * delta);
			_Points[i].y += (0.3f * delta);
			
		
	}

	for (int i = 0; i < Smoke_circle; i++)
	{

		if (_Points[i].y < 0.5f) { //﹟Τ翴ぃtop(0.5f) ぇ
			touch_top = false;
			break;
		}
		else
		{
			touch_top = true;
		}

	}

	
	for (int i = 0; i < Smoke_circle; i++)
	{
		if (touch_top) { //翴常程よ

			_Points[i].x = 0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f;//砞﹚–翴计﹍篈
			_Points[i].x = _Points[i].x * (2.0 / 10.0);

			_Points[i].y = 0.3f * sinf(2.0f * M_PI * i / Smoke_circle);//砞﹚–翴计﹍篈
			_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

		}

	}


	//翴2.
	for (int i = Smoke_circle; i < Smoke_circle * 2; i++)
	{
		_Points[i].x += (0.05f * delta);
		_Points[i].y += (0.2f * delta);

	}

	for (int i = Smoke_circle; i < Smoke_circle * 2; i++)
	{

		if (_Points[i].y < 0.5f) { //﹟Τ翴ぃtop(0.5f) ぇ
			touch_top = false;
			break;
		}
		else
		{
			touch_top = true;
		}

	}


	for (int i = Smoke_circle; i < Smoke_circle * 2; i++)
	{
		if (touch_top) { //翴常程よ

			_Points[i].x = 0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f;//砞﹚–翴计﹍篈
			_Points[i].x = _Points[i].x * (2.0 / 10.0);



			_Points[i].y = 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.2f;//砞﹚–翴计﹍篈
			_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

		}

	}


	//翴3.
	for (int i = Smoke_circle * 2; i < Smoke_circle * 3; i++)
	{
		_Points[i].x += (0.01f * delta);
		_Points[i].y += (0.15f * delta);

	}

	for (int i = Smoke_circle * 2; i < Smoke_circle * 3; i++)
	{

		if (_Points[i].y < 0.4f) { //﹟Τ翴ぃtop(0.5f) ぇ
			touch_top = false;
			break;
		}
		else
		{
			touch_top = true;
		}

	}


	for (int i = Smoke_circle * 2; i < Smoke_circle * 3; i++)
	{
		if (touch_top) { //翴常程よ

			_Points[i].x = 0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f;//砞﹚–翴计﹍篈
			_Points[i].x = _Points[i].x * (2.0 / 10.0);



			_Points[i].y = 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.2f;//砞﹚–翴计﹍篈
			_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

		}

	}



	//翴4.
	for (int i = Smoke_circle * 3; i < Smoke_circle * 4; i++)
	{
		_Points[i].x += (0.015f * delta);
		_Points[i].y += (0.2f * delta);

	}

	for (int i = Smoke_circle * 3; i < Smoke_circle * 4; i++)
	{

		if (_Points[i].y < 0.5f) { //﹟Τ翴ぃtop(0.5f) ぇ
			touch_top = false;
			break;
		}
		else
		{
			touch_top = true;
		}

	}


	for (int i = Smoke_circle * 3; i < Smoke_circle * 4; i++)
	{
		if (touch_top) { //翴常程よ

			_Points[i].x = 0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f;//砞﹚–翴计﹍篈
			_Points[i].x = _Points[i].x * (2.0 / 10.0);



			_Points[i].y = 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.2f;//砞﹚–翴计﹍篈
			_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

		}

	}


	//翴5.
	for (int i = Smoke_circle * 4; i < Smoke_circle * 5; i++)
	{
		_Points[i].x += (0.1f * delta);
		_Points[i].y += (0.15f * delta);

	}

	for (int i = Smoke_circle * 4; i < Smoke_circle * 5; i++)
	{

		if (_Points[i].y < 0.5f) { //﹟Τ翴ぃtop(0.5f) ぇ
			touch_top = false;
			break;
		}
		else
		{
			touch_top = true;
		}

	}


	for (int i = Smoke_circle * 4; i < Smoke_circle * 5; i++)
	{
		if (touch_top) { //翴常程よ

			_Points[i].x = 0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f;//砞﹚–翴计﹍篈
			_Points[i].x = _Points[i].x * (2.0 / 10.0);



			_Points[i].y = 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.2f;//砞﹚–翴计﹍篈
			_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

		}

	}



	//翴6.
	for (int i = Smoke_circle * 5; i < Smoke_circle * 6; i++)
	{
		_Points[i].x += (0.1f * delta);
		_Points[i].y += (0.25f * delta);

	}

	for (int i = Smoke_circle * 5; i < Smoke_circle * 6; i++)
	{

		if (_Points[i].y < 0.4f) { //﹟Τ翴ぃtop(0.5f) ぇ
			touch_top = false;
			break;
		}
		else
		{
			touch_top = true;
		}

	}


	for (int i = Smoke_circle * 5; i < Smoke_circle * 6; i++)
	{
		if (touch_top) { //翴常程よ

			_Points[i].x = 0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f;//砞﹚–翴计﹍篈
			_Points[i].x = _Points[i].x * (2.0 / 10.0);



			_Points[i].y = 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.2f;//砞﹚–翴计﹍篈
			_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

		}

	}


	//翴7.
	for (int i = Smoke_circle * 6; i < Smoke_circle * 7; i++)
	{
		_Points[i].x += (-0.02f * delta);
		_Points[i].y += (0.15f * delta);

	}

	for (int i = Smoke_circle * 6; i < Smoke_circle * 7; i++)
	{

		if (_Points[i].y < 0.1f) { //﹟Τ翴ぃtop(0.5f) ぇ
			touch_top = false;
			break;
		}
		else
		{
			touch_top = true;
		}

	}


	for (int i = Smoke_circle * 6; i < Smoke_circle * 7; i++)
	{
		if (touch_top) { //翴常程よ

			_Points[i].x = 0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f;//砞﹚–翴计﹍篈
			_Points[i].x = _Points[i].x * (2.0 / 10.0);



			_Points[i].y = 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.2f;//砞﹚–翴计﹍篈
			_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

		}

	}


	//翴8.
	for (int i = Smoke_circle * 7; i < Smoke_circle * 8; i++)
	{
		_Points[i].x += (0.12f * delta);
		_Points[i].y += (0.08f * delta);

	}

	for (int i = Smoke_circle * 7; i < Smoke_circle * 8; i++)
	{

		if (_Points[i].y < 0.3f) { //﹟Τ翴ぃtop(0.5f) ぇ
			touch_top = false;
			break;
		}
		else
		{
			touch_top = true;
		}

	}


	for (int i = Smoke_circle * 7; i < Smoke_circle * 8; i++)
	{
		if (touch_top) { //翴常程よ

			_Points[i].x = 0.3f * cosf(2.0f * M_PI * i / Smoke_circle) + 2.8f;//砞﹚–翴计﹍篈
			_Points[i].x = _Points[i].x * (2.0 / 10.0);



			_Points[i].y = 0.3f * sinf(2.0f * M_PI * i / Smoke_circle) - 0.2f;//砞﹚–翴计﹍篈
			_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

		}

	}

	_x = boss_x;
	_y = boss_y;
	mxTran_Smoke = Translate(_x , _y , 0.0);
	this->SetTRSMatrix(mxTran_Smoke);





	//盢戈癟肚患狝竟狠
	
	glBindBuffer(GL_ARRAY_BUFFER, _VBO); 
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_Points), _Points);
	
}
