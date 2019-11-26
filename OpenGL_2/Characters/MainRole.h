
#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


const int body_circle = 100;
const int head_circle = 150;
const int circle = 100;
const int rectangle = 6;
const int triangle = 6;
const int Point_NUM = body_circle+ head_circle+ (circle*7)+ (rectangle*4) + triangle; // 2 faces, 2 triangles/face 

class MainRole
{

public:

	MainRole();
	~MainRole() {};
	GLfloat _x = 0;
	GLfloat _y = 0;
	GLfloat _scale = 1;

	void SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle=MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _Program;}
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetAlpha(float alpha); // 設定透明度
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color
	
	void Draw();
	void DrawW();

	void AutoCheckHurt_MainRole(GLfloat x , GLfloat y , float Max_Y , float MAX_Y , bool *HurtMainRole, int *defense_ball);

	bool can_change_hurtMain = true; //自己是否有受傷
	

	const float MAX_X = 0.3f; //最長寬
	const float MAX_Y = 0.3f; //最高點

	//移動矩陣
	mat4 mxTran_Main;

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

	// 紀錄是否有矩陣的更新
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	


	void CreateBufferObject();

};



