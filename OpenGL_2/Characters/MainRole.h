
#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


const int body_circle = 200;
const int head_circle = 200;
const int circle = 200;
const int rectangle = 6;
const int triangle = 6;
const int Point_NUM = body_circle+ head_circle+ (circle*7)+ (rectangle*4) + triangle; // 2 faces, 2 triangles/face 

class MainRole
{
private:
	vec4 _Points[Point_NUM];
	vec4 _Colors[Point_NUM];
	// VAO
	GLuint _VAO;
	// VBO
	GLuint _VBO;
	//  for Shader
	GLuint _Program ;
	// Vertex Position Attribute
	GLuint _ModelView, _Projection;
	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;

	// �����O�_���x�}����s
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	

	void CreateBufferObject();
public:

	MainRole();
	GLfloat _x = 0;
	GLfloat _y = 0;
	GLfloat _scale = 1;

	void SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle=MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _Program;}
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color
	
	void Draw();
	void DrawW();
};



