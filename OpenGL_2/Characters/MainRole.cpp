#include "MainRole.h"

MainRole::MainRole()
{

	//body
	for (int i = 0; i < body_circle; i++)
	{
		_Points[i] = vec4(0.5f*cosf(2.0f*M_PI*i/body_circle),0.5f* sinf(2.0f * M_PI * i / body_circle),0.0f,1.0f);
	}
	for (int i = 0; i < body_circle; i++)
	{
		_Colors[i] = vec4(0.2187f, 0.6171f, 0.7734f, 1.0f);
	}


	//head
	for (int i = 0; i < head_circle; i++)
	{
		float h = 0.6;
		float x = 0.4-i*(0.8/ head_circle);
		float y = ((0.3-h)/0.16)*x*x + h ;


		_Points[i + body_circle] = vec4(x, y, 0.0f, 1.0f);
		
	}

	for (int i = 0; i < head_circle; i++)
	{
		_Colors[i+ body_circle] = vec4(0.9921f, 0.0039f, 0.0f, 1.0f);
	}

	//circle_1

	for (int i = 0; i < circle; i++)
	{
		_Points[i + body_circle + head_circle] = vec4(0.25f * cosf(2.0f * M_PI * i / body_circle), 0.25f * sinf(2.0f * M_PI * i / body_circle), 0.0f, 1.0f);
	}
	for (int i = 0; i < circle; i++)
	{
		_Colors[i + body_circle + head_circle] = vec4(0.9531f, 0.9375f, 0.3828, 1.0f);
	}



	//circle_2

	for (int i = 0; i < circle; i++)
	{
		_Points[i + body_circle + head_circle + circle] = vec4(0.15f * cosf(2.0f * M_PI * i / body_circle), 0.15f * sinf(2.0f * M_PI * i / body_circle), 0.0f, 1.0f);
	}
	for (int i = 0; i < circle; i++)
	{
		_Colors[i + body_circle + head_circle+ circle] = vec4(0.496f, 0.9179f, 0.9335, 1.0f);
	}


	//rectangle_left
	_Points[0 + body_circle + head_circle + (circle * 2)] = vec4(-0.6, -0.1, 0.0, 1.0);
	_Points[1 + body_circle + head_circle + (circle * 2)] = vec4(-0.6, -0.55, 0.0, 1.0);
	_Points[2 + body_circle + head_circle + (circle * 2)] = vec4(-0.42, -0.55, 0.0, 1.0);
	_Points[3 + body_circle + head_circle + (circle * 2)] = vec4(-0.6, -0.1, 0.0, 1.0);
	_Points[4 + body_circle + head_circle + (circle * 2)] = vec4(-0.42, -0.55, 0.0, 1.0);
	_Points[5 + body_circle + head_circle + (circle * 2)] = vec4(-0.42, -0.1, 0.0, 1.0);


	for (int i = 0; i < rectangle; i++)
	{
		_Colors[i + body_circle + head_circle + (circle * 2)] = vec4(0.9921f, 0.0039f, 0.0f, 1.0f);
	}


	//rectangle_right
	_Points[0 + body_circle + head_circle + (circle * 2) + rectangle] = vec4(0.6, -0.1, 0.0, 1.0);
	_Points[1 + body_circle + head_circle + (circle * 2) + rectangle] = vec4(0.6, -0.55, 0.0, 1.0);
	_Points[2 + body_circle + head_circle + (circle * 2) + rectangle] = vec4(0.42, -0.55, 0.0, 1.0);
	_Points[3 + body_circle + head_circle + (circle * 2) + rectangle] = vec4(0.6, -0.1, 0.0, 1.0);
	_Points[4 + body_circle + head_circle + (circle * 2) + rectangle] = vec4(0.42, -0.55, 0.0, 1.0);
	_Points[5 + body_circle + head_circle + (circle * 2) + rectangle] = vec4(0.42, -0.1, 0.0, 1.0);


	for (int i = 0; i < rectangle; i++)
	{
		_Colors[i + body_circle + head_circle + (circle * 2) + rectangle] = vec4(0.9921f, 0.0039f, 0.0f, 1.0f);
	}

	//semicircle_right

	for (int i = 0; i < circle; i++)
	{
		_Points[i + body_circle + head_circle + (circle * 2) + (rectangle*2)] = vec4(0.09f * cosf(1.0f * M_PI * i / body_circle)+0.51, 0.15f * sinf(1.0f * M_PI * i / body_circle)-0.1, 0.0f, 1.0f);
	}

	for (int i = 0; i < circle; i++)
	{
		_Colors[i + body_circle + head_circle + (circle * 2) + (rectangle * 2)] = vec4(0.9921f, 0.0039f, 0.0f, 1.0f);
	}

	//semicircle_left

	for (int i = 0; i < circle; i++)
	{
		_Points[i + body_circle + head_circle + (circle * 3) + (rectangle * 2)] = vec4(0.09f * cosf(1.0f * M_PI * i / body_circle) - 0.51, 0.15f * sinf(1.0f * M_PI * i / body_circle) - 0.1, 0.0f, 1.0f);
	}

	for (int i = 0; i < circle; i++)
	{
		_Colors[i + body_circle + head_circle + (circle * 3) + (rectangle * 2)] = vec4(0.9921f, 0.0039f, 0.0f, 1.0f);
	}

	//circle bottom
	for (int i = 0; i < circle; i++)
	{
		_Points[i + body_circle + head_circle + (circle * 4) + (rectangle * 2)] = vec4(0.25f * cosf(2.0f * M_PI * i / body_circle), 0.15f * sinf(2.0f * M_PI * i / body_circle) - 0.63, 0.0f, 1.0f);
	}

	for (int i = 0; i < circle; i++)
	{
		_Colors[i + body_circle + head_circle + (circle * 4) + (rectangle * 2)] = vec4(0.9882f, 0.9023, 0.2226, 1.0f);
	}


	//triangle_bottom
	_Points[0 + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(-0.23f, -0.7, 0.0, 1.0);
	_Points[1 + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(0.0f, -0.9, 0.0, 1.0);
	_Points[2 + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(0.23f, -0.7, 0.0, 1.0);
	

	for (int i = 0; i < triangle; i++)
	{
		_Colors[i + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(0.9882f, 0.9023, 0.2226, 1.0f);
	}


	//rectangle_bottom
	_Points[0+triangle + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(-0.2, -0.45, 0.0, 1.0);
	_Points[1+triangle + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(-0.2, -0.55, 0.0, 1.0);
	_Points[2+triangle + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(0.2, -0.55, 0.0, 1.0);
	_Points[3+triangle + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(-0.2, -0.45, 0.0, 1.0);
	_Points[4+triangle + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(0.2, -0.55, 0.0, 1.0);
	_Points[5+triangle + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(0.2, -0.45, 0.0, 1.0);


	for (int i = 0; i < rectangle; i++)
	{
		_Colors[i + triangle + body_circle + head_circle + (circle * 5) + (rectangle * 2)] = vec4(0.9921f, 0.0039f, 0.0f, 1.0f);
	}

	//校正比例
	for (int i = 0; i < Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (3.5 / 10.0);
		_Points[i].y = _Points[i].y  * (360.0/640.0) * (3.5 / 10.0);

	}



	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}


void MainRole::CreateBufferObject()
{
    glGenVertexArrays( 1, &_VAO );
    glBindVertexArray( _VAO );

    // Create and initialize a buffer object

    glGenBuffers( 1, &_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, _VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(_Points) + sizeof(_Colors), NULL, GL_STATIC_DRAW );

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(_Points), _Points ); 
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors );
}

void MainRole::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle)
{
    // Load shaders and use the resulting shader program
	if( uiShaderHandle == MAX_UNSIGNED_INT) _Program = InitShader("vsMainRole.glsl", "fsMainRole.glsl");
	else _Program = uiShaderHandle;

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( _Program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( _Program, "vColor" ); 
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(_Points)) );

	_ModelView = glGetUniformLocation( _Program, "ModelView" );
	_mxView = mxView;
	glUniformMatrix4fv( _ModelView, 1, GL_TRUE, _mxView );

    _Projection = glGetUniformLocation( _Program, "Projection" );
	_mxProjection = mxProjection;
	glUniformMatrix4fv( _Projection, 1, GL_TRUE, _mxProjection );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void MainRole::SetViewMatrix(mat4 &mat)
{
	_mxView = mat;
	_bUpdateMV = true;
}

void MainRole::SetProjectionMatrix(mat4 &mat)
{
	_mxProjection = mat;
	_bUpdateProj = true;
}

void MainRole::SetTRSMatrix(mat4 &mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}

void MainRole::SetAlpha(float alpha)
{
	for( int i = 0 ; i < Point_NUM; i++ ) {
		
		_Colors[i].w = alpha;
	}
	glBindBuffer( GL_ARRAY_BUFFER, _VBO );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors );
}

void MainRole::SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[])
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

	glBindBuffer( GL_ARRAY_BUFFER, _VBO );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors );
}

void MainRole::Draw()
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


	glDrawArrays(GL_TRIANGLE_FAN, 0, body_circle);
	glDrawArrays(GL_TRIANGLE_FAN, body_circle, head_circle);
	glDrawArrays(GL_TRIANGLE_FAN, body_circle + head_circle, circle);
	glDrawArrays(GL_TRIANGLE_FAN, body_circle + head_circle + circle, circle);
	glDrawArrays(GL_TRIANGLES, body_circle + head_circle + (circle*2), rectangle);
	glDrawArrays(GL_TRIANGLES, body_circle + head_circle + (circle * 2)+ rectangle, rectangle);
	glDrawArrays(GL_TRIANGLE_FAN, body_circle + head_circle + (circle * 2) + (rectangle*2), circle);
	glDrawArrays(GL_TRIANGLE_FAN, body_circle + head_circle + (circle * 3) + (rectangle * 2), circle);
	glDrawArrays(GL_TRIANGLE_FAN, body_circle + head_circle + (circle * 4) + (rectangle * 2), circle);
	glDrawArrays(GL_TRIANGLES, body_circle + head_circle + (circle * 5) + (rectangle * 2), triangle);
	glDrawArrays(GL_TRIANGLES, body_circle + head_circle + (circle * 5) + (rectangle * 2)+ triangle, rectangle);
	glDrawArrays(GL_LINE_LOOP, body_circle + head_circle + (circle * 5) + (rectangle * 3) + triangle, circle);
	glDrawArrays(GL_LINE_LOOP, body_circle + head_circle + (circle * 6) + (rectangle * 3) + triangle, circle);

}



/*void MainRole::DrawW()
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


//偵測main role使否遭受碰撞
void MainRole::AutoCheckHurt_MainRole(GLfloat x, GLfloat y, float Max_X, float MAX_Y, bool *HurtMainRole , int *defense_ball) {
	

	if (_x - this->MAX_X <= x - Max_X && _x + this->MAX_X >= x + Max_X && _y + this->MAX_Y >= y + MAX_Y && _y - this->MAX_Y <= y - MAX_Y  && can_change_hurtMain)//偵測是否位於攻擊範圍 且是否為可攻擊狀態
	{
		//printf("yes");
		*HurtMainRole = true;
		can_change_hurtMain = false;
		*defense_ball = *defense_ball - 1; //少一命
		


	}

	

}