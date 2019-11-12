#include "../Header/Angel.h"

typedef Angel::vec4 color4;
typedef Angel::vec4 point4; 

const int Bullet_Main_Head = 80;
const int Bullet_Main_Button = 6;

const int Bullet_Main_Point_NUM = Bullet_Main_Head + Bullet_Main_Button;



class Bullet_Main
{
public:
	Bullet_Main();
	~Bullet_Main();
	GLfloat _x = 0.0f;
	GLfloat _y = 0.0f;
	int Bullet_UseSpace; //計算使用哪個陣列
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
	GLuint GetShaderHandle() { return _Program; }

	mat4 BulletTrans;


	const float MAX_X = 0.05f; //最長寬
	const float MAX_Y = 0.2f; //最高點

	
	

	//自動移動物件
	virtual void AutoTranslate_Bullet();

	bool HurtAlien =false ;  //是否打中Alien

protected:
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








class Bullet_SAlien :public Bullet_Main
{
public:
	Bullet_SAlien ();
	~Bullet_SAlien ();
	bool HurtMainRole = false;  //是否打中Alien

	void AutoTranslate_Bullet();
private:

};



class Bullet_MAlien :public Bullet_Main
{
public:
	Bullet_MAlien();
	~Bullet_MAlien();
	bool HurtMainRole = false;  //是否打中Alien

	mat4 _mxMainRoleRotate = 0.0f; //紀錄Main Role 選轉角度
	float MainRoleDis_x = 0.0f; //移動x方向位移
	float MainRoleDis_y = 0.0f; //移動y方向位移

	void AutoTranslate_Bullet();
private:

};



