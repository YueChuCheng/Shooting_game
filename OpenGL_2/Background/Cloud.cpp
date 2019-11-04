#include "Cloud.h"


Cloud::Cloud()
{

	 
	//circle top_left
	for (int i = 0; i < Cloud_circle; i++)
	{
		_Points[i] = vec4(0.3f * cosf(2.0f * M_PI * i / Cloud_circle) , 0.3 * sinf(2.0f * M_PI * i / Cloud_circle), 0.0f, 1.0f);
	}




	//rectangle top
	_Points[0 + Cloud_circle] = vec4(-0.0f , 0.3f, 0.0f , 1.0f );
	_Points[1 + Cloud_circle] = vec4(-0.0f, -0.3f, 0.0f, 1.0f);
	_Points[2 + Cloud_circle] = vec4(1.2f, -0.3f, 0.0f, 1.0f);
	_Points[3 + Cloud_circle] = vec4(-0.0f, 0.3f, 0.0f, 1.0f);
	_Points[4 + Cloud_circle] = vec4(1.2f, -0.3f, 0.0f, 1.0f);
	_Points[5 + Cloud_circle] = vec4(1.2f, 0.3f, 0.0f, 1.0f);

	

	//circle top_right
	for (int i = 0; i < Cloud_circle; i++)
	{
		_Points[i + Cloud_circle + Cloud_rectangle] = vec4(0.3f * cosf(2.0f * M_PI * i / Cloud_circle) +1.2 , 0.3 * sinf(2.0f * M_PI * i / Cloud_circle), 0.0f, 1.0f);
	}

	


	//circle bottom_left
	for (int i = 0; i < Cloud_circle; i++)
	{
		_Points[i + (Cloud_circle * 2) + Cloud_rectangle] = vec4(0.3f * cosf(2.0f * M_PI * i / Cloud_circle) - 0.5, 0.3 * sinf(2.0f * M_PI * i / Cloud_circle) - 0.5 , 0.0f, 1.0f);
	}

	


	//rectangle bottom
	_Points[0 + (Cloud_circle * 3) + Cloud_rectangle] = vec4(-0.5, -0.2f, 0.0f, 1.0f);
	_Points[1 + (Cloud_circle * 3) + Cloud_rectangle] = vec4(-0.5, -0.8f, 0.0f, 1.0f);
	_Points[2 + (Cloud_circle * 3) + Cloud_rectangle] = vec4(0.7, -0.8f, 0.0f, 1.0f);
	_Points[3 + (Cloud_circle * 3) + Cloud_rectangle] = vec4(-0.5, -0.2f, 0.0f, 1.0f);
	_Points[4 + (Cloud_circle * 3) + Cloud_rectangle] = vec4(0.7, -0.8f, 0.0f, 1.0f);
	_Points[5 + (Cloud_circle * 3) + Cloud_rectangle] = vec4(0.7, -0.2f, 0.0f, 1.0f);

	

	//circle bottom_right
	for (int i = 0; i < Cloud_circle; i++)
	{
		_Points[i + (Cloud_circle * 3) + (Cloud_rectangle*2)] = vec4(0.3f * cosf(2.0f * M_PI * i / Cloud_circle) + 0.7, 0.3 * sinf(2.0f * M_PI * i / Cloud_circle) - 0.5, 0.0f, 1.0f);
	}

	for (int i = 0; i < Cloud_Point_NUM; i++)
	{
		_Colors[i] = vec4(0.9960,0.9609,0.9023,1.0f);
	}



	//校正
	for (int i = 0; i < Cloud_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x ;
		_Points[i].y = _Points[i].y * (360.0 / 640.0) ;
	}


	CreateBufferObject();
	
}


void Cloud::CreateBufferObject()
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


void Cloud::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) _Program = InitShader("vsCloud_1.glsl", "fsCloud_1.glsl");
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
	

	//設定 速度、位置、大小
	_xLoc = glGetUniformLocation(_Program,"fx");
	_yLoc = glGetUniformLocation(_Program, "fy");
	_scaleLoc = glGetUniformLocation(_Program, "fscale");

	glBindBuffer(GL_ARRAY_BUFFER, 0);




}




//設定位置、大小
void Cloud::SetXYScale(float fx, float fy, float fscale) {
	
	glUseProgram(_Program); //利用shader計算時為了避免用到前一張圖片的shader program因此必須在執行一次
	glUniform1f(_xLoc, fx);
	glUniform1f(_yLoc, fy);
	glUniform1f(_scaleLoc, fscale);
	
}


void Cloud::SetViewMatrix(mat4& mat)
{
	_mxView = mat;
	_bUpdateMV = true;
}

void Cloud::SetProjectionMatrix(mat4& mat)
{
	_mxProjection = mat;
	_bUpdateProj = true;
}

void Cloud::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}

void Cloud::SetColor(GLfloat vColor[4])
{
	for (int i = 0; i < Cloud_Point_NUM; i++) {
		_Colors[i].x = vColor[0];
		_Colors[i].y = vColor[1];
		_Colors[i].z = vColor[2];
		_Colors[i].w = vColor[3];
	}
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
}

void Cloud::SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[])
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






void Cloud::Draw()
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

	glDrawArrays(GL_TRIANGLE_FAN,0, Cloud_circle);
	glDrawArrays(GL_TRIANGLES, Cloud_circle, Cloud_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, Cloud_circle + Cloud_rectangle, Cloud_circle);
	glDrawArrays(GL_TRIANGLE_FAN, ( Cloud_circle * 2 ) + Cloud_rectangle, Cloud_circle);
	glDrawArrays(GL_TRIANGLES, (Cloud_circle * 3) + Cloud_rectangle, Cloud_rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, (Cloud_circle * 3) + (Cloud_rectangle * 2), Cloud_circle);

}


//Cloud Update



/*void Cloud::DrawW()
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
	glDrawArrays( GL_TRIANGLE_FAN, 0, body_circle);
	glDrawArrays(GL_TRIANGLE_FAN, body_circle, head_circle);
}*/



//雲層自動移動
void Cloud:: AutoTranslate_Background() {



		if (_y < -2.0) {

			_x = (double)(rand() % 4600 - 2300.0) / 1000.0;
			_y = 2.5;

		}

		_y -= 0.002f;     // 遞減
		SetXYScale(_x, _y, _scale);//設定雲朵資訊



}