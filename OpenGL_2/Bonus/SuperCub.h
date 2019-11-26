#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int SuperCube_triangle = 3;
const int SuperCube_circle = 50;
const int SuperCube_Point_NUM = SuperCube_circle + SuperCube_triangle * 2; //最大點子總數

enum Cube_style
{
	HIT = 0 , TWO_GUN = 1
};


class SuperCube
{
public:
	SuperCube();
	~SuperCube() {};

	int cubeStyle; //cube 的型態
	
	bool used = false;//空間是否被利用
	bool if_first_cube = false;


	GLfloat _x = 0.0f;
	GLfloat _y = 3.0f; //一開始不得出現於螢幕上


	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _Program; }
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	void SetTRSMatrix(mat4& mat);

	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color
	void Draw(); //宣告為虛擬類別，於各自類別中設計
	
	void CheackMainRole(GLfloat x, GLfloat y, float Max_X, float MAX_Y); //檢查是否被main role碰到


	//移動矩陣
	mat4 mxTran_SuperCube;
	mat4 mxRotate_SuperCube;

	//自動移動函式
	void AutomaticMotion(float mainrole_x, float mainrole_y);

	void SetColor(GLfloat r, GLfloat g, GLfloat b);
	
	
	float MAX_X = 0.5f; //最長寬
	float MAX_Y = 0.5f; //最高點


private:

	float theta = 0.0f; //紀錄選轉角度
	
	vec4 _Points[SuperCube_Point_NUM];
	vec4 _Colors[SuperCube_Point_NUM];

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
	bool if_first_alien = true; //第一次發出SuperCube

	


};
