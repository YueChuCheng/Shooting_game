#include"SuperCub.h"

extern bool touch_superCube;
extern bool touch_twoGunStar;

SuperCube::SuperCube()
{

	_Points[0] = vec4(0.0, sqrt(3.0) - (1/(2+ sqrt(3.0))) - (1 / (2 + sqrt(3.0))),0.0f,1.0f);
	_Points[1] = vec4(-1.0, - 2 / (2 + sqrt(3.0)), 0.0f, 1.0f);
	_Points[2] = vec4(1.0, -2 / (2 + sqrt(3.0)), 0.0f, 1.0f);
	

	_Points[3] = vec4(1.0, 2 / (2 + sqrt(3.0)), 0.0f, 1.0f);
	_Points[4] = vec4(-1.0, 2 / (2 + sqrt(3.0)), 0.0f, 1.0f);
	_Points[5] = vec4(0.0, - sqrt(3.0) + (1 / (2 + sqrt(3.0))) + (1 / (2 + sqrt(3.0))), 0.0f, 1.0f);
	
	
	


	for (int i = 6; i < 6 + SuperCube_circle; i++)
	{
		_Points[i] = vec4(1.7f * cosf(2.0f * M_PI * i / SuperCube_circle), 1.7f * sinf(2.0f * M_PI * i / SuperCube_circle), 0.0f, 1.0f);
	}


	for (int i = 0; i < 6; i++)
		{
			_Colors[i] = vec4(1.0,0.0,0.0,1.0);
	}


	for (int i = 6; i < SuperCube_Point_NUM; i++)
	{
		_Colors[i] = vec4(1.0, 0.0, 0.0, 0.5);
	}



	//super cube校正比例
	for (int i = 6; i < SuperCube_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x * (2.0 / 10.0) ;
		_Points[i].y = _Points[i].y * (360.0 / 640.0) * (2.0 / 10.0) - 0.03f;

	}


	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}


void SuperCube::CreateBufferObject()
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

void SuperCube::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
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

void SuperCube::SetViewMatrix(mat4& mat)
{
	_mxView = mat;
	_bUpdateMV = true;
}

void SuperCube::SetProjectionMatrix(mat4& mat)
{
	_mxProjection = mat;
	_bUpdateProj = true;
}

void SuperCube::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}

void SuperCube::SetAlpha(GLfloat alpha)
{
	for (int i = 0; i < SuperCube_Point_NUM; i++) {
		_Colors[i].w = alpha;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
}

void SuperCube::SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[])
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

void SuperCube::Draw()
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


	if (cubeStyle == HIT)
	{
		if(!touch_superCube){
	
				glDrawArrays(GL_TRIANGLES, 0, SuperCube_triangle);
				glDrawArrays(GL_TRIANGLES, SuperCube_triangle, SuperCube_triangle);

	
			}
			else if(touch_superCube){
	
				glDrawArrays(GL_TRIANGLE_FAN, SuperCube_triangle * 2, SuperCube_circle);
			}
	}

	else if (cubeStyle == TWO_GUN)
	{
		if (!touch_twoGunStar) {

			glDrawArrays(GL_TRIANGLES, 0, SuperCube_triangle);
			glDrawArrays(GL_TRIANGLES, SuperCube_triangle, SuperCube_triangle);
			
		}
	
	}



	
	



}


void SuperCube::AutomaticMotion( float mainrole_x , float mainrole_y) {
	

	if (cubeStyle == HIT) {


		if(!touch_superCube ){ //Main Role尚未碰到 superCube
			if (if_first_cube) { //一開始發射cube

				_x = (double)(rand() % 3000 - 1000.0) / 1000.0;
				_y = 2.0f;
				theta = 0.0f;
				mxRotate_SuperCube = RotateZ(theta);
				mxTran_SuperCube = Translate(_x, _y, 0.0);
				SetTRSMatrix(mxTran_SuperCube * mxRotate_SuperCube);

				if_first_cube = false;
			}


			if (_y < -2.0f) {

				used = false;
			}


			if (theta > 360.0f) {//避免角度溢位
				theta -= 360.0f;

			}

			_y -= 0.001f;

			mxRotate_SuperCube = RotateZ(theta -= 0.5f);
			mxRotate_SuperCube._m[0] *= (2.0 / 10.0);
			mxRotate_SuperCube._m[1] *= (360.0 / 640.0) * (2.0 / 10.0);

			mxTran_SuperCube = Translate(_x, _y, 0.0);

			SetTRSMatrix(mxTran_SuperCube * mxRotate_SuperCube);
	
		} 

		else //Main Role碰到 superCube ，跟隨main role 位置
		{
			_x = mainrole_x;
			_y = mainrole_y;
			mxTran_SuperCube = Translate(_x, _y, 0.0);

			SetTRSMatrix(mxTran_SuperCube);


		}

	}



	else if (cubeStyle == TWO_GUN) {


		if (!touch_twoGunStar) { //Main Role尚未碰到 superCube
			if (if_first_cube) { //一開始發射cube

				_x = (double)(rand() % 3000 - 1000.0) / 1000.0;
				_y = 2.0f;
				theta = 0.0f;
				mxRotate_SuperCube = RotateZ(theta);
				mxTran_SuperCube = Translate(_x, _y, 0.0);
				SetTRSMatrix(mxTran_SuperCube * mxRotate_SuperCube);

				if_first_cube = false;
			}


			if (_y < -2.0f) {

				used = false;
			}


			if (theta > 360.0f) {//避免角度溢位
				theta -= 360.0f;

			}

			_y -= 0.001f;

			mxRotate_SuperCube = RotateZ(theta -= 0.5f);
			mxRotate_SuperCube._m[0] *= (2.0 / 10.0);
			mxRotate_SuperCube._m[1] *= (360.0 / 640.0) * (2.0 / 10.0);

			mxTran_SuperCube = Translate(_x, _y, 0.0);

			SetTRSMatrix(mxTran_SuperCube * mxRotate_SuperCube);

		}

		else //Main Role碰到 superCube ，跟隨main role 位置
		{
			_x = mainrole_x;
			_y = mainrole_y;
			mxTran_SuperCube = Translate(_x, _y, 0.0);

			SetTRSMatrix(mxTran_SuperCube);


		}

	}


	


}



//檢查是否被main role碰到
void SuperCube::CheackMainRole(GLfloat x, GLfloat y, float Max_X, float MAX_Y) {

	if (cubeStyle == HIT)
	{
		if (_x - this->MAX_X <= x - Max_X && _x + this->MAX_X >= x + Max_X && _y + this->MAX_Y >= y + MAX_Y && _y - this->MAX_Y <= y - MAX_Y )//偵測是否位於攻擊範圍 且是否為可攻擊狀態
			{
		
				touch_superCube = true;

				this->MAX_X = 0.7f; //最長寬
				this->MAX_Y = 0.7f; //最高點

		
		
			}
	}

	else if (cubeStyle == TWO_GUN) {


		if (_x - this->MAX_X <= x - Max_X && _x + this->MAX_X >= x + Max_X && _y + this->MAX_Y >= y + MAX_Y && _y - this->MAX_Y <= y - MAX_Y)//偵測是否位於攻擊範圍 且是否為可攻擊狀態
		{
			touch_twoGunStar = true;
			used = false;
		}

	}

	




}