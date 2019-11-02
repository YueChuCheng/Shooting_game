#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;



const int MainRole_Point_NUM = 200;

class MainRole_Ring
{
public:
	MainRole_Ring();
	~MainRole_Ring();
	GLfloat _x = 0;
	GLfloat _y = 0;
	GLfloat _scale = 1;

	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _Program; }
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	void SetTRSMatrix(mat4& mat);
	void SetColor(GLfloat vColor[4]); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color

	void Draw();
	void DrawW();

private:

	vec4 _Points[MainRole_Point_NUM];
	vec4 _Colors[MainRole_Point_NUM];

	// VAO
	GLuint _VAO;
	// VBO
	GLuint _VBO;
	//  for Shader
	GLuint _Program;
	// Vertex Position Attribute
	GLuint _ModelView, _Projection;
	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;

	// 紀錄是否有矩陣的更新
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	void CreateBufferObject();


};

