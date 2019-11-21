#include "Explo.h"

Explo::Explo()
{

	for (int i = 0; i < Explo_circle; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Explo_circle) + 3.5f, 0.3f * sinf(2.0f * M_PI * i / Explo_circle), 0.0f, 1.0f);

	}


	for (int i = 0; i < Explo_circle; i++)
	{
		_Colors[i] = vec4(0.6953f,0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Explo_circle; i < Explo_circle * 2; i++)
	{
		_Points[i] = vec4(0.6f * cosf(2.0f * M_PI * i / Explo_circle) + 2.8f, 0.6f * sinf(2.0f * M_PI * i / Explo_circle) - 0.2f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle ; i < Explo_circle * 2; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Explo_circle * 2; i < Explo_circle * 3; i++)
	{
		_Points[i] = vec4(0.42f * cosf(2.0f * M_PI * i / Explo_circle) + 3.1f, 0.42f * sinf(2.0f * M_PI * i / Explo_circle) + 0.1f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 2; i < Explo_circle * 3; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}



	for (int i = Explo_circle * 3; i < Explo_circle * 4; i++)
	{
		_Points[i] = vec4(0.43f * cosf(2.0f * M_PI * i / Explo_circle) + 2.3f, 0.43f * sinf(2.0f * M_PI * i / Explo_circle) - 0.1f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 3; i < Explo_circle * 4; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}



	for (int i = Explo_circle * 4; i < Explo_circle * 5; i++)
	{
		_Points[i] = vec4(0.7f * cosf(2.0f * M_PI * i / Explo_circle) + 1.6f, 0.7f * sinf(2.0f * M_PI * i / Explo_circle) + 0.35f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 4; i < Explo_circle * 5; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}


	for (int i = Explo_circle * 5; i < Explo_circle * 6; i++)
	{
		_Points[i] = vec4(0.7f * cosf(2.0f * M_PI * i / Explo_circle) + 0.8f, 0.7f * sinf(2.0f * M_PI * i / Explo_circle) - 0.32f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 5; i < Explo_circle * 6; i++)
	{
		_Colors[i] = vec4(0.5664f, 0.5820f, 0.5234f, 1.0f);

	}


	for (int i = Explo_circle * 6; i < Explo_circle * 7; i++)
	{
		_Points[i] = vec4(0.9f * cosf(2.0f * M_PI * i / Explo_circle) + 0.9f, 0.9f * sinf(2.0f * M_PI * i / Explo_circle) + 0.9f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 6; i < Explo_circle * 7; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}


	for (int i = Explo_circle * 7; i < Explo_circle * 8; i++)
	{
		_Points[i] = vec4(0.7f * cosf(2.0f * M_PI * i / Explo_circle) + 0.7f, 0.7f * sinf(2.0f * M_PI * i / Explo_circle) - 0.2f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 7; i < Explo_circle * 8; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Explo_circle * 8; i < Explo_circle * 9; i++)
	{
		_Points[i] = vec4(1.1f * cosf(2.0f * M_PI * i / Explo_circle) + 0.3f, 1.0f * sinf(2.0f * M_PI * i / Explo_circle) + 1.3f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 8; i < Explo_circle * 9; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}


	for (int i = Explo_circle * 9; i < Explo_circle * 10; i++)
	{
		_Points[i] = vec4(1.1f * cosf(2.0f * M_PI * i / Explo_circle) + 0.23f, 1.0f * sinf(2.0f * M_PI * i / Explo_circle) + 1.6f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 9; i < Explo_circle * 10; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}


	for (int i = Explo_circle * 10; i < Explo_circle * 11; i++)
	{
		_Points[i] = vec4(1.0f * cosf(2.0f * M_PI * i / Explo_circle) - 0.5f, 0.8f * sinf(2.0f * M_PI * i / Explo_circle) - 0.2f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 10; i < Explo_circle * 11; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Explo_circle * 11; i < Explo_circle * 12; i++)
	{
		_Points[i] = vec4(1.0f * cosf(2.0f * M_PI * i / Explo_circle) - 0.5f, 0.8f * sinf(2.0f * M_PI * i / Explo_circle) + 0.2f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 11; i < Explo_circle * 12; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}



	for (int i = Explo_circle * 12; i < Explo_circle * 13; i++)
	{
		_Points[i] = vec4(0.43f * cosf(2.0f * M_PI * i / Explo_circle) + 1.77f, 0.43f * sinf(2.0f * M_PI * i / Explo_circle) - 0.8f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 12; i < Explo_circle * 13; i++)
	{
		_Colors[i] = vec4(0.5f, 0.5078f, 0.4726f, 1.0f);

	}


	for (int i = Explo_circle * 13; i < Explo_circle * 14; i++)
	{
		_Points[i] = vec4(0.43f * cosf(2.0f * M_PI * i / Explo_circle) + 1.7f, 0.43f * sinf(2.0f * M_PI * i / Explo_circle) - 0.65f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 13; i < Explo_circle * 14; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}



	for (int i = Explo_circle * 14; i < Explo_circle * 15; i++)
	{
		_Points[i] = vec4(0.43f * cosf(2.0f * M_PI * i / Explo_circle) + 2.2f, 0.43f * sinf(2.0f * M_PI * i / Explo_circle) - 0.8f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 14; i < Explo_circle * 15; i++)
	{
		_Colors[i] = vec4(0.6953f, 0.7148f, 0.6367f, 1.0f);

	}


	for (int i = Explo_circle * 15; i < Explo_circle * 16; i++)
	{
		_Points[i] = vec4(0.43f * cosf(2.0f * M_PI * i / Explo_circle) + 2.15f, 0.43f * sinf(2.0f * M_PI * i / Explo_circle) - 0.7f, 0.0f, 1.0f);

	}


	for (int i = Explo_circle * 15; i < Explo_circle * 16; i++)
	{
		_Colors[i] = vec4(0.8515f, 0.8593f, 0.8164f, 1.0f);

	}


	//校正比例
	for (int i = 0; i < Explo_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (2.0 / 10.0);
		_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0);

	}


	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}


void Explo::CreateBufferObject()
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

void Explo::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
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

void Explo::SetViewMatrix(mat4& mat)
{
	_mxView = mat;
	_bUpdateMV = true;
}

void Explo::SetProjectionMatrix(mat4& mat)
{
	_mxProjection = mat;
	_bUpdateProj = true;
}

void Explo::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}

void Explo::SetAlpha(GLfloat alpha)
{
	for (int i = 0; i < Explo_Point_NUM; i++) {
		_Colors[i].w = alpha;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
}

void Explo::SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[])
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

void Explo::Draw()
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


	glDrawArrays(GL_TRIANGLE_FAN, 0, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 1 ,  Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 2, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 3, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 4, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 5, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 6, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 7, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 8, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 9, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 10, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 11, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 12, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 13, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 14, Explo_circle);
	glDrawArrays(GL_TRIANGLE_FAN, Explo_circle * 15, Explo_circle);
	


}


void Explo::AutomaticMotion(float delta) {
	timer_smoke += delta;

	this->_y -= 0.002f;
	this->mxTran_Smoke = Translate(this->_x , this->_y , 0.0f);
	this->SetTRSMatrix(this->mxTran_Smoke);

	if (timer_smoke > (1.0/250.0 )) {
		
		this->alphea_explo -= 0.008f;
		SetAlpha(alphea_explo);
		timer_smoke = 0.0f;
	}
	
	
	if (this->alphea_explo <= 0.0f) {
		this->alphea_explo = 1.0f;
		this->used = false;
		timer_smoke = 0.0f;

	}


}
