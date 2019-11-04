#include "../Header/Angel.h"

typedef Angel::vec4 color4;
typedef Angel::vec4 point4; 



const int Bullet_Main_Point_NUM = 200 ;

class Bullet_Main
{
public:
	Bullet_Main();
	~Bullet_Main();
	GLfloat _x = 0.0f;
	GLfloat _y = 0.0f;
	GLfloat _scale = 1.0f;
	GLfloat _speed = 0.0f;
	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	void SetTRSMatrix(mat4& mat);
	void SetColor(GLfloat vColor[4]); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color
	void Draw();
	void DrawW();

	mat4 BulletTrans;


	//自動移動物件
	void AutoTranslate_Bullet();



private:
	vec4 _Points[Bullet_Main_Point_NUM];
	vec4 _Colors[Bullet_Main_Point_NUM];

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

