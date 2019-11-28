#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int Smoke_circle = 50;

const int Smoke_Point_NUM = Smoke_circle * 16; //最大點子總數


class Smoke
{
public:
	Smoke();
	~Smoke() {};

	bool used = false;//空間是否被利用

	GLfloat _x = 0.0f;
	GLfloat _y = -3.0f; //一開始不得出現於螢幕上


	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _Program; }
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	void SetTRSMatrix(mat4& mat);

	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color


	void Draw(); //宣告為虛擬類別，於各自類別中設計

	float timer_smoke = 0;

	//移動矩陣
	mat4 mxTran_Smoke;
	//自動移動函式
	void AutomaticMotion(float boss_x, float boss_y,float delta);

	void SetAlpha(GLfloat alpha);
	GLfloat alphea_Smoke = 1.0f;


	float dis_x = 0; //相差多少寬
	float dis_y = 0; //相差多少高




private:

	vec4 _Points[Smoke_Point_NUM];
	vec4 _Colors[Smoke_Point_NUM];

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

	void CreateBufferObject();

	// 紀錄是否有矩陣的更新
	bool  _bUpdateMV;
	bool  _bUpdateProj;
	bool if_first_alien = true; //第一次發出Smoke

};