#include "../Header/Angel.h"

typedef Angel::vec4 color4;
typedef Angel::vec4 point4; 

const int Bullet_Main_Head = 80;
const int Bullet_Main_Button = 6;

const int Bullet_Main_Point_NUM = Bullet_Main_Head + Bullet_Main_Button;

extern bool addspeed; //�Y�I��super cube �h�[�t;

class Bullet_Main
{
public:
	Bullet_Main();
	~Bullet_Main();
	GLfloat _x = 0.0f;
	GLfloat _y = 0.0f;
	GLfloat _scale = 1.0f;
	GLfloat _speed = 0.0f;
	short fire_style; //�p�l�u�����覡

	virtual void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	virtual void SetTRSMatrix(mat4& mat);
	void SetColor(GLfloat vColor[4]); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color
	virtual void Draw();
	//virtual void DrawW() = 0;
	GLuint GetShaderHandle() { return _Program; }

	mat4 BulletTrans;


	const float MAX_X = 0.05f; //�̪��e
	const float MAX_Y = 0.2f; //�̰��I

	
	

	//�۰ʲ��ʪ���
	virtual void AutoTranslate_Bullet();

	bool HurtAlien =false ;  //�O�_����Alien

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


	void CreateBufferObject();




protected:
	// �����O�_���x�}����s
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	
};




enum sSBullet_direction //�p�Ǥl�u������V
{
	LEFT_45, RIGHT_45, NORMAL
};

const int Bullet_SAlien_Point_NUM = 20;

class Bullet_SAlien :public Bullet_Main
{
public:
	Bullet_SAlien ();
	~Bullet_SAlien ();
	bool HurtMainRole = false;  //�O�_����Alien
	void AutoTranslate_Bullet();
	void Draw();
	void DrawW();
	GLuint GetShaderHandle() { return _Program; }

	void SetTRSMatrix(mat4& mat);

	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);



private:
	vec4 _Points[Bullet_SAlien_Point_NUM];
	vec4 _Colors[Bullet_SAlien_Point_NUM];

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

};

const int Bullet_MAlien_Point_NUM = 20;

class Bullet_MAlien :public Bullet_Main
{
public:
	Bullet_MAlien();
	~Bullet_MAlien();
	bool HurtMainRole = false;  //�O�_����Alien

	float MainRoleDis_x = 0.0f; //����x��V�첾
	float MainRoleDis_y = 0.0f; //����y��V�첾

	void AutoTranslate_Bullet();
	void Draw();
	void DrawW();
	void SetTRSMatrix(mat4& mat);
	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);

	GLuint GetShaderHandle() { return _Program; }
private:
	vec4 _Points[Bullet_MAlien_Point_NUM];
	vec4 _Colors[Bullet_MAlien_Point_NUM];

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

};


enum direction
{
	LEFT , RIGHT , TOP , BOTTOM
};
const int Bullet_BAlienMode2_Point_NUM = 20;

//BOSS �ĤG�Ҧ������l�u
class Bullet_BAlien :public Bullet_Main
{
public:
	Bullet_BAlien();
	~Bullet_BAlien();
	bool HurtMainRole = false;  //�O�_����Alien

	
	void AutoTranslate_Bullet();
	void Draw();
	void DrawW();
	void SetTRSMatrix(mat4& mat);
	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);

	GLuint GetShaderHandle() { return _Program; }

	short first_direction_x; //�l�u�Ĥ@�Ӧ�|��V
	short first_direction_y; //�l�u�Ĥ@�Ӧ�|��V

private:
	vec4 _Points[Bullet_BAlienMode2_Point_NUM];
	vec4 _Colors[Bullet_BAlienMode2_Point_NUM];

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

};

