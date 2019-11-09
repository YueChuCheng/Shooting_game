#include "Bullet_Main.h"

Bullet_Main::~Bullet_Main()
{
}


Bullet_Main::Bullet_Main()
{
	float w = 0.045f; //half width
	float h = 0.08f;

	for (int i = 0; i < Bullet_Main_Head; i++)
	{
		
		float x = w - (i * (( 2.0f * w ) / (float)Bullet_Main_Head));
		float y = ((-2.0f * h) / ( w * w )) * x * x + h;

		_Points[i ] = vec4(x, y, 0.0f, 1.0f);
		
	}

	_Points[0 + Bullet_Main_Head] = vec4(-w , h   - h  - 0.02, 0.0f, 1.0f);
	_Points[1 + Bullet_Main_Head] = vec4(-w, -h  - h - 0.02, 0.0f, 1.0f);
	_Points[2 + Bullet_Main_Head] = vec4(w, -h  - h - 0.02, 0.0f, 1.0f);
	_Points[3 + Bullet_Main_Head] = vec4(-w, h  - h - 0.02, 0.0f, 1.0f);
	_Points[4 + Bullet_Main_Head] = vec4(w, -h  - h - 0.02, 0.0f, 1.0f);
	_Points[5 + Bullet_Main_Head] = vec4(w, h  - h - 0.02, 0.0f, 1.0f);




	for (int i = 0; i < Bullet_Main_Point_NUM; i++)
	{

		_Colors[i] = vec4(0.9960f , 0.5507f , 0.25f, 1.0f);

	}


	//校正
	for (int i = 0; i < Bullet_Main_Point_NUM; i++)
	{
		_Points[i].x = _Points[i].x;
		_Points[i].y = _Points[i].y * (360.0 / 640.0) + 0.2f; // + 0.2 子彈射出的起始位置校正
	}

	CreateBufferObject();


}


void Bullet_Main::CreateBufferObject()
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



void Bullet_Main::SetShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
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



void Bullet_Main::SetViewMatrix(mat4& mat)
{
	_mxView = mat;
	_bUpdateMV = true;
}

void Bullet_Main::SetProjectionMatrix(mat4& mat)
{
	_mxProjection = mat;
	_bUpdateProj = true;
}

void Bullet_Main::SetTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}

void Bullet_Main::SetColor(GLfloat vColor[4])
{
	for (int i = 0; i < Bullet_Main_Point_NUM; i++) {
		_Colors[i].x = vColor[0];
		_Colors[i].y = vColor[1];
		_Colors[i].z = vColor[2];
		_Colors[i].w = vColor[3];
	}
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
}

void Bullet_Main::SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[])
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






void Bullet_Main::Draw()
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

	
	glDrawArrays(GL_TRIANGLE_FAN, 0, Bullet_Main_Head);
	glDrawArrays(GL_TRIANGLE_FAN, Bullet_Main_Head, Bullet_Main_Button);
	
}


//Bullet_Main Update



/*void Bullet_Main::DrawW()
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



//子彈往前飛
void Bullet_Main::AutoTranslate_Bullet() {

	_y += 0.01;
	BulletTrans = Translate(_x , _y , 0.0);
	SetTRSMatrix(BulletTrans);

}