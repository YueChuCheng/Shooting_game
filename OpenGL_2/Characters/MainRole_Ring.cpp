#include "MainRole_Ring.h"


MainRole_Ring::MainRole_Ring()
{
	

	//外圍環
	for (int i = 0; i < Ring; i++)
	{
		//Y扣0.1使戰機於圓圈的中心
		_Points[i] = vec4(1.0f * cosf(2.0f * M_PI * i / Ring), 1.0 * sinf(2.0f * M_PI * i / Ring), 0.0f, 1.0f);
	}

	for (int i = 0; i < Ring; i++)
	{
		_Colors[i] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}


	//外回環球
	//R
	for (int i = 0; i < Ring_ball; i++)
	{
		_Points[i+ Ring] = vec4(0.1f * cosf(2.0f * M_PI * i / Ring_ball) , 0.1 * sinf(2.0f * M_PI * i / Ring_ball)+1.0 , 0.0f, 1.0f);
	}

	for (int i = 0; i < Ring_ball; i++)
	{
		_Colors[i+ Ring] = vec4(0.9921f, 0.0039f, 0.0f, 1.0f);
	}

	//B
	for (int i = 0; i < Ring_ball; i++)
	{
		_Points[i + Ring + Ring_ball] = vec4(0.1f * cosf(2.0f * M_PI * i / Ring_ball)+ 0.866, 0.1 * sinf(2.0f * M_PI * i / Ring_ball) - 0.5 , 0.0f, 1.0f);
	}

	for (int i = 0; i < Ring_ball; i++)
	{
		_Colors[i + Ring + Ring_ball] = vec4(0.2187f, 0.6171f, 0.7734f, 1.0f);
	}

	//Y
	for (int i = 0; i < Ring_ball; i++)
	{
		_Points[i + Ring + (Ring_ball * 2)] = vec4(0.1f * cosf(2.0f * M_PI * i / Ring_ball) - 0.866f, 0.1 * sinf(2.0f * M_PI * i / Ring_ball) - 0.5, 0.0f, 1.0f);
	}

	for (int i = 0; i < Ring_ball; i++)
	{
		_Colors[i + Ring + (Ring_ball * 2)] = vec4(0.9531f, 0.9375f, 0.3828, 1.0f);
	}


	//校正大小已於AutomaticRotation處校正
	/*for (int i = 0; i < Ring_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (6.5 / 10.0);
		_Points[i].y = _Points[i].y * (360.0 / 640.0) * (6.5 / 10.0);
		
	}
	*/
	CreateBufferObject();
	_bUpdateProj = false;
}


void MainRole_Ring::CreateBufferObject()
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

void MainRole_Ring::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) _Program = InitShader("vsMainRole_Ring.glsl", "fsMainRole_Ring.glsl");
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

void MainRole_Ring::SetViewMatrix(mat4& mat)
{
	_mxView = mat;
	_bUpdateMV = true;
}

void MainRole_Ring::SetProjectionMatrix(mat4& mat)
{
	_mxProjection = mat;
	_bUpdateProj = true;
}

void MainRole_Ring::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}

void MainRole_Ring::SetColor(GLfloat vColor[4])
{
	for (int i = 0; i < Ring_Point_NUM; i++) {
		_Colors[i].x = vColor[0];
		_Colors[i].y = vColor[1];
		_Colors[i].z = vColor[2];
		_Colors[i].w = vColor[3];
	}
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
}

void MainRole_Ring::SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[])
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



void MainRole_Ring::SetDefenseBall() { //設定有幾顆防禦球


	switch (_defenceBallNUM) //幾顆防禦球
	{

	case 0:
		break;

	case 1:
		glDrawArrays(GL_LINE_LOOP, 0, Ring);
		glDrawArrays(GL_TRIANGLE_FAN, Ring, Ring_ball);
		break;

	case 2:
		glDrawArrays(GL_LINE_LOOP, 0, Ring);
		glDrawArrays(GL_TRIANGLE_FAN, Ring, Ring_ball);
		glDrawArrays(GL_TRIANGLE_FAN, Ring + Ring_ball, Ring_ball);
		break;

	case 3:
		glDrawArrays(GL_LINE_LOOP, 0, Ring);
		glDrawArrays(GL_TRIANGLE_FAN, Ring, Ring_ball);
		glDrawArrays(GL_TRIANGLE_FAN, Ring + Ring_ball, Ring_ball);
		glDrawArrays(GL_TRIANGLE_FAN, Ring + (Ring_ball * 2), Ring_ball);
		break;



	default:
		glDrawArrays(GL_LINE_LOOP, 0, Ring);
		glDrawArrays(GL_TRIANGLE_FAN, Ring, Ring_ball);
		glDrawArrays(GL_TRIANGLE_FAN, Ring + Ring_ball, Ring_ball);
		glDrawArrays(GL_TRIANGLE_FAN, Ring + (Ring_ball * 2), Ring_ball);

		break;
	}
	

}



void MainRole_Ring::Draw()
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
	
	SetDefenseBall(); //防禦球函數
}




//自動旋轉
void MainRole_Ring:: AutomaticRotation(mat4 mainrole_mxTran) {

	//防止角度溢位
	if (_rotate > 360) {
		_rotate -= 360;
	}


	mxAutoRotate_Ring = RotateZ(_rotate += 0.5);

	//rotate 需要做校正 
	mxAutoRotate_Ring._m[0] *= (6.5 / 10.0);
	mxAutoRotate_Ring._m[1] *= (360.0 / 640.0) * (6.5 / 10.0);

	SetTRSMatrix(mainrole_mxTran * mxTran_Ring * mxAutoRotate_Ring);

}
